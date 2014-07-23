#include "volumelevel.h"
#include <QPainter>
#include <QRect>
#include <iostream>
#include <QPaintEvent>
#include <decibelworker.h>
#include <controller.h>
#include <QThread>
#include <VolumeLevelintermixer.h>

VolumeLevel::VolumeLevel(QWidget *parent) :
    QWidget(parent)
{
    x = 30;
    h = 200;
    fillArray();
    VolumeLevelInterMixer *vlim = new VolumeLevelInterMixer();
    connect(vlim,SIGNAL(emitLevels(unsigned short*)),this,SLOT(setInputLevels(unsigned short*)));
    QThread *thread = new QThread(this);
    vlim->moveToThread(thread);
    connect(thread,SIGNAL(started()),vlim, SLOT(getLevels()));
    thread->start(QThread::NormalPriority);
}


void VolumeLevel::paintEvent(QPaintEvent *event)
{
    QRect rect = event->rect();
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawRect(rect);
    x = -40;
    for(int i = 0;i < noChannels; i++)
    {
        x = - 40 - (i * 100);
        painter.rotate(180);
        if(hArray[i] > 22000)
            hArray[i] = 22000;
        QRect *vol = new QRect(x - 25 ,-250,30,hArray[i + 6]/100);
        painter.drawRect(*vol);
        painter.rotate(180);

    }

}

void VolumeLevel::setInputLevels(unsigned short * hxArray)
{
    hArray = hxArray;
    update();
}

void VolumeLevel::fillArray()
{
    hArray = new unsigned short[12];
    for(int i = 0;i <= 11;i++) {
        hArray[i] = 0;
    }
}

void VolumeLevel::setChannels(int n)
{
    noChannels = n;
    fillArray();
}


