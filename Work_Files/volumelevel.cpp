#include "volumelevel.h"
#include <QPainter>
#include <QRect>
#include <iostream>
#include <QPaintEvent>
#include <decibelworker.h>
#include <controller.h>
#include <QThread>
//#include <VolumeLevelintermixer.h>
#include <QStyleOption>


VolumeLevel::VolumeLevel(Interface * interfacevl, int channels, QWidget *parent) : QGroupBox(parent)
{
    noChannels = channels;
    x = 30;
    h = 200;
    fillArray();
    vlim = new VolumeLevelInterMixer(interfacevl);
    QTimer *refresh = new QTimer();
    connect(refresh,SIGNAL(timeout()),this,SLOT(setInputLevels()));
    refresh->start(1);
}


void VolumeLevel::paintEvent(QPaintEvent *event)
{



    for(int i = 0;i < 32;i++)
    {
    //unsigned short larry = hArray[i];
    int g = 10;
    g = 50;
    }
\
    p.begin(this);
    p.setRenderHint(QPainter::Antialiasing);
    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QColor myPenColor = QColor(255,255,255,255);
    QBrush *brush = new QBrush(myPenColor,Qt::SolidPattern);
    p.setPen(myPenColor);
    p.setBrush(*brush);
    x = -40;
    hArray = vlim->getLevels();

    unsigned short * levs;

    levs = hArray;

    //unsigned short *larry2;
    //memcpy(newArray,hArray,sizeof(hArray));


    for(int i = 0;i < noChannels; i++)
    {
        x = - 40 - (i * 100);
        p.rotate(180);

        unsigned short larry = levs[0+i];
        if(larry > 22000)
            larry = 22000;
        if(larry < 1)
            larry = 1;
        QRect *vol = new QRect(x - 25 ,-250,30,(larry)/200);
        p.drawRect(*vol);
        p.rotate(180);
    }
    p.end();
}

void VolumeLevel::setInputLevels()
{
    //unsigned short * hxArray = vlim->getLevels();
    //hArray = hxArray;
    update();
}

void VolumeLevel::fillArray()
{

    for(int i = 0;i < noChannels;i++) {
        //hArray[i] = 1000;
    }
}




