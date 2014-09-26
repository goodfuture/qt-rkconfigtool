#include "delegatedioconfig.h"

DelegateDioConfig::DelegateDioConfig(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

QWidget *DelegateDioConfig::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &index) const
{
    int col = index.column();

    if (col == 0) {
        return NULL;
    }

    if (col == 2) {
        QLineEdit *editor = new QLineEdit(parent);
        editor->setFrame(false);
        editor->setMaxLength(7);
        return editor;
    }

    return NULL;
}

void DelegateDioConfig::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QVariant value = index.model()->data(index, Qt::EditRole);

    int col = index.column();
    if (col == 2) {
        QLineEdit *line_edit = static_cast<QLineEdit *>(editor);
        line_edit->setText(value.toString());
    }
}

void DelegateDioConfig::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    int col = index.column();
    if (col == 2) {
        QLineEdit *line_edit = static_cast<QLineEdit *>(editor);
        model->setData(index, line_edit->text(), Qt::EditRole);
    }
}

void DelegateDioConfig::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const
{
    editor->setGeometry(option.rect);
}

void DelegateDioConfig::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem item_option(option);
    if (item_option.state & QStyle::State_HasFocus) {
        item_option.state ^= QStyle::State_HasFocus;
    }
    QStyledItemDelegate::paint(painter, item_option, index);
}
