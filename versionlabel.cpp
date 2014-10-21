#include "versionlabel.h"

VersionLabel::VersionLabel(QWidget *parent) :
    QWidget(parent)
{
    QLabel *hmiLabel = new QLabel();
    QLabel *blpLabel = new QLabel();
    //QLabel *dtuLabel = new QLabel();

    QPalette palette;
    palette.setColor(QPalette::WindowText, QColor(243, 152, 0));
    hmiLabel->setPalette(palette);
    blpLabel->setPalette(palette);

    hmiLabel->setText(tr("HMI Firmware Version:"));
    blpLabel->setText(tr("Business Layer Firmware Version:"));
    //dtuLabel->setText(tr("DTU Tool Firmware Version:"));

    hmiFirmwareVersion = new QLabel();
    blpFirmwareVersion = new QLabel();
    hmiFirmwareVersion->setPalette(palette);
    blpFirmwareVersion->setPalette(palette);
    //dtuFirmwareVersion = new QLabel();

    hmiFirmwareVersion->setText(tr("Unknow"));
    blpFirmwareVersion->setText(tr("Unknow"));
    //dtuFirmwareVersion->setText(tr("Unknow"));

    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(hmiLabel, 1, 1, Qt::AlignRight);
    mainLayout->addWidget(hmiFirmwareVersion, 1, 2, Qt::AlignLeft);

    mainLayout->addWidget(blpLabel, 2, 1, Qt::AlignRight);
    mainLayout->addWidget(blpFirmwareVersion, 2, 2, Qt::AlignLeft);

    //mainLayout->addWidget(dtuLabel, 3, 1, Qt::AlignRight);
    //mainLayout->addWidget(dtuFirmwareVersion, 3, 2, Qt::AlignLeft);
}

void VersionLabel::setHmiVersion(QString version)
{
    if (version.isEmpty()) {
        hmiFirmwareVersion->setText(tr("Unknow"));
    } else {
        hmiFirmwareVersion->setText(version);
    }
}

void VersionLabel::setBlpVersion(QString version)
{
    if (version.isEmpty()) {
        blpFirmwareVersion->setText(tr("Unknow"));
    } else {
        blpFirmwareVersion->setText(version);
    }
}

#if 0
void VersionLabel::setDtuVersion(QString &version)
{
    if (version.isEmpty()) {
        dtuFirmwareVersion->setText(tr("Unknow"));
    } else {
        dtuFirmwareVersion->setText(version);
    }
}
#endif

void VersionLabel::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);

    QLinearGradient centerLinear(this->rect().topLeft(), this->rect().topRight());
    centerLinear.setColorAt(0, QColor(235, 242, 255, 0));
    centerLinear.setColorAt(0.5, QColor(255, 255, 255, 255));
    centerLinear.setColorAt(1, QColor(235, 242, 255, 0));
    painter.setBrush(centerLinear);
    painter.drawRect(this->rect());

    QLinearGradient borderLinear(this->rect().topLeft(), this->rect().topRight());
    borderLinear.setColorAt(0, QColor(235, 242, 255));
    borderLinear.setColorAt(0.5, QColor(45, 160, 202));
    borderLinear.setColorAt(1, QColor(235, 242, 255));
    painter.setBrush(borderLinear);

    QRect borderRect(this->rect().topLeft(), QSize(this->rect().width(), 1));
    painter.drawRect(borderRect);

    borderRect.moveBottomLeft(this->rect().bottomLeft());
    painter.drawRect(borderRect);
}
