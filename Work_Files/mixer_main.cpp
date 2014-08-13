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
#include <QLabel>
#include <libusb.h>
#include <usb_mixer.h>

mixer_main::mixer_main() :QWidget()
{
    int error = -5;
    unsigned char* error2;
    char* error3;
    int ex = controller.initController();
    this->constructWindow();

    error = stringReturn();
    error3 = (char*)error2;
    QString errorstring = QString::number(ex);
    QLabel *errorlabel = new QLabel(this);

    errorlabel->setText(errorstring);
    errorlabel->setFixedSize(1000,100);
    errorlabel->move(500,910);
}





mixer_main::~mixer_main()
{
    controller.deinitController();

}

void mixer_main::constructWindow()
{

    Controller *contP = &controller;
    this->setMinimumSize(1920,900);
    QTabWidget *tabs = new QTabWidget(this);
    tabs->setMinimumSize(1920,900);
    mix1 = new Mixer(0, 26, contP);
    mix2 = new Mixer(1, 28, contP);
    mix3 = new Mixer(2, 30, contP);
    mix4 = new Mixer(3, 32, contP);
    connect(tabs,SIGNAL(currentChanged(int)),this,SLOT(saveAndLoadArray(int)));
    tabs->addTab(mix1, "Mix 1");
    tabs->addTab(mix2, "Mix 2");
    tabs->addTab(mix3, "Mix 3");
    tabs->addTab(mix4, "Mix 4");



}

void mixer_main::saveAndLoadArray(int tab)
{
    if(tab == 0)
    {

    }
    else if(tab == 1)
    {

    }
    else if(tab == 2)
    {

    }
    else if(tab == 3)
    {

    }
}





