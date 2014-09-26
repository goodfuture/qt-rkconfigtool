#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <QPushButton>
#include <QMouseEvent>
#include <QPainter>

class PushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit PushButton(QWidget *parent = 0);
    ~PushButton();
    void setPicName(QString);

signals:
    //void clicked();

public slots:

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *e);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void paintEvent(QPaintEvent *);

private:
    enum Button_Status {NORMAL, ENTER, PRESS, NOSTATUS};
    Button_Status status;
    QString pic_name;
    bool mouse_press;

};

#endif // PUSHBUTTON_H
