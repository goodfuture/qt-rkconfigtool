#ifndef MAINPAGEWIDGET_H
#define MAINPAGEWIDGET_H

#include "util.h"
#include "common.h"
#include "logolabel.h"
#include "dockwidget.h"
#include "roundbutton.h"
#include "versionlabel.h"
#include "firmwareupgradedialog.h"

#include <QFont>
#include <QRect>
#include <QDebug>
#include <QLabel>
#include <QImage>
#include <QScreen>
#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QTextEdit>
#include <QShowEvent>
#include <QPaintEvent>
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QGuiApplication>
#include <QLinearGradient>
#include <QGraphicsBlurEffect>

extern struct Context g_tContext;

class MainPageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainPageWidget(QWidget *parent = 0);
    ~MainPageWidget(){}
    void	translate();
    void	initWidgets();
    void	setBackgroundPixmap(QPixmap);

signals:
    void userRequest(int);
    void upgradeProgress(int);
    void requestGetFirmwareVersion(Util::FirmwareType);
    void requestUpgradeFirmware(Util::FirmwareType, QString);

public slots:
    void onLinkDrop();
    void onDockWidgetClicked(int);
    void onMessageHandled(Util::MsgHandleFlag, Util::MsgHandleRst);

private:
    QScreen			*screen;
    DockWidget 		*dockWidget;
    RoundButton 	*roundButton;
    VersionLabel 	*versionLabel;
    QLabel 			*productPicLabel;
    QPixmap 		backgroundPixmap;
    QLabel 			*productSpecifyLabel;
    FirmwareUpgradeDialog *firmwareUpgradeDialog;

protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void showEvent(QShowEvent *);
};

#endif // MAINPAGEWIDGET_H
