#ifndef DOCKITEMWIDGET_H
#define DOCKITEMWIDGET_H

#include <QSize>
#include <QFont>
#include <QRect>
#include <QDebug>
#include <QLabel>
#include <QTimer>
#include <QImage>
#include <QPoint>
#include <QString>
#include <QPixmap>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QResizeEvent>
#include <qmath.h>

class DockItemWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DockItemWidget(QWidget *parent = 0, QPixmap &icon = QPixmap(), QString &tip = QString());
    ~DockItemWidget();

public:
    void setDefaultIconSize(QSize &);
    void resize();
    QPixmap createMirrorIcon(QPixmap &icon);

signals:
    void	clicked();

public slots:

protected:
    void	initIconPosAndSize();
    void 	initTipStringRect();
    void	initJumping();

protected slots:
    void onJumpTimerTimeout();
    virtual void enterEvent(QEvent *);
    virtual void leaveEvent(QEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void paintEvent(QPaintEvent *);
    virtual void resizeEvent(QResizeEvent *);

private:
    bool	mouseIn;
    bool	mousePressed;
    bool	jumping;
    int		jumpOffset;
    float	jumpOffsetFactor;
    int		jumpTicks;
    int		jumpTicksWhenTop;
    int 	jumpCount;
    int		jumpMaxCount;
    QPoint	basePoint;
    QPixmap	normalIcon;
    QRect	normalIconRect;
    QPixmap mirrorIcon;
    QRect	mirrorIconRect;
    QString	tipString;
    QRect	tipStringRect;
    QTimer 	*jumpTimer;
    float	iconMaxScaleFactor;
    float	iconScaleFactor;
    QSize	defaultIconSize;
};

#endif // DOCKITEMWIDGET_H
