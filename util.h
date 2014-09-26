#ifndef UTIL_H
#define UTIL_H

#include "common.h"

#include <QString>
#include <QVariant>
#include <QSettings>
#include <QMetaType>
#include <QByteArray>
#include <QStringList>

class Util
{
public:
    enum FirmwareType {
        AllFirmware,
        HmiFirmware,
        CoreFirmware,
        DtuToolFirmware
    };

    enum DispMsgId {
        NoneMsg,
        EmptyUserNameMsg,
        EmptyPasswordMsg,
        EmptyUserOrPasswordMsg,
        LoginFailedMsg,
        ConnectFailedMsg,
        ConnectTimeOutMsg,
        EmptyTargetAddrMsg,
        EmptyTargetPortMsg,
        EmptyTargetAddrOrPortMsg
    };

    enum MsgHandleFlag {
        LoginFlag,
        ConnectFlag,
        MessageFlag,
        GetConfigFlag,
        PutConfigFlag,
        RebootDeviceFlag,
        GetFirmwareVersionFlag,
        GetSupportedProtocolFlag
    };

    enum MsgHandleRst {
        LoginFailedRst,
        LoginSuccessRst,
        ConnectTimeOutRst,
        ConnectFailedRst,
        ConnectSuccessRst,
        MessageSendingSuccessRst,
        MessageSendingFailedRst,
        MessageRecvingSuccessRst,
        MessageRecvingFailedRst,
        GetConfigFlagSuccessRst,
        GetConfigFlagFailedRst,
        PutConfigFlagSuccessRst,
        PutConfigFlagFailedRst,
        RebootDeviceSuccessRst,
        RebootDeviceFailedRst,
        GetFirmwareVersionSuccessRst,
        GetFirmwareVersionFailedRst,
        GetSupportedProtocolSuccessRst,
        GetSupportedProtocolFailedRst
    };

    enum UserRequestType {
        REQUEST_SYNC_ALL_CONFIG,
        REQUEST_SAVE_ALL_CONFIG,
        REQUEST_SYNC_SYSTEM_CONFIG,
        REQUEST_SAVE_SYSTEM_CONFIG,
        REQUEST_SYNC_COM_CONFIG,
        REQUEST_SAVE_COM_CONFIG,
        REQUEST_SYNC_NET_CONFIG,
        REQUEST_SAVE_NET_CONFIG,
        REQUEST_SYNC_ANALOG_CONFIG,
        REQUEST_SAVE_ANALOG_CONFIG,
        REQUEST_SYNC_SERIAL_CONFIG,
        REQUEST_SAVE_SERIAL_CONFIG,
        REQUEST_SYNC_DIO_CONFIG,
        REQUEST_SAVE_DIO_CONFIG,
        REQUEST_SYNC_DTU_CONFIG,
        REQUEST_SAVE_DTU_CONFIG,
        REQUEST_FACTORY_CONFIG,
        REQUEST_REBOOT_DEVICE,
        REQUEST_GET_DYNAMIC_PROTOCOL_SET
    };

public:
    Util();

private:

};
//Q_DECLARE_METATYPE(Util);

#endif // UTIL_H
