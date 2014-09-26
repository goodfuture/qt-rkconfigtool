#ifndef MODELDIOCONFIG_H
#define MODELDIOCONFIG_H

#include "common.h"

#include <QIcon>
#include <QDebug>
#include <QWidget>
#include <QVariant>
#include <QByteArray>
#include <QStringList>
#include <QTimerEvent>
#include <QMessageBox>
#include <QAbstractTableModel>

extern Context_t g_tContext;

class ModelDioConfig : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ModelDioConfig(QObject *parent = 0);
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
    void setDigitalOutputStatus(int, bool);

private:
    int	timer;
    QStringList labelNameList;

};

#endif // MODELDIOCONFIG_H
