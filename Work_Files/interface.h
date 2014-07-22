#ifndef INTERFACE_H
#define INTERFACE_H

#include <QObject>

class Interface : public QObject
{
    Q_OBJECT
public:
    Interface();
    static void MixerMapClear();
    static int IDtoAbs(int mixerID);
    static void addChannel(int channel);
    static int CreateMix(int noChannels);
    static int AbstoID(int absChannel);

    static unsigned short* getLevels();
    static void setOutputChannel(int channel);

public slots:
    void ChangeVolume(int channel, int volume);

};

#endif // INTERFACE_H
