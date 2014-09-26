#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include "util.h"
#include "common.h"
#include "rkprotocol.h"

#ifdef WIN32
#include <WinSock2.h>
#pragma comment(lib,"Ws2_32.lib.")
#else
#include <arpa/inet.h>
#endif

#include <QFile>
#include <QDebug>
#include <QThread>
#include <QString>
#include <QByteArray>
#include <QTcpSocket>
#include <QDataStream>
#include <QTimerEvent>
#include <QStringList>
#include <QHostAddress>
#include <QSignalMapper>

extern Context_t g_tContext;

class MessageHandler : public QTcpSocket
{
    Q_OBJECT
public:
    explicit MessageHandler(QObject *parent = 0);
    bool sendMsg();

signals:
    void quit();
    void upgradeProgress(int);
    //void messageHandled(int, int);
    void messageHandled(Util::MsgHandleFlag, Util::MsgHandleRst);

public slots:
    void onQuit();
    void onUserRequest(int);
    void tryLogin(QStringList);
    void onRequestGetFirmwareVersion(Util::FirmwareType);

private slots:
    void onConnected();
    void onReadyRead();
    void sendLoginMsg();
    void sendRebootMsg();
    void onDisConnected();
    bool handleRecevicedMsg();
    void sendGetProtocolSetMsg();
    void readyToUpgradeFirmware();
    bool sendFirmwareUpgradeMsg(bool start);
    void sendPutConfigParamMsg(enum ParamType);
    void sendGetConfigParamMsg(enum ParamType);
    void onError(QAbstractSocket::SocketError);
    void onStateChanged(QAbstractSocket::SocketState);
    void onRequestUpgradeFirmware(Util::FirmwareType, QString);

private:
    //QSignalMapper *signalMapper;
    QString 	user;
    QString 	passwd;
    QString 	targetAddr;
    rkMsgPkt_t	sendBuffer;
    rkMsgPkt_t 	recvBuffer;
    int			targetPort;
    bool		loginStatus;
    int			loginTimer;
    int			upgradeTimer;
    int			upgradePktTotalNum;
    int			upgradePktCurrentSeq;
    bool		upgradePktResendFlag;
    int			firmwareType;
    QString		firmwareFilePath;
    qint64		firmwareFilePosOfRead;

protected:
    void timerEvent(QTimerEvent *);
};

#endif // MESSAGEHANDLER_H
