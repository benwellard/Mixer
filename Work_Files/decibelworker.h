#ifndef DECIBELWORKER_H
#define DECIBELWORKER_H

#include <QObject>

class DecibelWorker : public QObject
{
    Q_OBJECT
public:
    explicit DecibelWorker(QObject *parent = 0);
    int calcMaster(int array[], int noChannels);
    int decAdd(long double x, long double c);
    int RMSadd(int a, int b);
signals:

public slots:

};

#endif // DECIBELWORKER_H
