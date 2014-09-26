#include "systemtray.h"

SystemTray::SystemTray(QObject *parent) :
    QSystemTrayIcon(parent)
{
    this->setIcon(QIcon(":/icon/AppIcon"));
    this->setToolTip(tr("rkbox"));

    tray_menu = new QMenu();
    tray_menu->setFixedWidth(100);

    action_open = new QAction(this);
    action_quit = new QAction(this);

    tray_menu->addAction(action_open);
    tray_menu->addSeparator();
    tray_menu->addAction(action_quit);

    connect(action_open, SIGNAL(triggered()), this, SIGNAL(showMainWindow()));
    connect(action_quit, SIGNAL(triggered()), this, SIGNAL(quit()));

    this->setContextMenu(tray_menu);
    this->translate();
}

void SystemTray::translate()
{
    action_open->setText(tr("Open Main Window"));
    action_quit->setText(tr("Quit"));
}
