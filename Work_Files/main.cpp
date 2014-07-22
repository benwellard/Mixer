#include "mixer_main.h"
#include <QApplication>
#include <usb_mixer.h>
#include <controller.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);





    mixer_main *w = new mixer_main();
    w->show();



    return a.exec();


}
