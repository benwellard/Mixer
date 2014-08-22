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
#include <qfingerscrollarea.h>
#include <QScrollBar>
#include <QDesktopWidget>

mixer_main::mixer_main() :QWidget()
{

    //Controller Initialization and Device Connection
    int ex = controller.initController();
    QPalette pal(palette());
    pal.setColor(QPalette::Background,Qt::white);
    this->setPalette(pal);


    //Program Start
    this->constructWindow();

}





mixer_main::~mixer_main()
{
    controller.deinitController();
}

void mixer_main::constructWindow()
{

    Controller *contP = &controller;
    QDesktopWidget *desktop = new QDesktopWidget();
    QRect screen = desktop->availableGeometry(this);
    this->setFixedSize(screen.width(),screen.height()-50);

    //Tab Object
    QTabWidget *tabs = new QTabWidget(this);
    tabs->setMinimumSize(screen.width(), screen.height()-50);
    tabs->setStyleSheet("QTabBar::tab { background: white; border: 2px solid black; } QTabBar::tab:selected { background: qlineargradient(x1: 0, y1: 1, x2: 0, y2: 0,"
                        "stop: 0 #FF0000, stop: 0.8 #FFFFFF); }");


    //Widgets used as frames for Scroll Areas
    QWidget *main1 = new QWidget();
    QWidget *main2 = new QWidget();
    QWidget *main3 = new QWidget();
    QWidget *main4 = new QWidget();

    //Mixer Objects
    mix1 = new Mixer(0, 26, contP);
    mix2 = new Mixer(1, 28, contP);
    mix3 = new Mixer(2, 30, contP);
    mix4 = new Mixer(3, 32, contP);


    //Scroll Area Objects
    QFingerScrollArea *mix1slide = new QFingerScrollArea(main1);
    QFingerScrollArea *mix2slide = new QFingerScrollArea(main2);
    QFingerScrollArea *mix3slide = new QFingerScrollArea(main3);
    QFingerScrollArea *mix4slide = new QFingerScrollArea(main4);


    //Setting Scroll Area targets and size
    mix1slide->setWidget(mix1);
    mix2slide->setWidget(mix2);
    mix3slide->setWidget(mix3);
    mix4slide->setWidget(mix4);
    mix1slide->setMinimumSize(screen.width()-30, screen.height()-30);
    mix2slide->setMinimumSize(screen.width()-30, screen.height()-30);
    mix3slide->setMinimumSize(screen.width()-30, screen.height()-30);
    mix4slide->setMinimumSize(screen.width()-30, screen.height()-30);

    //Show Scroll Areas
    mix1slide->show();
    mix2slide->show();
    mix3slide->show();
    mix4slide->show();

    //Add Frames to tab object
    tabs->addTab(main1, "Mix 1");
    tabs->addTab(main2, "Mix 2");
    tabs->addTab(main3, "Mix 3");
    tabs->addTab(main4, "Mix 4");

    connect(tabs,SIGNAL(currentChanged(int)),this,SLOT(saveAndLoadArray(int)));

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





