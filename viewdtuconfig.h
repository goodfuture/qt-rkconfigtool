#ifndef VIEWDTUCONFIG_H
#define VIEWDTUCONFIG_H

#include "modeldtuconfig.h"
#include "styledtableview.h"
#include "delegatedtuconfig.h"

class ViewDtuConfig : public StyledTableView
{
    Q_OBJECT
public:
    explicit ViewDtuConfig(QWidget *parent = 0);

signals:
    void configChanged();

public slots:
    void	setUserPermission(bool superUser);

private:
    bool	superUser;
    ModelDtuConfig *model;
    DelegateDtuConfig *delegate;
};

#endif // VIEWDTUCONFIG_H
