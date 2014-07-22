#ifndef VOLUMELEVEL_H
#define VOLUMELEVEL_H

#include <QWidget>
#include <QRect>
#include <QTimer>
#include <VolumeLevelintermixer.h>
class VolumeLevel : public QWidget
{

    Q_OBJECT
public:
    explicit VolumeLevel(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);


    void fillArray();
    int noChannels;

signals:

private:
    QTimer timer;
    int x,y,h;
    unsigned short *hArray;
    QRect vol;
    VolumeLevelInterMixer vlim;

public slots:
    void setInputLevels(unsigned short *hxArray);
    void setChannels(int n);
};

#endif // VOLUMELEVEL_H
