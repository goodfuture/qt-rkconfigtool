#include "basicparammodel.h"
#include <QDebug>
#include <QIcon>

BasicParamModel::BasicParamModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    label_name_list << tr("SIM Card Number")
                    << tr("Device ID")
                    << tr("System Type")
                    << tr("Data Storage Interval")
                    << tr("Message Upload Interval")
                    << tr("Message Upload Mode")
                    << tr("Real Data Upload Enable")
                    << tr("Real Data Upload Enable")
                    << tr("Ten Minutes Statistical Data Upload Enable")
                    << tr("An Hour Statistical Data Upload Enable")
                    << tr("A Day Statistical Data Upload Enable")
                    << tr("DIO Status Data Upload Enable")
                    << tr("Alarm Data Upload Enable");
}

int BasicParamModel::rowCount(const QModelIndex &) const
{
    return label_name_list.count();
}

int BasicParamModel::columnCount(const QModelIndex &) const
{
    return 2;
}

QVariant BasicParamModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

#if 0
    qDebug() << QString("row %1, col %2, role %3")
                .arg(row).arg(col).arg(role);
#endif

    switch(role) {
    case Qt::DisplayRole:
        if (col == 0) {
            return label_name_list.at(row);
        } else {
        }
        break;
    case Qt::DecorationRole:
        if (col == 0) {
            return QIcon(QString(":/flag/flag_blue"));
        }
        break;
    case Qt::EditRole:
        break;
    case Qt::ToolTipRole:
        break;
    case Qt::StatusTipRole:
        break;
    case Qt::WhatsThisRole:
        break;
    case Qt::SizeHintRole:
        break;
    case Qt::FontRole:
        break;
    case Qt::TextAlignmentRole:
        return Qt::AlignCenter;
        //break;
    case Qt::BackgroundRole:
        break;
    case Qt::ForegroundRole:
        break;
    case Qt::CheckStateRole:
        break;
    }

    return QVariant();
}
