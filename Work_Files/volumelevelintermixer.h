#ifndef BOARDINTERMIXER_H
#define BOARDINTERMIXER_H

#include <QObject>
#include <interface.h>
class VolumeLevelInterMixer : public QObject
{
    Q_OBJECT
public:
    explicit VolumeLevelInterMixer(QObject *parent = 0);
    Interface *interface;
    unsigned short* levelsX;
    //unsigned short* levelDataX;

signals:
    void emitLevels(unsigned short*);

public slots:
    void getLevels();
};

#endif // BOARDINTERMIXER_H
