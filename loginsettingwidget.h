#ifndef LOGINSETTINGWIDGET_H
#define LOGINSETTINGWIDGET_H

#include "util.h"
#include "appsettings.h"

#include <QLabel>
#include <QEvent>
#include <QDebug>
#include <QWidget>
#include <QLineEdit>
#include <QShowEvent>
#include <QValidator>
#include <QHideEvent>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

class LoginSettingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LoginSettingWidget(QWidget *parent = 0);
    void getSettings(QStringList &);

public slots:
    void	onOkButtonClicked();

private:
    void	initWidgets();
    void	translate();

private:
    QLabel *dest_addr_label;
    QLabel *dest_port_label;
    QLineEdit *dest_addr_edit;
    QLineEdit *dest_port_edit;
    QPushButton *ok_button;
    QPushButton *cancel_button;

signals:
    void	showLogin();
    void 	showMsg(Util::DispMsgId);

protected:
    virtual void showEvent(QShowEvent *);
    virtual void hideEvent(QHideEvent *);

};

#endif // LOGINSETTINGWIDGET_H
