#include "common.h"
#include "rkprotocol.h"

extern Context_t g_tContext;

void rkInitMsgHeader(rkMsgPkt_t &pkt, qint8 cw)
{
    pkt.m_aHeader[0] = RK_PROTOCOL_HEADER >> 16 & 0xFF;
    pkt.m_aHeader[1] = RK_PROTOCOL_HEADER >> 8 & 0xFF;
    pkt.m_aHeader[2] = RK_PROTOCOL_HEADER & 0xFF;
    pkt.m_uCmdWord = cw;
    pkt.m_sLen = 0;
}

void rkFillMsgTail(rkMsgPkt_t &pkt)
{
    quint16 crc16;
    crc16 = rkCrc16(pkt.m_aMsg, pkt.m_sLen);
    pkt.m_aMsg[pkt.m_sLen] = crc16 >> 8;
    pkt.m_aMsg[pkt.m_sLen + 1] = crc16 & 0xFF;
    pkt.m_sLen += RK_PROTOCOL_TAIL_LEN;
}

bool rkPushTlvToMsg(rkMsgPkt_t &pkt, quint16 tag, quint16 len, const void *value)
{
    int need_len = RK_PROTOCOL_HEADER_LEN + pkt.m_sLen + RK_PROTOCOL_TAIL_LEN;
    need_len += TLV_TAG_SEG_LEN + TLV_LEN_SEG_LEN + len;
    if (need_len >= RK_PROTOCOL_MESSAGE_MAX_LEN) {
        return false;
    }

    tag = htons(tag);
    quint8 *ptr = pkt.m_aMsg + pkt.m_sLen;
    memcpy(ptr, &tag, TLV_TAG_SEG_LEN);
    quint16	tag_value_len = htons(len);
    memcpy(ptr + TLV_LEN_SEG_OFFSET, &tag_value_len, TLV_LEN_SEG_LEN);
    memcpy(ptr + TLV_VALUE_SEG_OFFSET, value, len);
    pkt.m_sLen += TLV_VALUE_SEG_OFFSET + len;

    return true;
}

bool rkGenMsgOfLogin(rkMsgPkt_t &pkt, QString &user, QString &passwd)
{
    rkInitMsgHeader(pkt, CW_USER_LOGIN);
    QByteArray user_name = user.toLatin1();
    rkPushTlvToMsg(pkt, TLV_TAG_LOGIN_USER, user_name.length(), user_name.data());
    QByteArray pass_word = passwd.toLatin1();
    rkPushTlvToMsg(pkt, TLV_TAG_LOGIN_PASSWORD, pass_word.length(), pass_word.data());
    rkFillMsgTail(pkt);

    return true;
}

bool rkGenMsgOfRebootDev(rkMsgPkt_t &pkt)
{
    rkInitMsgHeader(pkt, (quint8)CW_REBOOT_DEVICE);
    rkFillMsgTail(pkt);

    return true;
}

bool rkGenMsgOfGetConfig(rkMsgPkt_t &pkt, enum ParamType type)
{
    bool ret;
    static int pos = 0;

    rkInitMsgHeader(pkt, (quint8)CW_GET_PARAM_CONFIG);

    switch(type) {
    case SystemParam:
        ret = rkPushTlvToMsg(pkt, TLV_TAG_ALL_SYS_PARAM, 0, NULL);
        if (!ret) {
            rkFillMsgTail(pkt);
            return false;
        }
        break;
    case ComParam:
        ret = rkPushTlvToMsg(pkt, TLV_TAG_ALL_COM_PARAM, 0, NULL);
        if (!ret) {
            rkFillMsgTail(pkt);
            return false;
        }
        break;
    case NetParam:
        ret = rkPushTlvToMsg(pkt, TLV_TAG_ALL_NET_PARAM, 0, NULL);
        if (!ret) {
            rkFillMsgTail(pkt);
            return false;
        }
        break;
    case AnalogParam:
        ret = rkPushTlvToMsg(pkt, TLV_TAG_ALL_ANALOG_PARAM, 0, NULL);
        if (!ret) {
            rkFillMsgTail(pkt);
            return false;
        }
        break;
    case SerialParam:
        ret = rkPushTlvToMsg(pkt, TLV_TAG_ALL_SERIAL_PARAM, 0, NULL);
        if (!ret) {
            rkFillMsgTail(pkt);
            return false;
        }
        break;
    case DioParam:
        ret = rkPushTlvToMsg(pkt, TLV_TAG_ALL_DIO_PARAM, 0, NULL);
        if (!ret) {
            rkFillMsgTail(pkt);
            return false;
        }
        break;
    case DtuParam:
        ret = rkPushTlvToMsg(pkt, TLV_TAG_ALL_DTU_PARAM, 0, NULL);
        if (!ret) {
            rkFillMsgTail(pkt);
            return false;
        }
        break;
    case AllParam: {
        switch(pos) {
        case 0:
            ret = rkPushTlvToMsg(pkt, TLV_TAG_ALL_SYS_PARAM, 0, NULL);
            if (!ret) {
                pos = 0;
                rkFillMsgTail(pkt);
                return false;
            }
        case 1:
            ret = rkPushTlvToMsg(pkt, TLV_TAG_ALL_COM_PARAM, 0, NULL);
            if (!ret) {
                pos = 1;
                rkFillMsgTail(pkt);
                return false;
            }
        case 2:
            ret = rkPushTlvToMsg(pkt, TLV_TAG_ALL_NET_PARAM, 0, NULL);
            if (!ret) {
                pos = 2;
                rkFillMsgTail(pkt);
                return false;
            }
        case 3:
            ret = rkPushTlvToMsg(pkt, TLV_TAG_ALL_ANALOG_PARAM, 0, NULL);
            if (!ret) {
                pos = 3;
                rkFillMsgTail(pkt);
                return false;
            }
        case 4:
            ret = rkPushTlvToMsg(pkt, TLV_TAG_ALL_SERIAL_PARAM, 0, NULL);
            if (!ret) {
                pos = 4;
                rkFillMsgTail(pkt);
                return false;
            }
        case 5:
            ret = rkPushTlvToMsg(pkt, TLV_TAG_ALL_DIO_PARAM, 0, NULL);
            if (!ret) {
                pos = 5;
                rkFillMsgTail(pkt);
                return false;
            }
        case 6:
            ret = rkPushTlvToMsg(pkt, TLV_TAG_ALL_DTU_PARAM, 0, NULL);
            if (!ret) {
                pos = 6;
                rkFillMsgTail(pkt);
                return false;
            }
        default:
            pos = 0;
            break;
        }
        break; }
    }

    rkFillMsgTail(pkt);

    return true;
}

