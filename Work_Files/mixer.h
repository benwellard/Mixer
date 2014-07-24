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
    explicit Mixer();


signals:
    void emitVolume(int vol, int indexNo);
    void emitChannels(int channels);
public slots:
    void changeVolume(int indexVal, int vol);
    void constructMixer();
    void setChannels(int n);
    void addChannel();
    void setChannel(int channel);
    void newSlider();
    void saveVolumesArray();
    void loadVolumesArray();
private:
    QList<VolSlider *> sliders;
    int selectedChannel;
    int indexNo;
    QHBoxLayout *sliderLayout;
    QVBoxLayout *mainLayout;
    QWidget *channels;
    QWidget *volumes;
    QComboBox *addChannelBox();
    QComboBox *addOutputBox();
    void initVolumesArray();
    QList<int> volArray;
};

#endif // MIXER_H
