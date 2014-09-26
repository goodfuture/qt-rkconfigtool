#include "logolabel.h"

LogoLabel::LogoLabel(QWidget *parent) :
    QWidget(parent)
{
    this->flashRatio = 0.0f;
    this->flashTimer = 0;
    this->cycleTimer = 0;
    this->mouseIn = false;
    this->flashInterval = 35;
    this->cycleInterval = this->flashInterval * 60;
    //qDebug() << this->flashInterval << this->cycleInterval;
}

void LogoLabel::paintEvent(QPaintEvent *)
{
    QLinearGradient edge_linear(this->rect().topLeft(), this->rect().topRight());
    edge_linear.setColorAt(0, QColor(255, 255, 255, 0));
    edge_linear.setColorAt(0.3, QColor(255, 255, 255, 255));
    edge_linear.setColorAt(0.7, QColor(255, 255, 255, 255));
    edge_linear.setColorAt(1, QColor(255, 255, 255, 0));

    QLinearGradient middle_linear(this->rect().topLeft(), this->rect().topRight());
#if 0
    if (mouseIn) {
        middle_linear.setColorAt(0, QColor(255, 255, 255, 0));
        middle_linear.setColorAt(0.2, QColor(255, 255, 255, 200));
        middle_linear.setColorAt(0.5, QColor(255, 255, 255, 255));
        middle_linear.setColorAt(0.8, QColor(255, 255, 255, 200));
        middle_linear.setColorAt(1, QColor(255, 255, 255, 0));
    } else {
        middle_linear.setColorAt(0, QColor(255, 255, 255, 0));
        middle_linear.setColorAt(0.5, QColor(255, 255, 255, 180));
        middle_linear.setColorAt(1, QColor(255, 255, 255, 0));
    }
#else
    middle_linear.setColorAt(0, QColor(255, 255, 255, 0));
    middle_linear.setColorAt(0.2, QColor(255, 255, 255, 110));
    middle_linear.setColorAt(0.5, QColor(255, 255, 255, 180));
    middle_linear.setColorAt(0.8, QColor(255, 255, 255, 110));
    middle_linear.setColorAt(1, QColor(255, 255, 255, 0));
#endif

    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(edge_linear));
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    int edge_height = 1;
    QRect top_edge_rect(0, 0, this->width(), edge_height);
    QRect middle_rect(0, edge_height, this->width(), this->height() - 2 * edge_height);
    QRect bottom_edge_rect(0, this->height() - edge_height, this->width(), edge_height);
    QRect logo_rect(middle_rect.topLeft() + QPoint(10, edge_height + 8), middle_rect.bottomRight() - QPoint(10, edge_height + 8));

    painter.drawRect(top_edge_rect);
    painter.drawRect(bottom_edge_rect);

    painter.setBrush(QBrush(middle_linear));
    painter.drawRect(middle_rect);

    QPixmap	logoPixmap(":/icon/logo");
    QPainter pixmap_painter(&logoPixmap);
    pixmap_painter.setPen(Qt::NoPen);

    if (flashTimer != 0) {
        QLinearGradient flash_linear(logoPixmap.rect().topLeft(), logoPixmap.rect().bottomRight());
        flash_linear.setColorAt(0, QColor(255, 255, 255, 0));
        if (flashRatio - 0.1f >= 0) {
            flash_linear.setColorAt(flashRatio - 0.1, QColor(255, 255, 255, 0));
        }
        flash_linear.setColorAt(flashRatio, QColor(255, 255, 255, 255));
        if (flashRatio + 0.1f <= 1) {
            flash_linear.setColorAt(flashRatio + 0.1, QColor(255, 255, 255, 0));
        }
        flash_linear.setColorAt(1, QColor(255, 255, 255, 0));

        pixmap_painter.setBrush(QBrush(flash_linear));
        pixmap_painter.setCompositionMode(QPainter::CompositionMode_SourceAtop);
        pixmap_painter.drawRect(logoPixmap.rect());
    }
    pixmap_painter.end();
    painter.drawPixmap(logo_rect, logoPixmap);
}

void LogoLabel::timerEvent(QTimerEvent *event)
{
    QWidget::timerEvent(event);
    if (event->timerId() == flashTimer) {
        flashRatio += 0.1f;
        if (flashRatio >= 1.0f) {
            flashRatio = 0.0f;
            killTimer(flashTimer);
            flashTimer = 0;
        }
    } else if (event->timerId() == cycleTimer) {
        if (flashTimer) {
            killTimer(flashTimer);
            flashTimer = 0;
        }
        flashTimer = startTimer(this->flashInterval);
    }
    this->repaint();
}

void LogoLabel::enterEvent(QEvent *)
{
    mouseIn = true;
    if (flashTimer == 0) {
        flashTimer = startTimer(this->flashInterval);
    }

    if (cycleTimer == 0) {
        cycleTimer = startTimer(this->cycleInterval);
    }
}

void LogoLabel::leaveEvent(QEvent *)
{
    mouseIn = false;
    if (cycleTimer) {
        killTimer(cycleTimer);
        cycleTimer = 0;
    }
    this->repaint();
}
