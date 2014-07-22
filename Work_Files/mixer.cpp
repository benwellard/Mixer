#include "mixer.h"
#include <QWidget>
#include <volslider.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <volumelevel.h>
#include <QLabel>
#include <QString>
#include <iostream>
#include <QPushButton>
#include <mixer_main.h>
#include <QComboBox>
#include <interface.h>


int noOfChannelsMixer = 0;
QHBoxLayout *sliderLayout = new QHBoxLayout();


Mixer::Mixer() : QWidget()
{
    Interface::MixerMapClear();
    constructMixer();
    //noOfChannelsMixer = 0;
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
    std::cout << selectedChannel;
    setChannels(noOfChannelsMixer);
}
int indexNo = 0;
void Mixer::newSlider()
{

    //Slider
    if(sliderLayout->count() > 0) {
    int indexNo = (sliderLayout->count()/2) + 1;
    } else {
        indexNo = 1;
    }
    VolSlider *myslider = new VolSlider(indexNo, selectedChannel);
    myslider->setFixedSize(50,250);
    connect(myslider,SIGNAL(valueChanged(int)),this,SLOT(changeVolume(int)));
    sliderLayout->setSpacing(25);
    sliderLayout->addWidget(myslider,Qt::AlignLeft);
    sliderLayout->setAlignment(Qt::AlignLeft);
    indexNo++;

    //Label
    QLabel *channelLabel = new QLabel;
    channelLabel->setFixedSize(50,20);
    channelLabel->setText(QString("Ch: ") + (char)(((int)'1')+selectedChannel - 1));
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


void Mixer::constructMixer() {
    QVBoxLayout *mainLayout = new QVBoxLayout();
    this->setLayout(mainLayout);
    QPushButton *newChannel = new QPushButton(this);
    QComboBox *channelSelect = addChannelBox();

    newChannel->move(1200,650);
    channelSelect->move(1200,550);
    newChannel->setText("Add Channel");
    newChannel->setMinimumSize(100,70);
    newChannel->setMaximumSize(200,100);
    channelSelect->setMinimumSize(100,50);
    channelSelect->setMaximumSize(200,100);
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addSpacing(200);
    mainLayout->addLayout(sliderLayout);

    connect(newChannel,SIGNAL(released()),this,SLOT(addChannel()));
    connect(newChannel,SIGNAL(released()),this,SLOT(newSlider()));
    connect(channelSelect,SIGNAL(activated(int)),this,SLOT(setChannel(int)));
    Interface *interface = new Interface();
    connect(this,SIGNAL(emitVolume(int,int)),interface,SLOT(ChangeVolume(int,int)));
}


void Mixer::changeVolume(int vol)
{

    std::cout << vol;

    emit emitVolume(indexNo, vol);
}





