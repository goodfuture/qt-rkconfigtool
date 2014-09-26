#include "switchbutton.h"

SwitchButton::SwitchButton(QWidget *parent) :
    QWidget(parent)
{
    switch_on = false;
    mouse_pressed = false;
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);

    pixmap_fg_on.load(QString(":/switch_button/fg_on"));
    pixmap_fg_off.load(QString(":/switch_button/fg_off"));
    pixmap_bg.load(QString(":/switch_button/bg"));
    this->setFixedSize(pixmap_bg.width(), pixmap_bg.height());
}

void SwitchButton::setSwitch(bool on)
{
    this->switch_on = on;
}

void SwitchButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        mouse_pressed = true;
    }
}

void SwitchButton::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        if (mouse_pressed) {
            switch_on = !switch_on;
            mouse_pressed = false;
            this->update();
            emit switched(switch_on);
        }
    }
}

void SwitchButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(QPoint(0, 0), pixmap_bg);

#if 1
    QRect rect;

    painter.setPen(QColor(255, 255, 255));
    if (switch_on) {
        painter.drawPixmap(this->rect().topLeft(), pixmap_fg_on);
        rect.setTopLeft(this->rect().topLeft());
        rect.setBottomRight(QPoint(pixmap_fg_on.width(), this->rect().bottom()));
        painter.drawText(rect, Qt::AlignCenter, tr("On"));
    } else {
        painter.drawPixmap(this->rect().width() - pixmap_fg_off.width(), this->rect().top(), pixmap_fg_off);
        rect.setTopLeft(QPoint(this->rect().width() - pixmap_fg_off.width(), this->rect().top()));
        rect.setBottomRight(this->rect().bottomRight());
        painter.drawText(rect, Qt::AlignCenter, tr("Off"));
    }
#else
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(QBrush(QColor(72, 128, 226), Qt::SolidPattern));

    painter.drawRoundedRect(this->rect(), 3, 3);

    painter.setBrush(QBrush(QColor()));
    if (switch_on) {
    } else {
    }

#endif
}
