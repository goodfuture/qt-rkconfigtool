#include "modelanalogconfig.h"

ModelAnalogConfig::ModelAnalogConfig(QObject *parent) :
    QAbstractTableModel(parent)
{
    label_name_list << tr("Channel Number")
                    << tr("Enable Status")
                    << tr("Channel Type")
                    << tr("Channel Code")
                    << tr("Upper Range Value")
                    << tr("Lower Range Value")
                    << tr("Upper Threshold Value")
                    << tr("Lower Threshold Value")
                    << tr("Scaled Value Flag")
                    << tr("Formula Enable");

    channel_type_list << QString("4-20mA")
                      << QString("0-5V");
    timer = startTimer(10);
}

int ModelAnalogConfig::rowCount(const QModelIndex &) const
{
    return ANALOG_CHANNEL_TOTAL_NUMBER;
}

int ModelAnalogConfig::columnCount(const QModelIndex &) const
{
    return label_name_list.count();
}

QVariant ModelAnalogConfig::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        if (col == 0) {
            return tr("Channel") + QString::number(row + 1);
        } else if (col == 2) {
            int sub_index = g_tContext.m_tParamConfig.m_aAnalogParam[row].m_uType % 2;
            return channel_type_list.at(sub_index);
        } else if (col == 3) {
            return QString(g_tContext.m_tParamConfig.m_aAnalogParam[row].m_aCode);
        } else if (col == 4) {
            return QString::number(g_tContext.m_tParamConfig.m_aAnalogParam[row].m_fUpperLimitValue);
        } else if (col == 5) {
            return QString::number(g_tContext.m_tParamConfig.m_aAnalogParam[row].m_fLowerLimitValue);
        } else if (col == 6) {
            return QString::number(g_tContext.m_tParamConfig.m_aAnalogParam[row].m_fUpperThresholdValue);
        } else if (col == 7) {
            return QString::number(g_tContext.m_tParamConfig.m_aAnalogParam[row].m_fLowerThresholdValue);
        } else if (col == 9) {
            return QString(g_tContext.m_tParamConfig.m_aAnalogParam[row].m_aFormula);
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

QVariant ModelAnalogConfig::headerData(int section, Qt::Orientation orientation, int role) const
{
    //qDebug("section = %d, orientation = %d, role = %d", section, orientation, role);
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return label_name_list.at(section);
    }

    return QVariant();
}

