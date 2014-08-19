#include "QFingerScrollArea.h"
#include <QWidget>
#include <QApplication>
#include <QDesktopWidget>
#include <QScrollBar>
#include <QMouseEvent>
#include <QTimerEvent>
#include <QChildEvent>
#include <QList>
#include <QTimer>
#include <stdlib.h>
#include <QDebug>


const int QPrivateFingerScroller::START_WITHIN    = 100;  // must move within X ms to scroll
const int QPrivateFingerScroller::SENSITIVITY     = 50;   // pixels before we scroll
const int QPrivateFingerScroller::KINETIC_REFRESH = 50;   // ms
const int QPrivateFingerScroller::VSCALE          = 100;  // velocity scaling to ensure not lost in int rounding
const int QPrivateFingerScroller::DECEL_PC        = 93;   // velocity reduction factor/kinetic refresh (%)
const int QPrivateFingerScroller::DECEL_DURATION  = 150; // ms
const int QPrivateFingerScroller::VMAX            = 100;  // Max velocity
const int QPrivateFingerScroller::MAX_OVERSHOOT   = 20;  // max pixels to overshoot
const int QPrivateFingerScroller::OVERSHOOT_DECEL_PC = 50;   // velocity reduction factor/kinetic refresh (%)
const int QPrivateFingerScroller::REBOUND_ACCEL   = 10;   // accel to apply when stabilising overshoot

// QFingerScrollArea a QScrollArea that responds to fingers
QFingerScrollArea::QFingerScrollArea(QWidget * parent) :QScrollArea(parent), scroller(0)
{
    if (! parent->property("FingerScrollable").isValid()) {
        //DEBUG("Register scroller");
        scroller = new QPrivateFingerScroller(this);
    }
}


QPrivateFingerScroller::QPrivateFingerScroller(QScrollArea *parent_area) :
    QObject(parent_area),
    qsa(parent_area),
    scrollState(NotScrolling),
    xScrollState(NotScrolling),
    yScrollState(NotScrolling),
    scrollBase(0,0),
    start(0,0),
    curr(0,0),
    scrollFactor(),
    last(0,0),
    vel(0,0),
    vel1(0,0),
    last_ev_time(0),
    curr_time(0)
{
    registerChildrenForFingerScrolling(parent_area);
}

