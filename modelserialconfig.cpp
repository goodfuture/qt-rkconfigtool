#include "modelserialconfig.h"

ModelSerialConfig::ModelSerialConfig(QObject *parent) :
    QAbstractTableModel(parent)
{
    label_name_list << tr("Channel Number")
                    << tr("Enable Status")
                    << tr("Channel Code")
                    << tr("COM ID")
                    << tr("Data Type")
                    << tr("Device Address")
                    << tr("Register Address")
                    << tr("Upper Range Value")
                    << tr("Lower Range Value")
                    << tr("Upper Threshold Value")
                    << tr("Lower Threshold Value")
                    << tr("Scaled Value Flag")
                    << tr("Formula Enable");

    for (int i = 0; i < COM_485_PORT_NUMBER; i++) {
        com_id_list.append(tr("Com Port") + QString::number(i + 1));
    }

    data_type_list << tr("Integer")
                   << tr("Float");

    timer = startTimer(10);
}

int ModelSerialConfig::rowCount(const QModelIndex &) const
{
    return SERIAL_CHANNEL_TOTAL_NUMBER;
}

int ModelSerialConfig::columnCount(const QModelIndex &) const
{
    return label_name_list.count();
}

QVariant ModelSerialConfig::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        if (col == 0) {
            return tr("Channel") + QString::number(row + 1);
        } else if (col == 2) {
            return QString(g_tContext.m_tParamConfig.m_aSerialParam[row].m_aCode);
        } else if (col == 3) {
            int sub_index = g_tContext.m_tParamConfig.m_aSerialParam[row].m_uComId % COM_485_PORT_NUMBER;
            return com_id_list.at(sub_index);
        } else if (col == 4) {
            int sub_index = g_tContext.m_tParamConfig.m_aSerialParam[row].m_uType % 2;
            return data_type_list.at(sub_index);
        } else if (col == 5) {
            return QString::number(g_tContext.m_tParamConfig.m_aSerialParam[row].m_uDevAddr);
        } else if (col == 6) {
            return QString::number(g_tContext.m_tParamConfig.m_aSerialParam[row].m_sRegAddr);
        } else if (col == 7) {
            return QString::number(g_tContext.m_tParamConfig.m_aSerialParam[row].m_fUpperLimitValue);
        } else if (col == 8) {
            return QString::number(g_tContext.m_tParamConfig.m_aSerialParam[row].m_fLowerLimitValue);
        } else if (col == 9) {
            return QString::number(g_tContext.m_tParamConfig.m_aSerialParam[row].m_fUpperThresholdValue);
        } else if (col == 10) {
            return QString::number(g_tContext.m_tParamConfig.m_aSerialParam[row].m_fLowerThresholdValue);
        } else if (col == 12) {
            return QString(g_tContext.m_tParamConfig.m_aSerialParam[row].m_aFormula);
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

bool ModelSerialConfig::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int col = index.column();
    int row = index.row();

    if (role != Qt::EditRole) {
        return false;
    }

    QByteArray byteArray;
    if (col == 2) {
        byteArray = value.toByteArray();
        if (byteArray.isEmpty()) {
            if (g_tContext.m_tParamConfig.m_aSerialParam[row].m_bInuse) {
                QMessageBox::warning(0, tr("Warning"), tr("Channel Code Can't Be Empty!"), tr("Ok"));
                return false;
            }
        }
#ifdef WIN32
        sprintf_s(g_tContext.m_tParamConfig.m_aSerialParam[row].m_aCode, "%s", byteArray.data());
#else
        sprintf(g_tContext.m_tParamConfig.m_aSerialParam[row].m_aCode, "%s", byteArray.data());
#endif
    } else if (col == 3) {
        int sub_index = com_id_list.indexOf(value.toString());
        if (sub_index < 0) {
            sub_index = 0;
        }
        g_tContext.m_tParamConfig.m_aSerialParam[row].m_uComId = sub_index;
    } else if (col == 4) {
        int sub_index = data_type_list.indexOf(value.toString());
        if (sub_index < 0) {
            sub_index = 0;
        }
        g_tContext.m_tParamConfig.m_aSerialParam[row].m_uType = sub_index;
    } else if (col == 5) {
        g_tContext.m_tParamConfig.m_aSerialParam[row].m_uDevAddr = value.toUInt();
    } else if (col == 6) {
        g_tContext.m_tParamConfig.m_aSerialParam[row].m_sRegAddr = value.toUInt();
    } else if (col == 7) {
        double upperLimitValue = value.toDouble();
        double lowerLimitValue = g_tContext.m_tParamConfig.m_aSerialParam[row].m_fLowerLimitValue;

        if (upperLimitValue < lowerLimitValue) {
            QMessageBox::warning(0, tr("Warning"), tr("Upper Limit Value Can't Less Than Lower Limit Value!\nSetting Invalid!"), tr("Ok"));
            return false;
        }
        g_tContext.m_tParamConfig.m_aSerialParam[row].m_fUpperLimitValue = value.toFloat();
        g_tContext.m_tParamConfig.m_aSerialParam[row].m_fUpperThresholdValue = value.toFloat();
    } else if (col == 8) {
        double lowerLimitValue = value.toDouble();
        double upperLimitValue = g_tContext.m_tParamConfig.m_aSerialParam[row].m_fUpperLimitValue;

        if (lowerLimitValue > upperLimitValue) {
            QMessageBox::warning(0, tr("Warning"), tr("Lower Limit Value Can't More Than Upper Limit Value!\nSetting Invalid!"), tr("Ok"));
            return false;
        }
        g_tContext.m_tParamConfig.m_aSerialParam[row].m_fLowerLimitValue = value.toFloat();
        g_tContext.m_tParamConfig.m_aSerialParam[row].m_fLowerThresholdValue = value.toFloat();
    } else if (col == 9) {
        double upperThresholdValue = value.toDouble();
        double upperLimitValue = g_tContext.m_tParamConfig.m_aSerialParam[row].m_fUpperLimitValue;
        double lowerThresholdValue = g_tContext.m_tParamConfig.m_aSerialParam[row].m_fLowerThresholdValue;

        if (upperThresholdValue > upperLimitValue) {
            QMessageBox::warning(0, tr("Warning"), tr("Upper Threshold Value Can't More Than Upper Limit Value!\nSetting Invalid!"), tr("Ok"));
            return false;
        }

        if (upperThresholdValue < lowerThresholdValue) {
            QMessageBox::warning(0, tr("Warning"), tr("Upper Threshold Value Can't Less Than Lower Threshold Value!\nSetting Invalid!"), tr("Ok"));
            return false;
        }
        g_tContext.m_tParamConfig.m_aSerialParam[row].m_fUpperThresholdValue = value.toFloat();
    } else if (col == 10) {
        double lowerThresholdValue = value.toDouble();
        double lowerLimitValue = g_tContext.m_tParamConfig.m_aSerialParam[row].m_fLowerLimitValue;
        double upperThresholdValue = g_tContext.m_tParamConfig.m_aSerialParam[row].m_fUpperThresholdValue;

        if (lowerThresholdValue > upperThresholdValue) {
            QMessageBox::warning(0, tr("Warning"), tr("Lower Threshold Value Can't More Than Upper Threshold Value!\nSetting Invalid!"), tr("Ok"));
            return false;
        }

        if (lowerThresholdValue < lowerLimitValue) {
            QMessageBox::warning(0, tr("Warning"), tr("Lower Threshold Value Can't Less Than Lower Limit Value!\nSetting Invalid!"), tr("Ok"));
            return false;
        }
        g_tContext.m_tParamConfig.m_aSerialParam[row].m_fLowerThresholdValue = value.toFloat();
    } else if (col == 12) {
        byteArray = value.toByteArray();
#ifdef WIN32
        sprintf_s(g_tContext.m_tParamConfig.m_aSerialParam[row].m_aFormula, "%s", byteArray.data());
#else
        sprintf(g_tContext.m_tParamConfig.m_aSerialParam[row].m_aFormula, "%s", byteArray.data());
#endif
    }

    return true;
}

