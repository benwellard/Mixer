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

mixer_main::mixer_main() :QWidget()
{

    //Controller Initialization and Device Connection
    int ex = controller.initController();
    QPalette pal(palette());
    pal.setColor(QPalette::Background,Qt::white);
    this->setPalette(pal);
    //Test Variables
    int error = -5;
    unsigned char* error2;
    char* error3;

    //Program Start
    this->constructWindow();

    //Test Functions
    error = stringReturn();
    error3 = (char*)error2;
    QString errorstring = QString::number(error);
    //QLabel *errorlabel = new QLabel(this);
    //errorlabel->setText(errorstring);
    //errorlabel->setFixedSize(1000,100);
    //errorlabel->move(500,910);

}





mixer_main::~mixer_main()
{
    controller.deinitController();
}

void mixer_main::constructWindow()
{

    Controller *contP = &controller;
    this->setMinimumSize(1920,1000);

    //Tab Object
    QTabWidget *tabs = new QTabWidget(this);
    tabs->setMinimumSize(1920,1100);
    tabs->setStyleSheet("QTabBar::tab { background: white; border: 2px solid black; } QTabBar::tab:selected { background: qlineargradient(x1: 0, y1: 1, x2: 0, y2: 0,"
                        "stop: 0 #FF0000, stop: 0.2 #FFFFFF); }");


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
    mix1slide->setFixedSize(1920,1000);
    mix2slide->setFixedSize(1920,1000);
    mix3slide->setFixedSize(1920,1000);
    mix4slide->setFixedSize(1920,1000);

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





