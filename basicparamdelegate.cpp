#include "basicparamdelegate.h"

BasicParamDelegate::BasicParamDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

QWidget *BasicParamDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &index) const
{
    int row = index.row();
    int col = index.column();

    if (col == 0) {
        return NULL;
    }

    if (row == 0) {
        QLineEdit *editor = new QLineEdit(parent);
        editor->setFrame(false);
        return editor;
    }
}

void BasicParamDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int row = index.row();
    int col = index.column();

    if (col == 0) {
        return;
    }

    if (row == 0) {
        QLineEdit *line_edit = static_cast<QLineEdit *>(editor);
        line_edit->setText("yes");
    }
}

void BasicParamDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    int row = index.row();
    int col = index.column();

    if (col == 0) {
        return;
    }

    if (row == 0) {
        QLineEdit *line_edit = static_cast<QLineEdit *>(editor);
        model->setData(index, line_edit->text(), Qt::EditRole);
    }
}

void BasicParamDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int row = index.row();
    int col = index.column();

    if (col == 0) {
        return;
    }

    if (row == 0) {
        editor->setGeometry(option.rect);
    }
}

void BasicParamDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem item_option(option);
    if (item_option.state & QStyle::State_HasFocus) {
        item_option.state ^= QStyle::State_HasFocus;
    }
    QStyledItemDelegate::paint(painter, item_option, index);
}
