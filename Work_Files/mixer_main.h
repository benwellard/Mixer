#ifndef MIXER_MAIN_H
#define MIXER_MAIN_H

#include <QWidget>
#include <volumelevel.h>
#include <mixer.h>

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
    void constructWindow();
    void saveAndLoadArray(int tab);

private:
    Ui::mixer_main *ui;
    int noOfChannels;
    Mixer *mix1;
    Mixer *mix2;

};

#endif // MIXER_MAIN_H