bool rkPushConfigTlvsToMsg(rkMsgPkt_t &pkt, ParamType type)
{
    bool ret;
    static int pos = 0;

    switch(type) {
    case SystemParam:
        ret = rkPushSysConfigTlvsToMsg(pkt);
        break;
    case ComParam:
        ret = rkPushComConfigTlvsToMsg(pkt);
        break;
    case NetParam:
        ret = rkPushNetConfigTlvsToMsg(pkt);
        break;
    case AnalogParam:
        ret = rkPushAnalogConfigTlvsToMsg(pkt);
        break;
    case SerialParam:
        ret = rkPushSerialConfigTlvsToMsg(pkt);
        break;
    case DioParam:
        ret = rkPushDioConfigTlvsToMsg(pkt);
        break;
    case DtuParam:
        ret = rkPushDtuConfigTlvsToMsg(pkt);
        break;
    case AllParam: {
        switch(pos) {
        case 0:
            ret = rkPushSysConfigTlvsToMsg(pkt);
            if (!ret) {
                pos = 0;
                return false;
            }
        case 1:
            ret = rkPushComConfigTlvsToMsg(pkt);
            if (!ret) {
                pos = 1;
                return false;
            }
        case 2:
            ret = rkPushNetConfigTlvsToMsg(pkt);
            if (!ret) {
                pos = 2;
                return false;
            }
        case 3:
            ret = rkPushAnalogConfigTlvsToMsg(pkt);
            if (!ret) {
                pos = 3;
                return false;
            }
        case 4:
            ret = rkPushSerialConfigTlvsToMsg(pkt);
            if (!ret) {
                pos = 4;
                return false;
            }
        case 5:
            ret = rkPushDioConfigTlvsToMsg(pkt);
            if (!ret) {
                pos = 5;
                return false;
            }
        case 6:
            ret = rkPushDtuConfigTlvsToMsg(pkt);
            if (!ret) {
                pos = 6;
                return false;
            }
        default:
            pos = 0;
        }
        break; }
    }

    return ret;
}

bool rkGenMsgOfPutConfig(rkMsgPkt_t &pkt, enum ParamType type)
{
    bool ret;

    rkInitMsgHeader(pkt, (quint8)CW_PUT_PARAM_CONFIG);
    ret = rkPushConfigTlvsToMsg(pkt, type);
    rkFillMsgTail(pkt);

    return ret;
}

bool rkPushSysConfigTlvsToMsg(rkMsgPkt_t &pkt)
{
    static int pos = 0;
    bool ret;

    switch(pos) {
    case 0:
        ret = rkPushTlvToMsg(pkt, TLV_TAG_SIM_ID, strlen(g_tContext.m_tParamConfig.m_tSysParam.m_aSim), g_tContext.m_tParamConfig.m_tSysParam.m_aSim);
        if (!ret) {
            pos = 0;
            return false;
        }
    case 1:
        ret = rkPushTlvToMsg(pkt, TLV_TAG_MN_ID, strlen(g_tContext.m_tParamConfig.m_tSysParam.m_aMn), g_tContext.m_tParamConfig.m_tSysParam.m_aMn);
        if (!ret) {
            pos = 1;
            return false;
        }
    case 2:
        ret = rkPushTlvToMsg(pkt, TLV_TAG_SYSTEM_TYPE, 1, &g_tContext.m_tParamConfig.m_tSysParam.m_uSystemType);
        if (!ret) {
            pos = 2;
            return false;
        }
    case 3: {
        quint16	value = g_tContext.m_tParamConfig.m_tSysParam.m_sRtdStorageInterval;
        value = htons(value);
        ret = rkPushTlvToMsg(pkt, TLV_TAG_STORAGE_INTERVAL, 2, &value);
        if (!ret) {
            pos = 3;
            return false;
        }
    }
    case 4:
        ret = rkPushTlvToMsg(pkt, TLV_TAG_UPLOAD_TYPE, 1, &g_tContext.m_tParamConfig.m_tSysParam.m_uMsgUploadMode);
        if (!ret) {
            pos = 4;
            return false;
        }
    case 5: {
        quint16 value = g_tContext.m_tParamConfig.m_tSysParam.m_sMsgUploadInterval;
        value = htons(value);
        ret = rkPushTlvToMsg(pkt, TLV_TAG_UPLOAD_INTERVAL, 2, &value);
        if (!ret) {
            pos = 5;
            return false;
        }
    }
    case 6:
        ret = rkPushTlvToMsg(pkt, TLV_TAG_RTD_UPLOAD, 1, &g_tContext.m_tParamConfig.m_tSysParam.m_bRtdUpload);
        if (!ret) {
            pos = 6;
            return false;
        }
    case 7:
        ret = rkPushTlvToMsg(pkt, TLV_TAG_TMD_UPLOAD, 1, &g_tContext.m_tParamConfig.m_tSysParam.m_bTmdUpload);
        if (!ret) {
            pos = 7;
            return false;
        }
    case 8:
        ret = rkPushTlvToMsg(pkt, TLV_TAG_HSD_UPLOAD, 1, &g_tContext.m_tParamConfig.m_tSysParam.m_bHsdUpload);
        if (!ret) {
            pos = 8;
            return false;
        }
    case 9:
        ret = rkPushTlvToMsg(pkt, TLV_TAG_DSD_UPLOAD, 1, &g_tContext.m_tParamConfig.m_tSysParam.m_bDsdUpload);
        if (!ret) {
            pos = 9;
            return false;
        }
    case 10:
        ret = rkPushTlvToMsg(pkt, TLV_TAG_SWITCH_SENSE, 1, &g_tContext.m_tParamConfig.m_tSysParam.m_bSwitchSense);
        if (!ret) {
            pos = 10;
            return false;
        }
    case 11:
        ret = rkPushTlvToMsg(pkt, TLV_TAG_ALARM_ENABLE, 1, &g_tContext.m_tParamConfig.m_tSysParam.m_bAlarmEnable);
        if (!ret) {
            pos = 11;
            return false;
        }
    default:
        pos = 0;
    }

    return true;
}

