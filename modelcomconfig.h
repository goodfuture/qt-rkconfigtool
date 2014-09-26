#ifndef MODELCOMCONFIG_H
#define MODELCOMCONFIG_H

#include "common.h"

#include <QIcon>
#include <QVariant>
#include <QCheckBox>
#include <QStringList>
#include <QAbstractTableModel>

extern Context_t g_tContext;

class ModelComConfig : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ModelComConfig(QObject *parent = 0);
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
    QStringList baud_rate_list;
    QStringList data_bit_list;
    QStringList stop_bit_list;
    QStringList parity_list;
    QStringList protocol_list;

};

#endif // MODELCOMCONFIG_H
