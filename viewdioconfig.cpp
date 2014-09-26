#include "viewdioconfig.h"

ViewDioConfig::ViewDioConfig(QWidget *parent) :
    StyledTableView(parent)
{
    this->horizontalHeader()->setVisible(true);
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //this->horizontalHeader()->setStretchLastSection(true);

    model = new ModelDioConfig;
    this->setModel(model);
    this->setItemDelegate(new DelegateDioConfig);

    switch_button_list.clear();
    switcher_list.clear();
    for (int i = 0; i < DIGITAL_INPUT_PORT_NUMBER + DIGITAL_OUTPUT_PORT_NUMBER; i++) {
        QWidget *widget = new QWidget;
        QHBoxLayout *layout = new QHBoxLayout(widget);
        SwitchButton *switch_button = new SwitchButton;
        layout->addWidget(switch_button, 0, Qt::AlignCenter);
        layout->setContentsMargins(0, 0, 0, 0);
        this->connect(switch_button, SIGNAL(switched(bool)), SLOT(switchButtonSignalMapper(bool)));
        switch_button_list.append(switch_button);

        QModelIndex index = model->index(i, 1);
        this->setIndexWidget(index, widget);

        if (i >= DIGITAL_INPUT_PORT_NUMBER) {
            widget = new QWidget;
            layout = new QHBoxLayout(widget);
            Switcher *switcher = new Switcher;
            this->connect(switcher, SIGNAL(switcher(bool)), SLOT(switcherSignalMapper(bool)));
            layout->addWidget(switcher, 0, Qt::AlignCenter);
            layout->setContentsMargins(0, 0, 0, 0);

            index = model->index(i, 3);
            this->setIndexWidget(index, widget);
            switcher_list.append(switcher);
        }
    }

    model->connect(this, SIGNAL(configChanged()), SLOT(onConfigChanged()));
    model->connect(this, SIGNAL(switchButtonStatusChanged(int,bool)), SLOT(setChannelEnableStatus(int, bool)));
    model->connect(this, SIGNAL(switcherStatusChanged(int,bool)), SLOT(setDigitalOutputStatus(int, bool)));
    this->connect(model, SIGNAL(channelStatusChanged(int)), SLOT(onChannelStatusChanged(int)));
}

void ViewDioConfig::switchButtonSignalMapper(bool value)
{
    SwitchButton *switch_button = static_cast<SwitchButton *>(this->sender());
    int index = switch_button_list.indexOf(switch_button);
    if (index < 0) {
        index = 0;
    }
    emit switchButtonStatusChanged(index, value);
}

void ViewDioConfig::switcherSignalMapper(bool value)
{
    Switcher *switcher = static_cast<Switcher *>(this->sender());
    int index = switcher_list.indexOf(switcher);
    if (index < 0) {
        index = 0;
    }
    emit switcherStatusChanged(index, value);
}

void ViewDioConfig::onChannelStatusChanged(int index)
{
    bool value;
    SwitchButton *switch_button = switch_button_list.at(index);
    Switcher *switcher;

    if (index < DIGITAL_INPUT_PORT_NUMBER) {
        value = g_tContext.m_tParamConfig.m_aDiParam[index].m_bInuse;
        switch_button->setSwitch(value);
    } else {
        index -= DIGITAL_INPUT_PORT_NUMBER;
        switcher = switcher_list.at(index);
        value = g_tContext.m_tParamConfig.m_aDoParam[index].m_bInuse;
        switch_button->setSwitch(value);
        value = g_tContext.m_tParamConfig.m_aDoParam[index].m_bIsOn;
        switcher->setSwitcher(value);
    }
}
