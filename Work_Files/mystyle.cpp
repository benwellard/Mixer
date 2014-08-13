#include "mystyle.h"
#include <QProxyStyle>
#include <QStyleOption>

class MyStyle : public QProxyStyle
{
  public:
    int pixelMetric ( PixelMetric metric, const QStyleOption * option = 0, const QWidget * widget = 0 ) const
    {
        switch(metric) {
          case PM_SliderLength            : return 150;
          default                         : return (QProxyStyle::pixelMetric(metric,option,widget));
        }
    }
};