QVariant ModelSerialConfig::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        return label_name_list.at(section);
    }

    if (role == Qt::BackgroundColorRole) {
        //return QColor(255, 255, 255, 255);
    }

    if (role == Qt::FontRole) {
    }

    return QVariant();
}

Qt::ItemFlags ModelSerialConfig::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);

    if (index.isValid() == false) {
        return flags;
    }

    if (index.column() != 0) {
        flags |= Qt::ItemIsEditable;
    }

    return flags;
}

void ModelSerialConfig::setChannelEnableStatus(int index, bool value)
{
    if (value) {
        if (QString(g_tContext.m_tParamConfig.m_aSerialParam[index].m_aCode).isEmpty()) {
            QMessageBox::warning(0, tr("Warning"), tr("Invalid Setting!") + "\n" + tr("Channel Code Can't Be Empty!"), tr("Ok"));
            emit channelStatusChanged(index);
            return;
        }
    }
    g_tContext.m_tParamConfig.m_aSerialParam[index].m_bInuse = value;
}

void ModelSerialConfig::setChannelConvertFlag(int index, bool value)
{
    g_tContext.m_tParamConfig.m_aSerialParam[index].m_uConvertFlag = value;
}

void ModelSerialConfig::onConfigChanged()
{
    emit dataChanged(this->index(0, 0), this->index(this->rowCount(QModelIndex()), this->columnCount(QModelIndex())));
}

void ModelSerialConfig::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timer) {
        for (int index = 0; index < SERIAL_CHANNEL_TOTAL_NUMBER; index++) {
            if (g_tContext.m_tParamConfig.m_aSerialParam[index].m_bDataChanged) {
                g_tContext.m_tParamConfig.m_aSerialParam[index].m_tMutex.lock();
                g_tContext.m_tParamConfig.m_aSerialParam[index].m_bDataChanged = false;
                g_tContext.m_tParamConfig.m_aSerialParam[index].m_tMutex.unlock();
                emit channelStatusChanged(index);
            }
        }
    }

    QAbstractTableModel::timerEvent(event);
}
