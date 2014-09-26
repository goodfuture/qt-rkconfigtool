#include "appsettings.h"

AppSettings::AppSettings(QObject *parent) :
    QSettings(parent)
{
    this->setDefaultFormat(this->IniFormat);
    this->setUserIniPath(QString(APP_CONFIG_FILE_PATH));
    this->setSystemIniPath(QString(APP_CONFIG_FILE_PATH));
}
