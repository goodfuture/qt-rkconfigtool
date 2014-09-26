#include "spinboxdelegate.h"

SpinBoxDelegate::SpinBoxDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

QWidget *SpinBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSpinBox *editor = new QSpinBox(parent);
    editor->setFrame(false);

    return editor;
}

void SpinBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int value = index.model()->data(index, Qt::EditRole).toInt();
    QSpinBox *spin_box = static_cast<QSpinBox *>(editor);
    spin_box->setValue(value);
}

void SpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QSpinBox *spin_box = static_cast<QSpinBox *>(editor);
    spin_box->interpretText();
    int value = spin_box->value();
    model->setData(index, value, Qt::EditRole);
}

void SpinBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
