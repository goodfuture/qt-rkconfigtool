#ifndef BASICPARAMDELEGATE_H
#define BASICPARAMDELEGATE_H

#include <QWidget>
#include <QLineEdit>
#include <QStyledItemDelegate>

class BasicParamDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit BasicParamDelegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

signals:

public slots:

protected:
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

};

#endif // BASICPARAMDELEGATE_H
