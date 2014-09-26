#ifndef MODELDTUCONFIG_H
#define MODELDTUCONFIG_H

#include <QMap>
#include <QList>
#include <QIcon>
#include <QDebug>
#include <QVariant>
#include <QStringList>
#include <QAbstractTableModel>

class ModelDtuConfig : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ModelDtuConfig(QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

signals:

public slots:
    void onConfigChanged();

private:
    bool 		superUser;
    QMap<int, QString> posNameMap;
    QStringList headerNameList;
    QStringList paramNameList;
    QStringList paramGroupNameList;
    QStringList comParamNameList;
    QStringList	modeParamNameList;
    QStringList gprsParamNameList;
    QStringList platformParamNameList;
    QStringList companyParamNameList;
    QStringList multiCenterParamNameList;
    QStringList multiLinkParamNameList;
    QStringList expandParamNameList;

};

#endif // MODELDTUCONFIG_H
