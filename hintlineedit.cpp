#include "hintlineedit.h"

HintLineEdit::HintLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
}

void HintLineEdit::changeEvent(QEvent *event)
{
    QLineEdit::changeEvent(event);
    qDebug("Change");
}
