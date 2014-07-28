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

Mixer::Mixer(int output, int mixerOut) : QWidget()
{
    interface = new Interface(output, mixerOut);
    indexNo = 0;
    interface->setOutputChannel(output);

    initVolumesArray();
    interface->MixerMapClear();
    constructMixer(output);
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

    interface->addChannel(selectedChannel);
    noOfChannelsMixer++;
    setChannels(noOfChannelsMixer);
}

void Mixer::newSlider()
{
    //Slider
    if(sliderLayout->count() > 0)
    {
    int indexNo = (sliderLayout->count()/2);
    } else {
        indexNo = 0;
    }
    VolSlider *mySlider = new VolSlider(indexNo, selectedChannel);
    sliders.insert(indexNo, mySlider);
    sliders[indexNo]->setInitValue(interface->getValue(sliders[indexNo]->channel));
    sliders[indexNo]->setFixedSize(50,250);
    connect(sliders[indexNo],SIGNAL(valueChanged(int)),sliders[indexNo],SLOT(releaseIndex(int)));
    connect(sliders[indexNo],SIGNAL(emitIndex(int, int)),this,SLOT(changeVolume(int,int)));
    sliderLayout->setSpacing(25);
    sliderLayout->addWidget(sliders[indexNo],Qt::AlignLeft);
    sliderLayout->setAlignment(Qt::AlignLeft);


    //Label
    QComboBox *channelBox = new QComboBox;
    selectors.insert(indexNo, channelBox);
    channelBox->setFixedSize(80,20);
    for(int i = 10;i < 16;i++)
    {
        QString myString = usb_mixer_get_input_name(0,i);
        myString.remove(0,5);
        myString.remove(4,5);
        channelBox->addItem(myString,Qt::DisplayRole);
        channelBox->setCurrentIndex(indexNo);
    }
    connect(channelBox,SIGNAL(activated(int)),sliders[indexNo],SLOT(changeChannel(int)));
    connect(channelBox,SIGNAL(activated(int)),this,SLOT(clearChannels(int)));
    QVBoxLayout *muteChannelLayout = new QVBoxLayout();
    QPushButton *muteButton = new QPushButton();

    muteButton->setFixedSize(80,50);
    muteButton->setText("Mute");
    connect(muteButton,SIGNAL(released()),sliders[indexNo],SLOT(muteChannel()));
    connect(sliders[indexNo],SIGNAL(emitUnmutedChannel(int)),this,SLOT(muteChannelController(int)));
    connect(sliders[indexNo],SIGNAL(emitMutedChannel(int, int)),this,SLOT(unMuteChannelController(int, int)));
    muteChannelLayout->setSpacing(0);
    muteChannelLayout->addWidget(muteButton,0,Qt::AlignTop);
    muteChannelLayout->addWidget(channelBox,0,Qt::AlignBottom);
    sliderLayout->addLayout(muteChannelLayout);
    indexNo++;
}

void Mixer::clearChannels(int nothing)
{
    QList<int> values;
    for(int i = 0;i < 6; i++)
        values.insert(i,0);

    for(int i = 0; i < 6; i++)
    {
        switch(sliders[i]->channel)
        {
        case 1:
            values[0]++;
            break;
        case 2:
            values[1]++;
            break;
        case 3:
            values[2]++;
            break;
        case 4:
            values[3]++;
            break;
        case 5:
            values[4]++;
            break;
        case 6:
            values[5]++;
            break;
        }
    }
    for(int i = 0;i < 6; i++)
        if((values[i] > 0))
        {
            interface->ChangeVolume(i + 1, sliders[i]->currentValue);
        }
    for(int i = 0; i < 6; i++)
        if(values[i] == 0)
        {
            interface->ChangeVolume(i + 1, -127);
        }

}

void Mixer::muteChannelController(int channel)
{
    interface->ChangeVolume(channel, -127);
}

void Mixer::unMuteChannelController(int channel, int volume)
{
    interface->ChangeVolume(channel, volume);
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

void Mixer::constructMixer(int output) {
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

    for(int i = 0;i < 6;i++)
    {
        selectedChannel = i;
        addChannel();
        newSlider();
    }

    connect(this,SIGNAL(emitCurrentOutput(int)),outputSelect,SLOT(setCurrentIndex(int)));
    connect(channelSelect,SIGNAL(activated(int)),this,SLOT(setChannel(int)));
    connect(this,SIGNAL(emitVolume(int,int)),interface,SLOT(ChangeVolume(int,int)));
    connect(outputSelect,SIGNAL(activated(int)),interface,SLOT(setOutputChannel(int)));
    emit emitCurrentOutput(output);
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
    }
}

void Mixer::initVolumesArray()
{
    for(int i = 0;i < 47;i++)
        volArray.insert(i, 0);
}










