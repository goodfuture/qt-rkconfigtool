#include "logintitle.h"
#include <QLinearGradient>

LoginTitle::LoginTitle(QWidget *parent) :
    QWidget(parent)
{
    this->setFixedHeight(100);
    this->initWidgets();
    this->translate();

    QHBoxLayout *title_button_layout = new QHBoxLayout();
    title_button_layout->addWidget(icon_label);
    title_button_layout->addWidget(title_label);
    title_button_layout->addStretch();
    title_button_layout->addWidget(setting_button);
    title_button_layout->addWidget(minimum_button);
    title_button_layout->addWidget(close_button);
    title_button_layout->setSpacing(0);
    title_button_layout->setContentsMargins(SHADOW_WIDTH + 5, SHADOW_WIDTH, SHADOW_WIDTH, 0);

    QGridLayout *logo_name_layout = new QGridLayout();
    logo_name_layout->setContentsMargins(0, 0, 0, 0);
    logo_name_layout->setSpacing(8);
    logo_name_layout->addWidget(logo_label, 1, 1, 2, 1, Qt::AlignLeft | Qt::AlignTop);
    logo_name_layout->addWidget(zh_tool_label, 1, 2, Qt::AlignBottom);
    logo_name_layout->addWidget(en_tool_label, 2, 2, Qt::AlignTop);
    logo_name_layout->setColumnStretch(0, 1);
    logo_name_layout->setColumnStretch(3, 1);

    icon_label->setHidden(true);
    title_label->setHidden(true);

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->setSpacing(5);
    main_layout->setContentsMargins(0, 0, 0, 0);
    main_layout->addLayout(title_button_layout, 0);
    main_layout->addStretch();
    main_layout->addLayout(logo_name_layout, Qt::AlignHCenter);
    main_layout->addStretch();

    this->setLayout(main_layout);
}

void LoginTitle::initWidgets()
{
    icon_label = new QLabel(this);
    title_label = new QLabel(this);

    icon_label->setFixedSize(25, 25);
    icon_label->setPixmap(QPixmap(":/icon/tool"));
    icon_label->setScaledContents(true);

    setting_button = new PushButton(this);
    minimum_button = new PushButton(this);
    close_button = new PushButton(this);

    setting_button->setPicName(QString(":/title_button/setting"));
    minimum_button->setPicName(QString(":/title_button/min"));
    close_button->setPicName(QString(":/title_button/close"));

    connect(setting_button, &PushButton::clicked, this, &LoginTitle::showSettingWidget);
    connect(minimum_button, &PushButton::clicked, this, &LoginTitle::showMin);
    connect(close_button, &PushButton::clicked, this, &LoginTitle::closeWidget);

    logo_label = new QLabel(this);
    zh_tool_label = new QLabel(this);
    en_tool_label = new QLabel(this);

    logo_label->setFixedSize(180, 180 * 88 / 300);
    logo_label->setPixmap(QPixmap(":/icon/logo"));
    logo_label->setScaledContents(true);

    //zh_tool_label->setStyleSheet(QString("font: normal 12pt;color:white"));
    zh_tool_label->setStyleSheet(QString("font: bold 12pt;color:rgb(232, 232, 232)"));
    //en_tool_label->setStyleSheet(QString("font: bold italic 10pt ;color:rgb(114, 118, 125);"));
    en_tool_label->setStyleSheet(QString("font: bold 10pt ;color:rgb(247, 148, 29);"));
}

void LoginTitle::translate()
{
    setting_button->setToolTip(tr("Setting"));
    minimum_button->setToolTip(tr("Minimize"));
    close_button->setToolTip(tr("Close"));
    zh_tool_label->setText(tr("Tool Name"));
    en_tool_label->setText("DAA ToolBox");

    QGraphicsDropShadowEffect *drop_shadow_effect = new QGraphicsDropShadowEffect(this);
    drop_shadow_effect->setColor(QColor(0, 0, 0, 160));
    drop_shadow_effect->setOffset(1, 1);
    drop_shadow_effect->setBlurRadius(1);

    zh_tool_label->setGraphicsEffect(drop_shadow_effect);
}

void LoginTitle::setIconHidden(bool value)
{
    icon_label->setHidden(value);
}

void LoginTitle::setTitle(QString title, bool hidden, bool is_white)
{
    title_label->setText(title);
    title_label->setHidden(hidden);
    if (is_white) {
        title_label->setStyleSheet("color:white;font-weight:normal");
        //title_label->setStyleSheet("color:white;font-weight:bold");
    } else {
        title_label->setStyleSheet("color:black;font-weight:normal");
        //title_label->setStyleSheet("color:black;font-weight:bold");
    }
}

void LoginTitle::setSettingHidden(bool value)
{
    setting_button->setHidden(value);
}

void LoginTitle::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
}

void LoginTitle::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
}

void LoginTitle::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
}

void LoginTitle::paintEvent(QPaintEvent *)
{
#if 0
    QPainter painter(this);
    QLinearGradient linear;
    //qDebug("x = %d, y = %d", logo_label->pos().rx(), logo_label->pos().ry());
    //qDebug("height = %d, width = %d", this->height(), this->width());
    //linear.setStart(0, logo_label->pos().y() - 20);
    //linear.setFinalStop(0, logo_label->pos().y() + logo_label->height() + 20);
    linear.setStart(0, icon_label->height());
    linear.setFinalStop(this->rect().bottomLeft());
    linear.setColorAt(0, QColor(230, 230, 230, 0));
    linear.setColorAt(0.5, QColor(230, 230, 230, 100));
    linear.setColorAt(1, QColor(230, 230, 230, 200));
    painter.setBrush(linear);
    painter.drawRect(rect());
#endif
}
