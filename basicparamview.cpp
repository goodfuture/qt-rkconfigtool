#include "basicparamview.h"
#include "spinboxdelegate.h"

BasicParamView::BasicParamView(QWidget *parent) :
    QTableView(parent)
{
    this->init();
}

void BasicParamView::init()
{
    model = new BasicParamModel;
    this->setModel(model);
    this->setShowGrid(false);
    this->setEditTriggers(QAbstractItemView::DoubleClicked);
    //this->setItemDelegateForColumn(0, new ReadOnlyDelegate);
    //this->setItemDelegate(new SpinBoxDelegate);
    this->setItemDelegate(new BasicParamDelegate);
    //this->horizontalHeader()->setHighlightSections(false);
    //this->horizontalHeader()->resizeSection(0, this->width() * 1 / 2);
    //this->horizontalHeader()->setStretchLastSection(true);
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->horizontalHeader()->setVisible(false);
    this->verticalHeader()->setVisible(false);
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    //this->setStyleSheet(QString("QTableWidget::item{border-bottom:1px solid rgb(210, 210, 210, 200)}"));
}
