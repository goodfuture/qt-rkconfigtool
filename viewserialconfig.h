#ifndef VIEWSERIALCONFIG_H
#define VIEWSERIALCONFIG_H

#include "common.h"
#include "checkbox.h"
#include "switchbutton.h"
#include "styledtableview.h"
#include "modelserialconfig.h"
#include "delegateserialconfig.h"

#include <QHeaderView>

class ViewSerialConfig : public StyledTableView
{
    Q_OBJECT
public:
    explicit ViewSerialConfig(QWidget *parent = 0);

signals:
    void configChanged();
    void switchButtonStatusChanged(int, bool);
    void checkBoxStatusChanged(int, bool);

public slots:

private slots:
    void switchButtonSignalMapper(bool);
    void checkBoxSignalMapper(bool);
    void onChannelStatusChanged(int);

private:
    ModelSerialConfig *model;
    QList<SwitchButton *> switch_button_list;
    QList<CheckBox *> flag_box_list;

};

#endif // VIEWSERIALCONFIG_H
