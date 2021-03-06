#ifndef INTERFACE_H
#define INTERFACE_H

#include <QObject>
#include <controller.h>

class Interface : public QObject
{
    Q_OBJECT
public:
    Interface(int outputchannel, int mixChannel, Controller *controller);
    void MixerMapClear();
    int IDtoAbs(int mixerID);
    void addChannel(int channel);
    int AbstoID(int absChannel);
    int getValue(int channel);
    unsigned short* getLevels();
    int outputChannel;
    int mixerChannel;
    int prevChannel;
    int prevChannel2;
    Controller *controlleri;
public slots:
    void ChangeVolume(int channel, int volume);
    void setOutputChannel(int channel);
    void setChannel(int index, int channel);
private:
    void deletePreviousMapping();
    unsigned short * levelThings;
};

#endif // INTERFACE_H
