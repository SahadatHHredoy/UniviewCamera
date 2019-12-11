
#ifndef _GLOBLE_DEF_H_
#define _GLOBLE_DEF_H_

#include "NetDEVSDK.h"   

#define NETDEMO_E_SUCCEED    0   /*Succeeded*/
#define NETDEMO_E_FAILED    -1   /*Failed*/


//MFC Message
#define        WM_VIDEO_MENU_BASE                WM_USER + 1979
#define        WM_VIDEO_MENU_END                 WM_USER + 1985
#define        WM_VIDEO_MENU_FULLSCREEN          WM_USER + 1979
#define        WM_VIDEO_MENU_MULTISCREEN         WM_USER + 1980
#define        WM_VIDEO_MENU_AUTOADJUST          WM_USER + 1981
#define        WM_VIDEO_MENU_RECORDVIDEO         WM_USER + 1982
#define        WM_VIDEO_MENU_PRINTSCREEN         WM_USER + 1983
#define        WM_VIDEO_MENU_EXITDECODE          WM_USER + 1984
#define        WM_VIDEO_MENU_EXITCYCLE           WM_USER + 1985
#define        WM_VIDEO_REPAINT                  WM_USER + 1999
#define        WM_ADD_DEVICE                     WM_USER + 2000      
#define        WM_CLICK_REALPLAY_WND             WM_USER + 2001
#define        WM_CLICK_PLAYBACK_WND             WM_USER + 2002
#define        WM_REALPLAY_SET_AUDIO_PARA        WM_USER + 2011



#define NETDEMO_MAX_SCREENNUM                     16                //Max Screen number
#define NETDEMO_MAX_DEVICES                       512               //Max device number
#define NETDEMO_MAX_LOGNUM                        2000
#define LOG_DESCRIB_TEMP                          512               //Clint log max size
#define METDEMO_CLINETLIST_ENLARGE_HIGH           575               //enlarge height of    local log or alarm list

#define NETDEMO_DEV_CFG_FILE_NAME   "DeviceCfg.dat"


#define NETDEMO_VIDEO_BACK_COLOR  RGB(0,0,0)

#define NETDEMO_DLG_SPLITTYPE_1            "1"
#define NETDEMO_DLG_SPLITTYPE_4            "4"
#define NETDEMO_DLG_SPLITTYPE_9            "9"
#define NETDEMO_DLG_SPLITTYPE_16           "16"

#define NETDEMO_CYCLE_MIN_INTERVAL         20
#define NETDEMO_CYCLE_MAX_INTERVAL         300
typedef enum tagNetDemoCycleType
{
    NETDEMO_CYCLETYPE_SINGLE = 0,
    NETDEMO_CYCLETYPE_ALLSCREEN

}NETDEMO_CYCLE_TYPE;

typedef enum tagClientLogLevel
{
    NETDEMO_OPERATION_SUCC = 0,         //operation succeed
    NETDEMO_OPERATION_FAIL = 1,          //operation fail
    NETDEMO_OPERATION_INFO
}NETDEMO_CLIENT_LOG_LEVEL;

//device list config
typedef enum tagNETDEMOTreeNode
{
    NETDEMO_NO_DEVICE   = -1,
    NETDEMO_NETDEMO_TREE_ALL_T    = 0,        //root node
    NETDEMO_TYPE_DEVICE     = 1,      //device
    NETDEMO_TYPE_CHANNEL    = 2          //channel
}NETDEMO_TREE_NODE;

//Primary Menu dialog type
typedef enum tagNETDEMOMenuPrimaryType
{
    NETDEMO_MANU_INDEX_LIVEVIEW = 0,
    NETDEMO_MANU_INDEX_PLAYBACK,
    NETDEMO_MANU_INDEX_CFG,
    NETDEMO_MANU_INDEX_ALARMRECORDS,
    NETDEMO_MANU_INDEX_VCA,
    NETDEMO_MANU_INDEX_MAINTAIN,
    NETDEMO_MANU_INDEX_USERCFG

}NETDEMO_MENU_PRIMARY_TYPE;


