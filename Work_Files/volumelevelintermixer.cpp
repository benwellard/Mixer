#include "VolumeLevelintermixer.h"
#include <controller.h>
#include <iostream>
#include <QTimer>
#include <controller.h>
#include <interface.h>
#include <QtConcurrent/QtConcurrent>
#include <QtConcurrent/QtConcurrentRun>
#include <QFuture>

using namespace QtConcurrent;

VolumeLevelInterMixer::VolumeLevelInterMixer(Interface *interface,QObject *parent) :
    QObject(parent)
{



    interfacev = interface;


}
unsigned short *  VolumeLevelInterMixer::getLevels()
{

    values.clear();
    levelDataX = interfacev->getLevels();
    unsigned short x2 = levelDataX[1];
    unsigned short x3 = levelDataX[2];

    for(int i = 0;i < 64;i++)
    {
        unsigned short  x = levelDataX[i];
        values.insert(i, x);
    }
    unsigned short x1 = values[1];

    return levelDataX;

}
