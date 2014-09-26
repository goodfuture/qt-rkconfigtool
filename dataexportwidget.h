#ifndef DATAEXPORTWIDGET_H
#define DATAEXPORTWIDGET_H

#include <QWidget>

class DataExportWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DataExportWidget(QWidget *parent = 0);

signals:

public slots:
    void onLinkDrop();

};

#endif // DATAEXPORTWIDGET_H
