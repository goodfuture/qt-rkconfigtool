#ifndef DOCKWIDGET_H
#define DOCKWIDGET_H

#include "dockitemwidget.h"

#include <QList>
#include <QLabel>
#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QPaintEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSignalMapper>

class DockWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DockWidget(QWidget *parent = 0);
    ~DockWidget(){}
    void addIcon(QPixmap icon, QString tip);
    void resize();

signals:
    void clicked(int);

public slots:

protected:
    virtual void paintEvent(QPaintEvent *);

private:
    int		marginLeft;
    int		marginTop;
    int		marginRight;
    int		marginBottom;
    QHBoxLayout *mainLayout;
    QSignalMapper *signalMapper;
    QList<DockItemWidget *> dockItemList;

};

#endif // DOCKWIDGET_H
