#ifndef CHANNELBOX_H
#define CHANNELBOX_H

#include <QWidget>
#include <QComboBox>

class ChannelBox : public QComboBox
{
    Q_OBJECT
public:
    explicit ChannelBox(QWidget *parent = 0);
    void showPopup();
signals:

public slots:

};

#endif // CHANNELBOX_H
