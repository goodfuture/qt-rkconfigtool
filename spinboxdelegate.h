#ifndef SPINBOXDELEGATE_H
#define SPINBOXDELEGATE_H

#include <QSpinBox>
#include <QWidget>
#include <QStyledItemDelegate>

class SpinBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit SpinBoxDelegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

signals:

public slots:

protected:

};

#endif // SPINBOXDELEGATE_H
