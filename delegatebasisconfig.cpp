#include "delegatebasisconfig.h"

DelegateBasisConfig::DelegateBasisConfig(QObject *parent) :
    QStyledItemDelegate(parent)
{
    sysTypeList << tr("Surface Water Monitor")
                  << tr("Air Quality Monitor")
                  << tr("Zone Noise Monitor")
                  << tr("Air Pollutant Source Monitor")
                  << tr("Surface Water Pollutant Source Monitor")
                  << tr("Underground Water Pollutant Source Monitor")
                  << tr("Ocean Environment Pollutant Source Monitor")
                  << tr("Soil Environment Pollutant Source Monitor")
                  << tr("Acoustical Environment Pollutant Source Monitor")
                  << tr("Vibration Environment Pollutant Source Monitor")
                  << tr("Radiation Environment Pollutant Source Monitor")
                  << tr("Electromagnetic Environment Pollutant Source Monitor")
                  << tr("System Interaction");

    rtdStorageIntervalList << QString("30") + tr("Second")
                              << QString("60") + tr("Second")
                              << QString("120") + tr("Second")
                              << QString("180") + tr("Second")
                              << QString("300") + tr("Second");

    msgUploadModeList << tr("DTU")
                         << tr("Ethernet")
                         << tr("DTU + Ethernet");

    msg_upload_interval_list << QString("30") + tr("Second")
                             << QString("60") + tr("Second")
                             << QString("120") + tr("Second")
                             << QString("180") + tr("Second")
                             << QString("300") + tr("Second");
}

QWidget *DelegateBasisConfig::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &index) const
{
    int row = index.row();
    int col = index.column();

    if (col == 0) {
        return NULL;
    }

    switch(row) {
    case 0: { /* SIM */
        QLineEdit *editor = new QLineEdit(parent);
        editor->setPlaceholderText(tr("Enter Sim Card Number"));
        editor->setValidator(new QRegExpValidator(QRegExp(QString("^[0-9]{0,11}$"))));
        editor->setFrame(false);
        return editor; }
    case 1: { /* Device ID */
        QLineEdit *editor = new QLineEdit(parent);
        editor->setPlaceholderText(tr("Enter Device ID"));
        //QValidator *validator = new
        editor->setValidator(new QRegExpValidator(QRegExp(QString("^[0-9]{0,14}$"))));
        editor->setFrame(false);
        return editor; }
    case 2: { /* System Type */
        QComboBox *editor = new QComboBox(parent);
        editor->addItems(sysTypeList);
        editor->setMaxVisibleItems(5);
        editor->setFrame(false);
        return editor; }
    case 3: { /* Data Storage Interval */
        QComboBox *editor = new QComboBox(parent);
        editor->addItems(rtdStorageIntervalList);
        editor->setFrame(false);
        return editor; }
    case 4: { /* Message Upload Mode */
        QComboBox *editor = new QComboBox(parent);
        editor->addItems(msgUploadModeList);
        editor->setFrame(false);
        return editor; }
    case 5: { /* Message Upload Interval */
        QComboBox *editor = new QComboBox(parent);
        editor->addItems(msg_upload_interval_list);
        editor->setFrame(false);
        return editor; }
    case 6: /* Rtd Message Upload Enable */
    case 7: /* Ten-minutes Message Upload Enable */
    case 8: /* Hour Message Upload Enable */
    case 9: /* Day Message Upload Enable */
    case 10: /* Switch-Sense Message Upload Enable */
    case 11: { /* Alarm Message Upload Enable */
        /*
        QWidget *item_widget = new QWidget(parent);
        QHBoxLayout *h_layout = new QHBoxLayout(item_widget);
        h_layout->setContentsMargins(0, 0, 0, 0);
        SwitchButton *switch_button = new SwitchButton(item_widget);
        h_layout->addWidget(switch_button, 0, Qt::AlignCenter);
        return item_widget;
        */
    }
    default:
        return NULL;
    }
}

void DelegateBasisConfig::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int row = index.row();
    int col = index.column();

    if (col == 0) {
        return;
    }

    QVariant value = index.model()->data(index, Qt::EditRole);

    switch(row) {
    case 0:
    case 1: {
        QLineEdit *line_edit = static_cast<QLineEdit *>(editor);
        line_edit->setText(value.toString());
        break;
    }
    case 2:
    case 3:
    case 4:
    case 5: {
        QComboBox *combox = static_cast<QComboBox *>(editor);
        combox->setCurrentText(value.toString());
        break;
    }
    default:
        break;
    }
}

void DelegateBasisConfig::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    int row = index.row();
    int col = index.column();

    if (col == 0) {
        return;
    }

    switch(row) {
    case 0: {
        QLineEdit *line_edit = static_cast<QLineEdit *>(editor);
        int len = line_edit->text().length();
        if ( len > 0 && len != 11) {
            QMessageBox::warning(0, tr("Warning"), tr("Sim Number Must Have 11 Digits!"), tr("Ok"));
        } else {
            model->setData(index, line_edit->text(), Qt::EditRole);
        }
        break;
    }
    case 1: {
        QLineEdit *line_edit = static_cast<QLineEdit *>(editor);
        int len = line_edit->text().length();
        if (len > 0 && len != 14) {
            QMessageBox::warning(0, tr("Warning"), tr("MN Number Must Have 14 Digits!"), tr("Ok"));
        } else {
            model->setData(index, line_edit->text(), Qt::EditRole);
        }
        break;
    }
    case 2:
    case 3:
    case 4:
    case 5: {
        QComboBox *combox = static_cast<QComboBox *>(editor);
        model->setData(index, combox->currentText(), Qt::EditRole);
        break;
    }
    default:
        break;
    }
}

void DelegateBasisConfig::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int col = index.column();

    if (col == 0) {
        return;
    }

#if 0
    if (row == 0) {
        editor->setGeometry(option.rect);
    }
#endif
    editor->setGeometry(option.rect);
}

void DelegateBasisConfig::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem item_option(option);
    if (item_option.state & QStyle::State_HasFocus) {
        item_option.state ^= QStyle::State_HasFocus;
    }
    QStyledItemDelegate::paint(painter, item_option, index);
}
