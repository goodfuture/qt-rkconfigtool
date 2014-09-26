#include "checkbox.h"

CheckBox::CheckBox(QWidget *parent) :
    QWidget(parent)
{
    this->setFixedSize(17, 17);
    mouse_press = false;
    is_checked = false;
    status = NORMAL;
}

void CheckBox::setCheck(bool check)
{
    is_checked = check;
}

void CheckBox::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        mouse_press = true;
        status = PRESS;
        update();
    }
}

void CheckBox::mouseReleaseEvent(QMouseEvent *event)
{
    status = NORMAL;
    if (mouse_press && rect().contains(event->pos())) {
        mouse_press = false;
        is_checked = !is_checked;
        emit checked(is_checked);
    }
    update();
}

void CheckBox::enterEvent(QEvent *)
{
    status = ENTER;
    update();
}

void CheckBox::leaveEvent(QEvent *)
{
    status = NORMAL;
    update();
}

void CheckBox::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    switch(status) {
    case NORMAL:
    case NOSTATUS: {
        if (is_checked) {
            painter.drawPixmap(rect(), QPixmap(QString(":/check_box/box_checked")));
        } else {
            painter.drawPixmap(rect(), QPixmap(QString(":/check_box/box_normal")));
        }
        break;
    }
    case ENTER:
    case PRESS:
        if (is_checked) {
            painter.drawPixmap(rect(), QPixmap(QString(":/check_box/box_checked_highlight")));
        } else {
            painter.drawPixmap(rect(), QPixmap(QString(":/check_box/box_highlight")));
        }
        break;
    }
}
