#ifndef TITLEWIDGET_H
#define TITLEWIDGET_H

#include "common.h"
#include "logolabel.h"
#include "pushbutton.h"
#include "toolbutton.h"

#include <QFont>
#include <QList>
#include <QLabel>
#include <QPoint>
#include <QWidget>
#include <QPalette>
#include <QShowEvent>
#include <QStringList>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QSignalMapper>

class TitleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TitleWidget(QWidget *parent = 0);
    ~TitleWidget();
    void translate();

signals:
    void showMenu();
    void showMin();
    void closeMainWindow();
    void turnPage(int);

public slots:
    void selectPage(int);

protected slots:
    virtual void showEvent(QShowEvent *);
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);

private:
    bool mousePressed;
    QPoint mousePoint;
    void 	initWidgets();

private:
    QLabel *title_icon;
    QLabel *title_version;
    LogoLabel *logo_label;
    PushButton *close_button;
    PushButton *min_button;
    PushButton *menu_button;
    QSignalMapper *signal_mapper;
    QList<ToolButton *> tool_button_list;
};

#endif // TITLEWIDGET_H
