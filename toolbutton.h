#ifndef TOOLBUTTON_H
#define TOOLBUTTON_H

#include <QPixmap>
#include <QPalette>
#include <QPainter>
#include <QMouseEvent>
#include <QToolButton>
#include <QLinearGradient>

class ToolButton : public QToolButton
{
    Q_OBJECT
public:
    explicit ToolButton(QString name, QWidget *parent = 0);
    void setMousePressed(bool);

signals:

public slots:

protected:
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

private:
    bool mouse_pressed;
    bool mouse_over;

private:
    void painterInfo(int top_color, int middle_color, int bottom_color);
};

#endif // TOOLBUTTON_H
