#include "dockwidget.h"

DockWidget::DockWidget(QWidget *parent) :
    QWidget(parent)
{
    dockItemList.clear();
    marginLeft = 50;
    marginTop = 0;
    marginRight = 50;
    marginBottom = 15;

    mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(marginLeft, marginTop, marginRight, marginBottom);

    signalMapper = new QSignalMapper(this);
    this->connect(signalMapper, SIGNAL(mapped(int)), SIGNAL(clicked(int)));
}

void DockWidget::resize()
{
    //QWidget::resize();
}

void DockWidget::addIcon(QPixmap &icon, QString &tip)
{
    DockItemWidget *item = new DockItemWidget(this, icon, tip);
    dockItemList << item;
    mainLayout->addWidget(item);
    signalMapper->connect(item, SIGNAL(clicked()), SLOT(map()));
    signalMapper->setMapping(item, dockItemList.indexOf(item));
}

void DockWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pixmap(":/dock/dock_bar");
    painter.drawPixmap(0, 0, this->width(), this->height(), pixmap);

}
