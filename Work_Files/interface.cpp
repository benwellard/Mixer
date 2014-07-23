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

    //maps the mixer to outputs 1 and 2
    //Controller::mapChannelToMix(0, 26);
    //Controller::mapChannelToMix(1, 27);
    //Controller::mapChannelToMix(2, 28);
    //Controller::mapChannelToMix(3, 29);

}

unsigned short* Interface::getLevels()
{
    return Controller::getLevels();
}

void Interface::ChangeVolume(int channel, int volume)
{
    //channel = channel - 2;
    int mixerID = 0;
    if (channel % 2 == 0){
        mixerID = 0;
    } else {
        mixerID = 1;
    }

    int node = mixerID + (channel * 8);
    Controller::changeVolume(node, volume);
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
    //Given the input channel, maps that channel to a free input on the mixer object
    //e.g. if given 15, will map channel 15 to play to the mixer object
    Controller::mapMixInput(0,x,channel);
    x++;
}
void Interface::setOutputChannel(int channel)
{
    for(int i = 0;i < 8;i++)
        Controller::mapChannelToMix(i, i);
    channel = channel * 2;
    Controller::mapChannelToMix(channel, 26);
    Controller::mapChannelToMix(channel + 1, 27);
}
