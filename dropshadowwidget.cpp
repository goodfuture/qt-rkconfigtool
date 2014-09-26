#include "dropshadowwidget.h"

DropShadowWidget::DropShadowWidget(QWidget *parent)
    : QDialog(parent)
{
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
    mousePressed = false;
    dropEnabled = false;
}

DropShadowWidget::~DropShadowWidget()
{
}

void DropShadowWidget::mousePressEvent(QMouseEvent *event)
{
    mousePressed = true;
    mousePoint = event->pos();
}

void DropShadowWidget::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}

void DropShadowWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (mousePressed && dropEnabled) {
        QPoint currentPoint = event->globalPos();
        move(currentPoint - mousePoint);
    }
}

void DropShadowWidget::setDropEnabled(bool value)
{
    dropEnabled = value;
}

void DropShadowWidget::setDropDisabled(bool value)
{
    dropEnabled = !value;
}

void DropShadowWidget::paintEvent(QPaintEvent *)
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(10, 10, this->width() - 20, this->height() - 20);
    //path.addRoundedRect(10, 10, this->width() - 20, this->height() - 20, 25, 25);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(path, QBrush(Qt::white));

    QColor color(0, 0, 0, 50);
    for (int index = 0; index < 10; index++) {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRect(10 - index, 10 - index, this->width() - 2 * (10 - index), this->height() - 2 * (10 - index));
        //path.addRoundedRect(10 - index, 10 - index, this->width() - 2 * (10 - index), this->height() - 2 * (10 - index), 25, 25);
        color.setAlpha(150 - qSqrt(index) * 50);
        painter.setPen(color);
        //painter.drawRect(10 - index, 10 - index, this->width() - 2 * (10 - index), this->height() - 2 * (10 - index));
        painter.drawPath(path);
    }
}

void DropShadowWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        return;
    }

    QDialog::keyPressEvent(event);
}

void DropShadowWidget::keyReleaseEvent(QKeyEvent *event)
{
    QDialog::keyReleaseEvent(event);
}

void DropShadowWidget::reject()
{
    //qDebug() << "Reject";
    QDialog::reject();
}
