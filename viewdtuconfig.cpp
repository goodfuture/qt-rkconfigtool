#include "viewdtuconfig.h"

ViewDtuConfig::ViewDtuConfig(QWidget *parent) :
    StyledTableView(parent)
{
    this->horizontalHeader()->setVisible(true);
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    model = new ModelDtuConfig;
    delegate = new DelegateDtuConfig;

    this->setModel(model);
    this->setItemDelegate(delegate);

#if 1
    int row = 0;
    this->setSpan(row, 0, 7, 1);
    row += 7;
    this->setSpan(row, 0, 7, 1);
    row += 7;
    this->setSpan(row, 0, 8, 1);
    row += 8;
    this->setSpan(row, 0, 8, 1);
    row += 8;
    this->setSpan(row, 0, 7, 1);
    row += 7;
    this->setSpan(row, 0, 8, 1);
    row += 8;
    this->setSpan(row, 0, 12, 1);
    row += 12;
    this->setSpan(row, 0, 4, 1);
    row += 4;
    this->setSpan(row, 0, 4, 1);
    row += 4;
#else
    this->setSpan(0, 0, 1, 3);
    this->setSpan(8, 0, 1, 3);
    this->setSpan(16, 0, 1, 3);
    this->setSpan(25, 0, 1, 3);
    this->setSpan(34, 0, 1, 3);
    this->setSpan(42, 0, 1, 3);
    this->setSpan(51, 0, 1, 3);
    this->setSpan(64, 0, 1, 3);

    this->setRowHeight(0, this->rowHeight(0) * 1.2f);
    this->setRowHeight(8, this->rowHeight(8) * 1.2f);
    this->setRowHeight(16, this->rowHeight(16) * 1.2f);
    this->setRowHeight(25, this->rowHeight(25) * 1.2f);
    this->setRowHeight(34, this->rowHeight(34) * 1.2f);
    this->setRowHeight(42, this->rowHeight(42) * 1.2f);
    this->setRowHeight(51, this->rowHeight(51) * 1.2f);
    this->setRowHeight(64, this->rowHeight(64) * 1.2f);
#endif

}

void ViewDtuConfig::setUserPermission(bool superUser)
{
    this->superUser = superUser;

    bool hide = !superUser;
    this->setRowHidden(0, hide);
    this->setRowHidden(8, hide);
    this->setRowHidden(16, hide);
    this->setRowHidden(25, hide);
    this->setRowHidden(34, hide);
}
