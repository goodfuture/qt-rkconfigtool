#include "styledtableview.h"

StyledTableView::StyledTableView(QWidget *parent) :
    QTableView(parent)
{
    QPalette palette;
    //palette.setColor(QPalette::Base, QColor(255, 255, 255));
    //palette.setColor(QPalette::AlternateBase, QColor(232, 232, 232));
    //palette.setColor(QPalette::Base, QColor(250, 250, 155));
    palette.setColor(QPalette::Base, QColor(250, 250, 255));
    palette.setColor(QPalette::AlternateBase, QColor(152, 216, 245));
    this->setPalette(palette);
    this->setShowGrid(false);
    this->setEditTriggers(QAbstractItemView::DoubleClicked);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setAlternatingRowColors(true);

    this->horizontalHeader()->setVisible(false);
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->horizontalHeader()->setHighlightSections(false);
    this->verticalHeader()->setVisible(false);
    this->verticalHeader()->setHighlightSections(false);

    //this->horizontalHeader()->resizeSection(0, this->width() * 1 / 2);
    //this->horizontalHeader()->setStretchLastSection(true);
    //this->setStyleSheet(QString("QTableWidget::item{border-bottom:1px solid rgb(210, 210, 210, 200)}"));
}
