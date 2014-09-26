#include "paramsettingwidget.h"

ParamSettingWidget::ParamSettingWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setFixedWidth(WINDOW_WIDTH - 2 * SHADOW_WIDTH);
    this->initWidgets();
    this->translate();

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);
    main_layout->addWidget(tabWidget);
    main_layout->addWidget(buttonLayoutWidget);

    this->setLayout(main_layout);
}

void ParamSettingWidget::initWidgets()
{
    QPalette palette;

    //next_page_button = new QPushButton();
    //prev_page_button = new QPushButton();
    syncSettingButton = new QPushButton();
    saveAllSettingButton = new QPushButton();
    syncCurrentSettingButton = new QPushButton();
    saveCurrentSettingButton = new QPushButton();
    factorySettingButton = new QPushButton();
    rebootDeviceButton = new QPushButton();

    signalMapper = new QSignalMapper;
    signalMapper->connect(syncSettingButton, SIGNAL(clicked()), SLOT(map()));
    signalMapper->connect(saveAllSettingButton, SIGNAL(clicked()), SLOT(map()));
    signalMapper->connect(syncCurrentSettingButton, SIGNAL(clicked()), SLOT(map()));
    signalMapper->connect(saveCurrentSettingButton, SIGNAL(clicked()), SLOT(map()));
    signalMapper->connect(factorySettingButton, SIGNAL(clicked()), SLOT(map()));
    signalMapper->connect(rebootDeviceButton, SIGNAL(clicked()), SLOT(map()));

    signalMapper->setMapping(syncSettingButton, 0);
    signalMapper->setMapping(saveAllSettingButton, 1);
    signalMapper->setMapping(syncCurrentSettingButton, 2);
    signalMapper->setMapping(saveCurrentSettingButton, 3);
    signalMapper->setMapping(factorySettingButton, 4);
    signalMapper->setMapping(rebootDeviceButton, 5);
    this->connect(signalMapper, SIGNAL(mapped(int)), SLOT(onButtonClicked(int)));

    buttonLayoutWidget = new QWidget(this);
    palette.setColor(QPalette::Background, QColor(88, 103, 184, 0));
    buttonLayoutWidget->setPalette(palette);
    buttonLayoutWidget->setAutoFillBackground(false);

    QHBoxLayout *button_layout = new QHBoxLayout(buttonLayoutWidget);
    button_layout->setContentsMargins(10, 3, 10, 3);
    button_layout->addStretch();
    button_layout->addWidget(factorySettingButton);
    button_layout->addWidget(rebootDeviceButton);
    button_layout->addWidget(syncSettingButton);
    button_layout->addWidget(saveAllSettingButton);
    button_layout->addWidget(syncCurrentSettingButton);
    button_layout->addWidget(saveCurrentSettingButton);

    tabWidget = new QTabWidget(this);
    tabWidget->setTabShape(QTabWidget::Rounded);

    tabNameList << tr("Basic Parameter")
                  << tr("Communication Parameter")
                  << tr("Analog Parameter")
                  << tr("Serial Parameter")
                  << tr("Switch Parameter")
                  << tr("DTU Configure");

    viewBasisConfig = new ViewBasisConfig();
    viewComConfig = new ViewComConfig();
    viewNetConfig = new ViewNetConfig();
    viewAnalogConfig = new ViewAnalogConfig();
    viewSerialConfig = new ViewSerialConfig();
    viewDioConfig = new ViewDioConfig();
    dtuConfigWidget = new DtuConfigWidget();

    viewBasisConfig->connect(this, SIGNAL(configChanged()), SIGNAL(configChanged()));
    viewComConfig->connect(this, SIGNAL(configChanged()), SIGNAL(configChanged()));
    viewNetConfig->connect(this, SIGNAL(configChanged()), SIGNAL(configChanged()));
    viewAnalogConfig->connect(this, SIGNAL(configChanged()), SIGNAL(configChanged()));
    viewSerialConfig->connect(this, SIGNAL(configChanged()), SIGNAL(configChanged()));
    viewDioConfig->connect(this, SIGNAL(configChanged()), SIGNAL(configChanged()));
    dtuConfigWidget->connect(this, SIGNAL(configChanged()), SIGNAL(configChanged()));

    viewComConfig->connect(this, SIGNAL(resetDynamicProtocolSet()), SIGNAL(resetDynamicProtocolSet()));
    this->connect(viewComConfig, SIGNAL(requestGetProtocolSet()), SLOT(onRequestGetProtocolSet()));

    QSplitter *splitter = new QSplitter;
    splitter->setOrientation(Qt::Vertical);
    splitter->setOpaqueResize(false);
    splitter->setHandleWidth(2);
    splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QWidget *widget = new QWidget;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    widget->setPalette(palette);
    widget->setAutoFillBackground(true);

    QVBoxLayout *layout = new QVBoxLayout(widget);

    QLabel *label = new QLabel;
    label->setText(tr("Serial Port Parameter"));
    layout->addWidget(label);
    layout->addWidget(viewComConfig);
    splitter->addWidget(widget);

    widget = new QWidget;
    widget->setPalette(palette);
    widget->setAutoFillBackground(true);
    //widget->setStyleSheet(QString("background:white"));
    layout = new QVBoxLayout(widget);
    label = new QLabel;
    label->setText(tr("Network Parameter"));
    layout->addWidget(label);
    layout->addWidget(viewNetConfig);
    splitter->addWidget(widget);

    for(int i = 0; i < splitter->count(); i++) {
        QSplitterHandle *handle = splitter->handle(i);
        handle->setEnabled(false);
    }

    tabWidget->addTab(viewBasisConfig, QIcon(QString(":/tab_icon/1")), tabNameList.at(0));
    tabWidget->addTab(splitter, QIcon(QString(":/tab_icon/2")), tabNameList.at(1));
    tabWidget->addTab(viewAnalogConfig, QIcon(QString(":/tab_icon/3")), tabNameList.at(2));
    tabWidget->addTab(viewSerialConfig, QIcon(QString(":/tab_icon/4")), tabNameList.at(3));
    tabWidget->addTab(viewDioConfig, QIcon(QString(":/tab_icon/5")), tabNameList.at(4));
    tabWidget->addTab(dtuConfigWidget, QIcon(QString(":/tab_icon/6")), tabNameList.at(5));

}

