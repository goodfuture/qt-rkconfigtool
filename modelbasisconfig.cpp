#include <QIcon>
#include <QDebug>
#include "modelbasisconfig.h"

ModelBasisConfig::ModelBasisConfig(QObject *parent) :
    QAbstractTableModel(parent)
{
    labelNameList << tr("SIM Card Number")
                    << tr("Device ID")
                    << tr("System Type")
                    << tr("Data Storage Interval")
                    << tr("Message Upload Mode")
                    << tr("Message Upload Interval")
                    << tr("Real Data Upload Enable")
                    << tr("Ten Minutes Statistical Data Upload Enable")
                    << tr("An Hour Statistical Data Upload Enable")
                    << tr("A Day Statistical Data Upload Enable")
                    << tr("DIO Status Data Upload Enable")
                    << tr("Alarm Data Upload Enable");

    sys_type_list << tr("Surface Water Monitor")
                  << tr("Air Quality Monitor")
                  << tr("Zone Noise Monitor")
                  << tr("Air Pollutant Source Monitor")
                  << tr("Surface Water Pollutant Source Monitor")
                  << tr("Underground Water Pollutant Source Monitor")
                  << tr("Ocean Environment Pollutant Source Monitor")
                  << tr("Soil Environment Pollutant Source Monitor")
                  << tr("Acoustical Environment Pollutant Source Monitor")
                  << tr("Vibration Environment Pollutant Source Monitor")
                  << tr("Radiation Environment Pollutant Source Monitor")
                  << tr("Electromagnetic Environment Pollutant Source Monitor")
                  << tr("System Interaction");

    sys_type_code_list << 21 << 22 << 23 << 31 << 32
                       << 33 << 34 << 35 << 36 << 37
                       << 38 << 41 << 91;

    rtd_storage_interval_list << QString("30") + tr("Second")
                              << QString("60") + tr("Second")
                              << QString("120") + tr("Second")
                              << QString("180") + tr("Second")
                              << QString("300") + tr("Second");

    msg_upload_mode_list << tr("DTU")
                         << tr("Ethernet")
                         << tr("DTU + Ethernet");

    msg_upload_interval_list << QString("30") + tr("Second")
                             << QString("60") + tr("Second")
                             << QString("120") + tr("Second")
                             << QString("180") + tr("Second")
                             << QString("300") + tr("Second");
    timer = startTimer(10);
}

int ModelBasisConfig::rowCount(const QModelIndex &) const
{
    return labelNameList.count();
}

int ModelBasisConfig::columnCount(const QModelIndex &) const
{
    return 2;
}

QVariant ModelBasisConfig::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        if (col == 0) {
            return labelNameList.at(row);
        }
        if (col == 1) {
            switch(row) {
            case 0:
                return QString(g_tContext.m_tParamConfig.m_tSysParam.m_aSim);
            case 1:
                return QString(g_tContext.m_tParamConfig.m_tSysParam.m_aMn);
            case 2: {
                int sys_type_index = sys_type_code_list.indexOf(g_tContext.m_tParamConfig.m_tSysParam.m_uSystemType);
                if (sys_type_index < 0) {
                    sys_type_index = 0;
                }
                return sys_type_list.at(sys_type_index);
            }
            case 3:
                return QString::number(g_tContext.m_tParamConfig.m_tSysParam.m_sRtdStorageInterval) + tr("Second");
            case 4: {
                int combox_index = g_tContext.m_tParamConfig.m_tSysParam.m_uMsgUploadMode % 3;
                if (combox_index < 0) {
                    combox_index = 0;
                }
                return msg_upload_mode_list.at(combox_index);
            }
            case 5:
                return QString::number(g_tContext.m_tParamConfig.m_tSysParam.m_sMsgUploadInterval) + tr("Second");
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            default:
                break;
            }
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

bool ModelBasisConfig::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int row = index.row();
    int col = index.column();

    if (col == 0 || role != Qt::EditRole) {
        return false;
    }

    QByteArray byteArray;
    switch(row) {
    case 0:
        byteArray = value.toByteArray();
        sprintf_s(g_tContext.m_tParamConfig.m_tSysParam.m_aSim, "%s", byteArray.data());
        return true;
    case 1:
        byteArray = value.toByteArray();
        sprintf_s(g_tContext.m_tParamConfig.m_tSysParam.m_aMn, "%s", byteArray.data());
        return true;
    case 2: {
        int sys_type_index = sys_type_list.indexOf(value.toString());
        if (sys_type_index < 0) {
            sys_type_index = 0;
        }
        g_tContext.m_tParamConfig.m_tSysParam.m_uSystemType = sys_type_code_list.at(sys_type_index);
        return true;
    }
    case 3: {
        QString string = value.toString();
        string.remove(tr("Second"));
        g_tContext.m_tParamConfig.m_tSysParam.m_sRtdStorageInterval = string.toInt();
        return true;
    }
    case 4: {
        g_tContext.m_tParamConfig.m_tSysParam.m_uMsgUploadMode = msg_upload_mode_list.indexOf(value.toString());
        return true;
    }
    case 5: {
        QString string = value.toString();
        string.remove(tr("Second"));
        g_tContext.m_tParamConfig.m_tSysParam.m_sMsgUploadInterval = string.toInt();
        return true;
    }
    default:
        break;
    }

    return false;
}

