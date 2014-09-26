#ifndef PARAMSETTINGWIDGET_H
#define PARAMSETTINGWIDGET_H

#include "util.h"
#include "common.h"
#include "checkbox.h"
#include "switchbutton.h"
#include "viewcomconfig.h"
#include "viewdioconfig.h"
#include "viewnetconfig.h"
#include "dtuconfigwidget.h"
#include "viewbasisconfig.h"
#include "viewanalogconfig.h"
#include "viewserialconfig.h"

#include <QRect>
#include <QList>
#include <QLabel>
#include <QPainter>
#include <QPalette>
#include <QSplitter>
#include <QTabWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QSignalMapper>
#include <QLinearGradient>

class ParamSettingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ParamSettingWidget(QWidget *parent = 0);
    void	initWidgets();
    void	translate();

public slots:
    void	onLinkDrop();
    void 	onButtonClicked(int);
    void 	onMessageHandled(Util::MsgHandleFlag, Util::MsgHandleRst);
    void 	onRequestGetProtocolSet();

signals:
    void	userRequest(int);
    void 	resetDynamicProtocolSet();
    void	configChanged();

private:
    QPushButton 		*syncSettingButton;
    QPushButton		 	*saveAllSettingButton;
    QPushButton 		*syncCurrentSettingButton;
    QPushButton 		*saveCurrentSettingButton;
    QPushButton 		*factorySettingButton;
    QPushButton 		*rebootDeviceButton;
    QSignalMapper 		*signalMapper;
    QWidget 			*buttonLayoutWidget;
    QTabWidget			*tabWidget;
    QStringList 		tabNameList;
    ViewBasisConfig 	*viewBasisConfig;
    ViewComConfig		*viewComConfig;
    ViewNetConfig		*viewNetConfig;
    ViewAnalogConfig	*viewAnalogConfig;
    ViewSerialConfig	*viewSerialConfig;
    ViewDioConfig		*viewDioConfig;
    DtuConfigWidget		*dtuConfigWidget;

protected slots:
    virtual void paintEvent(QPaintEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
};

#endif // PARAMSETTINGWIDGET_H
