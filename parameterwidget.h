#ifndef PARAMETERWIDGET_H
#define PARAMETERWIDGET_H

#include <QWidget>
#include <QTabWidget>
#include <QLabel>
#include <QStringList>
#include <QList>
#include <QVBoxLayout>
#include <QHBoxLayout>

class ParameterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ParameterWidget(QWidget *parent = 0);
    void	initWidgets();
    void	initSysWidget();
    void	initNetWidget();
    void	translate();

private:
    QTabWidget *tab_widget;
    QWidget	*sys_widget;
    QWidget *net_widget;

    QList<QLabel *> *sys_label_list;

signals:

public slots:

};

#endif // PARAMETERWIDGET_H
