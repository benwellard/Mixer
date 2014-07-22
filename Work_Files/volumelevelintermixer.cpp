#include "VolumeLevelintermixer.h"
#include <controller.h>
#include <iostream>
#include <QTimer>
#include <controller.h>
#include <interface.h>

VolumeLevelInterMixer::VolumeLevelInterMixer(QObject *parent) :
    QObject(parent)
{

}
void VolumeLevelInterMixer::getLevels()
{

    //while(true) {
    unsigned short *levelDataX = Interface::getLevels();
    emit emitLevels(levelDataX);
    //}

}
