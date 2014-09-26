#ifndef DELEGATENETCONFIG_H
#define DELEGATENETCONFIG_H

#include <QRegExp>
#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QValidator>
#include <QStringList>
#include <QIntValidator>
#include <QRegExpValidator>
#include <QStyledItemDelegate>

class DelegateNetConfig : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit DelegateNetConfig(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

signals:

protected:
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

public slots:

private:
    QStringList link_mode_list;

};

#endif // DELEGATENETCONFIG_H
