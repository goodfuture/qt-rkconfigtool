#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    :DropShadowWidget(parent)
{
#if 0
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(3000);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
#endif

    //setMouseTracking(true);
    this->setWindowFlags(this->windowFlags() | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    //setMinimumSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    this->setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    this->setWindowIcon(QIcon(":/icon/AppIcon"));
    this->setWindowTitle(tr("Title"));

    this->initWidgets();

    QHBoxLayout *center_layout = new QHBoxLayout();
    center_layout->addWidget(stacked_widget);
    center_layout->setSpacing(0);
    center_layout->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addWidget(title_widget);
    main_layout->addLayout(center_layout);
    main_layout->addWidget(status_bar);
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(SHADOW_WIDTH, SHADOW_WIDTH, SHADOW_WIDTH, SHADOW_WIDTH);

    setLayout(main_layout);
}

MainWindow::~MainWindow()
{
    emit quit();
}

void MainWindow::initWidgets()
{
    title_widget = new TitleWidget(this);
    connect(title_widget, SIGNAL(showMenu()), this, SLOT(showMenu()));
    connect(title_widget, SIGNAL(showMin()), this, SLOT(showMinimized()));
    connect(title_widget, SIGNAL(closeMainWindow()), this, SLOT(hide()));
    connect(title_widget, SIGNAL(turnPage(int)), this, SLOT(turnPage(int)));

    title_menu = new TitleMenu(this);
    connect(title_menu, SIGNAL(showSettingDialog()), this, SLOT(showSettingDialog()));
    connect(title_menu, SIGNAL(showAboutDialog()), this, SLOT(showAboutDialog()));

    stacked_widget = new QStackedWidget(this);
    /*
    QPalette palette;
    //palette.setBrush(QPalette::Window, QBrush(Qt::white));
    palette.setBrush(QPalette::Window, QBrush(QColor(250, 250, 250, 235)));
    stacked_widget->setPalette(palette);
    stacked_widget->setAutoFillBackground(true);
    */

    status_bar = new StatusBar(this);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(214, 225, 241));
    //palette.setColor(QPalette::Background, QColor(93, 131, 193, 255));
    //palette.setColor(QPalette::Foreground, QColor(255, 255, 255, 255));
    status_bar->setPalette(palette);

    login_dialog = new LoginDialog();
    connect(login_dialog, SIGNAL(login(QStringList)), this, SIGNAL(loginRequest(QStringList)));
    connect(this, SIGNAL(loginResult(int)), login_dialog, SLOT(onLoginResult(int)));

    about_dialog = new AboutDialog(this);

    system_tray = new SystemTray(this);
    connect(system_tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayIsActived(QSystemTrayIcon::ActivationReason)));
    connect(system_tray, SIGNAL(showMainWindow()), this, SLOT(showWindow()));
    connect(system_tray, SIGNAL(quit()), this, SIGNAL(quit()));

    main_page_widget = new MainPageWidget;
    stacked_widget->addWidget(main_page_widget);
    this->connect(main_page_widget, SIGNAL(requestUpgradeFirmware(Util::FirmwareType,QString)), SIGNAL(requestUpgradeFirmware(Util::FirmwareType, QString)));
    this->connect(main_page_widget, SIGNAL(requestGetFirmwareVersion(Util::FirmwareType)), SIGNAL(requestGetFirmwareVersion(Util::FirmwareType)));
    this->connect(main_page_widget, SIGNAL(userRequest(int)), SLOT(userRequestReceiver(int)));
    main_page_widget->connect(this, SIGNAL(upgradeProgress(int)), SIGNAL(upgradeProgress(int)));
    main_page_widget->connect(this, SIGNAL(linkDrop()), SLOT(onLinkDrop()));
    main_page_widget->connect(this, SIGNAL(messageHandled(Util::MsgHandleFlag,Util::MsgHandleRst)), SLOT(onMessageHandled(Util::MsgHandleFlag,Util::MsgHandleRst)));

    param_setting_widget = new ParamSettingWidget;
    stacked_widget->addWidget(param_setting_widget);
    this->connect(param_setting_widget, SIGNAL(userRequest(int)), SLOT(userRequestReceiver(int)));
    param_setting_widget->connect(this, SIGNAL(linkDrop()), SLOT(onLinkDrop()));
    param_setting_widget->connect(this, SIGNAL(messageHandled(Util::MsgHandleFlag,Util::MsgHandleRst)), SLOT(onMessageHandled(Util::MsgHandleFlag,Util::MsgHandleRst)));

    rtd_view_widget = new RtdViewWidget;
    stacked_widget->addWidget(rtd_view_widget);
    connect(this, SIGNAL(linkDrop()), rtd_view_widget, SLOT(onLinkDrop()));

    history_view_widget = new HistoryViewWidget;
    stacked_widget->addWidget(history_view_widget);
    connect(this, SIGNAL(linkDrop()), history_view_widget, SLOT(onLinkDrop()));

    data_export_widget = new DataExportWidget;
    stacked_widget->addWidget(data_export_widget);
    connect(this, SIGNAL(linkDrop()), data_export_widget, SLOT(onLinkDrop()));
}

void MainWindow::login()
{
    this->hide();
    system_tray->hide();
    login_dialog->showLoginWidget();
    switch (login_dialog->exec()) {
    case QDialog::Rejected:
        system_tray->deleteLater();
        this->close();
        exit(0);
        break;
    case QDialog::Accepted:
        this->show();
        break;
    default:
        break;
    }
}

