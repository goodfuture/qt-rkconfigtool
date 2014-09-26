#include "pushbutton.h"

PushButton::PushButton(QWidget *parent) :
    QPushButton(parent)
{
    mouse_press = false;
    status = NORMAL;
}

PushButton::~PushButton()
{
}

void PushButton::setPicName(QString name)
{
    pic_name = name;
    setFixedSize(QPixmap(name).size());
}

void PushButton::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        mouse_press = true;
        status = PRESS;
        update();
    }
}

void PushButton::mouseReleaseEvent(QMouseEvent *event)
{
    status = NORMAL;
    if (mouse_press && rect().contains(event->pos())) {
        mouse_press = false;
        emit clicked();
    }
    update();
}

void PushButton::enterEvent(QEvent *)
{
    status = ENTER;
    update();
}

void PushButton::leaveEvent(QEvent *)
{
    status = NORMAL;
    update();
}

void PushButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    switch(status) {
    case NORMAL:
    case NOSTATUS:
        painter.drawPixmap(rect(), QPixmap(pic_name));
        break;
    case ENTER:
        painter.drawPixmap(rect(), QPixmap(pic_name + "_hover"));
        break;
    case PRESS:
        painter.drawPixmap(rect(), QPixmap(pic_name + "_pressed"));
        break;
    }
}
