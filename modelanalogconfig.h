#ifndef MODELANALOGCONFIG_H
#define MODELANALOGCONFIG_H

#include <QIcon>
#include <QDebug>
#include <QStringList>
#include <QTimerEvent>
#include <QMessageBox>
#include <QAbstractTableModel>

#include "common.h"

extern Context_t g_tContext;

class ModelAnalogConfig : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ModelAnalogConfig(QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;

signals:
    void channelStatusChanged(int);

public slots:
    void onConfigChanged();
    void timerEvent(QTimerEvent *);
    void setChannelEnableStatus(int, bool);
    void setChannelConvertFlag(int, bool);

private:
    int timer;
    QStringList label_name_list;
    QStringList channel_type_list;

};

#endif // MODELANALOGCONFIG_H