bool ModelAnalogConfig::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int row = index.row();
    int col = index.column();

    if (col == 0 || role == 1|| role != Qt::EditRole) {
        return false;
    }

    QByteArray byteArray;
    QString string;
    if (col == 2) {
        int sub_index = channel_type_list.indexOf(value.toString());
        if (sub_index < 0) {
            sub_index = 0;
        }
        g_tContext.m_tParamConfig.m_aAnalogParam[row].m_uType = sub_index;
        //qDebug() << sub_index << g_tContext.m_tParamConfig.m_aAnalogParam[row].type;
    } else if(col == 3) {
        byteArray = value.toByteArray();
        if (byteArray.isEmpty()) {
            if (g_tContext.m_tParamConfig.m_aAnalogParam[row].m_bInuse) {
                QMessageBox::warning(0, tr("Warning"), tr("Channel Code Can't Be Empty!"), tr("Ok"));
                return false;
            }
        }
#ifdef WIN32
        sprintf_s(g_tContext.m_tParamConfig.m_aAnalogParam[row].m_aCode, "%s", byteArray.data());
#else
        sprintf(g_tContext.m_tParamConfig.m_aAnalogParam[row].m_aCode, "%s", byteArray.data());
#endif
    } else if (col == 4) {
        string = value.toString();
        double upperLimitValue = string.toDouble();
        double lowerLimitValue = g_tContext.m_tParamConfig.m_aAnalogParam[row].m_fLowerLimitValue;

        if (upperLimitValue < lowerLimitValue) {
            QMessageBox::warning(0, tr("Warning"), tr("Upper Limit Value Can't Less Than Lower Limit Value!\nSetting Invalid!"), tr("Ok"));
            return false;
        }
        g_tContext.m_tParamConfig.m_aAnalogParam[row].m_fUpperLimitValue = string.toFloat();
        g_tContext.m_tParamConfig.m_aAnalogParam[row].m_fUpperThresholdValue = string.toFloat();
    } else if (col == 5) {
        string = value.toString();
        double lowerLimitValue = string.toDouble();
        double upperLimitValue = g_tContext.m_tParamConfig.m_aAnalogParam[row].m_fUpperLimitValue;

        if (lowerLimitValue > upperLimitValue) {
            QMessageBox::warning(0, tr("Warning"), tr("Lower Limit Value Can't More Than Upper Limit Value!\nSetting Invalid!"), tr("Ok"));
            return false;
        }
        g_tContext.m_tParamConfig.m_aAnalogParam[row].m_fLowerLimitValue = string.toFloat();
        g_tContext.m_tParamConfig.m_aAnalogParam[row].m_fLowerThresholdValue = string.toFloat();
    } else if (col == 6) {
        string = value.toString();
        double upperThresholdValue = string.toDouble();
        double upperLimitValue = g_tContext.m_tParamConfig.m_aAnalogParam[row].m_fUpperLimitValue;
        double lowerThresholdValue = g_tContext.m_tParamConfig.m_aAnalogParam[row].m_fLowerThresholdValue;

        if (upperThresholdValue > upperLimitValue) {
            QMessageBox::warning(0, tr("Warning"), tr("Upper Threshold Value Can't More Than Upper Limit Value!\nSetting Invalid!"), tr("Ok"));
            return false;
        }

        if (upperThresholdValue < lowerThresholdValue) {
            QMessageBox::warning(0, tr("Warning"), tr("Upper Threshold Value Can't Less Than Lower Threshold Value!\nSetting Invalid!"), tr("Ok"));
            return false;
        }
        g_tContext.m_tParamConfig.m_aAnalogParam[row].m_fUpperThresholdValue = string.toFloat();
    } else if (col == 7) {
        string = value.toString();
        double lowerThresholdValue = string.toDouble();
        double lowerLimitValue = g_tContext.m_tParamConfig.m_aAnalogParam[row].m_fLowerLimitValue;
        double upperThresholdValue = g_tContext.m_tParamConfig.m_aAnalogParam[row].m_fUpperThresholdValue;

        if (lowerThresholdValue > upperThresholdValue) {
            QMessageBox::warning(0, tr("Warning"), tr("Lower Threshold Value Can't More Than Upper Threshold Value!\nSetting Invalid!"), tr("Ok"));
            return false;
        }

        if (lowerThresholdValue < lowerLimitValue) {
            QMessageBox::warning(0, tr("Warning"), tr("Lower Threshold Value Can't Less Than Lower Limit Value!\nSetting Invalid!"), tr("Ok"));
            return false;
        }
        g_tContext.m_tParamConfig.m_aAnalogParam[row].m_fLowerThresholdValue = string.toFloat();
    } else if (col == 9) {
        byteArray = value.toByteArray();
#ifdef WIN32
        sprintf_s(g_tContext.m_tParamConfig.m_aAnalogParam[row].m_aFormula , "%s", byteArray.data());
#else
        sprintf(g_tContext.m_tParamConfig.m_aAnalogParam[row].m_aFormula , "%s", byteArray.data());
#endif
    }

    return true;
}

Qt::ItemFlags ModelAnalogConfig::flags(const QModelIndex &index) const
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

void ModelAnalogConfig::setChannelEnableStatus(int index, bool value)
{
    if (value) {
        if (QString(g_tContext.m_tParamConfig.m_aAnalogParam[index].m_aCode).isEmpty()) {
            QMessageBox::warning(0, tr("Warning"), tr("Invalid Setting!") + "\n" + tr("Channel Code Can't Be Empty!"), tr("Ok"));
            emit channelStatusChanged(index);
            return;
        }
    }
    g_tContext.m_tParamConfig.m_aAnalogParam[index].m_bInuse = value;
}

void ModelAnalogConfig::setChannelConvertFlag(int index, bool value)
{
    g_tContext.m_tParamConfig.m_aAnalogParam[index].m_uConvertFlag = value;
}

void ModelAnalogConfig::onConfigChanged()
{
    emit dataChanged(this->index(0, 0), this->index(this->rowCount(QModelIndex()), this->columnCount(QModelIndex())));
}

void ModelAnalogConfig::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timer) {
        for (int index = 0; index < ANALOG_CHANNEL_TOTAL_NUMBER; index++) {
            if (g_tContext.m_tParamConfig.m_aAnalogParam[index].m_bDataChanged) {
                g_tContext.m_tParamConfig.m_aAnalogParam[index].m_tMutex.lock();
                g_tContext.m_tParamConfig.m_aAnalogParam[index].m_bDataChanged = false;
                g_tContext.m_tParamConfig.m_aAnalogParam[index].m_tMutex.unlock();
                emit channelStatusChanged(index);
            }
        }
    }

    QAbstractTableModel::timerEvent(event);
}
