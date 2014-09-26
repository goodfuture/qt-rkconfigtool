#ifndef MODELBASISCONFIG_H
#define MODELBASISCONFIG_H

#include "common.h"
#include "messagehandler.h"

#include <QMap>
#include <QList>
#include <stdio.h>
#include <QTimer>
#include <QVariant>
#include <QByteArray>
#include <QStringList>
#include <QTimerEvent>
#include <QAbstractTableModel>

extern Context_t g_tContext;

class ModelBasisConfig : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ModelBasisConfig(QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;

public slots:
    void setModelEnableStatus(int id, bool enable);
    void onDataEnableStatusChanged();
    void onConfigChanged();

signals:
    void setViewEnableStatus(int, bool);

private:
    int	timer;
    QStringList labelNameList;
    QStringList sys_type_list;
    QList<int> 	sys_type_code_list;
    QStringList rtd_storage_interval_list;
    QStringList msg_upload_mode_list;
    QStringList msg_upload_interval_list;

protected:
    void timerEvent(QTimerEvent *);

};

#endif // MODELBASISCONFIG_H
