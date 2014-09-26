#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include "util.h"
#include "appsettings.h"

#include <QDebug>
#include <QLabel>
#include <QWidget>
#include <QLineEdit>
#include <QShowEvent>
#include <QHideEvent>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

class LoginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LoginWidget(QWidget *parent = 0);

signals:
    void	login(QString &user, QString &passwd);
    void 	showMsg(Util::DispMsgId);

public slots:
    void 	onLoginButtonClicked();

private:
    void	initWidgets();
    void	translate();

private:
    QLineEdit *user_name_edit;
    QLineEdit *password_edit;
    QPushButton *login_button;
    QLabel *copyright_label;

protected:
    virtual void showEvent(QShowEvent *);
    virtual void hideEvent(QHideEvent *);

};

#endif // LOGINWIDGET_H
