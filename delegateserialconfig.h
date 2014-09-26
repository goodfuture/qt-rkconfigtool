#ifndef DELEGATESERIALCONFIG_H
#define DELEGATESERIALCONFIG_H

#include "common.h"
#include "codeeditor.h"

#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QStringList>
#include <QValidator>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QStyledItemDelegate>

class DelegateSerialConfig : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit DelegateSerialConfig(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

signals:

public slots:
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    QStringList com_id_list;
    QStringList data_type_list;

};

#endif // DELEGATESERIALCONFIG_H
