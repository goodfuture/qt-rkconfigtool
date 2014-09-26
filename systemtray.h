#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H

#include <QIcon>
#include <QMenu>
#include <QAction>
#include <QApplication>
#include <QSystemTrayIcon>

class SystemTray : public QSystemTrayIcon
{
    Q_OBJECT
public:
    explicit SystemTray(QObject *parent = 0);
    void	translate();

signals:
    void	showMainWindow();
    void	quit();

public slots:

private:
    QMenu *tray_menu;

    QAction *action_open;
    QAction	*action_quit;
};

#endif // SYSTEMTRAY_H
