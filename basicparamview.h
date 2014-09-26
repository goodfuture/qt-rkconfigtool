#ifndef BASICPARAMVIEW_H
#define BASICPARAMVIEW_H

#include "basicparammodel.h"
#include "basicparamdelegate.h"
#include <QTableView>
#include <QHeaderView>
#include <QList>

class BasicParamView : public QTableView
{
    Q_OBJECT
public:
    explicit BasicParamView(QWidget *parent = 0);
    void init();

signals:

public slots:

private:
    BasicParamModel *model;
};

#endif // BASICPARAMVIEW_H
