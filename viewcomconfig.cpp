#include "viewcomconfig.h"

ViewComConfig::ViewComConfig(QWidget *parent) :
    StyledTableView(parent)
{
    model = new ModelComConfig;
    delegate = new DelegateComConfig;

    model->connect(this, SIGNAL(configChanged()), SLOT(onConfigChanged()));
    delegate->connect(this, SIGNAL(resetDynamicProtocolSet()), SLOT(onResetDynamicProtocolSet()));
    this->connect(delegate, SIGNAL(requestGetProtocolSet()), SIGNAL(requestGetProtocolSet()));

    this->setModel(model);
    this->setItemDelegate(delegate);
    this->horizontalHeader()->setVisible(true);
}