//child Menu about Configure
typedef enum tagNETDEMOMenuCfgChild
{
    NETDEMO_CFG_DEVICE =0,
    NETDEMO_CFG_NETWORK,
    NETDEMO_CFG_STREAM,
    NETDEMO_CFG_IMAGE,
    NETDEMO_CFG_OSD,
    NETDEMO_CFG_ALARM,
    NETDEMO_CFG_PRIVACYMASK,
    NETDEMO_CFG_MOTION,
    NETDEMO_CFG_TAMPER,
}NETDEMO_MENU_CFG_CHILD;


//child Menu about Alarm
typedef enum tagNETDEMOMenuAlarmChild
{
    NETDEMO_REAL_ALARM = 0,
    NETDEMO_HISTORY_ALARM
}NETDEMO_MENU_ALARM_CHILD;


typedef enum tagNetdemoSplitType{
    NETDEMO_SPLIT_TYPE_NULL = 0,
    NETDEMO_SPLIT_TYPE_REAL_PLAY,   
    NETDEMO_SPLIT_TYPE_PLAY_BACK,    
    NETDEMO_SPLIT_TYPE_CYCLEMONITOR
}NETDEMO_SPLITTYPE;

//Split type
typedef enum tagNETDEMOSplitNumber
{
    NETDEMO_SPLIT1 = 0,
    NETDEMO_SPLIT4,
    NETDEMO_SPLIT9,
    NETDEMO_SPLIT16,
    NETDEMO_SPLIT_TOTAL
}NETDEMO_SPLIT_NUMBER;

//login type
typedef enum tagNETDEMODEVLogType
{
    NETDEMO_LOGTYPE_UNKNOW = -1,
    NETDEMO_LOGTYPE_LOCAL,
    NETDEMO_LOGTYPE_CLOUD
}NETDEMO_DEV_LOGIN_TYPE;


typedef struct NETDEMO_BASIC_INFO_S
{
    NETDEV_TIME_CFG_S stSystemTime;
    char szDeviceName[NETDEV_LEN_64];
    NETDEV_DISK_INFO_LIST_S stDiskInfoList;
}NETDEMO_BASIC_INFO_S,*LPNETDEMO_BASIC_INFO_S;

typedef struct NETDEMO_NETWORK_INFO_S
{
    NETDEV_NETWORKCFG_S stNetWorkIP;
    NETDEV_UPNP_NAT_STATE_S stNetWorkPort;
    NETDEV_SYSTEM_NTP_INFO_LIST_S stNetWorkNTP;

}NETDEMO_NETWORK_INFO_S,*LPNETDEMO_NETWORK_INFO_S;

typedef struct NETDEMO_INPUT_INFO_S
{
    NETDEV_ALARM_INPUT_LIST_S stInPutInfo;
//    NETDEV_ALARM_OUTPUT_INFO_S stOutPutInfo;
    NETDEV_ALARM_OUTPUT_LIST_S stOutPutInfo;
}NETDEMO_INPUT_INFO_S,*LPNETDEMO_INPUT_INFO_S;

//device index info
typedef struct NETDEMO_CHANNEL_INFO
{ 
    INT32   dwDeviceIndex;          //device index 
    INT32   dwChlID;                //channel ID
    BOOL    bIsRecording;
    NETDEV_VIDEO_CHL_DETAIL_INFO_S stChlDetailInfo;
    NETDEV_PREVIEWINFO_S stPriViewWinfo;
    NETDEV_VIDEO_EFFECT_S stVideoEffect;
    NETDEV_CRUISE_LIST_S stCruiseList;

    LPNETDEMO_BASIC_INFO_S pstBasicInfo;
    LPNETDEMO_NETWORK_INFO_S pstNetworkInfo;
    LPNETDEV_VIDEO_STREAM_INFO_S pstVideoStreamInfo;
    LPNETDEV_IMAGE_SETTING_S pstImageInfo;
    LPNETDEV_VIDEO_OSD_CFG_S pstOSDInfo;
    LPNETDEMO_INPUT_INFO_S pstIOInfo;
    LPNETDEV_PRIVACY_MASK_CFG_S pstPrivacyMaskInfo;
    LPNETDEV_MOTION_ALARM_INFO_S pstMotionAlarmInfo;
    LPNETDEV_TAMPER_ALARM_INFO_S pstTamperAlarmInfo;

    NETDEMO_CHANNEL_INFO()
    {
        dwDeviceIndex   = 0;
        dwChlID = 0;
        bIsRecording = TRUE;
        pstBasicInfo = NULL;
        pstNetworkInfo = NULL;
        pstVideoStreamInfo = NULL;
        pstImageInfo = NULL;
        pstOSDInfo = NULL;
        pstIOInfo = NULL;
        pstPrivacyMaskInfo = NULL;
        pstMotionAlarmInfo = NULL;
        pstTamperAlarmInfo = NULL;
        memset(&stChlDetailInfo,0,sizeof(stChlDetailInfo));
        memset(&stPriViewWinfo,0,sizeof(stPriViewWinfo));
        memset(&stVideoEffect,0,sizeof(stVideoEffect));
        memset(&stCruiseList,0,sizeof(stCruiseList));
    }

}NETDEMO_CHANNEL_INFO,*LPNETDEMO_CHANNEL_INFO;

