#ifndef LOGOLABEL_H
#define LOGOLABEL_H

#include <QRect>
#include <QDebug>
#include <QEvent>
#include <QLabel>
#include <QBrush>
#include <QPoint>
#include <QColor>
#include <QPixmap>
#include <QWidget>
#include <QPainter>
#include <QTimerEvent>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QLinearGradient>

class LogoLabel : public QWidget
{
    Q_OBJECT
public:
    explicit LogoLabel(QWidget *parent = 0);
    ~LogoLabel() {}

signals:

public slots:

protected:
    virtual void enterEvent(QEvent *);
    virtual	void leaveEvent(QEvent *);
    virtual void paintEvent(QPaintEvent *);
    virtual void timerEvent(QTimerEvent *);

private:
    bool	mouseIn;
    float	flashRatio;
    int		flashTimer;
    int		cycleTimer;
    int		flashInterval;
    int		cycleInterval;
};

#endif // LOGOLABEL_H
