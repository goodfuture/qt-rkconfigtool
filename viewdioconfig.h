#ifndef VIEWDIOCONFIG_H
#define VIEWDIOCONFIG_H

#include "common.h"
#include "switcher.h"
#include "switchbutton.h"
#include "modeldioconfig.h"
#include "styledtableview.h"
#include "delegatedioconfig.h"

#include <QList>
#include <QWidget>
#include <QHBoxLayout>

class ViewDioConfig : public StyledTableView
{
    Q_OBJECT
public:
    explicit ViewDioConfig(QWidget *parent = 0);

signals:
    void configChanged();
    void switchButtonStatusChanged(int, bool);
    void switcherStatusChanged(int, bool);

public slots:
    void switchButtonSignalMapper(bool);
    void switcherSignalMapper(bool);
    void onChannelStatusChanged(int);

private:
    ModelDioConfig *model;
    QList<SwitchButton *> switch_button_list;
    QList<Switcher *> switcher_list;

};

#endif // VIEWDIOCONFIG_H