void MainWindow::showMenu()
{
    //qDebug("Menu");
    QPoint p = rect().topRight();
    p.setX(p.x() - 97);
    p.setY(p.y() + 25);
    title_menu->exec(this->mapToGlobal(p));
}

void MainWindow::showSettingDialog()
{
}

void MainWindow::showAboutDialog()
{
    about_dialog->exec();
}

void MainWindow::showEvent(QShowEvent *event)
{
    //qDebug("show");
    //setMouseTracking(true);
    DropShadowWidget::showEvent(event);
}

void MainWindow::trayIsActived(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason) {
    case QSystemTrayIcon::DoubleClick:
        this->showWindow();
        break;
    case QSystemTrayIcon::Unknown:
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::Context:
    case QSystemTrayIcon::MiddleClick:
        break;
    }
}

void MainWindow::showWindow()
{
    this->showNormal();
    this->raise();
    this->activateWindow();
}

void MainWindow::turnPage(int page)
{
    switch(page) {
    case 0:
        stacked_widget->setCurrentWidget(main_page_widget);
        break;
    case 1:
        stacked_widget->setCurrentWidget(param_setting_widget);
        break;
    case 2:
        stacked_widget->setCurrentWidget(rtd_view_widget);
        break;
    case 3:
        stacked_widget->setCurrentWidget(history_view_widget);
        break;
    case 4:
        stacked_widget->setCurrentWidget(data_export_widget);
        break;
    default:
        break;
    }
}

void MainWindow::userRequestReceiver(int requestId)
{
    //qDebug() << requestId;
    //status_bar->showMessage(tr("Sending Request!"));
    emit userRequest(requestId);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    DropShadowWidget::paintEvent(event);
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));

    QRect rect(SHADOW_WIDTH, SHADOW_WIDTH, this->width() - 2 * SHADOW_WIDTH, this->height() - 2 * SHADOW_WIDTH);
    painter.drawPixmap(rect, QPixmap(":/skin/24_big"));

    int pos_y = title_widget->pos().y() + title_widget->height();
    painter.fillRect(QRect(SHADOW_WIDTH, pos_y, this->width() - 2 * SHADOW_WIDTH, this->height() - pos_y - SHADOW_WIDTH), QColor(250, 250, 250, 160));

    painter.setPen(QColor(17, 95, 141));
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(SHADOW_WIDTH - 1, SHADOW_WIDTH, this->width() - 2 * SHADOW_WIDTH + 1, this->height() - 2 * SHADOW_WIDTH);
}

void MainWindow::onMessageHandled(Util::MsgHandleFlag type, Util::MsgHandleRst result)
{
    if (type == Util::LoginFlag) {
        if (result == Util::LoginSuccessRst) {
            system_tray->show();
        } else {
            system_tray->hide();
        }
        emit loginResult(result);
        return;
    } else if (type == Util::ConnectFlag) {
        if (result == Util::ConnectSuccessRst) {
            status_bar->showLinkOn();
        } else if (result == Util::ConnectFailedRst && this->isVisible()) {
            status_bar->showLinkOff();
            emit linkDrop();
            QMessageBox msgBox;
            msgBox.setText(tr("Detected Link Dropped, Please Relogin!"));
            msgBox.exec();
            login();
        }
        emit loginResult(result);
        return;
    } else if (type == Util::MessageFlag) {
        if (result == Util::MessageSendingSuccessRst) {
            status_bar->showMessage(tr("Sending Message Success!"));
        } else if (result == Util::MessageSendingFailedRst) {
            status_bar->showMessage(tr("Sending Message Failed!"));
        } else if (result == Util::MessageRecvingSuccessRst) {
            status_bar->showMessage(tr("Receiving Message Success!"));
        } else if (result == Util::MessageRecvingFailedRst) {
            status_bar->showMessage(tr("Receiving Message Failed!"));
        }
        return;
    } else if (type == Util::GetConfigFlag) {
        if (result == Util::GetConfigFlagSuccessRst) {
            status_bar->showMessage(tr("Get Configuration Success!"));
        } else if (result == Util::GetConfigFlagFailedRst) {
            status_bar->showMessage(tr("Get Configuration Failed!"));
        }
    } else if (type == Util::PutConfigFlag) {
        if (result == Util::PutConfigFlagSuccessRst) {
            status_bar->showMessage(tr("Put Configuration Success!"));
        } else if (result == Util::PutConfigFlagFailedRst) {
            status_bar->showMessage(tr("Put Configuration Failed!"));
        }
    } else if (type == Util::RebootDeviceFlag) {
        if (result == Util::RebootDeviceSuccessRst) {
            status_bar->showMessage(tr("Reboot Device Success!"));
        } else if (result == Util::RebootDeviceFailedRst) {
            status_bar->showMessage(tr("Reboot Device Failed!"));
        }
    } else if (type == Util::GetFirmwareVersionFlag) {
        if (result == Util::GetFirmwareVersionSuccessRst) {
            status_bar->showMessage(tr("Get Firmware Version Success!"));
        } else if (result == Util::GetFirmwareVersionFailedRst) {
            status_bar->showMessage(tr("Get Firmware Version Failed!"));
        }
    } else if (type == Util::GetSupportedProtocolFlag) {
        if (result == Util::GetSupportedProtocolSuccessRst) {
            status_bar->showMessage(tr("Get Dynamic Protocol Success!"));
        } else if (result == Util::GetSupportedProtocolFailedRst) {
            status_bar->showMessage(tr("Get Dynamic Protocol Failed!"));
        }
    }

    emit messageHandled(type, result);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()) {
    case Qt::Key_Escape:
        emit quit();
        break;
    default:
        DropShadowWidget::keyPressEvent(event);
    }
}
