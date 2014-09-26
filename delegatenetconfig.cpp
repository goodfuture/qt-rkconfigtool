#include "delegatenetconfig.h"

DelegateNetConfig::DelegateNetConfig(QObject *parent) :
    QStyledItemDelegate(parent)
{
    link_mode_list << tr("TCP Client")
                    << tr("UDP Client");
}

QWidget *DelegateNetConfig::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &index) const
{
    int row = index.row();
    int col = index.column();

    if (col == 0) {
        return NULL;
    }

    switch(row) {
    case 0: {
        QComboBox *editor = new QComboBox(parent);
        editor->setFrame(false);
        editor->addItems(link_mode_list);
        return editor;
    }
    case 1: {
        QLineEdit *editor = new QLineEdit(parent);
        editor->setFrame(false);
        QString reg_exp("([1-9]|[1-9]\\d|1\\d{2}|2[0-4]\\d|25[0-5])(\\.(\\d|[1-9]\\d|1\\d{2}|2[0-4]\\d|25[0-5])){3}");
        QValidator *validator = new QRegExpValidator(QRegExp(reg_exp));
        editor->setValidator(validator);
        editor->setPlaceholderText(tr("Enter Dotted Decimal Device IP Address"));
        return editor;
    }
    case 2: {
        QLineEdit *editor = new QLineEdit(parent);
        editor->setFrame(false);
        QString reg_exp("([1-9]|[1-9]\\d|1\\d{2}|2[0-4]\\d|25[0-5])(\\.(\\d|[1-9]\\d|1\\d{2}|2[0-4]\\d|25[0-5])){3}");
        QValidator *validator = new QRegExpValidator(QRegExp(reg_exp));
        editor->setValidator(validator);
        editor->setPlaceholderText(tr("Enter Device IP Address NetMask"));
        return editor;
    }
    case 3: {
        QLineEdit *editor = new QLineEdit(parent);
        editor->setFrame(false);
        QString reg_exp("([1-9]|[1-9]\\d|1\\d{2}|2[0-4]\\d|25[0-5])(\\.(\\d|[1-9]\\d|1\\d{2}|2[0-4]\\d|25[0-5])){3}");
        QValidator *validator = new QRegExpValidator(QRegExp(reg_exp));
        editor->setValidator(validator);
        editor->setPlaceholderText(tr("Enter Dotted Decimal Remote IP Address"));
        return editor;
    }
    case 4: {
        QLineEdit *editor = new QLineEdit(parent);
        editor->setFrame(false);
        /*
        editor->setMaxLength(5);
        QString reg_exp("^[1-9]$|(^[1-9][0-9]$)|(^[1-9][0-9][0-9]$)|(^[1-9][0-9][0-9][0-9]$)|(^[1-6][0-5][0-5][0-3][0-5]$)");
        QValidator *validator = new QRegExpValidator(QRegExp(reg_exp));
        editor->setValidator(validator);
        */
        editor->setValidator(new QIntValidator(1, 65535));
        editor->setPlaceholderText(tr("Enter Remote Port"));
        return editor;
    }
    default:
        break;
    }
    return NULL;
}

void DelegateNetConfig::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int row = index.row();
    int col = index.column();

    if (col == 0) {
        return;
    }

    QVariant value = index.model()->data(index, Qt::EditRole);
    switch(row) {
    case 0: {
        QComboBox *combox = static_cast<QComboBox *>(editor);
        int sub_index = link_mode_list.indexOf(value.toString());
        if (sub_index < 0) {
            sub_index = 0;
        }
        combox->setCurrentIndex(sub_index);
        break;
    }
    case 1:
    case 2:
    case 3:
    case 4: {
        QLineEdit *line_edit = static_cast<QLineEdit *>(editor);
        line_edit->setText(value.toString());
        break;
    }
    default:
        break;
    }
}

void DelegateNetConfig::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    int row = index.row();
    int col = index.column();

    if (col == 0) {
        return;
    }

    switch(row) {
    case 0: {
        QComboBox *combox = static_cast<QComboBox *>(editor);
        model->setData(index, combox->currentText(), Qt::EditRole);
        break;
    }
    case 1:
    case 2:
    case 3:
    case 4: {
        QLineEdit *line_edit = static_cast<QLineEdit *>(editor);
        model->setData(index, line_edit->text(), Qt::EditRole);
        break;
    }
    default:
        break;
    }
}

void DelegateNetConfig::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const
{
    editor->setGeometry(option.rect);
}

void DelegateNetConfig::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem item_option(option);
    if (item_option.state & QStyle::State_HasFocus) {
        item_option.state ^= QStyle::State_HasFocus;
    }
    QStyledItemDelegate::paint(painter, item_option, index);
}
