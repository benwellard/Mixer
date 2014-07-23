#ifndef MIXER_H
#define MIXER_H

#include <QWidget>
#include <QHBoxLayout>
#include <QComboBox>
#include <volslider.h>
#include <QList>

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

private:
    QList<VolSlider *> sliders;
    int selectedChannel;
    QVBoxLayout *mainLayout;
    QWidget *channels;
    QWidget *volumes;

    QComboBox *addChannelBox();
    QComboBox *addOutputBox();
};

#endif // MIXER_H
