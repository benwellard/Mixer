#ifndef VOLUMELEVEL_H
#define VOLUMELEVEL_H

#include <QWidget>
#include <QRect>
#include <QTimer>
#include <VolumeLevelintermixer.h>
#include <QGroupBox>
#include <QPainter>
#include <QList>

class VolumeLevel : public QGroupBox
{
    Q_OBJECT

public:
    explicit VolumeLevel(Interface *interfacevl, int channels, QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);
    void fillArray();
    int noChannels;
signals:

private:
    QTimer timer;
    int x,y,h;

    unsigned short * hArray;

    QRect vol;
    QPainter p;
    VolumeLevelInterMixer *vlim;

public slots:
    void setInputLevels();
};

#endif // VOLUMELEVEL_H
