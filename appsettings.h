#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include "common.h"

#include <QSettings>

class AppSettings : public QSettings
{
    Q_OBJECT
public:
    explicit AppSettings(QObject *parent = 0);

signals:

public slots:

};

#endif // APPSETTINGS_H
