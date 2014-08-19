#include "mixer_main.h"
#include <QApplication>
#include <usb_mixer.h>
#include <controller.h>
#include <QProxyStyle>

class MyProxyStyle : public QProxyStyle
{
  public:
    int pixelMetric ( PixelMetric metric, const QStyleOption * option = 0, const QWidget * widget = 0 ) const
    {
        switch(metric) {
          case PM_SliderLength            : return 100;
          case PM_SliderThickness         : return 200;
          default                         : return (QProxyStyle::pixelMetric(metric,option,widget));
        }
    }
};



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //TODO Add outputSelector box, get it working
    //Add custom artwork for as much as possible





    MyProxyStyle *sliderStyle = new MyProxyStyle();
    a.setStyle(sliderStyle);
    mixer_main *w = new mixer_main();
    w->show();



    return a.exec();


}
