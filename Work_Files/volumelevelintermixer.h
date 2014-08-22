#ifndef BOARDINTERMIXER_H
#define BOARDINTERMIXER_H

#include <QObject>
#include <interface.h>
#include <QList>

class VolumeLevelInterMixer : public QObject
{
    Q_OBJECT
public:
    explicit VolumeLevelInterMixer(Interface *interface, QObject *parent = 0);
    Interface *interfacev;
    unsigned short* levelsX;
    //unsigned short* levelDataX;
    unsigned short *getLevels();
    unsigned short * levelDataX;
    QList<unsigned short> values;
signals:
    void emitLevels(unsigned short*);

public slots:

};

#endif // BOARDINTERMIXER_H
