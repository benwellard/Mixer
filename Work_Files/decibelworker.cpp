#include "decibelworker.h"
#include <math.h>
#include <QQueue>
DecibelWorker::DecibelWorker(QObject *parent) :
    QObject(parent)
{




}


int DecibelWorker::calcMaster(int array[], int noChannels)
{
    long double a,b;
    int c;
    a = 0.0;
    b = 0.0;
    c = 0;
    long double x = 0.0;

    for(int i = 1; i <= noChannels; i = i + 2) {
        if(array[i] != 0 || array[i+1] != 0) {

        a = array[i];
        if(a != 0){
        a = a/10;
        a = pow(10,a);
        }

        b = array[i+1];
        if(b !=0) {
        b = b/10;
        b = pow(10, b);
        }
        x = a + b;
        x = log10(x);
        x = 10 * x;
        c = (decAdd(x, c));
        }

    }
    return c;

}

int DecibelWorker::decAdd(long double a, long double b) {

    if(a != 0){
    a = a/10;
    a = pow(10,a);
    }

    if(b !=0) {
    b = b/10;
    b = pow(10, b);
    }
    long double x = a + b;
    x = log10(x);
    x = 10 * x;

    return x;
}

int DecibelWorker::RMSadd(int a, int b)
{

    long double x;

    int c;

    c = 0;
    x = 0.0;
    a = pow(a, 2);
    b = pow(b, 2);
    x = (a + b)/2;
    x = sqrt(x);




}



