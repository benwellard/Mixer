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
#include <channelbox.h>
#include <QGroupBox>
#include <QCheckBox>
#include <outputbox.h>

int noOfChannelsMixer = 0;


Mixer::Mixer(int output, int mixerOut, Controller *controller) : QWidget()
{
    //Creates interface object for controller-mixer operations
    interface = new Interface(output, mixerOut, controller);

    //sets output channel
    //interface->setOutputChannel(output);

    //Controller pointer
    controllerp = controller;

    //Does nothing
    initVolumesArray();


    interface->MixerMapClear();
    constructMixer(output);
    //QWidget *volumes = new QWidget();

}

void Mixer::setChannels(int n)
{
    emit emitChannels(noOfChannelsMixer);
}

void Mixer::addChannel()
{
    interface->addChannel(selectedChannel);
    noOfChannelsMixer++;
    setChannels(noOfChannelsMixer);
}

void Mixer::newSlider()
{
    //Create the slider object, passing the current index and whatever channel it is assigned to
    VolSlider *mySlider = new VolSlider(indexNo, selectedChannel);

    //Add the slider to an array(QList)
    sliders.insert(indexNo, mySlider);

    //Retrieves the slider's relevant channel's current volume level and sets that to the slider
    sliders[indexNo]->setInitValue(interface->getValue(sliders[indexNo]->channel));

    //Sets slider size
    sliders[indexNo]->setMinimumSize(100,400);
    sliders[indexNo]->setMaximumSize(100,400);

    //Connects the change in the slider' value with a function to release that value along with current index
    connect(sliders[indexNo],SIGNAL(valueChanged(int)),sliders[indexNo],SLOT(releaseIndex(int)));

    //Connects a slider to this object, emitting current volume level and index
    connect(sliders[indexNo],SIGNAL(emitIndex(int, int)),this,SLOT(changeVolume(int,int)));

    //Slider layout adjustment
    sliderLayout->setSpacing(50);
    QGroupBox *sliderBox = new QGroupBox();
    sliderBox->setFixedWidth(170);
    QHBoxLayout *sliderBoxLayout = new QHBoxLayout();
    sliderBox->setLayout(sliderBoxLayout);
    sliderBoxLayout->setAlignment(this,Qt::AlignRight);
    sliderBoxLayout->addStretch(50000);
    sliderBoxes.insert(indexNo,sliderBox);


    sliderBoxLayout->addWidget(sliders[indexNo]);


    sliderLayout->addWidget(sliderBox,Qt::AlignLeft);
    sliderLayout->addStretch(5);



    //Create the channel selector box
    ChannelBox *channelBox = new ChannelBox(indexNo);
    channelBox->setStyleSheet("");
    channelBox->setStyleSheet("QComboBox QAbstractItemView { background-color: white; selection-color: red; border: 2px solid red;} QComboBox { background-color: white; border: 2px solid black;}");
    //Add the channel selector to an array (Qlist)
    selectors.insert(indexNo, channelBox);

    //Set the selector's size
    channelBox->setFixedSize(60,50);

    //Loop that fills the selector box with channels taken from the device
    for(int i = 0;i < 18;i++)
    {
        //Creates a string with data pulled from device
        QString myString = usb_mixsel_get_input_string(0,i);

        //Trim the string to remove DAW/AUD
        myString.remove(1,2);
        myString.remove(5,myString.length()-6);

        //Add string to box
        channelBox->addItem(myString,Qt::DisplayRole);


    }
    //Sets the selector to whatever the slider's current channel is
    //Read from device, find out name of whatever channel is currently at usb_mixer_get_input_name(0, indexNo)
    //That channel is what this channel is currently assigned to.
    QString *channelName = new QString(usb_mixer_get_input_name(0,indexNo));
    int curInd;
    for(curInd = 0;curInd < 18;curInd++)
    {
        QString *channelInput = new QString(usb_mixsel_get_input_string(0,curInd));
        if(channelName->compare(channelInput) == 0)
        break;
    }

    channelBox->setCurrentIndex(curInd);

    //Connects the channel selector to the relevant slider, adjusting what channel that slider is currently operating
    //connect(channelBox,SIGNAL(activated(int)),sliders[indexNo],SLOT(changeChannel(int)));

    connect(selectors[indexNo],SIGNAL(activated(int)),selectors[indexNo],SLOT(setChannel(int)));
    connect(selectors[indexNo],SIGNAL(emitChannel(int,int)),interface,SLOT(setChannel(int,int)));


    //Create the mute button layout and button, and set size and text
    QVBoxLayout *muteChannelLayout = new QVBoxLayout();
    QPushButton *muteButton = new QPushButton();
    muteButton->setStyleSheet("QPushButton { image: url(:/new/prefix1/muteimage.jpg); border: 5px solid black; border-radius:5px;}");
    mutes.insert(indexNo,muteButton);
    muteButton->setFixedSize(50,50);


    //Connects the mute button with the relevant slider
    connect(muteButton,SIGNAL(released()),sliders[indexNo],SLOT(muteChannel()));

    //Connects the slider with this object to emit when a channel is muted, passing the index of the channel
    connect(sliders[indexNo],SIGNAL(emitUnmutedChannel(int)),this,SLOT(muteChannelController(int)));

    //Reverse of above
    connect(sliders[indexNo],SIGNAL(emitMutedChannel(int, int)),this,SLOT(unMuteChannelController(int, int)));

    //Add buttons to layout
    muteChannelLayout->setSpacing(0);
    muteChannelLayout->addWidget(muteButton,0,Qt::AlignTop);
    muteChannelLayout->addWidget(channelBox,0,Qt::AlignBottom);

    sliderBoxLayout->addLayout(muteChannelLayout, Qt::AlignRight);
    sliderBoxLayout->addStretch(5000);
}

