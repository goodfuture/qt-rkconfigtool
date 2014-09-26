#include "dtuloginwidget.h"

DtuLoginWidget::DtuLoginWidget(QWidget *parent) :
    QWidget(parent)
{
    this->initWidgets();
    this->translate();

    QGridLayout *gridLayout = new QGridLayout(this);
    gridLayout->setColumnStretch(0, 1);
    gridLayout->setRowStretch(0, 1);
    gridLayout->addWidget(userNameLabel, 1, 1);
    gridLayout->addWidget(userNameEdit, 1, 2);
    gridLayout->addWidget(passwdLabel, 2, 1);
    gridLayout->addWidget(passwdLineEdit, 2, 2);
    gridLayout->addWidget(loginButton, 3, 1, 1, 2);
    gridLayout->setColumnStretch(3, 1);
    gridLayout->setRowStretch(4, 1);
}

void DtuLoginWidget::initWidgets()
{
    userNameLabel = new QLabel;
    userNameEdit = new QComboBox;

    passwdLabel = new QLabel;
    passwdLineEdit = new QLineEdit;
    passwdLineEdit->setEchoMode(QLineEdit::Password);
    passwdLineEdit->setMaxLength(6);
    loginButton = new QPushButton;

    this->connect(loginButton, SIGNAL(clicked()), SLOT(onButtonClicked()));
}

void DtuLoginWidget::translate()
{
    userNameLabel->setText(tr("User Select:"));
    passwdLabel->setText(tr("Password:"));

    userNameEdit->addItem(tr("Guest"));
    userNameEdit->addItem(tr("Administrator"));
    userNameEdit->setCurrentIndex(0);

    loginButton->setText(tr("Login"));
}

void DtuLoginWidget::onButtonClicked()
{
    emit login();
}
