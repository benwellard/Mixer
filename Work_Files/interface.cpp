#include "interface.h"
#include <iostream>
#include <controller.h>
Interface::Interface()
    :QObject()
{

}


void Interface::MixerMapClear() {



    //Controller::mapMixInput(0,0,10);
    //Controller::mapMixInput(0,1,11);
    //Controller::mapMixInput(0,2,12);
    //Controller::mapMixInput(0,3,13);
    //Controller::mapMixInput(0,4,14);
    //Controller::mapMixInput(0,5,15);
    Controller::changeVolume(16, 0);
    Controller::changeVolume(25,0);
    Controller::changeVolume(32, 0);
    Controller::changeVolume(41,0);

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
int outputChannel;
void Interface::ChangeVolume(int channel, int volume)
{

    channel = channel + 9;
    int node = outputChannel + (channel * 8);
    volume = -50 + volume;
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

int x = 0;

void Interface::addChannel(int channel)
{
    channel = channel + 9;
    int node = (channel * 8) + outputChannel;
    Controller::changeVolume(node ,0);
    Controller::changeVolume(node + 1,0);
}
void Interface::setOutputChannel(int channel)
{
    channel = channel * 2;
    outputChannel = channel;
}