bool rkPushComConfigTlvsToMsg(rkMsgPkt_t &pkt)
{
    bool ret;
    static int id = 0, pos = 0;

    for (id; id < COM_485_PORT_NUMBER; id++) {
        QString string;
        string.sprintf("baud=%d,databit=%d,stopbit=%d,parity=%d",
                       g_tContext.m_tParamConfig.m_aComParam[id].m_nBaud,
                       g_tContext.m_tParamConfig.m_aComParam[id].m_uDataBit,
                       g_tContext.m_tParamConfig.m_aComParam[id].m_uStopBit,
                       g_tContext.m_tParamConfig.m_aComParam[id].m_uParity);
        QByteArray byteArray(string.toLatin1());
        switch(pos) {
        case 0:
            ret = rkPushTlvToMsg(pkt, TLV_TAG_COM1_PARAM + id * 2, byteArray.length(), byteArray.data());
            if (!ret) {
                pos = 0;
                return false;
            }
        case 1:
            ret = rkPushTlvToMsg(pkt, TLV_TAG_COM1_PROTOCOL + id * 2, strlen(g_tContext.m_tParamConfig.m_aComParam[id].m_aProtocol), g_tContext.m_tParamConfig.m_aComParam[id].m_aProtocol);
            if (!ret) {
                pos = 1;
                return false;
            }
        default:
            pos = 0;
        }
    }
    id = 0;

    return true;
}

bool rkPushNetConfigTlvsToMsg(rkMsgPkt_t &pkt)
{
    bool ret;
    static int pos = 0;
    switch(pos) {
    case 0:
        ret = rkPushTlvToMsg(pkt, TLV_TAG_LINK_MODE, 1, &g_tContext.m_tParamConfig.m_tNetParam.m_uLinkMode);
        if (!ret) {
            pos = 0;
            return false;
        }
    case 1:
        ret = rkPushTlvToMsg(pkt, TLV_TAG_DEVICE_IP_ADDR, strlen(g_tContext.m_tParamConfig.m_tNetParam.m_aDeviceIpAddr), g_tContext.m_tParamConfig.m_tNetParam.m_aDeviceIpAddr);
        if (!ret) {
            pos = 1;
            return false;
        }
    case 2:
        ret = rkPushTlvToMsg(pkt, TLV_TAG_DEVICE_NETMASK, strlen(g_tContext.m_tParamConfig.m_tNetParam.m_aDeviceNetMask), g_tContext.m_tParamConfig.m_tNetParam.m_aDeviceNetMask);
        if (!ret) {
            pos = 2;
            return false;
        }
    case 3:
        ret = rkPushTlvToMsg(pkt, TLV_TAG_REMOTE_IP_ADDR, strlen(g_tContext.m_tParamConfig.m_tNetParam.m_aRemoteIpAddr), g_tContext.m_tParamConfig.m_tNetParam.m_aRemoteIpAddr);
        if (!ret) {
            pos = 3;
            return false;
        }
    case 4: {
        quint16	value = g_tContext.m_tParamConfig.m_tNetParam.m_sRemotePort;
        value = htons(value);
        ret = rkPushTlvToMsg(pkt, TLV_TAG_REMOTE_PORT, 2, &value);
        if (!ret) {
            pos = 4;
            return false;
        }
    }
    default:
        pos = 0;
    }

    return true;
}

bool rkPushAnalogConfigTlvsToMsg(rkMsgPkt_t &pkt)
{
    static int id = 0;
    bool ret;

    for (id; id < ANALOG_CHANNEL_TOTAL_NUMBER; id++) {
        QString string;
        string.sprintf("inuse=%d,type=%d,code=%s,ulv=%f,llv=%f,utv=%f,ltv=%f,convert=%d,formula=%s",
                       g_tContext.m_tParamConfig.m_aAnalogParam[id].m_bInuse,
                       g_tContext.m_tParamConfig.m_aAnalogParam[id].m_uType,
                       g_tContext.m_tParamConfig.m_aAnalogParam[id].m_aCode,
                       g_tContext.m_tParamConfig.m_aAnalogParam[id].m_fUpperLimitValue,
                       g_tContext.m_tParamConfig.m_aAnalogParam[id].m_fLowerLimitValue,
                       g_tContext.m_tParamConfig.m_aAnalogParam[id].m_fUpperThresholdValue,
                       g_tContext.m_tParamConfig.m_aAnalogParam[id].m_fLowerThresholdValue,
                       g_tContext.m_tParamConfig.m_aAnalogParam[id].m_uConvertFlag,
                       g_tContext.m_tParamConfig.m_aAnalogParam[id].m_aFormula);
        QByteArray byteArray(string.toLatin1());
        ret = rkPushTlvToMsg(pkt, TLV_TAG_ANALOG_CH1_PARAM + id, byteArray.length(), byteArray.data());
        if (!ret) {
            return false;
        }
    }
    id = 0;

    return true;
}

