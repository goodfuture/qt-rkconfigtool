#include "promptwidget.h"
#include <QPropertyAnimation>

PromptWidget::PromptWidget(QWidget *parent) :
    QWidget(parent)
{
    this->initSetting();
    this->initWidgets();

#if 0
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
#endif
}

void PromptWidget::initSetting()
{
    widget_width = this->parentWidget()->width() - 2 * SHADOW_WIDTH;
    this->resize(widget_width, 38);
    widget_height = this->height();

    this->setWindowFlags(Qt::FramelessWindowHint);
    QPalette palette;
    QColor color(190, 230, 250);
    color.setAlphaF(0.6);
    palette.setBrush(this->backgroundRole(), color);
    this->setPalette(palette);
    this->setAutoFillBackground(true);
}

void PromptWidget::initWidgets()
{
    close_button= new QToolButton(this);
    QPixmap close_pix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
    close_button->setIcon(close_pix);
    close_button->setStyleSheet("QToolButton{background-color: transparent;}");
    close_button->setGeometry(widget_width-20, 0, 20, 20);

    icon_label = new QLabel(this);
    icon_label->setGeometry(QRect(20, 10, 20, 20));
    icon_label->setStyleSheet("background-color: transparent;");
    icon_label->setScaledContents(true);

    msg_label = new QLabel(this);
    msg_label->setStyleSheet("background-color: transparent; color: red;");
    msg_label->setGeometry(QRect(30, 0, widget_width - 60, widget_height));
    msg_label->setAlignment(Qt::AlignCenter);

    close_button->setCursor(Qt::PointingHandCursor);
    QObject::connect(close_button, SIGNAL(clicked()), this, SLOT(closeWidget()));
}

void PromptWidget::closeWidget()
{
#if 0
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();
    connect(animation, SIGNAL(finished()), this, SLOT(hide()));
#endif
    this->hide();
}

void PromptWidget::setTipInfo(QString info)
{
    msg_label->setText(info);
}

void PromptWidget::setTipIcon(QPixmap pixmap)
{
    icon_label->setPixmap(pixmap);
}

void PromptWidget::showTip(QString info, QPixmap icon)
{
    this->setTipInfo(info);
    this->setTipIcon(icon);
    this->show();
    this->raise();
}
