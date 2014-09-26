#include "titlemenu.h"
#include <QUrl>
#include <QDesktopServices>
#include <QIcon>
#include <QPalette>

TitleMenu::TitleMenu(QWidget *parent) :
    QMenu(parent)
{
    /*
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255, 0)));
    setPalette(palette);
    */
    this->setWindowFlags(Qt::FramelessWindowHint | this->windowFlags());
    this->setAttribute(Qt::WA_TranslucentBackground, true);

    QString style;
    style = QString("QMenu{"
                    "background:white;"
                    "border:2px groove lightgray;"
                    "border-radius:5px;}");
    style += QString("QMenu::item{"
                     "padding:0px 5px 0px 30px;"
                     "height:25px;}");
    style += QString("QMenu::item:selected:enabled{"
                     "background:rgb(0, 191, 243, 255);"
                     "color:white;}");
    style += QString("QMenu::item:selected:!enabled{"
                     "background:transparent;};");
    style += QString("QMenu::separator{"
                     "height:1px;"
                     "background:lightgrav;"
                     "margin:2px 0px 2px 0px;}");
    style += QString("QMenu::indicator{"
                     "padding:10px}");
    setStyleSheet(style);

    this->create_actions();
    this->translate();
    //this->setObjectName("menu");
}

void TitleMenu::create_actions()
{
    action_setting = new QAction(this);
    action_check_update = new QAction(this);
    action_know_more = new QAction(this);
    action_about = new QAction(this);

    action_setting->setIcon(QIcon(":/icon/menu_setting"));
    action_check_update->setIcon(QIcon(":/icon/menu_check_update"));
    action_know_more->setIcon(QIcon(":/icon/menu_know_more"));
    action_about->setIcon(QIcon(":/icon/menu_about_us"));

    this->addAction(action_setting);
    this->addSeparator();
    this->addAction(action_check_update);
    this->addAction(action_know_more);
    this->addAction(action_about);

    connect(action_setting, SIGNAL(triggered()), this, SIGNAL(showSettingDialog()));
    //connect(action_check_update, SIGNAL(triggered()), this, SIGNAL(showAboutDialog()));
    connect(action_know_more, SIGNAL(triggered()), this, SLOT(showWebPage()));
    connect(action_about, SIGNAL(triggered()), this, SIGNAL(showAboutDialog()));
}

void TitleMenu::translate()
{
    action_setting->setText(tr("Setting"));
    action_check_update->setText(tr("Check Update"));
    action_know_more->setText(tr("Know More"));
    action_about->setText(tr("About Us"));
}

void TitleMenu::showWebPage()
{
    QUrl url("http://www.rockontrol.com");
    QDesktopServices::openUrl(url);
}
