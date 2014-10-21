#include "modelnetconfig.h"

ModelNetConfig::ModelNetConfig(QObject *parent) :
    QAbstractTableModel(parent)
{
    label_name_list << tr("Communication Mode")
                    << tr("Device IP Address")
                    << tr("Device NetMask")
                    << tr("Remote IP Address")
                    << tr("Remote Port");

    link_mode_list << tr("TCP Client")
                    << tr("UDP Client");
}

int ModelNetConfig::rowCount(const QModelIndex &) const
{
    return label_name_list.count();
}

int ModelNetConfig::columnCount(const QModelIndex &) const
{
    return 2;
}

QVariant ModelNetConfig::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    if (role == Qt::DisplayRole && col == 0) {
        return label_name_list.at(row);
    }

    if ((role == Qt::DisplayRole || role == Qt::EditRole) && col == 1) {
        switch(row) {
        case 0: {
            int sub_index = g_tContext.m_tParamConfig.m_tNetParam.m_uLinkMode % 2;
            return link_mode_list.at(sub_index);
        }
        case 1:
            return QString(g_tContext.m_tParamConfig.m_tNetParam.m_aDeviceIpAddr);
        case 2:
            return QString(g_tContext.m_tParamConfig.m_tNetParam.m_aDeviceNetMask);
        case 3:
            return QString(g_tContext.m_tParamConfig.m_tNetParam.m_aRemoteIpAddr);
        case 4:
            return QString::number(g_tContext.m_tParamConfig.m_tNetParam.m_sRemotePort);
        default:
            break;
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

QVariant ModelNetConfig::headerData(int, Qt::Orientation, int) const
{
    return QVariant();
}

bool ModelNetConfig::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int row = index.row();
    int col = index.column();

    if (col == 0 || role != Qt::EditRole) {
        return false;
    }

    QByteArray byteArray;
    QString string;
    switch(row) {
    case 0: {
        int link_mode = link_mode_list.indexOf(value.toString());
        if (link_mode < 0) {
            link_mode = 0;
        }
        g_tContext.m_tParamConfig.m_tNetParam.m_uLinkMode = link_mode;
        return true;
    }
    case 1:
        byteArray = value.toByteArray();
#ifdef WIN32
        sprintf_s(g_tContext.m_tParamConfig.m_tNetParam.m_aDeviceIpAddr, "%s", byteArray.data());
#else
        sprintf(g_tContext.m_tParamConfig.m_tNetParam.m_aDeviceIpAddr, "%s", byteArray.data());
#endif
        return true;
    case 2:
        byteArray = value.toByteArray();
#ifdef WIN32
        sprintf_s(g_tContext.m_tParamConfig.m_tNetParam.m_aDeviceNetMask, "%s", byteArray.data());
#else
        sprintf(g_tContext.m_tParamConfig.m_tNetParam.m_aDeviceNetMask, "%s", byteArray.data());
#endif
        return true;
    case 3:
        byteArray = value.toByteArray();
#ifdef WIN32
        sprintf_s(g_tContext.m_tParamConfig.m_tNetParam.m_aRemoteIpAddr, "%s", byteArray.data());
#else
        sprintf(g_tContext.m_tParamConfig.m_tNetParam.m_aRemoteIpAddr, "%s", byteArray.data());
#endif
        return true;
    case 4:
        string = value.toString();
        g_tContext.m_tParamConfig.m_tNetParam.m_sRemotePort = string.toUInt();
        return true;
    default:
        break;
    }

    return false;
}

Qt::ItemFlags ModelNetConfig::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);

    if (index.isValid() && index.column() == 1) {
        flags |= Qt::ItemIsEditable;
    }

    return flags;
}

void ModelNetConfig::onConfigChanged()
{
    emit dataChanged(this->index(0, 0), this->index(this->rowCount(QModelIndex()), this->columnCount(QModelIndex())));
}