bool rkPushSerialConfigTlvsToMsg(rkMsgPkt_t &pkt)
{
    static int id = 0;
    bool ret;

    for (id; id < SERIAL_CHANNEL_TOTAL_NUMBER; id++) {
        QString string;
        string.sprintf("inuse=%d,code=%s,com=%d,type=%d,devaddr=%d,regaddr=%d,ulv=%f,llv=%f,utv=%f,ltv=%f,convert=%d,formula=%s",
                       g_tContext.m_tParamConfig.m_aSerialParam[id].m_bInuse,
                       g_tContext.m_tParamConfig.m_aSerialParam[id].m_aCode,
                       g_tContext.m_tParamConfig.m_aSerialParam[id].m_uComId,
                       g_tContext.m_tParamConfig.m_aSerialParam[id].m_uType,
                       g_tContext.m_tParamConfig.m_aSerialParam[id].m_uDevAddr,
                       g_tContext.m_tParamConfig.m_aSerialParam[id].m_sRegAddr,
                       g_tContext.m_tParamConfig.m_aSerialParam[id].m_fUpperLimitValue,
                       g_tContext.m_tParamConfig.m_aSerialParam[id].m_fLowerLimitValue,
                       g_tContext.m_tParamConfig.m_aSerialParam[id].m_fUpperThresholdValue,
                       g_tContext.m_tParamConfig.m_aSerialParam[id].m_fLowerThresholdValue,
                       g_tContext.m_tParamConfig.m_aSerialParam[id].m_uConvertFlag,
                       g_tContext.m_tParamConfig.m_aSerialParam[id].m_aFormula);
        QByteArray byteArray(string.toLatin1());
        ret = rkPushTlvToMsg(pkt, TLV_TAG_SERIAL_CH1_PARAM + id, byteArray.length(), byteArray.data());
        if (!ret) {
            return false;
        }
    }
    id = 0;

    return true;
}

bool rkPushDioConfigTlvsToMsg(rkMsgPkt_t &pkt)
{
    static int pos = 0, id = 0;
    bool ret;

    switch(pos) {
    case 0:
        for (id; id < DIGITAL_INPUT_PORT_NUMBER; id++) {
            QString string;
            string.sprintf("inuse=%d,code=%s",
                           g_tContext.m_tParamConfig.m_aDiParam[id].m_bInuse,
                           g_tContext.m_tParamConfig.m_aDiParam[id].m_aCode);
            QByteArray byteArray(string.toLatin1());
            ret = rkPushTlvToMsg(pkt, TLV_TAG_DI_CH1_PARAM + id, byteArray.length(), byteArray.data());
            if (!ret) {
                return false;
            }
        }
        pos = 1;
        id = 0;
    case 1:
        for (id; id < DIGITAL_OUTPUT_PORT_NUMBER; id++) {
            QString string;
            string.sprintf("inuse=%d,code=%s,status=%d",
                           g_tContext.m_tParamConfig.m_aDoParam[id].m_bInuse,
                           g_tContext.m_tParamConfig.m_aDoParam[id].m_aCode,
                           g_tContext.m_tParamConfig.m_aDoParam[id].m_bIsOn);
            QByteArray byteArray(string.toLatin1());
            ret = rkPushTlvToMsg(pkt, TLV_TAG_DO_CH1_PARAM + id, byteArray.length(), byteArray.data());
            if (!ret) {
                return false;
            }
        }
    default:
        pos = 0;
        id = 0;
    }

    return true;
}

bool rkPushDtuConfigTlvsToMsg(rkMsgPkt_t &)
{
    return true;
}

bool rkVerifyMsgTail(rkMsgPkt_t &pkt)
{
    quint16 calc_crc, msg_crc;

    msg_crc = pkt.m_aMsg[pkt.m_sLen - 2] << 8 | pkt.m_aMsg[pkt.m_sLen - 1];
    calc_crc = rkCrc16(pkt.m_aMsg, pkt.m_sLen - 2);

    //qDebug("MSG_CRC:%04X, CALC_CRC:%04X", msg_crc, calc_crc);
    if (msg_crc == calc_crc) {
        return true;
    }

    return false;
}

