#ifndef VIEWNETCONFIG_H
#define VIEWNETCONFIG_H

#include <QList>
#include <QTableView>
#include <QHeaderView>
#include <QModelIndex>
#include <QAbstractItemView>

#include "modelnetconfig.h"
#include "delegatenetconfig.h"
#include "styledtableview.h"

class ViewNetConfig : public StyledTableView
{
    Q_OBJECT
public:
    explicit ViewNetConfig(QWidget *parent = 0);

signals:
    void configChanged();

public slots:

private:
    ModelNetConfig *model;

};

#endif // VIEWNETCONFIG_H
