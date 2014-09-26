#ifndef PROMPTWIDGET_H
#define PROMPTWIDGET_H

#include <QWidget>
#include <QToolButton>
#include <QLabel>
#include <QStyle>

#include "common.h"

class PromptWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PromptWidget(QWidget *parent = 0);

private:
    void initSetting();
    void initWidgets();

private:
    int widget_width;
    int widget_height;
    QToolButton *close_button;
    QLabel *icon_label;
    QLabel *msg_label;

signals:

public slots:
    void closeWidget();
    void setTipInfo(QString);
    void setTipIcon(QPixmap);
    void showTip(QString, QPixmap);

};

#endif // PROMPTWIDGET_H
