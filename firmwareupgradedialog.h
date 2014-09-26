#ifndef FIRMWAREUPGRADEDIALOG_H
#define FIRMWAREUPGRADEDIALOG_H

#include "util.h"
#include "common.h"
#include "pushbutton.h"
#include "dropshadowwidget.h"

#include <QFont>
#include <QDebug>
#include <QLabel>
#include <QPainter>
#include <QLineEdit>
#include <QComboBox>
#include <QPaintEvent>
#include <QCloseEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFileDialog>
#include <QPushButton>
#include <QToolButton>
#include <QMessageBox>
#include <QProgressBar>
#include <QStackedLayout>

class FirmwareUpgradeDialog : public DropShadowWidget
{
    Q_OBJECT
public:
    explicit FirmwareUpgradeDialog(QWidget *parent = 0);
    ~FirmwareUpgradeDialog(){}

public:
    void	initWidgets();
    void	translate();

signals:
    void 	beginUpgrade(Util::FirmwareType, QString);
    void	userRequest(int);

public slots:
    void 	onUpgradeButtonClicked();
    void	onFileSelectButtonClicked();
    void 	onUpgradeProgress(int);

protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void closeEvent(QCloseEvent *);

private:
    QHBoxLayout *title_layout;
    QVBoxLayout *center_layout;
    QVBoxLayout *main_layout;
    PushButton *close_button;
    QWidget *progress_widget;
    QWidget *select_widget;
    QComboBox *combox;
    QLabel *title_icon_label;
    QLabel *title_string_label;
    QLabel *logo_label;
    QLabel *specify_label;
    QLabel *firmware_type_label;
    QLabel *file_path_label;
    QLabel *progress_label;
    QLabel *prompt_label;
    QLineEdit *file_path_line;
    QToolButton *file_select_button;
    QPushButton *upgrade_button;
    QPushButton *cancel_button;
    QProgressBar *progress_bar;
    QStackedLayout *stacked_layout;
};

#endif // FIRMWAREUPGRADEDIALOG_H
