#include "util.h"
#include "common.h"
#include "thread.h"
#include "mainwindow.h"
#include "logindialog.h"
#include "messagehandler.h"

#include <QFont>
#include <QObject>
#include <QThread>
#include <QDialog>
#include <QString>
#include <QTextCodec>
#include <QMessageBox>
#include <QTranslator>
#include <QApplication>
#include <QSharedMemory>
#include <QCoreApplication>

Context_t	g_tContext;

int main(int argc, char *argv[])
{
    qRegisterMetaType<Util::FirmwareType>("Util::FirmwareType");
    qRegisterMetaType<Util::MsgHandleFlag>("Util::MsgHandleFlag");
    qRegisterMetaType<Util::MsgHandleRst>("Util::MsgHandleRst");
    QApplication app(argc, argv);

    memset(&g_tContext, 0, sizeof(Context_t));

#ifdef WIN32
    QTextCodec *codec = QTextCodec::codecForName("System");
#else
    QTextCodec *codec = QTextCodec::codecForName("GBK");
#endif
    QTextCodec::setCodecForLocale(codec);

    QTranslator translator;
    translator.load(QString(":/qm/RkBoxTr_Zh"));
    app.installTranslator(&translator);

    QFile qss(":/qss/rkbox");
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();

    //QFont font(QString("Î¢ÈíÑÅºÚ"), 10, QFont::Normal, false);
    //QApplication::setFont(font);

    QCoreApplication::setOrganizationName(QString("Rockontrol"));
    QCoreApplication::setOrganizationDomain(QString("rockontrol.com"));
    QCoreApplication::setApplicationName(QString("ToolBox"));

    MainWindow main;
    MessageHandler msgHandler;
    //QThread msgHandlerThread;
    Thread msgHandlerThread;

    main.connect(&msgHandler, SIGNAL(messageHandled(Util::MsgHandleFlag, Util::MsgHandleRst)), SLOT(onMessageHandled(Util::MsgHandleFlag, Util::MsgHandleRst)));
    main.connect(&msgHandler, SIGNAL(upgradeProgress(int)), SIGNAL(upgradeProgress(int)));

    msgHandler.connect(&main, SIGNAL(quit()), SLOT(onQuit()));
    msgHandler.connect(&main, SIGNAL(userRequest(int)), SLOT(onUserRequest(int)));
    msgHandler.connect(&main, SIGNAL(loginRequest(QStringList)), SLOT(tryLogin(QStringList)));
    msgHandler.connect(&main, SIGNAL(requestUpgradeFirmware(Util::FirmwareType, QString)), SLOT(onRequestUpgradeFirmware(Util::FirmwareType, QString)));
    msgHandler.connect(&main, SIGNAL(requestGetFirmwareVersion(Util::FirmwareType)), SLOT(onRequestGetFirmwareVersion(Util::FirmwareType)));

    msgHandlerThread.connect(&msgHandler, SIGNAL(quit()), SLOT(quit()));
    qApp->connect(&msgHandlerThread, SIGNAL(finished()), SLOT(quit()));
    //msgHandlerThread.connect(&msgHandlerThread, SIGNAL(finished()), SLOT(deleteLater()));
    //msgHandlerThread.connect(&msgHandler, SIGNAL(destroyed()), SLOT(quit()));

    msgHandler.moveToThread(&msgHandlerThread);

    QSharedMemory share_memory;
    share_memory.setKey(QString("RkControl"));

    if (share_memory.attach()) {
        QMessageBox::information(0, QObject::tr("Tip"), QObject::tr("Already Have A Instance Running!"), QObject::tr("Ok"));
        return 0;
    }

    if (share_memory.create(1, QSharedMemory::ReadWrite)) {
        msgHandlerThread.start();
        main.login();
        return app.exec();
    }

    return 0;
}
