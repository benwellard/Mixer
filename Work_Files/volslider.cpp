#include "volslider.h"
#include <QSlider>
#include <QDial>

VolSlider::VolSlider(int indexNo, int channelSelected, QWidget *parent) :
    QSlider()
{
    this->setStyleSheet("QSlider::handle { image: url(:/new/prefix1/sliderimage.jpg); border-radius:2px;}");
    index = indexNo;
    //channels are assigned incorrectly
    //TODO assign channels correctly
    channel = channelSelected;
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
    //channel = channelSel;
    //Map the new selected Channel(channelSel) to this

}

void VolSlider::setInitValue(int value)
{
    currentValue = value;
    this->setValue(currentValue);
}
