#ifndef MODELSERIALCONFIG_H
#define MODELSERIALCONFIG_H

#include <QIcon>
#include <QColor>
#include <QDebug>
#include <QVariant>
#include <QTimerEvent>
#include <QStringList>
#include <QMessageBox>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QAbstractTableModel>

#include "common.h"

extern Context_t g_tContext;

class ModelSerialConfig : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ModelSerialConfig(QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

signals:
    void channelStatusChanged(int);

public slots:
    void onConfigChanged();
    void timerEvent(QTimerEvent *);
    void setChannelEnableStatus(int, bool);
    void setChannelConvertFlag(int, bool);

private:
    int	timer;
    QStringList label_name_list;
    QStringList com_id_list;
    QStringList data_type_list;
};

#endif // MODELSERIALCONFIG_H
