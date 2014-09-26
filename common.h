#ifndef COMMON_H
#define COMMON_H

#include <QMutex>
#include <QtGlobal>

#define DEBUG_MODE
//#define DEBUG_LEVEL_RAW_SEND_MESSAGE_OUTPUT
//#define DEBUG_LEVEL_RAW_RECV_MESSAGE_OUTPUT
//#define DEBUG_LEVEL_MESSAGE_PARSE_OUTPUT

#define PROGRAM_BETA_VERSION
#define PROGRAM_VERSION_NUM			"1.1.7"

#define APP_CONFIG_FILE_PATH 	"./configure"

#define APP_PARAM_GROUP_TARGET 	"Target"
#define APP_PARAM_ADDR 			"Address"
#define APP_PARAM_PORT			"Port"

#define DEFAULT_TARGET_ADDR		"192.168.205.100"
#define DEFAULT_TARGET_PORT		"8088"

#define SHADOW_WIDTH 			5
#define WINDOW_WIDTH			860
#define WINDOW_HEIGHT			610
#define WINDOW_START_X			0
#define WINDOW_START_Y			0
#define WINDOW_PAGE_COUNT		4

#define TOOL_BUTTON_ICON_WIDTH		64
#define TOOL_BUTTON_ICON_HEIGHT		60
#define TOOL_BUTTON_WIDTH			TOOL_BUTTON_ICON_WIDTH + 25
#define TOOL_BUTTON_HEIGHT			TOOL_BUTTON_ICON_HEIGHT + 25

#define ANALOG_CHANNEL_TOTAL_NUMBER		16
#define SERIAL_CHANNEL_TOTAL_NUMBER		32

#define COM_232_PORT_NUMBER	2
#define COM_485_PORT_NUMBER	4

#define DIGITAL_INPUT_PORT_NUMBER	8
#define DIGITAL_OUTPUT_PORT_NUMBER	8

#define MESSAGE_UPLOAD_BY_DTU 	0
#define MESSAGE_UPLOAD_BY_ETH	1
#define MESSAGE_UPLOAD_BY_DTU_AND_ETH	2

typedef struct SysParam {
    char 		m_aSim[12];
    char		m_aMn[16];
    quint8		m_uSystemType;
    quint8		m_uMsgUploadMode;
    quint16		m_sMsgUploadInterval;
    quint16		m_sRtdStorageInterval;
    bool		m_bRtdUpload;
    bool		m_bTmdUpload;
    bool		m_bHsdUpload;
    bool		m_bDsdUpload;
    bool		m_bSwitchSense;
    bool		m_bAlarmEnable;
    bool		m_bDataChanged;
    QMutex		m_tMutex;
} SysParam_t;

#define COM_WITH_NONE_PARITY		0
#define COM_WITH_ODD_PARITY		1
#define COM_WHTH_EVEN_PARITY		2

#define COM_WITH_1_STOP_BIT		0
#define COM_WITH_1P5_STOP_BIT	1
#define COM_WITH_2_STOP_BIT		2

typedef struct ComParam {
    quint32		m_nBaud;
    quint8		m_uDataBit;
    quint8		m_uStopBit;
    quint8		m_uParity;
    char		m_aProtocol[32];
} ComParam_t;

#define TCP_CLIENT_LINK_MODE 	0
#define UDP_CLIENT_LINK_MODE	1

typedef struct 	NetParam {
    quint8		m_uLinkMode;
    char		m_aDeviceIpAddr[16];
    char		m_aDeviceNetMask[16];
    char		m_aRemoteIpAddr[16];
    quint16		m_sRemotePort;
} NetParam_t;

#define ANALOG_TYPE_4_20MA		0
#define ANALOG_TYPE_0_5V		1

typedef struct AnalogParam {
    bool 		m_bInuse;
    quint8		m_uConvertFlag;
    quint8		m_uType;
    char		m_aCode[8];
    float		m_fUpperLimitValue;
    float		m_fLowerLimitValue;
    float		m_fUpperThresholdValue;
    float		m_fLowerThresholdValue;
    char		m_aFormula[64];
    bool		m_bDataChanged;
    QMutex		m_tMutex;
} AnalogParam_t;

#define SERIAL_TYPE_INTEGER		0
#define SERIAL_TYPE_FLOAT		1

#define SERIAL_WITH_COM_ID_0	0
#define SERIAL_WITH_COM_ID_1 	1
#define SERIAL_WITH_COM_ID_2 	2
#define SERIAL_WITH_COM_ID_3 	3

typedef struct SerialParam {
    bool		m_bInuse;
    quint8 		m_uConvertFlag;
    quint8		m_uType;
    quint8		m_uComId;
    quint8		m_uDevAddr;
    quint16		m_sRegAddr;
    float		m_fUpperLimitValue;
    float		m_fLowerLimitValue;
    float		m_fUpperThresholdValue;
    float		m_fLowerThresholdValue;
    char		m_aCode[8];
    char		m_aFormula[64];
    bool		m_bDataChanged;
    QMutex		m_tMutex;
} SerialParam_t;

typedef struct DiParam {
    bool		m_bInuse;
    bool		m_bDataChanged;
    char		m_aCode[8];
    QMutex		m_tMutex;
} DiParam_t;

typedef struct DoParam {
    bool 		m_bInuse;
    bool 		m_bIsOn;
    bool		m_bDataChanged;
    char		m_aCode[8];
    QMutex		m_tMutex;
} DoParam_t;

typedef struct ParamConfig {
    SysParam_t 	m_tSysParam;
    ComParam_t	m_aComParam[COM_485_PORT_NUMBER];
    NetParam_t	m_tNetParam;
    AnalogParam_t m_aAnalogParam[ANALOG_CHANNEL_TOTAL_NUMBER];
    SerialParam_t m_aSerialParam[SERIAL_CHANNEL_TOTAL_NUMBER];
    DiParam_t	m_aDiParam[DIGITAL_INPUT_PORT_NUMBER];
    DoParam_t	m_aDoParam[DIGITAL_OUTPUT_PORT_NUMBER];
} ParamConfig_t;

typedef struct Context {
    ParamConfig_t m_tParamConfig;
    char	m_aHmiVersion[32];
    char	m_aBlpVersion[32];
    char	m_aDtuToolVersion[32];
    char	m_aDynamicProtocolSet[512];
} Context_t;

#endif // COMMON_H
