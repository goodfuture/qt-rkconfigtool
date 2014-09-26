#ifndef DELEGATEDTUCONFIG_H
#define DELEGATEDTUCONFIG_H

#include <QRect>
#include <QColor>
#include <QDebug>
#include <QStyle>
#include <QWidget>
#include <QPainter>
#include <QComboBox>
#include <QLineEdit>
#include <QStringList>
#include <QIntValidator>
#include <QStyledItemDelegate>

class DelegateDtuConfig : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit DelegateDtuConfig(QObject *parent = 0);

signals:

public slots:
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize	sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    //virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    QStringList	baudRateList;
    QStringList dataBitList;
    QStringList stopBitList;
    QStringList parityBitList;
    QStringList linkModeList;
    QStringList twoValueList;
    QStringList	platformLinkProtocolList;
    QStringList	companyLinkProtocolList;

};

#endif // DELEGATEDTUCONFIG_H
