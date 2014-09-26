#ifndef VIEWCOMCONFIG_H
#define VIEWCOMCONFIG_H

#include "modelcomconfig.h"
#include "styledtableview.h"
#include "delegatecomconfig.h"

class ViewComConfig : public StyledTableView
{
    Q_OBJECT
public:
    explicit ViewComConfig(QWidget *parent = 0);

signals:
    void	configChanged();
    void 	resetDynamicProtocolSet();
    void	requestGetProtocolSet();

public slots:

private:
    ModelComConfig 		*model;
    DelegateComConfig	*delegate;

};

#endif // VIEWCOMCONFIG_H
