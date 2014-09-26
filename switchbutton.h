#ifndef SWITCHBUTTON_H
#define SWITCHBUTTON_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPixmap>

class SwitchButton : public QWidget
{
    Q_OBJECT
public:
    explicit SwitchButton(QWidget *parent = 0);

signals:
    void switched(bool on);

public slots:
    void setSwitch(bool on);

protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);

private:
    bool  switch_on;
    bool  mouse_pressed;
    QPixmap pixmap_bg;
    QPixmap pixmap_fg_on;
    QPixmap pixmap_fg_off;
};

#endif // SWITCHBUTTON_H
