#include "switcher.h"

Switcher::Switcher(QWidget *parent) :
    QWidget(parent)
{
    switch_on = false;
    mouse_pressed = false;
    pix_on.load(QString(":/switch_button/switcher_on"));
    pix_off.load(QString(":/switch_button/switcher_off"));
    this->setFixedSize(pix_on.size());
}

void Switcher::setSwitcher(bool on)
{
    switch_on = on;
}

void Switcher::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        mouse_pressed = true;
    }
}

void Switcher::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if (mouse_pressed) {
            mouse_pressed = false;
            switch_on = !switch_on;
            emit switcher(switch_on);
            update();
        }
    }
}

void Switcher::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QRect rect;

#if 0
    QFont font = painter.font();
    font.setBold(true);
    painter.setFont(font);
#endif

    if (switch_on) {
        painter.drawPixmap(this->rect(), pix_on);
        painter.setPen(QColor(100, 149, 0));
        rect.setTopLeft(this->rect().topLeft());
        rect.setBottomRight(QPoint(this->width() / 2, this->height()));
        painter.drawText(rect, Qt::AlignCenter, tr("ON"));

        painter.setPen(QColor(168, 168, 168));
        rect.setBottomRight(this->rect().bottomRight());
        rect.setTopLeft(QPoint(this->width() / 2 - 3, this->rect().top()));
        rect.setHeight(this->height());
        rect.setWidth(this->width() / 2);
        painter.drawText(rect, Qt::AlignCenter, tr("OFF"));
    } else {
        painter.drawPixmap(this->rect(), pix_off);
        painter.setPen(QColor(168, 168, 168));
        rect.setTopLeft(QPoint(this->rect().left() + 3, this->rect().top()));
        rect.setBottomRight(QPoint(this->width() / 2, this->height()));
        painter.drawText(rect, Qt::AlignCenter, tr("ON"));

        painter.setPen(QColor(194, 33, 33));
        rect.setBottomRight(this->rect().bottomRight());
        rect.setTopLeft(QPoint(this->width() / 2, this->rect().top()));
        rect.setHeight(this->height());
        rect.setWidth(this->width() / 2);
        painter.drawText(rect, Qt::AlignCenter, tr("OFF"));
    }
}
