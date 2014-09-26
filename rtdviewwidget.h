#ifndef RTDVIEWWIDGET_H
#define RTDVIEWWIDGET_H

#include <QWidget>
#include <QTabWidget>

class RtdViewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RtdViewWidget(QWidget *parent = 0);
    void initWidgets();
    void translate();

signals:

public slots:
    void onLinkDrop();

private:
    QTabWidget *tab_widget;

};

#endif // RTDVIEWWIDGET_H
