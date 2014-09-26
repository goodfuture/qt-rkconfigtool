#include "dialog.h"

Dialog::Dialog(QWidget *parent, QPixmap &icon, QString &title) :
    DropShadowWidget(parent)
{
    this->setDropEnabled(true);
    this->setFixedSize(460, 320);

    title_icon_label = new QLabel();
    title_icon_label->setPixmap(icon);
    title_icon_label->setScaledContents(true);
    title_icon_label->setFixedSize(22, 22);

    title_string_label = new QLabel();
    title_string_label->setText(title);

    QPalette palette;
    palette.setColor(QPalette::Foreground, QColor(255, 255, 255));
    title_string_label->setPalette(palette);

    close_button = new PushButton();
    close_button->setPicName(QString(":/title_button/close"));
    this->connect(close_button, SIGNAL(clicked()), SLOT(close()));

    title_layout = new QHBoxLayout;
    title_layout->setSpacing(5);
    title_layout->addWidget(title_icon_label, 0, Qt::AlignVCenter);
    title_layout->addWidget(title_string_label, 0, Qt::AlignVCenter);
    title_layout->addStretch();
    title_layout->addWidget(close_button, 0, Qt::AlignTop);
    title_layout->setContentsMargins(5, 0, 0, 0);

    center_layout = new QVBoxLayout;

    main_layout = new QVBoxLayout(this);
    main_layout->addLayout(title_layout);
    main_layout->addLayout(center_layout, 1);
    main_layout->setContentsMargins(SHADOW_WIDTH, SHADOW_WIDTH, SHADOW_WIDTH, SHADOW_WIDTH);
    this->hide();
}

void Dialog::setTitleIcon(QPixmap &icon)
{
    title_icon_label->setPixmap(icon);
}

QVBoxLayout *Dialog::getLayout()
{
    return center_layout;
}

void Dialog::setTitleString(QString &title)
{
    title_string_label->setText(title);
}

void Dialog::paintEvent(QPaintEvent *event)
{
    DropShadowWidget::paintEvent(event);
    QPainter painter(this);
    int height = 27;
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawPixmap(QRect(SHADOW_WIDTH, SHADOW_WIDTH, this->width() - 2 * SHADOW_WIDTH, this->height() - 2 * SHADOW_WIDTH), QPixmap(":/skin/24_big"));
    painter.drawRect(QRect(SHADOW_WIDTH, height, this->width() - 2 * SHADOW_WIDTH, this->height() - SHADOW_WIDTH - height));
}
