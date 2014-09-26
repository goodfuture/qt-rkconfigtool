#include "delegateserialconfig.h"

DelegateSerialConfig::DelegateSerialConfig(QObject *parent) :
    QStyledItemDelegate(parent)
{
    for (int i = 0; i < COM_485_PORT_NUMBER; i++) {
        com_id_list.append(tr("Com Port") + QString::number(i + 1));
    }

    data_type_list << tr("Integer")
                   << tr("Float");
}

QWidget *DelegateSerialConfig::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &index) const
{
    int col = index.column();

    switch(col) {
    case 0:
    case 1:
    case 11:
        return NULL;
    case 2: {
        CodeEditor *editor = new CodeEditor(parent);
        return editor;
    }
    case 3: {
        QComboBox *editor = new QComboBox(parent);
        editor->addItems(com_id_list);
        return editor;
    }
    case 4: {
        QComboBox *editor = new QComboBox(parent);
        editor->addItems(data_type_list);
        return editor;
    }
    case 5: {
        QLineEdit *editor = new QLineEdit(parent);
        editor->setValidator(new QIntValidator(0, 255));
        //editor->setPlaceholderText(tr("Device Address Range From 0 To 255"));
        return editor;
    }
    case 6: {
        QLineEdit *editor = new QLineEdit(parent);
        editor->setValidator(new QIntValidator(0, 65535));
        //editor->setPlaceholderText(tr("Register Address Range From 0 To 65535"));
        return editor;
    }
    case 7:
    case 8:
    case 9:
    case 10: {
        QLineEdit *editor = new QLineEdit(parent);
        QDoubleValidator *validator = new QDoubleValidator;
        validator->setBottom(0);
        //validator->setDecimals(3);
        editor->setValidator(validator);
        //editor->setMaxLength(9);
        return editor;
    }
    case 12: {
        QLineEdit *editor = new QLineEdit(parent);
        editor->setMaxLength(63);
        return editor;
    }
    default:
        break;
    }

    return NULL;
}

void DelegateSerialConfig::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int col = index.column();
    QVariant value = index.model()->data(index, Qt::EditRole);
    if (col == 2) {
        CodeEditor *codeEditor = static_cast<CodeEditor *>(editor);
        codeEditor->setText(value.toString());
    } else if ((col >= 5 && col <= 10) || col == 12) {
        QLineEdit *lineEdit = static_cast<QLineEdit *>(editor);
        lineEdit->setText(value.toString());
    } else if (col == 3) {
        int sub_index = com_id_list.indexOf(value.toString());
        if (sub_index < 0) {
            sub_index = 0;
        }
        QComboBox *combox = static_cast<QComboBox *>(editor);
        combox->setCurrentIndex(sub_index);
    } else if (col == 4) {
        int sub_index = data_type_list.indexOf(value.toString());
        if (sub_index < 0) {
            sub_index = 0;
        }
        QComboBox *combox = static_cast<QComboBox *>(editor);
        combox->setCurrentIndex(sub_index);
    }
}

void DelegateSerialConfig::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    int col = index.column();

    if (col == 2) {
        CodeEditor *codeEditor = static_cast<CodeEditor *>(editor);
        model->setData(index, codeEditor->text(), Qt::EditRole);
    } else if ((col >= 5 && col <= 10) || col == 12) {
        QLineEdit *lineEdit = static_cast<QLineEdit *>(editor);
        model->setData(index, lineEdit->text(), Qt::EditRole);
    } else if (col == 3 || col == 4) {
        QComboBox *combox = static_cast<QComboBox *>(editor);
        model->setData(index, combox->currentText(), Qt::EditRole);
    }
}

void DelegateSerialConfig::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const
{
    editor->setGeometry(option.rect);
}

void DelegateSerialConfig::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem item_option(option);
    if (item_option.state & QStyle::State_HasFocus) {
        item_option.state ^= QStyle::State_HasFocus;
    }
    QStyledItemDelegate::paint(painter, item_option, index);
}
