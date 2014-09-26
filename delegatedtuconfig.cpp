#include "delegatedtuconfig.h"

DelegateDtuConfig::DelegateDtuConfig(QObject *parent) :
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

    parityBitList << tr("None") << tr("Odd") << tr("Even");

    linkModeList << tr("Long Connection") << tr("Short Connection");

    twoValueList << tr("Yes") << tr("No");

    platformLinkProtocolList << tr("TCP") << tr("UDP");

    companyLinkProtocolList << tr("TCP") << tr("UDP") << tr("DCUDP") << tr("DCTCP")
                            << tr("MODBUS Bridge") << tr("101 To SMS");
}

void DelegateDtuConfig::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem itemOption(option);
    if (itemOption.state & QStyle::State_HasFocus) {
        itemOption.state ^= QStyle::State_HasFocus;
    }

#if 1
    if (index.column() == 0) {
        if (itemOption.state & QStyle::State_Selected) {
            itemOption.state ^=QStyle::State_Selected;
        }

        painter->fillRect(itemOption.rect, Qt::white);
        painter->fillRect(itemOption.rect, QColor(248, 181, 81));
        painter->setPen(QColor(181, 181, 181));
        painter->drawLine(itemOption.rect.topLeft(), itemOption.rect.topRight());
        painter->drawLine(itemOption.rect.bottomLeft(), itemOption.rect.bottomRight());
    }
#endif

    QStyledItemDelegate::paint(painter, itemOption, index);
}

QSize DelegateDtuConfig::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QStyledItemDelegate::sizeHint(option, index);
}

