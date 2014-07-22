#ifndef MIXER_H
#define MIXER_H

#include <QWidget>
#include <QHBoxLayout>
#include <QComboBox>
#include <volslider.h>

class Mixer : public QWidget
{
    Q_OBJECT
public:
    explicit Mixer();


signals:
    void emitVolume(int vol, int indexNo);
    void emitChannels(int channels);
public slots:
    void changeVolume(int vol);
    void constructMixer();
    void setChannels(int n);
    void addChannel();
    void setChannel(int channel);
    void newSlider();

private:
    int selectedChannel;
    QVBoxLayout *mainLayout;
    QWidget *channels;
    QWidget *volumes;
    QComboBox *addChannelBox();
};

#endif // MIXER_H
