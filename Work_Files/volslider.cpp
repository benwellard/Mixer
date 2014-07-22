#include "volslider.h"
#include <QSlider>
VolSlider::VolSlider(int indexNo, int channelSelected, QWidget *parent) :
    QSlider()
{
    this->setTickPosition(QSlider::TicksRight);
    this->setValue(80);
    index = indexNo;
    channel = channelSelected;
}
