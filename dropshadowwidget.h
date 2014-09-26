#ifndef DROPSHADOWWIDGET_H
#define DROPSHADOWWIDGET_H

#include <QDebug>
#include <qmath.h>
#include <QDialog>
#include <QPainter>
#include <QKeyEvent>
#include <QMouseEvent>

class DropShadowWidget : public QDialog
{
    Q_OBJECT
    
public:
    DropShadowWidget(QWidget *parent = 0);
    ~DropShadowWidget();
    void setDropEnabled(bool);
    void setDropDisabled(bool);

protected:
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
    virtual void paintEvent(QPaintEvent *);
    virtual void keyPressEvent(QKeyEvent *);
    virtual void keyReleaseEvent(QKeyEvent *);
    virtual void reject();

private:
    bool mousePressed;
    bool dropEnabled;
    QPoint mousePoint;
};

#endif // DROPSHADOWWIDGET_H
