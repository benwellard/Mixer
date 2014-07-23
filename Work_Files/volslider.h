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
signals:
    void emitIndex(int index, int volume);
public slots:
    void releaseIndex(int volume);
};

#endif // VOLSLIDER_H
