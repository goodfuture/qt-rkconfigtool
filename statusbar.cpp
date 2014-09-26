#include "statusbar.h"
#include <QHBoxLayout>
#include <QPalette>

StatusBar::StatusBar(QWidget *parent) :
    QWidget(parent)
{
    msg_timer = link_on_timer = 0;

    //setWindowFlags(Qt::Window| Qt::FramelessWindowHint);
    //setAttribute(Qt::WA_TranslucentBackground, true);

    /*
    QFont &font = const_cast<QFont &>(this->font());
    font.setPointSize(10);
    */

    //setStyleSheet(QString("border:0px; background:rgba(52, 138, 221, 230)"));
    setStyleSheet(QString("border:0px; color:rgba(255, 255, 255, 230)"));

    //QPalette palette;
    //palette.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255, 245)));
    //palette.setColor(Qt::BackgroundColorRole, QColor());
    //palette.setColor(QPalette::Foreground, QColor(255, 255, 255));
    //palette.setColor(QPalette::Background, QColor(255, 255, 255));
    //setPalette(palette);

    setFixedHeight(28);
    //setAutoFillBackground(true);

    message_label = new QLabel(this);
    message_label->setText(QString(tr("Main Program Version")) + QString(":") + QString(PROGRAM_VERSION_NUM));
    message_label->setFixedWidth(WINDOW_WIDTH / 4);

    copyright_label = new QLabel(this);
    copyright_label->setAlignment(Qt::AlignCenter);
    copyright_label->setText(QString(tr("TaiYuan Rockontrol Industrial Inc")));
    copyright_label->setFixedWidth(WINDOW_WIDTH / 4);

    QWidget *widget = new QWidget(this);
    widget->setFixedWidth(WINDOW_WIDTH / 4);

    link_status_icon = new QLabel();
    link_status_icon->setScaledContents(true);
    link_status_icon->setFixedSize(20, 20);
    //link_status_icon->setStyleSheet(QString("background:rgb(255,255,255, 0)"));

    link_status_text = new QLabel();
    //link_status_text->setStyleSheet(QString("background:rgb(255,255,255, 0)"));

    link_timer_label = new QLabel();
    link_timer_label->clear();

    QHBoxLayout *widget_layout = new QHBoxLayout(widget);
    widget_layout->addStretch();
    widget_layout->addWidget(link_status_icon);
    widget_layout->addWidget(link_status_text);
    widget_layout->addWidget(link_timer_label);
    widget_layout->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *h_layout = new QHBoxLayout(this);
    h_layout->setContentsMargins(5, 0, 5, 0);
    //h_layout->setSpacing(0);
    h_layout->addWidget(message_label);
    h_layout->addStretch(1);
    h_layout->addWidget(copyright_label);
    h_layout->addStretch(1);
    h_layout->addWidget(widget);

    showLinkOff();
    //showLinkOn();
}

void StatusBar::showMessage(const QString &message, int timeout)
{
    if (timeout != 0) {
        if (msg_timer) {
            killTimer(msg_timer);
        }
        msg_timer = startTimer(timeout);
    }
    message_label->setText(message);
}

void StatusBar::clearMessage()
{
    message_label->clear();
}

void StatusBar::showLinkOn(bool value)
{
    link_on_counter = 0;
    if (link_on_timer) {
        killTimer(link_on_timer);
        link_on_timer = 0;
    }
    if (value) {
        link_status_icon->setPixmap(QPixmap(":/icon/link_on"));
        link_status_text->setText(tr("link success"));
        link_on_timer = startTimer(1000);
    } else {
        link_status_icon->setPixmap(QPixmap(":/icon/link_off"));
        link_status_text->setText(tr("link failed"));
        link_timer_label->clear();
    }
}

void StatusBar::showLinkOff(bool value)
{
    showLinkOn(!value);
}

void StatusBar::timerEvent(QTimerEvent *timer)
{
    int minute, second;
    if (timer->timerId() == msg_timer) {
        killTimer(msg_timer);
        msg_timer = 0;
        clearMessage();
        message_label->setText(QString(tr("Main Program Version")) + QString(":") + QString(PROGRAM_VERSION_NUM));
    } else if (timer->timerId() == link_on_timer) {
        link_on_counter++;
        minute = link_on_counter / 60;
        second = link_on_counter % 60;
        QString string;
        string = QString("%1").arg(minute, 3) + QString(tr("minute"))
                + QString("%1").arg(second, 2) + QString(tr("second"));
        link_timer_label->setText(string);
    }
}

void StatusBar::paintEvent(QPaintEvent *)
{
    //QWidget::paintEvent(event);
    /*
    QStyleOption opt;
    opt.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    */
    QLinearGradient linear(this->rect().topLeft(), this->rect().bottomLeft());
    linear.setColorAt(0, QColor(255, 255, 255, 80));
    linear.setColorAt(0.1, QColor(52, 138, 221, 255));
    linear.setColorAt(1, QColor(52, 138, 221, 255));
    //linear.setColorAt(1, QColor(255, 255, 255, 80));

    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(linear));
    painter.fillRect(this->rect(), Qt::transparent);
    painter.drawRect(this->rect());
}
