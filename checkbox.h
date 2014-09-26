#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <QPixmap>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>

class CheckBox : public QWidget
{
    Q_OBJECT
public:
    explicit CheckBox(QWidget *parent = 0);

signals:
    void checked(bool);

public slots:
    void setCheck(bool);

protected:
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void enterEvent(QEvent *);
    virtual void leaveEvent(QEvent *);
    virtual void paintEvent(QPaintEvent *);

private:
    bool mouse_press;
    enum ButtonStatus { NORMAL, ENTER, PRESS, NOSTATUS};
    ButtonStatus status;
    bool is_checked;

};

#endif // CHECKBOX_H
