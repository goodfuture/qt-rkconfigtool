#include "viewbasisconfig.h"

ViewBasisConfig::ViewBasisConfig(QWidget *parent) :
    StyledTableView(parent)
{
    this->init();
}

void ViewBasisConfig::init()
{
    model = new ModelBasisConfig;
    this->setModel(model);
    //this->setItemDelegateForColumn(0, new ReadOnlyDelegate);
    //this->setItemDelegate(new SpinBoxDelegate);
    this->setItemDelegate(new DelegateBasisConfig);

    for (int i = 0; i < 6; ++i) {
        QWidget *item_widget = new QWidget;
        QHBoxLayout *h_layout = new QHBoxLayout(item_widget);
        h_layout->setContentsMargins(0, 0, 0, 0);
        SwitchButton *switchButton = new SwitchButton;
        connect(switchButton, SIGNAL(switched(bool)), this, SLOT(switchSignalMapper(bool)));
        h_layout->addWidget(switchButton, 0, Qt::AlignCenter);
        switchButtonList.append(switchButton);
        QModelIndex index = model->index(i + 6, 1);
        this->setIndexWidget(index, item_widget);
    }

    model->connect(this, SIGNAL(switchButtonChanged(int, bool)), SLOT(setModelEnableStatus(int, bool)));
    model->connect(this, SIGNAL(configChanged()), SLOT(onConfigChanged()));
    this->connect(model, SIGNAL(setViewEnableStatus(int, bool)), SLOT(setSwitchButtonStatus(int, bool)));
}

void ViewBasisConfig::setSwitchButtonStatus(int id, bool on)
{
    //qDebug() << id << on;
    SwitchButton *switchButton = switchButtonList.at(id);
    switchButton->setSwitch(on);
}

void ViewBasisConfig::switchSignalMapper(bool on)
{
    SwitchButton *switchButton = static_cast<SwitchButton *>(this->sender());
    int index = switchButtonList.indexOf(switchButton);
    emit switchButtonChanged(index, on);
}

void ViewBasisConfig::onDataEnableStatusChanged()
{
    bool status;
    status = !g_tContext.m_tParamConfig.m_tSysParam.m_bRtdUpload ? false : true;
    setSwitchButtonStatus(0, status);
    status = !g_tContext.m_tParamConfig.m_tSysParam.m_bTmdUpload ? false : true;
    setSwitchButtonStatus(1, status);
    status = !g_tContext.m_tParamConfig.m_tSysParam.m_bHsdUpload ? false : true;
    setSwitchButtonStatus(2, status);
    status = !g_tContext.m_tParamConfig.m_tSysParam.m_bDsdUpload ? false : true;
    setSwitchButtonStatus(3, status);
    status = !g_tContext.m_tParamConfig.m_tSysParam.m_bSwitchSense ? false : true;
    setSwitchButtonStatus(4, status);
    status = !g_tContext.m_tParamConfig.m_tSysParam.m_bAlarmEnable ? false : true;
    setSwitchButtonStatus(5, status);
}
