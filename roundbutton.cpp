#include "roundbutton.h"

RoundButton::RoundButton(QWidget *parent) :
    QWidget(parent)
{
    this->setFixedSize(300, 300);

    /*
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(5, 5);
    shadow_effect->setColor(Qt::gray);
    shadow_effect->setBlurRadius(8);
    label->setGraphicsEffect(shadow_effect);

    QHBoxLayout *main_layout = new QHBoxLayout(this);
    main_layout->addWidget(label);
    */
}

void RoundButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //painter.setPen(Qt::NoPen);
    painter.setPen(Qt::black);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    //painter.drawEllipse(this->rect());

#if 0
    QPainterPath path;
    path.addEllipse(this->rect());
    path.addEllipse(5, 5, this->rect().width() - 10, this->rect().height() - 10);
    path.setFillRule(Qt::OddEvenFill);

    QRadialGradient radialGradient(this->rect().center(), this->rect().width() / 2.0f);
    radialGradient.setColorAt(0, Qt::yellow);
    radialGradient.setColorAt(0.9, Qt::yellow);
    radialGradient.setColorAt(0.95, Qt::blue);
    radialGradient.setColorAt(1, Qt::red);
    painter.fillPath(path, QBrush(radialGradient));
    //painter.drawPath(path);
#endif

    painter.drawPixmap(this->rect(), QPixmap(":/round_button/round_button"));
}
