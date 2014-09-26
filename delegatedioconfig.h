#ifndef DELEGATEDIOCONFIG_H
#define DELEGATEDIOCONFIG_H

#include <QString>
#include <QWidget>
#include <QLineEdit>
#include <QValidator>
#include <QStyledItemDelegate>

class DelegateDioConfig : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit DelegateDioConfig(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

signals:

public slots:
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

};

#endif // DELEGATEDIOCONFIG_H
