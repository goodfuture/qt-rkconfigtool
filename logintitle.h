#ifndef LOGINTITLE_H
#define LOGINTITLE_H

#include "common.h"
#include "pushbutton.h"
#include "logolabel.h"

#include <QPoint>
#include <QLabel>
#include <QPixmap>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QMouseEvent>
#include <QGraphicsDropShadowEffect>

class LoginTitle : public QWidget
{
    Q_OBJECT
public:
    explicit LoginTitle(QWidget *parent = 0);
    void 	initWidgets();
    void	translate();
    void	setTitle(QString, bool hidden = false, bool is_white = true);
    void	setIconHidden(bool);
    void	setSettingHidden(bool);

signals:
    void	showSettingWidget();
    void	showMin();
    void	closeWidget();

public slots:

protected:
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
    virtual void paintEvent(QPaintEvent *);

private:

private:
    QLabel *icon_label;
    QLabel *title_label;
    PushButton *setting_button;
    PushButton *minimum_button;
    PushButton *close_button;
    QLabel *logo_label;
    QLabel *zh_tool_label;
    QLabel *en_tool_label;
};

#endif // LOGINTITLE_H
