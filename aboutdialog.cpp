#include "aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    DropShadowWidget(parent)
{
    setDropEnabled(true);
    this->setFixedSize(460, 320);

    this->initWidgets();

    QHBoxLayout *title_layout = new QHBoxLayout();
    title_layout->setSpacing(5);
    title_layout->addWidget(title_icon_label, 0, Qt::AlignVCenter);
    title_layout->addWidget(title_label, 0, Qt::AlignVCenter);
    title_layout->addStretch();
    title_layout->addWidget(close_button, 0, Qt::AlignTop);
    title_layout->setContentsMargins(5, 0, 0, 0);

    QHBoxLayout *bottom_layout = new QHBoxLayout();
    bottom_layout->setSpacing(0);
    bottom_layout->addStretch();
    bottom_layout->addWidget(ok_button, 0, Qt::AlignVCenter);
    bottom_layout->setContentsMargins(0, 0, 30, 20);

    QVBoxLayout *centeral_layout = new QVBoxLayout();
    centeral_layout->setSpacing(5);
    centeral_layout->addSpacing(20);
    centeral_layout->addWidget(logo_label, 0, Qt::AlignHCenter);
    centeral_layout->addSpacing(20);
    centeral_layout->addWidget(head_company_label, 0, Qt::AlignLeft);
    centeral_layout->addWidget(head_company_addr_label, 0, Qt::AlignLeft);
    centeral_layout->addSpacing(10);
    centeral_layout->addWidget(manufacture_company_label, 0, Qt::AlignLeft);
    centeral_layout->addWidget(manufacture_company_addr_label, 0, Qt::AlignLeft);
    centeral_layout->addSpacing(10);
    centeral_layout->addWidget(copyright_label, 0, Qt::AlignLeft);
    centeral_layout->setContentsMargins(50, 0, 50, 0);

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->setSpacing(0);
    main_layout->addLayout(title_layout, 0);
    main_layout->addLayout(centeral_layout, 0);
    main_layout->addStretch();
    main_layout->addLayout(bottom_layout, 0);
    main_layout->setContentsMargins(SHADOW_WIDTH, SHADOW_WIDTH, SHADOW_WIDTH, SHADOW_WIDTH);

    connect(close_button, SIGNAL(clicked()), this, SLOT(hide()));
    connect(ok_button, SIGNAL(clicked()), this, SLOT(hide()));

    this->setLayout(main_layout);
    this->translate();
}

void AboutDialog::initWidgets()
{
    title_icon_label = new QLabel(this);
    title_label = new QLabel(this);
    close_button = new PushButton(this);
    logo_label = new QLabel(this);
    ok_button = new QPushButton(this);

    title_icon_label->setPixmap(QPixmap(":/icon/AppIcon"));
    title_icon_label->setFixedSize(22, 22);
    title_icon_label->setScaledContents(true);
    title_label->setStyleSheet(QString("color:white;font:bold"));
    close_button->setPicName(QString(":/title_button/close"));

    logo_label->setPixmap(QPixmap(":/icon/logo"));
    int width = this->width() / 2;
    int height = width * 88 / 300;
    //qDebug("width = %d, height = %d", width, height);
    logo_label->setFixedSize(width, height);
    logo_label->setScaledContents(true);

    head_company_label = new QLabel(this);
    head_company_label->setStyleSheet(QString("color:rgb(0, 84, 166);font:bold"));
    head_company_addr_label = new QLabel(this);
    manufacture_company_label = new QLabel(this);
    manufacture_company_label->setStyleSheet(QString("color:rgb(0, 84, 166);font:bold"));
    manufacture_company_addr_label = new QLabel(this);
    copyright_label = new QLabel(this);
    copyright_label->setStyleSheet(QString("color:gray"));
}

void AboutDialog::translate()
{
    title_label->setText(QString(tr("About")));
    ok_button->setText(tr("ok"));
    head_company_label->setText(tr("Head Company Name"));
    head_company_addr_label->setText(tr("Head Company Address"));
    manufacture_company_label->setText(tr("Manufacture Company Name"));
    manufacture_company_addr_label->setText(tr("Manufacture Company Address"));
    copyright_label->setText("Copyright(c) Rockontrol Inc. All Rights Reserved.");
}

void AboutDialog::paintEvent(QPaintEvent *event)
{
    DropShadowWidget::paintEvent(event);
    QPainter painter(this);
    int height = 27;
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawPixmap(QRect(SHADOW_WIDTH, SHADOW_WIDTH, this->width() - 2 * SHADOW_WIDTH, this->height() - 2 * SHADOW_WIDTH), QPixmap(":/skin/24_big"));
    painter.drawRect(QRect(SHADOW_WIDTH, height, this->width() - 2 * SHADOW_WIDTH, this->height() - SHADOW_WIDTH - height));
}