bool rkParseParamConfig(rkMsgPkt_t &pkt)
{
    int pos = 0;
    quint16 tag, len;
    quint8 *value = NULL;

    while(pos < pkt.m_sLen - RK_PROTOCOL_TAIL_LEN) {
        //tag = ntohs(pkt.m_aMsg[pos++] << 8 | pkt.m_aMsg[pos++]);
        tag = pkt.m_aMsg[pos] << 8 | pkt.m_aMsg[pos + 1];
        pos += 2;
        //len = ntohs(pkt.m_aMsg[pos++] << 8 | pkt.m_aMsg[pos++]);
        len = pkt.m_aMsg[pos] << 8 | pkt.m_aMsg[pos + 1];
        pos += 2;
        value = pkt.m_aMsg + pos;
        pos += len;
        //qDebug("TAG:%04X, LEN:%04X", tag, len);

        if (tag >= TLV_TAG_COM1_PARAM && tag <= TLV_TAG_COM4_PROTOCOL) {
            int index = (tag - TLV_TAG_COM1_PARAM) / 2;
            if ((tag - TLV_TAG_COM1_PARAM) % 2) {// PROTOCOL
                memset(g_tContext.m_tParamConfig.m_aComParam[index].m_aProtocol, 0, 32);
                memcpy(g_tContext.m_tParamConfig.m_aComParam[index].m_aProtocol, value, len);
            } else {//PARAM
                char buf[64];
                char *ptr;
                memset(buf, 0, sizeof(buf));
                memcpy(buf, value, len);
#ifdef DEBUG_LEVEL_MESSAGE_PARSE_OUTPUT
                qDebug("COM[%d]", index);
                qDebug() << buf;
#endif
                ptr = strstr(buf, "baud=");
                if (ptr)
                    g_tContext.m_tParamConfig.m_aComParam[index].m_nBaud = atoi(ptr + 5);
                ptr = strstr(buf, "databit=");
                if (ptr)
                    g_tContext.m_tParamConfig.m_aComParam[index].m_uDataBit = atoi(ptr + 8);
                ptr = strstr(buf, "stopbit=");
                if (ptr)
                    g_tContext.m_tParamConfig.m_aComParam[index].m_uStopBit = atoi(ptr + 8);
                ptr = strstr(buf, "parity=");
                if (ptr)
                    g_tContext.m_tParamConfig.m_aComParam[index].m_uParity = atoi(ptr + 7);
            }
            continue;
        }

        if(tag >= TLV_TAG_ANALOG_CH1_PARAM && tag <= TLV_TAG_ANALOG_CH16_PARAM) {
            int index = tag - TLV_TAG_ANALOG_CH1_PARAM;
            char buf[512];
            memset(buf, 0, len + 1);
            memcpy(buf, value, len);
#ifdef DEBUG_LEVEL_MESSAGE_PARSE_OUTPUT
            qDebug("Analog[%d]", index);
            qDebug() << buf;
#endif
            char *ptr = strstr(buf, "inuse=");
            if (ptr) {
                g_tContext.m_tParamConfig.m_aAnalogParam[index].m_bInuse = atoi(ptr + 6) ? 1 : 0;
                g_tContext.m_tParamConfig.m_aAnalogParam[index].m_tMutex.lock();
                g_tContext.m_tParamConfig.m_aAnalogParam[index].m_bDataChanged = true;
                g_tContext.m_tParamConfig.m_aAnalogParam[index].m_tMutex.unlock();
            }
            ptr = strstr(buf, "type=");
            if (ptr)
                g_tContext.m_tParamConfig.m_aAnalogParam[index].m_uType = atoi(ptr + 5);
            ptr = strstr(buf, "code=");
            if (ptr) {
                ptr += 5;
                char *tmp_ptr = strchr(ptr, ',');
                memset(g_tContext.m_tParamConfig.m_aAnalogParam[index].m_aCode, 0, 8);
                if (tmp_ptr) {
                    memcpy(g_tContext.m_tParamConfig.m_aAnalogParam[index].m_aCode, ptr, tmp_ptr - ptr);
                } else {
                    strcpy_s(g_tContext.m_tParamConfig.m_aAnalogParam[index].m_aCode, ptr);
                }
            }
            ptr = strstr(buf, "ulv=");
            if (ptr)
                g_tContext.m_tParamConfig.m_aAnalogParam[index].m_fUpperLimitValue = atof(ptr + 4);
            ptr = strstr(buf, "llv=");
            if (ptr)
                g_tContext.m_tParamConfig.m_aAnalogParam[index].m_fLowerLimitValue = atof(ptr + 4);
            ptr = strstr(buf, "utv=");
            if (ptr)
                g_tContext.m_tParamConfig.m_aAnalogParam[index].m_fUpperThresholdValue = atof(ptr + 4);
            ptr = strstr(buf, "ltv=");
            if (ptr)
                g_tContext.m_tParamConfig.m_aAnalogParam[index].m_fLowerThresholdValue = atof(ptr + 4);
            ptr = strstr(buf, "convert=");
            if (ptr) {
                g_tContext.m_tParamConfig.m_aAnalogParam[index].m_uConvertFlag = atoi(ptr + 8) ? 1 : 0;
                g_tContext.m_tParamConfig.m_aAnalogParam[index].m_tMutex.lock();
                g_tContext.m_tParamConfig.m_aAnalogParam[index].m_bDataChanged = true;
                g_tContext.m_tParamConfig.m_aAnalogParam[index].m_tMutex.unlock();
            }
            ptr = strstr(buf, "formula=");
            if (ptr) {
                ptr += 8;
                char *tmp_ptr = strchr(ptr, ',');
                memset(g_tContext.m_tParamConfig.m_aAnalogParam[index].m_aFormula, 0, sizeof(g_tContext.m_tParamConfig.m_aAnalogParam[index].m_aFormula));
                if (tmp_ptr) {
                    memcpy(g_tContext.m_tParamConfig.m_aAnalogParam[index].m_aFormula, ptr, tmp_ptr - ptr);
                } else {
                    strcpy_s(g_tContext.m_tParamConfig.m_aAnalogParam[index].m_aFormula, ptr);
                }
            }
            continue;
        }

        if(tag >= TLV_TAG_SERIAL_CH1_PARAM && tag <= TLV_TAG_SERIAL_CH32_PARAM) {
            int index = tag - TLV_TAG_SERIAL_CH1_PARAM;
            char buf[512];
            memset(buf, 0, len + 1);
            memcpy(buf, value, len);
#ifdef DEBUG_LEVEL_MESSAGE_PARSE_OUTPUT
            qDebug("Serial[%d]", index);
            qDebug() << buf;
#endif
            char *ptr = strstr(buf, "inuse=");
            //qDebug() << buf;
            if (ptr) {
                g_tContext.m_tParamConfig.m_aSerialParam[index].m_bInuse = atoi(ptr + 6) ? 1 : 0;
                g_tContext.m_tParamConfig.m_aSerialParam[index].m_tMutex.lock();
                g_tContext.m_tParamConfig.m_aSerialParam[index].m_bDataChanged = true;
                g_tContext.m_tParamConfig.m_aSerialParam[index].m_tMutex.unlock();
            }
            ptr = strstr(buf, "type=");
            if (ptr)
                g_tContext.m_tParamConfig.m_aSerialParam[index].m_uType = atoi(ptr + 5);
            ptr = strstr(buf, "code=");
            if (ptr) {
                ptr += 5;
                char *tmp_ptr = strchr(ptr, ',');
                memset(g_tContext.m_tParamConfig.m_aSerialParam[index].m_aCode, 0, 8);
                if (tmp_ptr) {
                    memcpy(g_tContext.m_tParamConfig.m_aSerialParam[index].m_aCode, ptr, tmp_ptr - ptr);
                } else {
                    strcpy_s(g_tContext.m_tParamConfig.m_aSerialParam[index].m_aCode, ptr);
                }
            }
            ptr = strstr(buf, "com=");
            if (ptr)
                g_tContext.m_tParamConfig.m_aSerialParam[index].m_uComId = atoi(ptr + 4);
            ptr = strstr(buf, "devaddr=");
            if (ptr)
                g_tContext.m_tParamConfig.m_aSerialParam[index].m_uDevAddr = atoi(ptr + 8);
            ptr = strstr(buf, "regaddr=");
            if (ptr)
                g_tContext.m_tParamConfig.m_aSerialParam[index].m_sRegAddr = atoi(ptr + 8);
            ptr = strstr(buf, "ulv=");
            if (ptr)
                g_tContext.m_tParamConfig.m_aSerialParam[index].m_fUpperLimitValue = atof(ptr + 4);
            ptr = strstr(buf, "llv=");
            if (ptr)
                g_tContext.m_tParamConfig.m_aSerialParam[index].m_fLowerLimitValue = atof(ptr + 4);
            ptr = strstr(buf, "utv=");
            if (ptr)
                g_tContext.m_tParamConfig.m_aSerialParam[index].m_fUpperThresholdValue = atof(ptr + 4);
            ptr = strstr(buf, "ltv=");
            if (ptr)
                g_tContext.m_tParamConfig.m_aSerialParam[index].m_fLowerThresholdValue = atof(ptr + 4);
            ptr = strstr(buf, "convert=");
            if (ptr) {
                g_tContext.m_tParamConfig.m_aSerialParam[index].m_uConvertFlag = atoi(ptr + 8) ? 1 : 0;
                g_tContext.m_tParamConfig.m_aSerialParam[index].m_tMutex.lock();
                g_tContext.m_tParamConfig.m_aSerialParam[index].m_bDataChanged = true;
                g_tContext.m_tParamConfig.m_aSerialParam[index].m_tMutex.unlock();
            }
            ptr = strstr(buf, "formula=");
            if (ptr) {
                ptr += 8;
                char *tmp_ptr = strchr(ptr, ',');
                memset(g_tContext.m_tParamConfig.m_aSerialParam[index].m_aFormula, 0, sizeof(g_tContext.m_tParamConfig.m_aSerialParam[index].m_aFormula));
                if (tmp_ptr) {
                    memcpy(g_tContext.m_tParamConfig.m_aSerialParam[index].m_aFormula, ptr, tmp_ptr - ptr);
                } else {
                    strcpy_s(g_tContext.m_tParamConfig.m_aSerialParam[index].m_aFormula, ptr);
                }
            }
            continue;
        }

        if(tag >= TLV_TAG_DI_CH1_PARAM && tag <= TLV_TAG_DI_CH8_PARAM) {
            int index = tag - TLV_TAG_DI_CH1_PARAM;
            char buf[128], *ptr = NULL;
            memset(buf, 0, sizeof(buf));
            memcpy(buf, value, len);
#ifdef DEBUG_LEVEL_MESSAGE_PARSE_OUTPUT
            qDebug("DI[%d]", index);
            qDebug() << buf;
#endif
            ptr = strstr(buf, "inuse=");
            if (ptr) {
                g_tContext.m_tParamConfig.m_aDiParam[index].m_bInuse = atoi(ptr + 6) ? 1 : 0;
                g_tContext.m_tParamConfig.m_aDiParam[index].m_tMutex.lock();
                g_tContext.m_tParamConfig.m_aDiParam[index].m_bDataChanged = true;
                g_tContext.m_tParamConfig.m_aDiParam[index].m_tMutex.unlock();
            }

            ptr = strstr(buf, "code=");
            if (ptr) {
                ptr += 5;
                char *tmp_ptr = strchr(ptr, ',');
                memset(g_tContext.m_tParamConfig.m_aDiParam[index].m_aCode, 0, sizeof(g_tContext.m_tParamConfig.m_aDiParam[index].m_aCode));
                if (tmp_ptr) {
                    memcpy(g_tContext.m_tParamConfig.m_aDiParam[index].m_aCode, ptr, tmp_ptr - ptr);
                } else {
                    strcpy_s(g_tContext.m_tParamConfig.m_aDiParam[index].m_aCode, ptr);
                }
            }
            continue;
        }

        if (tag >= TLV_TAG_DO_CH1_PARAM && tag <= TLV_TAG_DO_CH8_PARAM) {
            int index = tag - TLV_TAG_DO_CH1_PARAM;
            char buf[128], *ptr = NULL;
            memset(buf, 0, sizeof(buf));
            memcpy(buf, value, len);
#ifdef DEBUG_LEVEL_MESSAGE_PARSE_OUTPUT
            qDebug("DO[%d]", index);
            qDebug() << buf;
#endif
            ptr = strstr(buf, "inuse=");
            if (ptr) {
                g_tContext.m_tParamConfig.m_aDoParam[index].m_bInuse = atoi(ptr + 6) ? 1 : 0;
                g_tContext.m_tParamConfig.m_aDoParam[index].m_tMutex.lock();
                g_tContext.m_tParamConfig.m_aDoParam[index].m_bDataChanged = true;
                g_tContext.m_tParamConfig.m_aDoParam[index].m_tMutex.unlock();
            }

            ptr = strstr(buf, "code=");
            if (ptr) {
                ptr += 5;
                char *tmp = strchr(ptr, ',');
                memset(g_tContext.m_tParamConfig.m_aDoParam[index].m_aCode, 0, sizeof(g_tContext.m_tParamConfig.m_aDoParam[index].m_aCode));
                if (tmp) {
                    memcpy(g_tContext.m_tParamConfig.m_aDoParam[index].m_aCode, ptr, tmp - ptr);
                } else {
                    strcpy_s(g_tContext.m_tParamConfig.m_aDoParam[index].m_aCode, ptr);
                }
            }

            ptr = strstr(buf, "status=");
            if (ptr) {
                g_tContext.m_tParamConfig.m_aDoParam[index].m_bIsOn = atoi(ptr + 7) ? 1 : 0;
                g_tContext.m_tParamConfig.m_aDoParam[index].m_tMutex.lock();
                g_tContext.m_tParamConfig.m_aDoParam[index].m_bDataChanged = true;
                g_tContext.m_tParamConfig.m_aDoParam[index].m_tMutex.unlock();
            }
            continue;
        }

        switch(tag) {
        case TLV_TAG_SIM_ID:
            memset(g_tContext.m_tParamConfig.m_tSysParam.m_aSim, 0, 12);
            memcpy(g_tContext.m_tParamConfig.m_tSysParam.m_aSim, value, len);
#ifdef DEBUG_LEVEL_MESSAGE_PARSE_OUTPUT
            qDebug() << "Sim Num: " << g_tContext.m_tParamConfig.m_tSysParam.m_aSim;
#endif
            break;
        case TLV_TAG_MN_ID:
            memset(g_tContext.m_tParamConfig.m_tSysParam.m_aMn, 0, 16);
            memcpy(g_tContext.m_tParamConfig.m_tSysParam.m_aMn, value, len);
#ifdef DEBUG_LEVEL_MESSAGE_PARSE_OUTPUT
            qDebug() << "MN Num: " << g_tContext.m_tParamConfig.m_tSysParam.m_aMn;
#endif
            break;
        case TLV_TAG_SYSTEM_TYPE:
            g_tContext.m_tParamConfig.m_tSysParam.m_uSystemType = value[0];
            break;
        case TLV_TAG_STORAGE_INTERVAL:
            g_tContext.m_tParamConfig.m_tSysParam.m_sRtdStorageInterval = value[0] << 8 | value[1];
            break;
        case TLV_TAG_UPLOAD_TYPE:
            g_tContext.m_tParamConfig.m_tSysParam.m_uMsgUploadMode = value[0];
            break;
        case TLV_TAG_UPLOAD_INTERVAL:
            g_tContext.m_tParamConfig.m_tSysParam.m_sMsgUploadInterval = value[0] << 8 | value[1];
            break;
        case TLV_TAG_RTD_UPLOAD:
            g_tContext.m_tParamConfig.m_tSysParam.m_bRtdUpload = value[0];
            g_tContext.m_tParamConfig.m_tSysParam.m_tMutex.lock();
            g_tContext.m_tParamConfig.m_tSysParam.m_bDataChanged = true;
            g_tContext.m_tParamConfig.m_tSysParam.m_tMutex.unlock();
            break;
        case TLV_TAG_TMD_UPLOAD:
            g_tContext.m_tParamConfig.m_tSysParam.m_bTmdUpload = value[0];
            g_tContext.m_tParamConfig.m_tSysParam.m_tMutex.lock();
            g_tContext.m_tParamConfig.m_tSysParam.m_bDataChanged = true;
            g_tContext.m_tParamConfig.m_tSysParam.m_tMutex.unlock();
            break;
        case TLV_TAG_HSD_UPLOAD:
            g_tContext.m_tParamConfig.m_tSysParam.m_bHsdUpload = value[0];
            g_tContext.m_tParamConfig.m_tSysParam.m_tMutex.lock();
            g_tContext.m_tParamConfig.m_tSysParam.m_bDataChanged = true;
            g_tContext.m_tParamConfig.m_tSysParam.m_tMutex.unlock();
            break;
        case TLV_TAG_DSD_UPLOAD:
            g_tContext.m_tParamConfig.m_tSysParam.m_bDsdUpload = value[0];
            g_tContext.m_tParamConfig.m_tSysParam.m_tMutex.lock();
            g_tContext.m_tParamConfig.m_tSysParam.m_bDataChanged = true;
            g_tContext.m_tParamConfig.m_tSysParam.m_tMutex.unlock();
            break;
        case TLV_TAG_SWITCH_SENSE:
            g_tContext.m_tParamConfig.m_tSysParam.m_bSwitchSense = value[0];
            g_tContext.m_tParamConfig.m_tSysParam.m_tMutex.lock();
            g_tContext.m_tParamConfig.m_tSysParam.m_bDataChanged = true;
            g_tContext.m_tParamConfig.m_tSysParam.m_tMutex.unlock();
            break;
        case TLV_TAG_ALARM_ENABLE:
            g_tContext.m_tParamConfig.m_tSysParam.m_bAlarmEnable = value[0];
            g_tContext.m_tParamConfig.m_tSysParam.m_tMutex.lock();
            g_tContext.m_tParamConfig.m_tSysParam.m_bDataChanged = true;
            g_tContext.m_tParamConfig.m_tSysParam.m_tMutex.unlock();
            break;
        case TLV_TAG_LINK_MODE:
            g_tContext.m_tParamConfig.m_tNetParam.m_uLinkMode = value[0];
            break;
        case TLV_TAG_DEVICE_IP_ADDR:
            memcpy(g_tContext.m_tParamConfig.m_tNetParam.m_aDeviceIpAddr, value, len);
            g_tContext.m_tParamConfig.m_tNetParam.m_aDeviceIpAddr[len] = 0;
            break;
        case TLV_TAG_DEVICE_NETMASK:
            memcpy(g_tContext.m_tParamConfig.m_tNetParam.m_aDeviceNetMask, value, len);
            g_tContext.m_tParamConfig.m_tNetParam.m_aDeviceNetMask[len] = 0;
            break;
        case TLV_TAG_REMOTE_IP_ADDR:
            memcpy(g_tContext.m_tParamConfig.m_tNetParam.m_aRemoteIpAddr, value, len);
            g_tContext.m_tParamConfig.m_tNetParam.m_aRemoteIpAddr[len] = 0;
            break;
        case TLV_TAG_REMOTE_PORT:
            g_tContext.m_tParamConfig.m_tNetParam.m_sRemotePort = value[0] << 8 | value[1];
            break;
        }
    }

    return true;
}

