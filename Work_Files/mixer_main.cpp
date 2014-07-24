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
    Controller::initController();
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
    Controller::deinitController();

}

void mixer_main::constructWindow()
{

    this->setMinimumSize(1400,800);
    QTabWidget *tabs = new QTabWidget(this);
    tabs->setMinimumSize(1400,800);
    mix1 = new Mixer();
    mix2 = new Mixer();
    //VolumeLevel *volumeMix1 = new VolumeLevel(mix1);
    //VolumeLevel *volumeMix2 = new VolumeLevel(mix2);
    //connect(mix1,SIGNAL(emitChannels(int)),volumeMix1,SLOT(setChannels(int)));
    //connect(mix2,SIGNAL(emitChannels(int)),volumeMix2,SLOT(setChannels(int)));
    //volumeMix1->setMinimumSize(1400,300);
    //volumeMix2->setMinimumSize(1400,300);
    connect(tabs,SIGNAL(currentChanged(int)),this,SLOT(saveAndLoadArray(int)));

    tabs->addTab(mix1, "Mix 1");
    tabs->addTab(mix2, "Mix 2");



}

void mixer_main::saveAndLoadArray(int tab)
{
    if(tab == 0)
    {
        std::cout << "tab 1";
        mix2->saveVolumesArray();
        mix1->loadVolumesArray();
    }
    else if(tab == 1)
    {
        std::cout << "tab 2";
        mix1->saveVolumesArray();
        mix2->loadVolumesArray();
    }
}





