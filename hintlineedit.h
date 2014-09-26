#ifndef HINTLINEEDIT_H
#define HINTLINEEDIT_H

#include <QLineEdit>
#include <QEvent>

class HintLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit HintLineEdit(QWidget *parent = 0);

signals:

public slots:

protected slots:
    void 	changeEvent(QEvent *);

};

#endif // HINTLINEEDIT_H
