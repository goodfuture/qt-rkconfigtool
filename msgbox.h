#ifndef MSGBOX_H
#define MSGBOX_H

#include <QFont>
#include <QLabel>
#include <QPoint>
#include <QBitmap>
#include <QDialog>
#include <QString>
#include <QCheckBox>
#include <QPushButton>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QSignalMapper>

#include "checkbox.h"
#include "pushbutton.h"

class MsgBox : public QDialog
{
    Q_OBJECT
public:
    explicit MsgBox(QWidget *parent = 0);
    int	showTipMessage(QString title, QString message, bool checkbox = false, bool cancel_button = true);
    int	showWarningMessage(QString title, QString message, bool checkbox = false, bool cancel_button = true);
    int	showErrorMessage(QString title, QString message, bool checkbox = false, bool cancel_button = true);

signals:
    void msgChecked(bool, bool);
    void okMessageHidden(bool);

public slots:
    void 	onButtonClicked(int);
    void 	translate();

private:
    bool mouse_press;
    QPoint	move_point;
    PushButton *close_button;
    QLabel	*title_label;
    QLabel	*tip_pic_label;
    QLabel	*message_label;
    QCheckBox *check_box;
    QPushButton *cancel_button;
    QPushButton *ok_button;
    QSignalMapper *signal_mapper;

protected slots:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
};

#endif // MSGBOX_H