////////////////////////////////////////////////////////////////
// Finger scroll implementation - movement
bool QPrivateFingerScroller::eventFilter(QObject *obj, QEvent *event)
{
//	_ENTER;
//	qDebug() << "event->type() =" << event->type();
    if (scrollState == ReissuingEvents or ! obj->isWidgetType()) {
//		qDebug() << "Ignoring event->type() =" << event->type() << " Scrollstate = " << scrollState;
        return false ; // ignore events during re-issue. Should this be QObject::eventFilter(obj, event);
    }

    QMouseEvent * mEv = dynamic_cast<QMouseEvent *>(event);

    QScrollBar* vsb = qsa->verticalScrollBar();
    qsa->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QScrollBar* hsb = qsa->horizontalScrollBar();

    if (scrollState == AutoScroll) {
        // We're already doing a kinetic movement. A click resets.
        if (event->type() == QEvent::MouseButtonPress and
            mEv and mEv->button() == Qt::LeftButton){
            scrollState = NotScrolling;
            xScrollState = NotScrolling;
            yScrollState = NotScrolling;
            // Fall through to maybe start another scroll
            // Would it be safer to kill the kinetic timer or just let it die?
        }
    }

    if (scrollState == NotScrolling) {
        if (event->type() == QEvent::MouseButtonPress and
            mEv and mEv->button() == Qt::LeftButton){
            start = mEv->globalPos();
            scrollBase.ry() = vsb->value(); // Record scrollbar at first touch - reduces jitter errors
            scrollBase.rx() = hsb->value();

            scrollFactor = QPointF();
            xScrollState = NotScrolling;
            yScrollState = NotScrolling;
            // We need to know the how much scrollBar->value changes per pixel of movement
            if ( vsb->minimum() < vsb->maximum()) {
                scrollFactor.ry() = (qreal) vsb->pageStep() / qsa->height();
//				qDebug() << "scrollFactor.y =" << scrollFactor.ry();
                yScrollState = Maybe;
            }
            if ( hsb->minimum() < hsb->maximum() ) {
                scrollFactor.rx() = (qreal) hsb->pageStep() / qsa->width();
//				qDebug() << "scrollFactor.x =" << scrollFactor.rx();
                xScrollState = Maybe;
            }

            if (xScrollState == NotScrolling and yScrollState == NotScrolling)
                return false; // We have no ability to scroll so don't try.

            if (! (eventSourceWidget = dynamic_cast<QWidget *>(obj)))
                return false; // just to be sure the object is a widget

            // We're definitely going to try and scroll if we get a move in time
            scrollState = Maybe;
//			qDebug() << "Queue in NotScrolling";
            storedEvents.enqueue(new QMouseEvent(*mEv)); // store the event for maybe replaying

            QTimer::singleShot(START_WITHIN, this, SLOT(replayEvents())); // this *will* fire..

            event_time.start();
            last_ev_time=0;
            mEv->accept(); // it's handled. The copy may be replayed.
            return true;
        }
    }

    if (scrollState == Maybe ) {
        if (event->type() == QEvent::MouseButtonRelease) {
//			qDebug() << "    QAbstractScrollArea::Released";
            if (mEv->button() != Qt::LeftButton) return false; // fall through, allow onward handling
//			qDebug() << "Queue in Maybe";
            storedEvents.enqueue(new QMouseEvent(*mEv));
            QTimer::singleShot(0, this, SLOT(replayEvents())); // immediate replay...
            mEv->accept(); // it's handled. The copy may be replayed.
            return true;
        }
        if (event->type() == QEvent::MouseMove) {
            handleMoveEvent(mEv);
            mEv->accept(); // it's handled. The copy may be replayed.
            return true;
        }
    }

    if (scrollState == ManualScroll) {
        if (event->type() == QEvent::MouseButtonRelease) {
            scrollState = NotScrolling;
            mEv->accept(); // it's handled.
            if (last_ev_time) { // Only do velocity if we had a last_ev_time
                vel1.rx() = qBound(-VMAX, vel1.rx(), VMAX);
                vel1.ry() = qBound(-VMAX, vel1.ry(), VMAX);
                vel = vel1; // make a copy of the initial velocity for direction
                curr_time = event_time.elapsed();
                // Note the current scroll values, possibly overshot
                curr = mEv->globalPos();
                scrollBase.ry() = scrollBase.ry() + ((start.ry() - curr.ry()) * scrollFactor.ry());
                scrollBase.rx() = scrollBase.rx() + ((start.rx() - curr.rx()) * scrollFactor.rx());
                curr = QPoint(); // rebase the pointer for the kinetic phase
                startTimer(KINETIC_REFRESH);
                scrollState = AutoScroll;
                if (xScrollState != NotScrolling) xScrollState = AutoScroll;
                if (yScrollState != NotScrolling) yScrollState = AutoScroll;
            }
            return true;
        }
        if (event->type() == QEvent::MouseMove) {
            handleMoveEvent(mEv);
            mEv->accept(); // it's handled. The copy may be replayed.
            return true;
        }
    }

    // Handle eventFilter to added/removed children

    if (event->type() ==  QEvent::ChildAdded or
        event->type() ==  70) { // FIX is this a Qt bug? 70 is ChildInserted which is
        // deprecated in 4.4 but it appears from time to time...
        registerChildrenForFingerScrolling(static_cast<QChildEvent *>(event)->child());
        return false;
    }

    if (event->type() == QEvent::ChildRemoved) {
        // deregisterChildrenForFingerScrolling
        QObject *childObj = static_cast<QChildEvent *>(event)->child();
        if (childObj->isWidgetType())
            childObj->removeEventFilter(this);
        QList<QObject *> children = childObj->findChildren<QObject *>();
        foreach (childObj, children){
            if (childObj->isWidgetType())
                childObj->removeEventFilter(this);
        }
        return false;
    }
    return false;
}

