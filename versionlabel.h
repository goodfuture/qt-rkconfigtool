#ifndef VERSIONLABEL_H
#define VERSIONLABEL_H

#include <QFont>
#include <QRect>
#include <QSize>
#include <QBrush>
#include <QColor>
#include <QDebug>
#include <QLabel>
#include <QWidget>
#include <QPainter>
#include <QPalette>
#include <QPaintEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLinearGradient>

class VersionLabel : public QWidget
{
    Q_OBJECT
public:
    explicit VersionLabel(QWidget *parent = 0);

signals:

public slots:
    void	setHmiVersion(QString &);
    void	setBlpVersion(QString &);
    //void 	setDtuVersion(QString &);

private:
    QLabel *hmiFirmwareVersion;
    QLabel *blpFirmwareVersion;
    //QLabel *dtuFirmwareVersion;

protected:
    virtual void paintEvent(QPaintEvent *);

};

#endif // VERSIONLABEL_H
