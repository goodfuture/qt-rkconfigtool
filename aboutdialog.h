#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include "dropshadowwidget.h"
#include "pushbutton.h"
#include "common.h"
#include <QLabel>
#include <QPushButton>
#include <QPaintEvent>
#include <QPixmap>
#include <QHBoxLayout>
#include <QVBoxLayout>

class AboutDialog : public DropShadowWidget
{
    Q_OBJECT
public:
    explicit AboutDialog(QWidget *parent = 0);

private:
    void initWidgets();
    void translate();

private:
    QLabel *title_icon_label;
    QLabel *title_label;
    QLabel *logo_label;
    QLabel *head_company_label;
    QLabel *head_company_addr_label;
    QLabel *manufacture_company_label;
    QLabel *manufacture_company_addr_label;
    QLabel *copyright_label;
    PushButton *close_button;
    QPushButton *ok_button;

protected slots:
    virtual void paintEvent(QPaintEvent *);

signals:

public slots:

};

#endif // ABOUTDIALOG_H