bool rkParseFirmwareVersion(rkMsgPkt_t &pkt)
{
    int pos = 0;
    quint16 tag, len;
    quint8 *value = NULL;

    while(pos < pkt.m_sLen - RK_PROTOCOL_TAIL_LEN) {
        tag = pkt.m_aMsg[pos] << 8 | pkt.m_aMsg[pos + 1];
        pos += 2;
        len = pkt.m_aMsg[pos] << 8 | pkt.m_aMsg[pos + 1];
        pos += 2;
        value = pkt.m_aMsg + pos;
        pos += len;
        //qDebug("TAG:%04X, LEN:%04X", tag, len);

        switch(tag) {
        case TLV_TAG_HMI_VERSION:
            memset(g_tContext.m_aHmiVersion, 0, 32);
            memcpy(g_tContext.m_aHmiVersion, value, len);
            break;
        case TLV_TAG_BLP_VERSION:
            memset(g_tContext.m_aBlpVersion, 0, 32);
            memcpy(g_tContext.m_aBlpVersion, value, len);
            break;
        case TLV_TAG_DTU_TOOL_VERSION:
            memset(g_tContext.m_aDtuToolVersion, 0, 32);
            memcpy(g_tContext.m_aDtuToolVersion, value, len);
            break;
        default:
            break;
        }
    }

    return true;
}

