#ifndef STATUSBAR_H
#define STATUSBAR_H

#include "common.h"

#include <QLabel>
#include <QPixmap>
#include <QWidget>
#include <QPainter>
#include <QTimerEvent>
#include <QPaintEvent>
#include <QLinearGradient>

class StatusBar : public QWidget
{
    Q_OBJECT
public:
    explicit StatusBar(QWidget *parent = 0);

private:
    int 	msg_timer;
    int 	link_on_timer; //link on timer
    long	link_on_counter;
    QLabel *message_label;
    QLabel *copyright_label;
    QLabel *link_status_icon;
    QLabel *link_status_text;
    QLabel *link_timer_label;

signals:

public slots:
    void showMessage(const QString &, int timeout = 1500);
    void clearMessage();
    void showLinkOn(bool value = true);
    void showLinkOff(bool value = true);

protected slots:
    void timerEvent(QTimerEvent *);
    void paintEvent(QPaintEvent *);
};

#endif // STATUSBAR_H
