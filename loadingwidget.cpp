#include "loadingwidget.h"

LoadingWidget::LoadingWidget(QWidget *parent) :
    QWidget(parent)
{
    index = 1;
    this->initWidgets();

    QVBoxLayout *center_layout = new QVBoxLayout();
    center_layout->addSpacing(30);
    center_layout->addWidget(loading_label, 0, Qt::AlignHCenter);
    center_layout->addWidget(prompt_label, 0, Qt::AlignHCenter);
    center_layout->setSpacing(15);
    center_layout->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *bottom_layout = new QHBoxLayout();
    bottom_layout->addWidget(cancel_button, 0, Qt::AlignRight);
    bottom_layout->setContentsMargins(0, 0, 30, 0);

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addStretch();
    main_layout->addLayout(center_layout);
    main_layout->addStretch();
    main_layout->addLayout(bottom_layout, 0);
    main_layout->setSpacing(20);
    main_layout->setContentsMargins(0, 0, 0, 30);

    timer = new QTimer(this);
    timer->setInterval(100);
    connect(timer, &QTimer::timeout, this, &LoadingWidget::updatePixmap);

    this->setLayout(main_layout);
    this->translate();
}

void LoadingWidget::initWidgets()
{
    loading_label = new QLabel();
    prompt_label = new QLabel();

    QPixmap pixmap(QString(":/login/") + QString::number(index, 10));
    loading_label->setFixedSize(pixmap.size());
    loading_label->setPixmap(pixmap);
    loading_label->setScaledContents(true);

    cancel_button = new QPushButton(this);
    connect(cancel_button, SIGNAL(clicked()), this, SIGNAL(cancel()));
}

void LoadingWidget::translate()
{
    prompt_label->setText(tr("Waiting"));
    cancel_button->setText(tr("Cancel"));
}

void LoadingWidget::updatePixmap()
{
    index++;
    if (index > 8)
        index = 1;

    QPixmap pixmap(QString(":/login/") + QString::number(index, 10));
    loading_label->setPixmap(pixmap);
}

void LoadingWidget::start()
{
    timer->start();
}

void LoadingWidget::stop()
{
    index = 1;
    timer->stop();
}
