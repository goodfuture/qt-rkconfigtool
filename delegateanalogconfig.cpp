#include "delegateanalogconfig.h"

DelegateAnalogConfig::DelegateAnalogConfig(QObject *parent) :
    QStyledItemDelegate(parent)
{
    channelTypeList << tr("4-20mA")
                      << tr("0-5V");

}

QWidget *DelegateAnalogConfig::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &index) const
{
    if (index.column() == 0) {
        return NULL;
    }

    switch(index.column()) {
    case 2: {
        QComboBox *editor = new QComboBox(parent);
        editor->setFrame(false);
        editor->addItems(channelTypeList);
        return editor;
    }
    case 3: {
        CodeEditor *editor = new CodeEditor(parent);
        return editor;
    }
    case 4:
    case 5:
    case 6:
    case 7: {
        QLineEdit *editor = new QLineEdit(parent);
        editor->setFrame(false);

        QDoubleValidator *validator = new QDoubleValidator;
        //validator->setBottom(0);
        //validator->setDecimals(3);
        editor->setValidator(validator);
        //editor->setMaxLength(9);
        return editor;
    }
    case 9: {
        QLineEdit *editor = new QLineEdit(parent);
        editor->setFrame(false);
        editor->setMaxLength(63);
        return editor;
    }
    default:
        break;
    }

    return NULL;
}

void DelegateAnalogConfig::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int col = index.column();

    if (col == 0 || col == 1) {
        return;
    }

    QVariant value = index.model()->data(index, Qt::EditRole);
    switch(col) {
    case 2: {
        int sub_index = channelTypeList.indexOf(value.toString());
        if (sub_index < 0) {
            sub_index = 0;
        }
        QComboBox *combox = static_cast<QComboBox *>(editor);
        combox->setCurrentIndex(sub_index);
        break;
    }
    case 3: {
        CodeEditor *codeEditor = static_cast<CodeEditor *>(editor);
        codeEditor->setText(value.toString());
        break;
    }
    case 4:
    case 5:
    case 6:
    case 7:
    case 9: {
        QLineEdit *lineEdit = static_cast<QLineEdit *>(editor);
        lineEdit->setText(value.toString());
        break;
    }
    default:
        break;
    }
}

void DelegateAnalogConfig::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    int col = index.column();

    if (col == 0 || col == 1) {
        return;
    }

    switch(col) {
    case 2: {
        QComboBox *combox  = static_cast<QComboBox *>(editor);
        model->setData(index, combox->currentText(), Qt::EditRole);
        break;
    }
    case 3: {
        CodeEditor *codeEditor = static_cast<CodeEditor *>(editor);
        model->setData(index, codeEditor->text(), Qt::EditRole);
        break;
    }
    case 4: {
        QLineEdit *lineEdit = static_cast<QLineEdit *>(editor);
        model->setData(index, lineEdit->text(), Qt::EditRole);
        break;
    }
    case 5: {
        QLineEdit *lineEdit = static_cast<QLineEdit *>(editor);
        model->setData(index, lineEdit->text(), Qt::EditRole);
        break;
    }
    case 6: {
        QLineEdit *lineEdit = static_cast<QLineEdit *>(editor);
        model->setData(index, lineEdit->text(), Qt::EditRole);
        break;
    }
    case 7: {
        QLineEdit *lineEdit = static_cast<QLineEdit *>(editor);
        model->setData(index, lineEdit->text(), Qt::EditRole);
        break;
    }
    case 9: {
        QLineEdit *lineEdit = static_cast<QLineEdit *>(editor);
        model->setData(index, lineEdit->text(), Qt::EditRole);
        break;
    }
    default:
        break;
    }
}

void DelegateAnalogConfig::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const
{
    editor->setGeometry(option.rect);
}

void DelegateAnalogConfig::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem item_option(option);
    if (item_option.state & QStyle::State_HasFocus) {
        item_option.state ^= QStyle::State_HasFocus;
    }
    QStyledItemDelegate::paint(painter, item_option, index);
}
