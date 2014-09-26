#ifndef DIALOG_H
#define DIALOG_H

#include "common.h"
#include "pushbutton.h"
#include "dropshadowwidget.h"

#include <QFont>
#include <QRect>
#include <QLabel>
#include <QPoint>
#include <QString>
#include <QPixmap>
#include <QPainter>
#include <QPalette>
#include <QPaintEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>

class Dialog : public DropShadowWidget
{
    Q_OBJECT
public:
    explicit Dialog(QWidget *parent = 0, QPixmap &icon = QPixmap(), QString &title = QString());
    ~Dialog(){}
    QVBoxLayout *getLayout();

signals:

public slots:
    void setTitleIcon(QPixmap &icon);
    void setTitleString(QString &title);

protected:
    virtual void paintEvent(QPaintEvent *);

private:
    QHBoxLayout *title_layout;
    QVBoxLayout *center_layout;
    QVBoxLayout *main_layout;
    QLabel *title_icon_label;
    QLabel *title_string_label;
    PushButton *close_button;
};

#endif // DIALOG_H
