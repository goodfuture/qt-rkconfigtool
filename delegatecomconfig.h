#ifndef DELEGATECOMCONFIG_H
#define DELEGATECOMCONFIG_H

#include "common.h"

#include <QWidget>
#include <QCheckBox>
#include <QComboBox>
#include <QStringList>
#include <QStyledItemDelegate>

extern Context_t g_tContext;

class DelegateComConfig : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit DelegateComConfig(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    QStringList baudRateList;
    QStringList dataBitList;
    QStringList stopBitList;
    QStringList parityBitList;
    QStringList protocolList;

signals:
    void	requestGetProtocolSet();

public slots:
    void 	onResetDynamicProtocolSet();

protected:
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

};

#endif // DELEGATECOMCONFIG_H
