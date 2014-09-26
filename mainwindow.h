#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "common.h"
#include "titlemenu.h"
#include "statusbar.h"
#include "msgbox.h"
#include "systemtray.h"
#include "logindialog.h"
#include "titlewidget.h"
#include "aboutdialog.h"
#include "rtdviewwidget.h"
#include "mainpagewidget.h"
#include "dataexportwidget.h"
#include "dropshadowwidget.h"
#include "historyviewwidget.h"
#include "paramsettingwidget.h"

#include <QIcon>
#include <QDebug>
#include <QPalette>
#include <QPainter>
#include <QPalette>
#include <QKeyEvent>
#include <QShowEvent>
#include <QStringList>
#include <QMessageBox>
#include <QPaintEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QPropertyAnimation>

class MainWindow : public DropShadowWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    virtual void showEvent(QShowEvent *);
    virtual void paintEvent(QPaintEvent *);

private:
    void	initWidgets();

private:
    TitleMenu			*title_menu;
    StatusBar			*status_bar;
    SystemTray			*system_tray;
    TitleWidget 		*title_widget;
    LoginDialog			*login_dialog;
    AboutDialog			*about_dialog;
    QStackedWidget		*stacked_widget;
    RtdViewWidget 		*rtd_view_widget;
    MainPageWidget		*main_page_widget;
    DataExportWidget	*data_export_widget;
    HistoryViewWidget 	*history_view_widget;
    ParamSettingWidget	*param_setting_widget;

signals:
    void	quit();
    void	linkDrop();
    void 	loginResult(int);
    void	userRequest(int);
    void	upgradeProgress(int);
    void 	loginRequest(QStringList);
    void 	requestGetFirmwareVersion(Util::FirmwareType);
    void 	requestUpgradeFirmware(Util::FirmwareType, QString);
    void 	messageHandled(Util::MsgHandleFlag, Util::MsgHandleRst);

public slots:
    void 	login();
    void 	showMenu();
    void	showWindow();
    void	turnPage(int);
    void	showAboutDialog();
    void 	showSettingDialog();
    void 	userRequestReceiver(int);
    void	keyPressEvent(QKeyEvent *);
    void	trayIsActived(QSystemTrayIcon::ActivationReason);
    void 	onMessageHandled(Util::MsgHandleFlag, Util::MsgHandleRst);
};

#endif // MAINWINDOW_H
