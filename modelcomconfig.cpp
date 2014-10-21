#include "modelcomconfig.h"

ModelComConfig::ModelComConfig(QObject *parent) :
    QAbstractTableModel(parent)
{
    label_name_list << tr("Channel Number")
                    << tr("Baud Rate")
                    << tr("Data Bit")
                    << tr("Stop Bit")
                    << tr("Parity Bit")
                    << tr("Protocol");

    baud_rate_list << QString("1200")
                   << QString("2400")
                   << QString("4800")
                   << QString("9600")
                   << QString("14400")
                   << QString("19200")
                   << QString("38400")
                   << QString("57600")
                   << QString("115200");

    data_bit_list << QString("5") + tr("bit")
                  << QString("6") + tr("bit")
                  << QString("7") + tr("bit")
                  << QString("8") + tr("bit");

    stop_bit_list << QString("1") + tr("bit")
                  << QString("2") + tr("bit");

    parity_list << tr("None")
                << tr("Odd")
                << tr("Even");

    protocol_list.clear();
}

int ModelComConfig::rowCount(const QModelIndex &) const
{
    return COM_485_PORT_NUMBER;
}

int ModelComConfig::columnCount(const QModelIndex &) const
{
    return label_name_list.count();
}

QVariant ModelComConfig::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        if (col == 0) {
            return tr("Serial Port") + QString::number(row + 1);
        } else if (col == 1) {
            return QString::number(g_tContext.m_tParamConfig.m_aComParam[row].m_nBaud);
        } else if (col == 2) {
            return QString::number(g_tContext.m_tParamConfig.m_aComParam[row].m_uDataBit) + tr("bit");
        } else if (col == 3) {
            return QString::number(g_tContext.m_tParamConfig.m_aComParam[row].m_uStopBit) + tr("bit");
        } else if (col == 4) {
            int sub_index = g_tContext.m_tParamConfig.m_aComParam[row].m_uParity % parity_list.count();
            return parity_list.at(sub_index);
        } else if (col == 5){
            return QString(g_tContext.m_tParamConfig.m_aComParam[row].m_aProtocol);
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

QVariant ModelComConfig::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        return label_name_list.at(section);
    }

    return QVariant();
}

bool ModelComConfig::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int row = index.row();
    int col = index.column();

    if (col == 0 || role != Qt::EditRole) {
        return false;
    }

    QByteArray byteArray;
    QString string;
    if (col == 1) {
        g_tContext.m_tParamConfig.m_aComParam[row].m_nBaud = value.toUInt();
    } else if (col == 2) {
        string = value.toString();
        string.remove(tr("bit"));
        g_tContext.m_tParamConfig.m_aComParam[row].m_uDataBit = string.toUInt();
    } else if (col == 3) {
        string = value.toString();
        string.remove(tr("bit"));
        g_tContext.m_tParamConfig.m_aComParam[row].m_uStopBit = string.toUInt();
    } else if (col == 4) {
        int parity = parity_list.indexOf(value.toString());
        if (parity < 0) {
            parity = 0;
        }
        g_tContext.m_tParamConfig.m_aComParam[row].m_uParity = parity;
    } else if (col == 5) {
        byteArray = value.toByteArray();
#ifdef WIN32
        sprintf_s(g_tContext.m_tParamConfig.m_aComParam[row].m_aProtocol, "%s", byteArray.data());
#else
        sprintf(g_tContext.m_tParamConfig.m_aComParam[row].m_aProtocol, "%s", byteArray.data());
#endif
    }

    return true;
}

Qt::ItemFlags ModelComConfig::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);

    if (index.isValid() && index.column() != 0) {
        flags |= Qt::ItemIsEditable;
    }

    return flags;
}

void ModelComConfig::onConfigChanged()
{
    emit dataChanged(this->index(0, 0), this->index(this->rowCount(QModelIndex()), this->columnCount(QModelIndex())));
}
