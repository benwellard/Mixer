#include "interface.h"
#include <iostream>

Interface::Interface(int outchannel, int mixChannel, Controller *controller)
    :QObject()
{
    outputChannel = outchannel * 2;
    prevChannel = 0;
    prevChannel2 = 0;
    mixerChannel = mixChannel;
    controlleri = controller;
}


void Interface::MixerMapClear() {

    controlleri->mapChannelToMix(0, 26);
    controlleri->mapChannelToMix(1, 27);
    controlleri->mapChannelToMix(2, 28);
    controlleri->mapChannelToMix(3, 29);
    controlleri->mapChannelToMix(4, 30);
    controlleri->mapChannelToMix(5, 31);
    controlleri->mapChannelToMix(6, 32);
    controlleri->mapChannelToMix(7, 33);
    for(int i = 0;i < 144; i++)
        controlleri->changeVolume(i, 80);
}

unsigned short* Interface::getLevels()
{
    return controlleri->getLevels();
}

void Interface::ChangeVolume(int channel, int volume)
{

    int node = outputChannel + (channel * 8);
    //volume = -50 + volume;
    if(volume < 1)
        volume = -127;
    controlleri->changeVolume(node, volume);
    controlleri->changeVolume(node + 1, volume);

}

int Interface::IDtoAbs(int mixerID)
{
    return mixerID + 26;
}

int Interface::AbstoID(int absChannel)
{
    return absChannel - 26;
}

void Interface::addChannel(int channel)
{


    int node = (channel * 8) + outputChannel;
    controlleri->changeVolume(node, 100);

    if(controlleri->getValue(node) < 1)
    {
    controlleri->changeVolume(node ,-127);
    controlleri->changeVolume(node + 1,-127);
    } else {
    controlleri->changeVolume(node, controlleri->getValue(node));
    controlleri->changeVolume(node + 1, controlleri->getValue(node));
    }

}

void Interface::setOutputChannel(int channel)
{

    prevChannel = outputChannel;
    prevChannel2 = prevChannel;
    channel = channel * 2;
    prevChannel = channel;
    deletePreviousMapping();
    controlleri->mapChannelToMix(prevChannel, mixerChannel);
    controlleri->mapChannelToMix(prevChannel + 1, mixerChannel + 1);

}

void Interface::deletePreviousMapping()
{
    //Maps whatever outputs the mixer is going FROM to 2 dud channels
    controlleri->mapChannelToMix(prevChannel2, controlleri->getChannelToMix(prevChannel));
    controlleri->mapChannelToMix(prevChannel2 + 1, controlleri->getChannelToMix(prevChannel + 1));

}

int Interface::getValue(int channel)
{
    int node = (channel * 8) + outputChannel;
    return controlleri->getValue(node);
}