bool rkGenMsgOfGetFirmwareVersion(rkMsgPkt_t &pkt, int type)
{
    rkInitMsgHeader(pkt, CW_GET_FIRMWARE_VERSION);
    switch(type) {
    case 0:
        rkPushTlvToMsg(pkt, TLV_TAG_ALL_FIRMWARE_VERSION, 0, NULL);
        break;
    case 1:
        rkPushTlvToMsg(pkt, TLV_TAG_HMI_VERSION, 0, NULL);
        break;
    case 2:
        rkPushTlvToMsg(pkt, TLV_TAG_BLP_VERSION, 0, NULL);
        break;
    case 3:
        rkPushTlvToMsg(pkt, TLV_TAG_DTU_TOOL_VERSION, 0, NULL);
        break;
    default:
        break;
    }
    rkFillMsgTail(pkt);

    return true;
}

bool rkGenMsgOfUpgradeFirmware(int type, rkMsgPkt_t &pkt, quint8 *src, quint16 len, quint16 seq, quint8 flag)
{
    if (type == 0) {
        rkInitMsgHeader(pkt, (quint8)CW_UPGRADE_HMI_FIRMWARE);
    } else if (type == 1) {
        rkInitMsgHeader(pkt, (quint8)CW_UPGRADE_BLP_FIRMWARE);
    } else if (type == 2) {
        rkInitMsgHeader(pkt, (quint8)CW_UPGRADE_DTU_TOOL_FIRMWARE);
    } else {
        return false;
    }

    rkFtpMsgPkt *ftpMsg = (rkFtpMsgPkt *)pkt.m_aMsg;
    ftpMsg->m_sSeqNum = htons(seq);
    ftpMsg->m_uFlag = flag;
    ftpMsg->m_sLen = htons(len);
    memcpy(ftpMsg->m_aMsg, src, len);

    pkt.m_sLen += RK_FTP_HEADER_LEN + len;
    rkFillMsgTail(pkt);

    return true;
}