#if 1
QWidget *DelegateDtuConfig::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &index) const
{
    int row = index.row();
    int col = index.column();

    if (col == 2) {
        switch(row) {
        case 0:		/* COM1 Baudrate */
        case 7: {	/* COM2 Baudrate */
            QComboBox *editor = new QComboBox(parent);
            editor->addItems(baudRateList);
            editor->setMaxVisibleItems(5);
            return editor;
        }
        case 1:		/* COM1 Data Bits */
        case 8: {	/* COM2 Data Bits */
            QComboBox *editor = new QComboBox(parent);
            editor->addItems(dataBitList);
            return editor;
        }
        case 2:		/* COM1 Stop Bits */
        case 9: {	/* COM2 Stop Bits */
            QComboBox *editor = new QComboBox(parent);
            editor->addItems(stopBitList);
            return editor;
        }
        case 3:		/* COM1 Parity Bits */
        case 10: {	/* COM2 Parity Bits */
            QComboBox *editor = new QComboBox(parent);
            editor->addItems(parityBitList);
            return editor;
        }
        case 4:		/* COM1 Scan Period */
        case 11: {	/* COM2 Scan Period */
            QLineEdit *editor = new QLineEdit(parent);
            QIntValidator *validator = new QIntValidator(editor);
            validator->setRange(0, 100);
            editor->setValidator(validator);
            editor->setPlaceholderText(tr("Range From 0 To 100"));
            return editor;
        }
        case 5:		/* COM1 Echo Timeout */
        case 12: {	/* COM2 Echo Timeout */
            QLineEdit *editor = new QLineEdit(parent);
            QIntValidator *validator = new QIntValidator(editor);
            validator->setRange(1, 255);
            editor->setValidator(validator);
            editor->setPlaceholderText(tr("Range From 1 To 255"));
            return editor;
        }
        case 6:		/* COM1 Frame Size */
        case 13: {	/* COM2 Frame Size */
            QLineEdit *editor = new QLineEdit(parent);
            QIntValidator *validator = new QIntValidator(editor);
            validator->setRange(10, 1024);
            editor->setValidator(validator);
            editor->setPlaceholderText(tr("Range From 10 To 1024"));
            return editor;
        }
        case 14:	/* Platform Connect */
        case 16:	/* Phone Active */
        case 17:	/* SMS Active */
        case 18:	/* Local Data Active */
        case 21:	/* Split Control/Business Stream */
        case 22: { /* Auto Dial */
            QComboBox *editor = new QComboBox(parent);
            editor->addItems(twoValueList);
            return editor;
        }
        case 15: { 	/* Link Mode */
            QComboBox *editor = new QComboBox(parent);
            editor->addItems(linkModeList);
            return editor;
        }
        case 19: {	/* Activate Period */
            QLineEdit *editor = new QLineEdit(parent);
            QIntValidator *validator = new QIntValidator(editor);
            validator->setRange(5, 1440);
            editor->setValidator(validator);
            editor->setPlaceholderText(tr("Range From 5 To 1440"));
            return editor;
        }
        case 20: {	/* OffLine Period */
            QLineEdit *editor = new QLineEdit(parent);
            QIntValidator *validator = new QIntValidator(editor);
            validator->setRange(1, 60);
            editor->setValidator(validator);
            editor->setPlaceholderText(tr("Range From 1 To 60"));
            return editor;
        }
        case 23:	/* GPRS Dial Number */
        case 24:	/* GPRS APN */
        case 25:	/* GPRS Dial User Name */
        case 26: {	/* GPRS Dial Password */
            QLineEdit *editor = new QLineEdit(parent);
            editor->setMaxLength(32);
            return editor;
        }
        case 27: 	/* PPP Level HeartBeat Interval */
        case 34: {	/* Platform Heartbeat Interval */
            QLineEdit *editor = new QLineEdit(parent);
            QIntValidator *validator = new QIntValidator(editor);
            validator->setRange(30, 3600);
            editor->setValidator(validator);
            editor->setPlaceholderText(tr("Range From 30 To 3600"));
            return editor;
        }
        case 28: {	/* Re-dial Interval */
            QLineEdit *editor = new QLineEdit(parent);
            QIntValidator *validator = new QIntValidator(editor);
            validator->setRange(0, 3600);
            editor->setValidator(validator);
            editor->setPlaceholderText(tr("Range From 0 To 3600"));
            return editor;
        }
        case 29: {	/* Max Number Of Re-dial */
            QLineEdit *editor = new QLineEdit(parent);
            QIntValidator *validator = new QIntValidator(editor);
            validator->setRange(1, 10);
            editor->setValidator(validator);
            editor->setPlaceholderText(tr("Range From 1 To 10"));
            return editor;
        }
        case 30:  	/* Platform Device Number */
        case 37: {	/* Company Device Number */
            QLineEdit *editor = new QLineEdit(parent);
            editor->setMaxLength(16);
            return editor;
        }
        case 31: 	/* Platform Gateway IP Address */
        case 38: 	/* Company Gateway IP Address */
        case 43:	/* Company DNS1 */
        case 44: {	/* Company DNS2 */
            QLineEdit *editor = new QLineEdit(parent);
            return editor;
        }
        case 32: 	/* Platform Port Number */
        case 39: {	/* Company Port Number */
            QLineEdit *editor = new QLineEdit(parent);
            QIntValidator *validator = new QIntValidator(editor);
            validator->setRange(0, 65536);
            editor->setValidator(validator);
            editor->setPlaceholderText(tr("Range From 0 To 65536"));
            return editor;
        }
        case 33: { 	/* Platform Link Protocol */
            QComboBox *editor = new QComboBox(parent);
            editor->addItems(platformLinkProtocolList);
            return editor;
        }
        case 35:	/* Platform SMS Center Number */
        case 36: {	/* Platform SMS Alarm Number */
            QLineEdit *editor = new QLineEdit(parent);
            editor->setMaxLength(16);
            QIntValidator *validator = new QIntValidator(editor);
            editor->setValidator(validator);
            return editor;
        }
        case 40: {	/* Company Link Protocol */
            QComboBox *editor = new QComboBox(parent);
            editor->addItems(companyLinkProtocolList);
            return editor;
        }
        case 41: {	/* Company HeartBeat Interval */
            QLineEdit *editor = new QLineEdit(parent);
            QIntValidator *validator = new QIntValidator(editor);
            validator->setRange(1, 60);
            editor->setValidator(validator);
            editor->setPlaceholderText(tr("Range From 1 To 60"));
            return editor;
        }
        case 42: {	/* Company Max Number Of ReSend */
            QLineEdit *editor = new QLineEdit(parent);
            QIntValidator *validator = new QIntValidator(editor);
            validator->setRange(1, 5);
            editor->setValidator(validator);
            editor->setPlaceholderText(tr("Range From 1 To 5"));
            return editor;
        }
        default:
            return NULL;
        }
    }
    return NULL;
}
#endif

void DelegateDtuConfig::setEditorData(QWidget *editor, const QModelIndex &index) const
{
}

void DelegateDtuConfig::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
}

#if 0
void DelegateDtuConfig::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
}
#endif
