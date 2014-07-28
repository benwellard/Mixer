#ifndef MIXER_H
#define MIXER_H

#include <QWidget>
#include <QHBoxLayout>
#include <QComboBox>
#include <volslider.h>
#include <QList>
#include <interface.h>

class Mixer : public QWidget
{
    Q_OBJECT
public:
    explicit Mixer(int output, int mixerOut);
signals:
    void emitVolume(int vol, int indexNo);
    void emitChannels(int channels);
    void emitCurrentOutput(int output);

public slots:
    void changeVolume(int indexVal, int vol);
    void constructMixer(int output);
    void setChannels(int n);
    void addChannel();
    void setChannel(int channel);
    void newSlider();
    void saveVolumesArray();
    void loadVolumesArray();
    void muteChannelController(int channel);
    void unMuteChannelController(int channel, int volume);
    void clearChannels(int nothing);

private:
    QList<VolSlider *> sliders;
    QList<QComboBox *> selectors;
    int selectedChannel;
    int indexNo;
    QHBoxLayout *sliderLayout;
    QVBoxLayout *mainLayout;
    QWidget *channels;
    QWidget *volumes;
    QComboBox *addChannelBox();
    QComboBox *addOutputBox();
    Interface *interface;
    void initVolumesArray();
    QList<int> volArray;
    bool mute;


};

#endif // MIXER_H
