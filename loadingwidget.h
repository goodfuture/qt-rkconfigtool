#ifndef LOADINGWIDGET_H
#define LOADINGWIDGET_H

#include "util.h"

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QPixmap>
#include <QSettings>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

class LoadingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LoadingWidget(QWidget *parent = 0);

private:
    void	initWidgets();
    void	translate();

private:
    int 	index;
    QLabel 	*loading_label;
    QLabel 	*prompt_label;
    QTimer 	*timer;
    QPushButton *cancel_button;

signals:
    void	cancel();
    void	showMsg(Util::DispMsgId);

public slots:
    void	updatePixmap();
    void	start();
    void	stop();
};

#endif // LOADINGWIDGET_H
