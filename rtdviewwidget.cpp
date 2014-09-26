#include "rtdviewwidget.h"

RtdViewWidget::RtdViewWidget(QWidget *parent) :
    QWidget(parent)
{
    this->initWidgets();
    this->translate();
}

void RtdViewWidget::initWidgets()
{
    tab_widget = new QTabWidget;
}

void RtdViewWidget::translate()
{
}

void RtdViewWidget::onLinkDrop()
{

}
