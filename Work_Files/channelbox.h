#ifndef CHANNELBOX_H
#define CHANNELBOX_H

#include <QComboBox>

class ChannelBox : public QComboBox
{
    Q_OBJECT
public:
    ChannelBox(int indexNo);
    int index;
    int channel;
    int getChannel();

public slots:
    void setChannel(int);

signals:
    void emitChannel(int,int);
};

#endif // CHANNELBOX_H
