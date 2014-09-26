#ifndef VIEWBASISCONFIG_H
#define VIEWBASISCONFIG_H

#include <QList>
#include <QTableView>
#include <QHeaderView>
#include <QModelIndex>
#include <QHBoxLayout>
#include <QSignalMapper>

#include "common.h"
#include "switchbutton.h"
#include "styledtableview.h"
#include "modelbasisconfig.h"
#include "delegatebasisconfig.h"

class ViewBasisConfig : public StyledTableView
{
    Q_OBJECT
public:
    explicit ViewBasisConfig(QWidget *parent = 0);
    void init();

signals:
    void switchButtonChanged(int id, bool on);
    void configChanged();

public slots:
    void setSwitchButtonStatus(int id, bool on);
    void switchSignalMapper(bool on);
    void onDataEnableStatusChanged();

private:
    //QSignalMapper *signal_mapper;
    ModelBasisConfig *model;
    QList<SwitchButton *> switchButtonList;

};

#endif // VIEWBASISCONFIG_H
