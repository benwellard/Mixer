#include "mixer.h"
#include <QWidget>
#include <volslider.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <volumelevel.h>
#include <QLabel>
#include <QString>
#include <QPushButton>
#include <mixer_main.h>
#include <QComboBox>
#include <interface.h>
#include <QThread>
#include <iostream>
#include <usb_mixer.h>
#include <controller.h>

int noOfChannelsMixer = 0;



Mixer::Mixer() : QWidget()
{
    indexNo = 0;
    initVolumesArray();
    Interface::MixerMapClear();
    constructMixer();
    QWidget *volumes = new QWidget();
}

void Mixer::setChannels(int n)
{
    emit emitChannels(noOfChannelsMixer);
}

void Mixer::setChannel(int channel)
{
    selectedChannel = channel + 1;
}

void Mixer::addChannel()
{
    Interface::addChannel(selectedChannel);
    noOfChannelsMixer++;
    setChannels(noOfChannelsMixer);
}

void Mixer::newSlider()
{
    //Slider
    if(sliderLayout->count() > 0) {
    int indexNo = (sliderLayout->count()/2);
    } else {
        indexNo = 0;
    }
    VolSlider *mySlider = new VolSlider(indexNo, selectedChannel);
    sliders.insert(indexNo, mySlider);

    sliders[indexNo]->setFixedSize(50,250);
    connect(sliders[indexNo],SIGNAL(valueChanged(int)),sliders[indexNo],SLOT(releaseIndex(int)));
    connect(sliders[indexNo],SIGNAL(emitIndex(int, int)),this,SLOT(changeVolume(int,int)));
    sliderLayout->setSpacing(25);
    sliderLayout->addWidget(sliders[indexNo],Qt::AlignLeft);
    sliderLayout->setAlignment(Qt::AlignLeft);
    indexNo++;

    //Label
    QLabel *channelLabel = new QLabel;
    channelLabel->setFixedSize(50,20);
    channelLabel->setText(QString("Ch: ") + (char)(((int)'1')+selectedChannel-1));
    sliderLayout->addWidget(channelLabel);
}

QComboBox* Mixer::addChannelBox()
{
    QComboBox *channelSelect = new QComboBox(this);
    channelSelect->addItem("1", Qt::DisplayRole);
    channelSelect->addItem("2", Qt::DisplayRole);
    channelSelect->addItem("3", Qt::DisplayRole);
    channelSelect->addItem("4", Qt::DisplayRole);
    channelSelect->addItem("5", Qt::DisplayRole);
    channelSelect->addItem("6", Qt::DisplayRole);
    return channelSelect;
}

QComboBox* Mixer::addOutputBox()
{
    QComboBox *outputSelect = new QComboBox(this);
    outputSelect->addItem("1/2", Qt::DisplayRole);
    outputSelect->addItem("3/4", Qt::DisplayRole);
    outputSelect->addItem("5/6", Qt::DisplayRole);
    outputSelect->addItem("7/8", Qt::DisplayRole);
    return outputSelect;
}

void Mixer::constructMixer() {
    QVBoxLayout *mainLayout = new QVBoxLayout();
    this->setLayout(mainLayout);
    QPushButton *newChannel = new QPushButton(this);
    QComboBox *channelSelect = addChannelBox();
    QComboBox *outputSelect = addOutputBox();
    QLabel *outputLabel = new QLabel(this);
    outputLabel->setText("Choose output");
    newChannel->move(1200,600);
    channelSelect->move(1200,550);
    outputLabel->move(1200,675);
    outputSelect->move(1200,700);
    newChannel->setText("Add Channel");
    newChannel->setMinimumSize(110,70);
    newChannel->setMaximumSize(200,100);
    channelSelect->setMinimumSize(100,50);
    channelSelect->setMaximumSize(200,100);
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addSpacing(200);
    sliderLayout = new QHBoxLayout;
    mainLayout->addLayout(sliderLayout);
    selectedChannel = 1;

    connect(newChannel,SIGNAL(released()),this,SLOT(newSlider()));
    connect(channelSelect,SIGNAL(activated(int)),this,SLOT(setChannel(int)));
    Interface *interface = new Interface();
    QThread *thread = new QThread(this);
    interface->moveToThread(thread);
    connect(this,SIGNAL(emitVolume(int,int)),interface,SLOT(ChangeVolume(int,int)));
    connect(newChannel,SIGNAL(released()),this,SLOT(addChannel()));
    connect(outputSelect,SIGNAL(activated(int)),interface,SLOT(setOutputChannel(int)));
    thread->start();
}

void Mixer::changeVolume(int indexVal, int vol)
{
    emit emitVolume(indexVal, vol);
}

void Mixer::saveVolumesArray()
{
    for(int i = 0;i < 47;i++)
        volArray[i] = Controller::getValue(i+80);
    int c = 0;
    c = c;
}

void Mixer::loadVolumesArray()
{
    for(int i = 0;i < 47;i++)
    {
        Controller::changeVolume(i+80, volArray[i]);
        std::cout << i+80 << ": " << volArray[i] << "   ";
    }
}

void Mixer::initVolumesArray()
{
    for(int i = 0;i < 47;i++)
        volArray.insert(i, -127);
}










