#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

class Controller : public QObject
{
    Q_OBJECT
public:
    Controller();

    static unsigned short *getLevels();
    static void mapChannelToMix(int channel, int mixerChannel);
    static void mapMixInput(int input, int mixerChannel, int channel);
    static void changeVolume(int node, int volume);
    static int getMap(int channel);
    static int getMixerMap(int mixerChannel);
    static int getValue(int node);
    static void initController();
    static void deinitController();
private:
    static QMutex mutex;

public slots:


signals:

};

#endif // CONTROLLER_H
