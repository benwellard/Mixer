#include "interface.h"
#include <iostream>
#include <controller.h>
Interface::Interface(int outchannel, int mixChannel)
    :QObject()
{
    outputChannel = outchannel * 2;
    prevChannel = 0;
    prevChannel2 = 0;
    mixerChannel = mixChannel;
}


void Interface::MixerMapClear() {



    //Controller::mapMixInput(0,0,10);
    //Controller::mapMixInput(0,1,11);
    //Controller::mapMixInput(0,2,12);
    //Controller::mapMixInput(0,3,13);
    //Controller::mapMixInput(0,4,14);
    //Controller::mapMixInput(0,5,15);
    Controller::mapChannelToMix(0, 26);
    Controller::mapChannelToMix(1, 27);
    Controller::mapChannelToMix(2, 28);
    Controller::mapChannelToMix(3, 29);
    Controller::mapChannelToMix(4, 30);
    Controller::mapChannelToMix(5, 31);
    Controller::mapChannelToMix(6, 32);
    Controller::mapChannelToMix(7, 33);

}

unsigned short* Interface::getLevels()
{
    return Controller::getLevels();
}

void Interface::ChangeVolume(int channel, int volume)
{
    channel = channel + 9;
    int node = outputChannel + (channel * 8);
    //volume = -50 + volume;
    if(volume < 1)
        volume = -127;
    Controller::changeVolume(node, volume);
    Controller::changeVolume(node + 1, volume);
}

int Interface::IDtoAbs(int mixerID)
{
    return mixerID + 26;
}

int Interface::AbstoID(int absChannel)
{
    return absChannel - 26;
}

//int x = 0;

void Interface::addChannel(int channel)
{

    channel = channel + 9;
    int node = (channel * 8) + outputChannel;
    if(Controller::getValue(node) < 1)
    {
    Controller::changeVolume(node ,-127);
    Controller::changeVolume(node + 1,-127);
    } else {
    Controller::changeVolume(node, Controller::getValue(node));
    Controller::changeVolume(node + 1, Controller::getValue(node));
    }
}

void Interface::setOutputChannel(int channel)
{
    prevChannel = outputChannel;
    prevChannel2 = prevChannel;
    channel = channel * 2;
    prevChannel = channel;
    deletePreviousMapping();
    Controller::mapChannelToMix(prevChannel, mixerChannel);
    Controller::mapChannelToMix(prevChannel + 1, mixerChannel + 1);
}

void Interface::deletePreviousMapping()
{
    //Maps whatever outputs the mixer is going FROM to 2 dud channels
    Controller::mapChannelToMix(prevChannel2, Controller::getChannelToMix(prevChannel));
    Controller::mapChannelToMix(prevChannel2 + 1, Controller::getChannelToMix(prevChannel + 1));

}

int Interface::getValue(int channel)
{
    channel = channel + 9;
    int node = (channel * 8) + outputChannel;
    return Controller::getValue(node);
}
