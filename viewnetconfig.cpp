#include "viewnetconfig.h"

ViewNetConfig::ViewNetConfig(QWidget *parent) :
    StyledTableView(parent)
{
    model = new ModelNetConfig;
    this->setModel(model);
    this->setItemDelegate(new DelegateNetConfig);

    model->connect(this, SIGNAL(configChanged()), SLOT(onConfigChanged()));
}
