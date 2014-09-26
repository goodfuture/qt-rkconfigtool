#include "dtuconfigwidget.h"

DtuConfigWidget::DtuConfigWidget(QWidget *parent) :
    QWidget(parent)
{
    this->initWidgets();
    this->translate();
    this->setAutoFillBackground(true);

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(250, 250, 255));
    this->setPalette(palette);

    stackedLayout = new QStackedLayout;
    stackedLayout->addWidget(loginWidget);
    stackedLayout->addWidget(viewDtuConfig);
    stackedLayout->setCurrentWidget(loginWidget);
    this->setLayout(stackedLayout);
}

void DtuConfigWidget::initWidgets()
{
    loginWidget = new DtuLoginWidget;
    viewDtuConfig = new ViewDtuConfig;

    this->connect(loginWidget, SIGNAL(login()), SLOT(onLogin()));
}

void DtuConfigWidget::translate()
{
}

void DtuConfigWidget::onLogin()
{
    stackedLayout->setCurrentWidget(viewDtuConfig);
}
