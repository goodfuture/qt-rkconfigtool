#include "messagehandler.h"

MessageHandler::MessageHandler(QObject *parent) :
    QTcpSocket(parent)
{
    this->loginStatus = false;
    this->loginTimer = 0;
    this->upgradePktResendFlag = false;
    this->upgradeTimer = 0;
    this->connect(this, SIGNAL(connected()), SLOT(onConnected()));
    this->connect(this, SIGNAL(disconnected()), SLOT(onDisConnected()));
    this->connect(this, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(onError(QAbstractSocket::SocketError)));
    this->connect(this, SIGNAL(stateChanged(QAbstractSocket::SocketState)), SLOT(onStateChanged(QAbstractSocket::SocketState)));
    this->connect(this, SIGNAL(readyRead()), this, SLOT(onReadyRead()));

}

void MessageHandler::tryLogin(QStringList info)
{
    //qDebug() << info;

    this->user = info.at(0);
    this->passwd = info.at(1);
    this->targetAddr = info.at(2);
    this->targetPort = info.at(3).toInt();

    this->abort();
    this->connectToHost(this->targetAddr, this->targetPort);
    if (loginTimer) {
        killTimer(loginTimer);
        loginTimer = 0;
    }
    loginTimer = startTimer(5000);
    //qDebug() << "LoginTimer" << loginTimer;
#ifdef DEBUG_MODE
    emit messageHandled(Util::LoginFlag, Util::LoginSuccessRst);
#endif
}

void MessageHandler::onConnected()
{
    //qDebug() << "Connected" << this->peerAddress();
    sendLoginMsg();
    emit messageHandled(Util::ConnectFlag, Util::ConnectSuccessRst);
    //sendGetConfigParamMsg(AllParam);
    //sendPutConfigParamMsg(ComParam);
}

void MessageHandler::onDisConnected()
{
    //qDebug() << "Disconnected";
    emit messageHandled(Util::ConnectFlag, Util::ConnectFailedRst);
    if (loginTimer) {
        killTimer(loginTimer);
        loginTimer = 0;
    }
}

void MessageHandler::onError(QAbstractSocket::SocketError error)
{
    //qDebug() << "Error" << error;
    switch(error) {
    case QAbstractSocket::ConnectionRefusedError:
    case QAbstractSocket::HostNotFoundError:
        if (loginTimer) {
            killTimer(loginTimer);
            loginTimer = 0;
        }
        emit messageHandled(Util::ConnectFlag, Util::ConnectFailedRst);
        break;
    default:
        break;
    }
}

void MessageHandler::onStateChanged(QAbstractSocket::SocketState)
{
}

bool MessageHandler::sendMsg()
{
    int ret;
#ifdef DEBUG_LEVEL_RAW_SEND_MESSAGE_OUTPUT
    rkPrintMsg(sendBuffer, false);
#endif
    quint16 msg_len = sendBuffer.m_sLen;
    sendBuffer.m_sLen = htons(msg_len);
    ret = write((char *)(&sendBuffer), RK_PROTOCOL_HEADER_LEN + msg_len);
    if (ret == RK_PROTOCOL_HEADER_LEN + msg_len) {
        emit messageHandled(Util::MessageFlag, Util::MessageSendingSuccessRst);
        return true;
    } else {
        emit messageHandled(Util::MessageFlag, Util::MessageSendingFailedRst);
        return false;
    }
}

