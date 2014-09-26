#ifndef DTULOGINWIDGET_H
#define DTULOGINWIDGET_H

#include <QLabel>
#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QGridLayout>

class DtuLoginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DtuLoginWidget(QWidget *parent = 0);

signals:
    void	login();

public slots:
    void 	onButtonClicked();

private:
    QLabel 	*userNameLabel;
    QLabel 	*passwdLabel;
    QLineEdit *passwdLineEdit;
    QComboBox *userNameEdit;
    QPushButton *loginButton;

private:
    void	initWidgets();
    void	translate();

};

#endif // DTULOGINWIDGET_H
