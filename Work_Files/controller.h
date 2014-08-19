#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QMutex>
#include <QAndroidJniObject>

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
    QAndroidJniObject activity;
    unsigned short* levelData;
    bool isChannelFree(int channel);

private:

public slots:


signals:

};

#endif // CONTROLLER_H
