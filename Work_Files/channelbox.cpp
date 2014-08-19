#include "channelbox.h"

ChannelBox::ChannelBox(int indexNo)
{
    index = indexNo;
}

void ChannelBox::setChannel(int channelX)
{
    channel = channelX;
    emit emitChannel(index, channelX);
}

int ChannelBox::getChannel()
{
    return channel;
}
