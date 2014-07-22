#include "mixer_main.h"
#include "ui_mixer_main.h"
#include <QString>
#include <QTabWidget>
#include <mixer.h>
#include <volumelevel.h>
#include <iostream>
#include <VolumeLevelintermixer.h>
#include <controller.h>
#include <interface.h>

mixer_main::mixer_main() :QWidget()
{
    noOfChannels = 0;
    this->constructWindow();

    //Commands to map an input channel to a mixer
    //Controller::mapMixInput(0, 0, 11);
    //Controller::mapMixInput(0, 0, 12);
    //Commands to map a mixer to an output
    //Controller::mapChannelToMix(0, 26);
    //Controller::mapChannelToMix(1, 26);
}

mixer_main::~mixer_main()
{


}


void mixer_main::noChannelsSlot(int noChannels)
{
    noOfChannels = noChannels;
    constructWindow();
}

void mixer_main::constructWindow()
{

    this->setMinimumSize(1400,800);
    QTabWidget *tabs = new QTabWidget(this);
    tabs->setMinimumSize(1400,800);
    Mixer *mix1 = new Mixer();
    VolumeLevel *volumeMix1 = new VolumeLevel(mix1);
    connect(mix1,SIGNAL(emitChannels(int)),this,SLOT(noChannelsSlot(int)));
    connect(mix1,SIGNAL(emitChannels(int)),volumeMix1,SLOT(setChannels(int)));

    volumeMix1->setMinimumSize(1400,300);


    tabs->addTab(mix1, "Mix 1");



}




