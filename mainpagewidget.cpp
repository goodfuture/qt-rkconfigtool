#include "mainpagewidget.h"

MainPageWidget::MainPageWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setFixedWidth(WINDOW_WIDTH - 2 * SHADOW_WIDTH);
    this->initWidgets();
    this->translate();
    this->setBackgroundPixmap(QPixmap(":/main_page/grass_background"));

    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->addWidget(versionLabel, 0, Qt::AlignRight);
    vLayout->addStretch();
    vLayout->addWidget(dockWidget, 0, Qt::AlignRight);
    vLayout->setContentsMargins(0, 40, 0, 20);

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->setContentsMargins(30, 0, 20, 0);
    hLayout->addWidget(roundButton, 0, Qt::AlignVCenter);
    //hLayout->addWidget(productPicLabel);
    hLayout->addSpacing(20);
    hLayout->addLayout(vLayout);
    //hLayout->addWidget(productSpecifyLabel, 0, Qt::AlignVCenter);
    //hLayout->addStretch();

    this->setLayout(hLayout);
}

void MainPageWidget::initWidgets()
{
    screen = QGuiApplication::primaryScreen();

    productPicLabel = new QLabel;
    productPicLabel->setPixmap(QPixmap(":/main_page/platform"));
    productPicLabel->setScaledContents(true);
    productPicLabel->setFixedSize(380, 380);

    /*
    QGraphicsBlurEffect *blurEffect = new QGraphicsBlurEffect(this);
    blurEffect->setBlurRadius(1);
    productPicLabel->setGraphicsEffect(blurEffect);
    */


    productSpecifyLabel = new QLabel;
#if 1
    productSpecifyLabel->setWordWrap(true);
    productSpecifyLabel->setText(tr("Product Specify"));

    QFont font = productSpecifyLabel->font();
    font.setPointSize(12);
    productSpecifyLabel->setFont(font);
    //productSpecifyLabel->setStyleSheet(QString("color:rgb(29, 124, 204)"));
    productSpecifyLabel->setStyleSheet(QString("color:white"));

#else
    productSpecifyLabel->setPixmap(QPixmap(":/main_page/global"));
    productSpecifyLabel->setScaledContents(true);
#endif

    roundButton = new RoundButton;
    versionLabel = new VersionLabel;

    dockWidget = new DockWidget;
    dockWidget->addIcon(QPixmap(":/dock/setting"), tr("Setting"));
    dockWidget->addIcon(QPixmap(":/dock/record"), tr("Record"));
    dockWidget->addIcon(QPixmap(":/dock/monitor"), tr("Monitor"));
    dockWidget->addIcon(QPixmap(":/dock/update"), tr("Firmware Upgrade"));
    dockWidget->addIcon(QPixmap(":/dock/debug"), tr("Debug"));
    this->connect(dockWidget, SIGNAL(clicked(int)), SLOT(onDockWidgetClicked(int)));

    firmwareUpgradeDialog = new FirmwareUpgradeDialog(this);
    this->connect(firmwareUpgradeDialog, SIGNAL(beginUpgrade(Util::FirmwareType, QString)), SIGNAL(requestUpgradeFirmware(Util::FirmwareType, QString)));
    this->connect(firmwareUpgradeDialog, SIGNAL(userRequest(int)), SIGNAL(userRequest(int)));
    firmwareUpgradeDialog->connect(this, SIGNAL(upgradeProgress(int)), SLOT(onUpgradeProgress(int)));
}

void MainPageWidget::translate()
{
}

void MainPageWidget::onLinkDrop()
{
    firmwareUpgradeDialog->close();
}

void MainPageWidget::onDockWidgetClicked(int item)
{
    //qDebug() << item;
    switch(item) {
    case 0:
        //screen->grabWindow(0).save("123", "jpg");
        //break;
    case 1:
    case 2:
    case 4:
        QMessageBox::information(this, tr("Information"), tr("Sorry! Invalid Fuction!"), tr("Ok"));
        break;
    case 3:
        firmwareUpgradeDialog->exec();
        break;
    default:
        break;
    }
}

void MainPageWidget::onMessageHandled(Util::MsgHandleFlag type, Util::MsgHandleRst)
{
    switch(type) {
    case Util::GetFirmwareVersionFlag:
        versionLabel->setHmiVersion(QString(g_tContext.m_aHmiVersion));
        versionLabel->setBlpVersion(QString(g_tContext.m_aBlpVersion));
        //versionLabel->setDtuVersion(QString(g_tContext.m_aDtuToolVersion));
        break;
    default:
        break;
    }
}

void MainPageWidget::setBackgroundPixmap(QPixmap pixmap)
{
    this->backgroundPixmap = pixmap;

    QPainter painter(&this->backgroundPixmap);
    painter.setPen(Qt::NoPen);

    QLinearGradient linear(pixmap.rect().topLeft(), pixmap.rect().bottomLeft());
    linear.setColorAt(0, QColor(255, 255, 255, 0));
    linear.setColorAt(0.8, QColor(255, 255, 255, 160));
    linear.setColorAt(1, QColor(255, 255, 255, 160));

    painter.setBrush(linear);
    painter.drawRect(pixmap.rect());
    painter.end();
}

void MainPageWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);

    QRect baseRect = this->rect();

    painter.setBrush(QBrush(QColor(235, 235, 235, 105)));
    painter.drawRect(baseRect);

#if 1
    QLinearGradient skyLayerLinear(baseRect.topLeft(), baseRect.bottomLeft());
    skyLayerLinear.setColorAt(0, QColor(128, 175, 224, 255));
    skyLayerLinear.setColorAt(0.095, QColor(235, 242, 255, 255));
    skyLayerLinear.setColorAt(1, QColor(235, 242, 255, 255));
    painter.setBrush(skyLayerLinear);
    painter.drawRect(baseRect);

    QRect topLineRect(0, 0, this->width(), 1);
    QLinearGradient topLineGradient(topLineRect.topLeft(), topLineRect.topRight());
    topLineGradient.setColorAt(0, QColor(230, 230, 230, 0));
    topLineGradient.setColorAt(0.5, QColor(250, 250, 250, 255));
    topLineGradient.setColorAt(1, QColor(230, 230, 230, 0));
    painter.setBrush(topLineGradient);
    painter.drawRect(topLineRect);

    painter.drawPixmap(baseRect, this->backgroundPixmap);

    QRect centerRect(QPoint(300, 158), QSize(baseRect.width() - 300, 140));

    QLinearGradient linear(centerRect.topLeft(), centerRect.topRight());
    linear.setColorAt(0, QColor(255, 255, 255));
    linear.setColorAt(1, QColor(235, 242, 255, 200));
    painter.setBrush(linear);
    painter.drawRect(centerRect);

    QFont font = painter.font();
    font.setBold(true);
    font.setPointSize(12);
    painter.setFont(font);

    QRect textRect(centerRect.topLeft() + QPoint(45, 15), centerRect.bottomRight() - QPoint(20, 10));
    painter.setPen(QColor(119, 90, 254));
    //painter.setPen(QColor(147, 147, 255));
    //painter.setPen(QColor(170, 213, 255));
    painter.drawText(textRect, tr("Product Features:"));

    font.setBold(false);
    font.setPointSize(10);
    painter.setFont(font);

    textRect.moveTop(textRect.top() + 25);
    painter.drawText(textRect, tr("1.Support GPRS/CDMA Multiple Communication Mode.") + "\n" +
                     tr("2.External Interface All Adopt Photoelectric Isolate Design, Strong Anti-Interference Ability.") + "\n" +
                     tr("3.Ultra-High Capability Storage, Historical Data Storage For More Than One Year.") + "\n" +
                     tr("4.High Precision Data Acquisition Function,The Sampling Precision Is 24.") + "\n" +
                     tr("5.The 7 Inch Color LCD Device With Touch Function,With The Reduced 6 Button To Complete The Human-Computer Interaction Function."));
    painter.setPen(Qt::NoPen);

    QRect borderRect;
    borderRect.setTopLeft(centerRect.topLeft());
    borderRect.setWidth(centerRect.width());
    borderRect.setHeight(3);

    linear.setColorAt(0, QColor(45, 160, 202));
    linear.setColorAt(1, QColor(235, 242, 255, 200));
    painter.setBrush(linear);
    painter.drawRect(borderRect);

    borderRect.moveBottomLeft(centerRect.bottomLeft());
    painter.drawRect(borderRect);

#else
    QLinearGradient skyLayerLinear(this->rect().topLeft(), this->rect().bottomLeft());
    //skyLayerLinear.setColorAt(0, QColor(230, 230, 230, 200));
    //skyLayerLinear.setColorAt(0.012, QColor(2, 37, 131, 220));
    //skyLayerLinear.setColorAt(0.1, QColor(9, 45, 138, 220));
    skyLayerLinear.setColorAt(0, QColor(235, 235, 235, 220));
    skyLayerLinear.setColorAt(0.10, QColor(120, 175, 255, 220));
    //skyLayerLinear.setColorAt(0.25, QColor(49, 104, 197, 220));
    //skyLayerLinear.setColorAt(0.6, QColor(120, 175, 255, 220));
    skyLayerLinear.setColorAt(0.65, QColor(120, 175, 255, 220));
    skyLayerLinear.setColorAt(1, QColor(231, 238, 248, 255));
    painter.setBrush(skyLayerLinear);
    painter.drawRect(this->rect());

    QRect rect(0, 0, this->width(), 1);
    QLinearGradient linear(rect.topLeft(), rect.topRight());
    linear.setColorAt(0, QColor(230, 230, 230, 0));
    linear.setColorAt(0.5, QColor(250, 250, 250, 255));
    linear.setColorAt(1, QColor(230, 230, 230, 0));
    painter.setBrush(linear);
    painter.drawRect(rect);

    painter.setPen(Qt::white);
    painter.drawLine(this->rect().topLeft(), this->rect().topRight());

    //QPixmap pixmap(":/main_page/platform");
#endif
}

void MainPageWidget::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    //emit requestGetFirmwareVersion(Util::AllFirmware);
}
