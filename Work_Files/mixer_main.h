#ifndef MIXER_MAIN_H
#define MIXER_MAIN_H

#include <QWidget>
#include <volumelevel.h>

namespace Ui {
class mixer_main;
}

class mixer_main : public QWidget
{
    Q_OBJECT

public:
    explicit mixer_main();
    ~mixer_main();
    VolumeLevel *volumeMix1;
    VolumeLevel *volumeMix2;
    VolumeLevel *volumeMix3;

private slots:
    void noChannelsSlot(int noChannels);
    void constructWindow();
private:
    Ui::mixer_main *ui;
    int noOfChannels;

};

#endif // MIXER_MAIN_H