bool rkGenMsgOfGetSupportedDynamicProtocol(rkMsgPkt_t &pkt)
{
    rkInitMsgHeader(pkt, CW_GET_SUPPORTED_PROTOCOL);
    rkFillMsgTail(pkt);

    return true;
}

bool rkParseSupportedDynamicProtocol(rkMsgPkt_t &pkt)
{
    memset(g_tContext.m_aDynamicProtocolSet, 0, sizeof(g_tContext.m_aDynamicProtocolSet));
    memcpy(g_tContext.m_aDynamicProtocolSet, pkt.m_aMsg, pkt.m_sLen - RK_PROTOCOL_TAIL_LEN);

    return true;
}

void rkPrintMsg(rkMsgPkt_t &pkt, bool recvFlag)
{
#if 0
    printf("%02X ", pkt.m_aHeader[0]);
    printf("%02X ", pkt.m_aHeader[1]);
    printf("%02X ", pkt.m_aHeader[2]);
    printf("%02X ", pkt.m_uCmdWord);
    printf("%02X ", pkt.m_sLen >> 8);
    printf("%02X ", pkt.m_sLen & 0xFF);
    for(int index = 0; index < pkt.m_sLen; index++) {
        printf("%02X ", pkt.m_aMsg[index]);
    }
    printf("\n");
#else
    int len = pkt.m_sLen;
    pkt.m_sLen = htons(pkt.m_sLen);
    QByteArray byteArray = QByteArray::fromRawData((char *)&pkt, RK_PROTOCOL_HEADER_LEN + len).toHex().toUpper();
    for (int i = byteArray.length(); i > 0; i -= 2) {
        byteArray.insert(i, " ");
    }
    if (recvFlag) {
        qDebug() << "Recv:" << len + RK_PROTOCOL_HEADER_LEN;
    } else {
        qDebug() << "Send:" << len + RK_PROTOCOL_HEADER_LEN;
    }
    qDebug() << byteArray;
    pkt.m_sLen = ntohs(pkt.m_sLen);

#endif
}