void MessageHandler::onReadyRead()
{
    //qDebug() << this->bytesAvailable();

    int pos = 0, needToRecv;
    quint16 len;

    while(read((char *)&recvBuffer.m_aHeader[pos], 1) == 1) {
        if (pos == 0 && recvBuffer.m_aHeader[0] == (RK_PROTOCOL_HEADER >> 16 & 0xFF)) {
            pos = 1;
            continue;
        } else if (pos == 1 && recvBuffer.m_aHeader[1] == (RK_PROTOCOL_HEADER >> 8 & 0xFF)) {
            pos = 2;
            continue;
        } else if (pos == 2 && recvBuffer.m_aHeader[2] == (RK_PROTOCOL_HEADER & 0xFF)) {
            pos = 0;

            if (read((char *)&recvBuffer.m_uCmdWord, 1) != 1) {
                return;
            }
            //qDebug("CW:%02X", recvBuffer.m_uCmdWord);

            if (read((char *)&len, 2) != 2) {
                return;
            }
            recvBuffer.m_sLen = ntohs(len);
            //qDebug("LEN:%d", recvBuffer.m_sLen);

            needToRecv = recvBuffer.m_sLen;
            do {
                len = read((char *)&recvBuffer.m_aMsg, needToRecv);
                if (len < 0) {
                    qDebug("Read Error!");
                    return;
                } else if (len == needToRecv) {
                    break;
                }
                needToRecv -= len;
                qDebug("Read : %d, Need : %d, Available : %d", len, needToRecv, this->bytesAvailable());
                if (waitForReadyRead(10)) {
                    continue;
                } else {
                    return;
                }
            } while(needToRecv > 0);

            handleRecevicedMsg();
        }
    }
}

void MessageHandler::onQuit()
{
    this->abort();
    emit quit();
}

void MessageHandler::sendPutConfigParamMsg(enum ParamType type)
{
    bool ret;

    do {
        ret = rkGenMsgOfPutConfig(sendBuffer, type);
        sendMsg();
    } while (!ret);
}

void MessageHandler::sendGetConfigParamMsg(enum ParamType type)
{
    bool ret;

    do {
        ret = rkGenMsgOfGetConfig(sendBuffer, type);
        sendMsg();
    } while(!ret);
}

void MessageHandler::sendLoginMsg()
{
    rkGenMsgOfLogin(sendBuffer, this->user, this->passwd);
    sendMsg();
}

void MessageHandler::sendRebootMsg()
{
    rkGenMsgOfRebootDev(sendBuffer);
    sendMsg();
}

void MessageHandler::sendGetProtocolSetMsg()
{
    rkGenMsgOfGetSupportedDynamicProtocol(sendBuffer);
    sendMsg();
}

void MessageHandler::onUserRequest(int requestId)
{
    switch(requestId) {
    case Util::REQUEST_SYNC_ALL_CONFIG:
        sendGetConfigParamMsg(AllParam);
        break;
    case Util::REQUEST_SAVE_ALL_CONFIG:
        sendPutConfigParamMsg(AllParam);
        break;
    case Util::REQUEST_SYNC_SYSTEM_CONFIG:
        sendGetConfigParamMsg(SystemParam);
        break;
    case Util::REQUEST_SAVE_SYSTEM_CONFIG:
        sendPutConfigParamMsg(SystemParam);
        break;
    case Util::REQUEST_SYNC_COM_CONFIG:
        sendGetConfigParamMsg(ComParam);
        break;
    case Util::REQUEST_SAVE_COM_CONFIG:
        sendPutConfigParamMsg(ComParam);
        break;
    case Util::REQUEST_SYNC_NET_CONFIG:
        sendGetConfigParamMsg(NetParam);
        break;
    case Util::REQUEST_SAVE_NET_CONFIG:
        sendPutConfigParamMsg(NetParam);
        break;
    case Util::REQUEST_SYNC_ANALOG_CONFIG:
        sendGetConfigParamMsg(AnalogParam);
        break;
    case Util::REQUEST_SAVE_ANALOG_CONFIG:
        sendPutConfigParamMsg(AnalogParam);
        break;
    case Util::REQUEST_SYNC_SERIAL_CONFIG:
        sendGetConfigParamMsg(SerialParam);
        break;
    case Util::REQUEST_SAVE_SERIAL_CONFIG:
        sendPutConfigParamMsg(SerialParam);
        break;
    case Util::REQUEST_SYNC_DIO_CONFIG:
        sendGetConfigParamMsg(DioParam);
        break;
    case Util::REQUEST_SAVE_DIO_CONFIG:
        sendPutConfigParamMsg(DioParam);
        break;
    case Util::REQUEST_SYNC_DTU_CONFIG:
        sendGetConfigParamMsg(DtuParam);
        break;
    case Util::REQUEST_SAVE_DTU_CONFIG:
        sendPutConfigParamMsg(DtuParam);
        break;
    case Util::REQUEST_FACTORY_CONFIG:
        break;
    case Util::REQUEST_REBOOT_DEVICE:
        sendRebootMsg();
        break;
    case Util::REQUEST_GET_DYNAMIC_PROTOCOL_SET:
        sendGetProtocolSetMsg();
        break;
    default:
        break;
    }
}

