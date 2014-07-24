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
    static int AbstoID(int absChannel);

    static unsigned short* getLevels();


public slots:
    void ChangeVolume(int channel, int volume);
    void setOutputChannel(int channel);

private:
    //static int outputChannel;
};

#endif // INTERFACE_H