//device info
typedef struct NETDEMO_DEVICE_INFO
{
    INT32   dwDeviceIndex;                          /* device index */
    LPVOID  lpDevHandle;                            /* UserID */ 
    INT32   dwMaxChnNum;                            /* channel Max Num */
    NETDEMO_DEV_LOGIN_TYPE   dwLoginType;           /* See in DEMO_DEV_LOGIN_TYPE */
    CHAR    szIPAddr[NETDEV_LEN_260];               /*  Device IP or Domain Name */
    INT32   dwDevPort;                              /*  Device port */
    CHAR    szDevUserName[NETDEV_LEN_64];           /*  Device username */
    CHAR    szPassword[NETDEV_LEN_64];              /*  Device Password */
    CHAR    szDevName[NETDEV_LEN_64];               /*  Device name */
    CHAR    szDevModel[NETDEV_LEN_64];              /*  Device model */
    CHAR    szDevSerialNum[NETDEV_LEN_64];          /*  Device serial number */
    INT32   dwOrgID;                                /* ID Home organization ID */
    
    HTREEITEM hTreeItem;                             /*tree node*/
    LPVOID  lpCloudHandle;                          /*cloud handle*/
    CHAR    szCloudUrl[NETDEV_LEN_64];              /*cloud Url*/
    CHAR    szCloudName[NETDEV_LEN_64];             /*cloud account Name*/
    CHAR    szCloudPasswd[NETDEV_LEN_64];            /*cloud account Passwd*/

    NETDEV_DEVICE_INFO_S stDevInfo;
    NETDEV_CLOUD_DEV_INFO_EX_S stCloudDevinfo;
    NETDEV_NETWORKCFG_S stNetWorkCfg;
    NETDEV_DEVICE_BASICINFO_S stBasiciInfo;
    NETDEV_UPNP_NAT_STATE_S stUpnpNatInfo;
    NETDEV_TIME_CFG_S stTimeCfg;
    LPNETDEMO_CHANNEL_INFO pstChlInfo;
    NETDEMO_DEVICE_INFO()
    {
        pstChlInfo = NULL;
        dwDeviceIndex = -1;
        lpDevHandle = NULL;
        dwMaxChnNum = -1;
        dwLoginType = NETDEMO_LOGTYPE_UNKNOW;
        hTreeItem = NULL;
        memset(szIPAddr,0,sizeof(szIPAddr));
        memset(szDevUserName,0,sizeof(szDevUserName));
        memset(szPassword,0,sizeof(szPassword));
        memset(szDevName,0,sizeof(szDevName));
        memset(szDevModel,0,sizeof(szDevModel));
        memset(szDevSerialNum,0,sizeof(szDevSerialNum));
        memset((void*)&stDevInfo,0,sizeof(stDevInfo));
        memset((void*)&stCloudDevinfo,0,sizeof(stCloudDevinfo));
        memset((void*)&stBasiciInfo,0,sizeof(stBasiciInfo));
        memset((void*)&stNetWorkCfg,0,sizeof(stNetWorkCfg));
        memset((void*)&stUpnpNatInfo,0,sizeof(stUpnpNatInfo));
        memset((void*)&stTimeCfg,0,sizeof(stTimeCfg));
        memset((void*)&pstChlInfo,0,sizeof(pstChlInfo));
        memset(szCloudUrl, 0, sizeof(szCloudUrl));
        memset(szCloudName, 0, sizeof(szCloudName));
        memset(szCloudPasswd, 0, sizeof(szCloudPasswd));
    }

    ~NETDEMO_DEVICE_INFO()
    {    
//         if (NULL != pstChanInfo)
//         {
//              delete []pstChanInfo;
//              pstChanInfo = NULL;
//         }
    } 

}NETDEMO_DEVICE_INFO, *PNETDEMO_DEVICE_INFO;


