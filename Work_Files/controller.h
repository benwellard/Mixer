#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QMutex>

class Controller : public QObject
{
    Q_OBJECT
public:
    Controller();


    unsigned short *getLevels();
    void mapChannelToMix(int channel, int mixerChannel);
    void mapMixInput(int input, int mixerChannel, int channel);
    void changeVolume(int node, int volume);
    int getMap(int channel);
    int getMixerMap(int mixerChannel);
    int getValue(int node);
    int initController();
    void deinitController();
    int getChannelToMix(int channel);
    unsigned char levels[64];
    bool isChannelFree(int channel);

private:

public slots:


signals:

};

#endif // CONTROLLER_H
