#ifndef MODELNETCONFIG_H
#define MODELNETCONFIG_H

#include "common.h"

#include <QIcon>
#include <QVariant>
#include <QByteArray>
#include <QStringList>
#include <QAbstractTableModel>
#include <QAbstractItemModel>

extern Context_t g_tContext;

class ModelNetConfig : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ModelNetConfig(QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;

signals:

public slots:
    void onConfigChanged();

private:
    QStringList label_name_list;
    QStringList link_mode_list;

};

#endif // MODELNETCONFIG_H
