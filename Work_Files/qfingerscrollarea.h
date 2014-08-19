#ifndef SHOPPER_UI_QFINGERSCROLLAREA_H
#define SHOPPER_UI_QFINGERSCROLLAREA_H

#include <QScrollArea>
#include <QTime>
#include <QQueue>
#include <QPointer>
#include <QScrollBar>
#include <QTimerEvent>
#include <QEvent>



class QAbstractScrollAreaPrivateScroller;

class QAbstractScrollAreaScrollBarContainer;

class QPrivateFingerScroller;

class QFingerScrollArea: public QScrollArea
{
        Q_OBJECT

    public:
        QFingerScrollArea(QWidget * parent = 0);
    private:
        QPrivateFingerScroller* scroller;
};

class QPrivateFingerScroller: public QObject
    {
        Q_OBJECT

    public:
        QPrivateFingerScroller(QScrollArea * parent = 0);

        // Operational
        bool eventFilter(QObject *obj, QEvent *event);

    protected Q_SLOTS:
        void replayEvents();

    protected:
        void handleMoveEvent ( QMouseEvent * event );
        void timerEvent(QTimerEvent *event);
        void registerChildrenForFingerScrolling(QObject *top);

        static const int SENSITIVITY, KINETIC_REFRESH, VSCALE,
            DECEL_DURATION, DEBOUNCE, DECEL_PC, START_WITHIN,
            VMAX, MAX_OVERSHOOT, OVERSHOOT_DECEL_PC, REBOUND_ACCEL;
    QScrollArea  *qsa;  // the area we're scrolling


    typedef enum { NotScrolling = 0, Maybe, ManualScroll, AutoScroll,
                   OverShootDecel, OverShootPause, OverShootStabilise,
                   ReissuingEvents } ScrollState;

    ScrollState  scrollState, xScrollState, yScrollState;

    QPointer<QWidget> eventSourceWidget; // who do we play events back to
    QQueue<QEvent*>   storedEvents;      // events to play back

    QPoint scrollBase;           // scrollbar value at fingerdown to establish base position
    QPoint start;                // global event x,y at start
    QPoint curr;                 // current x,y (kept to allow velocity calc)
    QPoint rest;                 // rest x,y (resting place after overshoot

    QPointF scrollFactor;        // scroll range factor - converts pixel delta to sb value delta

    QTime event_time;
    QPoint last;                 // global event x,y at start
    QPoint vel;                  // Velocity
    QPoint vel1;                 // Velocity before
    int last_ev_time, curr_time; // timer for velocity

    int scrollingNotStartedTimer;
    int x_braking_cycles;          // how long do we slow down for
    int y_braking_cycles;          // how long do we slow down for

    };

#endif // SHOPPER_UI_QFINGERSCROLLAREA_H
