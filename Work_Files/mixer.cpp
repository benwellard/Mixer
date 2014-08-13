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
#include <iostream>
#include <usb_mixer.h>
#include <controller.h>
#include <QScrollArea>

int noOfChannelsMixer = 0;


Mixer::Mixer(int output, int mixerOut, Controller *controller) : QWidget()
{
    interface = new Interface(output, mixerOut, controller);
    indexNo = 0;
    interface->setOutputChannel(output);
    controllerp = controller;
    initVolumesArray();
    interface->MixerMapClear();
    constructMixer(output);
    //QWidget *volumes = new QWidget();

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


    VolSlider *mySlider = new VolSlider(indexNo, selectedChannel);
    sliders.insert(indexNo, mySlider);
    sliders[indexNo]->setInitValue(interface->getValue(sliders[indexNo]->channel));
    sliders[indexNo]->setInitValue(10);
    sliders[indexNo]->setMinimumSize(100,350);
    sliders[indexNo]->setMaximumSize(100,350);
    connect(sliders[indexNo],SIGNAL(valueChanged(int)),sliders[indexNo],SLOT(releaseIndex(int)));
    connect(sliders[indexNo],SIGNAL(emitIndex(int, int)),this,SLOT(changeVolume(int,int)));
    sliderLayout->setSpacing(5);
    sliderLayout->addWidget(sliders[indexNo],Qt::AlignLeft);
    sliderLayout->setAlignment(Qt::AlignLeft);


    //Label
    QComboBox *channelBox = new QComboBox;
    channelBox->setMinimumContentsLength(30);
    selectors.insert(indexNo, channelBox);
    channelBox->setFixedSize(300,100);
    for(int i = 0;i < 18;i++)
    {
        QString myString = usb_mixer_get_input_name(0, i);
        myString.remove(1,2);
        channelBox->addItem(myString,Qt::DisplayRole);
        channelBox->setCurrentIndex(indexNo);
    }
    connect(channelBox,SIGNAL(activated(int)),sliders[indexNo],SLOT(changeChannel(int)));
    connect(channelBox,SIGNAL(activated(int)),this,SLOT(clearChannels(int)));
    QVBoxLayout *muteChannelLayout = new QVBoxLayout();
    QPushButton *muteButton = new QPushButton();

    muteButton->setFixedSize(150,200);
    muteButton->setText("mute");
    connect(muteButton,SIGNAL(released()),sliders[indexNo],SLOT(muteChannel()));
    connect(sliders[indexNo],SIGNAL(emitUnmutedChannel(int)),this,SLOT(muteChannelController(int)));
    connect(sliders[indexNo],SIGNAL(emitMutedChannel(int, int)),this,SLOT(unMuteChannelController(int, int)));
    muteChannelLayout->setSpacing(0);
    muteChannelLayout->addWidget(muteButton,0,Qt::AlignTop);
    muteChannelLayout->addWidget(channelBox,0,Qt::AlignBottom);
    sliderLayout->addLayout(muteChannelLayout);
}

void Mixer::clearChannels(int nothing)
{
    /*
    QList<int> values;
    for(int i = 0;i < 18; i++)
        values.insert(i,0);

    for(int i = 0; i < 8; i++)
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
        case 7:
            values[6]++;
            break;
        case 8:
            values[7]++;
            break;
        case 9:
            values[8]++;
            break;
        case 10:
            values[9]++;
            break;
        case 11:
            values[10]++;
            break;
        case 12:
            values[11]++;
            break;
        case 13:
            values[12]++;
            break;
        case 14:
            values[13]++;
            break;
        case 15:
            values[14]++;
            break;
        case 16:
            values[15]++;
            break;
        case 17:
            values[16]++;
            break;
        case 18:
            values[17]++;
            break;
        }
    }

    for(int i = 0;i < 18; i++)
        if((values[i] > 0))

        {
            //interface->ChangeVolume(i + 1, sliders[i]->currentValue);
        }

    for(int i = 0; i < 8; i++)

        if(values[i] == 0)
        {
            //interface->ChangeVolume(i + 1, -127);
        }

    */
}

void Mixer::muteChannelController(int channel)
{
    interface->ChangeVolume(channel, -127);
}

void Mixer::unMuteChannelController(int channel, int volume)
{
    interface->ChangeVolume(channel, volume);
}

QComboBox* Mixer::addOutputBox()
{
    QComboBox *outputSelect = new QComboBox(this);
    outputSelect->setFixedSize(100,200);
    outputSelect->addItem("1/2", Qt::DisplayRole);
    outputSelect->addItem("3/4", Qt::DisplayRole);
    outputSelect->addItem("5/6", Qt::DisplayRole);
    outputSelect->addItem("7/8", Qt::DisplayRole);
    return outputSelect;
}

void Mixer::constructMixer(int output) {
    QVBoxLayout *mainLayout = new QVBoxLayout();
    this->setLayout(mainLayout);

    QComboBox *outputSelect = addOutputBox();
    QLabel *outputLabel = new QLabel(this);
    outputLabel->setFixedSize(100,200);
    outputLabel->setText("Choose output");
    outputLabel->move(1200,800);
    outputSelect->move(1200,850);


    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addSpacing(200);
    sliderLayout = new QHBoxLayout;
    mainLayout->addLayout(sliderLayout);
    selectedChannel = 1;
    indexNo = 0;
    for(int i = 0;i < 18;i++)
    {
        selectedChannel = i;
        addChannel();
        newSlider();
    }

    connect(this,SIGNAL(emitCurrentOutput(int)),outputSelect,SLOT(setCurrentIndex(int)));
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
        volArray[i] = controllerp->getValue(i+80);
    int c = 0;

}

void Mixer::loadVolumesArray()
{
    for(int i = 0;i < 47;i++)
    {
        controllerp->changeVolume(i+80, volArray[i]);
    }
}

void Mixer::initVolumesArray()
{
    for(int i = 0;i < 47;i++)
        volArray.insert(i, 0);
}










