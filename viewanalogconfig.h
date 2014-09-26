#ifndef VIEWANALOGCONFIG_H
#define VIEWANALOGCONFIG_H

#include <QList>
#include <QModelIndex>

#include "common.h"
#include "checkbox.h"
#include "switchbutton.h"
#include "styledtableview.h"
#include "modelanalogconfig.h"
#include "delegateanalogconfig.h"

class ViewAnalogConfig : public StyledTableView
{
    Q_OBJECT
public:
    explicit ViewAnalogConfig(QWidget *parent = 0);

signals:
    void configChanged();
    void switchButtonStatusChanged(int, bool);
    void checkBoxStatusChanged(int, bool);

public slots:
    void onChannelStatusChanged(int);

private slots:
    void switchButtonSignalMapper(bool);
    void checkBoxSignalMapper(bool);

private:
    ModelAnalogConfig *model;
    QList<SwitchButton *> enable_button_list;
    QList<CheckBox *> flag_box_list;

};

#endif // VIEWANALOGCONFIG_H
