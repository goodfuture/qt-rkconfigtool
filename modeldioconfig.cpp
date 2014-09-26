#include "modeldioconfig.h"

ModelDioConfig::ModelDioConfig(QObject *parent) :
    QAbstractTableModel(parent)
{
    labelNameList << tr("Channel Number")
                    << tr("Enable Status")
                    << tr("Channel Code")
                    << tr("Control Status");
    timer = startTimer(10);
}

int ModelDioConfig::rowCount(const QModelIndex &) const
{
    return DIGITAL_INPUT_PORT_NUMBER + DIGITAL_OUTPUT_PORT_NUMBER;
}

int ModelDioConfig::columnCount(const QModelIndex &) const
{
    return labelNameList.count();
}

QVariant ModelDioConfig::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        if (col == 0) {
            if (row < DIGITAL_INPUT_PORT_NUMBER) {
                return tr("Input Channel") + QString::number(row + 1);
            } else {
                return tr("Output Channel") + QString::number(row - DIGITAL_INPUT_PORT_NUMBER + 1);
            }
        }

        if (col == 2) {
            if (row < DIGITAL_INPUT_PORT_NUMBER) {
                return QString(g_tContext.m_tParamConfig.m_aDiParam[row].m_aCode);
            } else {
                return QString(g_tContext.m_tParamConfig.m_aDoParam[row - DIGITAL_INPUT_PORT_NUMBER].m_aCode);
            }
        }

        if (col == 3 && row < DIGITAL_INPUT_PORT_NUMBER) {
            return tr("Invalid");
        }
    }

    if (role == Qt::TextAlignmentRole) {
        return Qt::AlignCenter;
    }

    if (role == Qt::DecorationRole && col == 0) {
        if (row < DIGITAL_INPUT_PORT_NUMBER) {
            return QIcon(QString(":/flag/flag_green"));
        } else {
            return QIcon(QString(":/flag/flag_red"));
        }
    }

    return QVariant();
}

bool ModelDioConfig::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int row = index.row();
    int col = index.column();

    if (role != Qt::EditRole) {
        return false;
    }

    QByteArray byteArray;
    if (col == 2) {
        byteArray = value.toByteArray();
        if (row < DIGITAL_INPUT_PORT_NUMBER) {
            if (byteArray.isEmpty()) {
                if (g_tContext.m_tParamConfig.m_aDiParam[row].m_bInuse) {
                    QMessageBox::warning(0, tr("Warning"), tr("Channel Code Can't Be Empty!"), tr("Ok"));
                    return false;
                }
            }
            sprintf_s(g_tContext.m_tParamConfig.m_aDiParam[row].m_aCode, "%s", byteArray.data());
        } else {
            if (byteArray.isEmpty()) {
                if (g_tContext.m_tParamConfig.m_aDoParam[row - DIGITAL_INPUT_PORT_NUMBER].m_bInuse) {
                    QMessageBox::warning(0, tr("Warning"), tr("Channel Code Can't Be Empty!"), tr("Ok"));
                    return false;
                }
            }
            sprintf_s(g_tContext.m_tParamConfig.m_aDoParam[row - DIGITAL_INPUT_PORT_NUMBER].m_aCode, "%s", byteArray.data());
        }
    }

    return true;
}

QVariant ModelDioConfig::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        return labelNameList.at(section);
    }

    return QVariant();
}

Qt::ItemFlags ModelDioConfig::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);

    if (index.isValid() == false) {
        return flags;
    }

    if (index.column() != 0) {
        flags |= Qt::ItemIsEditable;
    }

#if 0
    if (index.column() == 0 | index.column() == 1 || index.column() == 8) {
        //flags |= Qt::ItemIsUserCheckable;
        flags ^= Qt::ItemIsSelectable;
    }
#endif

    return flags;
}

void ModelDioConfig::setChannelEnableStatus(int index, bool value)
{
    if (index < DIGITAL_INPUT_PORT_NUMBER) {
        if (value && QString(g_tContext.m_tParamConfig.m_aDiParam[index].m_aCode).isEmpty()) {
            QMessageBox::warning(0, tr("Warning"), tr("Invalid Setting!") + "\n" + tr("Channel Code Can't Be Empty!"), tr("Ok"));
            emit channelStatusChanged(index);
            return;
        }
        g_tContext.m_tParamConfig.m_aDiParam[index].m_bInuse = value;
    } else {
        if (value && QString(g_tContext.m_tParamConfig.m_aDoParam[index - DIGITAL_INPUT_PORT_NUMBER].m_aCode).isEmpty()) {
            QMessageBox::warning(0, tr("Warning"), tr("Invalid Setting!") + "\n" + tr("Channel Code Can't Be Empty!"), tr("Ok"));
            emit channelStatusChanged(index);
            return;
        }
        g_tContext.m_tParamConfig.m_aDoParam[index - DIGITAL_INPUT_PORT_NUMBER].m_bInuse = value;
    }
}

void ModelDioConfig::setDigitalOutputStatus(int index, bool value)
{
    g_tContext.m_tParamConfig.m_aDoParam[index].m_bIsOn = value;
}

void ModelDioConfig::onConfigChanged()
{
    emit dataChanged(this->index(0, 0), this->index(this->rowCount(QModelIndex()), this->columnCount(QModelIndex())));
}

void ModelDioConfig::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timer) {
        for (int index = 0; index < DIGITAL_INPUT_PORT_NUMBER; index++) {
            if (g_tContext.m_tParamConfig.m_aDiParam[index].m_bDataChanged) {
                g_tContext.m_tParamConfig.m_aDiParam[index].m_tMutex.lock();
                g_tContext.m_tParamConfig.m_aDiParam[index].m_bDataChanged = false;
                g_tContext.m_tParamConfig.m_aDiParam[index].m_tMutex.unlock();
                emit channelStatusChanged(index);
            }
        }

        for (int index = 0; index < DIGITAL_OUTPUT_PORT_NUMBER; index++) {
            if (g_tContext.m_tParamConfig.m_aDoParam[index].m_bDataChanged) {
                g_tContext.m_tParamConfig.m_aDoParam[index].m_tMutex.lock();
                g_tContext.m_tParamConfig.m_aDoParam[index].m_bDataChanged = false;
                g_tContext.m_tParamConfig.m_aDoParam[index].m_tMutex.unlock();
                emit channelStatusChanged(index + DIGITAL_INPUT_PORT_NUMBER);
            }
        }
    }

    QAbstractTableModel::timerEvent(event);
}
