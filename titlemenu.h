#ifndef TITLEMENU_H
#define TITLEMENU_H

#include <QMenu>
#include <QAction>

class TitleMenu : public QMenu
{
    Q_OBJECT
public:
    explicit TitleMenu(QWidget *parent = 0);
    void 	translate();

private:
    QAction *action_setting;
    QAction *action_check_update;
    QAction *action_know_more;
    QAction *action_about;
private:
    void create_actions();

signals:
    void 	showSettingDialog();
    void	showAboutDialog();

public slots:
    void 	showWebPage();

};

#endif // TITLEMENU_H
