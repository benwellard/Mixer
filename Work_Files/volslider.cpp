#include "volslider.h"
#include <QSlider>
VolSlider::VolSlider(int indexNo, int channelSelected, QWidget *parent) :
    QSlider()
{
    this->setTickPosition(QSlider::TicksRight);
    //currentValue = 0;
    index = indexNo;
    //channels are assigned incorrectly
    //TODO assign channels correctly
    channel = channelSelected + 1;
    muted = false;
}

void VolSlider::releaseIndex(int volume)
{
    currentValue = volume;
    if(muted)
       volume = -1000;
    emit emitIndex(channel, volume);
}

void VolSlider::muteChannel()
{
    if(!muted) {
    muted = true;
    emit emitUnmutedChannel(channel);
    }
    else
    {
    muted = false;
    emit emitMutedChannel(channel, currentValue);
    }
}

void VolSlider::changeChannel(int channelSel)
{
    channel = channelSel + 1;
}

void VolSlider::setInitValue(int value)
{
    currentValue = value;
    this->setValue(currentValue);
}
