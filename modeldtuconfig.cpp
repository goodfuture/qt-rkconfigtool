#include "modeldtuconfig.h"

ModelDtuConfig::ModelDtuConfig(QObject *parent) :
    QAbstractTableModel(parent)
{
    headerNameList << tr("Parameter Group") << tr("Parameter Name") << tr("Parameter Value") << tr("Select");

    comParamNameList << tr("Baud") << tr("Data Bits") << tr("Stop Bits") << tr("Parity")
                     << tr("Scan Period") << tr("Response Timeout") << tr("Frame Size");

    modeParamNameList << tr("Link To Platform") << tr("Link Mode") << tr("Phone Activate")
                      << tr("SMS Activate") << tr("Local Data Activate") << tr("Activate Period")
                      << tr("Offline Period") << tr("Split Control/Business Stream");

    gprsParamNameList << tr("Auto Dial") << tr("Dialing Number") << tr("Access Point Name")
                      << tr("Dial User Name") << tr("Dial Password") << tr("PPP Level Heartbeat Period")
                      << tr("Redial Interval") << tr("Max Number Of Redial");

    platformParamNameList << tr("Device Number") << tr("Gateway IP Address") << tr("Gateway Port Number")
                          << tr("Link Mode") << tr("Heartbeat Period") << tr("SMS Center Number")
                          << tr("SMS Alarm Number");

    companyParamNameList << tr("Device Number") << tr("Gateway IP Address") << tr("Gateway Port Number")
                         << tr("Link Mode") << tr("Heartbeat Period") << tr("Max Number Of Resend")
                         << tr("DNS1") << tr("DNS2");

    multiCenterParamNameList << tr("Extern1 ") + tr("IP Address") << tr("Extern1 ") + tr("Port Number")
                             << tr("Extern1 ") + tr("DNS")
                             << tr("Extern2 ") + tr("IP Address") << tr("Extern2 ") + tr("Port Number")
                             << tr("Extern2 ") + tr("DNS")
                             << tr("Extern3 ") + tr("IP Address") << tr("Extern3 ") + tr("Port Number")
                             << tr("Extern3 ") + tr("DNS")
                             << tr("Extern4 ") + tr("IP Address") << tr("Extern4 ") + tr("Port Number")
                             << tr("Extern4 ") + tr("DNS");

    multiLinkParamNameList << tr("Minimum Interval Of Relink") << tr("Maximum Interval Of Relink")
                           << tr("Polling Mode") << tr("Tcp Server/Udp Source Port Number");

    expandParamNameList << tr("Maximum Number Of Login") << tr("Allow Remote Telnet") << tr("Debug Mode")
                        << tr("Lower Power Mode");

    paramNameList.clear();
    posNameMap[paramNameList.count()] = tr("COM1 Parameter");
    for (int i = 0; i < comParamNameList.count(); i++) {
        paramNameList << tr("COM1") + " " + comParamNameList.at(i);
    }

    posNameMap[paramNameList.count()] = tr("COM2 Parameter");
    for (int i = 0; i < comParamNameList.count(); i++) {
        paramNameList << tr("COM2") + " " + comParamNameList.at(i);
    }

    posNameMap[paramNameList.count()] = tr("Work Mode Parameter");
    paramNameList << modeParamNameList;

    posNameMap[paramNameList.count()] = tr("GPRS Dial Paramter");
    paramNameList << gprsParamNameList;

    posNameMap[paramNameList.count()] = tr("Platform Parameter");
    paramNameList << platformParamNameList;

    posNameMap[paramNameList.count()] = tr("Company Gateway Parameter");
    paramNameList << companyParamNameList;

    posNameMap[paramNameList.count()] = tr("Multi-Center Parameter");
    paramNameList << multiCenterParamNameList;

    posNameMap[paramNameList.count()] = tr("Multi-Link Parameter");
    paramNameList << multiLinkParamNameList;

    posNameMap[paramNameList.count()] = tr("Application Expand Parameter");
    paramNameList << expandParamNameList;
}

int ModelDtuConfig::rowCount(const QModelIndex &) const
{
    return paramNameList.count();
}

int ModelDtuConfig::columnCount(const QModelIndex &) const
{
    return headerNameList.count();
}

QVariant ModelDtuConfig::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        if (col == 0) {
            return posNameMap[row];
        } else if (col == 1) {
            return paramNameList.at(row);
        }
    }

    if (role == Qt::TextAlignmentRole) {
        return Qt::AlignCenter;
    }

    if (role == Qt::DecorationRole && col == 0) {
        return QIcon(QString(":/flag/flag_blue"));
    }

    return QVariant();
}

bool ModelDtuConfig::setData(const QModelIndex &, const QVariant &, int )
{
    return false;
}

QVariant ModelDtuConfig::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        if (section < headerNameList.count()) {
            return headerNameList.at(section);
        }
    }

    return QVariant();
}

Qt::ItemFlags ModelDtuConfig::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);

    if (index.isValid() == false) {
        return flags;
    }

    if (index.column() == 2) {
        flags |= Qt::ItemIsEditable;
    }

    return flags;
}

void ModelDtuConfig::onConfigChanged()
{
    emit dataChanged(this->index(0, 0), this->index(this->rowCount(QModelIndex()), this->columnCount(QModelIndex())));
}
