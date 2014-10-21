#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include "util.h"
#include "common.h"
#include "logintitle.h"
#include "appsettings.h"
#include "loginwidget.h"
#include "promptwidget.h"
#include "loadingwidget.h"
#include "dropshadowwidget.h"
#include "loginsettingwidget.h"

#include <QPen>
#include <QRect>
#include <QDebug>
#include <QImage>
#include <QDialog>
#include <QPainter>
#include <QSettings>
#include <QCloseEvent>
#include <QPaintEvent>
#include <QApplication>
#include <QPainterPath>
#include <QStackedLayout>
#include <QLinearGradient>
#include <QPropertyAnimation>

class LoginDialog : public DropShadowWidget
{
    Q_OBJECT
public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

private:
    void	initWidgets();
    void	translate();

signals:
    void 	login(QStringList);
    void 	quit();

public slots:
    void showSettingWidget();
    void showLoginWidget();
    void showLoadingWidget();
    void showMin();
    void login(QString &, QString &);
    void abortLogin();
    void showMsg(Util::DispMsgId);
    void showError(QString);
    void showWarning(QString);
    //void msgHandleRst(Util::MsgHandleFlag, Util::MsgHandleRst);
    void onLoginResult(int);

protected:
    virtual void paintEvent(QPaintEvent *);
    virtual	void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
    virtual void closeEvent(QCloseEvent *);

private:
    bool mouse_pressed;
    QPoint	pressed_point;

private:
    LoginTitle *title;
    LoginWidget *login_widget;
    LoginSettingWidget *setting_widget;
    LoadingWidget	*loading_widget;
    QStackedLayout *stack_layout;
    PromptWidget *prompt_widget;

};

#endif // LOGINDIALOG_H