typedef struct NETDEMO_CYCLE_DEVICE_INFO
{
    INT32  dwGaIndex;
    CHAR   szDevName[NETDEV_LEN_64];
    INT32  dwChnID;
}NETDEMO_CYCLE_DEVICE_INFO,*PNETDEMO_CYCLE_DEVICE_INFO;

typedef struct NETDEMO_CYCLE_WINDOW_INFO
{
    INT32 dwWinID; // windows ID
    INT32 dwIntervalTime; // ms
    INT32 dwDevCount;

    INT32 dwCurDevPlayIndex;
    NETDEMO_CYCLE_DEVICE_INFO szCycleDevInfo[NETDEMO_MAX_DEVICES];
}NETDEMO_CYCLE_WINDOW_INFO,*PNETDEMO_CYCLE_WINDOW_INFO;

typedef struct NETDEMO_CYCLE_INFO
{
     INT32 dwCycleType; //tagNetDemoCycleType
     INT32 dwIntervalTime;
     NETDEMO_CYCLE_WINDOW_INFO szCycleWinInfo[NETDEMO_MAX_SCREENNUM];
}NETDEMO_CYCLE_INFO,*PNETDEMO_CYCLE_INFO;


typedef struct _NetDemoSplitInfoNode
{
    LPVOID iHandle; 
    NETDEMO_SPLITTYPE emType;  //see  NETDEMO_SPLITTYPE
    HTREEITEM hDevTreePos;
    BOOL   bSaveData;  
    INT32  dwDevIndex;
    INT32  dwChnIndex;
    _NetDemoSplitInfoNode()
    {
        iHandle = NULL;
        hDevTreePos = NULL;
        dwDevIndex = -1;
        dwChnIndex = -1;
        iHandle = NULL;
    }
}NETDEMO_SPLITINFO_NODE,*PNETDEMO_SPLITINFO_NODE;

//local config
typedef struct NETDEMO_LOCAL_PARAM
{
    CHAR    szPictureSavePath[NETDEV_PATH_LEN];
    CHAR    szLocalRecordPath[NETDEV_PATH_LEN];
    CHAR    szLogpath[NETDEV_PATH_LEN];
    BOOL    bAutoSaveLog;
    BOOL    bSuccLog;
    BOOL    bFailLog;
    INT32   dwStreamType;

    NETDEMO_LOCAL_PARAM()
    {
        bAutoSaveLog = TRUE;
        bSuccLog = TRUE;
        bFailLog = TRUE;
        dwStreamType = NETDEV_LIVE_STREAM_INDEX_AUX;    //default aux stream
    }

}NETDEMO_LOCAL_PARAM;

typedef struct NETDEMO_ALARM_INFO
{
    INT32 ulAlarmType;
    CHAR *pcReportAlarm;
}NETDEMO_ALARM_INFO;


typedef struct NETDEMO_DEVTYPE_INFO
{
    INT32 dwDevType;
    CHAR *pcTypeInfo; 
}NETDEMO_DEVTYPE_INFO;


typedef struct tagUpdateInfo
{
    LPVOID  lpHandle;
    INT64   tBeginTime;
    INT64   tEndTime;
    INT64   tCurTime;
    INT32   dwCount;
    CString strFileName;
    CString strFilePath;
} NETDEMO_UPDATE_TIME_INFO;

