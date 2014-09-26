#ifndef ROUNDBUTTON_H
#define ROUNDBUTTON_H

#include <QLabel>
#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainterPath>
#include <QLinearGradient>
#include <QRadialGradient>
#include <QGraphicsEffect>
#include <QGraphicsDropShadowEffect>

class RoundButton : public QWidget
{
    Q_OBJECT
public:
    explicit RoundButton(QWidget *parent = 0);

signals:

public slots:

protected:
    virtual void paintEvent(QPaintEvent *);
};

#endif // ROUNDBUTTON_H