bool MessageHandler::handleRecevicedMsg()
{
#ifdef DEBUG_LEVEL_RAW_RECV_MESSAGE_OUTPUT
    rkPrintMsg(recvBuffer, true);
#endif

    if (rkVerifyMsgTail(recvBuffer) == false) {
        emit messageHandled(Util::MessageFlag, Util::MessageRecvingFailedRst);
        return false;
    }

    switch(recvBuffer.m_uCmdWord) {
    case CW_ECHO_OF_USER_LOGIN:
        if (loginTimer) {
            killTimer(loginTimer);
            loginTimer = 0;
        }

        if (recvBuffer.m_aMsg[0] != 0){
            this->loginStatus = true;
            sendGetConfigParamMsg(AllParam);
            sendGetProtocolSetMsg();
            onRequestGetFirmwareVersion(Util::AllFirmware);
            emit messageHandled(Util::LoginFlag, Util::LoginSuccessRst);
        } else {
            emit messageHandled(Util::LoginFlag, Util::LoginFailedRst);
        }
        break;
    case CW_ECHO_OF_GET_PARAM_CONFIG:
        if (rkParseParamConfig(recvBuffer)) {
            emit messageHandled(Util::GetConfigFlag, Util::GetConfigFlagSuccessRst);
        } else {
            emit messageHandled(Util::GetConfigFlag, Util::GetConfigFlagFailedRst);
        }
        break;
    case CW_ECHO_OF_PUT_PARAM_CONFIG:
        if (rkParseParamConfig(recvBuffer)) {
            emit messageHandled(Util::PutConfigFlag, Util::PutConfigFlagSuccessRst);
        } else {
            emit messageHandled(Util::PutConfigFlag, Util::PutConfigFlagFailedRst);
        }
        break;
    case CW_ECHO_OF_REBOOT_DEVICE:
        emit messageHandled(Util::RebootDeviceFlag, Util::RebootDeviceSuccessRst);
        break;
    case CW_ECHO_OF_GET_FIRMWARE_VERSION:
        rkParseFirmwareVersion(recvBuffer);
        emit messageHandled(Util::GetFirmwareVersionFlag, Util::GetFirmwareVersionSuccessRst);
        break;
    case CW_ECHO_OF_UPGRADE_DTU_TOOL_FIRMWARE:
    case CW_ECHO_OF_UPGRADE_HMI_FIRMWARE:
    case CW_ECHO_OF_UPGRADE_BLP_FIRMWARE: {
        if (upgradeTimer) {
            killTimer(upgradeTimer);
            upgradeTimer = 0;
        }

        rkFtpMsgPkt *ftpMsg = (rkFtpMsgPkt *)recvBuffer.m_aMsg;
        if (ftpMsg->m_uFlag & FTP_PKT_FLAG_ERROR) {
            emit upgradeProgress(-1);
            return true;
        } else if (ftpMsg->m_uFlag & FTP_PKT_FLAG_ACK) {
            if (ftpMsg->m_uFlag & FTP_PKT_FLAG_LAST) {
                emit upgradeProgress(100);
                return true;
            } else {
                int rate = upgradePktCurrentSeq * 100.0f / upgradePktTotalNum;
                emit upgradeProgress(rate);
            }
        } else if (recvBuffer.m_aMsg[2] & FTP_PKT_FLAG_RESEND) {
            this->upgradePktResendFlag = true;
        }

        sendFirmwareUpgradeMsg(false);
        break;
    }
    case CW_ECHO_OF_GET_SUPPORTED_PROTOCOL:
        rkParseSupportedDynamicProtocol(recvBuffer);
        emit messageHandled(Util::GetSupportedProtocolFlag, Util::GetSupportedProtocolSuccessRst);
        break;
    default:
        emit messageHandled(Util::MessageFlag, Util::MessageRecvingFailedRst);
        break;
    }

    return true;
}

