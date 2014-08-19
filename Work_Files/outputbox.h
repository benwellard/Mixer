#ifndef OUTPUTBOX_H
#define OUTPUTBOX_H

#include <QWidget>
#include <QCheckBox>

class OutputBox : public QCheckBox
{
    Q_OBJECT
public:
    OutputBox(int indexNo);
    int index;
    bool checked;

signals:
    void emitIndex(int index);

public slots:
    void setOut();
};

#endif // OUTPUTBOX_H
