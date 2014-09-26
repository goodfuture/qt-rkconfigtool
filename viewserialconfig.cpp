#include "viewserialconfig.h"

ViewSerialConfig::ViewSerialConfig(QWidget *parent) :
    StyledTableView(parent)
{
    this->horizontalHeader()->setVisible(true);
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    model = new ModelSerialConfig;
    this->setModel(model);
    this->setItemDelegate(new DelegateSerialConfig);

    for (int i = 0; i < SERIAL_CHANNEL_TOTAL_NUMBER; i++) {
        QWidget *widget = new QWidget;
        QHBoxLayout *layout = new QHBoxLayout(widget);
        SwitchButton *switch_button = new SwitchButton;
        layout->addWidget(switch_button, 0, Qt::AlignCenter);
        layout->setContentsMargins(0, 0, 0, 0);
        switch_button_list.append(switch_button);
        this->connect(switch_button, SIGNAL(switched(bool)), SLOT(switchButtonSignalMapper(bool)));

        QModelIndex index = model->index(i, 1);
        this->setIndexWidget(index, widget);

        widget = new QWidget;
        layout = new QHBoxLayout(widget);
        CheckBox *check_box = new CheckBox;
        layout->addWidget(check_box, 0, Qt::AlignCenter);
        layout->setContentsMargins(0, 0, 0, 0);
        flag_box_list.append(check_box);
        this->connect(check_box, SIGNAL(checked(bool)), SLOT(checkBoxSignalMapper(bool)));

        index = model->index(i, 11);
        this->setIndexWidget(index, widget);
    }

    model->connect(this, SIGNAL(configChanged()), SLOT(onConfigChanged()));
    model->connect(this, SIGNAL(switchButtonStatusChanged(int,bool)), SLOT(setChannelEnableStatus(int, bool)));
    model->connect(this, SIGNAL(checkBoxStatusChanged(int,bool)), SLOT(setChannelConvertFlag(int, bool)));
    this->connect(model, SIGNAL(channelStatusChanged(int)), SLOT(onChannelStatusChanged(int)));
}

void ViewSerialConfig::switchButtonSignalMapper(bool value)
{
    SwitchButton *switch_button = static_cast<SwitchButton *>(this->sender());
    int index = switch_button_list.indexOf(switch_button);
    if (index < 0) {
        index = 0;
    }
    emit switchButtonStatusChanged(index, value);
}

void ViewSerialConfig::checkBoxSignalMapper(bool value)
{
    CheckBox *check_box = static_cast<CheckBox *>(this->sender());
    int index = flag_box_list.indexOf(check_box);
    if (index < 0) {
        index = 0;
    }
    emit checkBoxStatusChanged(index, value);
}

void ViewSerialConfig::onChannelStatusChanged(int index)
{
    bool value = g_tContext.m_tParamConfig.m_aSerialParam[index].m_bInuse;
    SwitchButton *switch_button = switch_button_list.at(index);
    switch_button->setSwitch(value);

    value = g_tContext.m_tParamConfig.m_aSerialParam[index].m_uConvertFlag;
    CheckBox *check_box = flag_box_list.at(index);
    check_box->setCheck(value);
}
