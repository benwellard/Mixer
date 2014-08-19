#include "outputbox.h"

OutputBox::OutputBox(int indexNo) : QCheckBox()
{
    index = indexNo;
    checked = false;
}

void OutputBox::setOut()
{
    emit emitIndex(index);
}