void QPrivateFingerScroller::handleMoveEvent ( QMouseEvent * event )
{
//	_ENTER;
//	qDebug() << "    QAbstractScrollArea::Released";
    if (scrollState == Maybe) {
        QPoint delta = start - event->globalPos();
        storedEvents.enqueue(new QMouseEvent(*event)); // we may need to play this back...
        int myX= abs(delta.rx());
        if (myX > SENSITIVITY) { // ...unless there's been enough movement
            scrollState = ManualScroll;
            if (xScrollState == Maybe) xScrollState = ManualScroll;
            if (yScrollState == Maybe) yScrollState = ManualScroll;
            while (!(storedEvents.isEmpty()))  // all previous events are ours; clean up
                delete storedEvents.dequeue() ;

        }
    }

    if (scrollState == ManualScroll) {
        curr = event->globalPos();

        int min_y = qsa->verticalScrollBar()->minimum();
        int max_y = qsa->verticalScrollBar()->maximum();
        int min_x = qsa->horizontalScrollBar()->minimum();
        int max_x = qsa->horizontalScrollBar()->maximum();
        int val_y = 0;
        int val_x = 0;
        int overshoot_x = 0;
        int overshoot_y = 0;

        if (yScrollState == ManualScroll) {
            val_y = scrollBase.ry() + ((start.ry() - curr.ry()) * scrollFactor.ry());
            if (val_y < min_y) {
                overshoot_y = min_y - val_y;
            } else if (val_y > max_y) {
                overshoot_y = max_y - val_y;
            }
            qsa->verticalScrollBar()->setValue(val_y);
        }
        if (xScrollState == ManualScroll) {
            val_x = scrollBase.rx() + ((start.rx() - curr.rx()) * scrollFactor.rx());
            if (val_x < min_x) {
                overshoot_x = min_x - val_x;
            } else if (val_x > max_x) {
                overshoot_x = max_x - val_x;
            }
            qsa->horizontalScrollBar()->setValue(val_x);
        }

        overshoot_y = qBound(-MAX_OVERSHOOT, overshoot_y, MAX_OVERSHOOT);
        overshoot_x = qBound(-MAX_OVERSHOOT, overshoot_x, MAX_OVERSHOOT);

//		qabstractscrollarea_d->drawOvershoot(overshoot_x, overshoot_y);

        curr_time = event_time.elapsed();

        if (curr_time >	last_ev_time){
            if (last_ev_time){  // first time round we set v to zero
                vel1 = vel;
                vel = QPoint((last - curr)*VSCALE / (curr_time - last_ev_time));
            } else {
                vel = QPoint(0,0);
                vel1 = QPoint(0,0);
            }
            // Store the last values
            last_ev_time = 	curr_time;
            last = curr;
        }
        event->accept();
    }
}



