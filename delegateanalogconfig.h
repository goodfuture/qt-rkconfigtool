#ifndef DELEGATEANALOGCONFIG_H
#define DELEGATEANALOGCONFIG_H

#include <QWidget>
#include <QRegExp>
#include <QString>
#include <QComboBox>
#include <QLineEdit>
#include <QValidator>
#include <QStringList>
#include <QHBoxLayout>
#include <QDoubleValidator>
#include <QRegExpValidator>
#include <QStyledItemDelegate>

#include "codeeditor.h"

class DelegateAnalogConfig : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit DelegateAnalogConfig(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

signals:

protected:
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

public slots:

private:
    QStringList channelTypeList;
};

#endif // DELEGATEANALOGCONFIG_H