static NETDEMO_ALARM_INFO gastNETDemoAlarmInfo[] = \
{\
    {NETDEV_ALARM_MOVE_DETECT,"Motion detection alarm"},\
    {NETDEV_ALARM_MOVE_DETECT_RECOVER,"Motion detection alarm recover"},\
    {NETDEV_ALARM_VIDEO_LOST,"Video loss alarm"},\
    {NETDEV_ALARM_VIDEO_TAMPER_DETECT,"Tampering detection alarm"},\
    {NETDEV_ALARM_VIDEO_TAMPER_RECOVER,"Tampering detection alarm recover"},\
    {NETDEV_ALARM_INPUT_SWITCH,"Boolean input alarm"},\
    {NETDEV_ALARM_TEMPERATURE_HIGH,"High temperature alarm"},\
    {NETDEV_ALARM_TEMPERATURE_LOW,"Low temperature alarm"},\
    {NETDEV_ALARM_AUDIO_DETECT,"Audio detection alarm"},\
    {NETDEV_ALARM_INPUT_SWITCH_RECOVER,"Boolean input alarm recover"},\
    {NETDEV_ALARM_REPORT_DEV_VIDEO_LOSS,"Video loss alarm"},\
    {NETDEV_ALARM_REPORT_DEV_VIDEO_LOSS_RECOVER,"Video loss alarm recover"},\
    {NETDEV_ALARM_REPORT_DEV_REBOOT,"Device restart"},\
    {NETDEV_ALARM_REPORT_DEV_SERVICE_REBOOT,"Service restart"},\
    {NETDEV_ALARM_REPORT_DEV_ONLINE,"Device online"},\
    {NETDEV_ALARM_REPORT_DEV_OFFLINE,"Device offline"},\
    {NETDEV_ALARM_REPORT_DEV_DELETE_CHL,"Delete channel"},\
    {NETDEV_ALARM_NET_FAILED,"Network timeout"},\
    {NETDEV_ALARM_SHAKE_FAILED,"Interaction error"},\
    {NETDEV_ALARM_NET_TIMEOUT,"Network error"},\
    {NETDEV_ALARM_DISK_OFFLINE_RECOVER,"Disk online"},\
    {NETDEV_ALARM_DISK_OFFLINE,"Disk offline"},\
    {NETDEV_ALARM_DISK_ONLINE_RECOVER,"Disk offline"},\
    {NETDEV_ALARM_DISK_ONLINE,"Disk online"},\
    {NETDEV_ALARM_DISK_ABNORMAL,"Disk abnormal"},\
    {NETDEV_ALARM_DISK_ABNORMAL_RECOVER,"Disk abnormal recover"},\
    {NETDEV_ALARM_DISK_STORAGE_WILL_FULL,"Disk storage will full"},\
    {NETDEV_ALARM_DISK_STORAGE_WILL_FULL_RECOVER,"Disk storage will full recover"},\
    {NETDEV_ALARM_DISK_STORAGE_IS_FULL,"Disk storage is full"},\
    {NETDEV_ALARM_DISK_STORAGE_IS_FULL_RECOVER,"Disk storage is full recover"},\
    {NETDEV_ALARM_DISK_RAID_DISABLED,"RAID disabled"},\
    {NETDEV_ALARM_DISK_RAID_DISABLED_RECOVER,"RAID disabled recover"},\
    {NETDEV_ALARM_DISK_RAID_DEGRADED,"RAID degraded"},\
    {NETDEV_ALARM_DISK_RAID_DEGRADED_RECOVER,"RAID degraded recover"},\
    {NETDEV_ALARM_DISK_RAID_RECOVERED,"RAID recovered"},\
    {NETDEV_ALARM_STREAMNUM_FULL,"Stream full"},\
    {NETDEV_ALARM_STREAM_THIRDSTOP,"Third party stream stopped"},\
    {NETDEV_ALARM_FILE_END,"File ended"},\
    {NETDEV_ALARM_ALLTIME_FLAG_START,"Start marker of alarm without arming schedule"},\
    {NETDEV_ALARM_STOR_ERR,"Storage error"},\
    {NETDEV_ALARM_STOR_DISOBEY_PLAN,"Not stored as planned"},\
    {NETDEV_ALARM_NO_RECOVER_FLAG_START,"Start marker of unrecoverable alarm"},\
    {NETDEV_ALARM_DISK_ERROR,"Disk error"},\
    {NETDEV_ALARM_ILLEGAL_ACCESS,"Illegal access"},\
    {NETDEV_ALARM_ALLTIME_FLAG_END,"End marker of alarm without arming schedule"},\
    {NETDEV_ALARM_VIDEO_LOST_RECOVER,"Video loss alarm recover"},\
    {NETDEV_ALARM_TEMPERATURE_RECOVER,"Temperature alarm recover"},\
    {NETDEV_ALARM_AUDIO_DETECT_RECOVER,"Audio detection alarm recover"},\
    {NETDEV_ALARM_STOR_ERR_RECOVER,"Storage error recover"},\
    {NETDEV_ALARM_STOR_DISOBEY_PLAN_RECOVER,"Not stored as planned recover"},\
    {NETDEV_ALARM_IMAGE_BLURRY_RECOVER,"Image blurry recover"},\
    {NETDEV_ALARM_SMART_TRACK_RECOVER,"Smart track recover"},\
    {NETDEV_EXCEPTION_REPORT_VOD_END,"Playback ended"},\
    {NETDEV_EXCEPTION_REPORT_VOD_ABEND,"Playback exception occured"},\
    {NETDEV_EXCEPTION_REPORT_BACKUP_END,"Backup ended"},\
    {NETDEV_EXCEPTION_REPORT_BACKUP_DISC_OUT,"Disk removed"},\
    {NETDEV_EXCEPTION_REPORT_BACKUP_DISC_FULL,"Disk full"},\
    {NETDEV_EXCEPTION_REPORT_BACKUP_ABEND,"Backup failure caused by other reasons"},\
    {NETDEV_EXCEPTION_EXCHANGE,"Exception occurred during user interaction (keep-alive timeout)"},\
    {NETDEV_ALARM_BANDWIDTH_CHANGE,"Bandwidth change"},\
    {NETDEV_E_VIDEO_RESOLUTION_CHANGE,"Resolution changed"},\
    {NETDEV_ALARM_LINE_CROSS,"Line cross"},\
    {NETDEV_ALARM_OBJECTS_INSIDE,"Objects inside"},\
    {NETDEV_ALARM_FACE_RECOGNIZE,"Face recognize"},\
    {NETDEV_ALARM_IMAGE_BLURRY,"Image blurry"},\
    {NETDEV_ALARM_SCENE_CHANGE,"Scene change"},\
    {NETDEV_ALARM_SMART_TRACK,"Smart track"},\
    {NETDEV_ALARM_ENTER_AREA,"Enter area"},\
    {NETDEV_ALARM_LEAVE_AREA,"Leave area"},\
    {NETDEV_ALARM_ARTICLE_MOVE,"Article move"},\
    {NETDEV_ALARM_PEOPLE_GATHER,"People gather alarm"},\
    {NETDEV_ALARM_REMAIN_ARTICLE,"Remain article"},\
//    {NETDEV_IP_CONFLICT,"IP Conflict"},
    {NETDEV_ALARM_LOITERING_DETECTOR,"Loitering detector"}
};

static NETDEMO_DEVTYPE_INFO gastNetDemoDevType[] = \
{\
    {NETDEV_DTYPE_UNKNOWN,"Unknow Type"},
    {NETDEV_DTYPE_IPC,"IPC"},
    {NETDEV_DTYPE_IPC_FISHEYE,"Diseconomic Fish Eye IPC"},
    {NETDEV_DTYPE_IPC_ECONOMIC_FISHEYE,"Economic Fish Eye IPC"},
    {NETDEV_DTYPE_NVR,"NVR"},
    {NETDEV_DTYPE_NVR_BACKUP,"NVR Back Up"},
    {NETDEV_DTYPE_DC,"DC"},
    {NETDEV_DTYPE_EC,"EC"},
    {NETDEV_DTYPE_VMS,"VMS"}
};
#endif
