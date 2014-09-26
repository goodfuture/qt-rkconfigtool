#ifndef HISTORYVIEWWIDGET_H
#define HISTORYVIEWWIDGET_H

#include <QWidget>

class HistoryViewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HistoryViewWidget(QWidget *parent = 0);

signals:

public slots:
    void onLinkDrop();

};

#endif // HISTORYVIEWWIDGET_H
