#ifndef DELEGATEBASISCONFIG_H
#define DELEGATEBASISCONFIG_H

#include <QMap>
#include <QDebug>
#include <QRegExp>
#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QValidator>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStringList>
#include <QMessageBox>
#include <QRegExpValidator>
#include <QStyledItemDelegate>

#include "switchbutton.h"

class DelegateBasisConfig : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit DelegateBasisConfig(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

signals:

public slots:

private:
    QStringList sysTypeList;
    QStringList rtdStorageIntervalList;
    QStringList msgUploadModeList;
    QStringList msg_upload_interval_list;

protected:
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

};

#endif // DELEGATEBASISCONFIG_H
