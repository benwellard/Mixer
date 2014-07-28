#ifndef VOLSLIDER_H
#define VOLSLIDER_H

#include <QWidget>
#include <QSlider>
class VolSlider : public QSlider
{
    Q_OBJECT
public:
    explicit VolSlider(int indexNo, int channelSelected, QWidget *parent = 0);
    int index;
    int channel;
    bool muted;
    int currentValue;
    void setInitValue(int value);
signals:
    void emitIndex(int index, int volume);
    void emitUnmutedChannel(int channel);
    void emitMutedChannel(int channel, int currentValue);
public slots:
    void releaseIndex(int volume);
    void changeChannel(int channelSel);
    void muteChannel();
};

#endif // VOLSLIDER_H