void Mixer::muteChannelController(int channel)
{
    interface->ChangeVolume(channel, -127);

    mutes[channel]->setStyleSheet("QPushButton { image: url(:/new/prefix1/mute2image.jpg); border: 5px solid black; border-radius:5px;}");
    update();
}

void Mixer::unMuteChannelController(int channel, int volume)
{
    interface->ChangeVolume(channel, volume);

    mutes[channel]->setStyleSheet("QPushButton { image: url(:/new/prefix1/muteimage.jpg); border: 5px solid black; border-radius:5px;}");
    update();

}

void Mixer::constructOutputs() {

    outputFrame = new QDialog();
    numOuts = (usb_mixer_get_num_outputs(0) + 1)/2;
    outputLayout = new QVBoxLayout(outputFrame);
    for(int i = 0;i < numOuts; i++)
    {
        OutputBox *outputBox = new OutputBox(i);
        outputBox->setFixedSize(200,200);
        outputBox->setStyleSheet("QCheckBox::indicator { width: 200px; height: 200px; }");
        connect(outputBox,SIGNAL(clicked()), outputBox,SLOT(setOut()));
        connect(outputBox,SIGNAL(emitIndex(int)),this,SLOT(deMapChannel(int)));
        QString text = "output: ";
        QString text2 = QString::number(controllerp->getMap(i));
        outputBox->setText(text.append(text2));
        outputBox->setVisible(false);
        outputs.insert(i,outputBox);
        outputLayout->addWidget(outputBox);
    }


    outputFrame->setStyleSheet("QDialog { border:10px solid black; background-color:white; } ");
    outputFrame->setFixedSize(500,500);


    hideOutputs = new QPushButton("Done");


    connect(hideOutputs,SIGNAL(pressed()),this,SLOT(dePopulateOutputs()));
    connect(hideOutputs,SIGNAL(pressed()),this,SLOT(setOutputs()));


}


void Mixer::deMapChannel(int index)
{
    if(outputs[index]->isChecked() == false)
         controllerp->mapChannelToMix(index*2, 15);
         controllerp->mapChannelToMix((index*2) + 1, 16);
}

void Mixer::populateOutputs()
{
    outputLayout->addWidget(hideOutputs);

    for(int i = 0;i < numOuts;i++)
    {
        if((controllerp->getMap(i*2)) < 26 || (outputs[i]->isChecked() == true))
        {

            outputs[i]->setVisible(true);
        }
    }
}

void Mixer::dePopulateOutputs()
{
     //QLayoutItem *child;
     //while ((child = outputLayout->takeAt(0)) != 0) {
    // }
    for(int i = 0;i < numOuts;i++)
        outputs[i]->setVisible(false);

}

void Mixer::setOutputs()
{
    for(int i = 0;i < numOuts;i++)
    {
        if((controllerp->getMap(i*2) < 26) && (outputs[i]->isChecked() == true))
        {
            interface->setOutputChannel(i*2);
        }
    }
    outputFrame->hide();
}

void Mixer::constructMixer(int output)
{

    //Create the Vertical layout. Contains two items, the sliders layout and the volume levels layout
    QVBoxLayout *mainLayout = new QVBoxLayout();
    this->setLayout(mainLayout);
    constructOutputs();
    mainLayout->setSpacing(0);
    QPushButton *outputButton = new QPushButton();
    outputButton->setFixedSize(100,50);
    outputButton->setText("Select \nOutputs");
    mainLayout->addWidget(outputButton);

    connect(outputButton,SIGNAL(clicked()),this,SLOT(populateOutputs()));
    connect(outputButton,SIGNAL(clicked()),outputFrame,SLOT(show()));

    //Adjust the main layout's spacing and alignment
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addSpacing(180);
    mainLayout->addStretch(5000);
    //Create the layout for the sliders and add it to the main layout
    sliderLayout = new QHBoxLayout;
    QGroupBox *sliderFrame = new QGroupBox();
    sliderFrame->setFixedSize(3200,500);
    mainLayout->addStretch(500);

    mainLayout->addWidget(sliderFrame,Qt::AlignBottom);
    mainLayout->setAlignment(sliderFrame,Qt::AlignBottom);
    QVBoxLayout *slidervolLayout = new QVBoxLayout();
    sliderFrame->setLayout(slidervolLayout);
    slidervolLayout->addStretch(50);
    slidervolLayout->addLayout(sliderLayout);
    sliderFrame->setStyleSheet("QGroupBox {background-color: white; border: 5px solid black; border-radius: 10px; }");

    //Loop that creates 18 input channels
    for(int i = 0;i < 18;i++)
    {
        indexNo = i;

        //Each slider starts off as assigned to its relevant channel e.g. slider 1 is assigned to channel 1
        selectedChannel = i;

        //Links up each slider with its relevant channel
        addChannel();

        //Creates the sliders and positions them in the layout
        newSlider();

    }


    //Connects a slider's current value to the interface's change volume function
    connect(this,SIGNAL(emitVolume(int,int)),interface,SLOT(ChangeVolume(int,int)));

    //Sets initial output
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