void ParamSettingWidget::translate()
{
    //next_page_button->setText(tr("Next Page"));
    //prev_page_button->setText(tr("Prev Page"));
    factorySettingButton->setText(tr("Factory Setting"));
    saveAllSettingButton->setText(tr("Save All To Device"));
    syncSettingButton->setText(tr("Sync All From Device"));
    saveCurrentSettingButton->setText(tr("Save Current To Device"));
    syncCurrentSettingButton->setText(tr("Sync Current From Device"));
    rebootDeviceButton->setText(tr("Reboot Device"));
}

void ParamSettingWidget::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
}

void ParamSettingWidget::onButtonClicked(int id)
{
    //qDebug() << "CurrentPage" << tabWidget->currentIndex();
    switch(id) {
    case 0: //Sync All
        emit userRequest(Util::REQUEST_SYNC_ALL_CONFIG);
        break;
    case 1: //Save All
        emit userRequest(Util::REQUEST_SAVE_ALL_CONFIG);
        break;
    case 2: //Sync Current
        switch(tabWidget->currentIndex()) {
        case 0:
            emit userRequest(Util::REQUEST_SYNC_SYSTEM_CONFIG);
            break;
        case 1:
            emit userRequest(Util::REQUEST_SYNC_COM_CONFIG);
            emit userRequest(Util::REQUEST_SYNC_NET_CONFIG);
            break;
        case 2:
            emit userRequest(Util::REQUEST_SYNC_ANALOG_CONFIG);
            break;
        case 3:
            emit userRequest(Util::REQUEST_SYNC_SERIAL_CONFIG);
            break;
        case 4:
            emit userRequest(Util::REQUEST_SYNC_DIO_CONFIG);
            break;
        case 5:
            emit userRequest(Util::REQUEST_SYNC_DIO_CONFIG);
            break;
        }
        break;
    case 3: //Save Current
        switch(tabWidget->currentIndex()) {
        case 0:
            emit userRequest(Util::REQUEST_SAVE_SYSTEM_CONFIG);
            break;
        case 1:
            emit userRequest(Util::REQUEST_SAVE_COM_CONFIG);
            emit userRequest(Util::REQUEST_SAVE_NET_CONFIG);
            break;
        case 2:
            emit userRequest(Util::REQUEST_SAVE_ANALOG_CONFIG);
            break;
        case 3:
            emit userRequest(Util::REQUEST_SAVE_SERIAL_CONFIG);
            break;
        case 4:
            emit userRequest(Util::REQUEST_SAVE_DIO_CONFIG);
            break;
        case 5:
            emit userRequest(Util::REQUEST_SAVE_DIO_CONFIG);
            break;
        }
        break;
    case 4: //Factory
        emit userRequest(Util::REQUEST_FACTORY_CONFIG);
    case 5: //Reboot
        emit userRequest(Util::REQUEST_REBOOT_DEVICE);
    default:
        break;
    }
}

void ParamSettingWidget::onLinkDrop()
{

}

void ParamSettingWidget::onMessageHandled(Util::MsgHandleFlag flag, Util::MsgHandleRst result)
{
    switch(flag) {
    case Util::GetSupportedProtocolFlag:
        if (result == Util::GetSupportedProtocolSuccessRst) {
            emit resetDynamicProtocolSet();
        }
        break;
    case Util::GetConfigFlag:
    case Util::PutConfigFlag:
        emit configChanged();
        break;
    default:
        break;
    }
}

void ParamSettingWidget::onRequestGetProtocolSet()
{
    emit userRequest(Util::REQUEST_GET_DYNAMIC_PROTOCOL_SET);
}

void ParamSettingWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);

    QLinearGradient base_layer_linear(this->rect().topLeft(), this->rect().bottomLeft());
    base_layer_linear.setColorAt(0, QColor(235, 235, 235, 200));
    base_layer_linear.setColorAt(0.04, QColor(49, 104, 197, 130));
    base_layer_linear.setColorAt(1, QColor(49, 104, 197, 135));
    painter.setBrush(base_layer_linear);
    painter.drawRect(this->rect());

#if 0
    QRect rect(0, 0, this->width(), 1);
    QLinearGradient linear(rect.topLeft(), rect.topRight());
    linear.setColorAt(0, QColor(230, 230, 230, 0));
    linear.setColorAt(0.5, QColor(250, 250, 250, 255));
    linear.setColorAt(1, QColor(230, 230, 230, 0));
    painter.setBrush(linear);
    painter.drawRect(rect);
    painter.setPen(Qt::white);
    painter.drawLine(this->rect().bottomLeft(), this->rect().bottomRight());
#endif
}
