#include "controller.h"
#include <QApplication>
#include <usb_mixer.h>
#include <iostream>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include <QMutex>
#include<interface.h>
static unsigned char levels[64];
static unsigned short* levelData;
QMutex Controller::mutex;


Controller::Controller()
    : QObject()
{


}

void Controller::initController()
{
    int g = usb_mixer_connect();
}

void Controller::deinitController()
{
    int g = usb_mixer_disconnect();
}

unsigned short* Controller::getLevels()
{
    mutex.lock();
    int y = usb_mixer_mem_get(0,0,levels);
    levelData = (unsigned short*)levels;
    mutex.unlock();
    return levelData;
}

void Controller::mapChannelToMix(int channel, int mixerChannel)
{
    int b = usb_set_aud_channel_map(channel ,mixerChannel);
}

int Controller::getChannelToMix(int channel)
{
    int r = usb_get_aud_channel_map(channel);
    return r;
}

int Controller::getMixerMap(int mixerChannel)
{
    mutex.lock();
    return usb_mixsel_get_state(0, mixerChannel);
    mutex.unlock();
}

void Controller::mapMixInput(int input, int mixerChannel, int channel)
{
    mutex.lock();
    usb_mixsel_set_state(input, mixerChannel, channel);
    mutex.unlock();
}

void Controller::changeVolume(int node, int volume)
{
    mutex.lock();
    int x = usb_mixer_set_value(0, node, volume);
    mutex.unlock();
}

int Controller::getMap(int channel)
{
    mutex.lock();
    int x = usb_get_aud_channel_map(channel);
    mutex.unlock();
    return x;
}

int Controller::getValue(int node)
{
    int y = usb_mixer_get_value(0,node);
    return y;
}




