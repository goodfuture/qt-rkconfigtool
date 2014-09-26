#ifndef SWITCHER_H
#define SWITCHER_H

#include <QPixmap>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>

class Switcher : public QWidget
{
    Q_OBJECT
public:
    explicit Switcher(QWidget *parent = 0);

signals:
    void switcher(bool on);

public slots:
    void setSwitcher(bool on);

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

private:
    bool switch_on;
    bool mouse_pressed;
    QPixmap pix_on;
    QPixmap pix_off;

};

#endif // SWITCHER_H
