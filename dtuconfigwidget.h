#ifndef DTUCONFIGWIDGET_H
#define DTUCONFIGWIDGET_H

#include <QColor>
#include <QWidget>
#include <QPalette>
#include <QStackedLayout>

#include "viewdtuconfig.h"
#include "dtuloginwidget.h"

class DtuConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DtuConfigWidget(QWidget *parent = 0);

signals:
	void	configChanged();

public slots:
    void	onLogin();

private:
    void	initWidgets();
    void	translate();

private:
    QStackedLayout	*stackedLayout;
    DtuLoginWidget	*loginWidget;
    ViewDtuConfig	*viewDtuConfig;
};

#endif // DTUCONFIGWIDGET_H
