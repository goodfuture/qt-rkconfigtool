#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QRect>
#include <QColor>
#include <QBrush>
#include <QDebug>
#include <QPainter>
#include <QComboBox>
#include <QLineEdit>
#include <QPaintEvent>
#include <QStringList>
#include <QLinearGradient>

class CodeEditor : public QComboBox
{
    Q_OBJECT
public:
    explicit CodeEditor(QWidget *parent = 0);

signals:

public slots:
    QString	text();
    void	onClicked();
    void	setText(QString &);

protected:
    virtual void paintEvent(QPaintEvent *);

private:
    QLineEdit 	*lineEdit;
    QStringList codeList;
    QStringList nameList;
};

#endif // CODEEDITOR_H