bool MessageHandler::sendFirmwareUpgradeMsg(bool start)
{
    static int read_cnt = 0;
    static qint64 pos = 0;
    quint8 flag, buf[RK_FTP_MESSAGE_MAX_LEN];

    QFile file(this->firmwareFilePath);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    if (start) {
        pos = 0;
        read_cnt = 0;
        this->upgradePktCurrentSeq = 0;
    }

    upgradePktTotalNum = (file.size() + RK_FTP_MESSAGE_MAX_LEN - 1) / RK_FTP_MESSAGE_MAX_LEN;

    if (upgradePktResendFlag) {
        upgradePktResendFlag = false;
        qDebug() << "Resend";
        file.seek(pos);
    } else {
        upgradePktCurrentSeq++;
        pos += read_cnt;
        file.seek(pos);
    }

    if (upgradePktCurrentSeq == upgradePktTotalNum) {
        flag = FTP_PKT_FLAG_LAST;
    } else {
        flag = 0;
    }

    read_cnt = file.read((char *)buf, (qint64)RK_FTP_MESSAGE_MAX_LEN);
    file.close();

    //static long already_read = 0;
    //already_read += read_cnt;
    //qDebug() << upgradePktCurrentSeq << upgradePktTotalNum << file.size() << already_read << RK_FTP_MESSAGE_MAX_LEN;

    rkGenMsgOfUpgradeFirmware(this->firmwareType, sendBuffer, buf, read_cnt, upgradePktCurrentSeq, flag);

    if (upgradeTimer) {
        killTimer(upgradeTimer);
        upgradeTimer = 0;
    }
    upgradeTimer = startTimer(10000);

    return sendMsg();
#if 0
    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_2);
#endif
}

void MessageHandler::readyToUpgradeFirmware()
{
    this->upgradePktCurrentSeq = 0;
}

void MessageHandler::onRequestGetFirmwareVersion(Util::FirmwareType type)
{
    switch(type) {
    case Util::AllFirmware:
        rkGenMsgOfGetFirmwareVersion(sendBuffer, 0);
        break;
    case Util::HmiFirmware:
        rkGenMsgOfGetFirmwareVersion(sendBuffer, 1);
        break;
    case Util::CoreFirmware:
        rkGenMsgOfGetFirmwareVersion(sendBuffer, 2);
        break;
    case Util::DtuToolFirmware:
        rkGenMsgOfGetFirmwareVersion(sendBuffer, 3);
        break;
    default:
        break;
    }
    sendMsg();
}

void MessageHandler::onRequestUpgradeFirmware(Util::FirmwareType type, QString firmware)
{
    if (type == Util::HmiFirmware) {
        this->firmwareType = 0;
    } else if (type == Util::CoreFirmware){
        this->firmwareType = 1;
    } else if (type == Util::DtuToolFirmware) {
        this->firmwareType = 2;
    }

    this->firmwareFilePath = firmware;

    this->readyToUpgradeFirmware();
    this->sendFirmwareUpgradeMsg(true);
}

void MessageHandler::timerEvent(QTimerEvent *event)
{
    //qDebug() << "TmOut" << event->timerId();

    if (event->timerId() == loginTimer) {
        killTimer(loginTimer);
        loginTimer = 0;
        emit messageHandled(Util::ConnectFlag, Util::ConnectTimeOutRst);
    } else if (event->timerId() == upgradeTimer) {
        //qDebug() << "TimeOut";
        killTimer(upgradeTimer);
        upgradeTimer = 0;
        emit upgradeProgress(-1);
    }

    QTcpSocket::timerEvent(event);
}
