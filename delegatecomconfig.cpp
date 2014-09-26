#include "delegatecomconfig.h"

DelegateComConfig::DelegateComConfig(QObject *parent) :
    QStyledItemDelegate(parent)
{
    baudRateList << QString("1200")
                   << QString("2400")
                   << QString("4800")
                   << QString("9600")
                   << QString("14400")
                   << QString("19200")
                   << QString("38400")
                   << QString("57600")
                   << QString("115200");

    dataBitList << QString("5") + tr("bit")
                  << QString("6") + tr("bit")
                  << QString("7") + tr("bit")
                  << QString("8") + tr("bit");

    stopBitList << QString("1") + tr("bit")
                  << QString("2") + tr("bit");

    parityBitList << tr("None")
                << tr("Odd")
                << tr("Even");

    protocolList.clear();
}

QWidget *DelegateComConfig::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &index) const
{
    int col = index.column();

    switch(col) {
    case 1: {
        QComboBox *editor = new QComboBox(parent);
        editor->setFrame(false);
        editor->addItems(baudRateList);
        return editor;
    }
    case 2: {
        QComboBox *editor = new QComboBox(parent);
        editor->setFrame(false);
        editor->addItems(dataBitList);
        return editor;
    }
    case 3: {
        QComboBox *editor = new QComboBox(parent);
        editor->setFrame(false);
        editor->addItems(stopBitList);
        return editor;
    }
    case 4: {
        QComboBox *editor = new QComboBox(parent);
        editor->setFrame(false);
        editor->addItems(parityBitList);
        return editor;
    }
    case 5: {
        QComboBox *editor = new QComboBox(parent);
        editor->setFrame(false);
        editor->addItems(protocolList);
        return editor;
    }
    default:
        break;
    }

    return NULL;
}

void DelegateComConfig::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int col = index.column();

    if (col == 0) {
        return;
    }

    QVariant value = index.model()->data(index, Qt::EditRole);
    if(col == 1) {
        QComboBox *combox = static_cast<QComboBox *>(editor);
        int sub_index = baudRateList.indexOf(value.toString());
        if (sub_index < 0) {
            sub_index = 0;
        }
        combox->setCurrentIndex(sub_index);
    } else if (col == 2) {
        QComboBox *combox = static_cast<QComboBox *>(editor);
        int sub_index = dataBitList.indexOf(value.toString());
        if (sub_index < 0) {
            sub_index = 0;
        }
        combox->setCurrentIndex(sub_index);
    } else if (col == 3) {
        QComboBox *combox = static_cast<QComboBox *>(editor);
        int sub_index = stopBitList.indexOf(value.toString());
        if (sub_index < 0) {
            sub_index = 0;
        }
        combox->setCurrentIndex(sub_index);
    } else if (col == 4) {
        QComboBox *combox = static_cast<QComboBox *>(editor);
        int sub_index = parityBitList.indexOf(value.toString());
        if (sub_index < 0) {
            sub_index = 0;
        }
        combox->setCurrentIndex(sub_index);
    } else if (col == 5) {
        QComboBox *combox = static_cast<QComboBox *>(editor);
        combox->clear();
        combox->addItems(protocolList);
        int sub_index = protocolList.indexOf(value.toString());
        if (sub_index < 0) {
            sub_index = 0;
        }
        combox->setCurrentIndex(sub_index);
    }
}

void DelegateComConfig::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    int col = index.column();

    if (col == 1 || col == 2 || col == 3 || col == 4 || col == 5) {
        QComboBox *combox = static_cast<QComboBox *>(editor);
        model->setData(index, combox->currentText(), Qt::EditRole);
    }
}

void DelegateComConfig::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const
{
    editor->setGeometry(option.rect);
}

void DelegateComConfig::onResetDynamicProtocolSet()
{
    protocolList.clear();
    protocolList << QString(g_tContext.m_aDynamicProtocolSet).split(",", QString::SkipEmptyParts);
}

void DelegateComConfig::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem item_option(option);
    if (item_option.state & QStyle::State_HasFocus) {
        item_option.state ^= QStyle::State_HasFocus;
    }
    QStyledItemDelegate::paint(painter, item_option, index);
}
