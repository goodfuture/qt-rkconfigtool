#ifndef BASICPARAMMODEL_H
#define BASICPARAMMODEL_H

#include <QAbstractTableModel>
#include <QVariant>
#include <QStringList>

class BasicParamModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit BasicParamModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

signals:

public slots:

private:
    QStringList label_name_list;

};

#endif // BASICPARAMMODEL_H