Qt::ItemFlags ModelBasisConfig::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);

    if (index.isValid() && index.column() == 1) {
        flags |= Qt::ItemIsEditable;
    }

    return flags;
}

void ModelBasisConfig::setModelEnableStatus(int id, bool enable)
{
    switch(id) {
    case 0:
        g_tContext.m_tParamConfig.m_tSysParam.m_bRtdUpload = !enable ? 0 : 1;
        break;
    case 1:
        g_tContext.m_tParamConfig.m_tSysParam.m_bTmdUpload = !enable ? 0 : 1;
        break;
    case 2:
        g_tContext.m_tParamConfig.m_tSysParam.m_bHsdUpload = !enable ? 0 : 1;
        break;
    case 3:
        g_tContext.m_tParamConfig.m_tSysParam.m_bDsdUpload = !enable ? 0 : 1;
        break;
    case 4:
        g_tContext.m_tParamConfig.m_tSysParam.m_bSwitchSense = !enable ? 0 : 1;
        break;
    case 5:
        g_tContext.m_tParamConfig.m_tSysParam.m_bAlarmEnable = !enable ? 0 : 1;
        break;
    default:
        break;
    }
    /*
    qDebug() << "Start";
    qDebug() << id << enable;
    qDebug() << g_tContext.m_tParamConfig.m_tSysParam.m_bRtdUpload;
    qDebug() << g_tContext.m_tParamConfig.m_tSysParam.m_bTmdUpload;
    qDebug() << g_tContext.m_tParamConfig.m_tSysParam.m_bHsdUpload;
    qDebug() << g_tContext.m_tParamConfig.m_tSysParam.m_bDsdUpload;
    qDebug() << g_tContext.m_tParamConfig.m_tSysParam.m_bSwitchSense;
    qDebug() << g_tContext.m_tParamConfig.m_tSysParam.m_bAlarmEnable;
    */
}

void ModelBasisConfig::onConfigChanged()
{
    emit dataChanged(this->index(0, 0), this->index(this->rowCount(QModelIndex()), this->columnCount(QModelIndex())));
}

void ModelBasisConfig::onDataEnableStatusChanged()
{
    bool status;
    status = !g_tContext.m_tParamConfig.m_tSysParam.m_bRtdUpload ? false : true;
    emit setViewEnableStatus(0, status);
    status = !g_tContext.m_tParamConfig.m_tSysParam.m_bTmdUpload ? false : true;
    emit setViewEnableStatus(1, status);
    status = !g_tContext.m_tParamConfig.m_tSysParam.m_bHsdUpload ? false : true;
    emit setViewEnableStatus(2, status);
    status = !g_tContext.m_tParamConfig.m_tSysParam.m_bDsdUpload ? false : true;
    emit setViewEnableStatus(3, status);
    status = !g_tContext.m_tParamConfig.m_tSysParam.m_bSwitchSense ? false : true;
    emit setViewEnableStatus(4, status);
    status = !g_tContext.m_tParamConfig.m_tSysParam.m_bAlarmEnable ? false : true;
    emit setViewEnableStatus(5, status);
}

void ModelBasisConfig::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timer && g_tContext.m_tParamConfig.m_tSysParam.m_bDataChanged) {
        g_tContext.m_tParamConfig.m_tSysParam.m_tMutex.lock();
        g_tContext.m_tParamConfig.m_tSysParam.m_bDataChanged = false;
        g_tContext.m_tParamConfig.m_tSysParam.m_tMutex.unlock();

        onDataEnableStatusChanged();
    }
    QAbstractTableModel::timerEvent(event);
}