////////////////////////////////////////////////////////////////
// Kinetics, reissue pending events
void QPrivateFingerScroller::timerEvent(QTimerEvent *event)
{
    // Track the projected position using curr. This will allow bounce effects and smooths non-pixel scrolled areas
    // In general work in pixels and convert to scrollbar values at the end

    // frequently used
    QScrollBar* vsb = qsa->verticalScrollBar();
    QScrollBar* hsb = qsa->horizontalScrollBar();

    int min_y = vsb->minimum();
    int max_y = vsb->maximum();// - qabstractscrollarea_d->overshootBottom;
    int min_x = hsb->minimum();
    int max_x = hsb->maximum();// - qabstractscrollarea_d->overshootRight;
    int val_y = 0;
    int val_x = 0;
    int overshoot_x = 0;
    int overshoot_y = 0;
// Y

    if (yScrollState == NotScrolling)
        vel1.ry() = 0;

    if (yScrollState == AutoScroll) {
        // decelerate normally
        int y = curr.ry();
        curr.ry() += (vel1.ry() * KINETIC_REFRESH)/VSCALE;
        val_y = scrollBase.ry() + curr.ry() * scrollFactor.ry();
        if (min_y < val_y and val_y < max_y) { // in range
            vsb->setValue(val_y);
            vel1.ry() = (vel1.ry()*DECEL_PC)/100;
            if (-1.0 < vel1.ry() and vel1.ry() < 1.0) // ie: stopped
                yScrollState = NotScrolling;
        } else { // we would have passed the min/max so set the target
            if (min_y <= val_y)
                rest.ry() = max_y;
            else
                rest.ry() = min_y;
            curr.ry()  = y; // reset the current position
            yScrollState = OverShootDecel;
        }
    }

    if (yScrollState == OverShootDecel) {
        // Overshoot needs to track the virtual finger position over time and pull
        // it back to a position that represents the start/end of the area
        //qDebug() << "OverShootDecel y="  << curr.ry() << " v.y = " << vel1.ry();
        if (-1.0 < vel1.ry() and vel1.ry() < 1.0) {
            // we stopped (or we may have been placed here)
            val_y=scrollBase.ry() + curr.ry() * scrollFactor.ry();
            if (val_y < min_y) {
                overshoot_y = min_y - val_y;
            } else if (val_y > max_y) {
                overshoot_y = max_y - val_y;
            }
            vel1.ry() = 0;
            yScrollState = OverShootPause; // this actually stops us for a frame.
        } else {
            // we're slowing down
            curr.ry() += (vel1.ry() * KINETIC_REFRESH)/VSCALE;
            vel1.ry() = (vel1.ry()*OVERSHOOT_DECEL_PC)/100;
            val_y=scrollBase.ry() + curr.ry() * scrollFactor.ry();
            vsb->setValue(val_y); // Is this worth doing if we overshot
            if (val_y < min_y) {
                overshoot_y = min_y - val_y;
            } else if (val_y > max_y) {
                overshoot_y = max_y - val_y;
            }
        }
    }

    // rest is target resting place in val, not pixels
    // if y>rest then reduce vel
    if (yScrollState == OverShootStabilise) {
        val_y=scrollBase.ry() + curr.ry() * scrollFactor.ry();
        if (min_y <= val_y and val_y <= max_y) { // in range
            // run out of braking... force setting to min/max
            vsb->setValue(rest.ry());
            overshoot_y = 0;
            yScrollState = NotScrolling;
        } else {
            // accelerate towards rest
            if (val_y < min_y)
                vel1.ry() += 5;
            else
                vel1.ry() -= 5;
            curr.ry() += vel1.ry();
            val_y = scrollBase.ry() + curr.ry() * scrollFactor.ry();
            vsb->setValue(val_y); // in overshoot?
            if (val_y < min_y) {
                overshoot_y = min_y - val_y;
            } else if (val_y > max_y) {
                overshoot_y = max_y - val_y;
            }
            if (qAbs(vel1.ry()) <= 5)
                yScrollState = NotScrolling;
        }
    }

    // Pause is deliberately after OverShootStabilise to force a timerEvent cycle
    if (yScrollState == OverShootPause)
    {
        // there won't be any change, we just need to get the previous amount of overshoot
        val_y=scrollBase.ry() + curr.ry() * scrollFactor.ry();
        if (val_y < min_y) {
            overshoot_y = min_y - val_y;
        } else if (val_y > max_y)	{
            overshoot_y = max_y - val_y;
        }
        yScrollState = OverShootStabilise;
    }

// X

    if (xScrollState == NotScrolling)
        vel1.rx() = 0;

    if (xScrollState == AutoScroll) {
        // decelerate normally
        int x = curr.rx();
        curr.rx() += (vel1.rx() * KINETIC_REFRESH)/VSCALE;
        val_x = scrollBase.rx() + curr.rx() * scrollFactor.rx();
        if (min_x < val_x and val_x < max_x) { // in range
            hsb->setValue(val_x);
            vel1.rx() = (vel1.rx()*DECEL_PC)/100;
            if (-1.0 < vel1.rx() and vel1.rx() < 1.0) // ie: stopped
                xScrollState = NotScrolling;
        } else { // we would have passed the min/max so set the target
            if (min_x <= val_x)
                rest.rx() = max_x;
            else
                rest.rx() = min_x;
            curr.rx()  = x; // reset the current position
            xScrollState = OverShootDecel;
        }
    }

    if (xScrollState == OverShootDecel) {
        // Overshoot needs to track the virtual finger position over time and pull
        // it back to a position that represents the start/end of the list
        //qDebug() << "OverShootDecel x="  << curr.rx() << " v.x = " << vel1.rx();
        if (-1.0 < vel1.rx() and vel1.rx() < 1.0) {
            // we stopped (or we may have been placed here)
            val_x=scrollBase.rx() + curr.rx() * scrollFactor.rx();
            if (val_x < min_x) {
                overshoot_x = min_x - val_x;
            } else if (val_x > max_x) {
                overshoot_x = max_x - val_x;
            }
            vel1.rx() = 0;
            xScrollState = OverShootPause;

        } else {
            // we're slowing down
            curr.rx() += (vel1.rx() * KINETIC_REFRESH)/VSCALE;
            vel1.rx() = (vel1.rx()*OVERSHOOT_DECEL_PC)/100;
            val_x=scrollBase.rx() + curr.rx() * scrollFactor.rx();
            hsb->setValue(val_x);
            if (val_x < min_x) {
                overshoot_x = min_x - val_x;
            } else if (val_x > max_x) {
                overshoot_x = max_x - val_x;
            }
        }
    }

    if (xScrollState == OverShootStabilise) {
        val_x=scrollBase.rx() + curr.rx() * scrollFactor.rx();
        if (min_x <= val_x and val_x <= max_x) { // in range
            // run out of braking... force setting to min/max
            hsb->setValue(rest.rx());
            overshoot_x = 0;
            xScrollState = NotScrolling;
        } else {
            // accelerate towards rest
            if (val_x < min_x)
                vel1.rx() += 5;
            else
                vel1.rx() -= 5;
            curr.rx() += vel1.rx();
            val_x = scrollBase.rx() + curr.rx() * scrollFactor.rx();
            hsb->setValue(val_x); // in overshoot?
            if (val_x < min_x) {
                overshoot_x = min_x - val_x;
            } else if (val_x > max_x) {
                overshoot_x = max_x - val_x;
            }
            if (qAbs(vel1.rx()) <= 5)
                xScrollState = NotScrolling;
        }
    }

    // Pause is deliberately after OverShootStabilise to force a timerEvent cycle
    if (xScrollState == OverShootPause)
    {
        // there won't be any change, we just need to get the previous amount of overshoot
        val_x=scrollBase.rx() + curr.rx() * scrollFactor.rx();
        if (val_x < min_x) {
            overshoot_x = min_x - val_x;
        } else if (val_x > max_x) {
            overshoot_x = max_x - val_x;
        }
        xScrollState = OverShootStabilise;
    }

    overshoot_y = qBound(-MAX_OVERSHOOT, overshoot_y, MAX_OVERSHOOT);
    if (yScrollState == OverShootDecel and qAbs(overshoot_y) == MAX_OVERSHOOT) {
        vel1.ry() = 0;
        yScrollState = OverShootPause;
        curr.ry() = (-overshoot_y - scrollBase.ry())/scrollFactor.ry();
    }

    overshoot_x = qBound(-MAX_OVERSHOOT, overshoot_x, MAX_OVERSHOOT);
    if (xScrollState == OverShootDecel and qAbs(overshoot_x) == MAX_OVERSHOOT) {
        vel1.rx() = 0;
        xScrollState = OverShootPause;
        curr.rx() = (-overshoot_x - scrollBase.rx())/scrollFactor.rx();
    }

//	qabstractscrollarea_d->drawOvershoot(overshoot_x, overshoot_y);

    qsa->show();

    if (xScrollState == NotScrolling and yScrollState == NotScrolling) {
        //qDebug() << "Stopped timer";
        killTimer(event->timerId());
        scrollState = NotScrolling;
    }
}

void QPrivateFingerScroller::registerChildrenForFingerScrolling(QObject *obj)
{
//	_ENTER;
//	if (qobject_cast<QAbstractScrollArea *>(obj)) return; // Ignore any QAbstractScrollArea derived objects and hence their children

    if (obj->isWidgetType())
        obj->installEventFilter(this);

    foreach (QObject* child, obj->children()){
        registerChildrenForFingerScrolling(child);
    }
}
void QPrivateFingerScroller::replayEvents()
{
//	_ENTER;
    if (scrollState != Maybe) return;

    QEvent *ev;
    scrollState = ReissuingEvents;
    while (!storedEvents.isEmpty()) {
        ev = storedEvents.dequeue() ;
        if (! eventSourceWidget.isNull()) {
            qApp->notify(eventSourceWidget, ev);
        }
        delete ev;
    }
    scrollState = NotScrolling;
}
