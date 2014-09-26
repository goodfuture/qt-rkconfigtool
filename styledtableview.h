#ifndef STYLEDTABLEVIEW_H
#define STYLEDTABLEVIEW_H

#include <QColor>
#include <QPalette>
#include <QTableView>
#include <QHeaderView>

class StyledTableView : public QTableView
{
    Q_OBJECT
public:
    explicit StyledTableView(QWidget *parent = 0);

signals:

public slots:

};

#endif // STYLEDTABLEVIEW_H
