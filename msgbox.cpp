#include "msgbox.h"

MsgBox::MsgBox(QWidget *parent) :
    QDialog(parent)
{
    //this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    this->resize(320, 160);

    int width = this->width();
    int height = this->height();

    mouse_press = false;

    close_button = new PushButton(this);
    close_button->setPicName(QString(":/title_button/close"));
    close_button->setGeometry(width - 30, 0, 30, 30);

    title_label = new QLabel(this);
    QFont font = title_label->font();
    font.setBold(true);
    title_label->setFont(font);
    title_label->setGeometry(0, 0, width - 50, 30);

    tip_pic_label = new QLabel(this);
    tip_pic_label->setGeometry(20, 50, 36, 36);
    tip_pic_label->setScaledContents(true);

    message_label = new QLabel(this);
    message_label->setGeometry(65, 60, width - 100, 25 * 2);
    message_label->setWordWrap(true);
    message_label->setAlignment(Qt::AlignTop);

    check_box = new QCheckBox(this);
    check_box->setGeometry(10, height - 35, 160, 25);
    check_box->setHidden(true);

    QPushButton *cancel_button = new QPushButton(this);
    cancel_button->resize(70, 25);
    cancel_button->move(width - cancel_button->width() - 10, height - 35);

    QPushButton *ok_button = new QPushButton(this);
    ok_button->resize(70, 25);
    ok_button->move(width - ok_button->width() - cancel_button->width() - 20, height - 35);

#if 0
    signal_mapper = new QSignalMapper(this);
    signal_mapper->connect(close_button, SIGNAL(clicked()), SLOT(map()));
    signal_mapper->connect(cancel_button, SIGNAL(clicked()), SLOT(map()));
    signal_mapper->connect(ok_button, SIGNAL(clicked()), SLOT(map()));
    signal_mapper->setMapping(close_button, 0);
    signal_mapper->setMapping(ok_button, 1);
    signal_mapper->setMapping(cancel_button, 2);
    this->connect(signal_mapper, SIGNAL(mapped(int)), SLOT(onButtonClicked(int)));

    this->translate();
#endif
}

void MsgBox::translate()
{
    close_button->setToolTip(tr("Close"));
    check_box->setText(tr("Remeber"));
    ok_button->setText(tr("Ok"));
    cancel_button->setText(tr("Cancel"));
}

int MsgBox::showTipMessage(QString title, QString message, bool checkBox, bool cancelButton)
{
    title_label->setText(QString("  ") + title);
    message_label->setText(message);
    tip_pic_label->setPixmap(QString(":/message_box/information"));
    check_box->setChecked(false);
    check_box->setHidden(checkBox);
    cancel_button->setHidden(cancelButton);
    if (cancelButton) {
        cancel_button->setFocus();
    } else {
        ok_button->setFocus();
    }
    return this->exec();
}

int MsgBox::showWarningMessage(QString title, QString message, bool checkBox, bool cancelButton)
{
    title_label->setText(QString("  ") + title);
    message_label->setText(message);
    tip_pic_label->setPixmap(QString(":/message_box/warning"));
    check_box->setChecked(false);
    check_box->setHidden(checkBox);
    cancel_button->setHidden(cancelButton);
    if (cancelButton) {
        cancel_button->setFocus();
    } else {
        ok_button->setFocus();
    }
    return this->exec();
}

int MsgBox::showErrorMessage(QString title, QString message, bool checkBox, bool cancelButton)
{
    title_label->setText(QString("  ") + title);
    message_label->setText(message);
    tip_pic_label->setPixmap(QString(":/message_box/error"));
    check_box->setChecked(false);
    check_box->setHidden(checkBox);
    cancel_button->setHidden(cancelButton);
    if (cancelButton) {
        cancel_button->setFocus();
    } else {
        ok_button->setFocus();
    }
    return this->exec();
}

void MsgBox::onButtonClicked(int button_id)
{
    switch(button_id) {
    case 1: {//Ok
        bool is_hidden = check_box->isHidden();
        if(!is_hidden) {
            bool is_checked = check_box->isChecked();
            emit msgChecked(is_checked, true);
        }
        this->accept();
        break;
    }
    case 0: //Close
    case 2: {//Cancel
        bool is_check_hidden = check_box->isHidden();
        bool is_ok_hidden = ok_button->isHidden();
        if(!is_check_hidden) {
            bool is_checked = check_box->isChecked();
            if(!is_ok_hidden) {
                emit msgChecked(is_checked, false);
            } else {
                emit okMessageHidden(is_checked);
            }
        }
        this->reject();
        break;
    }
    default:
        break;
    }
}

void MsgBox::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(rect(), QPixmap(":/icon/tip"));
    QBitmap bitmap(this->size());
    QPainter painter2(&bitmap);
    painter2.fillRect(bitmap.rect(), Qt::white);
    painter2.setBrush(QColor(0, 0, 0));
    painter2.drawRoundedRect(rect(), 4, 4);
    setMask(bitmap);
}

void MsgBox::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        mouse_press = true;
    }
    move_point = event->globalPos() - pos();
}

void MsgBox::mouseReleaseEvent(QMouseEvent *)
{
    mouse_press = false;
}

void MsgBox::mouseMoveEvent(QMouseEvent *event)
{
    if(mouse_press) {
        QPoint move_pos = event->globalPos();
        move(move_pos - move_point);
    }
}
