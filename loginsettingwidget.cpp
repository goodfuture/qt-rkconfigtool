#include "loginsettingwidget.h"

LoginSettingWidget::LoginSettingWidget(QWidget *parent) :
    QWidget(parent)
{
    this->initWidgets();
    this->translate();

    QGridLayout *grid_layout = new QGridLayout();
    grid_layout->setSpacing(10);
    grid_layout->setContentsMargins(10, 10, 10, 10);
    grid_layout->setColumnStretch(0, 1);
    grid_layout->setRowStretch(0, 1);
    grid_layout->addWidget(dest_addr_label, 1, 1);
    grid_layout->addWidget(dest_addr_edit, 1, 2);
    grid_layout->addWidget(dest_port_label, 2, 1);
    grid_layout->addWidget(dest_port_edit, 2, 2);
    grid_layout->setColumnStretch(3, 1);
    grid_layout->setRowStretch(3, 1);

    QHBoxLayout *button_layout = new QHBoxLayout();
    button_layout->setAlignment(Qt::AlignCenter);
    button_layout->setSpacing(10);
    button_layout->setContentsMargins(10, 0, 10, 0);
    button_layout->addWidget(ok_button);
    button_layout->addWidget(cancel_button);

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addSpacing(10);
    main_layout->addLayout(grid_layout);
    main_layout->addLayout(button_layout);
    main_layout->addStretch();

    this->setLayout(main_layout);
}

void LoginSettingWidget::initWidgets()
{
    dest_addr_label = new QLabel();
    dest_port_label = new QLabel();
    dest_addr_edit = new QLineEdit();
    dest_port_edit = new QLineEdit();

    dest_addr_edit->setAlignment(Qt::AlignLeft);
    dest_port_edit->setAlignment(Qt::AlignLeft);

    dest_addr_edit->setFixedWidth(120);
    dest_port_edit->setFixedWidth(120);

    dest_addr_edit->setPlaceholderText(tr("Enter Target Device IP Address"));
    dest_port_edit->setPlaceholderText(tr("Enter Target Port Number"));

    QString ip_regexp("([1-9]|[1-9]\\d|1\\d{2}|2[0-4]\\d|25[0-5])(\\.(\\d|[1-9]\\d|1\\d{2}|2[0-4]\\d|25[0-5])){3}");
    QValidator *ip_validator = new QRegExpValidator(QRegExp(ip_regexp));
    dest_addr_edit->setValidator(ip_validator);

    QString port_regexp("^[1-9]$|(^[1-9][0-9]$)|(^[1-9][0-9][0-9]$)|(^[1-9][0-9][0-9][0-9]$)|(^[1-6][0-5][0-5][0-3][0-5]$)");
    QValidator *port_validator = new QRegExpValidator(QRegExp(port_regexp));
    dest_port_edit->setValidator(port_validator);

    ok_button = new QPushButton();
    cancel_button = new QPushButton();
    //cancel_button->setDefault(true);

    connect(ok_button, SIGNAL(clicked()), this, SLOT(onOkButtonClicked()));
    connect(cancel_button, SIGNAL(clicked()), this, SIGNAL(showLogin()));
}

void LoginSettingWidget::translate()
{
    dest_addr_label->setText(QString(tr("Address")) + ":");
    dest_port_label->setText(QString(tr("Port")) + ":");
    ok_button->setText(tr("Ok"));
    cancel_button->setText(tr("Cancel"));
}

void LoginSettingWidget::onOkButtonClicked()
{
    QString ip_addr = dest_addr_edit->text();
    QString port = dest_port_edit->text();

    if(ip_addr.isEmpty() || port.isEmpty()) {
        emit showMsg(Util::EmptyTargetAddrOrPortMsg);
    } else {
        AppSettings settings;
        settings.beginGroup(QString(APP_PARAM_GROUP_TARGET));
        settings.setValue(QString(APP_PARAM_ADDR), ip_addr);
        settings.setValue(QString(APP_PARAM_PORT), port);
        settings.endGroup();
        emit showLogin();
    }
}

void LoginSettingWidget::getSettings(QStringList &settings)
{
    settings << dest_addr_edit->text()
             << dest_port_edit->text();
}

void LoginSettingWidget::showEvent(QShowEvent *event)
{
    AppSettings settings;
    settings.beginGroup(QString(APP_PARAM_GROUP_TARGET));
    dest_addr_edit->setText(settings.value(QString(APP_PARAM_ADDR), QString(DEFAULT_TARGET_ADDR)).toString());
    dest_port_edit->setText(settings.value(QString(APP_PARAM_PORT), QString(DEFAULT_TARGET_PORT)).toString());
    settings.endGroup();

    ok_button->setFocus();
    QWidget::showEvent(event);
}

void LoginSettingWidget::hideEvent(QHideEvent *event)
{
    //emit showMsg(Util::None);
    QWidget::hideEvent(event);
}
