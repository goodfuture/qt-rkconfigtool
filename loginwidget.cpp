#include "loginwidget.h"

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent)
{
    this->initWidgets();
    this->translate();

    QVBoxLayout *widget_layout = new QVBoxLayout();
    widget_layout->setSpacing(10);
    widget_layout->setContentsMargins(10, 10, 10, 10);
    widget_layout->addWidget(user_name_edit);
    widget_layout->addWidget(password_edit);
    widget_layout->addWidget(login_button);
    widget_layout->addSpacing(15);
    widget_layout->addWidget(copyright_label);

    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addStretch();
    main_layout->addLayout(widget_layout);
    main_layout->addStretch();

    this->setLayout(main_layout);
}

void LoginWidget::initWidgets()
{
    user_name_edit = new QLineEdit();
    password_edit = new QLineEdit();

    user_name_edit->setMaxLength(8);
    password_edit->setMaxLength(8);

    user_name_edit->setAlignment(Qt::AlignLeft);
    password_edit->setAlignment(Qt::AlignLeft);
    password_edit->setEchoMode(QLineEdit::Password);

    login_button = new QPushButton();
    /*
    login_button->setShortcut(Qt::Key_Enter);
    login_button->setShortcut(Qt::Key_Return);
    */
    login_button->setDefault(true);

    copyright_label = new QLabel();
    copyright_label->setStyleSheet(QString("color:gray"));

    connect(login_button, SIGNAL(clicked()), this, SLOT(onLoginButtonClicked()));
}

void LoginWidget::translate()
{
    user_name_edit->setPlaceholderText(tr("User Name"));
    password_edit->setPlaceholderText(tr("Password"));
    login_button->setText(tr("Login"));
    copyright_label->setText(tr("CopyRight"));
}

void LoginWidget::onLoginButtonClicked()
{
    QString user_name = user_name_edit->text();
    QString password = password_edit->text();

    if (user_name.isEmpty() || password.isEmpty()) {
        emit showMsg(Util::EmptyUserOrPasswordMsg);
    } else {
        //qDebug() << user_name << password;
        emit login(user_name, password);
    }
}

void LoginWidget::showEvent(QShowEvent *event)
{
    emit showMsg(Util::NoneMsg);
    login_button->setFocus();
    QWidget::showEvent(event);
}

void LoginWidget::hideEvent(QHideEvent *event)
{
    emit showMsg(Util::NoneMsg);
    QWidget::hideEvent(event);
}
