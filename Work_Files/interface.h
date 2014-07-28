#ifndef INTERFACE_H
#define INTERFACE_H

#include <QObject>

class Interface : public QObject
{
    Q_OBJECT
public:
    Interface(int outputchannel, int mixChannel);
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
public slots:
    void ChangeVolume(int channel, int volume);
    void setOutputChannel(int channel);

private:
    void deletePreviousMapping();
};

#endif // INTERFACE_H
