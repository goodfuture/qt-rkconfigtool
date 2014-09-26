#include "toolbutton.h"
#include "common.h"

ToolButton::ToolButton(QString pic_name, QWidget *parent) :
    QToolButton(parent)
{
    QPalette text_palette = palette();
    text_palette.setColor(QPalette::ButtonText, QColor(250, 250, 250));
    setPalette(text_palette);

    QFont &text_font = const_cast<QFont &>(font());
    text_font.setWeight(QFont::Normal);

    setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    QPixmap pixmap(pic_name);
    setIcon(pixmap);
    //setIconSize(pixmap.size());
    //qDebug("pixmap.width() = %d, height = %d\n", pixmap.width(), pixmap.height());
    setIconSize(QSize(TOOL_BUTTON_ICON_WIDTH, TOOL_BUTTON_ICON_HEIGHT));

    //setFixedSize(pixmap.width() + 25, pixmap.height() + 25);
    setFixedSize(TOOL_BUTTON_WIDTH, TOOL_BUTTON_HEIGHT);
    setAutoRaise(true);
    setAutoFillBackground(false);

    //setObjectName("transparentToolButton");
    this->setStyleSheet(QString("background:transparent;"));

    mouse_pressed = false;
    mouse_over = false;
}

void ToolButton::setMousePressed(bool press)
{
    this->mouse_pressed = press;
    update();
}

void ToolButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked();
    }
}

void ToolButton::mouseReleaseEvent(QMouseEvent *)
{
}

void ToolButton::enterEvent(QEvent *)
{
    mouse_over = true;
    update();
}

void ToolButton::leaveEvent(QEvent *)
{
    mouse_over = false;
    update();
}

void ToolButton::paintEvent(QPaintEvent *event)
{
    if (mouse_over || mouse_pressed) {
#if 0
        QPainter painter(this);
        QPen pen(Qt::NoBrush, 1);
        painter.setPen(pen);

        QLinearGradient linear(rect().topLeft(), rect().bottomLeft());
        linear.setColorAt(0, QColor(230, 230, 230, 0));
        linear.setColorAt(0.5, QColor(230, 230, 230, 100));
        linear.setColorAt(1, QColor(230, 230, 230, 200));
        painter.setBrush(linear);
        painter.drawRect(rect());
#endif
        painterInfo(0, 100, 160);
    }

    QToolButton::paintEvent(event);
}

void ToolButton::painterInfo(int top_color, int middle_color, int bottom_color)
{
    QPainter painter(this);
    QPen pen(Qt::NoBrush, 1);
    painter.setPen(pen);
    QLinearGradient linear(rect().topLeft(), rect().bottomLeft());
    linear.setColorAt(0, QColor(230, 230, 230, top_color));
    linear.setColorAt(0.5, QColor(230, 230, 230, middle_color));
    linear.setColorAt(1, QColor(255, 255, 255, bottom_color));
    painter.setBrush(linear);
    painter.drawRect(rect());
}
