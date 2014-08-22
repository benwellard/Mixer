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
    //controlleri->mapChannelToMix(outputChannel, mixerChannel);
    //controlleri->mapChannelToMix(outputChannel + 1,mixerChannel + 1);
}


void Interface::MixerMapClear() {


}

unsigned short* Interface::getLevels()
{
    levelThings = controlleri->getLevels();

    return levelThings;
}

void Interface::ChangeVolume(int channel, int volume)
{

    //Calculates node from output(mixer) channel and input channel
    int node = outputChannel + (channel * 8);

    //If the slider for an input channel is below 1, it sets the relevant volume level to -127
    //Otherwise sets the node to whatever value it is passed in volume
    if(volume < 1)
        volume = -127;
    controlleri->changeVolume(node, volume);
    controlleri->changeVolume(node + 1, volume);

}

int Interface::IDtoAbs(int mixerID)
{
    //Obselete
    return mixerID + 26;
}

int Interface::AbstoID(int absChannel)
{
    //Obselete
    return absChannel - 26;
}

void Interface::addChannel(int channel)
{
    //Calculate node, and retrieve volume level from device
    int node = (channel * 8) + outputChannel;
    controlleri->changeVolume(node, controlleri->getValue(node));
    controlleri->changeVolume(node + 1, controlleri->getValue(node));
}

void Interface::setOutputChannel(int channel)
{
    controlleri->mapChannelToMix(channel,mixerChannel);
    controlleri->mapChannelToMix(channel + 1,mixerChannel + 1);
}

void Interface::setChannel(int index, int channel)
{
    controlleri->mapMixInput(0,index,channel);
}

int Interface::getValue(int channel)
{
    int node = (channel * 8) + outputChannel;
    return controlleri->getValue(node);
}
