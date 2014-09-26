#include "viewanalogconfig.h"

ViewAnalogConfig::ViewAnalogConfig(QWidget *parent) :
    StyledTableView(parent)
{
    model = new ModelAnalogConfig;
    this->setModel(model);
    this->setItemDelegate(new DelegateAnalogConfig);
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    this->horizontalHeader()->setVisible(true);
    this->verticalHeader()->setSectionsClickable(false);
    this->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    //this->setSelectionBehavior(QAbstractItemView::SelectItems);

    for (int i = 0; i < ANALOG_CHANNEL_TOTAL_NUMBER; i++) {
        QWidget *widget = new QWidget;
        QHBoxLayout *layout = new QHBoxLayout(widget);
        SwitchButton *switch_button = new SwitchButton;
        this->connect(switch_button, SIGNAL(switched(bool)), SLOT(switchButtonSignalMapper(bool)));
        layout->addWidget(switch_button, 0, Qt::AlignCenter);
        layout->setContentsMargins(0, 0, 0, 0);
        enable_button_list.append(switch_button);

        QModelIndex index = model->index(i, 1);
        this->setIndexWidget(index, widget);

        widget = new QWidget;
        layout = new QHBoxLayout(widget);
        CheckBox *check_box = new CheckBox;
        layout->addWidget(check_box, 0, Qt::AlignCenter);
        layout->setContentsMargins(0, 0, 0, 0);
        flag_box_list.append(check_box);
        this->connect(check_box, SIGNAL(checked(bool)), SLOT(checkBoxSignalMapper(bool)));

        index = model->index(i, 8);
        this->setIndexWidget(index, widget);
    }

    model->connect(this, SIGNAL(configChanged()), SLOT(onConfigChanged()));
    model->connect(this, SIGNAL(switchButtonStatusChanged(int,bool)), SLOT(setChannelEnableStatus(int, bool)));
    model->connect(this, SIGNAL(checkBoxStatusChanged(int,bool)), SLOT(setChannelConvertFlag(int, bool)));
    this->connect(model, SIGNAL(channelStatusChanged(int)), SLOT(onChannelStatusChanged(int)));
}

void ViewAnalogConfig::switchButtonSignalMapper(bool value)
{
    SwitchButton *switch_button = static_cast<SwitchButton*>(this->sender());
    int index = enable_button_list.indexOf(switch_button);
    if (index < 0) {
        index = 0;
    }
    emit switchButtonStatusChanged(index, value);
}

void ViewAnalogConfig::checkBoxSignalMapper(bool value)
{
    CheckBox *check_box = static_cast<CheckBox *>(this->sender());
    int index = flag_box_list.indexOf(check_box);
    if (index < 0) {
        index = 0;
    }
    emit checkBoxStatusChanged(index, value);
}

void ViewAnalogConfig::onChannelStatusChanged(int index)
{
    SwitchButton *switch_button = enable_button_list.at(index);
    bool value = g_tContext.m_tParamConfig.m_aAnalogParam[index].m_bInuse;
    switch_button->setSwitch(value);

    CheckBox *check_box = flag_box_list.at(index);
    value = g_tContext.m_tParamConfig.m_aAnalogParam[index].m_uConvertFlag;
    check_box->setCheck(value);
}
