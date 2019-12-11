#ifndef _NETDEV_H_
#define _NETDEV_H_

#ifdef  __cplusplus
extern "C"{
#endif

#ifndef STATIC
    #define STATIC                  static
#endif

#ifndef CONST
    #define CONST                   const
#endif

#ifndef EXTERN
    #define EXTERN                  extern
#endif

#ifndef INLINE
    #define INLINE                  __inline
#endif

#ifndef UNION
    #define UNION                   union
#endif

#ifndef IN
    #define IN
#endif

#ifndef OUT
    #define OUT
#endif

#ifndef INOUT
    #define INOUT
#endif

#ifndef NEWINTERFACE
    #define NEWINTERFACE
#endif

#if defined(WIN32)  /* windows */
#if defined(NETDEV_SDK_DLL)
#define NETDEV_API                  __declspec(dllexport)
#else
#define NETDEV_API                  __declspec(dllimport)
#endif
#else
#define NETDEV_API
#endif

/*  Standard function calling convention */
#ifdef i386
    #ifdef LINUX
        #ifndef STDCALL
        #define STDCALL                 __attribute__((stdcall))__attribute__((visibility ("default")))
        #endif
    #else
        #ifndef STDCALL
        #define STDCALL                 __attribute__((stdcall))
        #endif
    #endif
#else
    #ifdef WIN32
        #ifndef STDCALL
        #define STDCALL                 __stdcall
        #endif
    #else
        #ifdef LINUX
            #ifndef STDCALL
            #define STDCALL                 __attribute__((stdcall))__attribute__((visibility ("default")))
            #endif
        #else
            #ifndef STDCALL
            #define STDCALL
            #endif
        #endif
    #endif
#endif


#ifndef UCHAR_DEF
#define UCHAR_DEF
    typedef unsigned char           UCHAR;
#endif

#ifndef CHAR_DEF
#define CHAR_DEF
    typedef char                    CHAR;
#endif

#ifndef BYTE_DEF
#define BYTE_DEF
    typedef unsigned char           BYTE;
#endif

#ifndef UINT16_DEF
#define UINT16_DEF
    typedef unsigned short          UINT16;
#endif

#ifndef UINT_DEF
#define UINT_DEF
    typedef unsigned int            UINT32;
#endif

#ifndef INT16_DEF
#define INT16_DEF
    typedef  short                  INT16;
#endif

#ifndef INT32_DEF
#define INT32_DEF
    typedef  int                    INT32;
#endif

#ifndef LPVOID_DEF
#define LPVOID_DEF
    typedef void*                   LPVOID;
#endif

#ifndef VOID
#ifndef VOID_DEF
#define VOID_DEF
    typedef void                    VOID;
#endif
#endif

#ifndef INT64_DEF
#define INT64_DEF
    typedef long long               INT64;
#endif

#ifndef BOOL_DEF
#define BOOL_DEF
    #ifndef TARGET_OS_IOS
        typedef int                 BOOL;
    #else
        #import<objc/objc.h>
    #endif
#endif

#ifndef FLOAT
#ifndef VOID_FLOAT
#define VOID_FLOAT
    typedef float                   FLOAT;
#endif
#endif

#ifndef FALSE
    #define FALSE                   0
#endif

#ifndef TRUE
    #define TRUE                    1
#endif

#ifndef WIN32
    typedef LPVOID                 HWND;
#endif

/**********************************   Commonly used numerical macros *************** */

/*   Length of stream ID*/
#define NETDEV_STREAM_ID_LEN                    32

/*   Length of filename */
#define NETDEV_FILE_NAME_LEN                    (256u)

/*  Maximum length of username */
#define NETDEV_USER_NAME_LEN                    32

/*   Maximum length of password */
#define NETDEV_PASSWD_LEN                       64

/*  Length of password and encrypted passcode for user login */
#define NETDEV_PASSWD_ENCRYPT_LEN               64

/*   Length of resource code string */
#define NETDEV_RES_CODE_LEN                     48

/*   Maximum length of domain name */
#define NETDEV_DOMAIN_LEN                       64

/*   Maximum length of device name */
#define NETDEV_DEVICE_NAME_LEN                  32

/*   Maximum length of path */
#define NETDEV_PATH_LEN_WITHOUT_NAME            64

/*   Maximum length of path, including filename */
#define NETDEV_PATH_LEN                         128

/*   Maximum length of email address */
#define NETDEV_EMAIL_NAME_ADDR                  32

/*   Length of MAC address */
#define NETDEV_MAC_ADDR_LEN                     6

/*  Length of endpoint called by gSOAP */
#define NETDEV_ENDPOINT_LEN                     96

/*   Maximum length of session ID */
#define NETDEV_SESSION_ID_LEN                   16

/*   Maximum length of URL */
#define NETDEV_MAX_URL_LEN                         512

/*   Common length */
#define NETDEV_LEN_4                            4
#define NETDEV_LEN_6                            6
#define NETDEV_LEN_8                            8
#define NETDEV_LEN_16                           16
#define NETDEV_LEN_32                           32
#define NETDEV_LEN_64                           64
#define NETDEV_LEN_128                          128
#define NETDEV_LEN_132                          132
#define NETDEV_LEN_256                          256
#define NETDEV_LEN_260                          260
#define NETDEV_LEN_1024                         1024

/*   Length of IP address string */
#define NETDEV_IPADDR_STR_MAX_LEN              (64u)

/*  Length of IPV4 address string */
#define NETDEV_IPV4_LEN_MAX                     16

/*  Length of IPV6 address string */
#define NETDEV_IPV6_LEN_MAX                     128

/*   Length of common name string */
#define NETDEV_NAME_MAX_LEN                    (20u)

/*   Length of common code */
#define NETDEV_CODE_STR_MAX_LEN                (48u)

/*  Maximum length of date string "2008-10-02 09:25:33.001 GMT" */
#define NETDEV_MAX_DATE_STRING_LEN             (64u)

/*  Length of time string "hh:mm:ss" */
#define NETDEV_SIMPLE_TIME_LEN                 (12u)

/*  Length of date string "YYYY-MM-DD"*/
#define NETDEV_SIMPLE_DATE_LEN                 (12u)

/*   Maximum number of alarm inputs */
#define NETDEV_MAX_ALARM_IN_NUM                 64

/*   Maximum number of alarm outputs */
#define NETDEV_MAX_ALARM_OUT_NUM                64

/*   Number of scheduled time sections in a day */
#define NETDEV_PLAN_SECTION_NUM                 8

/*  Total number of plans allowed in a week, including Monday to Sunday, and holidays */
#define NETDEV_PLAN_NUM_AWEEK                   8

/*   Maximum number of motion detection areas allowed */
#define NETDEV_MAX_MOTION_DETECT_AREA_NUM       4

/*   Maximum number of privacy mask areas allowed */
#define NETDEV_MAX_PRIVACY_MASK_AREA_NUM        8

/*   Maximum number of tamper-proof areas allowed */
#define NETDEV_MAX_TAMPER_PROOF_AREA_NUM        1

/*   Maximum number of text overlays allowed for a channel */
#define NETDEV_MAX_TEXTOVERLAY_NUM              6

/*   Maximum number of video streams */
#define NETDEV_MAX_VIDEO_STREAM_NUM             8

/*  Month of the year */
#define NETDEV_MONTH_OF_YEAR                    12

/*   Day of the month */
#define NETDEV_DAYS_OF_MONTH                    32

/*   Length of device ID */
#define NETDEV_DEV_ID_LEN                       64

/*   Length of device serial number */
#define NETDEV_SERIAL_NUMBER_LEN                32

/*   Maximum number of queries allowed at a time */
#define NETDEV_MAX_QUERY_NUM                    200

/*   Total number of queries allowed */
#define NETDEV_MAX_QUERY_TOTAL_NUM              2000

/*   Maximum number of IP cameras */
#define NETDEV_MAX_IPC_NUM                      128

/*   Maximum number of presets */
#define NETDEV_MAX_PRESET_NUM                   255

/*   Maximum number of presets for preset patrol */
#define NETDEV_MAX_CRUISEPOINT_NUM              32

/*   Maximum number of routes for preset patrol */
#define NETDEV_MAX_CRUISEROUTE_NUM              16

/*   PTZ rotating speed */
#define NETDEV_MIN_PTZ_SPEED_LEVEL              1
#define NETDEV_MAX_PTZ_SPEED_LEVEL              9

/*  Maximum / Minimum values for image parameters (brightness, contrast, hue, saturation) */
#define NETDEV_MAX_VIDEO_EFFECT_VALUE           255
#define NETDEV_MIN_VIDEO_EFFECT_VALUE           0

/*  Minimum values for image parameters (Gama) */
#define NETDEV_MAX_VIDEO_EFFECT_GAMMA_VALUE     10

/*   Maximum connection timeout */
#define NETDEV_MAX_CONNECT_TIME_VALUE           75000

/*   Minimum connection timeout */
#define NETDEV_MIN_CONNECT_TIME_VALUE           300

/*   Maximum number of users */
#define NETDEV_MAX_USER_NUM                     (256 + 32)

/*   Maximum number of channels allowed for live preview */
#define NETDEV_MAX_REALPLAY_NUM                 128

/*   Maximum number of channels allowed for playback or download */
#define NETDEV_MAX_PALYBACK_NUM                 128

/*   Maximum number of alarm channels */
#define NETDEV_MAX_ALARMCHAN_NUM                128

/*   Maximum number of channels allowed for formatting hard disk */
#define NETDEV_MAX_FORMAT_NUM                   128

/*   Maximum number of channels allowed for file search */
#define NETDEV_MAX_FILE_SEARCH_NUM              2000

/*   Maximum number of channels allowed for log search */
#define NETDEV_MAX_LOG_SEARCH_NUM               2000

/*   Maximum number of channels allowed for creating transparent channels */
#define NETDEV_MAX_SERIAL_NUM                   2000

/*   Maximum number of channels allowed for upgrade */
#define NETDEV_MAX_UPGRADE_NUM                  256

/*   Maximum number of channels allowed for audio forwarding */
#define NETDEV_MAX_VOICE_COM_NUM                256

/*   Maximum number of channels allowed for audio broadcast */
#define NETDEV_MAX_VOICE_BROADCAST_NUM          256

/*   Maximum timeout, unit: ms */
#define NETDEV_MAX_CONNECT_TIME                 75000

/*   Minimum timeout, unit: ms */
#define NETDEV_MIN_CONNECT_TIME                 300

/*   Default timeout, unit: ms */
#define NETDEV_DEFAULT_CONNECT_TIME             3000

/*   Number of connection attempts */
#define NETDEV_CONNECT_TRY_TIMES                1

/*   User keep-alive interval */
#define NETDEV_KEEPLIVE_TRY_TIMES               3

/*  Number of OSD text overlays */
#define NETDEV_OSD_TEXTOVERLAY_NUM              6

/*   Length of OSD texts */
#define NETDEV_OSD_TEXT_MAX_LEN                 (64 + 4)

/*  Maximum number of OSD type */
#define NETDEV_OSD_TYPE_MAX_NUM                 26

/*  Maximum number of OSD time format type */
#define NETDEV_OSD_TIME_FORMAT_MAX_NUM          7

/*   Maximum number of OSD date format type */
#define NETDEV_OSD_DATE_FORMAT_MAX_NUM          15

/*   Maximum number of alarms a user can get */
#define NETDEV_PULL_ALARM_MAX_NUM               8

/*   Maximum number of patrol routes allowed  */
#define NETDEV_TRACK_CRUISE_MAXNUM               1

/*   Minimum volume */
#define NETDEV_AUDIO_SOUND_MIN_VALUE            0

/*   Maximum volume */
#define NETDEV_AUDIO_SOUND_MAX_VALUE            255

/*   Minimum volume */
#define NETDEV_MIC_SOUND_MIN_VALUE              0

/*   Maximum volume */
#define NETDEV_MIC_SOUND_MAX_VALUE              255

/*   Screen Info Row */
#define NETDEV_SCREEN_INFO_ROW                  18

/*   Screen Info Column */
#define NETDEV_SCREEN_INFO_COLUMN               22

/*  Length of IP */
#define NETDEV_IP_LEN                           64

/*  Maximum length of buffer */
#define NETDEV_BUFFER_MAX_LEN                   1024

/*  Maximum number of channel */
#define NETDEV_CHANNEL_MAX                      512

/*  Maximum number of resolution */
#define NETDEV_RESOLUTION_NUM_MAX               32

/*  Maximum number of days in a month */
#define NETDEV_MONTH_DAY_MAX                    31

/*  Maximum number of encode type */
#define NETDEV_VIDEO_ENCODE_TYPE_MAX            16

/*  Maximum number of people count */
#define   NETDEV_PEOPLE_CNT_MAX_NUM             31

/*   Length of wifi sniffer MAC */
#define NETDEV_WIFISNIFFER_MAC_MAX_NUM          64

/*  Maximum number of wifi sniffer MAC array */
#define NETDEV_WIFISNIFFER_MAC_ARRY_MAX_NUM     128

/*  Maximum number of Disk */
#define NETDEV_DISK_MAX_NUM                     256

/*  Maximum number of image quality level */
#define NETDEV_IMAGE_QUALITY_MAX_NUM            9

/*  Maximum number of bit rate mode */
#define NETDEV_BIT_RATE_TYPE_MAX_NUM            2

/*  Maximum number of video compression */
#define NETDEV_ENCODE_FORMAT_MAX_NUM            3

/*  Maximum number of smart image encoding mode */
#define NETDEV_SMART_ENCODE_MODEL_MAX_NUM       3

/*  Maximum number of GOP type */
#define NETDEV_GOP_TYPE_MAX_NUM                 4


/* BEGIN****************************  Error codes ************************************************************/
#define NETDEV_E_SUCCEED                        0           /*   Succeeded */
#define NETDEV_E_FAILED                         -1          /*   Failed */

/*   Common error codes */
#define NETDEV_E_COMMON_FAILED                  1           /*  Common error */
#define NETDEV_E_DEV_COMMON_FAILED              2           /*  Common error returned by device */
#define NETDEV_E_SYSCALL_FALIED                 3           /*  Failed to call system function. See errno */
#define NETDEV_E_NULL_POINT                     4           /*  Null pointer */
#define NETDEV_E_INVALID_PARAM                  5           /*  Invalid parameter */
#define NETDEV_E_INVALID_MODULEID               6           /*  Invalid module ID */
#define NETDEV_E_NO_MEMORY                      7           /*  Failed to allocate memory */
#define NETDEV_E_NOT_SUPPORT                    8           /*  Not supported by device */
#define NETDEV_E_SDK_SOCKET_LSN_FAIL            9           /*  Failed to create socket listen */
#define NETDEV_E_INIT_MUTEX_FAIL                10          /*  Failed to initialize lock */
#define NETDEV_E_INIT_SEMA_FAIL                 11          /*  Failed to initialize semaphore */
#define NETDEV_E_ALLOC_RESOURCE_ERROR           12          /*  Error occurred during SDK resource allocation */
#define NETDEV_E_SDK_NOINTE_ERROR               13          /*  SDK not initialized */
#define NETDEV_E_ALREDY_INIT_ERROR              14          /*  SDK already initialized */
#define NETDEV_E_HAVEDATA                       15          /*  Data not all sent */
#define NETDEV_E_NEEDMOREDATA                   16          /*  More data required  */
#define NETDEV_E_CONNECT_ERROR                  17          /*  Failed to create connection */
#define NETDEV_E_SEND_MSG_ERROR                 18          /*  Failed to send request message */
#define NETDEV_E_TIMEOUT                        19          /*  Message timeout */
#define NETDEV_E_DECODE_RSP_ERROR               20          /*  Failed to decode response message */
#define NETDEV_E_SOCKET_RECV_ERROR              21          /*  Socket failed to receive message */
#define NETDEV_E_NUM_MAX_ERROR                  22          /*  Maximum number reached. The assigned numbers of registration connections and preview connections reached the maximum supported by SDK */
#define NETDEV_E_GET_PORT_ERROR                 24          /*  Failed to obtain local port number */
#define NETDEV_E_CREATE_THREAD_FAIL             25          /*  Failed to create thread */
#define NETDEV_E_NOENOUGH_BUF                   26          /*  Buffer is too small for receiving device data */
#define NETDEV_E_GETLOCALIPANDMACFAIL           27          /*  Failed to obtain the IP or MAC address of the local PC */
#define NETDEV_E_RESCODE_NO_EXIST               28          /*  Resource code not exist */
#define NETDEV_E_MSG_DATA_INVALID               31          /*  Incorrect message content */
#define NETDEV_E_GET_CAPABILITY_ERROR           32          /*  Failed to obtain capabilities */
#define NETDEV_E_USER_NOT_BIND                  33          /*  User not subscribed to alarms */
#define NETDEV_E_AUTHORIZATIONFAIL              34          /*  User authentication failed */
#define NETDEV_E_BINDNOTIFY_FAIL                35          /*  Failed to bind alarms*/
#define NETDEV_E_NOTADMIN                       36          /*  Not enough permission. In Windows, it is normally because the operator is not an administrator. */
#define NETDEV_E_DEVICE_FACTURER_ERR            37          /*  Manufacturers that are not supported */
#define NETDEV_E_NONSUPPORT                     38          /*  Function not supported */
#define NETDEV_E_TRANSFILE_FAIL                 39          /*  File transmission failed */
#define NETDEV_E_JSON_ERROR                     40          /* Json common error */
#define NETDEV_E_NO_RESULT                      41          /* No result */
#define NETDEV_E_DEVICE_TYPE_ERR                42          /* Device type that are not supported */
#define NETDEV_E_NONCE_TIMEOUT                  43          /* nonce be overdue */
#define NETDEV_E_INNER_ERR                      44          /* System internal error */
#define NETDEV_E_PUBLICKEYFAIL                  60068       /* Failed to match publickey*/

/*   User-related error codes */
#define NETDEV_E_USER_WRONG_PASSWD                  101          /*   Incorrect password */
#define NETDEV_E_USER_LOGIN_MAX_NUM                 102          /*   Number of login users reached the upper limit */
#define NETDEV_E_USER_NOT_ONLINE                    103          /*   User not online */
#define NETDEV_E_USER_NO_SUCH_USER                  104          /*   User not online */
#define NETDEV_E_USER_NO_AUTH                       105          /*   User has no rights */
#define NETDEV_E_USER_MAX_NUM                       106          /*   Reached the upper limit¨Cno more users can be added */
#define NETDEV_E_USER_EXIST                         107          /*   User already exists */
#define NETDEV_E_USER_PASSWORD_CHANGE               108          /*   Password changed */
#define NETDEV_E_REMOTE_USER_WITH_WEAK_PASSWD       109          /*   Remote user with weak password */

#define NETDEV_E_REMOTE_NOT_YOUR_DEVICE             122          /*  Not Your Device */
#define NETDEV_E_REMOTE_CHL_NOT_EXIST               123          /*  Channel Not Exist */
#define NETDEV_E_REMOTE_STREAMID_NOT_EXIST          124          /*  StreamID Not Exist */
#define NETDEV_E_REMOTE_BITRATE_UNEXPECTED          125          /*  Bitrate Unexpected */
#define NETDEV_E_REMOTE_VISITOR_TOTAL_UNEXPECTED    126          /*  Visitor Total Unexpected*/
#define NETDEV_E_REMOTE_LIVEID_NOT_EXIST            127          /*  LiveID Not Exist */
#define NETDEV_E_REMOTE_PROTOCOL_TYPE_ILLEGAL       128          /*  Protocol Type Illegal*/
#define NETDEV_E_REMOTE_CLIENTID_NOT_EXIST          129          /*  ClientID Not Exist */
#define NETDEV_E_REMOTE_REQUESTID_NOT_EXIST         130          /*  RequestID Not Exist */
/*   Service-related error codes */

/*   Playback-related error codes */
#define NETDEV_E_VOD_PLAY_END                   250         /*   Playback ended */
#define NETDEV_E_VOD_NO_CM                      251         /*   Playback controlling module not exist */
#define NETDEV_E_VOD_OVER_ABILITY               252         /*   Beyond playback capability */
#define NETDEV_E_VOD_NO_RECORDING_CM            253         /*   Recording file controlling module not exist */
#define NETDEV_E_VOD_NO_RECORDING               254         /*   No recording */
#define NETDEV_E_VOD_NO_REPLAYURL               255         /*   Cannot get the URL for playback*/


/*   PTZ-related error codes */
#define NETDEV_E_PTZ_SET_PRESET_FAILED              300         /*   Failed to set preset */
#define NETDEV_E_PTZ_QUERY_PRESET_FAILED            301         /*   Failed to query preset */
#define NETDEV_E_PTZ_QUERY_TRACK_FAILED             302         /*   Failed to query route */
#define NETDEV_E_PTZ_START_RECORD_TRACK_FAILED      303         /*   Failed to start route recording */
#define NETDEV_E_PTZ_STOP_RECORD_TRACK_FAILED       304         /*   Failed to end route recording */
#define NETDEV_E_PTZ_QUERY_CRUISE_FAILED            305         /*   Failed to query patrol route */
#define NETDEV_E_PTZ_SET_CRUISE_FAILED              306         /*   Failed to set patrol route */
#define NETDEV_E_PTZ_CTRL_FAILED                    307         /*   PTZ operation failed */
#define NETDEV_E_PTZ_PRESET_IN_CRUISE               308         /*   Preset is being used in patrol route and cannot be deleted */
#define NETDEV_E_PTZ_CRUISEPOINT_ERR                309         /*   Discontinuous presets */
#define NETDEV_E_PTZ_TRACK_ISUSED                   310         /*   Route is in use and cannot be deleted */
#define NETDEV_E_PTZ_SERIALMODE_MISMATCH            311         /*   Serial modes do not match */
#define NETDEV_E_PTZ_TRACK_NOT_EXIST                312         /*   Route does not exist */
#define NETDEV_E_PTZ_MODE_CRUISE_FULL               313         /*   Route points are full */


/*  SOAP-related error codes */
#define NETDEV_E_DEVICE_STREAM_FULL                 500         /*   Device stream full */
#define NETDEV_E_DEVICE_STREAM_CLOSED               501         /*   Device stream closed */
#define NETDEV_E_DEVICE_STREAM_NONEXIST             502         /*   Device stream does not exist */

#define NETDEV_E_COMMON_FAIL_STAT                   503         /*   Failed to read file (directory) status */
#define NETDEV_E_COMMON_FILE_NONEXIST               504         /*   File does not exist */
#define NETDEV_E_COMMON_MKDIR_ERR                   505         /*   Failed to create directory */
#define NETDEV_E_SUBSCRIBE_FULL                     506         /*   Subscription is full for current user */
#define NETDEV_E_UPGRADE_NOTADMIN                   507         /*   Only admin can upgrade */
#define NETDEV_E_UPGRADE_INVALID                    508         /*   Upgrade not started */
#define NETDEV_E_UPGRADE_INPROCESS                  509         /*   Upgrade in process */
#define NETDEV_E_UPGRADE_NOMEMORY                   510         /*   Insufficient memory for upgrade */
#define NETDEV_E_UPGRADE_FILE_OPEN_ERR              511         /*   Error occurred while opening the mirror file during upgrade */
#define NETDEV_E_UPGRADE_DEVICE_ERR                 512         /*   Error occurred while upgrading FLASH */
#define NETDEV_E_UPGRADE_BUSY                       513         /*   Cannot load multiple upgrade processes at the same time */
#define NETDEV_E_UPGRADE_FAIL_TIMEOUT               514         /*   Upgrade timeout */
#define NETDEV_E_INVALID_CONFIGFILE                 515         /*   Invalid configuration file */
#define NETDEV_E_STOR_RESOURCE_NOTINIT              516         /*   Storage resource not allocated */

#define NETDEV_E_PLAYER_BASE_ERR                    1000        /*   Basic decoding error code */
#define NETDEV_E_PLAYER_FAIL                        1001        /*   Basic decoding error code */
#define NETDEV_E_PLAYER_INVALID_PARAM               1002        /*   Invalid input parameter */
#define NETDEV_E_PLAYER_NO_MEMORY                   1003        /*   Not enough system memory */
#define NETDEV_E_PLAYER_SOCKET_FAIL                 1004        /*   Failed to create SOCKET */
#define NETDEV_E_PLAYER_RECV_FAIL                   1005        /*   Failed to receive */
#define NETDEV_E_PLAYER_RECV_ZERO                   1006        /*   None received */
#define NETDEV_E_PLAYER_NOT_SUPPORT                 1007        /*   Currently not supported */
#define NETDEV_E_PLAYER_CREATETHREAD_FAILED         1008        /*   Failed to create the thread */
#define NETDEV_E_PLAYER_OPENDL_FAILED               1009        /*   Failed to load the dynamic library */
#define NETDEV_E_PLAYER_SYMDL_FAILED                1010        /*   Failed to get the dynamic library */
#define NETDEV_E_PLAYER_SEND_FAILED                 1011        /*   Failed to send */
#define NETDEV_E_PLAYER_EACCES                      1012        /*   No permission to create the file */
#define NETDEV_E_PLAYER_FILE_NOT_FIND               1013        /*   Failed to find the file to read */
#define NETDEV_E_PLAYER_LOG_CLOSE                   1014        /*   Close log */

/*********************** Player ********************************/
#define NETDEV_E_FAIL_TO_INIT_EZPLAYER              1257        /*   Failed to initialize the player */
#define NETDEV_E_FAIL_TO_ALLOC_PORT_RES             1258        /*   Failed to allocate playing channel resources */
#define NETDEV_E_FAIL_TO_GET_PORT_RES               1259        /*   Failed to get playing channel resources */
#define NETDEV_E_BUFFER_QUEUE_FULL                  1260        /*   Cache queue full */
#define NETDEV_E_BUFFER_QUEUE_EMPTY                 1261        /*   Cache queue empty */
#define NETDEV_E_OPEN_FILE_FAILED                   1262        /*   Failed to open the file */
#define NETDEV_E_FILE_READ_END                      1263        /*   The file is read */
#define NETDEV_E_FILE_DISKSPACE_FULL                1264        /*   Disk space full */
#define NETDEV_E_FILE_READ_FAIL                     1265        /*   Failed to read */
#define NETDEV_E_MCM_MIC_NOT_EXIST                  1266        /*   The microphone does not exist */
#define NETDEV_E_TS_PACKET_IN_THE_ROUGH             1267        /*   TS packing not finished */
#define NETDEV_E_FILE_RECORD_FINISH                 1268        /*   Recording saved */
#define NETDEV_E_VIDEO_RESOLUTION_CHANGE            1269        /*  Resolution changed */
#define NETDEV_E_VIDEO_RECORD_PART                  1270        /*  Video segmentation*/

#define NETDEV_E_FAIL_TO_OPEN_STREAM                1513        /*   Failed to start media streaming */
#define NETDEV_E_FAIL_TO_CLOSE_STREAM               1514        /*   Failed to close media streaming */
#define NETDEV_E_FAIL_TO_RECV_DATA                  1515        /*   Failed to receive data due to network error */
#define NETDEV_E_FAIL_TO_PROCESS_MEDIA_DATA         1516        /*   Failed to handle media data */
#define NETDEV_E_NOT_START_PLAY                     1517        /*   Playing not started in playing channel */
#define NETDEV_E_FAIL_TO_INPUT_DATA                 1518        /*   Failed to enter media stream data */
#define NETDEV_E_INPUTDATA_BUFFER_FULL              1519        /*   Input data cache full */
#define NETDEV_E_FAIL_TO_SET_PROCESS_DATA_CB        1520        /*   Failed to set media stream data callback function */
#define NETDEV_E_VOICE_RUNNING                      1521        /*   Error occurred when running voice service */
#define NETDEV_E_FAIL_TO_OPEN_VOICE_SVC             1522        /*   Failed to start voice service */
#define NETDEV_E_FAIL_TO_CLOSE_VOICE_SVC            1523        /*   Failed to close voice service */
#define NETDEV_E_UNKNOWN_STREAM_TYPE                1524        /*   Unknown media stream */
#define NETDEV_E_PACKET_LOSE                        1525        /*   Packet loss */
#define NETDEV_E_NEED_MORE_PACKET                   1526        /*   More packets are needed for the packing */
#define NETDEV_E_FAIL_TO_CREATE_DECODE              1527        /*   Failed to create the decoder */
#define NETDEV_E_FAIL_TO_DECODE                     1528        /*   Failed to decode */
#define NETDEV_E_RECV_DATA_NOTENOUGH                1529        /*   Not enough data received */
#define NETDEV_E_RENDER_RES_FULL                    1530        /*   Display resources full */
#define NETDEV_E_RENDER_RES_NOT_EXIST               1531        /*   Display resources do not exist */
#define NETDEV_E_CREATE_DEV_FAILED                  1532        /*   Failed to create the resources */
#define NETDEV_E_AUDIO_RES_NOT_EXIST                1533        /*   Audio resources do not exist */
#define NETDEV_E_IHW265D_NEED_MORE_BITS             1534        /*   Decoder requires more data */
#define NETDEV_E_FAIL_TO_CREATE_ENCODE              1535        /*   Failed to create encoder */
#define NETDEV_E_CAPTURE_RES_EXIST                  1536        /*   Capture resources do not exist */
#define NETDEV_E_RECORD_STARTED                     1537        /*   Recording already opened */
#define NETDEV_E_NEED_WAIT_DECODEC                  1538        /*   Decoding in progress, please wait */
#define NETDEV_E_MORE_DATA_NEED_PACKET              1539        /*   Too much data, still need packing */

/*   Live video error codes */
#define NETDEV_E_LIVE_EXISTED                       2000        /*   Live video service already established */
#define NETDEV_E_LIVE_INPUT_NOT_READY               2001        /*   Media stream not ready */
#define NETDEV_E_LIVE_OUTPUT_BUSY                   2002        /*   Display resource is busy for live video service */
#define NETDEV_E_LIVE_CB_NOTEXIST                   2003        /*   Control module for live video not exist */
#define NETDEV_E_LIVE_STREAM_FULL                   2004        /*   Live stream resource full */

/*   Capture-related error codes */
#define NETDEV_E_CAPTURE_NO_SUPPORT_FORMAT          2100        /*   Format of captured image not supported */
#define NETDEV_E_CAPTURE_NO_ENOUGH_CAPACITY         2101        /*   Insufficient disk space */
#define NETDEV_E_CAPTURE_NO_DECODED_PICTURE         2102        /*   No decoded image for capture */
#define NETDEV_E_CAPTURE_SINGLE_FAILED              2103        /*   Single capture failed */

/*   Error codes related to two-way audio */
#define NETDEV_E_AUDIO_EXISTED                      2200        /*   Two-way audio already exists */
#define NETDEV_E_AUDIO_NO_EXISTED                   2201        /*   Two-way audio service does not exist */
#define NETDEV_E_AUDIO_RESCODE_INVALID              2202        /*   Invalid two-way audio resource code */
#define NETDEV_E_AUDIO_RES_USED_BY_TALK             2203        /*   Audio resource is being used by two-way audio */
#define NETDEV_E_AUDIO_FAILED                       2204        /*   Two-way audio failed */
#define NETDEV_E_AUDIO_AUDIOBCAST_FULL              2205        /*   No more audio service allowed */


/* Cloud and RTMP related error codes */
#define NETDEV_E_GET_CLOUD_DDNS_FAIL                2300        /* Failed to obtain DDNS information */
#define NETDEV_E_ADD_CLOUD_DEVICE_FAIL              2301        /* Failed to add cloud account device */
#define NETDEV_E_START_PULL_STREAM_FAIL             2303        /* Startup pull flow failure */
#define NETDEV_E_GET_RTMP_URL_FAIL                  2304        /* Failed to get RTMP pull URL */
#define NETDEV_E_GET_PUSH_STREAM_STATE_FAIL         2305        /* Failed to get the push state */
#define NETDEV_E_GET_DEV_INFO_FAILED                2306        /* Failure to obtain device information */
#define NETDEV_E_GET_CLOUD_ORG_LIST_FAIL            2307        /* Failed to get a list of cloud organizations */
#define NETDEV_E_MODIFT_CLOUD_DEV_NAME_FAIL         2308        /* Failed to update cloud device name */
#define NETDEV_E_DELETE_CLOUD_DEVICE_FAIL           2309        /* Delete cloud device failed */
#define NETDEV_E_STOP_DEVICE_SHARE_FAIL             2310        /* Failure to stop cloud device sharing*/
#define NETDEV_E_GET_SHARE_RECORD_INFO_FAIL         2311        /* Failure to obtain shared record information in the cloud */
#define NETDEV_E_GET_NAT_TYPE_FAIL                  2312        /* Failure to get Nat type */
#define NETDEV_E_ADD_CLOUD_ORG_FAIL                 2313        /* Increase cloud organization failure */
#define NETDEV_E_MODIFY_CLOUD_ORG_FAIL              2314        /* Failure to modify cloud organization */
#define NETDEV_E_DELETE_CLOUD_ORG_FAIL              2315        /* Delete cloud organization failure*/
#define NETDEV_E_ADD_DEV_TO_CLOUD_ORG_FAIL          2316        /* Increasing device to cloud organization failure */
#define NETDEV_E_GET_CLOUD_DEV_POPULATION           2317        /* Failed to obtain cloud account device statistics */
#define NETDEV_E_GET_CLOUD_DEV_CHANNEL_LIST_FAIL    2318        /* Getting the failure of the cloud device channel */
#define NETDEV_E_START_DEVICE_SHARE_FAIL            2319        /* Failed to start device sharing */
#define NETDEV_E_FIND_SHARE_DEVLIST_ERROR           2320        /* Failed to get a list of shared devices */
#define NETDEV_E_STOP_PULL_STREAM_FAIL              2321        /* stop pulling stream failed */
#define NETDEV_E_KEEP_ALIVE_PULL_STREAM_FAIL        3222        /* keep pulling alive failed */
#define NETDEV_E_KEEP_ALIVE_LIST_EMPTY              2323        /* Alive list is empty */
#define NETDEV_E_GET_LIVE_ID_FAIL                   2324        /* get live id failed */

/* TV wall related error code(12400-12799) */
#define    NETDEV_E_WIND_NUMLIMITED         12400       /* The number of windows exceeds the limit */
#define    NETDEV_E_TVWALL_NUMLIMITED       12401       /* The number of TV walls exceeds the limit */
#define    NETDEV_E_LED_NUMLIMITED          12402       /* The number of virtual LEDs exceeds the limit */
#define    NETDEV_E_LED_LINELIMITED         12403       /* Single virtual LED rows exceed limit*/
#define    NETDEV_E_SCENE_NUMLIMITED        12404       /* The number of scenes in the single TV wall is beyond the limit */
#define    NETDEV_E_BASEPIC_NUMLIMITED      12405       /* The number of base maps that devices can store exceeds the limit */
#define    NETDEV_E_BASEPIC_SCENELIMITED    12406       /* The number of bindings in a single scenario exceeds the limit */
#define    NETDEV_E_DECODE_OUTRANGE         12407       /* Destination position has been overdecoded */
#define    NETDEV_E_WIND_OUTRANGE           12408       /* The window area has more than three times the area */
#define    NETDEV_E_WIND_RANGELIMITED       12409       /* Windowed position roaming position out of range */
#define    NETDEV_E_WIND_LOCKED             12430       /* The current window is locked */
#define    NETDEV_E_LED_NOTEXIST            12431       /* Virtual LED does not exist */
#define    NETDEV_E_SEQ_EXITED              12432       /* Wheel cutting already exists. */
#define    NETDEV_E_WIND_NOTEXIST           12433       /* Window does not exist */
#define    NETDEV_E_WIND_EXIST              12434       /* Windows already exist. */
#define    NETDEV_E_SPILT_NOTEXIST          12435       /* The split screen in the window does not exist */
#define    NETDEV_E_WIND_NOSPILT            12436       /* Windows cannot be separated */
#define    NETDEV_E_CHANNEL_UESED           12437       /* The passage is occupied by other television walls */
#define    NETDEV_E_TVWALL_WINDEXIST        12438       /* TV wall window*/
#define    NETDEV_E_TVWALL_NOTEXIST         12439       /* TV wall information doesn't exist */
#define    NETDEV_E_SPLIT_INFOERR           12440       /* Error screen type */
#define    NETDEV_E_CHANNEL_NUMERR          12441       /* Channel number error */
#define    NETDEV_E_ENC_ERR                 12442       /* Media stream not ready */

/* END*********************   Error codes *********************************************************** */

/* BEGIN:******************   Enumeration value ***************************************************** */
/**
 * @enum tagNETDEVChannelStatus
 * @brief  Channel status Enumeration definition
 * @attention  None
 */
typedef enum tagNETDEVChannelStatus
{
    NETDEV_CHL_STATUS_OFFLINE   = 0,             /*   Channel offline */
    NETDEV_CHL_STATUS_ONLINE    = 1,             /*   Channel online */
    NETDEV_CHL_STATUS_UNBIND    = 2,             /*   Channel unbind */
    NETDEV_CHL_STATUS_INVALID
}NETDEV_CHANNEL_STATUS_E;

/**
 * @enum tagNETDEVChannelType
 * @brief   Channel type Enumeration definition
 * @attention  None
 */
typedef enum tagNETDEVChannelType
{
    NETDEV_CHL_TYPE_DIGITAL = 0,            /*   Digital Channel */
    NETDEV_CHL_TYPE_ANALOG = 1,             /*   analog Channel */
    NETDEV_CHL_TYPE_INVALID
}NETDEV_CHANNEL_TYPE_E;

/**
 * @enum tagNETDEVVideoStandard
 * @brief  
 * @attention  None
 */
typedef enum tagNETDEVVideoStandard
{
    NETDEV_VIDEO_STANDARD_PAL = 0,            /* PAL */
    NETDEV_VIDEO_STANDARD_NTSC = 1,             /* NTSC */
    NETDEV_VIDEO_STANDARD_INVALID
}NETDEV_VIDEO_STANDARD_E;

/**
 * @enum tagNETDEVCameraType
 * @brief   Camera type Enumeration definition
 * @attention  None
 */
typedef enum tagNETDEVCameraType
{
    NETDEV_CAMERA_TYPE_FIX         = 0,            /*   Fixed camera */
    NETDEV_CAMERA_TYPE_PTZ         = 1,            /*   PTZ camera */

    NETDEV_CAMERA_TYPE_INVALID     = 0xFF          /*   Invalid value */
}NETDEV_CAMERA_TYPE_E;

/**
 * @enum tagNETDEVLiveStreamIndex
 * @brief  Live stream index Enumeration definition
 * @attention  None
 */
typedef enum tagNETDEVLiveStreamIndex
{
    NETDEV_LIVE_STREAM_INDEX_MAIN  = 0,   /*   Main stream */
    NETDEV_LIVE_STREAM_INDEX_AUX   = 1,   /*   Sub stream */
    NETDEV_LIVE_STREAM_INDEX_THIRD = 2,   /*   Third stream */

    NETDEV_LIVE_STREAM_INDEX_INVALID
}NETDEV_LIVE_STREAM_INDEX_E;

/**
 * @enum tagHOSTType
 * @brief    Protocol type Enumeration definition
 * @attention  None
 */
typedef enum tagHOSTType
{
    NETDEV_NETWORK_HOSTTYPE_IPV4 = 0,               /* IPv4 */
    NETDEV_NETWORK_HOSTTYPE_IPV6 = 1,               /* IPv6 */
    NETDEV_NETWORK_HOSTTYPE_DNS  = 2                /* DNS */
}NETDEV_HOSTTYPE_E;


/**
 * @enum tagNETDEVProtocal
 * @brief  Media transport protocol Enumeration definition
 * @attention  None
 */
typedef enum tagNETDEVProtocal
{
    NETDEV_TRANSPROTOCAL_RTPUDP = 0,         /* UDP */
    NETDEV_TRANSPROTOCAL_RTPTCP = 1          /* TCP */
}NETDEV_PROTOCAL_E;

/**
 * @enum tagNETDEVStartStreamMode
 * @brief    start stream mode Enumeration definition
 * @attention None
 */
typedef enum tagNETDEVStreamMode
{
    NETDEV_STREAM_MODE_ALL   = 0x0000, /*  audio & Video */
    NETDEV_STREAM_MODE_VIDEO = 0x8000  /*  only video */
}NETDEV_STREAM_MODE_E;

/**
 * @enum tagNETDEVMediaFileFormat
 * @brief   Media file format Enumeration definition
 * @attention  None
 */
typedef enum tagNETDEVMediaFileFormat
{
    NETDEV_MEDIA_FILE_MP4                   = 0,    /*  mp4 media file (Audio + Video) */
    NETDEV_MEDIA_FILE_TS                    = 1,    /*  TS media file (Audio + Video) */
    NETDEV_MEDIA_FILE_MP4_ADD_TIME          = 2,    /*  MP4 media file with time in file name (Audio + Video) */
    NETDEV_MEDIA_FILE_TS_ADD_TIME           = 3,    /*  TS media file with time in file name (Audio + Video) */
    NETDEV_MEDIA_FILE_AUDIO_TS              = 4,    /*  TS audio file (Only audio) */
    NETDEV_MEDIA_FILE_AUDIO_MP4             = 5,    /*  MP4 audio file (Only audio) */
    NETDEV_MEDIA_FILE_AUDIO_TS_ADD_TIME     = 6,    /*  TS audio file with time in file name (Only audio) */
    NETDEV_MEDIA_FILE_AUDIO_MP4_ADD_TIME    = 7,    /*  MP4 audio file with time in file name (Only audio) */
    NETDEV_MEDIA_FILE_MP4_ADD_RCD_TIME      = 8,    /*  MP4 media file with start and end times in file name (Audio + Video)*/
    NETDEV_MEDIA_FILE_TS_ADD_RCD_TIME       = 9,    /*  TS media file with start and end times in file name (Audio + Video)*/
    NETDEV_MEDIA_FILE_AUDIO_MP4_ADD_RCD_TIME= 10,   /*  MP4 audio file with start and end times in file name (Only audio)*/
    NETDEV_MEDIA_FILE_AUDIO_TS_ADD_RCD_TIME = 11,   /*  TTS audio file with start and end times in file name (Only audio)*/
    NETDEV_MEDIA_FILE_VIDEO_MP4_ADD_RCD_TIME= 12,   /*  mp4 media file (Only video) */
    NETDEV_MEDIA_FILE_VIDEO_TS_ADD_RCD_TIME = 13,   /*  Tts media file (Only video) */

    NETDEV_MEDIA_FILE_AVI                   = 14,   /*  AVI media file (Audio + Video) */
    NETDEV_MEDIA_FILE_AVI_ADD_TIME          = 15,   /*  AVI media file with start and end times in file name (Audio + Video)*/
    NETDEV_MEDIA_FILE_AUDIO_AVI             = 16,   /* AVI audio file (Only audio) */
    NETDEV_MEDIA_FILE_AUDIO_AVI_ADD_TIME    = 17,   /* AVI audio file with time in file name (Only audio)*/
    NETDEV_MEDIA_FILE_AVI_ADD_RCD_TIME      = 18,   /* AVI audio file with start and end times in file name (Audio + Video)*/
    NETDEV_MEDIA_FILE_AUDIO_AVI_ADD_RCD_TIME= 19,   /* AVI audio file with start and end times in file name (Only audio)*/
    NETDEV_MEDIA_FILE_VIDEO_AVI_ADD_RCD_TIME= 20,   /* AVI media file (Only video) */

    NETDEV_MEDIA_FILE_INVALID
}NETDEV_MEDIA_FILE_FORMAT_E;

/**
 * @enum tagNETDEVPlayerVideoCodeType
 * @brief    Player Video encoding format Enumeration definition
 * @attention  None
 */
typedef enum tagNETDEVPlayerVideoCodeType
{
    NETDEV_PLAYER_VIDEO_CODE_MPEG2     = 0,          /* MPEG-2 */
    NETDEV_PLAYER_VIDEO_CODE_MPEG4     = 1,          /* MPEG-4 */
    NETDEV_PLAYER_VIDEO_CODE_H264      = 2,          /* H.264 */
    NETDEV_PLAYER_VIDEO_CODE_MJPEG     = 3,          /* MJPEG */
    NETDEV_PLAYER_VIDEO_CODE_H265      = 4,          /* H.265 */

    NETDEV_PLAYER_VIDEO_CODE_INVALID
}NETDEV_PLAYER_VIDEO_CODE_TYPE_E;

/**
 * @enum tagNETDEVVideoCodeType
 * @brief   Video encoding format Enumeration definition
 * @attention  None
 */
typedef enum tagNETDEVVideoCodeType
{
    NETDEV_VIDEO_CODE_MJPEG = 0,          /* MJPEG */
    NETDEV_VIDEO_CODE_H264  = 1,          /* H.264 */
    NETDEV_VIDEO_CODE_H265  = 2,          /* H.265 */
    NETDEV_VIDEO_CODE_INVALID
}NETDEV_VIDEO_CODE_TYPE_E;

/**
 * @enum tagNETDEVVideoFrameType
 * @brief    Video frame type Enumeration definition
 * @attention  None
 */
typedef enum tagNETDEVVideoFrameType
{
    NETDEV_VIDEO_FRAME_I = 0,               /* I-frame */
    NETDEV_VIDEO_FRAME_P = 1,               /* P-frame */
    NETDEV_VIDEO_FRAME_B = 2                /* B-frame */
}NETDEV_VIDEO_FRAME_TYPE_E;

/**
* @enum tagNetDEVAudioEncodeType
* @brief  Audio encode type
* @attention  None
*/
typedef enum tagNetDEVAudioEncodeType
{
    NETDEV_AUDIO_ENCODE_G711U = 0,          /*  Audio up to G.711U-law standard*/
    NETDEV_AUDIO_ENCODE_MP2   = 1,          /*  Audio up to MP2 standard */
    NETDEV_AUDIO_ENCODE_AAC   = 2,          /*  Audio up to AAC standard*/
    NETDEV_AUDIO_ENCODE_G711A = 3,          /*  Audio up to G.711A-law standard*/
    NETDEV_AUDIO_ENCODE_PCM   = 4,          /*  Audio up to PCM law standard*/
    NETDEV_AUDIO_ENCODE_NULL  = 5           /*  No audio */
}NETDEV_AUDIO_ENCODE_TYPE_E;

/**
* @enum tagNetDEVWaveFormatInfo
* @brief  Wave format info
* @attention  None
*/
typedef enum tagNetDEVWaveFormatInfo
{
    NETDEV_WAVE_FORMAT_PCM8M16        = 0,        /*  PCM,8k sampling rate,16 bit sampling*/
    NETDEV_WAVE_FORMAT_PCM16M16       = 1,        /*  PCM,16k sampling rate,16 bit sampling*/
    NETDEV_WAVE_FORMAT_PCM441M16      = 2,        /*  PCM,44.1k sampling rate,16 bit sampling*/
    NETDEV_WAVE_FORMAT_PCM11025M16    = 3,        /*  PCM,11.025k sampling rate,16 bit sampling*/
    NETDEV_WAVE_FORMAT_UNKNOWN
}NETDEV_WAVE_FORMAT_INFO_E;

/**
 * @enum tagNETDEVRenderScale
 * @brief    Video display ratio Enumeration definition
 * @attention  None
 */
typedef enum tagNETDEVRenderScale
{
    NETDEV_RENDER_SCALE_FULL        = 0,                  /*   Stretch */
    NETDEV_RENDER_SCALE_PROPORTION  = 1,                  /*   Scale */

    NETDEV_RENDER_SCALE_INVALID     = 0xFF
}NETDEV_RENDER_SCALE_E;

/**
 * @enum tagNETDEVPictureFormat
 * @brief   Picture type Enumeration definition
 * @attention  None
 */
typedef enum tagNETDEVPictureFormat
{
    NETDEV_PICTURE_BMP = 0,                  /*   Picture format is bmp */
    NETDEV_PICTURE_JPG = 1,                  /*   Picture format is jpg */

    NETDEV_PICTURE_INVALID
}NETDEV_PICTURE_FORMAT_E;

/**
 * @enum tagNETDEVVideoQuality
 * @brief    Video image quality Enumeration definition
 * @attention  None
 */
typedef enum tagNETDEVVideoQuality
{
    NETDEV_VQ_L0 = 0,                    /*   Highest */
    NETDEV_VQ_L1 = 1,
    NETDEV_VQ_L2 = 4,                    /*   Higher */
    NETDEV_VQ_L3 = 8,
    NETDEV_VQ_L4 = 12,                   /*   Medium */
    NETDEV_VQ_L5 = 16,
    NETDEV_VQ_L6 = 20,                   /*   Low */
    NETDEV_VQ_L7 = 24,
    NETDEV_VQ_L8 = 28,                   /*   Lower */
    NETDEV_VQ_L9 = 31,                   /*   Lowest */

    NETDEV_VQ_LEVEL_INVALID = -1         /*   Valid */
}NETDEV_VIDEO_QUALITY_E;

/**
 * @enum tagNETDEVPictureSize
 * @brief   Image resolution Enumeration definition
 * @attention None
 */
typedef enum tagNETDEVPictureSize
{
    NETDEV_PICTURE_SIZE_D1     = 0,           /* D1 */
    NETDEV_PICTURE_SIZE_4CIF   = 1,           /* 4CIF */
    NETDEV_PICTURE_SIZE_2CIF   = 2,           /* 2CIF */
    NETDEV_PICTURE_SIZE_CIF    = 3,           /* CIF */
    NETDEV_PICTURE_SIZE_960H   = 4,           /* 960H */
    NETDEV_PICTURE_SIZE_QCIF   = 5,           /* QCIF */
    NETDEV_PICTURE_SIZE_HALFD1 = 6,           /* HALFD1 */
    NETDEV_PICTURE_SIZE_720    = 7,           /* 720 */
    NETDEV_PICTURE_SIZE_1080   = 8,           /* 1080 */
    NETDEV_PICTURE_SIZE_XGA    = 9,           /* 1024*768 */
    NETDEV_PICTURE_SIZE_SXGA   = 10,          /* 1280*1024 */

    NETDEV_PICTURE_SIZE_INVALID               /*   Invalid value */
}NETDEV_PICTURE_SIZE_E;

/**
 * @enum tagNETDEVPtzCmdEnum
 * @brief   PTZ commands Enumeration definition
 * @attention  None
 */
typedef enum tagNETDEVPtzCmdEnum
{
#if 0
    NETDEV_PTZ_IRISCLOSE_STOP       =0x0101,       /*   Iris close stop */
    NETDEV_PTZ_IRISCLOSE            =0x0102,       /*   Iris close */
    NETDEV_PTZ_IRISCLOSE_STOP       =0x0103,       /*   Iris open stop */
    NETDEV_PTZ_IRISOPEN             =0x0104,       /*   Iris open */
#endif
    NETDEV_PTZ_FOCUSNEAR_STOP       =0x0201,       /*   Focus near stop */
    NETDEV_PTZ_FOCUSNEAR            =0x0202,       /*   Focus near */
    NETDEV_PTZ_FOCUSFAR_STOP        =0x0203,       /*   Focus far stop */
    NETDEV_PTZ_FOCUSFAR             =0x0204,       /*   Focus far */

    NETDEV_PTZ_ZOOMTELE_STOP        = 0x0301,       /*   Zoom in stop */
    NETDEV_PTZ_ZOOMTELE             = 0x0302,       /*   Zoom in */
    NETDEV_PTZ_ZOOMWIDE_STOP        = 0x0303,       /*   Zoom out stop */
    NETDEV_PTZ_ZOOMWIDE             = 0x0304,       /*   Zoom out */
    NETDEV_PTZ_TILTUP               = 0x0402,       /*   Tilt up */
    NETDEV_PTZ_TILTDOWN             = 0x0404,       /*   Tilt down */
    NETDEV_PTZ_PANRIGHT             = 0x0502,       /*   Pan right */
    NETDEV_PTZ_PANLEFT              = 0x0504,       /*   Pan left */
    NETDEV_PTZ_LEFTUP               = 0x0702,       /*   Move up left */
    NETDEV_PTZ_LEFTDOWN             = 0x0704,       /*   Move down left */
    NETDEV_PTZ_RIGHTUP              = 0x0802,       /*   Move up right */
    NETDEV_PTZ_RIGHTDOWN            = 0x0804,       /*   Move down right */

#if 0
    NETDEV_PTZ_PRESAVE              = 0x0601,       /*   Save preset */
    NETDEV_PTZ_PRECALL              = 0x0602,       /*   Call preset */
    NETDEV_PTZ_PREDEL               = 0x0603,       /*   Delete preset */
#endif

    NETDEV_PTZ_ALLSTOP              = 0x0901,       /*   All-stop command word */
    NETDEV_PTZ_FOCUS_AND_IRIS_STOP  = 0x0907,       /*  Focus & Iris-stop command word */
    NETDEV_PTZ_MOVE_STOP            = 0x0908,       /*  move stop command word */
    NETDEV_PTZ_ZOOM_STOP            = 0x0909,       /*  zoom stop command word */

    NETDEV_PTZ_TRACKCRUISE          = 0x1001,       /*   Start route patrol*/
    NETDEV_PTZ_TRACKCRUISESTOP      = 0x1002,       /*   Stop route patrol*/
    NETDEV_PTZ_TRACKCRUISEREC       = 0x1003,       /*   Start recording route */
    NETDEV_PTZ_TRACKCRUISERECSTOP   = 0x1004,       /*   Stop recording route */
    NETDEV_PTZ_TRACKCRUISEADD       = 0x1005,       /*   Add patrol route */
    NETDEV_PTZ_TRACKCRUISEDEL       = 0x1006,       /*   Delete patrol route */

    NETDEV_PTZ_AREAZOOMIN           = 0x1101,       /*   Zoom in area */
    NETDEV_PTZ_AREAZOOMOUT          = 0x1102,       /*   Zoom out area */
    NETDEV_PTZ_AREAZOOM3D           = 0x1103,       /*   3D positioning */

    NETDEV_PTZ_BRUSHON              = 0x0A01,       /*   Wiper on */
    NETDEV_PTZ_BRUSHOFF             = 0x0A02,       /*   Wiper off */

    NETDEV_PTZ_LIGHTON              = 0x0B01,       /*   Lamp on */
    NETDEV_PTZ_LIGHTOFF             = 0x0B02,       /*   Lamp off */

    NETDEV_PTZ_HEATON               = 0x0C01,       /*   Heater on */
    NETDEV_PTZ_HEATOFF              = 0x0C02,       /*   Heater off */

    NETDEV_PTZ_SNOWREMOINGON        = 0x0E01,       /*   Snowremoval on */
    NETDEV_PTZ_SNOWREMOINGOFF       = 0x0E02,       /*   Snowremoval off  */

#if 0
    NETDEV_PTZ_ABSPOSITION          = 0x0902,       /*   Set absolute position of camera */
    NETDEV_PTZ_GUARD                = 0x0903,       /*   Return to home position (this command is not implemented on the PTZ template) */
    NETDEV_PTZ_SPEEDSET             = 0x0904,       /*   Set speed */

    NETDEV_PTZ_INFRAREDON           = 0x0D01,       /*   IR on */
    NETDEV_PTZ_INFRAREDOFF          = 0x0D02,       /*   IR off */

    NETDEV_PTZ_PRESETCRUISE         = 0x1001,       /*   Preset-based PTZ patrol (the command word is not implemented on the PTZ template) */
    NETDEV_PTZ_PRESETCRUISESTOP     = 0x1002,       /*   Preset-based PTZ patrol stop (the command word is not implemented on the PTZ template) */
    NETDEV_PTZ_CRUISEDEL            = 0X1003,       /*   Delete route */
    NETDEV_PTZ_CRUISEADDPRESET      = 0x1004,       /*   Add preset to route */
    NETDEV_PTZ_CRUISEADDSTART       = 0x1005,       /*   Start adding preset to route */
    NETDEV_PTZ_CRUISEADDSTOP        = 0x1006,       /*   Stop adding preset to route */
#endif

    NETDEV_PTZ_INVALID

} NETDEV_PTZ_E;

/**
 * @enum tagNETDEVPtzPresetCmd
 * @brief   PTZ preset operation commands Enumeration Definition
 * @attention  None
 */
typedef enum tagNETDEVPtzPresetCmd
{
    NETDEV_PTZ_SET_PRESET   = 0,            /*   Set preset */
    NETDEV_PTZ_CLE_PRESET   = 1,            /*   Clear preset */
    NETDEV_PTZ_GOTO_PRESET  = 2             /*   Go to preset */
}NETDEV_PTZ_PRESETCMD_E;

/**
 * @enum tagNETDEVPTZCruiseCmd
 * @brief   PTZ patrol operation commands Enumeration Definition
 * @attention  None
 */
typedef enum tagNETDEVPTZCruiseCmd
{
    NETDEV_PTZ_ADD_CRUISE      = 0,         /*    Add patrol route */
    NETDEV_PTZ_MODIFY_CRUISE   = 1,         /*   Edit patrol route */
    NETDEV_PTZ_DEL_CRUISE      = 2,         /*   Delete patrol route */
    NETDEV_PTZ_RUN_CRUISE      = 3,         /*   Start patrol */
    NETDEV_PTZ_STOP_CRUISE     = 4          /*   Stop patrol */
}NETDEV_PTZ_CRUISECMD_E;

/**
 * @enum tagNETDEVPlayControl
 * @brief   Playback control commands Enumeration definition
 * @attention  None
 */
typedef enum tagNETDEVPlayControl
{
    NETDEV_PLAY_CTRL_PLAY            = 0,           /*   Play */
    NETDEV_PLAY_CTRL_PAUSE           = 1,           /*   Pause */
    NETDEV_PLAY_CTRL_RESUME          = 2,           /*   Resume */
    NETDEV_PLAY_CTRL_GETPLAYTIME     = 3,           /*   Obtain playing time */
    NETDEV_PLAY_CTRL_SETPLAYTIME     = 4,           /*   Configure playing time */
    NETDEV_PLAY_CTRL_GETPLAYSPEED    = 5,           /*   Obtain playing speed */
    NETDEV_PLAY_CTRL_SETPLAYSPEED    = 6,           /*   Configure playing speed */
    NETDEV_PLAY_CTRL_SINGLE_FRAME    = 7            /*   Configure single frame playing speed */
}NETDEV_VOD_PLAY_CTRL_E;

/**
 * @enum tagNETDEVVodPlayStatus
 * @brief .  Playback and download status Enumeration definition
 * @attention  None
 */
typedef enum tagNETDEVVodPlayStatus
{
    /**   Play status */
    NETDEV_PLAY_STATUS_16_BACKWARD          = 0,            /* Backward at 16x speed */
    NETDEV_PLAY_STATUS_8_BACKWARD           = 1,            /* Backward at 8x speed */
    NETDEV_PLAY_STATUS_4_BACKWARD           = 2,            /* Backward at 4x speed */
    NETDEV_PLAY_STATUS_2_BACKWARD           = 3,            /* Backward at 2x speed */
    NETDEV_PLAY_STATUS_1_BACKWARD           = 4,            /* Backward at normal speed */
    NETDEV_PLAY_STATUS_HALF_BACKWARD        = 5,            /* Backward at 1/2 speed */
    NETDEV_PLAY_STATUS_QUARTER_BACKWARD     = 6,            /* Backward at 1/4 speed */
    NETDEV_PLAY_STATUS_QUARTER_FORWARD      = 7,            /* Play at 1/4 speed */
    NETDEV_PLAY_STATUS_HALF_FORWARD         = 8,            /* Play at 1/2 speed */
    NETDEV_PLAY_STATUS_1_FORWARD            = 9,            /* Forward at normal speed */
    NETDEV_PLAY_STATUS_2_FORWARD            = 10,           /* Forward at 2x speed */
    NETDEV_PLAY_STATUS_4_FORWARD            = 11,           /* Forward at 4x speed */
    NETDEV_PLAY_STATUS_8_FORWARD            = 12,           /* Forward at 8x speed */
    NETDEV_PLAY_STATUS_16_FORWARD           = 13,           /* Forward at 16x speed */
    NETDEV_PLAY_STATUS_2_FORWARD_IFRAME     = 14,           /* Forward at 2x speed(I frame) */
    NETDEV_PLAY_STATUS_4_FORWARD_IFRAME     = 15,           /* Forward at 4x speed(I frame) */
    NETDEV_PLAY_STATUS_8_FORWARD_IFRAME     = 16,           /* Forward at 8x speed(I frame) */
    NETDEV_PLAY_STATUS_16_FORWARD_IFRAME    = 17,           /* Forward at 16x speed(I frame) */
    NETDEV_PLAY_STATUS_2_BACKWARD_IFRAME    = 18,           /* Backward at 2x speed(I frame) */
    NETDEV_PLAY_STATUS_4_BACKWARD_IFRAME    = 19,           /* Backward at 4x speed(I frame) */
    NETDEV_PLAY_STATUS_8_BACKWARD_IFRAME    = 20,           /*  Backward at 8x speed(I frame) */
    NETDEV_PLAY_STATUS_16_BACKWARD_IFRAME   = 21,           /*  Backward at 16x speed(I frame) */
    NETDEV_PLAY_STATUS_INTELLIGENT_FORWARD  = 22,           /*  Intelligent forward */
    NETDEV_PLAY_STATUS_1_FRAME_FORWD        = 23,           /*  Forward at 1 frame speed */
    NETDEV_PLAY_STATUS_1_FRAME_BACK         = 24,           /*  Backward at 1 frame speed */

    NETDEV_PLAY_STATUS_40_FORWARD           = 25,           /*  Forward at 40x speed*/

    NETDEV_PLAY_STATUS_32_FORWARD_IFRAME    = 26,           /*  Forward at 32x speed(I frame)*/
    NETDEV_PLAY_STATUS_32_BACKWARD_IFRAME   = 27,           /*  Backward at 32x speed(I frame)*/
    NETDEV_PLAY_STATUS_64_FORWARD_IFRAME    = 28,           /*  Forward at 64x speed(I frame)*/
    NETDEV_PLAY_STATUS_64_BACKWARD_IFRAME   = 29,           /*  Backward at 64x speed(I frame)*/
    NETDEV_PLAY_STATUS_128_FORWARD_IFRAME   = 30,           /*  Forward at 128x speed(I frame)*/
    NETDEV_PLAY_STATUS_128_BACKWARD_IFRAME  = 31,           /*  Backward at 128x speed(I frame)*/
    NETDEV_PLAY_STATUS_256_FORWARD_IFRAME   = 32,           /*  Forward at 256x speed(I frame)*/
    NETDEV_PLAY_STATUS_256_BACKWARD_IFRAME  = 33,           /*  Backward at 256x speed(I frame)*/

    NETDEV_PLAY_STATUS_32_FORWARD           = 34,           /* Forward at 32x speed */
    NETDEV_PLAY_STATUS_32_BACKWARD          = 35,           /* Backward at 32x speed */

    NETDEV_PLAY_STATUS_INVALID
}NETDEV_VOD_PLAY_STATUS_E;

/**
 * @enum tagNETDEVDownloadSpeed
 * @brief   Recording download speed
 * @attention  None
 */
typedef enum tagNETDEVDownloadSpeed
{
    NETDEV_DOWNLOAD_SPEED_ONE           = 0,                /*   1x */
    NETDEV_DOWNLOAD_SPEED_TWO           = 1,                /*   2x */
    NETDEV_DOWNLOAD_SPEED_FOUR          = 2,                /*   4x */
    NETDEV_DOWNLOAD_SPEED_EIGHT         = 3,                /*   8x */
    NETDEV_DOWNLOAD_SPEED_TWO_IFRAME    = 4,                /*   I2x */
    NETDEV_DOWNLOAD_SPEED_FOUR_IFRAME   = 5,                /*   I4x */
    NETDEV_DOWNLOAD_SPEED_EIGHT_IFRAME  = 6,                /*   I8x */
    NETDEV_DOWNLOAD_SPEED_HALF          = 7                 /*   1/2x */
}NETDEV_E_DOWNLOAD_SPEED_E;

/**
 * @enum tagNETDEVStoreType
 * @brief   Recording storage type Enumeration definition
 * @attention  None
 */
typedef enum tagNETDEVStoreType
{
    NETDEV_TYPE_STORE_TYPE_ALL                  = 0,            /*   All */

    NETDEV_EVENT_STORE_TYPE_MOTIONDETECTION     = 4,            /*   Motion detection */
    NETDEV_EVENT_STORE_TYPE_DIGITALINPUT        = 5,            /*   Digital input */
    NETDEV_EVENT_STORE_TYPE_VIDEOLOSS           = 7,            /*   Video loss */

    NETDEV_TYPE_STORE_TYPE_INVALID              = 0xFF          /*   Invalid value */
}NETDEV_PLAN_STORE_TYPE_E;

/**
 * @enum tagNETDEVException
 * @brief   Exception callback message types Enumeration definition 
 * @attention  None
 */
typedef enum tagNETDEVException
{
    /*   Playback exceptions report 300~399 */
    NETDEV_EXCEPTION_REPORT_VOD_END             = 300,          /*   Playback ended*/
    NETDEV_EXCEPTION_REPORT_VOD_ABEND           = 301,          /*   Playback exception occured */
    NETDEV_EXCEPTION_REPORT_BACKUP_END          = 302,          /*   Backup ended */
    NETDEV_EXCEPTION_REPORT_BACKUP_DISC_OUT     = 303,          /*   Disk removed */
    NETDEV_EXCEPTION_REPORT_BACKUP_DISC_FULL    = 304,          /*   Disk full */
    NETDEV_EXCEPTION_REPORT_BACKUP_ABEND        = 305,          /*   Backup failure caused by other reasons */

    NETDEV_EXCEPTION_EXCHANGE                   = 0x8000,       /*  Exception occurred during user interaction (keep-alive timeout) */
    NETDEV_EXCEPTION_REPORT_ALARM_INTERRUPT     = 0x8001,       /*  Alarm reports abnormal termination of live preservation failure or long connection disconnection */

    NETDEV_EXCEPTION_REPORT_INVALID             = 0xFFFF        /*   Invalid value */
}NETDEV_EXCEPTION_TYPE_E;

/**
 * @enum tagNETDEVAlarmTypeEn
 * @brief Alarm configuration operation Enumeration definition
 * @attention  None
 */
typedef enum tagNETDEVAlarmTypeEn
{
    /*   Recoverable alarms */
    NETDEV_ALARM_MOVE_DETECT                        = 1,            /*  Motion detection alarm */
    NETDEV_ALARM_VIDEO_LOST                         = 2,            /*  Video loss alarm */
    NETDEV_ALARM_VIDEO_TAMPER_DETECT                = 3,            /*  Tampering detection alarm */
    NETDEV_ALARM_INPUT_SWITCH                       = 4,            /*  boolean input alarm */
    NETDEV_ALARM_TEMPERATURE_HIGH                   = 5,            /*  High temperature alarm */
    NETDEV_ALARM_TEMPERATURE_LOW                    = 6,            /*  Low temperature alarm */
    NETDEV_ALARM_AUDIO_DETECT                       = 7,            /*  Audio detection alarm */
    NETDEV_ALARM_DISK_ABNORMAL                      = 8,            /*  Disk abnormal */
    NETDEV_ALARM_DISK_OFFLINE                       = 9,            /*  Disk online (Compatible with previous versions, not maintained) */
    NETDEV_ALARM_DISK_ONLINE                        = 10,           /*  Disk online */
    NETDEV_ALARM_DISK_STORAGE_WILL_FULL             = 11,           /*  Disk StorageGoingfull */
    NETDEV_ALARM_DISK_STORAGE_IS_FULL               = 12,           /*  StorageIsfull */
    NETDEV_ALARM_DISK_RAID_DISABLED                 = 13,           /*  RAIDDisabled */
    NETDEV_ALARM_DISK_RAID_DEGRADED                 = 14,           /*  RAIDDegraded */
    NETDEV_ALARM_DISK_RAID_RECOVERED                = 15,           /*  RAIDDegraded */

    /*   Status report of NVR and access device 100~199 */
    NETDEV_ALARM_REPORT_DEV_ONLINE                  = 100,          /*   Device online */
    NETDEV_ALARM_REPORT_DEV_OFFLINE                 = 101,          /*   Device offline */
    NETDEV_ALARM_REPORT_DEV_VIDEO_LOSS              = 102,          /*   Video loss */
    NETDEV_ALARM_REPORT_DEV_VIDEO_LOSS_RECOVER      = 103,          /*   Video loss recover */
    NETDEV_ALARM_REPORT_DEV_REBOOT                  = 104,          /*   Device restart */
    NETDEV_ALARM_REPORT_DEV_SERVICE_REBOOT          = 105,          /*   Service restart */
    NETDEV_ALARM_REPORT_DEV_DELETE_CHL              = 106,          /*   Delete channel */

    /*   Live view exception report 200~299 */
    NETDEV_ALARM_NET_FAILED                         = 200,          /*  Network error */
    NETDEV_ALARM_NET_TIMEOUT                        = 201,          /*  Network timeout */
    NETDEV_ALARM_SHAKE_FAILED                       = 202,          /*  Interaction error */
    NETDEV_ALARM_STREAMNUM_FULL                     = 203,          /*  Stream full */
    NETDEV_ALARM_STREAM_THIRDSTOP                   = 204,          /*  Third party stream stopped */
    NETDEV_ALARM_FILE_END                           = 205,          /*  File ended */
    NETDEV_ALARM_RTMP_CONNECT_FAIL                  = 206,          /*  RTMP connection failed */
    NETDEV_ALARM_RTMP_INIT_FAIL                     = 207,          /*  RTMP init faliled*/
    /*   Valid alarms within 24 hours without arming schedule */
    NETDEV_ALARM_ALLTIME_FLAG_START                 = 400,          /*   Start marker of alarm without arming schedule */
    NETDEV_ALARM_STOR_ERR                           = 401,          /*   Storage error */
    NETDEV_ALARM_STOR_DISOBEY_PLAN                  = 402,          /*   Not stored as planned */

    /*   Unrecoverable alarms */
    NETDEV_ALARM_NO_RECOVER_FLAG_START              = 500,          /*  Start marker of unrecoverable alarm */
    NETDEV_ALARM_DISK_ERROR                         = 501,          /*  Disk error */
    NETDEV_ALARM_ILLEGAL_ACCESS                     = 502,          /*  Illegal access */
    NETDEV_ALARM_LINE_CROSS                         = 503,          /*  Line cross */
    NETDEV_ALARM_OBJECTS_INSIDE                     = 504,          /*  Objects inside */
    NETDEV_ALARM_FACE_RECOGNIZE                     = 505,          /*  Face recognize */
    NETDEV_ALARM_IMAGE_BLURRY                       = 506,          /*  Image blurry */
    NETDEV_ALARM_SCENE_CHANGE                       = 507,          /*  Scene change */
    NETDEV_ALARM_SMART_TRACK                        = 508,          /*  Smart track */
    NETDEV_ALARM_LOITERING_DETECTOR                 = 509,          /*  Loitering Detector */
	NETDEV_ALARM_BANDWIDTH_CHANGE					= 526,          /*  Bandwidth change */
    NETDEV_ALARM_ALLTIME_FLAG_END                   = 600,          /*  End marker of alarm without arming schedule */
    NETDEV_ALARM_MEDIA_CONFIG_CHANGE                = 601,          /*  media configurationchanged */
	NETDEV_ALARM_REMAIN_ARTICLE                     = 602,          /*  Remain article*/
    NETDEV_ALARM_PEOPLE_GATHER                      = 603,          /*  People gather alarm*/
    NETDEV_ALARM_ENTER_AREA                         = 604,          /*  Enter area*/
    NETDEV_ALARM_LEAVE_AREA                         = 605,          /*  Leave area*/
    NETDEV_ALARM_ARTICLE_MOVE                       = 606,          /*  Article move*/

    /*   Alarm recover */
    NETDEV_ALARM_RECOVER_BASE                       = 1000,         /*   Alarm recover base */
    NETDEV_ALARM_MOVE_DETECT_RECOVER                = 1001,         /*   Motion detection alarm recover */
    NETDEV_ALARM_VIDEO_LOST_RECOVER                 = 1002,         /*   Video loss alarm recover */
    NETDEV_ALARM_VIDEO_TAMPER_RECOVER               = 1003,         /*   Tampering detection alarm recover */
    NETDEV_ALARM_INPUT_SWITCH_RECOVER               = 1004,         /*   Boolean input alarm recover */
    NETDEV_ALARM_TEMPERATURE_RECOVER                = 1005,         /*   Temperature alarm recover */
    NETDEV_ALARM_AUDIO_DETECT_RECOVER               = 1007,         /*   Audio detection alarm recover */
    NETDEV_ALARM_DISK_ABNORMAL_RECOVER              = 1008,         /*  Disk abnormal recover */
    NETDEV_ALARM_DISK_OFFLINE_RECOVER               = 1009,         /*  Disk online recover */
    NETDEV_ALARM_DISK_ONLINE_RECOVER                = 1010,         /*  Disk online recover */
    NETDEV_ALARM_DISK_STORAGE_WILL_FULL_RECOVER     = 1011,         /*  Disk StorageGoingfull recover */
    NETDEV_ALARM_DISK_STORAGE_IS_FULL_RECOVER       = 1012,         /*  StorageIsfull recover */
    NETDEV_ALARM_DISK_RAID_DISABLED_RECOVER         = 1013,         /*  RAIDDisabled recover */
    NETDEV_ALARM_DISK_RAID_DEGRADED_RECOVER         = 1014,         /*  RAIDDegraded recover */

    NETDEV_ALARM_STOR_ERR_RECOVER                   = 1201,         /*   Storage error recover */
    NETDEV_ALARM_STOR_DISOBEY_PLAN_RECOVER          = 1202,         /*   Not stored as planned recover */

    NETDEV_ALARM_IMAGE_BLURRY_RECOVER               = 1506,         /*   Image blurry recover */
    NETDEV_ALARM_SMART_TRACK_RECOVER                = 1508,         /*   Smart track recover */

    NETDEV_ALARM_IP_CONFLICT                        = 1509,         /*  IP conflict exception alarm*/
    NETDEV_ALARM_IP_CONFLICT_CLEARED                = 1510,         /* IP conflict exception alarm recovery */

    /* Smart信息 */
    NETDEV_ALARM_SMART_READ_ERROR_RATE          	= 1511,        /* Error reding the underlying data */
    NETDEV_ALARM_SMART_SPIN_UP_TIME                 = 1512,        /* Rotation time of spindle */
    NETDEV_ALARM_SMART_START_STOP_COUNT             = 1513,        /* Rev. Stop counting*/
    NETDEV_ALARM_SMART_REALLOCATED_SECTOR_COUNT     = 1514,        /* Remap sector count*/
    NETDEV_ALARM_SMART_SEEK_ERROR_RATE              = 1515,        /* Trace error rate*/
    NETDEV_ALARM_SMART_POWER_ON_HOURS               = 1516,       
    NETDEV_ALARM_SMART_SPIN_RETRY_COUNT             = 1517,        
    NETDEV_ALARM_SMART_CALIBRATION_RETRY_COUNT      = 1518,       
    NETDEV_ALARM_SMART_POWER_CYCLE_COUNT            = 1519,        
    NETDEV_ALARM_SMART_POWEROFF_RETRACT_COUNT       = 1520,   
    NETDEV_ALARM_SMART_LOAD_CYCLE_COUNT             = 1521,      
    NETDEV_ALARM_SMART_TEMPERATURE_CELSIUS          = 1522,     
    NETDEV_ALARM_SMART_REALLOCATED_EVENT_COUNT      = 1523,      
    NETDEV_ALARM_SMART_CURRENT_PENDING_SECTOR       = 1524,        
    NETDEV_ALARM_SMART_OFFLINE_UNCORRECTABLE        = 1525,   
    NETDEV_ALARM_SMART_UDMA_CRC_ERROR_COUNT         = 1526,      
    NETDEV_ALARM_SMART_MULTI_ZONE_ERROR_RATE        = 1527,

    NETDEV_ALARM_INVALID                            = 0xFFFF        /* 无效�? Invalid value */
}NETDEV_ALARM_TYPE_E;

/**
 * @enum tagNETDEVAlarmSrcTypeEn
 * @brief Alarm configuration operation Enumeration definition
 * @attention �?None
 */
typedef enum tagNETDEVAlarmSrcTypeEn
{
    NETDEV_ALARM_SRC_LOCAL_HARD_DISK                            = 0,        
    NETDEV_ALARM_SRC_EX_CABINET_1_STORAGE_DISK                  = 1, 
    NETDEV_ALARM_SRC_EX_CABINET_2_STORAGE_DISK                  = 2, 
    NETDEV_ALARM_SRC_ARRAY_STORAGE_DISK                         = 3,
    NETDEV_ALARM_SRC_NAS_STORAGE_DISK                           = 4, 
    NETDEV_ALARM_SRC_SAN_STORAGE_DISK                           = 5, 
    NETDEV_ALARM_SRC_ESATA_STORAGE_DISK                         = 6, 
    NETDEV_ALARM_SRC_SD_STORAGE_DISK                            = 7, 
    NETDEV_ALARM_SRC_VIDEO_CHANNEL                              = 8, 
    NETDEV_ALARM_SRC_ALARM_INPUT_CHANNEL                        = 9, 
    NETDEV_ALARM_SRC_SYSTEM                                     = 10,


    NETDEV_ALARM_SRC_INVALID                                    = 0xFFFF
}NETDEV_ALARM_SRC_TYPE_E;



/**
 * @enum tagNETDEVLogMainType
 * @brief  Major types of logs Enumeration definition
 * @attention  None
 */
typedef enum tagNETDEVLogMainType
{
    NETDEV_LOG_MAIN_TYPE_ALL                    = 0,               /*   Logs of all types */
    NETDEV_LOG_MAIN_TYPE_ALARM                  = 1,               /*   Alarms */
    NETDEV_LOG_MAIN_TYPE_EXCEPTION              = 2,               /*   Exceptions */
    NETDEV_LOG_MAIN_TYPE_OPERATION              = 3,               /*   Operations */
    NETDEV_LOG_MAIN_TYPE_MESSAGE                = 4,               /*   Messages */

    NETDEV_LOG_MAIN_TYPE_INVALID                = 0xFFFF            /*   Invalid value */
}NETDEV_LOG_MAIN_TYPE_E;

/**
 * @enum tagNETDEVLogSubType
 * @brief   Minor type IDs of logs Enumeration definition
 * @attention  None
 */
typedef enum tagNETDEVLogSubType
{
    NETDEV_LOG_ALL_SUB_TYPES                     = 0x0101,          /*  All information logs */

    /*   Information logs */
    NETDEV_LOG_MSG_HDD_INFO                     = 300,              /*   HDD information */
    NETDEV_LOG_MSG_SMART_INFO                   = 301,              /*   S.M.A.R.T information */
    NETDEV_LOG_MSG_REC_OVERDUE                  = 302,              /*   Expired recording deletion */
    NETDEV_LOG_MSG_PIC_REC_OVERDUE              = 303,              /*   Expired image deletion */

    /*   notification logs */
    NETDEV_LOG_NOTICE_IPC_ONLINE                = 310,              /*   Device online */
    NETDEV_LOG_NOTICE_IPC_OFFLINE               = 311,              /*   Device offline */
    NETDEV_LOG_NOTICE_ARRAY_RECOVER             = 312,              /*   arrayRecover */
    NETDEV_LOG_NOTICE_INIT_ARRARY               = 313,              /*   initializeArray */
    NETDEV_LOG_NOTICE_REBUILD_ARRARY            = 314,              /*   rebuildArray */
    NETDEV_LOG_NOTICE_POE_PORT_STATUS           = 315,              /*   poePortStatus */
    NETDEV_LOG_NOTICE_NETWORK_PORT_STATUS       = 316,              /*  networkPortStatus */
    NETDEV_LOG_NOTICE_DISK_ONLINE               = 317,              /*   Disk online */

    /*   Sub type log ID of alarm logs */
    NETDEV_LOG_ALARM_MOTION_DETECT              = 350,              /*   Motion detection alarm */
    NETDEV_LOG_ALARM_MOTION_DETECT_RESUME       = 351,              /*   Motion detection alarm recover */
    NETDEV_LOG_ALARM_VIDEO_LOST                 = 352,              /*   Video loss alarm */
    NETDEV_LOG_ALARM_VIDEO_LOST_RESUME          = 353,              /*   Video loss alarm recover */
    NETDEV_LOG_ALARM_VIDEO_TAMPER_DETECT        = 354,              /*   Tampering detection alarm */
    NETDEV_LOG_ALARM_VIDEO_TAMPER_RESUME        = 355,              /*   Tampering detection alarm recover */
    NETDEV_LOG_ALARM_INPUT_SW                   = 356,              /*   Boolean input alarm */
    NETDEV_LOG_ALARM_INPUT_SW_RESUME            = 357,              /*   Boolean input alarm recover */
    NETDEV_LOG_ALARM_IPC_ONLINE                 = 358,              /*   Device online */
    NETDEV_LOG_ALARM_IPC_OFFLINE                = 359,              /*   Device offline */
    
    NETDEV_LOG_ALARM_AUDIO_DETECTION_START      = 360,              /*   Audio detection start */
    NETDEV_LOG_ALARM_AUDIO_DETECTION_END        = 361,              /*   Audio detection end */
    NETDEV_LOG_ALARM_CROSS_LINE_DETECT          = 362,              /*   CrossLine detection */
    NETDEV_LOG_ALARM_FACE_DETECT                = 363,              /*   Face Detection */
    NETDEV_LOG_ALARM_INTRUSION_DETECT           = 364,              /*   Intrusion Detection */
    NETDEV_LOG_ALARM_POS                        = 365,              /*   POS Alarm */
    NETDEV_LOG_ALARM_IMAGETOOBLURRY_ON          = 366,              /*   Defocus detection started*/
    NETDEV_LOG_ALARM_IMAGETOOBLURRY_OFF         = 367,              /*   Defocus detection ended*/
    NETDEV_LOG_ALARM_GLOBAL_SCENE_CHANGE        = 368,              /*   Scene change detection*/
    NETDEV_LOG_ALARM_AUTO_TRACK_ON              = 369,              /*   Auto tracking started*/
    NETDEV_LOG_ALARM_AUTO_TRACK_OFF             = 370,              /*   Auto tracking ended*/

    /*   Sub type log ID of exception logs */
    NETDEV_LOG_EXCEP_DISK_ONLINE                = 400,              /*   Disk online */
    NETDEV_LOG_EXCEP_DISK_OFFLINE               = 401,              /*   Disk offline */
    NETDEV_LOG_EXCEP_DISK_ERR                   = 402,              /*   Disk exception */
    NETDEV_LOG_EXCEP_STOR_ERR                   = 403,              /*   Storage error */
    NETDEV_LOG_EXCEP_STOR_ERR_RECOVER           = 404,              /*   Storage error recover */
    NETDEV_LOG_EXCEP_STOR_DISOBEY_PLAN          = 405,              /*   Not stored as planned */
    NETDEV_LOG_EXCEP_STOR_DISOBEY_PLAN_RECOVER  = 406,              /*   Not stored as planned recover */
    NETDEV_LOG_EXCEP_ILLEGAL_ACCESS             = 407,              /*   Illegal access */
    NETDEV_LOG_EXCEP_IP_CONFLICT                = 408,              /*   IP address conflict */
    NETDEV_LOG_EXCEP_NET_BROKEN                 = 409,              /*   Network disconnection */
    NETDEV_LOG_EXCEP_PIC_REC_ERR                = 410,              /*   Failed to get captured image */
    NETDEV_LOG_EXCEP_VIDEO_EXCEPTION            = 411,              /*   Video input exception (for analog channel only) */
    NETDEV_LOG_EXCEP_VIDEO_MISMATCH             = 412,              /*   Video standards do not match */
    NETDEV_LOG_EXCEP_RESO_MISMATCH              = 413,              /*   Encoding resolution and front-end resolution do not match */
    NETDEV_LOG_EXCEP_TEMP_EXCE                  = 414,              /*   Temperature exception */
    NETDEV_LOG_EXCEP_RUNOUT_RECORD_SPACE        = 415,              /*   runOutOfRecordSpace */
    NETDEV_LOG_EXCEP_RUNOUT_IMAGE_SPACE         = 416,              /*   runOutOfImageSpace */
    NETDEV_LOG_EXCEP_OUT_RECORD_SPACE           = 417,              /*   recordSpaceUsedUp */
    NETDEV_LOG_EXCEP_OUT_IMAGE_SPACE            = 418,              /*   imageSpaceUsedUp */
    NETDEV_LOG_EXCEP_ANRIDISASSEMBLY            = 419,              /*   antiDisassembly Alarm */
    NETDEV_LOG_EXCEP_ANRIDISASSEMBLY_RECOVER    = 420,              /*  antiDisassembly AlarmClear*/
    NETDEV_LOG_EXCEP_ARRAY_DAMAGE               = 421,              /*   arrayDamage */
    NETDEV_LOG_EXCEP_ARRAY_DEGRADE              = 422,              /*   arrayDegrade */
    NETDEV_LOG_EXCEP_RECORD_SNAPSHOT_ABNOR      = 423,              /*   recordSnapshotAbnormal */
    NETDEV_LOG_EXCEP_NET_BROKEN_RECOVER         = 424,              /*   networkDisconnectClear */
    NETDEV_LOG_EXCEP_IP_CONFLICT_RECOVER        = 425,              /*   ipConflictClear */

    /*   Sub type log ID of operation logs */
    /*   Services */
    NETDEV_LOG_OPSET_LOGIN                      = 450,              /*   User login */
    NETDEV_LOG_OPSET_LOGOUT                     = 451,              /*   Log out */
    NETDEV_LOG_OPSET_USER_ADD                   = 452,              /*   Add user */
    NETDEV_LOG_OPSET_USER_DEL                   = 453,              /*   Delete user */
    NETDEV_LOG_OPSET_USER_MODIFY                = 454,              /*   Modify user */
    NETDEV_LOG_OPSET_START_REC                  = 455,              /*   Start recording */
    NETDEV_LOG_OPSET_STOP_REC                   = 456,              /*   Stop recording */
    NETDEV_LOG_OPSETR_PLAY_DOWNLOAD             = 457,              /*   Playback and download */
    NETDEV_LOG_OPSET_DOWNLOAD                   = 458,              /*   Download */
    NETDEV_LOG_OPSET_PTZCTRL                    = 459,              /*   PTZ control */
    NETDEV_LOG_OPSET_PREVIEW                    = 460,              /*   Live preview */
    NETDEV_LOG_OPSET_REC_TRACK_START            = 461,              /*   Start recording route */
    NETDEV_LOG_OPSET_REC_TRACK_STOP             = 462,              /*   Stop recording route */
    NETDEV_LOG_OPSET_START_TALKBACK             = 463,              /*   Start two-way audio */
    NETDEV_LOG_OPSET_STOP_TALKBACK              = 464,              /*   Stop two-way audio */
    NETDEV_LOG_OPSET_IPC_ADD                    = 465,              /*   Add IP camera */
    NETDEV_LOG_OPSET_IPC_DEL                    = 466,              /*   Delete IP camera */
    NETDEV_LOG_OPSET_IPC_SET                    = 467,              /*   Modify IP camera */
    NETDEV_LOG_OPSET_IPC_QUICK_ADD              = 468,              /*   quickAddIpc*/
    NETDEV_LOG_OPSET_IPC_ADD_BY_NETWORK         = 469,              /*   addIpcByNetwork */
    NETDEV_LOG_OPSET_IPC_MOD_IP                 = 470,              /*   modifyIpcAddr */

    /*   Configurations */
    NETDEV_LOG_OPSET_DEV_BAS_CFG                = 500,              /*   Basic device information */
    NETDEV_LOG_OPSET_TIME_CFG                   = 501,              /*   Device time */
    NETDEV_LOG_OPSET_SERIAL_CFG                 = 502,              /*   Device serial port */
    NETDEV_LOG_OPSET_CHL_BAS_CFG                = 503,              /*   Basic channel configuration */
    NETDEV_LOG_OPSET_CHL_NAME_CFG               = 504,              /*   Channel name configuration */
    NETDEV_LOG_OPSET_CHL_ENC_VIDEO              = 505,              /*   Video encoding configuration */
    NETDEV_LOG_OPSET_CHL_DIS_VIDEO              = 506,              /*   Video display configuration */
    NETDEV_LOG_OPSET_PTZ_CFG                    = 507,              /*   PTZ configuration */
    NETDEV_LOG_OPSET_CRUISE_CFG                 = 508,              /*   Patrol route configuration */
    NETDEV_LOG_OPSET_PRESET_CFG                 = 509,              /*   Preset configuration */
    NETDEV_LOG_OPSET_VIDPLAN_CFG                = 510,              /*   Recording schedule configuration */
    NETDEV_LOG_OPSET_MOTION_CFG                 = 511,              /*   Motion detection configuration */
    NETDEV_LOG_OPSET_VIDLOSS_CFG                = 512,              /*   Video loss configuration */
    NETDEV_LOG_OPSET_COVER_CFG                  = 513,              /*   Tampering detection configuration */
    NETDEV_LOG_OPSET_MASK_CFG                   = 514,              /*   Privacy mask configuration */
    NETDEV_LOG_OPSET_SCREEN_OSD_CFG             = 515,              /*   OSD overlay configuration */
    NETDEV_LOG_OPSET_ALARMIN_CFG                = 516,              /*   Alarm input configuration */
    NETDEV_LOG_OPSET_ALARMOUT_CFG               = 517,              /*   Alarm output configuration */
    NETDEV_LOG_OPSET_ALARMOUT_OPEN_MAN          = 518,              /*   Manually enable alarm output, GUI */
    NETDEV_LOG_OPSET_ALARMOUT_CLOSE_MAN         = 519,              /*   Manually disable alarm input, GUI */
    NETDEV_LOG_OPSET_ABNORMAL_CFG               = 520,              /*   Exception configuration */
    NETDEV_LOG_OPSET_HDD_CFG                    = 521,              /*   HDD configuration */
    NETDEV_LOG_OPSET_NET_IP_CFG                 = 522 ,             /*   TCP/IP configuration */
    NETDEV_LOG_OPSET_NET_PPPOE_CFG              = 523,              /*   PPPOE configuration */
    NETDEV_LOG_OPSET_NET_PORT_CFG               = 524,              /*   Port configuration */
    NETDEV_LOG_OPSET_NET_DDNS_CFG               = 525,              /*   DDNS configuration */
    NETDEV_LOG_OPSET_AUDIO_DETECT               = 527,              /*   searchExtendDisk */
    NETDEV_LOG_OPSET_SEARCH_EX_DISK             = 528,              /*   searchExtendDisk */
    NETDEV_LOG_OPSET_ADD_EX_DISK                = 529 ,             /*   addExtendDisk */
    NETDEV_LOG_OPSET_DEL_EX_DISK                = 530,              /*   deleteExtendDisk */
    NETDEV_LOG_OPSET_SET_EX_DISK                = 531,              /*   setExtendDisk */
    NETDEV_LOG_OPSET_LIVE_BY_MULTICAST          = 532,              /*   liveViewByMulticast */
    NETDEV_LOG_OPSET_BISC_DEV_INFO              = 533,              /*   setBasicDeviceInfo */
    NETDEV_LOG_OPSET_PREVIEW_CFG                = 534,              /*   SetPreviewOnNvr */
    NETDEV_LOG_OPSET_SET_EMAIL                  = 535,              /*   setEmail */
    NETDEV_LOG_OPSET_TEST_EMAIL                 = 536,              /*   testEmail */
    NETDEV_LOG_OPSET_SET_IPCONTROL              = 537,              /*   setIPControl */
    NETDEV_LOG_OPSET_PORT_MAP                   = 538 ,             /*   setPortMap */
    NETDEV_LOG_OPSET_ADD_TAG                    = 539,              /*   addTag */
    NETDEV_LOG_OPSET_DEL_TAG                    = 540,              /*   deleteTag */
    NETDEV_LOG_OPSET_MOD_TAG                    = 541,              /*   modifyTag */
    NETDEV_LOG_OPSET_LOCK_RECORD                = 542,              /*   lockRecord */
    NETDEV_LOG_OPSET_UNLOCK_RECORD              = 543,              /*   unlockRecord */
    NETDEV_LOG_OPSET_DDNS_UPDATE_SUCCESS        = 545,              /*   DDNSUpdateSuccess */
    NETDEV_LOG_OPSET_DDNS_INCORRECT_ID          = 546,              /*   DDNSUpdateFailedIncorrectUsernamePassword */
    NETDEV_LOG_OPSET_DDNS_DOMAIN_NAME_NOT_EXIST = 547,              /*   DDNSUpdateFailedDomainNameNotExist */
    NETDEV_LOG_OPSET_DDNS_UPDATE_FAIL           = 548,              /*   DDNSUpdateFailed */
    NETDEV_LOG_OPSET_HTTP_CFG                   = 549,              /*   setHttps */
    NETDEV_LOG_OPSET_IP_OFFLINE_ALARM_CFG       = 550,              /*   testDDNSDomain */
    NETDEV_LOG_OPSET_TELNET_CFG                 = 551,              /*   setTelnet */
    NETDEV_LOG_OPSET_TEST_DDNS_DOMAIN           = 552,              /*   testDDNSDomain */
    NETDEV_LOG_OPSET_DDNS_DOMAIN_CONFLICT       = 553,              /*   DDNSDomainInvalid */
    NETDEV_LOG_OPSET_DDNS_DOMAIN_INVALID        = 554,              /*   setDDNS */
    NETDEV_LOG_OPSET_DEL_PRESET                 = 555,              /*   deletePreset */
    NETDEV_LOG_OPSET_PTZ_3D_POSITION            = 556,              /*   ptz3DPosition */
    NETDEV_LOG_OPSET_SNAPSHOT_SCHEDULE_CFG      = 557,             /*   setSnapshotSchedule */
    NETDEV_LOG_OPSET_IMAGE_UPLOAD_SCHEDULE_CFG  = 558,              /*   setImageUploadSchedule */
    NETDEV_LOG_OPSET_FTP_CFG                    = 559,              /*   setFtpServer */
    NETDEV_LOG_OPSET_TEST_FTP_SERVER            = 560,              /*   testFtpServer */
    NETDEV_LOG_OPSET_START_MANUAL_SNAPSHOT      = 561,              /*   startManualSnapshot */
    NETDEV_LOG_OPSET_CLOSE_MANUAL_SNAPSHOT      = 562,              /*   endManualSnapshot */
    NETDEV_LOG_OPSET_SNAPSHOT_CFG               = 563,              /*   setSnapshot */
    NETDEV_LOG_OPSET_ADD_HOLIDAY                = 564 ,             /*   addHoliday */
    NETDEV_LOG_OPSET_DEL_HOLIDAY                = 565,              /*   deleteHoliday */
    NETDEV_LOG_OPSET_MOD_HOLIDAY                = 566,              /*   modifyHoliday */
    NETDEV_LOG_OPSET_ONOFF_HOLIDAY              = 567,              /*   enableDisableHoliday */
    NETDEV_LOG_OPSET_ALLOCATE_SPACE             = 568,              /*   allocateSpace */
    NETDEV_LOG_OPSET_HDD_FULL_POLICY_CFG        = 569,              /*   setHddFullPolicy */
    NETDEV_LOG_OPSET_AUDIO_STREAM_CFG           = 570,              /*   setAudioStream */
    NETDEV_LOG_OPSET_ARRAY_PROPERTY_CFG         = 571,              /*   setArrayProperty */
    NETDEV_LOG_OPSET_HOT_SPACE_DISK_CFG         = 572,              /*   setHotSpaceDisk */
    NETDEV_LOG_OPSET_CREAT_ARRAY                = 573,              /*   createArray */
    NETDEV_LOG_OPSET_ONE_CLICK_CREAT_ARRAY      = 574,              /*   oneClickCreateArray */
    NETDEV_LOG_OPSET_REBUILD_ARRAY              = 575,              /*   rebuildArray */
    NETDEV_LOG_OPSET_DEL_ARRAY                  = 576,              /*   deleteArray */
    NETDEV_LOG_OPSET_ENABLE_RAID                = 577,              /*   enableRaid */
    NETDEV_LOG_OPSET_DISABLE_RAID               = 578,              /*   disableRaid */
    NETDEV_LOG_OPSET_TEST_SMART                 = 579,              /*  testSmart */
    NETDEV_LOG_OPSET_SMART_CFG                  = 580,              /*   setSmart */
    NETDEV_LOG_OPSET_BAD_SECTOR_DETECT          = 581,              /*   badSectorDetect */
    NETDEV_LOG_OPSET_AUDIO_ALARM_DURATION       = 582,              /*   setAudioAlarmDuration */
    NETDEV_LOG_OPSET_CLR_AUDIO_ALARM            = 583,             /*   clearAudioAlarm */
    NETDEV_LOG_OPSET_IPC_TIME_SYNC_CFG          = 584,              /*   setIpcTimeSync */
    NETDEV_LOG_OPSET_ENABLE_DISK_GROUP          = 585,              /*   enableDiskGroup */
    NETDEV_LOG_OPSET_DISABLE_DISK_GRRUOP        = 586,              /*   disableDiskGroup */
    NETDEV_LOG_OPSET_ONVIF_AUTH_CFG             = 587,              /*   setOnvifAuth */
    NETDEV_LOG_OPSET_8021X_CFG                  = 588,              /*   set8021x */
    NETDEV_LOG_OPSET_ARP_PROTECTION_CFG         = 589,              /*   setArpProtection */
    NETDEV_LOG_OPSET_SMART_BASIC_INFO_CFG       = 590 ,             /*   setSmartBasicInfo */
    NETDEV_LOG_OPSET_CROSS_LINE_DETECT_CFG      = 591,              /*   setCrossLineDetection */
    NETDEV_LOG_OPSET_INSTRUSION_DETECT_CFG      = 592,              /*   setIntrusionDetection */
    NETDEV_LOG_OPSET_PEOPLE_COUNT_CFG           = 593,              /*   setPeopleCount */
    NETDEV_LOG_OPSET_FACE_DETECT_CFG            = 594,              /*   setFaceDetection */
    NETDEV_LOG_OPSET_FISHEYE_CFG                = 595,              /*   setFisheye */
    NETDEV_LOG_OPSET_CUSTOM_PROTOCOL_CFG        = 596,              /*   setCustomProtocol */
    NETDEV_LOG_OPSET_BEHAVIOR_SEARCH            = 597,              /*   behaviorSearch */
    NETDEV_LOG_OPSET_FACE_SEARCH                = 598,              /*   faceSearch */
    NETDEV_LOG_OPSET_PEOPLE_COUNT               = 599,              /*   peopleCount */
        
    /*  Maintenance */
    NETDEV_LOG_OPSET_START_DVR                  = 600,              /*   Start up*/
    NETDEV_LOG_OPSET_STOP_DVR                   = 601,              /*   Shut down */
    NETDEV_LOG_OPSET_REBOOT_DVR                 = 602,              /*   Restart device */
    NETDEV_LOG_OPSET_UPGRADE                    = 603,              /*   Version upgrade */
    NETDEV_LOG_OPSET_LOGFILE_EXPORT             = 604,              /*   Export log files */
    NETDEV_LOG_OPSET_CFGFILE_EXPORT             = 605,              /*   Export configuration files */
    NETDEV_LOG_OPSET_CFGFILE_IMPORT             = 606,              /*   Import configuration files */
    NETDEV_LOG_OPSET_CONF_SIMPLE_INIT           = 607,              /*   Export configuration files */
    NETDEV_LOG_OPSET_CONF_ALL_INIT              = 608,               /*   Restore to factory settings */

    NETDEV_LOG_OPSET_VCA_BACKUP                 = 700,              /*  vcaBackup */
    NETDEV_LOG_OPSET_3G4G_CFG                   = 701,              /*  set3g4g */
    NETDEV_LOG_OPSET_MOUNT_EXTENDED_DISK        = 702,              /*  Mount extended disk*/
    NETDEV_LOG_OPSET_UNMOUNT_EXTENDED_DISK      = 703,              /*  Unmount extended disk*/
    NETDEV_LOG_OPSET_FORCE_USER_OFFLINE         = 704,              /*  Force user off line*/

    NETDEV_LOG_OPSET_AUTO_FUNCTION              = 709,              /*   autoFunction */
    NETDEV_LOG_OPSET_IPC_UPRAGDE                = 710,              /*   ipcUpgrade */
    NETDEV_LOG_OPSET_RESTORE_IPC_DEFAULTS       = 711,              /*   restoreIpcDefaults */
    NETDEV_LOG_OPSET_ADD_TRANSACTION            = 712,              /*   addTransaction */
    NETDEV_LOG_OPSET_MOD_TRANSACTION            = 713,              /*   modifyTransaction */
    NETDEV_LOG_OPSET_DEL_TRANSACTION            = 714,              /*   deleteTransaction */
    NETDEV_LOG_OPSET_POS_OSD                    = 715,              /*   setPosOsd */
    NETDEV_LOG_OPSET_ADD_HOT_SPACE_DEV          = 716,              /*   addHotSpaceDevice */
    NETDEV_LOG_OPSET_DEL_HOT_SPACE_DEV          = 717,              /*   deleteHotSpaceDevice */
    NETDEV_LOG_OPSET_MOD_HOT_SPACE_DEV          = 718,              /*   modifyHotSpaceDevice */
    NETDEV_LOG_OPSET_DEL_WORK_DEV               = 719,              /*   deleteWorkDevice */
    NETDEV_LOG_OPSET_WORKMODE_TO_NORMAL_CFG     = 720,              /*   SetWorkModeToNormal */
    NETDEV_LOG_OPSET_WORKMODE_TO_HOTSPACE_CFG   = 721,              /*   SetWorkModeToHotSpace */
    NETDEV_LOG_OPSET_AUTO_GUARD_CFG             = 723,              /*   setAutoGuard */
    NETDEV_LOG_OPSET_MULTICAST_CFG              = 724,              /*   SetMulticast */
    NETDEV_LOG_OPSET_DEFOCUS_DETECT_CFG         = 725,              /*  Set defocus detection*/
    NETDEV_LOG_OPSET_SCENECHANGE_CFG            = 726,              /*  Set scene change detection*/
    NETDEV_LOG_OPSET_AUTO_TRCAK_CFG             = 727,              /*  Set auto tracking*/
    NETDEV_LOG_OPSET_SORT_CAMERA_CFG            = 728,              /*  Sort camera*/
    NETDEV_LOG_OPSET_WATER_MARK_CFG             = 729              /*  Set watermark*/
}NETDEV_LOG_SUB_TYPE_E;

typedef enum tagNETDEVDeviceType
{
    NETDEV_DTYPE_UNKNOWN                        = 0,            /* Unknown type */
    NETDEV_DTYPE_IPC                            = 1,            /* IPC range */
    NETDEV_DTYPE_IPC_FISHEYE                    = 2,            /* Certain fisheye camera models*/
    NETDEV_DTYPE_IPC_ECONOMIC_FISHEYE           = 3,            /* Certain fisheye camera models*/
    NETDEV_DTYPE_NVR                            = 101,          /* NVR range */
    NETDEV_DTYPE_NVR_BACKUP                     = 102,          /* NVR back up */
    NETDEV_DTYPE_HNVR                           = 103,          /* mix NVR */
    NETDEV_DTYPE_DC                             = 201,          /* DC range */
    NETDEV_DTYPE_DC_ADU                         = 202,          /* ADU range */
    NETDEV_DTYPE_EC                             = 301,          /* EC range */
    NETDEV_DTYPE_VMS                            = 501,          /* VMS range */

    NETDEV_DTYPE_INVALID                        = 0xFFFF        /* Invalid value */
}NETDEV_DEVICETYPE_E;

/**
 * @enum tagNETDEVCfgCmd
 * @brief  Parameter configuration command words Enumeration definition
 * @attention  None
 */
typedef enum tagNETDEVCfgCmd
{
    NETDEV_GET_DEVICECFG                = 100,              /*  Get device information, see #NETDEV_DEVICE_BASICINFO_S */
    NETDEV_SET_DEVICECFG                = 101,              /*  Reserved */

    NETDEV_GET_NTPCFG                   = 110,              /*  Get NTP parameter, see #NETDEV_SYSTEM_NTP_INFO_S */
    NETDEV_SET_NTPCFG                   = 111,              /*  Set NTP parameter, see #NETDEV_SYSTEM_NTP_INFO_S */
    NETDEV_GET_NTPCFG_EX                = 112,              /* Get NTP parameter, see #NETDEV_SYSTEM_NTP_INFO_LIST_S */
    NETDEV_SET_NTPCFG_EX                = 113,              /* Set NTP parameter, see #NETDEV_SYSTEM_NTP_INFO_LIST_S */

    NETDEV_GET_STREAMCFG                = 120,              /*  Get video encoding parameter, see #NETDEV_VIDEO_STREAM_INFO_S */
    NETDEV_SET_STREAMCFG                = 121,              /*  Set video encoding parameter, see #NETDEV_VIDEO_STREAM_INFO_S */

    NETDEV_GET_STREAMCFG_EX             = 122,              /*  Get video encoding parameter, see #NETDEV_VIDEO_STREAM_INFO_LIST_S */
    NETDEV_SET_STREAMCFG_EX             = 123,              /*  Set video encoding parameter, see #NETDEV_VIDEO_STREAM_INFO_LIST_S */

    NETDEV_GET_VIDEOMODECFG             = 124,              /*  Get Image acquisition system£¬see#NETDEV_VIDEO_MODE_INFO_S */
    NETDEV_SET_VIDEOMODECFG             = 125,              /*  Set Image acquisition system£¬see#NETDEV_VIDEO_MODE_INFO_S */

    NETDEV_GET_PTZPRESETS               = 130,              /*  Get PTZ preset, see #NETDEV_PTZ_ALLPRESETS_S */

    NETDEV_GET_OSDCFG                   = 140,              /*  Get OSD configuration information, see #NETDEV_VIDEO_OSD_CFG_S */
    NETDEV_SET_OSDCFG                   = 141,              /*  Set OSD configuration information, see #NETDEV_VIDEO_OSD_CFG_S */

    NETDEV_GET_OSD_CONTENT_CFG          = 144,              /*  Get OSD configuration information, see #NETDEV_OSD_CONTENT_S */
    NETDEV_SET_OSD_CONTENT_CFG          = 145,              /*  Set OSD configuration information, see #NETDEV_OSD_CONTENT_S */
    NETDEV_GET_OSD_CONTENT_STYLE_CFG    = 146,              /*  Get OSD content style, see #NETDEV_OSD_CONTENT_STYLE_S */
    NETDEV_SET_OSD_CONTENT_STYLE_CFG    = 147,              /*  Set OSD content style, see #NETDEV_OSD_CONTENT_STYLE_S */

    NETDEV_GET_ALARM_OUTPUTCFG          = 150,              /* Get boolean configuration information, see #NETDEV_ALARM_OUTPUT_LIST_S */
    NETDEV_SET_ALARM_OUTPUTCFG          = 151,              /* Set boolean configuration information, see #NETDEV_ALARM_OUTPUT_LIST_S */
    NETDEV_TRIGGER_ALARM_OUTPUT         = 152,              /* Trigger boolean, see #NETDEV_TRIGGER_ALARM_OUTPUT_S */
    NETDEV_GET_ALARM_INPUTCFG           = 153,              /* Get the number of boolean inputs, see #NETDEV_ALARM_INPUT_LIST_S */
    NETDEV_GET_MANUAL_ALARM_CFG         = 154,              /* Get manual alarm boolean configuration information, see #NETDEV_OUTPUT_SWITCH_ALARM_STATUS_LIST_S*/
    NETDEV_SET_MANUAL_ALARM_CFG         = 155,              /* Set manual alarm boolean configuration information, see #NETDEV_OUTPUT_SWITCH_MANUAL_ALARM_INFO_S */

    NETDEV_GET_IMAGECFG                 = 160,              /* Get image configuration information, see #NETDEV_IMAGE_SETTING_S */
    NETDEV_SET_IMAGECFG                 = 161,              /* Set image configuration information, see #NETDEV_IMAGE_SETTING_S */

    NETDEV_GET_NETWORKCFG               = 170,              /* Get network configuration information, see #NETDEV_NETWORKCFG_S */
    NETDEV_SET_NETWORKCFG               = 171,              /* Set network configuration information, see #NETDEV_NETWORKCFG_S */

    NETDEV_GET_PRIVACYMASKCFG           = 180,              /* Get privacy mask configuration information, see #NETDEV_PRIVACY_MASK_CFG_S */
    NETDEV_SET_PRIVACYMASKCFG           = 181,              /* Set privacy mask configuration information, see #NETDEV_PRIVACY_MASK_CFG_S */
    NETDEV_DELETE_PRIVACYMASKCFG        = 182,              /* Delete privacy mask configuration information */

    NETDEV_GET_TAMPERALARM              = 190,              /* Get tamper alarm configuration information, see #NETDEV_TAMPER_ALARM_INFO_S */
    NETDEV_SET_TAMPERALARM              = 191,              /* Set tamper alarm configuration information, see #NETDEV_TAMPER_ALARM_INFO_S */

    NETDEV_GET_MOTIONALARM              = 200,              /* Get motion alarm configuration information, see #NETDEV_MOTION_ALARM_INFO_S */
    NETDEV_SET_MOTIONALARM              = 201,              /* Set motion alarm configuration information, see #NETDEV_MOTION_ALARM_INFO_S */

    NETDEV_GET_CROSSLINEALARM           = 202,              /* Get Cross Line alarm configuration information, see #NETDEV_CROSS_LINE_ALARM_INFO_S*/
    NETDEV_SET_CROSSLINEALARM           = 203,              /* Set Cross Line alarm configuration information, see #NETDEV_CROSS_LINE_ALARM_INFO_S*/

    NETDEV_GET_INTRUSIONALARM           = 204,              /* Get intrusion alarm configuration information, see #NETDEV_INTRUSION_ALARM_INFO_S*/
    NETDEV_SET_INTRUSIONALARM           = 205,              /* Set intrusion alarm configuration information, see #NETDEV_INTRUSION_ALARM_INFO_S*/

    NETDEV_GET_DISKSINFO                = 210,              /* Get disks information, see #NETDEV_GET_DISKS_INFO_S */

    NETDEV_GET_PTZSTATUS                = 220,              /* Get PTZ status,  see #NETDEV_PTZ_STATUS_S  */

    NETDEV_GET_FOCUSINFO                = 230,              /* Get focus info, see #NETDEV_FOCUS_INFO_S */
    NETDEV_SET_FOCUSINFO                = 231,              /* Set focus info, see #NETDEV_FOCUS_INFO_S */

    NETDEV_GET_IRCUTFILTERINFO          = 240,              /* Get IRcut filter info, see #NETDEV_IRCUT_FILTER_INFO_S */
    NETDEV_SET_IRCUTFILTERINFO          = 241,              /* Set IRcut filter info, see #NETDEV_IRCUT_FILTER_INFO_S */

    NETDEV_GET_DEFOGGINGINFO            = 250,              /* Get defogging info, see #NETDEV_DEFOGGING_INFO_S */
    NETDEV_SET_DEFOGGINGINFO            = 251,              /* Set defogging info, see #NETDEV_DEFOGGING_INFO_S */
    
    NETDEV_GET_RECORDPLANINFO           = 252,              /* Getting up video plan configuration information see#NETDEV_RECORD_PLAN_CFG_INFO_S */
    NETDEV_SET_RECORDPLANINFO           = 253,              /* Setting up video plan configuration information see#NETDEV_RECORD_PLAN_CFG_INFO_S */

    NETDEV_GET_DST_CFG                  = 260,             /* Get defogging info, see #NETDEV_DST_CFG_S */
    NETDEV_SET_DST_CFG                  = 261,              /* Set defogging info, see #NETDEV_DST_CFG_S */

    NETDEV_GET_AUDIOIN_CFG              = 262,              /* get audio input config info see #NETDEV_AUDIO_INPUT_CFG_INFO_S */
    NETDEV_SET_AUDIOIN_CFG              = 263,              /* set audio input config info see #NETDEV_AUDIO_INPUT_CFG_INFO_S */

    NETDEV_SET_DNS_CFG                 = 270,              /*Set DNS info see #NETDEV_DNS_INFO_S*/
    NETDEV_GET_DNS_CFG                 = 271,              /*Get DNS info see #NETDEV_DNS_INFO_S*/

    NETDEV_SET_NETWORK_CARDS            = 272,              /* set device networkcards infos see #NETDEV_NETWORK_CARD_INFO_S*/
    NETDEV_GET_NETWORK_CARDS            = 273,              /*get device networkcards infos see #NETDEV_NETWORK_CARD_INFO_S*/

    

    NETDEV_CFG_INVALID                  = 0xFFFF            /* 无效�? Invalid value */

}NETDEV_CONFIG_COMMAND_E;


/**
 * @enum tagNETDEVDateOSDFormateCap
 * @brief  OSD date format capabilities enumeration 
 * @attention  None
 */
typedef enum tagNETDEVDateOSDFormateCap
{
    NETDEV_OSD_DATE_FORMAT_CAP_MD_YYYY          = 0,        /* M/d/yyyy */
    NETDEV_OSD_DATE_FORMAT_CAP_MMDD_YYYY        = 1,        /* MM/dd/yyyy */
    NETDEV_OSD_DATE_FORMAT_CAP_DDMM_YYYY        = 2,        /* dd/MM/yyyy */
    NETDEV_OSD_DATE_FORMAT_CAP_YYYY_MMDD        = 3,        /* yyyy/MM/dd */
    NETDEV_OSD_DATE_FORMAT_CAP_YYYYMMDDB        = 4,        /* yyyy-MM-dd */
    NETDEV_OSD_DATE_FORMAT_CAP_XX_MMDD_YYYY     = 5,        /* dddd, MMMM dd, yyyy */
    NETDEV_OSD_DATE_FORMAT_CAP_MMMMDD_YYYY      = 6,        /* MMMM dd, yyyy */
    NETDEV_OSD_DATE_FORMAT_CAP_DDMMMM_YYYY      = 7         /* dd MMMM, yyyy */
}NETDEV_OSD_DATE_FORMAT_CAP_E;

/**
 * @enum tagNETDEVTimeOSDFormateCap
 * @brief  OSD time format capabilities enumeration
 * @attention  None
 */
typedef enum tagNETDEVTimeOSDFormateCap
{
    NETDEV_OSD_TIME_FORMAT_CAP_HHMMSS = 0,                  /* HH:mm:ss */
    NETDEV_OSD_TIME_FORMAT_CAP_HH_MM_SS_PM                  /* hh:mm:ss tt */
}NETDEV_OSD_TIME_FORMAT_CAP_E;

/**
 * @enum tagNETDEVBooleanMode
 * @brief  Boolean input operation mode
 * @attention  None
 */
typedef enum tagNETDEVBooleanMode
{
    NETDEV_BOOLEAN_MODE_OPEN   = 1,                         /*   Always open */
    NETDEV_BOOLEAN_MODE_CLOSE  = 2,                         /*   Always closed */
    NETDEV_BOOLEAN_MODE_INVALID
}NETDEV_BOOLEAN_MODE_E;

/**
 * @enum tagNETDEVTimeOSDFormateCap
 * @brief  Boolean input operation mode
 * @attention  None
 */
typedef enum tagNETDEVRelayOutPutState
{
    NETDEV_BOOLEAN_STATUS_ACTIVE    = 0,                /*  Triggered */
    NETDEV_BOOLEAN_STATUS_INACTIVE  = 1                 /*  Not triggered */
}NETDEV_RELAYOUTPUT_STATE_E;

/**
 * @enum tagNETDEVOutPutManualAlarmCmd
 * @brief Control manual alarm switch quantity status command
 * @attention  None
 */
typedef enum tagNETDEVOutPutManualAlarmCmd
{
    NETDEV_MANUAL_ALARM_CMD_CLOSE    = 0,                /*  close */
    NETDEV_MANUAL_ALARM_CMD_TRIGGER  = 1                 /*   Triggered */
}NETDEV_MANUAL_ALARM_CMD_E;

/**
* @enum tagNETDEVMediaDataFormat
* @brief Media data stream format
* @attention none
*/
typedef enum tagNETDEVMediaDataFormat
{
    NETDEV_MEDIA_DATA_TS            = 0,            /* TS */
    NETDEV_MEDIA_DATA_RTP_ES        = 3             /* RTP + ES */
}NETDEV_MEDIA_DATA_FORMAT_E;

/**
* @enum tagNETDEVProtocolType
* @brief protocol type 
* @attention none
*/
typedef enum tagNETDEVProtocolType
{
    NETDEV_PROTOCOL_TYPE_HTTP  = 0,
    NETDEV_PROTOCOL_TYPE_HTTPS = 1,
    NETDEV_PROTOCOL_TYPE_RTSP  = 2
}NETDEV_PROTOCOL_TYPE_E;

/**
* @enum tagNETDEVTTimeZone
* @brief  Time Zone
* @attention  None
*/
typedef enum tagNETDEVTimeZone
{
    NETDEV_TIME_ZONE_W1200 = 0,              /* W12 */
    NETDEV_TIME_ZONE_W1100 = 1,              /* W11 */
    NETDEV_TIME_ZONE_W1000 = 2,              /* W10 */
    NETDEV_TIME_ZONE_W0900 = 3,              /* W9 */
    NETDEV_TIME_ZONE_W0800 = 4,              /* W8 */
    NETDEV_TIME_ZONE_W0700 = 5,              /* W7 */
    NETDEV_TIME_ZONE_W0600 = 6,              /* W6 */
    NETDEV_TIME_ZONE_W0500 = 7,              /* W5 */
    NETDEV_TIME_ZONE_W0430 = 8,              /* W4:30 */
    NETDEV_TIME_ZONE_W0400 = 9,              /* W4 */
    NETDEV_TIME_ZONE_W0330 = 10,             /* W3:30 */
    NETDEV_TIME_ZONE_W0300 = 11,             /* W3 */
    NETDEV_TIME_ZONE_W0200 = 12,             /* W2 */
    NETDEV_TIME_ZONE_W0100 = 13,             /* W1 */
    NETDEV_TIME_ZONE_0000  = 14,             /* W0 */
    NETDEV_TIME_ZONE_E0100 = 15,             /* E1 */
    NETDEV_TIME_ZONE_E0200 = 16,             /* E2 */
    NETDEV_TIME_ZONE_E0300 = 17,             /* E3 */
    NETDEV_TIME_ZONE_E0330 = 18,             /* E3:30 */
    NETDEV_TIME_ZONE_E0400 = 19,             /* E4 */
    NETDEV_TIME_ZONE_E0430 = 20,             /* E4:30 */
    NETDEV_TIME_ZONE_E0500 = 21,             /* E5 */
    NETDEV_TIME_ZONE_E0530 = 22,             /* E5:30 */
    NETDEV_TIME_ZONE_E0545 = 23,             /* E5:45 */
    NETDEV_TIME_ZONE_E0600 = 24,             /* E6 */
    NETDEV_TIME_ZONE_E0630 = 25,             /* E6:30 */
    NETDEV_TIME_ZONE_E0700 = 26,             /* E7 */
    NETDEV_TIME_ZONE_E0800 = 27,             /* E8 */
    NETDEV_TIME_ZONE_E0900 = 28,             /* E9 */
    NETDEV_TIME_ZONE_E0930 = 29,             /* E9:30 */
    NETDEV_TIME_ZONE_E1000 = 30,             /* E10 */
    NETDEV_TIME_ZONE_E1100 = 31,             /* E11 */
    NETDEV_TIME_ZONE_E1200 = 32,             /* E12 */
    NETDEV_TIME_ZONE_E1300 = 33,             /* E13 */
    NETDEV_TIME_ZONE_W0930 = 34,              /* W9:30 */
    NETDEV_TIME_ZONE_E0830 = 35,             /* E8:30 */
    NETDEV_TIME_ZONE_E0845 = 36,             /* E8:45 */
    NETDEV_TIME_ZONE_E1030 = 37,             /* E10:30 */
    NETDEV_TIME_ZONE_E1245 = 38,             /* E12:45 */
    NETDEV_TIME_ZONE_E1400 = 39,             /* E14 */

    NETDEV_TIME_ZONE_INVALID = 0xFF          /* Invalid value */
}NETDEV_TIME_ZONE_E;

/**
* @enum  tagNetDEVDayInWeek
* @brief Week emnu
* @attention none
*/
typedef enum tagNetDEVDayInWeek
{
    NETDEV_WEEK_SUNDAY                  = 0,                  /*   Sunday */
    NETDEV_WEEK_MONDAY                  = 1,                  /*   Monday */
    NETDEV_WEEK_TUESDAY                 = 2,                  /*   Tuesday */
    NETDEV_WEEK_WEDNESDAY               = 3,                  /*   Wednesday */
    NETDEV_WEEK_THURSDAY                = 4,                  /*   Thursday */
    NETDEV_WEEK_FRIDAY                  = 5,                  /*   Friday */
    NETDEV_WEEK_SATURDAY                = 6,                  /*   Saturday */
    NETDEV_WEEK_INVALID               = 0xff                  /*   Invalid value */
}NETDEV_DAY_IN_WEEK_E;

/**
* @enum  tagNetDEVDSTOffsetTime
* @brief  DST offset time
* @attention none
*/
typedef enum tagNetDEVDSTOffsetTime
{
    NETDEV_DST_OFFSET_TIME_30MIN                 = 30,          /*   30Minutes */
    NETDEV_DST_OFFSET_TIME_60MIN                 = 60,          /*   60Minutes */
    NETDEV_DST_OFFSET_TIME_90MIN                 = 90,          /*   90Minutes */
    NETDEV_DST_OFFSET_TIME_120MIN                = 120,         /*   120Minutes */
    NETDEV_DST_OFFSET_TIME_INVALID               = 0xff         /*  Invalid value */
}NETDEV_DST_OFFSET_TIME;



/**
 * @enum tagNETDEVDiskWorkStatus
 * @brief  Disk work status 
 * @attention None
 */
typedef enum tagNETDEVDiskWorkStatus
{
    NETDEV_DISK_WORK_STATUS_EMPTY       = 0,            /*  Empty */
    NETDEV_DISK_WORK_STATUS_UNFORMAT    = 1,            /*  Unformat */
    NETDEV_DISK_WORK_STATUS_FORMATING   = 2,            /*  Formating */
    NETDEV_DISK_WORK_STATUS_RUNNING     = 3,            /*  Running */
    NETDEV_DISK_WORK_STATUS_HIBERNATE   = 4,            /*  Hibernate */
    NETDEV_DISK_WORK_STATUS_ABNORMAL    = 5,            /*  Abnormal */
    NETDEV_DISK_WORK_STATUS_UNKNOWN     = 6,            /*  Unknown */

    NETDEV_DISK_WORK_STATUS_INVALID                     /*  Invalid value */
}NETDEV_DISK_WORK_STATUS_E;


/**
* @enum tagPictureFluency
* @brief  Picture fluency
* @attention none
*/
typedef enum tagNetDEVPictureFluency
{
    NETDEV_PICTURE_REAL                 = 0,                /*  Real-time first */
    NETDEV_PICTURE_FLUENCY              = 1,                /*  Fluency first */
    NETDEV_PICTURE_BALANCE_NEW          = 3,                /*  Balance */
    NETDEV_PICTURE_RTMP_FLUENCY         = 4,                /*  RTMP fluency first */

    NETDEV_PICTURE_FLUENCY_INVALID      = 0xff              /*  Invalid value */
}NETDEV_PICTURE_FLUENCY_E;

/**
* @enum tagNETDEVPtzHomePositionCmd
* @brief   PTZ home position operation commands Enumeration Definition
* @attention  None
*/
typedef enum tagNETDEVPtzHomePositionCmd
{
    NETDEV_PTZ_SET_HOMEPOSITION   = 0,            /*   Set home position */
    NETDEV_PTZ_GOTO_HOMEPOSITION  = 1             /*   Go to home position */
}NETDEV_PTZ_HOMEPOSITIONCMD_E;

/**
* @enum tagNETDEVPTZMoveStatus
* @brief  PTZ Move status
* @attention  None
*/
typedef enum tagNETDEVPTZMoveStatus
{
    NETDEV_PTZ_MOVE_STATUS_IDLE     = 0,             /*  Free */
    NETDEV_PTZ_MOVE_STATUS_MOVING   = 1,             /*  Moving */

    NETDEV_PTZ_MOVE_STATUS_INVALID  = 0xff           /*  Invalid value */
}NETDEV_PTZ_MOVE_STATUS_E;

/**
 * @enum tagNETDEVIrCutFilterMode
 * @brief  IRCut filter mode
 * @attention  None
 */
typedef enum  tagNETDEVIrCutFilterMode
{
    NETDEV_IR_CUT_FILTER_ON     = 0,            /*  On */
    NETDEV_IR_CUT_FILTER_OFF    = 1,            /*  Off */
    NETDEV_IR_CUT_FILTER_AUTO   = 2             /*  Auto */
}NETDEV_IR_CUT_FILTER_MODE_E;

/**
 * @enum tagNETDEVDefoggingMode
 * @brief  Defogging mode
 * @attention  None
 */
typedef enum  tagNETDEVDefoggingMode
{
    NETDEV_DEFOGGING_ON = 0,            /*  On */
    NETDEV_DEFOGGING_OFF                /*  Off */
}NETDEV_DEFOGGING_MODE_E;

/**
 * @enum tagNETDEVFocusMode
 * @brief  Focus mode
 * @attention  None
 */
typedef enum tagNETDEVFocusMode
{
    NETDEV_FOCUS_AUTO           = 1,            /*  Auto */
    NETDEV_FOCUS_MANUAL         = 2             /*  Manual */
}NETDEV_FOCUS_MODE_E;

/**
 * @enum tagNETDEVFocusNearlimit
 * @brief  Focus near limit
 * @attention  None
 */
typedef enum tagNETDEVFocusNearlimit
{
    NETDEV_FOCUS_NEARLIMIT_10       = 1,            /* 10cm */
    NETDEV_FOCUS_NEARLIMIT_100      = 2,            /* 100cm */
    NETDEV_FOCUS_NEARLIMIT_300      = 3,            /* 300cm */
    NETDEV_FOCUS_NEARLIMIT_1000     = 4,            /* 1000cm */

    NETDEV_FOCUS_NEARLIMI_INVALID   = 0xff          /*   Invalid value */
}NETDEV_FOCUS_NEARLIMIT_E;

/**
* @enum tagNETDEVRecordType
* @brief  Record Type
* @attention 
*/
typedef enum tagNETDEVRecordType
{
    NETDEV_RECORD_TYPE_MANUAL  = 0,
    NETDEV_RECORD_TYPE_NORMAL = 1
}NETDEV_RECORD_TYPE_E;


/**
 * @enum tagNETDEVVideoPosition
 * @brief  Video Position
 * @attention  None
 */
typedef enum tagNETDEVVideoPosition
{
    NETDEV_POSITION_LOCAL       = 1,
    NETDEV_POSITION_CHANNEL     = 2,
    NETDEV_POSITION_INVALID
}NETDEV_VIDEO_POSITION_E;

/**
 * @enum tagNETDEVVideoStatus
 * @brief  Video Status
 * @attention  None
 */
typedef enum tagNETDEVVideoStatus
{
    NETDEV_VIDEO_NONE       = 0,        /*  No video */
    NETDEV_VIDEO_EVENT      = 1,        /*  Event video */
    NETDEV_VIDEO_NORMAL     = 2,        /*  Normal video */
    NETDEV_VIDEO_INVALID
}NETDEV_VIDEO_STATUS_E;


/**
* @enum tagNETDEVCapabilityCommond
* @brief  Device capability commond
* @attention noen
*/
typedef enum tagNETDEVCapabilityCommond
{
    NETDEV_CAP_VIDEO_ENCODE         = 1,            /* Video encoding capability. See # NETDEV_VIDEO_STREAM_CAP_S for reference*/
    NETDEV_CAP_OSD                  = 2,            /* OSD parameter capability. See # NETDEV_OSD_CAP_S for reference*/
    NETDEV_CAP_SMART                = 3,            /* see # NETDEV_SMART_CAP_S for reference */
    NETDEV_CAP_VIDEO_ENCODE_EX      = 4,            /* Video encoding capability. See # NETDEV_VIDEO_STREAM_CAP_EX_S for reference */

    NETDEV_CAP_INVALID              = 0Xff
}NETDEV_CAPABILITY_COMMOND_E;

/**
* @enum tagNETDEVVideoEncodeType
* @brief Coding format type
* @attention none
*/
typedef enum tagNETDEVVideoEncodeType
{
    NETDEV_VIDEO_ENCODE_H264    = 1,
    NETDEV_VIDEO_ENCODE_MPEG4   = 2,
    NETDEV_VIDEO_ENCODE_JPEG    = 3,

    NETDEV_VIDEO_ENCODE_INVALID = 0XFF
}NETDEV_ENCODE_TYPE_E;



/**
* @enum tagNETDEVTrafficStatisticsType
* @brief Type of passenger flow statistical model 
* @attention  None
*/
typedef enum tagNETDEVTrafficStatisticsType
{
    NETDEV_TRAFFIC_STATISTICS_TYPE_IN   = 0,        /*  Statistics type : Enter */
    NETDEV_TRAFFIC_STATISTICS_TYPE_OUT  = 1,        /*  Statistics type : Exit */
    NETDEV_TRAFFIC_STATISTICS_TYPE_ALL  = 2,        /*  Statistics type : All */
    NETDEV_TRAFFIC_STATISTICS_TYPE_BUTT
}NETDEV_TRAFFIC_STATISTICS_TYPE_E;

/**
* @enum tagNETDEVPeoplecntType
* @brief Type of report form of passenger flow statistics
* @attention  None
*/
typedef enum tagNETDEVFormType
{
    NETDEV_FORM_TYPE_DAY    = 0,            /*  Form type : Day */
    NETDEV_FORM_TYPE_WEEK   = 1,            /*  Form type : Week */
    NETDEV_FORM_TYPE_MONTH  = 2,            /*  Form type : Month */
    NETDEV_FORM_TYPE_YEAR   = 3,            /*  Form type : Year */
    NETDEV_FORM_TYPE_BUTT
}NETDEV_FORM_TYPE_E;

/**
* @enum tagNETDEVAddrType
* @brief address type 
* @attention  None
*/
typedef enum tagNETDEVAddrType
{
    NETDEV_ADDR_TYPE_IPV4       = 0,             /* IPV4 */
    NETDEV_ADDR_TYPE_IPV6       = 1,             /* IPV6 */
    NETDEV_ADDR_TYPE_DOMAIN     = 2,             /* domain name */
    NETDEV_ADDR_TYPE_IPV4_IPV6  = 3,             /* Both IPV4 and IPV6 require */
    NETDEV_ADDR_TYPE_INVALID    = 0XFFFF         /* Invalid value */
}NETDEV_ADDR_TYPE_E;

/**
* @enum tagNETDEVSmartEncodeMode
* @brief   Enumeration of smart image encoding mode
* @attention  None
*/
typedef enum tagNETDEVSmartEncodeMode
{
    NETDEV_SMART_ENCODE_MODE_OFF      = 0,      /* Off*/
    NETDEV_SMART_ENCODE_MODE_BASIC    = 1,      /*  Basic mode*/
    NETDEV_SMART_ENCODE_MODE_ADVANCED           /*  Advanced mode*/
}NETDEV_SMART_ENCODE_MODE_E;
/**
* @enum tagNETDEVBitRateType
* @brief   Enumeration of bit rate mode
* @attention  None
*/
typedef enum tagNETDEVBitRateType
{
    NETDEV_BIT_RATE_TYPE_CBR      = 0,         /*  CBR mode*/
    NETDEV_BIT_RATE_TYPE_VBR      = 1          /*  VBR mode*/
}NETDEV_BIT_RATE_TYPE_E;

/**
* @enum tagNETDEVMainStreamType
* @brief   Enumeration of main stream type
* @attention  None
*/
typedef enum tagNETDEVMainStreamType
{
    NETDEV_MAIN_STREAM_TYPE_TIME     = 0,      /*  Scheduled main stream*/
    NETDEV_MAIN_STREAM_TYPE_EVENT    = 1       /*  Event main stream*/
}NETDEV_MAIN_STREAM_TYPE_E;

/**
* @enum tagNETDEVGopType
* @brief   Enumeration of GOP type
* @attention  None
*/
typedef enum tagNETDEVGopType
{
    NETDEV_GOP_TYPE_IP       = 0,      /* IP */
    NETDEV_GOP_TYPE_IBP      = 1,      /* IBP */
    NETDEV_GOP_TYPE_IBBP     = 2,      /* IBBP */
    NETDEV_GOP_TYPE_I        = 3       /* I */
}NETDEV_GOP_TYPE_E;

/**
* @enum tagNETDEVOSDContentType
* @brief Enumeration of content type
* @attention  None
*/
typedef enum tagNETDEVOSDContentType
{
    NETDEV_OSD_CONTENT_TYPE_NOTUSE                      = 0,                    /*  Not used*/
    NETDEV_OSD_CONTENT_TYPE_CUSTOM                      = 1,                    /*  Custom*/
    NETDEV_OSD_CONTENT_TYPE_DATE_AND_TIME               = 2,                    /*  Time and date*/
    NETDEV_OSD_CONTENT_TYPE_PTZ_CONTROLLER              = 3,                    /*  PTZ controller*/
    NETDEV_OSD_CONTENT_TYPE_PTZ_COORDINATES             = 4,                    /*  PTZ Coordinates*/
    NETDEV_OSD_CONTENT_TYPE_CRUISE                      = 5,                    /*  Patrol*/
    NETDEV_OSD_CONTENT_TYPE_ZOOM                        = 6,                    /*  Zoom*/
    NETDEV_OSD_CONTENT_TYPE_PRESET                      = 7,                    /*  Preset*/
    NETDEV_OSD_CONTENT_TYPE_ALARM_INFO                  = 8,                    /*  Alarm */
    NETDEV_OSD_CONTENT_TYPE_ENCODE                      = 9,                    /*  Encoding*/
    NETDEV_OSD_CONTENT_TYPE_SERIAL_PORT                 = 10,                   /*  Serial Port OSD*/
    NETDEV_OSD_CONTENT_TYPE_PTZ_ORIENTATION             = 11,                   /*  PZT direction*/
    NETDEV_OSD_CONTENT_TYPE_CHN_NAME                    = 12,                   /*  Channel name*/
    NETDEV_OSD_CONTENT_TYPE_DEBUG                       = 13,                   /*  Debug OSD*/
    NETDEV_OSD_CONTENT_TYPE_PEOPLE_COUNTING             = 14,                   /*  People counting OSD*/
    NETDEV_OSD_CONTENT_TYPE_NETWORK_PORT                = 15,                   /*  Network Port OSD*/
    NETDEV_OSD_CONTENT_TYPE_TIME                        = 16,                   /*  Time*/
    NETDEV_OSD_CONTENT_TYPE_DATE                        = 17,                   /*  Date*/
    NETDEV_OSD_CONTENT_TYPE_SMART_CONTENT               = 18,                   /*  Sensing OSD*/
    NETDEV_OSD_CONTENT_TYPE_BATTERY                     = 19,                   /*  Battery OSD*/
    NETDEV_OSD_CONTENT_TYPE_SCROLL_OSD                  = 20,                   /*  Scroll text OSD*/
    NETDEV_OSD_CONTENT_TYPE_PICTURE_OVERLAY             = 21,                   /*  LOGO OSD */
    NETDEV_OSD_CONTENT_TYPE_MOTOR_VEHICLE_NUM           = 22,                   /*  Vehicle flow of LPR*/
    NETDEV_OSD_CONTENT_TYPE_NON_MOTOR_VEHICLE_NUM       = 23,                   /*  Non-vehicle flow of LPR*/
    NETDEV_OSD_CONTENT_TYPE_PEOPLE_NUM                  = 24,                   /*  Pedestrian flow of LPR*/
    NETDEV_OSD_CONTENT_TYPE_INFOOSD_NUM                 = 25                    /*  Number of INFOOSDtype*/
}NETDEV_OSD_CONTENT_TYPE_E;

/**
 * @enum tagNETDEVDateOSDFormate
 * @brief Enumeration of date format
 * @attention ÎÞ None
 */
typedef enum tagNETDEVDateOSDFormate
{
    NETDEV_OSD_DATE_FORMAT_YYYY_MMDD                = 0,           /* yyyy-MM-dd */
    NETDEV_OSD_DATE_FORMAT_MMDD_YYYY                = 1,           /* MM-dd-yyyy */
    NETDEV_OSD_DATE_FORMAT_CHINESE_YYYY_MMDD        = 2,           /* yyyy year  MM month dd day yyyy/MM/dd*/
    NETDEV_OSD_DATE_FORMAT_CHINESE_MMDD_YYYY        = 3,           /* MM month dd day yyyy year MM/dd/yyyy*/
    NETDEV_OSD_DATE_FORMAT_CHINESE_YYY_MMDD_X       = 4,           /* yyyy year  MM month dd day week:X¡£ dddd yyyy MM dd*/
    NETDEV_OSD_DATE_FORMAT_CHINESE_MMDD_YYYY_X      = 5,           /* MM month dd day yyyy year week:X¡£ dddd MM dd yyyy*/
    NETDEV_OSD_DATE_FORMAT_ENGLISH_DDMM_YYYY        = 100,         /* dd/MM/yyyy */
    NETDEV_OSD_DATE_FORMAT_ENGLISH_MMDD_YYYY        = 101,         /* MM/dd/yyyy */
    NETDEV_OSD_DATE_FORMAT_ENGLISH_DDMMMM_YYYY      = 102,         /* dd MMMM, yyyy */
    NETDEV_OSD_DATE_FORMAT_ENGLISH_MMMMDD_YYYY      = 103,         /* MMMM dd, yyyy */
    NETDEV_OSD_DATE_FORMAT_ENGLISH_DDDDDDMMMM_YYYY  = 104,         /* dddd, dd MMMM, yyyy  */
    NETDEV_OSD_DATE_FORMAT_ENGLISH_DDDDDDMMMM_DDYYYY = 105,        /* dddd, MMMM dd, yyyy */
    NETDEV_OSD_DATE_FORMAT_ENGLISH_YYYY_MMDD        = 106,         /*  yyyy/MM/dd */
    NETDEV_OSD_DATE_FORMAT_ENGLISH_YYYY_MMMMDD      = 107,         /*  yyyy, MMMM dd */
    NETDEV_OSD_DATE_FORMAT_ENGLISH_DDDDYY_MMDD      = 108         /*  dddd, yy, MM dd */
}NETDEV_OSD_DATE_FORMAT_E;

/**
 * @enum tagNETDEVTimeOSDFormate
 * @brief  Enumeration of OSD time format
 * @attention  None
 */
typedef enum tagNETDEVTimeOSDFormate
{
    NETDEV_OSD_TIME_FORMAT_HHMMSS         = 0,                  /* HH:mm:ss */
    NETDEV_OSD_TIME_FORMAT_HH_MM_SS_T     = 1,                  /* hh:mm:ss t.t. */
    NETDEV_OSD_TIME_FORMAT_HH_MM_SS_TT    = 2,                  /* hh:mm:ss tt */
    NETDEV_OSD_TIME_FORMAT_TT_HH_MM_SS    = 3,                  /* tt hh:mm:ss */
    NETDEV_OSD_TIME_FORMAT_PM_HH_MM_SS    = 4,                  /* P.M. hh:mm:ss*/
    NETDEV_OSD_TIME_FORMAT_HH_MM_SS_XX    = 5,                  /* HH:mm:ss.xxx */
    NETDEV_OSD_TIME_FORMAT_HH_MM_SS_XX_TT = 6                   /* hh:mm:ss.xxx tt */

}NETDEV_OSD_TIME_FORMAT_E;

/**
 * @enum tagNETDEVOSDFontStyle
 * @brief  Enumeration of OSD font style
 * @attention  None
 */
typedef enum tagNETDEVOSDFontStyle
{
    NETDEV_OSD_FONT_STYLE_BACKGROUND = 0,                  /*  Background*/
    NETDEV_OSD_FONT_STYLE_STROKE     = 1,                  /*  Stroke*/
    NETDEV_OSD_FONT_STYLE_HOLLOW     = 2,                  /*  Hollow*/
    NETDEV_OSD_FONT_STYLE_NORMAL     = 3                   /*  Normal*/
}NETDEV_OSD_FONT_STYLE_E;

/**
 * @enum tagNETDEVOSDFontSize
 * @brief  Enumeration of OSD font size
 * @attention  None
 */
typedef enum tagNETDEVOSDFontSize
{
    NETDEV_OSD_FONT_SIZE_LARGE  = 0,                  /*  X-large*/
    NETDEV_OSD_FONT_SIZE_BIG    = 1,                  /*  Large*/
    NETDEV_OSD_FONT_SIZE_MEDIUM = 2,                  /*  Medium*/
    NETDEV_OSD_FONT_SIZE_SMALL  = 3                   /*  Small*/
}NETDEV_OSD_FONT_SIZE_E;

/**
 * @enum tagNETDEVOSDMinMargin
 * @brief  Enumeration of OSD font size
 * @attention  None
 */
typedef enum tagNETDEVOSDMinMargin
{
    NETDEV_OSD_MIN_MARGIN_NONE    = 0,               /*  None*/
    NETDEV_OSD_MIN_MARGIN_SINGLE  = 1,               /*  One char width*/
    NETDEV_OSD_MIN_MARGIN_DOUBLE  = 2                /*  Two char width*/
}NETDEV_OSD_MIN_MARGIN_E;

/**
 * @enum tagNETDEVOSDAlign
 * @brief Enumeration of OSD align
 * @attention  None
 */
typedef enum tagNETDEVOSDAlign
{
    NETDEV_OSD_ALIGN_LEFT   = 0,               /*  Left*/
    NETDEV_OSD_ALIGN_RIGHT  = 1                /*  Right*/
}NETDEV_OSD_ALIGN_E;

/**
 * @enum tagNETDEVQueryCondLogic
 * @brief Query condition logic type
 * @attention  None
 */
typedef enum tagNETDEVQueryCondLogic
{
    NETVMS_LOGIC_EQUAL             = 0,                /* Query condition logic type: equal to */
    NETVMS_LOGIC_GREATER           = 1,                /* Query condition logic type: greater than */
    NETVMS_LOGIC_LESS              = 2,                /* Query condition logic type: less than */
    NETVMS_LOGIC_NO_LESS           = 3,                /* Query condition logic type: not less than */
    NETDEV_LOGIC_NO_GREATER        = 4,                /* Query condition logic type: not greater than */
    NETDEV_LOGIC_NO_EQUAL          = 5                 /* Query conditional logic type: not equal to */
}NETDEV_QUERYCOND_LOGICTYPE_E;


/**
*@enum tagNETDEVStreamProtocol
*@brief Pull type enumeration
*@attention none
*/
typedef enum tagNETDEVStreamProtocol
{
    NETDEV_STREAM_PRO_RTMP         = 1,          /* RTP */
    NETDEV_STREAM_PRO_HLS          = 2,          /* HLS */
    NETDEV_STREAM_PRO_FLV          = 3           /* FLV */
}NETDEV_CLOUD_STREAM_PROTOCAL_E;

/**
*@enum tagNETDEVPullStreamMode
*@brief Open-flow mode type enumeration
*@attention none
*/
typedef enum tagNETDEVPullStreamMode
{
    NETDEV_STREAM_MODE_SERVER_DISTRIBUTE    = 0,   /* Server allocation */
    NETDEV_STREAM_MODE_FORCE_CDN            = 1    /* Mandatory distribution */
}NETDEV_PULL_STREAM_MODE_E;

/**
*@enum tagNETDEVDistributeMode
*@brief Distribution pattern type enumeration
*@attention none
*/
typedef enum tagNETDEVDistributeCloud
{
    NETDEV_DISTRIBUTE_CLOUD_NONE      = 0,            /* Distribution not enabled */
    NETDEV_DISTRIBUTE_CLOUD_KS        = 1,            /* Enable KS Cloud Distribution */
    NETDEV_DISTRIBUTE_CLOUD_UN        = 2,            /* Enable UNV Cloud Distribution */
    NETDEV_DISTRIBUTE_CLOUD_TEN       = 3            /* Enable Ten Cloud Distribution */
}NETDEV_DISTRIBUTE_CLOUD_SRV_E;

/**
*@enum tagNETDEVDistributeMode
*@brief Distribution pattern type enumeration
*@attention none
*/
typedef enum tagNETDEVDistributeMode
{
    NETDEV_DISTRIBUTE_MODE_AUTO       = 0,            /* automatic */
    NETDEV_DISTRIBUTE_MODE_FORCE      = 1             /* force */
}NETDEV_DISTRIBUTE_MODE_E;

/**
 * @enum tagNETDEVCloudConnectMode
 * @brief Cloud device connection mode 
 * @attention  None
 */
typedef enum tagNETDEVCloudConnectMode
{
    NETDEV_CLOUD_CONNECT_MODE_ALL       = 0,         /* Local direct link-> wide area network direct link-> hole-> forward */
    NETDEV_CLOUD_CONNECT_MODE_P2P_TURN  = 1,         /* Local direct link-> wide area network direct link-> hole forwarding(Forwarding delay 500ms) */
    NETDEV_CLOUD_CONNECT_MODE_P2P       = 2,         /* Direct hole */
    NETDEV_CLOUD_CONNECT_MODE_TURN      = 3          /* Direct forwarding */
}NETDEV_CLOUD_CONNECT_MODE;

/**
*@enum tagNETDEVLoginType
*@brief Login type enumeration
*@attention none
*/
typedef enum tagNETDEVLoginType
{
    NETDEV_LOGIN_TYPE_LOCAL             = 0,          /* Local login */
    NETDEV_LOGIN_TYPE_DYNAMIC           = 1,          /* Dynamic password login */
    NETDEV_LOGIN_TYPE_LOCAL_ALL         = 2,          /* Support for third party equipment */
    NETDEV_LOGIN_TYPE_CLOUD_DEVICE      = 3           /* Cloud device login */
}NETDEV_LOGIN_TYPE_E;

/* END*************   Enumeration value *************************** */

/* BEGIN***********   Structure *********************************** */
/**
 * @struct tagNETDEVDeviceInfo
 * @brief   Device information Structure definition
 * @attention  None
 */
typedef struct tagNETDEVDeviceInfo
{
    INT32   dwDevType;                          /*   see enumeration #NETDEV_DEVICETYPE_E */
    INT16   wAlarmInPortNum;                    /*   Number of alarm inputs */
    INT16   wAlarmOutPortNum;                   /*   Number of alarm outputs */
    INT32   dwChannelNum;                       /*   Number of Channels */
    BYTE    byRes[48];                          /* Reserved field   Reserved */
}NETDEV_DEVICE_INFO_S,*LPNETDEV_DEVICE_INFO_S;

/**
 * @struct tagNETDEVDeviceBasicInfo
 * @brief  Basic device information Structure definition
 * @attention  None
 */
typedef struct tagNETDEVDeviceBasicInfo
{ 
    CHAR szDevModel[NETDEV_LEN_64];                     /*   Device model */
    CHAR szSerialNum[NETDEV_LEN_64];                    /*   Hardware serial number */
    CHAR szFirmwareVersion[NETDEV_LEN_64];              /*   Software version */
    CHAR szMacAddress[NETDEV_LEN_64];                   /*   MAC address of IPv4 */
    CHAR szDeviceName[NETDEV_LEN_64];                   /*   Device name */
    BYTE byRes[448];                                    /* Reserved field   Reserved */
}NETDEV_DEVICE_BASICINFO_S, *LPNETDEV_DEVICE_BASICINFO_S;

/**
 * @struct tagNETDEVNetworkInterfaces
 * @brief  Network configuration information
 * @attention  None
 */
typedef struct tagNETDEVNetworkInterfaces
{
    INT32   dwMTU;                              /*   MTU value */
    BOOL    bIPv4DHCP;                          /*   DHCP of IPv4 */
    CHAR    szIpv4Address[NETDEV_LEN_32];       /*   IP address of IPv4 */
    CHAR    szIPv4GateWay[NETDEV_LEN_32];       /*   Gateway of IPv4 */
    CHAR    szIPv4SubnetMask[NETDEV_LEN_32];    /*   Subnet mask of IPv4 */
    BYTE    byRes[480];                         /* Reserved field   Reserved */
}NETDEV_NETWORKCFG_S, *LPNETDEV_NETWORKCFG_S;

/**
 * @struct tagSysemIPAddr
 * @brief  Address Structure definition 
 * @attention  None
 */
typedef struct tagSysemIPAddr
{
    INT32   eIPType;                            /*  see enumeration #NETDEV_HOSTTYPE_E */
    CHAR    szIPAddr[NETDEV_LEN_132];           /*  IP address */
}NETDEV_SYSTEM_IPADDR_S, *LPNETDEV_SYSTEM_IPADDR_S;

/**
 * @struct tagNETDEVSystemNTPInfo
 * @brief   NTP parameter
 * @attention  None
 */
typedef struct tagNETDEVSystemNTPInfo
{
    BOOL bSupportDHCP;                      /* Support DHCP or not */
    NETDEV_SYSTEM_IPADDR_S stAddr;          /* NTP information */
}NETDEV_SYSTEM_NTP_INFO_S, *LPNETDEV_SYSTEM_NTP_INFO_S;

#define NETDEV_NTP_SERVER_LIST_NUM          5
typedef struct tagSysemIPAddrInfo
{
    BOOL         bEnabled;                      /*NTP Server enable 0:unable  1:enable */
    INT64        ulAddressType;	                /*Address type  0:IPv4  1:IPv6(Temporary does not support)  2:domain name(NVR and AIO support)*/
    CHAR         szIPAddress[NETDEV_LEN_64];     /* The IP address of the NTP server ,character length range [0,64]. When address type is 0,the node must be selected. */
    CHAR         szDomainName[NETDEV_LEN_64];    /*The domain name of the NTP server ,character length range [0,64]. When address type is 2,the node must be selected.*/
    INT64        ulPort;                        /*NTP Port ,the range of [1-65535]. IPC does not support this configuration. */
    INT64        ulSynchronizeInterval;         /*Synchronize Interval: The support range of NVR and VMS is 5/10/15/30 minutes ,1/2/3/6/12 hours ,1 day ,and 1 week.The support range of IPC is 30-3600 seconds.All of the above time periods need to be converted to a time value in seconds.*/
    BYTE         byRes[128];                    /* Reserved*/
}NETDEV_SYSTEM_IPADDR_INFO_S, *LPNETDEV_SYSTEM_IPADDR_INFO_S;

typedef struct tagNETDEVSystemNTPInfoList
{
    INT64                              ulNum;                                             /*NTP服务器个�? NTP Server Number*/
    NETDEV_SYSTEM_IPADDR_INFO_S        astNTPServerInfoList[NETDEV_NTP_SERVER_LIST_NUM];  /*NTP服务器列表当前只支持一个NTP服务�?The NTP server list currently supports only one NTP server.*/
    BYTE                               byRes[128];	                                      /*保留字段   Reserved*/
}NETDEV_SYSTEM_NTP_INFO_LIST_S, *LPNETDEV_SYSTEM_NTP_INFO_LIST_S;



/**
 * @struct tagNETDEVPriviewInfo
 * @brief  Live view parameter Structure definition
 * @attention  None
 */
typedef struct tagNETDEVPriviewInfo
{
    INT32   dwChannelID;                 /* Channel ID */
    INT32   dwStreamType;                /* Stream type, see enumeration #NETDEV_LIVE_STREAM_INDEX_E */
    INT32   dwLinkMode;                  /* Transport protocol, see enumeration #NETDEV_PROTOCAL_E */
    LPVOID  hPlayWnd;                    /* Play window handle Play window handle */ 
    INT32   dwFluency;                   /* Image playback fluency priority type,see#NETDEV_PICTURE_FLUENCY_E */
    INT32   dwStreamMode;                /* stream see#NETDEV_STREAM_MODE_E  start stream mode see #NETDEV_STREAM_MODE_E*/
    INT32   dwLiveMode;                  /* live mode see#NETDEV_PULL_STREAM_MODE_E */
    INT32   dwDisTributeCloud;           /* Distribution capacity see#NETDEV_DISTRIBUTE_CLOUD_SRV_E */
    BOOL    dwallowDistribution;         /* Does the channel support distribution*/
    BYTE    byRes[244];                  /* Reserved field   Reserved */
}NETDEV_PREVIEWINFO_S, *LPNETDEV_PREVIEWINFO_S;

/**
 * @struct tagNETDEVVideoEffect
 * @brief  Live image information Structure definition
 * @attention Gamma parameter range: 0-10, other parameters: 0-255
 */
typedef struct tagNETDEVVideoEffect
{
    INT32 dwContrast;                   /*   Contrast */
    INT32 dwBrightness;                 /*   Brightness */
    INT32 dwSaturation;                 /*   Saturation */
    INT32 dwHue;                        /*   Hue */
    INT32 dwGamma;                      /*   Gamma */
    BYTE  byRes[16];                    /* Reserved field   Reserved */
}NETDEV_VIDEO_EFFECT_S, *LPNETDEV_VIDEO_EFFECT_S;

/**
 * @struct tagNETDEVImagingSetting
 * @brief     Device image settings Structure definition
 * @attention   parameter range: 0-255
 */
typedef struct tagNETDEVImagingSetting
{
    INT32 dwContrast;                   /*   Contrast */
    INT32 dwBrightness;                 /*   Brightness */
    INT32 dwSaturation;                 /*   Saturation */
    INT32 dwSharpness;                  /*   Sharpness */
    BYTE  byRes[252];                   /*   Reserved field   Reserved */
}NETDEV_IMAGE_SETTING_S, *LPNETDEV_IMAGE_SETTING_S;

/************  Playback services***********************************************/

/**
 * @struct tagNETDEVVodFile
 * @brief   Recording file Structure definition
 * @attention  None
 */
typedef struct tagNETDEVVodFile
{
    CHAR                        szFileName[NETDEV_LEN_64];      /*   Recording file name */
    NETDEV_PLAN_STORE_TYPE_E    enType;                         /*   Recording storage type */
    INT64                       tBeginTime;                     /*   Start time */
    INT64                       tEndTime;                       /*   End time */
}NETDEV_VOD_FILE_S, *LPNETDEV_VOD_FILE_S;

/**
 * @struct tagNETDEVFindCond
 * @brief   Recording query Structure definition
 *        . Query recording files according to file type and time
 * @attention  None
 */
typedef struct tagNETDEVFindCond
{
    CHAR    szFileName[NETDEV_LEN_64];      /* Recording file name */
    INT32   dwChannelID;                    /* Channel ID */
    INT32   dwStreamType;                   /* Stream type, see enumeration #NETDEV_LIVE_STREAM_INDEX_E */
    INT32   dwFileType;                     /* Recording storage type, see enumeration #NETDEV_PLAN_STORE_TYPE_E */
    INT64   tBeginTime;                     /* Start time */
    INT64   tEndTime;                       /* End time */
    BYTE    byRes[36];                      /* Reserved field   Reserved */
}NETDEV_FILECOND_S, *LPNETDEV_FILECOND_S;

/**
 * @struct tagNETDEVFingData
 * @brief  Recording query data Structure definition
 *         Get the information of found files one by one
 * @attention  None
 */
typedef struct tagNETDEVFindData
{
    CHAR    szFileName[NETDEV_FILE_NAME_LEN];               /*   Recording file name */
    INT64   tBeginTime;                                     /*   Start time */
    INT64   tEndTime;                                       /*   End time */
    BYTE    byFileType;                                     /*   Recording storage type */
    BYTE    byRes[171];                                     /*   Reserved */
}NETDEV_FINDDATA_S,*LPNETDEV_FINDDATA_S;

/**
 * @struct tagNETDEVPlayBackInfo
 * @brief  Parameters of play back recordings by file name Structure definition
 * @attention  None
 */
typedef struct tagNETDEVPlayBackInfo
{
    char    szName[NETDEV_LEN_260];         /* Playback control block name*/
    INT64   tBeginTime;                     /* Playback start time */
    INT64   tEndTime;                       /* Playback end time */
    INT32   dwLinkMode;                     /* Transport protocol, see enumeration #NETDEV_PROTOCAL_E */
    LPVOID  hPlayWnd;                       /* Play window handle */
    INT32   dwFileType;                     /* Recording storage type, see enumeration #NETDEV_PLAN_STORE_TYPE_E */
    INT32   dwDownloadSpeed;                /* Download speed, see enumeration #NETDEV_E_DOWNLOAD_SPEED_E */
    INT32   dwStreamMode;                   /* stream mode see #NETDEV_STREAM_MODE_E */
    BYTE    byRes[252];                     /* Reserved field   Reserved */
}NETDEV_PLAYBACKINFO_S, *LPNETDEV_PLAYBACKINFO_S;

/**
 * @struct tagNETDEVPlayBackCondition
 * @brief  Parameters of play back by time Structure definition
 * @attention  None
 */
typedef struct tagNETDEVPlayBackCondition
{
    INT32   dwChannelID;                /* Playback channel */
    INT64   tBeginTime;                 /* Playback start time */
    INT64   tEndTime;                   /* Playback end time */
    INT32   dwLinkMode;                 /* Transport protocol, see enumeration #NETDEV_PROTOCAL_E */
    LPVOID  hPlayWnd;                   /* Play window handle */
    INT32   dwFileType;                 /* Recording storage type, see enumeration #NETDEV_PLAN_STORE_TYPE_E */
    INT32   dwDownloadSpeed;            /* download speed see#NETDEV_E_DOWNLOAD_SPEED_E */
    INT32   dwStreamMode;               /* stream mode see #NETDEV_STREAM_MODE_E */
    BYTE    byRes[252];                 /* Reserved field   Reserved */
}NETDEV_PLAYBACKCOND_S, *LPNETDEV_PLAYBACKCOND_S;


/**
 * @struct tagNETDEVPlayBackCondition
 * @brief  Parameters of play back Structure definition
 * @attention  None
 */
typedef struct tagNETDEVPlayBackParam
{
    INT64   tBeginTime;                 /* Playback start time */
    INT64   tEndTime;                   /* Playback end time */
    INT32   dwLinkMode;                 /* Transport protocol, see enumeration #NETDEV_PROTOCAL_E */
    LPVOID  hPlayWnd;                   /* Play window handle */
    INT32   dwFileType;                 /* Recording storage type, see enumeration #NETDEV_PLAN_STORE_TYPE_E */
    INT32   dwDownloadSpeed;            /* download speed see #NETDEV_E_DOWNLOAD_SPEED_E */
    INT32   dwStreamMode;               /* stream mode see #NETDEV_STREAM_MODE_E */
    BYTE    byRes[252];                 /* Reserved field   Reserved */
}NETDEV_PLAYBACKPARAM_S, *LPNETDEV_PLAYBACKPARAM_S;


/************************************************* PTZ services*****************************************************/
/**
 * @struct tagstNETDEVPtzPreset
 * @brief   PTZ preset information Structure definition
 * @attention  None
 */
typedef struct tagstNETDEVPtzPreset
{
    INT32   dwPresetID;                                 /*   Preset ID */
    CHAR    szPresetName[NETDEV_LEN_32];                /*   Preset name */
}NETDEV_PTZ_PRESET_S, *LPNETDEV_PTZ_PRESET_S;

/**
 * @struct tagstNETDEVPtzAllPresets
 * @brief  All PTZ presets Structure definition
 * @attention None
 */
typedef struct tagstNETDEVPtzAllPresets
{
    INT32               dwSize;                             /*   Total number of presets */
    NETDEV_PTZ_PRESET_S astPreset[NETDEV_MAX_PRESET_NUM];   /*   Structure of preset information */
}NETDEV_PTZ_ALLPRESETS_S, *LPNETDEV_PTZ_ALLPRESETS_S;

/**
 * @struct tagNETDEVCruisePointInfo
 * @brief  PTZ preset patrol point information Structure definition
 * @attention  None
 */
typedef struct tagNETDEVCruisePoint
{
    INT32   dwPresetID;                     /*   Preset ID */
    INT32   dwStayTime;                     /*   Stay time */
    INT32   dwSpeed;                        /*   Speed */
    INT32   dwReserve;                      /*   Reserved */
}NETDEV_CRUISE_POINT_S, *LPNETDEV_CRUISE_POINT_S;

/**
 * @struct tagNETDEVCruiseInfo
 * @brief  PTZ preset patrol route information Structure definition 
 * @attention  None
 */
typedef struct tagNETDEVCruiseInfo
{
    INT32                   dwCuriseID;                                     /*   Route ID */
    CHAR                    szCuriseName[NETDEV_LEN_32];                    /*   Route name */
    INT32                   dwSize;                                         /*   Number of presets included in the route */
    NETDEV_CRUISE_POINT_S   astCruisePoint[NETDEV_MAX_CRUISEPOINT_NUM];     /*   Information of presets included in the route */
}NETDEV_CRUISE_INFO_S, *LPNETDEV_CRUISE_INFO_S;

/**
 * @struct tagNETDEVCruiseList
 * @brief  PTZ preset patrol route list Structure definition
 * @attention  None
 */
typedef struct tagNETDEVCruiseList
{
    INT32                   dwSize;                                         /*   Number of patrol routes */
    NETDEV_CRUISE_INFO_S    astCruiseInfo[NETDEV_MAX_CRUISEROUTE_NUM];      /*   Information of patrol routes */
}NETDEV_CRUISE_LIST_S, *LPNETDEV_CRUISE_LIST_S;

/**
 * @struct tagNETDEVPtzTrackinfo
 * @brief  Route information of PTZ route patrol Structure definition
 * @attention  None
 */
typedef struct tagNETDEVPtzTrackinfo
{
    INT32 dwTrackNum;                                               /*   Number of existing patrol routes */
    CHAR  aszTrackName[NETDEV_TRACK_CRUISE_MAXNUM][NETDEV_LEN_64];  /*   Route name */
}NETDEV_PTZ_TRACK_INFO_S, *LPNETDEV_PTZ_TRACK_INFO_S;

/**
 * @struct tagNETDEVPTZStatus
 * @brief  PTZ status Structure definition
 * @attention  Absolute horizontal coordinates correspond to angles: 0 to 1 correspond to 0 to 180 degrees, and -1 to 0 correspond 180 to 360 degrees 
               Absolute vertical coordinates correspond to angles: 0 to 1 correspond to 0 to 90 degrees 
               Absolute multiples correspond to the actual multiples: 0 to 1, correspond to 0 to maximum multiples 
 */
typedef struct tagNETDEVPTZStatus
{
    FLOAT                       fPanTiltX;              /*   Absolute horizontal coordinates*/
    FLOAT                       fPanTiltY;              /*   Absolute vertical coordinates*/
    FLOAT                       fZoomX;                 /*   Absolute multiples*/
    NETDEV_PTZ_MOVE_STATUS_E    enPanTiltStatus;        /*   PTZ Status*/
    NETDEV_PTZ_MOVE_STATUS_E    enZoomStatus;           /*   Focus Status*/
}NETDEV_PTZ_STATUS_S, *LPNETDEV_PTZ_STATUS_S;

/**
 * @struct tagNETDEVPTZAbsoluteMove
 * @brief    Absolute coodinates Structure definition
 * @attention  Absolute horizontal coordinates correspond to angles: 0 to 1 correspond to 0 to 180 degrees, and -1 to 0 correspond 180 to 360 degrees 
                 Absolute vertical coordinates correspond to angles: 0 to 1 correspond to 0 to 90 degrees 
                 Absolute multiples correspond to the actual multiples: 0 to 1, correspond to 0 to maximum multiples 
 */
typedef struct tagNETDEVPTZAbsoluteMove
{
    FLOAT                       fPanTiltX;                          /*  Absolute horizontal coordinates*/
    FLOAT                       fPanTiltY;                          /*  Absolute vertical coordinates*/
    FLOAT                       fZoomX;                             /*  Absolute multiples*/
}NETDEV_PTZ_ABSOLUTE_MOVE_S, *LPNETDEV_PTZ_ABSOLUTE_MOVE_S;

/**
 * @struct tagNETDEVRect
 * @brief  Rectangle Area  Structure definition
 * @attention  None
 */
typedef struct tagNETDEVRect
{
    INT32   dwLeft;                               /* X axis left point value [0,10000] */
    INT32   dwTop;                                /* Y axis top point value [0,10000] */
    INT32   dwRight;                              /* X axis right point value [0,10000] */
    INT32   dwBottom;                             /* Y axis bottom point value [0,10000] */
}NETDEV_RECT_S, *LPNETDEV_RECT_S;

/**
 * @struct tagNETDEVPtzOperateAreaInfo
 * @brief  Image area information Structure definition
 * @attention  None
 */
typedef struct tagNETDEVPtzOperateAreaInfo
{
    INT32   dwBeginPointX;                           /*   Area start point X value [0,10000] */
    INT32   dwBeginPointY;                           /*   Area start point Y value [0,10000] */
    INT32   dwEndPointX;                             /*   Area end point X value [0,10000] */
    INT32   dwEndPointY;                             /*   Area end point Y value [0,10000] */
}NETDEV_PTZ_OPERATEAREA_S, *LPNETDEV_PTZ_OPERATEAREA_S;

/**
 * @struct tagNETDEVPictureData
 * @brief  Image data Structure definition
 *         Storing pointer and length of decoded picture data
 * @attention  None
 */
typedef struct tagNETDEVPictureData
{
    BYTE    *pucData[4];                /* pucData[0]: Y plane pointer, pucData[1]: U plane pointer, pucData[2]: V plane pointer */
    INT32   dwLineSize[4];              /* ulLineSize[0]: Y line spacing, ulLineSize[1]: U line spacing, ulLineSize[2]: V line spacing */
    INT32   dwPicHeight;                /* Picture height */
    INT32   dwPicWidth;                 /* Picture width */
    INT32   dwRenderTimeType;           /* Time data type for rendering */
    INT64   tRenderTime;                /* Time data for rendering */
}NETDEV_PICTURE_DATA_S, *LPNETDEV_PICTURE_DATA_S;

/**
 * @struct tagNETDEVWaveData
 * @brief  Audio data Structure definition
 *         Storing pointer and length of decoded picture data
 * @attention  None
 */
typedef struct tagNETDEVWaveData
{
    CHAR  *pcData;                      /*   Audio data pointer */
    INT32 dwDataLen;                    /*   Audio data length */
    INT32 dwWaveFormat;                 /*   Format of decoded audio*/
}NETDEV_WAVE_DATA_S, *LPNETDEV_WAVE_DATA_S;

/**
* @struct tagNETDEVParseAudioData
* @brief Definition of structure for storing pointer and length of audio data after framing
* @attention none
*/
typedef struct tagNETDEVParseAudioData
{
    BYTE *pucData;                  /* Audio data pointer */
    UINT32 udwDataLen;              /* Audio data length */
    UINT32 udwAudioCodeFormat;      /* AudioCodeFormat,see#NETDEV_AUDIO_ENCODE_TYPE_E */
    UINT32 udwWaveFormat;           /* WaveFormat, see #NETDEV_WAVE_FORMAT_INFO_E */
    INT64 tTimeStamp;               /* Time stamp (ms)*/
    BYTE  byRes[8];                 /* Reserved field   Reserved */
}NETDEV_PARSE_AUDIO_DATA_S, *LPNETDEV_PARSE_AUDIO_DATA_S;

/**
 * @struct tagNETDEVParseVideoData
 * @brief  Video analytic data Structure definition
 *         Storing pointer and length of framed video data
 * @attention  None
 */
typedef struct tagNETDEVParseVideoData
{
    BYTE   *pucData;             /* Pointer to video data */
    INT32  dwDataLen;            /* Video data length */
    INT32  dwVideoFrameType;     /* Frame type, see enumeration #NETDEV_VIDEO_FRAME_TYPE_E */
    INT32  dwVideoCodeFormat;    /* Video encoding format, see enumeration #NETDEV_VIDEO_CODE_TYPE_E  */
    INT32  dwHeight;             /* Video image height */
    INT32  dwWidth;              /* Video image width */
    INT64  tTimeStamp;           /* Time stamp (ms) */
    BYTE  byRes[8];              /* Reserved field   Reserved */
}NETDEV_PARSE_VIDEO_DATA_S, *LPNETDEV_PARSE_VIDEO_DATA_S;


/**
 * @struct tagNETDEVVideoChlDetailInfo
 * @brief    Structure definition
 * @attention  None
 */
typedef struct tagNETDEVVideoChlDetailInfo
{
    INT32                       dwChannelID;                        /* Channel ID */
    BOOL                        bPtzSupported;                      /* Whether ptz is supported */
    NETDEV_CHANNEL_STATUS_E     enStatus;                           /* Channel status NETDEV_CHANNEL_STATUS_E*/
    INT32                       dwStreamNum;                        /* Number of streams µ±enStatusÎªNETDEV_CHL_STATUS_UNBINDÊ±£¬´ËÖµÎÞÐ§*/
    CHAR                        szChnName[NETDEV_LEN_64];           /* Channel Name */
    BYTE                        byRes[4];                           /* Reserved field   Reserved field*/
}NETDEV_VIDEO_CHL_DETAIL_INFO_S, *LPNETDEV_VIDEO_CHL_DETAIL_INFO_S;

/**
 * @struct tagNETDEVVideoChlDetailInfoEx
 * @brief  Structure definition
 * @attention  None
 */
typedef struct tagNETDEVVideoChlDetailInfoEx
{
    INT32                       dwChannelID;                        /* Channel ID */
    BOOL                        bPtzSupported;                      /* Whether ptz is supported */
    NETDEV_CHANNEL_STATUS_E     enStatus;                           /* Channel status NETDEV_CHANNEL_STATUS_E */
    INT32                       dwStreamNum;                        /* Number of streams when enStatus is NETDEV_CHL_STATUS_UNBIND£¬This value is not valid*/
	NETDEV_CHANNEL_TYPE_E       enChannelType;                      /* Channel type,(note: This field is valid only for mixed NVR) */
    NETDEV_VIDEO_STANDARD_E     enVideoFormat;                      /* Video input system£¬when ChannelType is NETDEV_CHL_TYPE_DIGITAL£¬This value is not valid (note: This field is valid only for mixed NVR) */
    NETDEV_HOSTTYPE_E           enAddressType;                      /* IP address type */
    CHAR                        szIPAddr[NETDEV_IPADDR_STR_MAX_LEN];/* IP address*/
    INT32                       dwPort;                             /* port */
    CHAR                        szChnName[NETDEV_LEN_64];           /* Channel Name */
    BOOL                        allowDistribution;                  /* Whether stream distribution is allowed*/
    BYTE                        byRes[92];                          /* Reserved field   Reserved field*/
}NETDEV_VIDEO_CHL_DETAIL_INFO_EX_S, *LPNETDEV_VIDEO_CHL_DETAIL_INFO_EX_S;

/**
 * @struct tagNETDEVVideoStreamInfo
 * @brief  Channel video stream information Structure definition
 * @attention  None
 */
typedef struct tagNETDEVVideoStreamInfo
{
    NETDEV_LIVE_STREAM_INDEX_E  enStreamType;       /*   Stream index */
    INT32                       bEnableFlag;        /*   Enable or not */
    INT32                       dwHeight;           /*   Video encoding resolution - Height */
    INT32                       dwWidth;            /*   Video encoding resolution - Width */
    INT32                       dwFrameRate;        /*   Video encoding configuration frame rate */
    INT32                       dwBitRate;          /*   Bit rate */
    NETDEV_VIDEO_CODE_TYPE_E    enCodeType;         /*   Video encoding format */
    NETDEV_VIDEO_QUALITY_E      enQuality;          /*   Image quality */
    INT32                       dwGop;              /*   I-frame interval */
    BYTE                        byRes[32];          /* Reserved field   Reserved */
}NETDEV_VIDEO_STREAM_INFO_S, *LPNETDEV_VIDEO_STREAM_INFO_S;


/**
* @enum tagNETDEVVideoResolution
* @brief Video resolution
* @attention none
*/
typedef struct tagNETDEVVideoResolution
{
    INT32 dwWidth;
    INT32 dwHeight;
}NETDEV_VIDEO_RESOLUTION_S, *LPNETDEV_VIDEO_RESOLUTION_S;


/**
* @enum tagNETDEVRange
* @brief  Range
* @attention none
*/
typedef struct tagNETDEVRange
{
    INT32   dwMin;
    INT32   dwMax;
}NETDEV_RANGE_S, *LPNETDEV_RANGE_S;

/**
* @enum tagNETDEVVideoEncodeOption
* @brief Video encode option
* @attention none
*/
typedef struct tagNETDEVVideoEncodeOption
{
    INT32                       dwEncodeType;                                       /*  NETDEV_VIDEO_CODE_TYPE_E*/
    INT32                       dwResolutionSize;                                   /*  Resolution size */
    NETDEV_VIDEO_RESOLUTION_S   astResolution[NETDEV_RESOLUTION_NUM_MAX];           /*  Resolution */
    NETDEV_RANGE_S              stIFrameInterval;                                   /*  I frame interval */
    NETDEV_RANGE_S              stFrameRate;                                        /*  Frame rate */
    NETDEV_RANGE_S              stEncodingInterval;                                 /*  Encode interval */
    NETDEV_RANGE_S              stBitRate;                                          /*  Bit rate */
}NETDEV_VIDEO_ENCODE_OPTION_S, *LPNETDEV_VIDEO_ENCODE_OPTION_S;

/**
* @enum tagNETDEVVideoStreamCap
* @brief  Video stream Cap
* @attention none
*/
typedef struct tagNETDEVVideoStreamCap
{
    INT32                           dwStreamType;                                   /*  Bitstream type see NETDEV_LIVE_STREAM_INDEX_E */
    INT32                           dwEncodeCapSize;                                /*  Encode capability size */
    NETDEV_VIDEO_ENCODE_OPTION_S    astEncodeCap[NETDEV_VIDEO_ENCODE_TYPE_MAX];     /*  Encode capability */
    NETDEV_RANGE_S                  stQuality;                                      /*  Quality range */
}NETDEV_VIDEO_STREAM_CAP_S, *LPNETDEV_VIDEO_STREAM_CAP_S;

/**
 * @struct tagNETDEVLogFindCond
 * @brief  Log query condition Structure definition
 * @attention  None
 */
typedef struct tagNETDEVLogFindCond
{
    INT32      dwMainType;         /* Log type. See #NETDEV_LOG_MAIN_TYPE_E for reference */
    INT32      dwSubType;          /* See #NETDEV_LOG_SUB_TYPE_E for reference */
    INT64      tBeginTime;         /* Start time */
    INT64      tEndTime;           /* End time */
    INT32      dwLimitNum;         /* Number of each query*/
    INT32      dwOffset;           /* Start search from No. X. X starts from 0*/
}NETDEV_FIND_LOG_COND_S, *LPNETDEV_FIND_LOG_COND_S;

/**
* @struct tagNETDEVOptLogInfo
* @brief Definition of log info structure
* @attention None
*/
typedef struct tagNETDEVOptLogInfo
{
    INT64       tTime;                                  /* Log time*/
    INT32       dwMainType;                             /* Main Type.See #NETDEV_LOG_MAIN_TYPE_E for reference*/
    INT32       dwSubType;                              /* Sub Type.See #NETDEV_LOG_SUB_TYPE_E for reference*/
    INT32       dwChannelID;                            /* Log source*/
    CHAR        szUserName[NETDEV_NAME_MAX_LEN];        /* Username*/
    CHAR        szUserAddr[NETDEV_IPADDR_STR_MAX_LEN];  /* User IP address*/
    BYTE        bRes[256];                              /* Reserved field  Reserved */
}NETDEV_LOG_INFO_S,*LPNETDEV_LOG_INFO_S;

/*****************   Alarm services**************************************************/
/**
 * @struct tagNETDEVAlarmInfo
 * @brief Alarm information Structure definition
 * @attention  None
 */
typedef struct tagNETDEVAlarmInfo
{
    INT32   dwAlarmType;                    /* see enumeration #NETDEV_ALARM_TYPE_E */
    INT64   tAlarmTime;                     /* Alarm time */
    INT32   dwChannelID;                    /* Channel ID for NVR */
    UINT16  wIndex;                         /* Index number,  disk slot index number */
    CHAR    *pszName;                       /* Alarm source name, alarm input/output name */
    INT32   dwTotalBandWidth;               /* Current total bandwidth (in MBps) */
    INT32   dwUnusedBandwidth;              /* Bandwidth left (in MBps)*/
    INT32   dwTotalStreamNum;               /* Total cameras*/
    INT32   dwFreeStreamNum;                /* Cameras left */
    INT32   dwMediaMode;                    /* For enumerations, see#NETDEV_MEDIA_MODE_E*/
    BYTE    byRes[10];                      /* Reserved field   Reserved */
}NETDEV_ALARM_INFO_S, *LPNETDEV_ALARM_INFO_S;

/**
* @enum tagNETDEVAlarmProtocol
* @brief Alarm protocol enumeration definition
 * @attention None
 */
typedef enum tagNETDEVAlarmProtocol
{
    NETDEV_ALARM_PROTOCOL_ONVIF = 0X01,                     /* ONVIF */
    NETDEV_ALARM_PROTOCOL_PRIVATE = 0X02,                   /* private */
}NETDEV_ALARM_PROTOCOL_E;

/**
* @enum tagNETDEVSubscribeAlarmType
* @brief Subscription alarm event type bit definition enumeration definition
 * @attention  None
 */
typedef enum tagNETDEVSubscribeAlarmType
{
    NETDEV_SUBSCRIBE_ALARM_TYPE_COM = 0X01,                     /* Universal alarm */
    NETDEV_SUBSCRIBE_ALARM_TYPE_SMART = 0X02,                   /* smart alarm */
    NETDEV_SUBSCRIBE_ALARM_TYPE_INTELLIGENTIPC = 0X04           /* smart IPC */
}NETDEV_SUBSCRIBE_ALARM_TYPE_E;

/**
 * @struct tagNETDEVAlarmSubscribeInfo
 * @brief  Alarm subscribe information Structure definition
 * @attention  None
 */
typedef struct tagNETDEVAlarmSubscribeInfo
{
    INT32   dwAlarmType;                    /* see NETDEV_SUBSCRIBE_ALARM_TYPE_E Use or operation of multiple types */
    BYTE    byRes[44];                      /* Reserved field   Reserved */
}NETDEV_ALARM_SUB_INFO_S, *LPNETDEV_ALARM_SUB_INFO_S;

/**
 * @struct tagNETDEVPullAlarmInfo
 * @brief  Get alarm information Structure definition
 * @attention None
 */
typedef struct tagNETDEVPullAlarmInfo
{
    NETDEV_ALARM_TYPE_E   enAlarm;         /*  Alarm type */
    INT32   dwChancelId;                   /*  Channel ID for NVR */
}NETDEV_PULLALARM_INFO_S, *LPNETDEV_PULLALARM_INFO_S;

/**********************  Passenger flow statistic **************************/
/**
 * @struct tagNETDEVPassengerFlowStatisticData
 * @brief  Passenger flow statistic infomation Sturcture definition
 * @attention  None
 */
typedef struct tagNETDEVPassengerFlowStatisticData
{
    INT32            dwChannelID;                  /*  Channel ID */
    INT64            tReportTime;                  /*  Report time */
    INT32            tInterval;                    /*  Interval time */
    INT32            dwEnterNum;                   /*  Enter num */
    INT32            dwExitNum;                    /*  Exit num */
    INT32            dwTotalEnterNum;              /*  Total enter num */
    INT32            dwTotalExitNum;               /*  Total exit num */
}NETDEV_PASSENGER_FLOW_STATISTIC_DATA_S, *LPNETDEV_PASSENGER_FLOW_STATISTIC_DATA_S;


/*******************************************Tms Face capture**************************************/
/* Face ID buffer length */
#define NETDEV_TMS_FACE_ID_LEN            16
/* face position string cache length */
#define NETDEV_TMS_FACE_POSITION_LEN      32
/* Record ID cache length */
#define NETDEV_TMS_FACE_RECORD_ID_LEN     32
/* Camera ID buffer length */
#define NETDEV_TMS_CAMER_ID_LEN           32
/* Cache length by time string */
#define NETDEV_TMS_PASSTIME_LEN           32
/* Bayonet number buffer length */
#define NETDEV_TMS_FACE_TOLLGATE_ID_LEN   32

/************************************************************************/
/*               Heat diagram                                                 */
/************************************************************************/
/*Heat map DevID field length*/
#define NETDEV_TMS_HEAT_MAP_DEVID_LEN                 32
/*Heat diagram record ID field length*/
#define NETDEV_TMS_HEAT_MAP_RECORD_ID_LEN             16
/*Heat graph CollectTime field length*/
#define NETDEV_TMS_HEAT_MAP_COllECT_TIME_LEN          18
/*Maximum number of pictures or regions*/
#define NETDEV_TMS_PIC_COMMON_NUM                     10

/*XML NODE*/
#define NETDEV_TMS_HEAT_MAP_XML_NODE_EVENT                 "Event"
#define NETDEV_TMS_HEAT_MAP_XML_NODE_EVENT_DEVID           "DevID"
#define NETDEV_TMS_HEAT_MAP_XML_NODE_EVENT_RECORDID        "RecordID"
#define NETDEV_TMS_HEAT_MAP_XML_NODE_EVENT_COLLECTTIME     "CollectTime"
#define NETDEV_TMS_HEAT_MAP_XML_NODE_EVENT_COLUMNS         "Columns"
#define NETDEV_TMS_HEAT_MAP_XML_NODE_EVENT_ROWS            "RowS"
#define NETDEV_TMS_HEAT_MAP_XML_NODE_EVENT_HOLDTIME        "HoldTime"
#define NETDEV_TMS_HEAT_MAP_XML_NODE_EVENT_DATA            "Data"

/************************************************************************/
/*            License plate                                                  */
/************************************************************************/
/*License plate recognition CamID field length*/
#define NETDEV_TMS_CAR_PLATE_CAMID_LEN                  32
/*License plate recognition RecordID field length*/
#define NETDEV_TMS_CAR_PLATE_RECORDID_LEN               16
/*License plate recognition TollgateID field length*/
#define NETDEV_TMS_CAR_PLATE_TOLLGATE_LEN               32
/*License plate recognition PassTime field length*/
#define NETDEV_TMS_CAR_PLATE_PASSTIME_LEN               18
/*License plate recognition LaneID field length*/
#define NETDEV_TMS_CAR_PLATE_LANEID_LEN                 2
/*Length of CarPlate field of license plate recognition*/
#define NETDEV_TMS_CAR_PLATE_CARPLATE_LEN               32

/*XML NODE*/
#define NETDEV_TMS_HEAT_CAR_PLATE_NODE_VEHICLE                 "Vehicle"
#define NETDEV_TMS_HEAT_CAR_PLATE_NODE_VEHICLE_CAMID           "CamID"
#define NETDEV_TMS_HEAT_CAR_PLATE_NODE_VEHICLE_RECORDID        "RecordID"
#define NETDEV_TMS_HEAT_CAR_PLATE_NODE_VEHICLE_TOLLGATEID      "TollgateID"
#define NETDEV_TMS_HEAT_CAR_PLATE_NODE_VEHICLE_PASSTIME        "PassTime"
#define NETDEV_TMS_HEAT_CAR_PLATE_NODE_VEHICLE_LANEID          "LaneID"
#define NETDEV_TMS_HEAT_CAR_PLATE_NODE_VEHICLE_CARPLATE        "CarPlate"


#define NETDEV_TMS_STRUT_CAMID_LEN                  32

#define NETDEV_TMS_STRUT_RECORDID_LEN               32

#define NETDEV_TMS_STRUT_TOLLGATE_LEN               32

#define NETDEV_TMS_STRUT_PASSTIME_LEN               32

#define NETDEV_TMS_STRUT_LANEID_LEN                 32


/*XML NODE*/
#define NETDEV_TMS_STRUT_NODE_StructureInfo                 "StructureInfo"
#define NETDEV_TMS_STRUT_NODE_CommonHeader                  "CommonHeader"
#define NETDEV_TMS_STRUT_NODE_CAMID                         "CamID"
#define NETDEV_TMS_STRUT_NODE_RECORDID                      "RecordID"
#define NETDEV_TMS_STRUT_NODE_TOLLGATEID                    "TollgateID"
#define NETDEV_TMS_STRUT_NODE_PASSTIME                      "PassTime"
#define NETDEV_TMS_STRUT_NODE_LANEID                        "LaneID"

/**
 * @enum tagNETDEVTMSPersionImageFormatType
 * @brief Picture type enumeration
 * @attention  None
 */
typedef enum  tagNETDEVTMSPersionImageType
{
    NETDEV_TMS_PERSION_IMAGE_TYPE_FULL_VIEW = 1,         /* panoramagram */
    NETDEV_TMS_PERSION_IMAGE_TYPE_FACE = 2,              /* Face image */
    NETDEV_TMS_PERSION_IMAGE_TYPE_INVALID
}NETDEV_TMS_PERSION_IMAGE_TYPE_E;

/**
 * @enum tagNETDEVTMSPersionImageFormatType
 * @brief Picture format enumeration
 * @attention  None
 */
typedef enum  tagNETDEVTMSPersionImageFormatType
{
    NETDEV_TMS_PERSION_IMAGE_FORMAT_JPG  = 1,            /* JPEG */
    NETDEV_TMS_PERSION_IMAGE_FORMAT_BMP  = 2,            /* BMP */
    NETDEV_TMS_PERSION_IMAGE_FORMAT_PNG  = 3,            /* PNG */
    NETDEV_TMS_PERSION_IMAGE_FORMAT_GIF  = 4,            /* GIF */
    NETDEV_TMS_PERSION_IMAGE_FORMAT_TIFF = 5,            /* TIFF */
    NETDEV_TMS_PERSION_IMAGE_FORMAT_INVALID
}NETDEV_TMS_PERSION_IMAGE_FORMAT_E;

/**
 * @struct tagNETDEVFacePositionInfo
 * @brief Connection and socket cache information
 * @attention
 */
typedef struct tagNETDEVTmsConnectInfo
{ 
    UINT32   udwPktVer;          /* Message version */ 
    UINT32   udwTmsProtoCmd;     /* Tms Protocol command code */
    CHAR     *pcRecvBuf;         /* socket Receive data buffer*/
    UINT32   udwBufMaxLen;       /* RecvBuf length */
    UINT32   udwPktTotalLen;     /* The total length of a packet at the communication protocol level, including a synchronization header, a synchronization tail */
    BOOL     bHdrParsed;         /* Message header resolution completion flag */
    BYTE     bRes[32];           /* Reserved field  Reserved */
}NETDEV_TMS_CONNECT_INFO_S, *LPNETDEV_TMS_CONNECT_INFO_S;

/**
 * @struct tagNETDEVTMSPersonInfo
 * @brief Personnel information
 * @attention
 */
typedef  struct tagNETDEVTMSPersonInfo
{
    UINT32 udwFaceId;                                      /* Face ID, possibly 0, indicating no xml correspondence */
    CHAR   szCamerID[NETDEV_TMS_CAMER_ID_LEN];             /* Camera No. */
    CHAR   szRecordID[NETDEV_TMS_FACE_RECORD_ID_LEN];      /* recodeing id */
    CHAR   szTollgateID[NETDEV_TMS_FACE_TOLLGATE_ID_LEN];  /* Bayonet number */
    CHAR   szPassTime[NETDEV_TMS_PASSTIME_LEN];            /* pass time */
    BOOL   bFinishFlag;                                    /* Analytic completion flag */
    BYTE   bRes[128];                                      /* Reserved field  Reserved */

}NETDEV_TMS_PERSION_INFO_S, *LPNETDEV_TMS_PERSION_INFO_S;

/**
 * @struct tagNETDEVFacePositionInfo
 * @brief Face position information
 * @attention
 */
typedef struct tagNETDEVFacePositionInfo
{
    INT32   dwTopLeftX;           /* top left corner X [0, 10000]  Upper left corner X [0, 10000]  */
    INT32   dwTopLeftY;           /* top left corner Y [0, 10000]  Upper left corner Y [0, 10000]  */
    INT32   dwBottomRightX;       /* lower right cornerX [0, 10000]  Lower right corner x [0, 10000] */
    INT32   dwBottomRightY;       /* lower right cornerY [0, 10000]  Lower right corner y [0, 10000] */
    BYTE     bRes[32];           /* Reserved field  Reserved */
}NETDEV_FACE_POSITION_INFO_S, *LPNETDEV_FACE_POSITION_INFO_S;

/**
 * @struct tagNETDEVTMSPersionFaceInfo
 * @brief Face Small graph info
 * @attention
 */
typedef struct tagNETDEVTMSPersionFaceInfo
{ 
    UINT32 udwFaceId;                                /* Face Id */
    NETDEV_FACE_POSITION_INFO_S stFacePos;           /* Face coordinates-screen coordinates normalized to 10: 0-10000; rectangle upper left and lower right: "138315282684" */
    BYTE   bRes[64];                                 /* Reserved field  Reserved */

}NETDEV_TMS_PERSION_FACE_INFO_S, *LPNETDEV_TMS_PERSION_FACE_INFO_S;

/**
 * @struct tagNETDEVTMSPersionPicInfo
 * @brief Face image detail parameters
 * @attention
 */
typedef struct tagNETDEVTMSPersionPicInfo
{
    UINT32 udwFaceId;                                    /* Face ID(Face Node resolves to this) will not be 0 */
    UINT32 udwPiclen;                                    /* Picture length in message information */
    CHAR   szPassTime[NETDEV_TMS_PASSTIME_LEN];          /* passtime */
    NETDEV_TMS_PERSION_FACE_INFO_S     stFaceInfo;       /* Face image information */
    NETDEV_TMS_PERSION_IMAGE_TYPE_E    enImgType;        /* Image type */
    NETDEV_TMS_PERSION_IMAGE_FORMAT_E  enImgFormat;      /* Image format */
    UINT32 udwImageWidth;                                /* image width*/
    UINT32 udwImageHeight;                               /* image height */ 
    BYTE   bRes[256];                                    /* Reserved field  Reserved*/
}NETDEV_TMS_PERSION_PIC_INFO_S, *LPNETDEV_TMS_PERSION_PIC_INFO_S;

/**
 * @struct tagNETDEVTMSFaceParseInfo
 * @brief Face recognition parsed information
 * @attention
 */
typedef struct tagNETDEVTMSFaceParseInfo
{ 
    UINT32 udwFaceNum;                                      /* Face number */
    UINT32 udwImageNum;                                     /* pstTMSPersonPicInfo number */
    CHAR *pcPktPicDataPtr;                                  /* Face picture message start pointer */
    NETDEV_TMS_PERSION_INFO_S stTMSPersonInfo;              /* Personnel information */
    LPNETDEV_TMS_PERSION_PIC_INFO_S pstTMSPersonPicInfo;    /* Face image detail parameters */
    BYTE     bRes[64];                                      /* Reserved field  Reserved */
}NETDEV_TMS_FACE_PARSE_INFO_S, *LPNETDEV_TMS_FACE_XML_INFO_S;

/**
 * @struct tagNETDEVTMSHeatMapXmlInfo
 * @brief Heat Graph message XML parsing Information
 * @attention
 */
typedef struct tagNETDEVTMSHeatMapXmlInfo
{
    CHAR  szDevID[NETDEV_TMS_HEAT_MAP_DEVID_LEN];                           /* Equipment number */
    CHAR  szRecordID[NETDEV_TMS_HEAT_MAP_RECORD_ID_LEN];                    /* Record ID number */
    CHAR  szCollectTime[NETDEV_TMS_HEAT_MAP_COllECT_TIME_LEN];              /* acquisition time  */
    INT32 dwColumns;                                                        /* Number of columns detected */
    INT32 dwRows;                                                           /* Number of rows detected */
    INT32 dwIntervalTime;                                                   /* Detection interval Unit min*/
    BYTE  bRes[256];                                                        /* Reserved field  Reserved */
}NETDEV_TMS_HEAT_MAP_XML_INFO_S, *LPNETDEV_TMS_HEAT_MAP_XML_INFO_S;

/**
 * @struct tagNETDEVTMSHeatMapPicInfo
 * @brief Heat map message region analysis information
 * @attention
 */
typedef struct tagNETDEVTMSHeatMapPicInfo
{
    UINT32  udwPicSize;                                                     /* area size */
    CHAR    *pcPicData;                                                     /* area data */
}NETDEV_TMS_HEAT_MAP_PIC_INFO_S,*LPNETDEV_TMS_HEAT_MAP_PIC_INFO_S;

/**
 * @struct tagNETDEVTMSHeatMapInfo
 * @brief Heat diagram message data information
 * @attention
 */
typedef struct tagNETDEVTMSHeatMapInfo
{
    UINT32                            udwPicNum;                                /*  Picture Number */
    NETDEV_TMS_HEAT_MAP_XML_INFO_S    stTmsXmlInfo;                             /*  XML Information */
    NETDEV_TMS_HEAT_MAP_PIC_INFO_S    stTmsPicInfo[NETDEV_TMS_PIC_COMMON_NUM];  /*  Picture Message */
}NETDEV_TMS_HEAT_MAP_INFO_S,*LPNETDEV_TMS_HEAT_MAP_INFO_S;

/**
 * @struct tagNETDEVTMSCarPlateXmlInfo
 * @brief XML parsing Information of license Plate recognition message
 * @attention
 */
typedef struct tagNETDEVTMSCarPlateXmlInfo
{
    CHAR szCamID[NETDEV_TMS_CAR_PLATE_CAMID_LEN];                               /* Bayonet camera number */
    CHAR szRecordID[NETDEV_TMS_CAR_PLATE_RECORDID_LEN];                         /* Record ID number */
    CHAR szTollgateID[NETDEV_TMS_CAR_PLATE_TOLLGATE_LEN];                       /* Bayonet number */
    CHAR szPassTime[NETDEV_TMS_CAR_PLATE_PASSTIME_LEN];                         /* After time */
    CHAR szLaneID[NETDEV_TMS_CAR_PLATE_LANEID_LEN];                             /* Lane number */
    CHAR szCarPlate[NETDEV_TMS_CAR_PLATE_CARPLATE_LEN];                         /* license plate */
    BYTE bRes[512];                                                             /* Reserved field  Reserved */

}NETDEV_TMS_CAR_PLATE_XML_INFO_S, *LPNETDEV_TMS_CAR_PLATE_XML_INFO_S;

/**
 * @struct tagNETDEVTMSCarPlatePicInfo
 * @brief License plate recognition message picture analysis information
 * @attention
 */
typedef struct tagNETDEVTMSCarPlatePicInfo
{
    UINT32  udwPicSize;                                                      /* pictuer size */
    CHAR    *pcPicData;                                                      /* pictuer message  */
}NETDEV_TMS_CAR_PLATE_PIC_INFO_S,*LPNETDEV_TMS_CAR_PLATE_PIC_INFO_S;

/**
 * @struct tagNETDEVTMSCarPlateInfo
 * @brief License plate recognition message data information
 * @attention
 */
typedef struct tagNETDEVTMSCarPlateInfo
{
    UINT32                             udwPicNum;                                   /*  Picture Number */
    NETDEV_TMS_CAR_PLATE_XML_INFO_S    stTmsXmlInfo;                                /*  XML Information */
    NETDEV_TMS_CAR_PLATE_PIC_INFO_S    stTmsPicInfo[NETDEV_TMS_PIC_COMMON_NUM];     /*  Picture Message */
}NETDEV_TMS_CAR_PLATE_INFO_S,*LPNETDEV_TMS_CAR_PLATE_INFO_S;

/**
* @struct tagNETDEVTMSFaceSnapshotPicInfo 
 * @brief Face capture information structure (for reporting)
 * @attention
 */
typedef struct tagNETDEVTMSFaceSnapshotPicInfo
{
    UINT32   udwFaceId;                                      /* face ID */
    CHAR    *pcPicBuff;                                      /* Picture cache£¬Base64 code(After using,need to free inside the SDK) */
    UINT32   udwPicBuffLen;                                  /* Picture cache length */
    NETDEV_TMS_PERSION_IMAGE_TYPE_E    enImgType;            /* Image type see NETDEV_TMS_PERSION_IMAGE_TYPE_E */
    NETDEV_TMS_PERSION_IMAGE_FORMAT_E  enImgFormat;          /* Image format see NETDEV_TMS_PERSION_IMAGE_FORMAT_E */
    NETDEV_FACE_POSITION_INFO_S        stFacePos;            /* Face coordinates-screen coordinates normalized to 10: 0-10000; rectangle upper left and lower right: "138315282684" */
    UINT32   udwImageWidth;                                  /* picture traverse */
    UINT32   udwImageHeight;                                 /* image height  */
    CHAR     szCamerID[NETDEV_TMS_CAMER_ID_LEN];             /* Camera No . */
    CHAR     szRecordID[NETDEV_TMS_FACE_RECORD_ID_LEN];      /* Record ID number */
    CHAR     szTollgateID[NETDEV_TMS_FACE_TOLLGATE_ID_LEN];  /* Bayonet number */
    CHAR     szPassTime[NETDEV_TMS_PASSTIME_LEN];            /* pass time,YYYYMMDDHHMMSSMMM£¬Time is set at 24 hours. The first group of MM is the month, the second group of MM is the minute, and the third group of MMM is millisecond. */
    BYTE     bRes[96];                                       /* Reserved field  Reserved */
}NETDEV_TMS_FACE_SNAPSHOT_PIC_INFO_S, *LPNETDEV_TMS_FACE_SNAPSHOT_PIC_INFO_S;



/************************************************************************/
/*                            XW                                        */
/************************************************************************/

/* Encrypted username length */
#define NETDEV_USER_NAME_ENCRYPT_LEN                    256

/* Encrypted password length */
#define NETDEV_PASSWORD_ENCRYPT_LEN                    256

/* Maximum number of supported video output standards */
#define NETDEV_VIDEO_FORMAT_MAX         32

/* Supported video output name length */
#define NETDEV_VIDEO_FORMAT_NAME_LEN    32

/* TV wall name length */
#define NETDEV_TVWALL_NAME_LEN          260

/* Maximum number of special output systems */
#define NETDEV_FORMAT_SPEC_MAX          256

/* Maximum number of special module boxes */
#define NETDEV_LED_SPEC_MAX             256

/* Output name length */
#define NETDEV_FORMAT_NAME_LEN          32

/* Maximum number of physical output ports */
#define NETDEV_VIDEO_OUT_MAX            64

/* Scene name length */
#define NETDEV_SCENE_NAME_LEN           260

/* Time string length */
#define NETDEV_TIME_LEN                 16

/* Window name length*/
#define NETDEV_WND_NAME_LEN             260

/* Maximum number of video sources in round patrol */
#define NETDEV_SEQUENCE_SRC_MAX         128

/* Virtual LED text lines */
#define NETDEV_TEXT_LINE                4

/* Virtual LED text content length*/
#define NETDEV_TEXT_LEN                 1024

/* Base map name length */
#define NETDEV_BMAP_NAME_LEN            256

/* Maximum length of base thumbnail data */
#define NETDEV_BMAP_THUMBNAL_LEN        256

/* Maximum configuration number of virtual LEDs in scenario
 */
#define NETDEV_VLED_MAX                 16

/* Maximum number of window configurations in the scenario */
#define NETDEV_WND_MAX                  128

/* Maximum number of output traffic configurations in the scenario */
#define NETDEV_VIDEO_MAX                16


/**
 * @struct tagNETDEVXWDelaySwitchPower
 * @brief Delay switch machine parameter information
 * @attention
 */
typedef struct tagNETDEVXWDelaySwitchPower
{
    UINT32            udwOperateType;                    /* Mode of operation 0: delayed boot (temporarily not implemented) 1: delayed shutdown*/
    UINT32            udwDelayTime;                      /* Delay shutdown time unit : min range 1 ~ 720*/

    BYTE              bRes[128];                         /* Reserved field  */
}NETDEV_XW_DELAY_SWITCH_POWER_S, *LPNETDEV_XW_DELAY_SWITCH_POWER_S;

/**
 * @struct tagNETDEVXWTimingSwitchPower
 * @brief Timing switch information
 * @attention
 */
typedef struct tagNETDEVXWTimingSwitchPower
{
    BOOL            bPowerOnEnabled;                     /* Enable (whether to turn on the timing boot function) 0: not enable 1: enable*/
    BOOL            bPowerOffEnabled;                    /* Enable (whether to turn on the timing shutdown function) 0: not enable 1: enable*/
    CHAR            szPowerOnTime[NETDEV_LEN_16];        /* Boot time format: HH: mm: SS (hour: minute: second >*/
    CHAR            szPowerOffTime[NETDEV_LEN_16];       /* Boot time format: HH: mm: SS (hour: minute: second >*/

    BYTE            bRes[128];                           /* Reserved field */
}NETDEV_XW_TIMING_SWITCH_POWER_S, *LPNETDEV_XW_TIMING_SWITCH_POWER_S;

/**
 * @struct tagNETDEVXWManualSwitchPower
 * @brief  Manual switch parameter information
 * @attention
 */
typedef struct tagNETDEVXWManualSwitchPower
{
    UINT32            udwOperateType;                    /* Mode of operation 0: boot 1: shut down*/

    BYTE               bRes[128];                        /* Reserved field */
}NETDEV_XW_MANUAL_SWITCH_POWER_S, *LPNETDEV_XW_MANUAL_SWITCH_POWER_S;

/**
 * @enum tagNETDEVXWScreenCtrlType
 * @brief Control mode type
 * @attention
 */
typedef enum tagNETDEVXWScreenCtrlType
{
    NETDEV_XW_SCREEN_CTRL_TYPE_TCP              = 0,          /* TCP */
    NETDEV_XW_SCREEN_CTRL_TYPE_UDP              = 1,          /* UDP */
    NETDEV_XW_SCREEN_CTRL_TYPE_COM              = 2,          /* serial port */

    NETDEV_XW_SCREEN_CTRL_TYPE_INVALID          = 0xFF        /* Invalid value */
}NETDEV_XW_SCREEN_CTRL_TYPE_S;

/**
 * @enum tagNETDEVXWScreenCtrlProtocolType
 * @brief Control protocol type
 * @attention
 */
typedef enum tagNETDEVXWScreenCtrlProtocolType
{
    NETDEV_XW_SCREEN_CTRL_PROTOCOL_UNV_LCD             = 0,          /* UNV LCD Scene Private protocol */
    NETDEV_XW_SCREEN_CTRL_PROTOCOL_UNV_LED             = 1,          /* UNV LED Scene Private protocol */
    NETDEV_XW_SCREEN_CTRL_PROTOCOL_MODBUS              = 2,          /* MODBUS */

    NETDEV_XW_SCREEN_CTRL_PROTOCOL_INVALID             = 0xFF        /* Invalid value */
}NETDEV_XW_SCREEN_CTRL_PROTOCOL_TYPE_S;

/**
 * @struct tagNETDEVXWScreenCtrlParamInfo
 * @brief Control parameter information of splicing screen
 * @attention
 */
typedef struct tagNETDEVXWScreenCtrlParamInfo
{
    UINT32            udwCtrlType;                              /* Control mode, seeNETDEV_XW_SCREEN_CTRL_TYPE_S */
    UINT32            udwAddressType;                           /* IP address type, see NETDEVSP ADDRDRTYPEAPE CtrlType 0 or 1, this node must be selected.*/
    CHAR              szIPV4Address[NETDEV_IP_LEN];             /* IPV4 address the node must be selected when the control mode is TCP or UDPand the IP address type is IPv4*/
    CHAR              szIPV6Address[NETDEV_IP_LEN];             /* IPV6 address the node must be selected when the control mode is TCP or UDPand the IP address type is IPv6*/
    CHAR              szDomainAddress[NETDEV_DOMAIN_LEN];       /* When the domain name is controlled by TCP or UDPand the IP address type is a domain name, the node must select*/
    UINT32            udwPort;                                  /* When the port is TCP or UDP, the node must be selected.*/
    UINT32            udwComID;                                 /* Serial port ID when the control mode is serial port, the node must be selected*/
    UINT32            udwProtocolType;                          /* Control protocol type. See synonyms atNETDEV_XW_SCREEN_CTRL_PROTOCOL_TYPE_S*/
    BYTE              bRes[256];                                /* Reserved field */
}NETDEV_XW_SCREEN_CTRL_PARAM_INFO_S, *LPNETDEV_XW_SCREEN_CTRL_PARAM_INFO_S;

/**
 * @enum tagNETDEVXWScreenZoomdType
 * @brief Screen amplification type
 * @attention
 */
typedef enum tagNETDEVXWScreenZoomdType
{
    NETDEV_XW_SCREEN_ZOOM_TYPE_PANE           = 0,           /*Scene amplify*/
    NETDEV_XW_SCREEN_ZOOM_TYPE_WIN            = 1,           /*Window amplify*/

    NETDEV_XW_SCREEN_ZOOM_TYPE_INVALID        = 0xFF         /* Invalid value */
}NETDEV_XW_SCREEN_ZOOM_TYPE_E;

/**
 * @enum tagNETDEVScreenZoomdMode
 * @brief Screen amplification mode
 * @attention
 */
typedef enum tagNETDEVXWScreenZoomdMode
{
    NETDEV_XW_SCREEN_ZOOM_MODE_OFF             = 0,          /*recover*/
    NETDEV_XW_SCREEN_ZOOM_MODE_ON              = 1,          /*amplify*/

    NETDEV_XW_SCREEN_ZOOM_MODE_INVALID         = 0xFF        /* Invalid value */
}NETDEV_XW_SCREEN_ZOOM_MODE_E;

/**
 * @struct tagNETDEVXWScreenZoomInfo
 * @brief Screen amplification information
 * @attention
 */
typedef struct tagNETDEVXWScreenZoomInfo
{
    UINT32            uOperatedType;                    /* Screen operation type, see NETDEV_XW_SCREEN_ZOOM_TYPE_E */
    UINT32            uOperatedMode;                    /* Screen mode, see NETDEV_XW_SCREEN_ZOOM_MODE_E */
    UINT32            uSplitScreenIndex;                /* Need to zoom in to full screen sequence number, effective when uOperated Type 0 & uOperated Mode = 1 */
}NETDEV_XW_SCREEN_ZOOM_INFO_S, *LPNETDEV_XW_SCREEN_ZOOM_INFO_S;

/* Coordinate information */
typedef struct tagNETDEVXWArea
{
    UINT32                          udwX;                        /* X position±ê */
    UINT32                          udwY;                        /* Y position */
}NETDEV_XW_COORD_S, *LPNETDEV_XW_COORD_S;

/* Position information relative to the TV wall */
typedef struct tagNETDEVXWVirtualLEDArea
{
    NETDEV_XW_COORD_S               stTopLeft;                   /* The point of coordinates in the upper left corner */
    NETDEV_XW_COORD_S               stBottomRight;               /* The coordinate point in the lower right corner */
}NETDEV_XW_AREA_S, *LPNETDEV_XW_AREA_S;

/* Resolution information */
typedef struct tagNETDEVXWVideoResolution
{
    UINT32                          udwWidth;                     /* width */
    UINT32                          udwHeight;                    /* high */
}NETDEV_XW_RESOLUTION_S, *LPNETDEV_XW_RESOLUTION_S;


/* Screen splitting ability */
typedef enum tagNETDEVPaneCap
{
    NETDEV_PANE_UNSUPPORT = 0,                                   /* nonsupport  */
    NETDEV_PANE_SAME_WND = 1,                                    /* Windows with the same size & position support for single monitor*/
    NETDEV_PANE_ANY_WND = 2                                      /* Support for split screens of arbitrary windows */
}NETDEV_XW_PANE_CAP_E;

/* Window roaming capability */
typedef enum tagNETDEVRoamingCap
{
    NETDEV_ROAMING_UNSUPPORT = 0,                                /* nonsupport  */
    NETDEV_ROAMING_SINGLE_WND = 1,                               /* Support for single split window roaming */
    NETDEV_ROAMING_PANE_WND = 2                                  /* Support for multi-screen window roaming */
}NETDEV_XW_ROAMING_CAP_E;

/* Window creating ability */
typedef enum tagNETDEVWndCap
{
    NETDEV_WINDOWS_UNSUPPORT  = 0,                               /* nonsupport  */
    NETDEV_WINDOWS_SINGLE_WND = 1,                               /* Windows that support the same size and location of a single monitor */
    NETDEV_WINDOWS_MULTI_WND  = 2,                               /* Support for multiple monitors, full window windows */
    NETDEV_WINDOWS_ANY_WND    = 3,                               /* Arbitrarily open a window */
    NETDEV_WINDOWS_INVALID                                       
}NETDEV_XW_WND_CAP_E;

/* "XW"Equipment TV wall capability set */
typedef struct tagNETDEVXWTVWallCap
{
    UINT32                          udwNumMax;                   /* Maximum number of television walls */
    UINT32                          udwSceneMax;                 /* Maximum number of scenes on a single TV wall */
    UINT32                          udwRowMax;                   /* Maximum number of rows for a single television wall */
    UINT32                          udwColumnMax;                /* Maximum number of columns for a single television wall */
    BYTE                            byRes[64];                   /* Reserved field  */
}NETDEV_XW_TVWALL_CAP_S, *LPNETDEV_XW_TVWALL_CAP_S;

/* "XW"XWFormatList */
typedef struct tagNETDEVXWFormatList
{
    UINT32                          udwSize;                     /* Number of supported video output formats */
    UINT32                          audwName[NETDEV_VIDEO_FORMAT_MAX]; /* Supported video output system NETDEV_VIDEO_FORMAT_E */
    BYTE                            byRes[64];                   /* Reserved field  */
}NETDEV_XW_FORMAT_LIST_S, *LPNETDEV_XW_FORMAT_LIST_S;

/* "XW"Device window capability set */
typedef struct tagNETDEVXWWndCap
{
    UINT32                          udwWndMaxPerScene;           /* Maximum number of windows for a single scenario */
    UINT32                          udwAreaMax;                  /* Window area of single physical outlet */
    UINT32                          udwPaneMax;                  /* Maximum number of screens in a single window */
    NETDEV_XW_RESOLUTION_S            stResolutionMin;             /* Minimum window pixels */
    BYTE                            byRes[64];                   /* Reserved field  */
}NETDEV_XW_Wnd_CAP_S, *LPNETDEV_XW_Wnd_CAP_S;

/* "XW"Equipment base map capability set */
typedef struct tagNETDEVXWBaseMapCap
{
    UINT32                          udwNumMax;                   /* "XW"Maximum equipment base number */
    UINT32                          udwNumMaxPerScene;           /* Maximum number of background maps for a single scene */
    UINT32                          udwBytesMax;                 /* The maximum number of bytes in a single base. */
    NETDEV_XW_RESOLUTION_S            stResolutionMax;             /* Background maximum resolution */
    BYTE                            byRes[64];                   /* Reserved field  */
}NETDEV_XW_BaseMap_CAP_S, *LPNETDEV_XW_BaseMap_CAP_S;

/* "XW"Virtual LED capability set */
typedef struct tagNETDEVXWVirtualLEDCap
{
    UINT32                          udwNumMaxPerScene;           /* Maximum number of virtual LEDs in single scenes */
    UINT32                          udwRowMax;                   /* Single virtual LED maximum number of rows. */
    UINT32                          udwCharMaxPerRow;            /* The maximum number of single-line words. */
    BYTE                            byRes[64];                   /* Reserved field  */
}NETDEV_XW_VIRTUALLED_CAP_S, *LPNETDEV_XW_VIRTUALLED_CAP_S;

/* "XW" Equipment wheel patrol capability set */
typedef struct tagNETDEVXWSequenceCap
{
    UINT32                          udwSrcNumMax;                /* Maximum number of resources per rotation */
    UINT32                          udwPaneNumMax;               /* Maximum number of single screen wheel patrol */
    UINT32                          udwWndNumMax;                /* Maximum number of single window wheel rounds */
    UINT32                          udwSceneNumMax;              /* Maximum number of scene rounds */
    BYTE                            byRes[64];                   /* Reserved field  */
}NETDEV_XW_SEQUENCE_CAP_S, *LPNETDEV_XW_SEQUENCE_CAP_S;

/* "XW" support splitting*/
typedef struct tagNETDEVXWPaneType
{
    UINT32                          udwSize;                     /* Supported split screen number */
    UINT32                          *pudwPaneType;               /* Supported split screen type NETDEV_XW_LAYOUT_NUM_E */
}NETDEV_XW_PANE_TYPE_S, *LPNETDEV_XW_PANE_TYPE_S;

/* "XW" Equipment other capability set */
typedef struct tagNETDEVXWSupportCap
{
    UINT32                          udwPane;                      /* Screen splitting ability NETDEV_XW_PANE_CAP_E*/
    UINT32                          udwWndRoaming;                /* Window roaming capability NETDEV_XW_ROAMING_CAP_E*/
    UINT32                          udwWnd;                      /* creat window capability NETDEV_XW_WND_CAP_E*/        
    BOOL                            bBackToShow;                 /* Echo capability 0: not supported 1: suppor */
    BOOL                            bWndOverlay;                 /* Window overlay ability 0: not supported 1: support */
    BOOL                            bTopWndSetTransp;            /* Top level window transparency 0: no support 1: support */
    UINT32                          udwMaxWinNumPerScreen;       /* The maximum number of windows supported by a single physical output */
    NETDEV_XW_PANE_TYPE_S           stPaneType;                  /* Supported screen */
    BYTE                            byRes[64];                   /* Reserved field  */
}NETDEV_XW_SUPPORT_CAP_S, *LPNETDEV_XW_SUPPORT_CAP_S;

/* "XW" Equipment capability set */
typedef struct tagNETDEVXWCAPINFO
{
    NETDEV_XW_TVWALL_CAP_S          stTVWall;                    /* TV wall capability set */
    NETDEV_XW_FORMAT_LIST_S         stVideoFormats;              /* Video output format list */
    NETDEV_XW_Wnd_CAP_S             stWnd;                       /* Window capability set */
    NETDEV_XW_BaseMap_CAP_S         stBaseMap;                   /* Base map capability set */
    NETDEV_XW_VIRTUALLED_CAP_S      stVirtualLED;                /* Virtual LED Capability Set */
    NETDEV_XW_SEQUENCE_CAP_S        stSequence;                  /* Wheel patrol capability set */
    NETDEV_XW_SUPPORT_CAP_S         stSupport;                   /* Characteristic capability set */
    BOOL                            bIsRSASupported;             /* Whether to use RSA encryption */
    BYTE                            byRes[64];                   /* Reserved field  */
}NETDEV_XW_CAP_INFO_S, *LPNETDEV_XW_CAP_INFO_S;


/* TV wall screen configuration */
typedef struct tagNETDEVTVWallScreen
{
    UINT32                          udwRowNum;                   /* TVWall Number of row units */
    UINT32                          udwColNum;                   /* TVWall Number of Column  units */
    UINT32                          udwFormat;                    /* Screen output system NETDEV_VIDEO_FORMAT_E */
    CHAR                            szFormat[NETDEV_FORMAT_NAME_LEN]; /* No configuration Screen output system */
    NETDEV_XW_RESOLUTION_S            stResolution;                /* Screen pixel */
    BYTE                            byRes[64];                   /* Reserved field  */
}NETDEV_TVWALL_SCREEN_S, *LPNETDEV_TVWALL_SCREEN_S;

/* Special output configuration */
typedef struct tagNETDEVTVWallFORMATSPECList
{
    UINT32                          udwScreenID;                      /* Screen serial number(Starting from 1)  */
    UINT32                          udwFormat;                        /* Screen output system NETDEV_VIDEO_FORMAT_E */
    CHAR                            szFormat[NETDEV_FORMAT_NAME_LEN]; /* No configuration Screen output system */
    BYTE                            byRes[32];                   /* Reserved field  */
}NETDEV_TVWALL_FORMAT_SPEC_S, *LPNETDEV_TVWALL_FORMAT_SPEC_S;

/* Special module box configuration */
typedef struct tagNETDEVTVWallLEDSPECList
{
    UINT32                          udwScreenID;                 /* Screen serial number(Starting from 1) */
    NETDEV_XW_RESOLUTION_S          stResolution;                /* Screen pixel */
    BYTE                            byRes[32];                   /* Reserved field  */
}NETDEV_TVWALL_LED_SPEC_S, *LPNETDEV_TVWALL_LED_SPEC_S;

/* Physical output port configuration */
typedef struct tagNETDEVTVWallVOUTList
{
    UINT32                          udwScreenID;                 /* Screen serial number(Starting from 1) */
    UINT32                          udwVideoOutID;               /* Physical output port ID */
    BYTE                            byRes[32];                   /* Reserved field  */
}NETDEV_TVWALL_VIDED_OUT_S, *LPNETDEV_TVWALL_VIDED_OUT_S;

/* TV wall screen configuration */
typedef struct tagNETDEVXWTVWallCfg
{
    UINT32                          udwTVWallID;                            /* TVWall ID */
    CHAR                            szName[NETDEV_TVWALL_NAME_LEN];           /* TVWall name */
    NETDEV_TVWALL_SCREEN_S            stScreenInfo;                           /* TV wall screen configuration */
    UINT32                          udwFormatSpecNum;                       /* Special output number */
    NETDEV_TVWALL_FORMAT_SPEC_S       astFormatSpec[NETDEV_FORMAT_SPEC_MAX];     /* Special output configuration */
    UINT32                          udwLedSpecNum;                          /* Special module box number */
    NETDEV_TVWALL_LED_SPEC_S          astLedSpec[NETDEV_LED_SPEC_MAX];          /* Special module box configuration */
    UINT32                          udwVideoOutNum;                         /* Physical output port number */
    NETDEV_TVWALL_VIDED_OUT_S         astVideoOut[NETDEV_VIDEO_OUT_MAX];        /* Physical output port configuration */
    BYTE                            byRes[256];                            /* Reserved field  */
}NETDEV_XW_TVWALL_CFG_S, *LPNETDEV_XW_TVWALL_CFG_S;


/* Scene basic information */
typedef struct tagNETDEVXWSceneInfoBase
{
    UINT32                          udwSceneID;                             /* Scene ID */
    CHAR                            szName[NETDEV_SCENE_NAME_LEN];          /* Scene name */
    BYTE                            byRes[32];                   /* Reserved field  */
}NETDEV_XW_SCENE_INFO_BASE_S, *LPNETDEV_XW_SCENE_INFO_BASE_S;

/* Scene brief information */
typedef struct tagNETDEVXWSceneInfoShort
{
    NETDEV_XW_SCENE_INFO_BASE_S       stSceneBase;                            /* S */
    UINT32                          udwIsCurrent;                             /* Is the current scenario   0: Non-current scenario 1: current scenario */
    BYTE                            byRes[64];                   /* Reserved field  */
}NETDEV_XW_SCENE_INFO_SHORT_S, *LPNETDEV_XW_SCENE_INFO_SHORT_S;
/* day of the week */
typedef enum tagNETDEVWeekInfo
{
    NETDEV_LAPI_WEEK_MONDAY                  = 1,                  /*   Monday */
    NETDEV_LAPI_WEEK_TUESDAY                 = 2,                  /*   Tuesday */
    NETDEV_LAPI_WEEK_WEDNESDAY               = 3,                  /*   Wednesday */
    NETDEV_LAPI_WEEK_THURSDAY                = 4,                  /*   Thursday */
    NETDEV_LAPI_WEEK_FRIDAY                  = 5,                  /*   Friday */
    NETDEV_LAPI_WEEK_SATURDAY                = 6,                  /*   Saturday */
    NETDEV_LAPI_WEEK_SUNDAY                  = 7,                  /*   Sunday */
    NETDEV_LAPI_WEEK_HOLIDAY                 = 8,                  /*   Holiday */
    NETDEV_LAPI_WEEK_INVALID                 = 0xff                /*   Invalid value */
}NETDEV_LAPI_WEEK_INFO;

/* plan info */

typedef struct tagNETDEVXWCfgTime
{
    CHAR                            szBeginTime[NETDEV_TIME_LEN];  /* stat time   if all day please write 00:00:00 */
    CHAR                            szEndTime[NETDEV_TIME_LEN];    /* over time   if all day please write 24:00:00 */
    UINT32                          udwSceneID;                  /*scene  ID */
}NETDEV_XW_CFG_TIME_S, *LPNETDEV_XW_CFG_TIME_S;

/* plan of week info */
typedef struct tagNETDEVXWPlanCfg
{
    UINT32                          udwDayOfWeek;                       /* day of week   see NETDEV_WEEK_INFO */
    UINT32                          udwSize;                            /* Time period number */
    NETDEV_XW_CFG_TIME_S             stTime[NETDEV_PLAN_SECTION_NUM];   /* Time period information */
}NETDEV_XW_PLAN_CFG_S, *LPNETDEV_XW_PLAN_CFG_S;

/* Scenario planning configuration */
typedef struct tagNETDEVXWScenePlan
{
    UINT32                          udwPlanID;                        /* plane ID */
    BOOL                            bIsEnabled;                       /* plane is used or not*/
    NETDEV_XW_PLAN_CFG_S            astConfig[NETDEV_PLAN_NUM_AWEEK]; /* plan configuration info  */
    BYTE                            byRes[64];                        /* Reserved field  */
}NETDEV_XW_SCENE_PLAN_S, *LPNETDEV_XW_SCENE_PLAN_S;



/* the scene window modifies the optional command word */
typedef enum tagNETDEVWndCommond
{
    NETDEV_WND_PANE_MOD             = 0x0001,                       /*  udwPaneMod */
    NETDEV_WND_LAYER                = 0x0002,                       /*  udwLayer */
    NETDEV_WND_TRANSPARENCY         = 0x0004,                       /*  udwTransparency */
    NETDEV_WND_AREA                 = 0x0008,                        /* positional information stArea */
    NETDEV_WND_NAME                 = 0x0010,                         /* window name */
    NETDEV_WND_ALL                  =0x00FF                          /* configuration all */
} NETDEV_XW_WND_CMD;

/* Scene window information */
typedef struct tagNETDEVXWSceneWndInfo
{
    UINT32                          udwWndID;                       /* window ID */
    UINT32                          udwModifyCmd;                   /* Modify optional command words NETDEV_XW_WND_CMD */
    CHAR                            szWndName[NETDEV_WND_NAME_LEN]; /* window name */
    UINT32                          udwPaneMod;                     /* Split screen mode, default 1 split screen NETDEV_XW_LAYOUT_NUM_E */
    UINT32                          udwLayer;                       /* Layer, large number on top*/
    UINT32                          udwTransparency;                /* Transparency: other values for default 0 opaque 100 full transparency 0-100 indicate partial transparency*/
    NETDEV_XW_AREA_S                stArea;                         /* positional information */
    BYTE                            byRes[64 ];                   /* Reserved field  */
}NETDEV_XW_SCENE_WND_INFO_S, *LPNETDEV_XW_SCENE_WND_INFO_S;


/* coded format */
typedef enum tagNETDEVVideoEncoding
{
    NETDEV_VIDEOENCODING_H264 = 0,                               /* H264 */
    NETDEV_VIDEOENCODING_H265 = 1,                               /* H265 */
    NETDEV_VIDEOENCODING_MPEG4 = 2,                             /* MPEG4 */
    NETDEV_VIDEOENCODING_MPEG2 = 3,                             /* MPEG2 */
    NETDEV_VIDEOENCODING_MJPEG = 4                             /* MJPEG */
}NETDEV_XW_VIDEOENCODING_E;

/*Encryption type*/
typedef enum tagNetDevAuthModel
{
     NETDEV_AM_RSA = 0,                                                            /* RSA encryption */
     NETDEV_AM_PRI      = 1,                                                            /* 通用字符串加�?*/
     NETDEV_AM_RSA_E16  = 2                                                             /* RSA加密，E公钥�?6进制 */
}NETDEV_XW_AUTH_MODEL_E;                                                                

typedef struct tagNETDEVAuthentication
{
    BOOL                            bIsNeedAuthentication;                   /* authentication be used or not*/
    CHAR                            szUserName[NETDEV_USER_NAME_ENCRYPT_LEN];/* Video source user name */
    CHAR                            szPassword[NETDEV_PASSWORD_ENCRYPT_LEN]; /* Video source cipher */
    NETDEV_XW_AUTH_MODEL_E            enAuthModel;                           /* Encryption type see #NETDEV_XW_AUTH_MODEL_E(Reserved field Temporary suspension) */
    BYTE                            byRes[64];                               /* Reserved field  */
}NETDEV_AUTHENTICATION_S, *LPNETDEV_AUTHENTICATION_S;

/* Remote playback Video source */
typedef struct tagNETDEVXWChannels
{
    UINT32                          udwVideoInID;                       /* Video source ID */
    CHAR                            szReplayURL[NETDEV_MAX_URL_LEN];      /* play back URL */
    NETDEV_AUTHENTICATION_S           stAuthentication;                   /* Authentication information */
    UINT32                          udwTransProtocol;                   /* transport protocol NETDEV_LAPI_TRANS_PROTOCOL_E  No configuration required for local input */
    UINT32                          udwMulticast;                       /* Single multicast NETDEV_STREAM_TYPE_E  No configuration required for local input */
    INT64                           tBeginTime;                         /* start time */
    INT64                           tEndTime;                           /* over time */
    BYTE                            byRes[64];                          /* Reserved field  */
}NETDEV_XW_CHANNELS_S, *LPNETDEV_XW_CHANNELS_S;

/* transport protocol */
typedef enum tagNETDEVLapiTransProtocol
{
    NETDEV_LAPI_TRANS_PROTOCOL_TCP = 0,              /* TCP */
    NETDEV_LAPI_TRANS_PROTOCOL_UDP = 1             /* UDP */
}NETDEV_LAPI_TRANS_PROTOCOL_E;

/**
* @enum tagNETDEVStreamType
* @brief transport protocol Enumeration definition
* @attention  None
*/
typedef enum tagNETDEVTransProtocol
{
    NETDEV_TRANS_PROTOCOL_TCP = 0,              /* TCP */
    NETDEV_TRANS_PROTOCOL_UDP = 1             /* UDP */
}NETDEV_TRANS_PROTOCOL_E;

/**
 * @enum tagNETDEVDecodeType
 * @brief Decoding type
 * @attention
 */
typedef enum tagNETDEVDecodeType
{
    NETDEV_DECODE_TYPE_CLIENT = 0,                               /* Decoder as client Active decoding*/
    NETDEV_DECODE_TYPE_SERVER = 1                                /* decoder as the server. Passive decoding*/
    
}NETDEV_XW_DECODE_TYPE_E;

/* Live service type */
typedef enum tagNETDEVRealPlayType
{
    NETDEV_TYPE_NORMAL = 0,                                      /* Default common live */
    NETDEV_TYPE_ALARM = 1,                                       /* Alarm linkage live */
    NETDEV_TYPE_LOCAL = 2                                        /* Local live */
}NETDEV_XW_REALPLAY_TYPE_E;

/* "XW" Device ID information*/
typedef struct tagNETDEVXWDisplayerID
{
    UINT32                           udwTVWallID;                  /* TVWall ID */
    UINT32                           udwWndID;                     /* Window ID */
    UINT32                           udwPaneID;                    /* Screen sequence number */
    BYTE                            byRes[16];                   /* Reserved field  */
}NETDEV_XW_DISPLAYER_ID_S, *LPNETDEV_XW_DISPLAYER_ID_S;

/* Remote live video source basic information */
typedef struct tagNETDEVXWVideoSourceBase
{
    UINT32                          udwVideoInID;                       /* Video source ID */
    CHAR                            szRealplayURL[NETDEV_MAX_URL_LEN];  /* Media stream URL  No configuration required for local input */
    UINT32                          udwStreamID;                        /* Media stream serial number */
    NETDEV_AUTHENTICATION_S           stAuthentication;                   /* Authentication information */
    UINT32                          udwTransProtocol;                   /* transport protocols NETDEV_LAPI_TRANS_PROTOCOL_E  No configuration required for local input */
    UINT32                          udwMulticast;                       /* Single multicast NETDEV_STREAM_TYPE_E */
    UINT32                          udwType;                            /* real play type  see  NETDEV_XW_REALPLAY_TYPE_E */
    BYTE                            byRes[32];                         /* Reserved field  */
}NETDEV_XW_VIDEO_SOURCE_BASE_S, *LPNETDEV_XW_VIDEO_SOURCE_BASE_S;

/* Remote live video source information */
typedef struct tagNETDEVXWVideoSource
{
    NETDEV_XW_DISPLAYER_ID_S          stDisplayerID;                      /* Device ID information */
    UINT32                          udwVideoInID;                       /* Video source ID*/
    CHAR                            szRealplayURL[NETDEV_MAX_URL_LEN];    /* No configuration is required when media stream URLs are entered locally*/
    UINT32                          udwStreamID;                        /* Media stream serial number */
    NETDEV_AUTHENTICATION_S           stAuthentication;                   /* Authentication information */
    UINT32                          udwTransProtocol;                   /* transport protocols NETDEV_LAPI_TRANS_PROTOCOL_E */
    UINT32                          udwMulticast;                       /* Single multicast NETDEV_STREAM_TYPE_E */
    UINT32                          udwType;                           /* real play type see  NETDEV_XW_REALPLAY_TYPE_E */
    UINT32                          udwDecodeType;                     /* decoding type  see NETDEV_XW_DECODE_TYPE_E */
    BYTE                            byRes[64];                         /* Reserved field  */
}NETDEV_XW_VIDEO_SOURCE_S, *LPNETDEV_XW_VIDEO_SOURCE_S;

/* Playback control type */
typedef enum tagNETDEVCtrlType
{
    NETDEV_CTRL_TYPE_SPEED = 1,                                     /* Playback speed */ 
    NETDEV_CTRL_TYPE_INVALID
}NETDEV_XW_CTRL_TYPE_E;

/* Playback control information */
typedef struct tagNETDEVXWPlaybackParam
{
    UINT32                          udwTaskNo;                   /* Playback service number */
    UINT32                          udwControlType;              /* Playback control type NETDEV_XW_CTRL_TYPE_E */
    UINT32                          udwControlParam;             /* The specific values of control, such as fast speed, */
    BYTE                            byRes[64];                  /* Reserved field  */
}NETDEV_XW_PLAYBACK_PARAM_S, *LPNETDEV_XW_PLAYBACK_PARAM_S;

/* Video Source Information for camera Service */
typedef struct tagNETDEVXWVideoInSource
{
    UINT32                          udwVideoInChlID;             /* Video source ID */
    UINT32                          udwStreamID;                 /* Media stream serial number */
    CHAR                            szURL[NETDEV_MAX_URL_LEN];    /* stream URL */
    NETDEV_AUTHENTICATION_S           stAuthentication;            /* Authentication information */
    UINT32                          udwSeqIntervalSec;           /* Wheel interval, unit: seconds to be configured only if it is a round patrol. */
    UINT32                          udwPreset;                  /* the preset serial number only needs to be configured if it is a wheel patrol * */
    BYTE                            byRes[32];                  /* Reserved field  */
}NETDEV_XW_VIDEO_IN_SOURCE_S, *LPNETDEV_XW_VIDEO_IN_SOURCE_S;

/* Camera service information */
typedef struct tagNETDEVXWVideoInChannelInfo
{
    UINT32                          udwWndID;                                   /* Window ID */
    UINT32                          udwPaneID;                                  /* Split screen serial number 0 indicates window rounds*/
    UINT32                          udwSourceSize;                              /* Number of video sources in camera service */
    NETDEV_XW_VIDEO_IN_SOURCE_S     astVideoInSource[NETDEV_SEQUENCE_SRC_MAX];        /* Video Source Information in camera Service */
    BYTE                            byRes[32];                                  /* Reserved field  */
}NETDEV_XW_VIDEO_IN_CHANNEL_INFO_S, *LPNETDEV_XW_VIDEO_IN_CHANNEL_INFO_S;

/* Virtual LED type */
typedef enum tagNETDEVLEDType
{
    NETDEV_LED_TYPE_STRING = 0                                   /* Hollerith type */
}NETDEV_XW_LED_TYPE_E;

/* Virtual LED font */
typedef enum tagNETDEVLEDFontFormat
{
    NETDEV_LED_FONT_SONG          = 0,                             /* Song typeface */
    NETDEV_LED_FONT_FORMAT_SIMHEI = 1,                             /* black body */
    NETDEV_LED_FONT_FORMAT_KAITI  = 2,                             /* regular script */
    NETDEV_LED_FONT_FORMAT_Arial  = 3                              /* Arial */
}NETDEV_XW_LED_FONT_FORMAT_E;
/* Virtual LED font size */
typedef enum tagNETDEVXWLEDFontSize
{
    NETDEV_LED_FONT_SIZE_48X48      = 0,                            /* 48X48 lattice  */
    NETDEV_LED_FONT_SIZE_64X64      = 1,                            /* 64X64 lattice  */
    NETDEV_LED_FONT_SIZE_96X96      = 2,                            /* 96X96 lattice  */
    NETDEV_LED_FONT_SIZE_128X128    = 3,                            /* 128X128 lattice  */
    NETDEV_LED_FONT_SIZE_192X192    = 4,                            /* 192X192 lattice  */
    NETDEV_LED_FONT_SIZE_256X256    = 5,                            /* 256X256 lattice  */
    NETDEV_LED_FONT_SIZE_512X512    = 6,                            /* 512X512 lattice  */
    NETDEV_FONT_SIZE_SELF_ADAPTION  = 7                             /* self-adaption */
}NETDEV_XW_LED_FONT_SIZE_E;

/*  Virtual LED word spacing 1 Chinese 2 characters*/
typedef enum tagNETDEVXWLEDFontGap
{
    NETDEV_LED_FONT_GAP_NORMAL      = 0,        /* Normal spacing */
    NETDEV_LED_FONT_GAP_ONE    		= 1,        /* Interval of 1 characters */
    NETDEV_LED_FONT_GAP_TWO         = 2,        /* Interval of 2 characters */
    NETDEV_LED_FONT_GAP_THREE    	= 3,        /* Interval of 3 characters */
    NETDEV_LED_FONT_GAP_FOUR       	= 4,         /* Interval of 4 characters */
    NETDEV_LED_FONT_GAP_INVALID    	= 0xFFFF    /* Invalid value */
}NETDEV_XW_LED_FONT_GAP_E;

/* Text rool alignment */
typedef enum tagNETDEVLEDScrollingMode
{
    NETDEV_LED_SCROLL_STATIC            = 0,        /* static */
    NETDEV_LED_SCROLL_RIGHT_TO_LEFT     = 1,        /* right-to-left */
    NETDEV_LED_SCROLL_LEFT_TO_RIGHT     = 2,        /* from left to right */
    NETDEV_LED_SCROLL_BOTTOM_TO_TOP     = 3,        /* from bottom to top */
    NETDEV_LED_SCROLL_TOP_TO_BOTTOM     = 4         /* from top to bottom */
}NETDEV_XW_LED_SCROLLING_MODE_E;

/* Text vertical alignment */
typedef enum tagNETDEVVerticalAlignMode
{
    NETDEV_VERTICAL_ALIGN_TOP           = 0,        /*  flush lef */
    NETDEV_VERTICAL_ALIGN_MIDDLE        = 1,       /* align center */
    NETDEV_VERTICAL_ALIGN_BOTTOM        = 2           /*  right alignment*/
}NETDEV_XW_VERTICAL_ALIGN_MODE_E;

/* Text horizontal alignment */
typedef enum tagNETDEVHorizontalAlignMode
{
    NETDEV_HORIZONTAL_ALIGN_LEFT        = 0,        /*  flush lef */
    NETDEV_HORIZONTAL_ALIGN_MIDDLE      = 1,        /* align center */
    NETDEV_HORIZONTAL_ALIGN_RIGHT       = 2         /*  right alignment*/
}NETDEV_XW_HORIZONTAL_ALIGN_MODE_E;

/* Virtual LED modifies optional command words*/
typedef enum tagNETDEVLedCmd
{
    NETDEV_LED_ENABLE               = 0x0001,                   /*  udwEnable */
    NETDEV_LED_TYPE                 = 0x0002,                   /*  dwType */
    NETDEV_LED_AREA                 = 0x0004,                   /*  stArea */
    NETDEV_LED_BACKGROUND           = 0x0008,                   /*  stBackground */
    NETDEV_LED_FONTINFO             = 0x0010,                   /*  stFontInfo */
    NETDEV_LED_TEXT                 = 0x0020,                   /*  udwTestLineNum szText*/
    NETDEV_LED_ALL                  = 0x00FF                    /*  all*/
} NETDEV_XW_LED_CMD_E;

/* back ground */
typedef struct tagNETDEVXWBackground
{
    UINT32      udwTransparency;             /* Transparency 0-full transparency default 100-opaque*/
    UINT32      udwBaseColor;                /*Color RGB: 0xABCDEF AB means R00FFFFF CD means G00FFFFFFEF means B00FFFFF; default: 0xFFFFFFF (white)*/
    BYTE       byRes[16];                   /* Reserved field  */
}NETDEV_XW_BACKGROUND_S, *LPNETDEV_XW_BACKGROUND_S;

/* * text message description * */
typedef struct tagNETDEVXWFontInfo
{
    UINT32  udwFont;                        /* script NETDEV_XW_LED_FONT_FORMAT_E */
    UINT32  udwSize;                        /*  font size NETDEV_XW_LED_FONT_SIZE_E  */
    UINT32  udwReferFontSize;               /* Reference font size When udwSize selects adaptively, the field must have a range of values referenced to the size field */ 
    UINT32  udwGap;                         /* word space £»  NETDEV_XW_LED_FONT_GAP_E */
    UINT32  udwHorizontalAlign;             /* Horizontal alignment mode NETDEV_XW_HORIZONTAL_ALIGN_MODE_E */
    UINT32  udwVerticalAlign;               /* Vertical alignment mode NETDEV_XW_VERTICAL_ALIGN_MODE_E */
    UINT32  udwColor;                       /* Color RGB: 0xABCDEF AB means R00FFFFF CD means G00FFFFFFEF means B00FFFFF; default: 0xFFFFFFF (white)*/
    UINT32  udwScrollMode;                  /*  Text scrolling mode NETDEV_XW_LED_SCROLLING_MODE_E  */
    UINT32  udwScrollRateSec;               /* ext scrolling mode,*/
    BYTE   byRes[32];                       /* Reserved field  */
}NETDEV_XW_FONT_INFO_S, *LPNETDEV_XW_FONT_INFO_S;/* Virtual LED information */
typedef struct tagNETDEVXWVirtualLEDInfo
{
    UINT32                  udwLEDID;                    /* Virtual LED enabled */
    UINT32                  udwModifyCmd;                /* Virtual LED enabled NETDEV_XW_LED_CMD_E */
    UINT32                  udwEnable;                   /* Virtual LED enabled  */
    UINT32                  udwType;                     /* Virtual led type  NETDEV_XW_LED_TYPE_E */
    NETDEV_XW_AREA_S        stArea;                      /* Location Information of Virtual LED */
    NETDEV_XW_BACKGROUND_S  stBackground;                /* background */
    NETDEV_XW_FONT_INFO_S   stFontInfo;                  /* Text information description */
    CHAR                   szText[NETDEV_TEXT_LEN];     /* Text content */
    BYTE                   byRes[32];                   /* Reserved field */
}NETDEV_XW_VIRTUAL_LED_INFO_S, *LPNETDEV_XW_VIRTUAL_LED_INFO_S;

/* Base map type */
typedef enum tagNETDEVBaseType
{
    NETDEV_BASE_TYPE_JPEG = 1                                    /* JPEG type */
}NETDEV_XW_BASE_TYPE_E;

/*******************************Batch switch window Begin*****************************/
/**
* @struct tagNETDEVXWSenceBatchWnd
* @brief Batch windowing scene window information
* @attention
*/
typedef struct tagNETDEVXWSenceBatchWnd
{
    UINT32                         udwReqSeq;                        /* Request data serial number */
    NETDEV_XW_SCENE_WND_INFO_S     stSenceWndInfo;                   /* window message  */
    BYTE                            byRes[32];                   /* Reserved field */
}NETDEV_XW_SENCE_BATCH_WND_S, *LPNETDEV_XW_SENCE_BATCH_WND_S;


/**
* @struct tagNETDEVXWSenceBatchWndList
* @brief List of window information for batch window opening scenarios
* @attention
*/
typedef struct tagNETDEVXWSenceBatchWndList
{
    UINT32                           udwSize;                           /* Number of windows */
    LPNETDEV_XW_SENCE_BATCH_WND_S      pstSenceBatchWndInfo;                /* Window information, dynamically applying for memory according to the number of windows */
    BYTE                            byRes[32];                          /* Reserved field  */
}NETDEV_XW_SENCE_BATCH_WND_LIST_S, *LPNETDEV_XW_SENCE_BATCH_WND_LIST_S;

/**
* @struct tagNETDEVXWSenceBatchResultWnd
* @brief Batch open window scene window return information
* @attention
*/
typedef struct tagNETDEVXWSenceBatchResultWnd
{
    UINT32                       udwReqSeq;                            /* Request data serial number */
    UINT32                       udwResuleCode;                        /* Return error code */
    UINT32                       udwWinID;                             /* window ID */
}NETDEV_XW_SENCE_BATCH_RESULT_WND_S, *LPNETDEV_XW_SENCE_BATCH_RESULT_WND_S;

/**
* @struct tagNETDEVXWSenceBatchResultList
* @brief  return information of batch creat scence window
* @attention
*/
typedef struct tagNETDEVXWSenceBatchResultList
{
    UINT32                                 udwSize;                           /* window number */
    UINT32                                 udwLastChange;                     /* Abstract word */
    LPNETDEV_XW_SENCE_BATCH_RESULT_WND_S   pstSenceBatchWndInfo;              /* Wheel interval unit second */
    BYTE                                byRes[32];                       /* Reserved field  */
}NETDEV_XW_SENCE_BATCH_RESULT_LIST_S, *LPNETDEV_XW_SENCE_BATCH_RESULT_LIST_S;

/* sequence resource information */
typedef struct tagNETDEVXWSequenceSource
{
    UINT32                          udwInterval;                               /* polling interval unit: sec  */
    UINT32                          udwPreset;                                 /* preset number  */
    NETDEV_XW_VIDEO_SOURCE_BASE_S      stVideoSourceBase;                      /* video source Info */
    BYTE                            byRes[32];                                 /* reserved */
}NETDEV_XW_SEQUENCE_SOURCE_S, *LPNETDEV_XW_SEQUENCE_SOURCE_S;

/* sequence resource list information */
typedef struct tagNETDEVXWSequenceSourceList
{
    UINT32                          udwWndID;                                   	/* window ID */
    UINT32                          udwSourceSize;                              	/* video source number */
    NETDEV_XW_SEQUENCE_SOURCE_S       astSequenceSource[NETDEV_SEQUENCE_SRC_MAX];   /* video source info */
    BYTE                            byRes[32];                                 		/* reserved */
}NETDEV_XW_SEQUENCE_SOURCE_LIST_S, *LPNETDEV_XW_SEQUENCE_SOURCE_LIST_S;

/* all base map info  */
typedef struct tagNETDEVXWBaseMapInfo
{
    UINT32                          udwID;                       				/* base map ID,Only in the device */
    CHAR                            szName[NETDEV_BMAP_NAME_LEN];				/* base map name */
    UINT32                          udwFormat;                     				/* base map format, see #NETDEV_XW_BASE_TYPE_E */
    NETDEV_XW_RESOLUTION_S            stResolution;                				/* base map resolution */
    BYTE                            bThumbnailData[NETDEV_BMAP_THUMBNAL_LEN]; 	/* thumbnail data */
    BYTE                            byRes[64];                   				/* reserved */
}NETDEV_XW_BASE_MAP_INFO_S, *LPNETDEV_XW_BASE_MAP_INFO_S;
/* scene detail info */
typedef struct tagNETDEVXWSceneInfoDetail
{
    CHAR                            szName[NETDEV_SCENE_NAME_LEN];      /* scene name */
    UINT32                          udwTVWallID;                      /* TV Wall ID */
    NETDEV_XW_BASE_MAP_INFO_S         stBaseMapInfo;                     /* base map info */
    UINT32                          udwVirtualLedNum;                  /* virtual LED Number */
    LPNETDEV_XW_VIRTUAL_LED_INFO_S     pstVirtualLedInfo;                 /* virtual LED info */
    UINT32                          udwWndNum;                         /* window number */
    LPNETDEV_XW_SCENE_WND_INFO_S       pstWndInfo;                       /* window info */
    UINT32                          udwLiveBindNum;                    /* Binding the number of Live */
    LPNETDEV_XW_VIDEO_SOURCE_S         pstVideoSource;                    /* Binding the info of Live */
    UINT32                          udwSequenceBindNum;                 /* Sequence work number */
    LPNETDEV_XW_SEQUENCE_SOURCE_LIST_S  pstSequenceSourceList;              /* Sequence work info */
    BYTE                            byRes[256];                        /* reserved */
}NETDEV_XW_SCENE_INFO_DETAIL_S, *LPNETDEV_XW_SCENE_INFO_DETAIL_S;

/* Coded channel information */
typedef struct tagNETDEVXWChannelsNum
{
    UINT32  udwVideoInNum;               /* Number of video input channels */
    UINT32  udwVideoOutNum;              /* Number of video output channels */
    UINT32  udwAudioInNum;               /* Number of Audio input channels */
    UINT32  udwAudioOutNum;              /* Number of Audio input channels */
    BYTE    byRes[64];                   /* reserved */
}NETDEV_XW_CHANNELS_NUM_S, *LPNETDEV_XW_CHANNELS_NUM_S;

 /**
 * @enum tagNETDEVAudioPortType
 * @brief Audio channel port, Enumeration Definition
 * @attention None
 */
typedef enum tagNETDEVAudioPortType
{
    NETDEV_AUDIO_PORT_SINGLE            = 0,                /* single track */
    NETDEV_AUDIO_PORT_DOUBLE            = 1,                /* dual track */
    NETDEV_AUDIO_PORT_INVALID           = 0xff              /* invalid vale */
}NETDEV_AUDIO_PORT_TYPE_E;

/**
 * @enum tagNETDEVVideoPortType
 * @brief video port type, Enumeration Definition
 * @attention None
 */
typedef enum tagNETDEVVideoPortType
{
    NETDEV_VIDEO_PORT_BNC            = 0,                /* BNC */
    NETDEV_VIDEO_PORT_VGA            = 1,                /* VGA */
    NETDEV_VIDEO_PORT_HDMI           = 2,                /* HDMI */
    NETDEV_VIDEO_PORT_DVI_D          = 3,                /* DVI_D */
    NETDEV_VIDEO_PORT_DVI_I          = 4,                /* DVI_D */
    NETDEV_VIDEO_PORT_DP             = 5,                /* DVI_D */
    NETDEV_VIDEO_PORT_SDI            = 6,                /* DVI_D */
    NETDEV_VIDEO_PORT_INVALID        = 0xff              /* invalid vale */
}NETDEV_VIDEO_PORT_TYPE_E;

/* video output channel info */
typedef struct tagNETDEVXWVideoOutInfo
{
    INT32   dwChannelID;                   /* channel ID */
    INT32   dwSlotID;                      /* slot ID */
    INT32   dwIndex;                       /* index */
    UINT32  udwVideoPortType;              /* channel type  #see NETDEV_VIDEO_PORT_TYPE_E */
}NETDEV_XW_VIDEO_OUT_INFO_S, *LPNETDEV_XW_VIDEO_OUT_INFO_S;

/* video input channel info */
typedef struct tagNETDEVXWVideoInInfo
{
    INT32   dwChannelID;                    /* channel ID */
    INT32   dwIndex;                        /* index */
    UINT32  udwVideoPortType;               /* channel Type, #see NETDEV_VIDEO_PORT_TYPE_E */
    BYTE    byRes[64];                  /* reserved */
}NETDEV_XW_VIDEO_IN_INFO_S, *LPNETDEV_XW_VIDEO_IN_INFO_S;

/* audio output channel info */
typedef struct tagNETDEVXWAudioOutInfo
{
    INT32   dwChannelID;                    /* channel ID */
    UINT32  udwAudioPortType;               /* channel type, see #NETDEV_AUDIO_PORT_TYPE_E */
    BYTE    byRes[64];                  	/* reserved */
}NETDEV_XW_AUDIO_OUT_INFO_S, *LPNETDEV_XW_AUDIO_OUT_INFO_S;

/* audio input channel info */
typedef struct tagNETDEVXWAudioInInfo
{
    INT32   dwChannelID;                    /* channel ID */
    UINT32  udwAudioPortType;               /* channel type, see #NETDEV_AUDIO_PORT_TYPE_E */
    BYTE    byRes[64];                      /* reserved */
}NETDEV_XW_AUDIO_IN_INFO_S, *LPNETDEV_XW_AUDIO_IN_INFO_S;

/* xware channel info */
typedef struct tagNETDEVXWChannelsList
{
    UINT32                          udwVideoInNum;                  /* video input channel number. The maximum number of channels that need to be given for ADU/CDU support  */
    LPNETDEV_XW_VIDEO_IN_INFO_S     pstVideoIn;                     /* video input channel info. */
    UINT32                          udwVideoOutNum;                 /* video output channel The maximum number of channels that need to be given for ADU/CDU support */
    LPNETDEV_XW_VIDEO_OUT_INFO_S    pstVideoOut;                    /* video output channel info */
    UINT32                          udwAudioInNum;                  /* audio input channel number. The maximum number of channels that need to be given for ADU/CDU support  */
    LPNETDEV_XW_AUDIO_IN_INFO_S     pstAudioIn;                     /* audio input channel info */
    UINT32                          udwAudioOutNum;                 /* audio output channel number. The maximum number of channels that need to be given for ADU/CDU support  */
    LPNETDEV_XW_AUDIO_OUT_INFO_S    pstAudioOut;                    /* audio output channel info */
    BYTE                            byRes[64];                      /* reserved */
}NETDEV_XW_CHANNELS_LIST_S, *LPNETDEV_XW_CHANNELS_LIST_S;
/**
* @enum tagNETDEVXWLayoutNum
* @brief xware Support split screen number
* @attention None
*/
typedef enum tagNETDEVXWLayoutNum
{
    NETDEV_XW_LAYOUT_TYPE_01             = 100,                /* 1 split screen */
    NETDEV_XW_LAYOUT_TYPE_02             = 200,                /* 2 split screen */
    NETDEV_XW_LAYOUT_TYPE_03             = 300,                /* 3 split screen */
    NETDEV_XW_LAYOUT_TYPE_04             = 400,                /* 4 split screen */
    NETDEV_XW_LAYOUT_TYPE_04_1           = 401,                /* 4 split screen 1+1+2 */
    NETDEV_XW_LAYOUT_TYPE_05             = 500,                /* 5 split screen 1+3+1 */
    NETDEV_XW_LAYOUT_TYPE_05_1           = 501,                /* 5 split screen 1+1+3 */
    NETDEV_XW_LAYOUT_TYPE_05_2           = 502,                /* 5 split screen 1+3+1 The order is different from the NETDEV_XW_LAYOUT_TYPE_05 */
    NETDEV_XW_LAYOUT_TYPE_05_3           = 503,                /* 5 split screen 1+1+3 The order is different from the NETDEV_XW_LAYOUT_TYPE_05_1 */
    NETDEV_XW_LAYOUT_TYPE_05_4           = 504,                /* 5 split screen 3+1+1*/
    NETDEV_XW_LAYOUT_TYPE_06             = 600,                /* 6 split screen 1+5 */
    NETDEV_XW_LAYOUT_TYPE_07             = 700,                /* 7 split screen 1+6 */
    NETDEV_XW_LAYOUT_TYPE_07_1           = 701,                /* 7 split screen 3+1+3 */
    NETDEV_XW_LAYOUT_TYPE_08             = 800,                /* 8 split screen 1+7 */
    NETDEV_XW_LAYOUT_TYPE_09             = 900,                /* 9 split screen */
    NETDEV_XW_LAYOUT_TYPE_10             = 1000,               /* 10 split screen 1+9 */
    NETDEV_XW_LAYOUT_TYPE_10_1           = 1001,               /* 10 split screen 2+8 */
    NETDEV_XW_LAYOUT_TYPE_13             = 1300,               /* 13 split screen 1+12 */
    NETDEV_XW_LAYOUT_TYPE_13_1           = 1301,               /* 13 split screen 1+12 The order is different from the NETDEV_XW_LAYOUT_TYPE_13 */
    NETDEV_XW_LAYOUT_TYPE_16             = 1600,               /* 16 split screen */

    NETDEV_XW_LAYOUT_TYPE_INVALID  = 0xffff
}NETDEV_XW_LAYOUT_NUM_E;

/**
* @enum tagNETDEVVideoFormat
* @brief resolution screen output standard
* @attention DC&&XW share
*/
typedef enum tagNETDEVVideoFormat
{
    NETDEV_VIDEO_FORMAT_720P24          = 2,            /* 1280x720@24 */
    NETDEV_VIDEO_FORMAT_720P25          = 3,            /* 1280x720@25 */
    NETDEV_VIDEO_FORMAT_720P30          = 4,            /* 1280x720@30 */
    NETDEV_VIDEO_FORMAT_720P50          = 5,            /* 1280x720@50 */
    NETDEV_VIDEO_FORMAT_720P60          = 6,            /* 1280x720@60 */
    NETDEV_VIDEO_FORMAT_1080P24         = 10,           /* 1920x1080@24 */
    NETDEV_VIDEO_FORMAT_1080P25         = 11,           /* 1920x1080@25 */
    NETDEV_VIDEO_FORMAT_1080P30         = 12,           /* 1920x1080@30 */
    NETDEV_VIDEO_FORMAT_1080P50         = 13,           /* 1920x1080@50 */
    NETDEV_VIDEO_FORMAT_1080P60         = 14,           /* 1920x1080@60 */
    NETDEV_VIDEO_FORMAT_XGA60           = 15,           /* 1024x768@60 */
    NETDEV_VIDEO_FORMAT_SXGA60          = 16,           /* 1280x1024@60 */
    NETDEV_VIDEO_FORMAT_UXGA60          = 17,           /* 1600x1200@60 */
    NETDEV_VIDEO_FORMAT_SXGAP60HZ       = 18,           
    NETDEV_VIDEO_FORMAT_WXGAP60HZ       = 19,           /* 1366x768@60 */
    NETDEV_VIDEO_FORMAT_WSXGA60HZ       = 20,           /* 1440x900@60 */
    NETDEV_VIDEO_FORMAT_4K30            = 21,           /* 3840x2160@30 */
    NETDEV_VIDEO_FORMAT_4K60            = 22,           /* 3840x2160@60 */
    NETDEV_VIDEO_FORMAT_MUXGA60HZ       = 23,           /* 1920x1200@60 */
    NETDEV_VIDEO_FORMAT_INVALID         = 0xFF
}NETDEV_VIDEO_FORMAT_E;
/**
* @enum tagNETDEVStreamType
* @brief stream type  Enumeration Definition
* @attention None
*/
typedef enum tagNETDEVStreamType
{
    NETDEV_STREAM_TYPE_RTP_UNICAST = 0,         /* unicast */
    NETDEV_STREAM_TYPE_RTP_MULTICAST = 1        /* multicast */
}NETDEV_STREAM_TYPE_E;
/**
* @struct tagNETDEVPassiveDecodeSend
* @brief Passive decoding control parameter information   
* @attention  None
*/
typedef struct tagNETDEVPassiveDecodeSend
{
    INT32 dwTransType;          /* transmission mode */
    INT32 dwBufSize;            /* data size */
    CHAR *pszBuffer;            /* data content */
    BYTE byRes[128];            /* reserved */
}NETDEV_PASSIVE_SEND_S, *LPNETDEV_PASSIVE_SEND_S;


/************************************************ Video stream information ******************************************************/

/**
 * @struct tagNETDEVSmartEncodeInfo 
 * @brief  Smart image encoding mode
 * @attention
 */
typedef struct tagNETDEVSmartEncodeInfo 
{
    UINT32 udwH264SmartEncodeModeNum;                                              /*  Number of smart image encoding in H.264*/
    UINT32 audwH264SmartEncodeModeList[NETDEV_SMART_ENCODE_MODEL_MAX_NUM];         /* List of smart image encoding in H.265. See NETDEV_SMART_ENCODE_MODE_E for reference*/
    UINT32 udwH265SmartEncodeModeNum;                                              /* Number of smart image encoding in H.264*/
    UINT32 audwH265SmartEncodeModeList[NETDEV_SMART_ENCODE_MODEL_MAX_NUM];         /* List of smart image encoding in H.265. See NETDEV_SMART_ENCODE_MODE_E for reference */
}NETDEV_SMART_ENCODE_S,*LPNETDEV_SMART_ENCODE_S;


/**
 * @struct tagNETDEVResolutionCapability
 * @brief Resolution details
 * @attention
 */
typedef struct tagNETDEVResolutionCapability
{
    UINT32 udwWidth;                                                                  /*  Image width*/
    UINT32 udwHeight;                                                                 /*  Image height*/
    UINT32 udwMinBitRate;                                                             /*  Minimum bit rate*/
    UINT32 udwMaxBitRate;                                                             /*  Maximum bit rate*/
    UINT32 udwDefaultBitRate;                                                         /*  Default bit rate*/
}NETDEV_RESOLUTION_CAPABILITY_S,*LPNETDEV_RESOLUTION_CAPABILITY_S;

/**
 * @struct tagNETDEVStreamCapability
 * @brief Stream capability
 * @attention
 */
typedef struct tagNETDEVStreamCapability
{
    UINT32 udwstreamID;                                                             /* Stream index. For enumeration, seeNETDEV_LIVE_STREAM_INDEX_E */
    UINT32 udwResolutionNum;                                                        /* Number of resolution*/
    UINT32 udwFrameRateNum;                                                         /* Number of frame rate*/
    UINT32 udwMaxFrameRate;                                                         /* Number of frame rate*/
    UINT32 udwMaxMJPEGFrameRate;                                                    /* Maximum MJPEG frame rate of current stream*/
    UINT32 audwFrameRateList[NETDEV_LEN_16];                                        /* Frame rate array*/
    NETDEV_RESOLUTION_CAPABILITY_S astResolutionCapabilityList[NETDEV_LEN_32];      /*  List of resolution*/
    NETDEV_SMART_ENCODE_S stSmartEncode;                                            /* Smart image encoding mode*/
}NETDEV_STREAM_CAP_S,*LPNETDEV_STREAM_CAPABILITY_S;

/**
 * @struct tagNETDEVVideoModeInfo
 * @brief Video mode capability
 * @attention
 */
typedef struct tagNETDEVVideoModeInfo 
{
    UINT32 udwWidth;                                      /* Image width*/
    UINT32 udwHeight;                                     /* Image height*/
    UINT32 udwFrameRate;                                  /* Image frame rate*/
}NETDEV_VIDEO_MODE_INFO_S,*LPNETDEV_VIDEO_MODE_INFO_S;

/**
 * @struct tagNETDEVVideoCapabilityInfo
 * @brief Encoding parameter capability
 * @attention
 */
typedef struct tagNETDEVVideoCapabilityInfo
{
    BOOL bIsSupportCfg;                                                             /* Support configuration or not. 0-No, 1-Yes*/
    BOOL bIsSupportSmoothLevel;                                                     /* Support smoothing or not. 0-No, 1-Yes*/
    BOOL bIsSupportImageFormat;                                                     /* Support configuration of image mode or not. 0-No, 1-Yes*/
    UINT32 udwEncodeFormatNum;                                                      /* Number of video compression*/
    UINT32 audwEncodeFormatList[NETDEV_ENCODE_FORMAT_MAX_NUM];                      /* Video compression list. See NETDEV_VIDEO_CODE_TYPE_E for reference */
    UINT32 udwMinIFrameInterval;                                                    /* Minimum value of I Frame Interval*/
    UINT32 udwMaxIFrameInterval;                                                    /* Maximum value of I Frame Interval*/
    UINT32 udwGOPTypeNum;                                                           /* Number of GOP type*/
    UINT32 audwGOPTypeList[NETDEV_GOP_TYPE_MAX_NUM];                                /* List of GOP type*/
    UINT32 udwVideoModeNum;                                                         /* Number of video mode*/
    NETDEV_VIDEO_MODE_INFO_S astVideoModeList[NETDEV_LEN_16];                       /* List of video mode capability*/
    UINT32 udwStreamCapNum;                                                         /* Number of stream*/
    NETDEV_STREAM_CAP_S astStreamCapList[NETDEV_LEN_16];                            /* List of stream capability*/
}NETDEV_VIDEO_STREAM_CAP_EX_S,*LPNETDEV_VIDEO_STREAM_CAP_EX_S;

/**
 * @struct tagNETDEVVideoCapabilityInfo
 * @brief Video encoding parameter
 * @attention
 */
typedef struct tagNETDEVVideoEncodeInfo
{
    BOOL bEnableSVCMode;                        /*  SVC configuration. 0-Off, 1-On*/
    UINT32 udwEncodeFormat;                     /*  Video Compression. For enumeration, seeNETDEV_VIDEO_CODE_TYPE_E*/
    UINT32 udwWidth;                            /* Image width*/
    UINT32 udwHeight;                           /* Image height*/
    UINT32 udwBitrate;                          /* Bit rate*/
    UINT32 udwBitrateType;                      /* Bitrate type. See NETDEV_BIT_RATE_TYPE_E for reference */
    UINT32 udwFrameRate;                        /* Frame rate*/
    UINT32 udwGopType;                          /* GOP mode. See NETDEV_GOP_TYPE_E for reference */
    UINT32 udwIFrameInterval;                   /* I Frame Interval. The range depends on capability*/
    UINT32 udwImageQuality;                     /* Image quality, ranges from 1 to 9. 9 means the highest quality*/
    UINT32 udwSmoothLevel;                      /* Smoothing level, ranges from 1 to 9. 1 means the lowest level*/
    UINT32 udwSmartEncodeMode;                  /* Smart encoding mode. See NETDEV_SMART_ENCODE_MODE_E for reference*/
}NETDEV_VIDEO_ENCODE_INFO_S,*LPNETDEV_VIDEO_ENCODE_INFO_S;

/**
 * @struct tagNETDEVVideoStreamInfoLapi
 * @brief  Video stream info
 * @attention
 */
typedef struct tagNETDEVVideoStreamInfoLapi 
{
    BOOL bEnabled;                                                                  /* Enable encoding for video stream or not*/
    UINT32 udwStreamID;                                                             /* Stream index. For enumeration, seeNETDEV_LIVE_STREAM_INDEX_E*/
    UINT32 udwMainStreamType;                                                       /* Main stream. See NETDEV_MAIN_STREAM_TYPE_E for reference */
    NETDEV_VIDEO_ENCODE_INFO_S stVideoEncodeInfo;                                   /* Video encoding parameter*/
}NETDEV_VIDEO_STREAM_INFO_EX_S,*LPNETDEV_VIDEO_STREAM_INFO_EX_S;

/**
 * @struct tagNETDEVVideoStreamInfoList
 * @brief Video stream list
 * @attention
 */
typedef struct tagNETDEVVideoStreamInfoList 
{
    UINT32 udwNum;                                                              /* Number of video stream*/
    NETDEV_VIDEO_STREAM_INFO_EX_S astVideoStreamInfoList[NETDEV_LEN_16];        /* Video stream list*/
}NETDEV_VIDEO_STREAM_INFO_LIST_S,*LPNETDEV_VIDEO_STREAM_INFO_LIST_S;



/***********************  Boolean configuration***************************** */

/**
 * @struct tagNETDEVAlarmInputInfo
 * @brief  Alarm boolean inputs info Structure definition
 * @attention None
 */
typedef struct tagNETDEVAlarmInputInfo
{
    CHAR  szName[NETDEV_LEN_64];                /* Name of input alarm */
}NETDEV_ALARM_INPUT_INFO_S, *LPNETDEV_ALARM_INPUT_INFO_S;

/**
 * @struct tagNETDEVAlarmInputInfoList
 * @brief  All Alarm boolean inputs info Structure definition
 * @attention None
 */
typedef struct tagNETDEVAlarmInputInfoList
{
    INT32                        dwSize;                                           /*  Number of input alarms */
    NETDEV_ALARM_INPUT_INFO_S    astAlarmInputInfo[NETDEV_MAX_ALARM_IN_NUM];       /*  Configuration information of input alarms */
}NETDEV_ALARM_INPUT_LIST_S, *LPNETDEV_ALARM_INPUT_LIST_S;

/**
 * @struct tagNETDEVAlarmOutputInfo
 * @brief Alarm boolean outputs info Structure definition
 * @attention None
 */
typedef struct tagNETDEVAlarmOutputInfo
{   
    CHAR    szName[NETDEV_LEN_64];                  /* Boolean name */
    INT32   dwChancelId;                            /* Channel ID */
    INT32   enDefaultStatus;                        /* Default status of boolean output, see enumeration #NETDEV_BOOLEAN_MODE_E */
    INT32   dwDurationSec;                          /* Alarm duration (s) */
} NETDEV_ALARM_OUTPUT_INFO_S, *LPNETDEV_ALARM_OUTPUT_INFO_S;

/**
 * @struct tagNETDEVAlarmOutputList
 * @brief All Alarm boolean outputs info Structure definition
 * @attention None
 */
typedef struct tagNETDEVAlarmOutputList
{   
    INT32                       dwSize;                                                 /*   Number of booleans  */
    NETDEV_ALARM_OUTPUT_INFO_S  astAlarmOutputInfo[NETDEV_MAX_ALARM_OUT_NUM];           /*  Boolean configuration information */
} NETDEV_ALARM_OUTPUT_LIST_S, *LPNETDEV_ALARM_OUTPUT_LIST_S;

/**
 * @struct tagNETDEVOutputSwitchesAlarmStatus
 * @brief  alarm state of output switch(Manual alarm)
 * @attention  None
 */
typedef struct tagNETDEVOutputSwitchesAlarmStatus
{
    INT32   dwBooleanId;                            /*  Boolean ID */
    INT32   dwChannelId;                            /* channel ID,The device itself is 0 */
    INT32   enAlarmStatus;                          /* Alarm Status, see #NETDEV_RELAYOUTPUT_STATE_E */
} NETDEV_OUTPUT_SWITCH_ALARM_STATUS_S, *LPNETDEV_OUTPUT_SWITCH_ALARM_STATUS_S;

/**
 * @struct tagNETDEVOutputSwitchesAlarmStatusList
 * @brief  alarm state list of output switch(Manual alarm)
 * @attention  None
 */
typedef struct tagNETDEVOutputSwitchesAlarmStatusList
{   
    INT32                                dwSize;                                                       /*   Number of booleans  */
    NETDEV_OUTPUT_SWITCH_ALARM_STATUS_S  astOutputAlarmStatusInfo[NETDEV_MAX_ALARM_OUT_NUM];           /* Output switches alarm status list*/
    BYTE                                 bRes[128];                                                    /* Reserved */
} NETDEV_OUTPUT_SWITCH_ALARM_STATUS_LIST_S, *LPNETDEV_OUTPUT_SWITCH_ALARM_STATUS_LIST_S;

/**
 * @struct tagNETDEVOutputSwitchesManualAlarmInfo
 * @brief  trigger or clean output switch alarm state(Manual alarm)
 * @attention None
 */
typedef struct tagNETDEVOutputSwitchesManualAlarmInfo
{   
    INT32                               dwSize;                                    /*  Number of booleans  */
    INT32                               dwIDList[NETDEV_MAX_ALARM_OUT_NUM];        /*  booleans ID list */
    NETDEV_MANUAL_ALARM_CMD_E           dwAlarmAction;                             /* command，see #NETDEV_MANUAL_ALARM_CMD_E*/
    BYTE                                 bRes[128];                                /*  Reserved */
} NETDEV_OUTPUT_SWITCH_MANUAL_ALARM_INFO_S, *LPNETDEV_OUTPUT_SWITCH_MANUAL_ALARM_INFO_S;

/**
 * @struct tagNETDEVTriggerAlarmOutput
 * @brief  Trigger boolean output alarm Structure definition
 * @attention �?None
 */
typedef struct tagNETDEVTriggerAlarmOutput
{   
    CHAR                        szName[NETDEV_LEN_64];          /*  Boolean name */
    NETDEV_RELAYOUTPUT_STATE_E  enOutputState;                  /*  Trigger status, see enumeration #NETDEV_RELAYOUTPUT_STATE_E */
} NETDEV_TRIGGER_ALARM_OUTPUT_S, *LPNETDEV_TRIGGER_ALARM_OUTPUT_S;

/************************************************ OSD********************************************************/

/**
 * @struct tagNETDEVAreaScope
 * @brief  Area
 * @attention None
 */
typedef struct tagNETDEVAreaScope
{
    INT32  dwLocateX;             /**  Coordinates of top point x [0,10000] */
    INT32  dwLocateY;             /**  Coordinates of top point y [0,10000] */
}NETDEV_AREA_SCOPE_S, *LPNETDEV_AREA_SCOPE_S;

/**
 * @struct tagNETDEVOsdTime
 * @brief OSD time configuration information
 * @attention None
 */
typedef struct tagNETDEVOsdTime
{
    BOOL                    bEnableFlag;        /* Enable time OSD, BOOL_TRUE means enable and BOOL_FALSE means disable */
    BOOL                    bWeekEnableFlag;    /* Display week or not (reserved) */
    NETDEV_AREA_SCOPE_S     stAreaScope;        /* Area coordinates */
    UINT32                  udwTimeFormat;      /* Time OSD format, see NETDEV_OSD_TIME_FORMAT_E */
    UINT32                  udwDateFormat;      /* Date OSD format, see NETDEV_OSD_TIME_FORMAT_E */
}NETDEV_OSD_TIME_S, *LPNETDEV_OSD_TIME_S;

/**
 * @struct tagNETDEVOsdTextOverlay
 * @brief OSD text overlay information
 * @attention
 */
typedef struct tagNETDEVOsdTextOverlay
{
    BOOL                    bEnableFlag;                /* Enable OSD text overlay, BOOL_TRUE means enable and BOOL_FALSE means disable */
    NETDEV_AREA_SCOPE_S     stAreaScope;                /* OSD text overlay area coordinates */
    CHAR                    szOSDText[NETDEV_OSD_TEXT_MAX_LEN];    /* OSD text overlay name strings */
    BYTE                    byRes[4];                               /*  Reserved */
}NETDEV_OSD_TEXT_OVERLAY_S, *LPNETDEV_OSD_TEXT_OVERLAY_S;

/**
 * @struct tagNETDEVOsdCfgInfo
 * @brief Basic channel OSD information
 * @attention
 */
typedef struct tagNETDEVOsdCfgInfo
{
    NETDEV_OSD_TIME_S         stTimeOSD;        /*  Information of channel time OSD */
    NETDEV_OSD_TEXT_OVERLAY_S stNameOSD;        /* Information of channel name OSD */
    INT16                     wTextNum;         /* Text OSD number */
    NETDEV_OSD_TEXT_OVERLAY_S astTextOverlay[NETDEV_OSD_TEXTOVERLAY_NUM];   /* Information of channel OSD text overlay */
}NETDEV_VIDEO_OSD_CFG_S, *LPNETDEV_VIDEO_OSD_CFG_S;

/**
 * @struct tagAreaInfo
 * @brief Definition of area configuration structure 
 * @attention
 */
typedef struct tagAreaInfo
{
    INT32   bIsEanbled;           /*  Enable or not. */
    INT32   dwTopLeftX;           /* Upper left corner X [0, 10000]  */
    INT32   dwTopLeftY;           /* Upper left corner Y [0, 10000]  */
    INT32   dwBottomRightX;       /*  Lower right corner x [0, 10000] */
    INT32   dwBottomRightY;       /* Lower right corner y [0, 10000] */
    INT32   dwIndex;              /* Index. */
}NETDEV_PRIVACY_MASK_AREA_INFO_S;

/**
 * @struct tagPrivacyMaskPara
 * @brief Privacy mask configuration information
 * @attention
 */
typedef struct tagPrivacyMaskPara
{
    INT32                                  dwSize;                                     /*  Mask area number */ 
    NETDEV_PRIVACY_MASK_AREA_INFO_S        astArea[NETDEV_MAX_PRIVACY_MASK_AREA_NUM];  /*  Mask area parameters */
}NETDEV_PRIVACY_MASK_CFG_S, *LPNETDEV_PRIVACY_MASK_CFG_S;

/**
 * @struct tagNETDEVOsdCapabilities
 * @brief OSD Capabilities
 * @attention
 */
typedef struct tagNETDEVOsdCapabilities
{
    BOOL     bIsSupportCfg;                                                     /* Support configuration or not. 0-No, 1-Ye*/
    BOOL     bIsSupportFontSizeCfg;                                             /* Support configuration of OSD size or not*/ 
    BOOL     bIsSupportFontColorCfg;                                            /* upport configuration of OSD color or not*/ 
    UINT32   udwMaxAreaNum;                                                     /* Maximum number of OSD area*/ 
    UINT32   udwMaxOSDNum;                                                      /* Maximum number of OSD*/ 
    UINT32   udwMaxPerAreaOSDNum;                                               /* Maximum number of OSD in each area*/ 
    UINT32   udwSupportedOSDTypeNum;                                            /* Number of OSD content type*/ 
    UINT32   udwSupportedTimeFormatNum;                                         /* Number of OSD time format*/ 
    UINT32   udwSupportedDateFormatNum;                                         /* Number of OSD date format*/ 
    UINT32   aduwSupportedDateFormatList[NETDEV_OSD_DATE_FORMAT_MAX_NUM];       /* date OSD format list，see #NETDEV_OSD_DATE_FORMAT_E */ 
    UINT32   audwSupportedTimeFormatList[NETDEV_OSD_TIME_FORMAT_MAX_NUM];       /* time OSD format list，see #NETDEV_OSD_TIME_FORMAT_E */ 
    UINT32   audwSupportedOSDTypeList[NETDEV_OSD_TYPE_MAX_NUM];                 /* supported OSD content type list，see #NETDEV_OSD_CONTENT_TYPE_E */ 
}NETDEV_OSD_CAP_S, *LPNETDEV_OSD_CAP_S;

/**
 * @struct tagNETDEVOsdContentStyle
 * @brief Display Style of channel OSD
 * @attention
 */
typedef struct tagNETDEVOsdContentStyle
{
    UINT32 udwFontStyle;                         /* Font style. For enumeration, seeNETDEV_OSD_FONT_STYLE_E*/
    UINT32 udwFontSize;                          /*  Font Size. For enumeration, seeNETDEV_OSD_FONT_SIZE_E*/
    UINT32 udwColor;                             /* Color*/
    UINT32 udwDateFormat;                        /* Date Format. For enumeration, seeNETDEV_OSD_DATE_FORMAT_E */
    UINT32 udwTimeFormat;                        /* Date Format. For enumeration, seeNETDEV_OSD_DATE_FORMAT_E */
    UINT32 audwFontAlignList[NETDEV_LEN_8];      /*  Font align in area, 8 areasfixed, IPcamera supported. For enumeration, seeNETDEV_OSD_ALIGN_E */
    UINT32 udwMargin;                            /*  Number of character with margin, IP camera supported. For enumeration, seeNETDEV_OSD_MIN_MARGIN_E */
}NETDEV_OSD_CONTENT_STYLE_S,*LPNETDEV_OSD_CONTENT_STYLE_S;

/**
 * @struct tagNETDEVContentInfo
 * @brief Content
 * @attention
 */
typedef struct tagNETDEVContentInfo
{

    UINT32 udwContentType;                        /* OSD content type. For enumeration, see NETDEV_OSD_CONTENT_TYPE_E*/
    CHAR   szOSDText[NETDEV_OSD_TEXT_MAX_LEN];    /* OSD text*/
}NETDEV_CONTENT_INFO_S,*LPNETDEV_CONTENT_INFO_S;

/**
 * @struct tagNETDEVOSDContentInfo
 * @brief Channel OSD content
 * @attention
 */
typedef struct tagNETDEVOSDContentInfo
{
    BOOL   bEnabled;                                        /*  Enable OSD area*/
    UINT32 udwOSDID;                                        /*  Area No., ranges from 0 to 7.*/
    UINT32 udwAreaOSDNum;                                   /* Number of OSD in current area*/
    UINT32 udwTopLeftX;                                     /* X-axis of OSD area, ranges from 0 to 999*/
    UINT32 udwTopLeftY;                                     /* Y-axisof OSD area, ranges from 0 to 999*/
    NETDEV_CONTENT_INFO_S astContentInfo[NETDEV_LEN_8];     /*  OSD content in current area*/
}NETDEV_OSD_CONTENT_INFO_S,*LPNETDEV_OSD_CONTENT_INFO_S;

/**
 * @struct tagNETDEVOsdContent
 * @brief All contents of channel OSD
 * @attention
 */
typedef struct tagNETDEVOsdContent
{
    UINT32                    udwNum;                          /* Number of OSD area*/
    NETDEV_OSD_CONTENT_INFO_S astContentList[NETDEV_LEN_32];   /* Content list of OSD area

*/
}NETDEV_OSD_CONTENT_S,*LPNETDEV_OSD_CONTENT_S;

/************************************************ Video analyzing********************************************************/

/**
 * @struct tagNETDEVTamperAlarmInfo
 * @brief Tampering detection analysis info
 * @attention None
 */
typedef struct tagNETDEVTamperAlarmInfo
{
    INT32  dwSensitivity;                               /*  Sensitivity */
    BYTE   byRes[256];                                  /*  Reserved */
}NETDEV_TAMPER_ALARM_INFO_S, *LPNETDEV_TAMPER_ALARM_INFO_S;

/**
 * @struct tagNETDEVMotionAlarmInfo
 * @brief Motion detection analysis info
 * @attention  None
 */
typedef struct tagNETDEVMotionAlarmInfo
{
    INT32  dwSensitivity;                                                     /*   Sensitivity */
    INT32  dwObjectSize;                                                      /*   Objection Size */
    INT32  dwHistory;                                                         /*   History */
    INT16  awScreenInfo[NETDEV_SCREEN_INFO_ROW][NETDEV_SCREEN_INFO_COLUMN];   /*   Screen Info */
    BYTE   byRes[64];                                                         /*   Reserved */
}NETDEV_MOTION_ALARM_INFO_S, *LPNETDEV_MOTION_ALARM_INFO_S;

typedef struct tagNETDEVCrossLinePointInfo
{
    BOOL    bEnable;                /* Supported or not */
    INT32   dwSensitivity;        /* Sensitivity */
    INT32   dwDirection;          /* trigger Direction */
    INT32   dwTopLeftX;           /* Upper left corner X [0, 10000]  */
    INT32   dwTopLeftY;           /* Upper left corner Y [0, 10000]  */
    INT32   dwBottomRightX;       /* Lower right corner x [0, 10000] */
    INT32   dwBottomRightY;       /* Lower right corner y [0, 10000] */
}NETDEV_CROSS_LINE_POINT_INFO_S, *LPNETDEV_CROSS_LINE_POINT_INFO_S;

/**
* @struct tagNETDEVCrossLineAlarmInfo
* @brief Cross Line detection analysis info
* @attention  None
*/
typedef struct tagNETDEVCrossLineAlarmInfo
{
    BOOL    bEnable;                                                  /*  Supported or not */
    NETDEV_CROSS_LINE_POINT_INFO_S stAreaInfo[4];                       /* area info */
    BYTE   byRes[64];                                                   /*  Reserved */
}NETDEV_CROSS_LINE_ALARM_INFO_S, *LPNETDEV_CROSS_LINE_ALARM_INFO_S;

/**
* @struct tagNETDEVIntrusionPointInfo
* @brief Intrusion detection point axis
* @attention  None
*/
typedef struct tagNETDEVIntrusionPointInfo
{

    INT32   dwPointX;           /* X [0, 10000]*/
    INT32   dwPointY;           /* Y [0, 10000]*/
}NETDEV_INTRUSION_POINT_INFO_S, *LPNETDEV_INTRUSION_POINT_INFO_S;


/**
* @struct tagNETDEVIntrusionAreaInfo
* @brief Intrusion detection area info
* @attention None
*/
typedef struct tagNETDEVIntrusionAreaInfo
{
    BOOL    bEnable;                                            /*  Supported or not */
    INT32   dwSensitivity;                                      /* Sensitivity. range [1-100] */
    INT32   dwTimeThreshold;                                    /* time threshold. Range [1,10]*/
    INT32   percentage;                                         /* percentage. range [1-100] */
    INT32   dwPointCount;                                       /* The number of points in the area，Range [3,6],If this area is not set, this field will be ignored */
    NETDEV_INTRUSION_POINT_INFO_S   stPointInfo[NETDEV_LEN_6];  /* point info */
    BYTE   byRes[64];                                           /*  Reserved */

}NETDEV_INTRUSION_AREA_INFO_S, *LPNETDEV_INTRUSION_AREA_INFO_S;

/**
* @struct tagNETDEVIntrusionAlarmInfo
* @brief Intrusion detection analysis info
* @attention None
*/
typedef struct tagNETDEVIntrusionAlarmInfo
{
    BOOL    bEnable;                                                  /*  Supported or not */
    NETDEV_INTRUSION_AREA_INFO_S stAreaInfo[NETDEV_LEN_4];            /*  area info. 4 zones are supported at most, each with three to six edges */
    BYTE   byRes[64];                                                   /* Reserved */
}NETDEV_INTRUSION_ALARM_INFO_S, *LPNETDEV_INTRUSION_ALARM_INFO_S;

/**
 * @struct tagNETDEVUpnpPortState
 * @brief  Protocol info
 * @attention None
 */
typedef struct tagNETDEVUpnpPortState
{
    NETDEV_PROTOCOL_TYPE_E   eType;                            /*  Protocol type, see enumeration #NETDEV_PROTOCOL_TYPE_E */
    BOOL                     bEnbale;                          /*  Supported or not */
    INT32                    dwPort;                           /*  Port number */
    BYTE                     byRes[128];                       /*  Reserved */
}NETDEV_UPNP_PORT_STATE_S, *LPNETDEV_UPNP_PORT_STATE_S;


/**
 * @struct tagNETDEVUpnpNatState
 * @brief  Protocol info list
 * @attention None
 */
typedef struct tagNETDEVUpnpNatState
{
    INT32   dwSize;                                            /*  Number of protocols */
    NETDEV_UPNP_PORT_STATE_S  astUpnpPort[NETDEV_LEN_16];      /*  Protocol info */
}NETDEV_UPNP_NAT_STATE_S, *LPNETDEV_UPNP_NAT_STATE_S;


/**
 * @struct tagNetDEVDiscoveryDevInfo
 * @brief  Info of discovered device
 * @attention None
 */
typedef struct tagNetDEVDiscoveryDevInfo
{
    CHAR    szDevAddr[NETDEV_LEN_64];                            /*  Device address */
    CHAR    szDevModule[NETDEV_LEN_64];                          /*  Device model */
    CHAR    szDevSerailNum[NETDEV_LEN_64];                       /*  Device serial number */
    CHAR    szDevMac[NETDEV_LEN_64];                             /*  Device MAC address */
    CHAR    szDevName[NETDEV_LEN_64];                            /*  Device name */
    CHAR    szDevVersion[NETDEV_LEN_64];                         /*  Device version */
    NETDEV_DEVICETYPE_E  enDevType;                              /*  Device type */
    INT32   dwDevPort;                                           /*  Device port number */
    CHAR    szManuFacturer[NETDEV_LEN_64];                       /* Device manufacture */
    CHAR    szActiveCode[NETDEV_LEN_64];                         /* activeCode */
    CHAR    szCloudUserName[NETDEV_LEN_64];                      /* cloudUserName */
    BYTE    byRes[68];                                           /*  Reserved */
}NETDEV_DISCOVERY_DEVINFO_S, *LPNETDEV_DISCOVERY_DEVINFO_S;

/**
* @struct tagNETDEVTime
* @brief Time parameter Structure definition
* @attention None
*/
typedef struct tagNETDEVTime
{
    INT32   dwYear;                       /*  Year */
    INT32   dwMonth;                      /*  Month */
    INT32   dwDay;                        /*  Day */
    INT32   dwHour;                       /*  Hour */
    INT32   dwMinute;                     /*  Minute */
    INT32   dwSecond;                     /*  Second */
}NETDEV_TIME_S, *LPNETDEV_TIME_S;

/**
* @struct tagNETDEVSystemTimeInfo
* @brief Time configuration structure definition
* @attention
*/
typedef struct tagNETDEVSystemTimeDST
{
    INT32 dwMonth;              /*  Month(1~12)*/
    INT32 dwWeekInMonth;        /*  1 for the first week and 5 for the last week in the month */
    INT32 dwDayInWeek;          /*  0 for Sunday and 6 for Saturday see enumeration NETDEV_DAY_IN_WEEK_E */
    INT32 dwHour;               /*  Hour */
}NETDEV_TIME_DST_S, *LPNETDEV_TIME_DST_S;

/**
* @struct tagNETDEVSystemTimeInfo
* @brief Time configuration structure definition
* @attention
*/
typedef struct tagNETDEVSystemTimeDSTCfg
{
    NETDEV_TIME_DST_S   stBeginTime;        /*  DST begin time. see enumeration NETDEV_TIME_DST_S */
    NETDEV_TIME_DST_S   stEndTime;          /*  DST end time. see enumeration NETDEV_TIME_DST_S */
    INT32               dwOffsetTime;       /*  DST saving time. see enumeration NETDEV_DST_OFFSET_TIME */
}NETDEV_TIME_DST_CFG_S, *LPNETDEV_TIME_DST_CFG_S;

/**
* @struct tagNETDEVSystemTimeInfo
* @brief Time configuration structure definition
* @attention
*/
typedef struct tagNETDEVSystemTimeInfo
{
    NETDEV_TIME_ZONE_E      dwTimeZone;             /* Time zone, see enumeration #NETDEV_TIME_ZONE_E */
    NETDEV_TIME_S           stTime;                 /*  Time */
    BOOL                    bEnableDST;             /* DST enable */
    NETDEV_TIME_DST_CFG_S   stTimeDSTCfg;           /* DST time config*/
    BYTE                    byRes[220];             /*  Reserved */
}NETDEV_TIME_CFG_S, *LPNETDEV_TIME_CFG_S;

/**
* @struct tagNETDEVDSTCfgInfo
* @brief  DST configuration structure definition
* @attention
*/
typedef struct tagNETDEVDSTCfgInfo
{
    BOOL                    bEnableDST;             /* DST enable */
    NETDEV_TIME_DST_CFG_S   stTimeDSTCfg;           /* DST time config*/
    BYTE                    byRes[128];             /* Reserved */
}NETDEV_DST_CFG_S, *LPNETDEV_DST_CFG_S;

/**
* @struct tagNETDEVNetParam
* @brief  Timeout structure definition
* @attention
*/
typedef struct tagNETDEVRevTimeout
{
    INT32   dwRevTimeOut;                 /*  Set timeout for receiving */
    INT32   dwFileReportTimeOut;          /*  Set timeout for file operation */
    BYTE    byRes[128];                   /*  Reserved */
}NETDEV_REV_TIMEOUT_S, *LPNETDEV_REV_TIMEOUT_S;

/**
*@enum tagNETDevNetWorkMode
*@brief NetWork Mode Enumeration Definition 
*@attention
*/
typedef enum tagNETDevNetWorkMode
{
    NETDEV_NETMODE_LAN                  = 0,            /* LAN mode,Only for local and port mappings */
    NETDEV_NETMODE_WAN                  = 1,            /* WAN wan,only for Single layer NAT */
    NETDEV_NETMODE_MULTINAT             = 2,            /* multilayer NAT mode,NAT hole */
    NETDEV_NETMODE_P2P                  = 3,            /* multilayer NAT mode,NAT hole */
    NETDEV_NETMODE_TURN                 = 4             /* multilayer NAT mode,For forwarding */

}NETDEV_NETWORK_MODE_E;

/**
 * @struct tagNetDEVCloudDevLogin
 * @brief  Cloud Device information Structure definition
 * @attention  Obsoleted (not recommended)
 * suggested use tagNetDEVCloudDevLoginInfo
 */
typedef struct tagNetDEVCloudDevLogin
{
    CHAR szDeviceName[NETDEV_LEN_64];       /* Dev Name Device name */
    CHAR szDevicePassword[NETDEV_LEN_64];   /*  Device login password (optional) */
    INT32 dwT2UTimeout;                     /*  P2P timeout (default: 15s) */
    //INT32 dwConnectMode;                  /*  Connect Mode*/
} NETDEV_CLOUD_DEV_LOGIN_S, *LPNETDEV_CLOUD_DEV_LOGIN_S;

/**
 * @struct tagNetDEVCloudDevLoginEx
 * @brief  Cloud Device information Structure definition
 * @attention   None, Discarded, not recommended
 *  suggested use tagNetDEVCloudDevLoginInfo
 */
typedef struct tagNetDEVCloudDevLoginEx
{
    CHAR szDeviceName[NETDEV_LEN_260];      /* Dev Name Device name */
    CHAR szDevicePassword[NETDEV_LEN_64];   /*  Device login password (optional) */
    INT32 dwT2UTimeout;                     /*  P2P timeout (default: 15s) */
    //INT32 dwConnectMode;                  /*  Connect Mode*/
} NETDEV_CLOUD_DEV_LOGIN_EX_S, *LPNETDEV_CLOUD_DEV_LOGIN_EX_S;


/**
 * @struct tagNetDEVCloudDevLoginInfo
 * @brief  Cloud Device information Structure definition
 * @attention   None
 */
typedef struct tagNetDEVCloudDevLoginInfo
{
    CHAR szDeviceName[NETDEV_LEN_260];      /* Dev Name Device name */
    CHAR szDevicePassword[NETDEV_LEN_64];   /*  Device login password (optional) */
    INT32 dwT2UTimeout;                     /*  P2P timeout (default: 15s) */
    INT32 dwConnectMode;                    /*  Connect Mode,  reference to #NETDEV_CLOUD_CONNECT_MODE,  When the duty is 0, the method can get the final landing mode accurately*/
    BYTE    byRes[256];                     /*  Reserved */
} NETDEV_CLOUD_DEV_LOGIN_INFO_S, *LPNETDEV_CLOUD_DEV_LOGIN_INFO_S;
/**
* @enum tagNETDEVCloudFunVersion
* @brief 
* @attention �?None
*/
typedef enum tagNETDEVCloudFunVersion
{
    NETDEV_CLOUD_FUN_VERSION_V2 = 0x00,              /* V2 */
    NETDEV_CLOUD_FUN_VERSION_V4 = 0x01,              /* V4 */

    NETDEV_CLOUD_FUN_VERSION_INVALID = 0x0F          /* Invalid value */
}NETDEV_CLOUD_FUN_VERSION_E;

/**
* @enum tagNETDEVCloudShareSrcType
* @brief 
* @attention �?None
*/
typedef enum tagNETDEVCloudShareSrcType
{
    NETDEV_CLOUD_SHARE_SRC_TYPE_DEF = 0x00,    
    NETDEV_CLOUD_SHARE_SRC_TYPE_EZLITE = 0x01, 

    NETDEV_CLOUD_SHARE_SRC_TYPE_INVALID = 0xFF
}NETDEV_CLOUD_SHARE_SRC_TYPE_E;

/**登录速度优化
 * @struct tagNETDEVLoginInfo
 * @brief  Device information Structure definition
 * @attention   None
 */
typedef struct tagNETDEVLoginInfo
{
    UINT32 LoginType;                          /* Login Type, reference to #NETDEV_LOGIN_TYPE_E */

    /* Dynamic password login field */
    LPVOID lpUserID;                           /* Cloud Login ID User login ID */
    LPNETDEV_CLOUD_DEV_LOGIN_INFO_S pstCloudInfo;   /* Cloud Device Login Info */
    INT32 dwCloudFunVersion;                   /* reference to NETDEV_CLOUD_FUN_VERSION_E */
    INT32 dwShareSrcType;                      /* reference to NETDEV_CLOUD_SHARE_SRC_TYPE_E */

    /* Local login field */
    CHAR szDevIP[NETDEV_LEN_64];               /*  Device IP */
    CHAR szUserName[NETDEV_LEN_64];            /*  User Name */
    CHAR szPassword[NETDEV_LEN_64];            /*  Password */
    INT32 dwDevPort;                           /*  Device Server Port */
    BYTE byRes[504];                           /*  Reserved */
}NETDEV_LOGIN_INFO_S,*LPNETDEV_LOGIN_INFO_S;

/**
 * @struct tagNETDEVCloudDevInfo
 * @brief  Cloud Device information Structure definition
 * @attention Discarded, not recommended
 */
typedef struct tagNETDEVCloudDevInfo
{
    CHAR    szIPAddr[NETDEV_IPV4_LEN_MAX];              /*  Device IP */
    CHAR    szDevUserName[NETDEV_LEN_64];               /*  Device username */
    CHAR    szDevName[NETDEV_LEN_64];                   /*  Device Name Device name */
    CHAR    szDevModel[NETDEV_LEN_64];                  /*  Device model */
    CHAR    szDevSerialNum[NETDEV_LEN_64];              /*  Device serial number */
    INT32   dwOrgID;                                    /*  ID Home organization ID */
    INT32   dwDevPort;                                  /*  Device port */
    //INT32   dwConnectMode;                            /*  Connect Mode*/
}NETDEV_CLOUD_DEV_INFO_S,*LPNETDEV_CLOUD_DEV_INFO_S;

/**
 * @struct tagNETDEVCloudDevInfo
 * @brief  Cloud Device information Structure definition
 * @attention   None    Discarded, not recommended
 */
typedef struct tagNETDEVCloudDevInfoEx
{
    CHAR    szIPAddr[NETDEV_IPV4_LEN_MAX];              /*  Device IP */
    CHAR    szDevUserName[NETDEV_LEN_260];              /*  Device username */
    CHAR    szDevName[NETDEV_LEN_260];                  /*  Dev Name Device name */
    CHAR    szDevModel[NETDEV_LEN_64];                  /*  Device model */
    CHAR    szDevSerialNum[NETDEV_LEN_64];              /*  Device serial number */
    INT32   dwOrgID;                                    /*  Home organization ID */
    INT32   dwDevPort;                                  /*  Device port */
    BYTE    byRes[128];                                 /*  Reserved */
}NETDEV_CLOUD_DEV_INFO_EX_S,*LPNETDEV_CLOUD_DEV_INFO_EX_S;

/**
 * @struct tagNETDEVCloudOrgInfo
 * @brief Cloud Device organization information Structure definition 
 * @attention   None
 */
typedef struct tagNETDEVCloudOrgInfo
{
    INT32   dwOrgID;                                /* Org ID */
    INT32   dwOrgParentID;                          /* Parent Org ID */
    CHAR    szOrgName[NETDEV_LEN_64];               /* Org Name */
    BYTE    byRes[128];                             /* Reserved */
}NETDEV_CLOUD_ORG_INFO_S,*LPNETDEV_CLOUD_ORG_INFO_S;


/**
 * @struct tagNETDEVCloudOrgList
 * @brief Cloud Device organization List Structure definition 
 * @attention   None
 */
typedef struct tagNETDEVCloudOrgList
{
    INT32   dwSize;                                     /* Num */
    NETDEV_CLOUD_ORG_INFO_S astOrgInfo[NETDEV_LEN_64];  /* Cloud Device organization information */
}NETDEV_CLOUD_ORG_LIST_S,*LPNETDEV_CLOUD_ORG_LIST_S;


/**
 * @struct tagNETDEVDiskInfo
 * @brief  Disk info
 * @attention   None
 */
typedef struct tagNETDEVDiskInfo
{
    INT32 dwDiskCabinetIndex;
    INT32 dwSlotIndex;                          /* Slot Index */
    INT32 dwTotalCapacity;                      /* Total Capacity */
    INT32 dwUsedCapacity;                       /* Used Capacity */
    NETDEV_DISK_WORK_STATUS_E enStatus;         /* Status */
    CHAR szManufacturer[NETDEV_LEN_32];         /* Manufacturer */
}NETDEV_DISK_INFO_S,*LPNETDEV_DISK_INFO_S;

/**
 * @struct tagNETDEVDiskInfoList
 * @brief  Disk info list
 * @attention   None
 */
typedef struct tagNETDEVDiskInfoList
{
    INT32 dwSize;                                             /*  Disk number */
    NETDEV_DISK_INFO_S astDisksInfo[NETDEV_DISK_MAX_NUM];     /*  Disk info */
}NETDEV_DISK_INFO_LIST_S,*LPNETDEV_DISK_INFO_LIST_S;

/**
* @struct tagNETDEVDefoggingInfo
* @brief  Defogging info
* @attention
*/
typedef struct tagNETDEVDefoggingInfo
{
    NETDEV_DEFOGGING_MODE_E  enDefoggingMode;           /* Defogging mode */
    FLOAT                    fDefoggingLevel;           /* Defogging level (0.0, 1.0) */
    BYTE                     bRes[64];                  /* Reserved */
}NETDEV_DEFOGGING_INFO_S, *LPNETDEV_DEFOGGING_INFO_S;

/**
* @struct tagNETDEVFocusInfo
* @brief Focus Info
* @attention
*/
typedef struct tagNETDEVFocusInfo
{
    NETDEV_FOCUS_MODE_E     enFocusMode;                /* Defogging mode */
    BYTE                    bRes[16];                   /* Reserved */
}NETDEV_FOCUS_INFO_S, *LPNETDEV_FOCUS_INFO_S;


/**
* @struct tagNETDEVIrFilterInfo
* @brief  IrCut filter info
* @attention
*/
typedef struct tagNETDEVIrFilterInfo
{
    NETDEV_IR_CUT_FILTER_MODE_E enIrCutFilterMode;      /* IrCut Filter mode */
    BYTE                        bRes[16];               /* Reserved */
}NETDEV_IRCUT_FILTER_INFO_S, *LPNETDEV_IRCUT_FILTER_INFO_S;

/**
* @struct tagNETDEVManualRecordcfg
* @brief  Manual Record structure definition
* @attention
*/
typedef struct tagNETDEVManualRecordcfg
{
    INT32                   dwChannelID;        /* Channel ID */
    NETDEV_RECORD_TYPE_E    enRecordType;       /* Record type, reference to #NETDEV_RECORD_TYPE_E */
    BYTE                    byRes[64];          /* Reserved */
}NETDEV_MANUAL_RECORD_CFG_S, *LPNETDEV_MANUAL_RECORD_CFG_S;


/**
 * @struct tagNETDEVMonthInfo
 * @brief  get video by Month Structure definition
 * @attention   None
 */
typedef struct tagNETDEVMonthInfo
{
    UINT32  udwYear;        /* year*/
    UINT32  udwMonth;       /* month */
    UINT32  udwPosition;    /* NETDEV_VIDEO_POSITION_E video query location */
}NETDEV_MONTH_INFO_S, *LPNETDEV_MONTH_INFO_S;

/**
 * @struct tagNETDEVMonthInfo
 * @brief  video status Structure definition
 * @attention   None
 */
typedef struct tagNETDEVMonthStatus
{
    UINT32  udwDayNumInMonth;                       /* The number of a month's days */
    UINT32  szVideoStatus[NETDEV_MONTH_DAY_MAX];    /* video status list, see in NETDEV_VIDEO_STATUS_E */
}NETDEV_MONTH_STATUS_S, *LPNETDEV_MONTH_STATUS_S;


/**
 * @struct tagNETDEVChannels
 * @brief  multichannel Structure definition
 * @attention   None
 */
typedef struct tagNETDEVChannels
{
    UINT32  udwSize;                            /* Channel size */
    UCHAR   szChannelIDs[NETDEV_CHANNEL_MAX];   /* Channel ID list[1,2,3,4] */
}NETDEV_CHANNELS_S, *LPNETDEV_CHANNELS_S;


/**
* @struct tagNETDEVTrafficStatisticsCond
* @brief Command of Passenger flow statistic Structure definition
* @attention   None
*/
typedef struct tagNETDEVTrafficStatisticsCond
{
    INT32       dwChannelID;            /* Channel ID */
    INT32       dwStatisticsType;       /* Statistics Type, reference to# NETDEV_TRAFFIC_STATISTICS_TYPE_E Statistics type */
    INT32       dwFormType;             /* Form Type,reference to # NETDEV_FORM_TYPE_E Form type */
    INT64       tBeginTime;             /* Begin time */
    INT64       tEndTime;               /* End time */
}NETDEV_TRAFFIC_STATISTICS_COND_S, *LPNETDEV_TRAFFIC_STATISTICS_COND_S;

/**
* @struct tagNETDEVTrafficStatisticsData
* @brief  Passenger flow statistic Structure definition
* @attention   None
*/
typedef struct tagNETDEVTrafficStatisticsData
{
    INT32  dwSize;                                          /* Report length, depending on the length of the different report types  */
    INT32  adwEnterCount[NETDEV_PEOPLE_CNT_MAX_NUM];        /* Numbers Enter Count */
    INT32  adwExitCount[NETDEV_PEOPLE_CNT_MAX_NUM];         /* Numbers Exit number */
}NETDEV_TRAFFIC_STATISTICS_DATA_S, *LPNETDEV_TRAFFIC_STATISTICS_DATA_S;


/**
* @struct tagNETDEVGeolocationInfo
* @brief  Geolocation info Structure definition
* @attention   None
*/
typedef struct tagNETDEVGeolocationInfo 
{
    FLOAT fLongitude;       /*  Longitude */
    FLOAT fLatitude;        /*  Latitude */
}NETDEV_GEOLACATION_INFO_S, *LPNETDEV_GEOLACATION_INFO_S;

/**
* @struct tagNETDEVWiFiSnifferMacInfo
* @brief  WIFISnifferMac info Structure definition 
* @attention   None
*/
typedef struct tagNETDEVWiFiSnifferMacInfo
{
    CHAR  aszMACInfo[NETDEV_WIFISNIFFER_MAC_MAX_NUM];     /* WiFi sniffer mac address*/
    INT16 wMaxSig;                                        /* corresponding max signal strength (in dBm) */
    CHAR  aszMaxSigTime[NETDEV_MAX_DATE_STRING_LEN];      /* Time to obtain Mac address�?corresponding max signal strength*/
}NETDEV_WIFISNIFFER_MAC_INFO_S, *LPNETDEV_WIFISNIFFER_MAC_INFO_S;

/**
* @struct tagNETDEVWiFiSnifferMacList
* @brief  WIFISnifferMac array Structure definition  
* @attention   None
*/
typedef struct tagNETDEVWiFiSnifferMacList
{
    INT32 dwSize;
    NETDEV_WIFISNIFFER_MAC_INFO_S  astMACList[NETDEV_WIFISNIFFER_MAC_ARRY_MAX_NUM];
}NETDEV_WIFISNIFFER_MAC_LIST_S, *LPNETDEV_WIFISNIFFER_MAC_LIST_S;


/**
 * @struct tagNETDEVCloudDevBindInfo
 * @brief Definition of organization information structure of cloud device organization 
 * @attention   None
 */
typedef struct tagNETDEVCloudDevBindInfo
{
    CHAR szDevRegisterCode[NETDEV_LEN_64];                  /* Device Register Code */
    CHAR szDevAlias[NETDEV_LEN_64];                         /* Device Alias */
    CHAR szDevCloudUsername[NETDEV_LEN_64];                 /* Device User Name */
    CHAR szDevSerialNum[NETDEV_LEN_64];                     /* Device series number */
    CHAR szDevModel[NETDEV_LEN_64];                         /* Device model */
    BYTE byRes[256];                                        /* Reserved */
}NETDEV_CLOUD_DEV_BASE_INFO_S,*LPNETDEV_CLOUD_DEV_BASE_INFO_S;


/**
 * @struct tagNETDEVCloudDevDistributeInfo
 * @brief Device distribution policy information structure
 * @attention  None
 */
typedef struct tagNETDEVCloudDevDistributeInfo
{
    INT32   dwDistributeCloud;                          /* Support distributor ,reference #NETDEV_DISTRIBUTE_CLOUD_SRV_E */
    INT32   dwBitrateLimit;                             /* Bitrate Limit(Kbps) */
    INT32   dwDistributeMode;                           /* Distribute Mode/reference #NETDEV_DISTRIBUTE_MODE_E */
    CHAR    szDevDistributeCap[NETDEV_LEN_64];          /* Equipment distribution capability */
    BYTE    byRes[128];                                 /* Reserved */
}NETDEV_CLOUD_DEV_DISTRIBUTE_INFO_S,*LPNETDEV_CLOUD_DEV_DISTRIBUTE_INFO_S;


/**
 * @struct tagNETDEVCloudDevChlInfo
 * @brief Cloud device channel information structure body definition
 * @attention  None
 */
 typedef struct tagNETDEVCloudDevChlInfo
{
    INT32                          dwChannelID;                               /* Channel number */
    CHAR                           szChannelSN[NETDEV_LEN_260];               /* Channel（IPC）series number */
    CHAR                           szChannelName[NETDEV_LEN_260];             /* Channel Nume */
    NETDEV_VIDEO_STREAM_INFO_S     astStreamInfo[NETDEV_LEN_8];               /* Stream information list */
    BOOL                           bChannelStatus;                            /* Channel Status */
    BYTE                           byRes[128];                                /* Reserved */
}NETDEV_CLOUD_DEV_CHL_INFO_S,*LPNETDEV_CLOUD_DEV_CHL_INFO_S;

/**
 * @struct tagNETDEVPageQueryCond
 * @brief Pagination query condition information structure
 * @attention  None
 */
typedef struct tagNETDEVPageQueryCond
{
    INT32   dwQueryCond;                    /* Query condition 0: device status; the organization of the 1: device */
    INT32   dwSubQueryCond;                 /* Right value of the current query condition,It is used to supplement the state of equipment in query condition: 0 indicates offline, 1 indicates Online*/
    INT32   dwLogicalType;                  /* Query condition logic type: reference#NETDEV_QUERYCOND_LOGICTYPE_E */
    BYTE    byRes[128];                     /*  Reserved */
}NETDEV_PAGE_FIND_LOGIC_S,*LPNETDEV_PAGE_FIND_LOGIC_S;


/** 
 * @struct tagNETDEVPageQueryInfo
 * @brief Pagination query condition information structure
 * @attention  None
 */
typedef struct tagNETDEVPageQueryInfo
{
    INT32   dwLimitNum;                                          /* Number of single page query devices，Set size reference #NETDEV_PAGE_QUERY_CAP_INFO_S  In structure dwSuggestSinglePageQuantily*/
    INT32   dwStartID;                                           /* The starting ID of a single page query device,In continuous queries, you can use the last paging query to get the ID field +1 in the last device, As the beginning ID of this query*/
    INT32   dwCondNum;                                           /* Number of query conditions */
    NETDEV_PAGE_FIND_LOGIC_S  astFindCond[NETDEV_LEN_16];        /* List of query conditions information,The number of query conditions is up to 16,When the number of queries is 0,This node is optional */
    BYTE    byRes[128];                                          /* Reserved*/
}NETDEV_PAGE_FIND_COND_S,*LPNETDEV_PAGE_FIND_COND_S;



/**
 * @struct tagNETDEVPageQueryParam
 * @brief Paging query capability set information structure
 * @attention  None
 */
typedef struct tagNETDEVCloudDevPopulationInfo
{
    INT32   dwDevTotalNum;              /* All the current number of devices under the current cloud account */
    INT32   dwDevOfflineNum;            /* Current total number of offline devices under the current cloud account */
    BYTE    byRes[128];                 /* Reserved */
}NETDEV_CLOUD_DEV_POPUL_INFO_S,*LPNETDEV_CLOUD_DEV_POPUL_INFO_S;


typedef enum tagNETDEVAlarmSnapShotType
{
    NETDEV_ALARM_SNAPSHOT_MOTION_DETECT                     = 0,            /* Mobile alarm */
    NETDEV_ALARM_SNAPSHOT_VIDEO_LOST                        = 1,            /* Video loss alarm */
    NETDEV_ALARM_SNAPSHOT_AUDIO_DETECTION                   = 2,            /* Sound detection alarm */
    NETDEV_ALARM_SNAPSHOT_INPUT_SWITCH                      = 3,            /* Switch input alarm */

    NETDEV_ALARM_SNAPSHOT_INVALID                           = 0xFFFF        /* Invalid value */
}NETDEV_ALARM_SNAPSHOT_TYPE_E;

typedef struct tagNETDEVAlarmSnapShotCond
{
    INT32                           dwChannelID;                                /* Channel number */
    INT64                           tAlarmTime;                                 /* Alarm Time */
    NETDEV_ALARM_SNAPSHOT_TYPE_E    enAlarmType;                                /* Alarm Type */
    INT32                           dwInputSwitch;                              /* Switch number alarm number，The parameter is the channel number *100+ alarm output number ，The device itself channel number is 0*/
    BYTE                            byRes[240];                                 /* Reserved */
}NETDEV_ALARM_SNAPSHOT_COND_S,*LPNETDEV_ALARM_SNAPSHOT_COND_S;

typedef struct tagNETDEVAlarmSnapShotPicInfo
{
    CHAR    szURL[NETDEV_MAX_URL_LEN];  /* Picture URL */
    CHAR    szName[NETDEV_LEN_64];      /* Picture Name */
    INT32   dwSize;                     /* Picture Size */
    BYTE    byRes[256];                 /* Reserved */
}NETDEV_ALARM_SNAPSHOT_PIC_S,*LPNETDEV_ALARM_SNAPSHOT_PIC_S;

typedef struct tagNETDEVSnapShotFileInfo
{
    CHAR    szURL[NETDEV_MAX_URL_LEN];         /* Picture URL */
    BOOL    bSaveLocal;                        /* Whether it is saved locally, TURE means saving local, and FALSE means writing cache */
    CHAR    szFileName[NETDEV_LEN_260];        /* Save the local path and name of the picture */
    CHAR*   pcBuffer;                          /* To save the picture cache, we need to apply for memory, size dwSize cache size */
    INT32   dwSize;                            /* buffer size */
    BYTE    byRes[256];                        /* Reserved */
}NETDEV_PIC_FILE_INFO_S, *LPNETDEV_PIC_FILE_INFO_S;


/* Total number of plans allowed in a week, including Monday to Sunday */
#define NETDEV_VIDEO_PLAN_DAY_NUM_AWEEK               8   
/* Total number of plans allowed in a day*/
#define NETDEV_VIDEO_PLAN_TIME_SECTION_NUM_ADAY       8

/**
* @enum tagNETDEVPreRecordTime
* @brief PreRecordTime Enumeration definition
* @attention 
*/
typedef enum tagNETDEVPreRecordTime
{
    NETDEV_PRE_RECORD_TIME_ZERO =  0,            /* 0s */
    NETDEV_PRE_RECORD_TIME_FIVE =  5,            /* 5s */
    NETDEV_PRE_RECORD_TIME_TEN =   10,           /* 10s */
    NETDEV_PRE_RECORD_TIME_TWENTY =20,           /* 20s */
    NETDEV_PRE_RECORD_TIME_THIRTY =30,           /* 30s */
    NETDEV_PRE_RECORD_TIME_SIXTY = 60            /* 60s */
}NETDEV_PRE_RECORD_TIME_E;

/**
* @enum tagNETDEVPostRecordTime
* @brief PostRecordTime Enumeration definition
* @attention 
*/
typedef enum tagNETDEVPostRecordTime
{
    NETDEV_POST_RECORD_TIME_FIVE =                   5,             /* 5s */
    NETDEV_POST_RECORD_TIME_TEN =                    10,            /* 10s*/
    NETDEV_POST_RECORD_TIME_THIRTY =                 30,            /* 30s*/
    NETDEV_POST_RECORD_TIME_SIXTY =                  60,            /* 60s*/
    NETDEV_POST_RECORD_TIME_ONE_HUNDRED_AND_TWENTY = 120,           /* 120s*/
    NETDEV_POST_RECORD_TIME_THREE_HUNDRED =          300,           /* 300s*/
    NETDEV_POST_RECORD_TIME_SIX_HUNDRED =            600            /* 600s*/
}NETDEV_POST_RECORD_TIME_E;

/**
* @enum tagNETDEVDefencePlanEnable
* @brief Defence Plan Enable Enumeration definition
* @attention �?None
*/
typedef enum tagNETDEVDefencePlanEnable
{
    NETDEV_DEFENCE_PLAN_DISABLE = 0, 
    NETDEV_DEFENCE_PLAN_ENABLE =  1
}NETDEV_DEFENCE_PLAN_ENABLE_E;

/**
* @enum tagNETDEVArmingType
* @brief Alarm And Defence Type Enumeration definition
* @attention
*/
typedef enum tagNETDEVArmingType
{
    NETDEV_ARMING_TYPE_TIMING = 0,
    NETDEV_ARMING_TYPE_MOTIONDETEC = 1,
    NETDEV_ARMING_TYPE_ALARM =2,
    NETDEV_ARMING_TYPE_MOTIONDETEC_AND_ALARM =3,
    NETDEV_ARMING_TYPE_MOTIONDETEC_OR_ALARM  =4,
    NETDEV_ARMING_TYPE_NO_PLAN =5, 
    NETDEV_ARMING_TYPE_EVENT =10
}NETDEV_ARMING_TYPE_E;

/**
 * @struct tagNETDEVVideoTimeSection
 * @brief  Time Sections Structure definition
 * @attention  None
 */
typedef struct tagNETDEVVideoTimeSection
{
    CHAR    szBeginTime[NETDEV_LEN_64];              /*  Begin time */
    CHAR    szEndTime[NETDEV_LEN_64];                /*  End time */
    UINT32  udArmingType;                            /*  ArmingType  */
}NETDEV_VIDEO_TIME_SECTION_S, *LPNETDEV_VIDEO_TIME_SECTION_S;

/**
 * @struct tagNETDEVVideoDayPlan
 * @brief Play (Day) Structure definition
 * @attention �?None
 */
typedef struct tagNETDEVVideoDayPlan
{
    UINT32                         udwIndex;                                                  /* day index */
    UINT32                         udwSectionNum;
    NETDEV_VIDEO_TIME_SECTION_S    astTimeSection[NETDEV_VIDEO_PLAN_TIME_SECTION_NUM_ADAY];   /* Time Sections */
}NETDEV_VIDEO_DAY_PLAN_S, *LPNETDEV_VIDEO_DAY_PLAN_S;

/**
 * @struct tagNETDEVVideoPlanWeek
 * @brief  Plan (Week) Structure definition
 * @attention �?None
 */
typedef struct tagNETDEVVideoPlanWeek
{
    BOOL                        bEnabled;                                           
    UINT32                      udwDayNum;
    NETDEV_VIDEO_DAY_PLAN_S     astDayPlan[NETDEV_VIDEO_PLAN_DAY_NUM_AWEEK];     
    BYTE                        byRes[32];                                    
}NETDEV_VIDEO_WEEK_PLAN_S, *LPNETDEV_VIDEO_WEEK_PLAN_S;

/**
 * @struct tagNETDEVRecordRule
 * @brief  录像计划规则 结构体定�?  Record Rule Structure definition
 * @attention �?None
 */
typedef struct tagNETDEVRecordRule
{
    UINT32                      udwPreRecordTime;                                  /* 警前预录时间,参考NETDEV_PRE_RECORD_TIME_E */
    UINT32                      udwPostRecordTime;                                 /* 警后录像时间,参考NETDEV_POST_RECORD_TIME_E */
    BYTE                        byRes[32];                                         /* 保留字段 */
}NETDEV_RECORD_RULE_S, *LPNETDEV_RECORD_RULE_S;

/**
 * @struct tagNETDEVRecordPlanCfgInfo
 * @brief  录像计划配置信息 结构体定�?  Record plan config info Structure definition
 * @attention �?None
 */
typedef struct tagNETDEVRecordPlanCfgInfo
{
    BOOL                       bPlanEnable;                                        /* 计划使能 */
    BOOL                       bRedundantStorage;                                  /* 冗余录像使能 */
    NETDEV_RECORD_RULE_S       stRecordRule;                                       /* 录像计划规则 */
    NETDEV_VIDEO_WEEK_PLAN_S   stWeekPlan;                                         /* 计划配置 */
    BYTE                       byRes[128];                                         /* 保留字段 */
}NETDEV_RECORD_PLAN_CFG_INFO_S, *LPNETDEV_RECORD_PLAN_CFG_INFO_S;
/* END********************************************************************************************************** */


/**
* Type of pointer to media stream data callback function before being framed 
* @param [IN] lpPlayHandle       Current live playing handle
* @param [IN] pucBuffer          Pointer to buffer that stores stream data that is not framed
* @param [IN] dwBufSize          Buffer size
* @param [IN] dwMediaDataType    Media data type, see definitions of enumeration #NETDEV_MEDIA_DATA_TYPE_E
* @param [IN] lpUserParam        User-set parameters, specified by users when they call the #NDPlayer_SetSourceMediaDataCB function
* @return  . None.
* @note   Users should handle output stream data in a timely manner so that functions can be returned quickly. Otherwise, stream processing in the player will be affected.
*/
typedef void (STDCALL *NETDEV_SOURCE_DATA_CALLBACK_PF)(IN LPVOID        lpPlayHandle,
                                                       IN const BYTE    *pucBuffer,
                                                       IN INT32         dwBufSize,
                                                       IN INT32         dwMediaDataType,
                                                       IN LPVOID        lpUserParam
                                                       );

/**
* Type of pointer to callback function for framed stream data 
* @param [IN] lpPlayHandle           Current live playing handle
* @param [IN] pstParseVideoData      Pointer to buffer that stores framed video stream data
* @param [IN] lUserParam             User-set parameters, specified by users when they call the #NDPlayer_SetParseVideoDataCB function
* @return  . None.
* @note
* -  Users should handle output stream data in a timely manner so that functions can be returned quickly. Otherwise, stream processing in the player will be affected.
*/
typedef void (STDCALL *NETDEV_PARSE_VIDEO_DATA_CALLBACK_PF)(IN LPVOID lpPlayHandle,
                                                            IN const NETDEV_PARSE_VIDEO_DATA_S *pstParseVideoData,
                                                            IN LPVOID lpUserParam
                                                            );

/**
* Type of pointer to callback function for decoded video stream data 
* @param [IN] lpPlayHandle       Current live playing handle
* @param [IN] pstPictureData     Pointer to buffer that stores decoded video stream data
* @param [IN] lpUserParam        User-set parameters, specified by users when they call the #NDPlayer_SetDecodeVideoDataCB function
* @return  . None.
* @note
* -     1. Users should handle output stream data in a timely manner so that functions can be returned quickly. Otherwise, stream processing in the player will be affected.
* -     2. Video data is in yv12 format in sequence of Y0-Y1-......, U0-U1-......, V0-V1-......
*/
typedef void (STDCALL* NETDEV_DECODE_VIDEO_DATA_CALLBACK_PF)(IN LPVOID lpPlayHandle,
                                                             IN const NETDEV_PICTURE_DATA_S *pstPictureData,
                                                             IN LPVOID lpUserParam
                                                             );

/**
* Type of pointer to callback function for framed stream data 
* @param [IN] lpPlayHandle    Current live playing handle
* @param [IN] pstWaveData     Pointer to buffer that stores decoded audio stream data
* @param [IN] lpUserParam    User-set parameters, specified by users when they call the #NDPlayer_SetDecodeAudioDataCB function
* @return  . None.
* @note
* -     Users should handle output stream data in a timely manner so that functions can be returned quickly. Otherwise, stream processing in the player will be affected.
*/
typedef void (STDCALL* NETDEV_PARSE_AUDIO_DATA_CALLBACK_PF)(IN LPVOID lpPlayHandle,
                                                            IN const NETDEV_PARSE_AUDIO_DATA_S *pstParseAudioData,
                                                            IN LPVOID lpUserParam
                                                            );

/**
*  Type of pointer to callback function for decoded audio stream data 
* @param [IN] lpPlayHandle    Current live playing handle
* @param [IN] pstWaveData     Pointer to buffer that stores decoded audio stream data
* @param [IN] lpUserParam     User-set parameters, specified by users when they call the #NDPlayer_SetDecodeAudioDataCB function
* @return  . None.
* @note
* -     Users should handle output stream data in a timely manner so that functions can be returned quickly. Otherwise, stream processing in the player will be affected.
*/
typedef void (STDCALL* NETDEV_DECODE_AUDIO_DATA_CALLBACK_PF)(IN LPVOID lpPlayHandle,
                                                             IN const NETDEV_WAVE_DATA_S *pstWaveData,
                                                             IN LPVOID lpUserParam
                                                             );

/**
* Type of pointer to display data callback function
* @param [IN] lpHandle        Current live playing handle
* @param [IN] hdc             Display superficial hdc which can be used for drawing graphics.
* @param [IN] lpUserParam     User-set parameters, specified by users when they call the #NETDEV_SetPlayDisplayCB
* @return  .
* @note
* -     Users should handle output stream data in a timely manner so that functions can be returned quickly. Otherwise, stream processing in the player will be affected.
*/
typedef void (STDCALL* NETDEV_DISPLAY_CALLBACK_PF)(IN LPVOID lpHandle,
                                                   IN LPVOID hdc,
                                                   IN LPVOID lpUserParam
                                                   );

 /**
 * @struct tagNETDEVAlarmInfoEx
 * @brief  Alarm infomation Sturcture definition
 * @attention   None
 */
typedef struct tagNETDEVAlarmInfoEx
{ 
    INT32   dwAlarmType;                        /* Alarm type, see enumeration #NETDEV_ALARM_TYPE_E */
    INT64   tAlarmTime;                         /*Alarm time */
    INT32   dwChannelID;
    INT32  dwAlarmSrcType;                     
    CHAR    szAlarmSrcName[NETDEV_LEN_132];     

    UINT16  wIndex;                             /* index number */
    INT32   dwTotalBandWidth;                   /* Current total bandwidth (in MBps) */
    INT32   dwUnusedBandwidth;                  /* Bandwidth left (in MBps)*/
    INT32   dwTotalStreamNum;                   /* Total cameras*/
    INT32   dwFreeStreamNum;                    /* Cameras left */
    INT32   dwMediaMode;                        /* For enumerations, see#NETDEV_MEDIA_MODE_E*/

    BYTE    byRes[256]; 

}NETDEV_ALARM_INFO_EX_S, *LPNETDEV_ALARM_INFO_EX_S;

 /**
 * Callback function to receive alarm information
* @param [IN] lpUserID               User login ID
* @param [IN] dwChannelID            Channel ID
* @param [IN] NETDEV_ALARM_INFO_S    Alarm information
* @param [IN] lpBuf                  Pointer to buffer
* @param [IN] dwBufLen               Length of structure for alarm information
* @param [IN] lpUserData             User data
* @note
*/
typedef void(STDCALL *NETDEV_AlarmMessCallBack_PF)(IN LPVOID    lpUserID,
                                                   IN INT32     dwChannelID,
                                                   IN NETDEV_ALARM_INFO_S   stAlarmInfo,
                                                   IN LPVOID    lpBuf,
                                                   IN INT32     dwBufLen,
                                                   IN LPVOID    lpUserData
                                                   );

/**
* Callback function to receive alarm information
* @param [IN] lpUserID                  User login ID
* @param [IN] NETDEV_ALARM_INFO_V2_S    Alarm information
* @param [IN] lpUserData                User data
* @note
*/
typedef void(STDCALL *NETDEV_AlarmMessCallBackV2_PF)(IN LPVOID    lpUserID,
                                                   IN NETDEV_ALARM_INFO_EX_S   stAlarmInfo,
                                                   IN LPVOID    lpUserData
                                                   );

/**
* Callback function to receive exception and reconnection messages
* @param [IN] lpUserID      User login ID
* @param [IN] dwType        Type of exception or reconnection message: NETDEV_EXCEPTION_TYPE_E
* @param [IN] lpExpHandle   Exception type handle
* @param [IN] lpUserData    User data
* @note
*/
typedef void(STDCALL *NETDEV_ExceptionCallBack_PF)(IN LPVOID    lpUserID,
                                                   IN INT32     dwType,
                                                   IN LPVOID    lpExpHandle,
                                                   IN LPVOID    lpUserData
                                                   );
/**
 * Callback function for passenger flow statistic message
 * @param [IN] lpUserID                 User login ID
 * @param [IN] pstPassengerFlowData     Passenger flow data
 * @param [IN] lpUserData               User data
 * @note   None
 */
typedef void (STDCALL *NETDEV_PassengerFlowStatisticCallBack_PF)(IN LPVOID lpUserID,
                                                                 IN LPNETDEV_PASSENGER_FLOW_STATISTIC_DATA_S pstPassengerFlowData,
                                                                 IN LPVOID lpUserData
                                                                 );


/**
 * Callback function for Face snap Info
 * @param [IN] lpUserID                User login ID
 * @param [IN] pstFaceSnapShotData     Face snap data
 * @param [IN] lpUserData              User data
 * @note   None
 */
typedef void (STDCALL *NETDEV_FaceSnapshotCallBack_PF)(IN LPVOID lpUserID,
                                                       IN LPNETDEV_TMS_FACE_SNAPSHOT_PIC_INFO_S pstFaceSnapShotData,
                                                       IN LPVOID lpUserData
                                                       );

/**
 * Register callback function that used for count passenger flow
 * @param [IN] lpUserID                   User login ID
 * @param [IN] cbPassengerFlowStatisticCallBack      Callback function which will be registered
 * @param [IN] lpUserData                 User data
 */
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_SetPassengerFlowStatisticCallBack(IN LPVOID lpUserID, 
                                                                              IN NETDEV_PassengerFlowStatisticCallBack_PF cbPassengerFlowStatisticCallBack, 
                                                                              IN LPVOID lpUserData
                                                                              );

/**
 *  Register callback function and receive Face snap  information
 * @param [IN] lpUserID                   User login ID
 * @param [IN] cbFaceSnapshotCallBack     Callback function which will be registered
 * @param [IN] lpUserData                 User data
 */
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_SetFaceSnapshotCallBack(IN LPVOID lpUserID, 
                                                                    IN NETDEV_FaceSnapshotCallBack_PF cbFaceSnapshotCallBack, 
                                                                    IN LPVOID lpUserData
                                                                    );


/**
 * Callback function to receive heat map information
 * @param [IN] lpUserID                User login ID
 * @param [IN] pstHeatMapData          heat map Data 
 * @param [IN] lpUserData              User data
 * @note   None
 */

typedef void (STDCALL *NETDEV_HeatMapCallBack_PF)(IN LPVOID lpUserID,
                                                  IN LPNETDEV_TMS_HEAT_MAP_INFO_S pstHeatMapData,
                                                  IN LPVOID lpUserData
                                                  );

/**
 * Register callback function and receive heat map information
 * @param [IN] lpUserID                    User login ID
 * @param [IN] cbHeatMapCallBack           Callback function which will be registered
 * @param [IN] lpUserData                  User data
 */
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_SetHeatMapCallBack (IN LPVOID lpUserID, 
                                                                IN NETDEV_HeatMapCallBack_PF cbHeatMapCallBack, 
                                                                IN LPVOID lpUserData
                                                                );


/**
*  Callback function to receive vehicle license plate recognition information
* @param [IN] lpUserID                 User login ID
* @param [IN] pstCarPlateData          License plate recognition data 
* @param [IN] lpUserData               User data
* @note   None
*/
typedef void (STDCALL *NETDEV_CarPlateCallBack_PF)(IN LPVOID lpUserID,
                                                   IN LPNETDEV_TMS_CAR_PLATE_INFO_S pstCarPlateData,
                                                   IN LPVOID lpUserData
                                                   );

 /**
 * Register callback function and  vehicle license plate recognition
 * @param [IN] lpUserID                    User login ID
 * @param [IN] cbCarPlateCallBack          Callback function which will be registered
 * @param [IN] lpUserData                  User data
 */
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_SetCarPlateCallBack(IN LPVOID lpUserID, 
                                                                IN NETDEV_CarPlateCallBack_PF cbCarPlateCallBack, 
                                                                IN LPVOID lpUserData
                                                                );


/**
* Register callback function and receive alarm information, etc. (Call back login ID at the same time to distinguish different devices)\n
* @param [IN] lpUserID               User login ID
* @param [IN] cbAlarmMessCallBack    Callback function
* @param [IN] lpUserData             User data
* @return TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_SetAlarmCallBack(IN LPVOID lpUserID,
                                                             IN NETDEV_AlarmMessCallBack_PF cbAlarmMessCallBack,
                                                             IN LPVOID lpUserData
                                                             );

/**
* Register callback function and receive alarm information, etc. (Call back login ID at the same time to distinguish different devices)\n
* @param [IN] lpUserID              
* @param [IN] cbAlarmMessCallBack   Callback function
* @param [IN] pstSubscribeInfo      Alarm subscription info
* @param [IN] lpUserData            User data
* @return TRUE means success, and any other value means failure
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_SetAlarmCallBackV2(IN LPVOID lpUserID, IN NETDEV_AlarmMessCallBackV2_PF cbAlarmMessCallBack, IN LPNETDEV_ALARM_SUB_INFO_S pstSubscribeInfo, IN LPVOID lpUserData);

/************************************************************************/
/*                  Alarm Report                                     */
/************************************************************************/
/**
* Callback function to register SDK, receive exception and reconnection messages, etc.
* @param [IN] cbExceptionCallBack     Callback function to receive exception messages, used to call back information about current exceptions
* @param [IN] lpUserData                 User data
* @return  TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_SetExceptionCallBack(IN NETDEV_ExceptionCallBack_PF cbExceptionCallBack,
                                                                 IN LPVOID lpUserData
                                                                 );

/**
* Device discovery callback function
* @param [IN] pstDevInfo                 Device info
* @param [IN] lpUserData                 User data
* @note
*/
typedef void(STDCALL *NETDEV_DISCOVERY_CALLBACK_PF)(IN LPNETDEV_DISCOVERY_DEVINFO_S pstDevInfo,
                                                    IN LPVOID lpUserData
                                                    );

/**
* Registered device discovery callback function
* @param [IN] cbDiscoveryCallBack    Callback function
* @param [IN] lpUserData             User data
* @return TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_SetDiscoveryCallBack(IN NETDEV_DISCOVERY_CALLBACK_PF cbDiscoveryCallBack,
                                                                 IN LPVOID lpUserData
                                                                 );

/**
* This interface is used for device discovery. Please first register callback functions related to device discovery and use this interface for device discovery. Discovered device info will be included in the callback function.
* @param [IN]   pszBeginIP                 
* @param [IN]   pszEndIP                   
* @return TRUE means success, and any other value means failure
*/
NETDEV_API NEWINTERFACE BOOL  STDCALL NETDEV_Discovery(IN CHAR *pszBeginIP,
                                                       IN CHAR *pszEndIP
                                                       );

/**
* SDK initialization
* @return TRUE means success, and any other value means failure.
* @note  Thread not safe
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_Init(void);

/**
* SDK cleaning
* @return TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_Cleanup(void);

/**
*  Get SDK version information 
* @return  SDK version information
* @note
* - The two high bytes indicate the major version, and the two low bytes indicate the minor version. For example, 0x00030000 means version 3.0.
*/
NETDEV_API NEWINTERFACE INT32 STDCALL NETDEV_GetSDKVersion(void);



/**
* User login
* @param [IN]  pszDevIP          Device IP
* @param [IN]  wDevPort          Device server port
* @param [IN]  pszUserName      Username
* @param [IN]  pszPassword       Password
* @param [OUT] pstDevInfo        Pointer to device information structure
* @return Returned user login ID. 0 indicates failure, and other values indicate the user ID.
* @note
*/
NETDEV_API NEWINTERFACE LPVOID STDCALL NETDEV_Login(IN char *pszDevIP,
                                                    IN INT16 wDevPort,
                                                    IN char *pszUserName,
                                                    IN char *pszPassword,
                                                    OUT LPNETDEV_DEVICE_INFO_S pstDevInfo
                                                    );

/**
* User login
* @param  [IN]  pstLoginInfo          Login Info
* @return  Returned user login ID. 0 indicates failure, and other values indicate the user ID.
* @note
*/
NETDEV_API NEWINTERFACE LPVOID STDCALL NETDEV_LoginV2( IN LPNETDEV_LOGIN_INFO_S pstLoginInfo );

/**
* User logout
* @param [IN] lpUserID     User login ID
* @returnTRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_Logout(IN LPVOID lpUserID);

/**
* Get Device Infos
* @param [IN] lpUserID           User login handle
* @param [OUT] pstDevInfo        Pointer to device information structure
* @return   TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_GetDeviceInfo(IN LPVOID lpUserID ,OUT LPNETDEV_DEVICE_INFO_S pstDevInfo);

/**
* Query channel info list
* @param [IN]    lpUserID            User login ID
* @param [INOUT] pdwChlCount         Number of channels
* @param [OUT]   pstVideoChlList     List of channel info list
* @return   TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_QueryVideoChlDetailList(IN LPVOID   lpUserID,
                                                                    INOUT INT32 *pdwChlCount,
                                                                    OUT LPNETDEV_VIDEO_CHL_DETAIL_INFO_S pstVideoChlList
                                                                    );

/**
* Query channel info list
* @param [IN]    lpUserID            User login ID
* @param [INOUT] pdwChlCount         Number of channels
* @param [OUT]   pstVideoChlList     List of channel info list
* @return   TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_QueryVideoChlDetailListEx(IN LPVOID   lpUserID,
                                                                    INOUT INT32 *pdwChlCount,
                                                                    OUT LPNETDEV_VIDEO_CHL_DETAIL_INFO_EX_S pstVideoChlList
                                                                    );

/**
* Query video channel info
* @param [IN]   lpUserID            User login ID
* @param [IN]   dwChannelID         Channel ID
* @param [OUT]  pstVideoChlInfo     video channel info
* @return   TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_QueryVideoChlInfo(IN LPVOID lpUserID,
                                                              IN INT32 dwChannelID,
                                                              OUT LPNETDEV_VIDEO_CHL_DETAIL_INFO_S pstVideoChlInfo
                                                              );


/***************Begin live view services*********************************************/

/**
* Start live preview
* @param [IN]  lpUserID              User login ID
* @param [IN]  pstPreviewInfo        Preview parameter, see enumeration: NETDEV_PROTOCAL_E, NETDEV_LIVE_STREAM_INDEX_E.
* @param [IN]  cbRealDataCallBack    Pointer to callback function of stream data
* @param [IN]  lpUserData            User data
* @return  Returned user login ID. 0 indicates failure, and other values indicate the user ID.
* @note
*/
NETDEV_API NEWINTERFACE LPVOID STDCALL NETDEV_RealPlay(IN LPVOID lpUserID,
                                                       IN LPNETDEV_PREVIEWINFO_S pstPreviewInfo,
                                                       IN NETDEV_SOURCE_DATA_CALLBACK_PF cbPlayDataCallBack,
                                                       IN LPVOID lpUserData
                                                       );

/**
* Stop live preview
* @param [IN]  lpPlayHandle      Preview handle
* @return   TRUE means success, and any other value means failure.
* @note  Stop the live view started by NETDEV_RealPlay
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_StopRealPlay(IN LPVOID lpPlayHandle);

/**
* Local recording
* @param [IN]  lpPlayHandle          Preview handle
* @param [IN]  pszSaveFileName       Name of saved file
* @param [IN]  dwFormat              Format of saved file, see #NETDEV_MEDIA_FILE_FORMAT_E 
* @return   TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_SaveRealData(IN LPVOID  lpPlayHandle,
                                                         IN CHAR    *pszSaveFileName,
                                                         IN INT32   dwFormat
                                                         );

/**
* Stop local recording
* @param [IN]  lpPlayHandle      Preview handle
* @return   TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_StopSaveRealData(IN LPVOID lpPlayHandle);


/**
* Get window bit rate
* @param [IN]  lpPlayHandle      Preview\playback handle
* @param [OUT] pdwBitRate        Pointer to obtained bit rate
* @return   TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_GetBitRate(IN LPVOID lpPlayHandle,
                                                       OUT INT32 *pdwBitRate
                                                       );

/*
* Get window frame rate
* @param [IN]  lpPlayHandle      Preview\playback handle
* @param [OUT] pdwFrameRate      Pointer to obtained frame rate
* @return   TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_GetFrameRate(IN LPVOID lpPlayHandle,
                                                         OUT INT32 *pdwFrameRate
                                                         );

/**
* Get window encoding format
* @param [IN]  lpPlayHandle           Preview\playback handle
* @param [OUT] pdwVideoEncFmt         Pointer to obtained encoding format, see NETDEV_VIDEO_CODE_TYPE_E
* @return   TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_GetVideoEncodeFmt(IN LPVOID lpPlayHandle,
                                                              OUT INT32 *pdwVideoEncFmt
                                                              );


/**
* Get video resolution
* @param [IN]  lpPlayHandle      Preview\playback handle
* @param [OUT] pdwWidth          Pointer to obtained resolution �?width
* @param [OUT] pdwHeight         Pointer to obtained resolution �?height
* @return   TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_GetResolution(IN LPVOID lpPlayHandle,
                                                          OUT INT32 *pdwWidth,
                                                          OUT INT32 *pdwHeight
                                                          );

/**
* Get window packet loss rate
* @param [IN]  lpPlayHandle      Preview\playback handle
* @param [OUT] pulRecvPktNum     Pointer to number of received packets
* @param [OUT] pulLostPktNum     Pointer to number of lost packets
* @return   TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_GetLostPacketRate(IN LPVOID lpPlayHandle,
                                                              OUT INT32 *pulRecvPktNum,
                                                              OUT INT32 *pulLostPktNum
                                                              );

/**
*  Reset window packet loss rate
* @param [IN]  lpPlayHandle   Preview\playback handle
* @return   TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_ResetLostPacketRate(IN LPVOID lpPlayHandle);

/**
* Live view snapshot
* @param [IN]  lpPlayHandle      Preview\playback handle
* @param [IN]  pszFileName       File path to save images (including file name)
* @param [IN]  dwCaptureMode     Image saving format, see #NETDEV_PICTURE_FORMAT_E
* @return   TRUE means success, and any other value means failure.
* @note  File format suffix is not required in the file name
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_CapturePicture(IN LPVOID    lpPlayHandle,
                                                           IN char      *pszFileName,
                                                           IN INT32     dwCaptureMode
                                                           );

/**
* Modify image display ratio
* @param [IN]  lpPlayHandle    Preview\playback handle
* @param [IN]  enRenderScale   Image display ratio
* @return   TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_SetRenderScale(IN LPVOID lpPlayHandle,
                                                           IN NETDEV_RENDER_SCALE_E enRenderScale
                                                           );

/**
* Get the current image info
* @param [IN]  lpPlayHandle     Preview\playback handle
* @param [IN]  pstImageInfo    Image information list
* @return   TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_GetVideoEffect(IN LPVOID lpPlayHandle, 
                                                           OUT LPNETDEV_VIDEO_EFFECT_S pstImageInfo
                                                           );

/**
*  Adjust the current image
* @param [IN]  lpPlayHandle    Preview\playback handle
* @param [IN]  pstImageInfo    Image information list
* @return   TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_SetVideoEffect(IN LPVOID lpPlayHandle, 
                                                           IN LPNETDEV_VIDEO_EFFECT_S pstImageInfo
                                                           );

/**
* Set Digital zoom
* @param [IN] lpPlayHandle     Preview\playback handle
* @param [IN] hWnd             window handle 
* @param [IN] pstRect          Rectangle Area
* @return   TRUE means success, and any other value means failure.
* @note All images will be displayed with digital zoom disabled when pstRect is null
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_SetDigitalZoom(IN LPVOID          lpPlayHandle, 
                                                           IN LPVOID          hWnd,
                                                           IN LPNETDEV_RECT_S pstRect
                                                           );

/**
* Set pictuer fluency
* @param [IN] lpPlayHandle         Preview\playback handle
* @param [IN] dwFluency            Fluency, reference to #NETDEV_PICTURE_FLUENCY_E
* @return   TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_SetPictureFluency(IN LPVOID lpPlayHandle,
                                                              IN INT32 dwFluency
                                                              );

/**
* Callback function to register streams (original stream)
* @param [IN]  lpPlayHandle                Live preview handle
* @param [IN]  cbSourceDataCallBack        Callback function for stream data
* @param [IN]  bContinue                   Whether to continue to following framing, decoding and displaying operations.
* @param [IN]  lpUser                      User data
* @return   TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE  BOOL STDCALL NETDEV_SetPlayDataCallBack(IN LPVOID lpPlayHandle,
                                                                 IN NETDEV_SOURCE_DATA_CALLBACK_PF cbPlayDataCallBack,
                                                                 IN INT32 bContinue,
                                                                 IN LPVOID lpUser);

/**
* Callback function to register live stream (framed stream data)
* @param [IN]  lpPlayHandle               Preview\playback handle
* @param [IN]  cbParsePlayDataCallBack    Data callback function
* @param [IN]  bContinue                  Whether to continue to following decoding and displaying operations.
* @param [IN]  lpUserData                 User data
* @return   TRUE means success, and any other value means failure.
* @note
* - To shut the callback function, set the second parameter as NULL.
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_SetPlayParseCB(IN LPVOID    lpPlayHandle,
                                                           IN NETDEV_PARSE_VIDEO_DATA_CALLBACK_PF cbParsePlayDataCallBack,
                                                           IN INT32     bContinue,
                                                           IN LPVOID    lpUserData
                                                           );

/**
* Callback function to register live stream (decoded media stream data)
* @param [IN]  lpPlayHandle                  Preview\playback handle
* @param [IN]  cbPlayDecodeVideoCALLBACK     Data callback function
* @param [IN]  bContinue                     Whether to continue to following displaying operations.
* @param [IN]  lpUserData                    User data
* @return   TRUE means success, and any other value means failure.
* @note
* - To shut the callback function, set the second parameter as NULL.
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_SetPlayDecodeVideoCB(IN LPVOID  lpPlayHandle,
                                                                 IN NETDEV_DECODE_VIDEO_DATA_CALLBACK_PF cbPlayDecodeVideoCALLBACK,
                                                                 IN INT32   bContinue,
                                                                 IN LPVOID  lpUserData
                                                                 );

/**
*  Callback function to register audio stream (framed stream data)
* @param [IN]  lpPlayHandle                 Preview\playback handle
* @param [IN]  cbPlayParseAudioCallBack     Data callback function
* @param [IN]  bContinue                    Whether to continue to playing operations.
* @param [IN]  lpUserData                   User data
* @return   TRUE means success, and any other value means failure.
* @note
* - To shut the callback function, set the second parameter as NULL.
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_SetPlayParseAudioCB(IN LPVOID lpPlayHandle,
                                                                IN NETDEV_PARSE_AUDIO_DATA_CALLBACK_PF cbPlayParseAudioCallBack,
                                                                IN INT32 bContinue,
                                                                IN LPVOID lpUserData
                                                                );

/**
*  Callback function to register audio stream (decoded media stream data)
* @param [IN]  lpPlayHandle                  Preview\playback handle
* @param [IN]  cbPlayDecodeAudioCallBack     Data callback function
* @param [IN]  bContinue                     Whether to continue to playing operations.
* @param [IN]  lpUserData                    User data
* @return   TRUE means success, and any other value means failure.
* @note
* - To shut the callback function, set the second parameter as NULL.
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_SetPlayDecodeAudioCB(IN LPVOID lpPlayHandle,
                                                                 IN NETDEV_DECODE_AUDIO_DATA_CALLBACK_PF cbPlayDecodeAudioCallBack,
                                                                 IN INT32 bContinue,
                                                                 IN LPVOID lpUserData
                                                                 );

/**
* Modify displayed data callback
* @param [IN]  lpPlayHandle              Preview\playback handle
* @param [IN]  cbPlayDisplayCallBack     Data callback function
* @param [IN]  lpUserData                User data
* @return   TRUE means success, and any other value means failure.
* @note
* - To shut the callback function, set the second parameter as NULL.
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_SetPlayDisplayCB(IN LPVOID lpPlayHandle,
                                                             IN NETDEV_DISPLAY_CALLBACK_PF cbPlayDisplayCallBack,
                                                             IN LPVOID lpUserData
                                                             );

/**
* Start two-way audio
* @param [IN]  lpUserID                   User ID
* @param [IN]  dwChannelID                Channel ID
* @param [IN]  cbRealDataCallBack         Pointer to callback function of the stream data 
* @param [IN]  lpUserData                 User data
* @return  Returned user ID. 0 means failure, and any other value is a user ID.
* @note
*/
NETDEV_API NEWINTERFACE LPVOID STDCALL NETDEV_StartVoiceCom(IN LPVOID lpUserID,
                                                            IN INT32 dwChannelID,
                                                            IN NETDEV_DECODE_AUDIO_DATA_CALLBACK_PF cbPlayDataCallBack,
                                                            IN LPVOID lpUserData
                                                            );

/**
* Stop two-way audio
* @param [IN]  lpPlayHandle    Two-way audio handle
* @return   TRUE means success, any other value indicates failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_StopVoiceCom(IN LPVOID lpPlayHandle);

/**
* Turn on microphone
* @param [IN]  lpPlayHandle    Preview handle
* @return   TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_OpenMic(IN LPVOID lpPlayHandle);

/**
* Turn off microphone
* @param [IN]  lpPlayHandle    Preview handle
* @return   TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_CloseMic(IN LPVOID lpPlayHandle);

/**
* Adjust sound volume of microphone
* @param [IN]  lpPlayHandle      Preview handle 
* @param [IN]  dwVolume          Sound volume
* @return   TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_MicVolumeControl(IN LPVOID lpPlayHandle,
                                                             IN INT32 dwVolume
                                                             );

/**
* Get mic volume
* @param [IN]  lpPlayHandle      Preview handle
* @param [IN]  pdwVolume         Volume
* @return   TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_GetMicVolume(IN LPVOID lpPlayHandle, 
                                                         OUT INT32* pdwVolume
                                                         );

/**
* Get mute status
* @param [IN]  lpPlayHandle      Preview handle
* @param [OUT]  pbMute           Mute status
* @return   TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_GetMuteStatus(IN LPVOID lpPlayHandle, 
                                                          OUT BOOL* pbMute
                                                          );

/**
* Set mute status
* @param [IN]  lpPlayHandle      Preview handle
* @param [IN]  bMute             Mute status
* @return   TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_SetMuteStatus(IN LPVOID lpPlayHandle, 
                                                          IN BOOL bMute
                                                          );


/**
* Enable sound
* @param [IN]  lpPlayHandle    Preview handle
* @return   TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_OpenSound(IN LPVOID lpPlayHandle);

/**
* Control sound volume
* @param [IN]  lpPlayHandle    Preview handle
* @param [IN]  dwVolume        Volume
* @return   TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_SoundVolumeControl(IN LPVOID lpPlayHandle, 
                                                               IN INT32 dwVolume
                                                               );

/**
* Get sound volume
* @param [IN]  lpPlayHandle      Preview handle
* @param [IN]  pdwVolume         Volume
* @return   TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_GetSoundVolume(IN LPVOID lpPlayHandle, 
                                                           OUT INT32* pdwVolume
                                                           );

/**
*  Close Sound
* @param [IN]  lpPlayHandle    Preview handle
* @return   TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_CloseSound(IN LPVOID lpPlayHandle);


/**
* @enum tagNETDEVAudioSampleFormatType
* @brief 
* @attention �?
*/
typedef enum tagNetDevAudioSampleFormatType
{
    NETDEV_AUDIO_SAMPLE_FMT_NONE = -1,
    NETDEV_AUDIO_SAMPLE_FMT_U8      = 0,            
    NETDEV_AUDIO_SAMPLE_FMT_S16     = 1,          
    NETDEV_AUDIO_SAMPLE_FMT_S32     = 2,          
    NETDEV_AUDIO_SAMPLE_FMT_FLT     = 3, 
    NETDEV_AUDIO_SAMPLE_FMT_DBL     = 4 
}NETDEV_AUDIO_SAMPLE_FORMAT_E;

/**
* @struct tagNETDEVAudioSampleParamType
* @brief 
* @attention �?
*/
typedef struct tagNETDEVAudioSampleParamType
{
    INT32 dwChannels;                              
    INT32 dwSampleRate;                             
    NETDEV_AUDIO_SAMPLE_FORMAT_E enSampleFormat;    
}NETDEV_AUDIO_SAMPLE_PARAM_S, *LPNETDEV_AUDIO_SAMPLE_PARAM_S;

/**
* Start Input Voice
* @param [IN]  lpUserID                 ID
* @param [IN]  dwChannelID              ChannelID
* @param [IN]  cbRealDataCallBack       Real Data CallBack
* @param [IN]  lpUserData               UserData
* @return TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE LPVOID STDCALL NETDEV_StartInputVoiceSrv(IN LPVOID lpUserID,
                                                                 IN INT32 dwChannelID
                                                                 );

/**
* Stop Input Voice
* @param [IN]  lpVoiceComHandle   Handle
* @return TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_StopInputVoiceSrv(IN LPVOID lpVoiceComHandle);

/**
* Input Voice Data\n
* @param [IN]  lpVoiceComHandle         Handle
* @param [IN] lpDataBuf                 DataBuf
* @param [IN] dwDataLen                 DataLen
* @param [IN] pstVoiceParam             VoiceParam
* @return TRUE means success, and any other value means failure.
* @note�?
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_InputVoiceData(IN LPVOID lpVoiceComHandle,
                                                           IN LPVOID lpDataBuf,
                                                           IN INT32 dwDataLen,
                                                           IN LPNETDEV_AUDIO_SAMPLE_PARAM_S pstVoiceParam
                                                           );

														   /**
* Parse Voice Data Callback.\n
* @param [IN] lpVoiceComHandle      Handle
* @param [IN] lpWaveData            Wave Data 
* @param [IN] lpUserParam           UserParam 
* @param [IN] dwReserved            DataLen
* @return �?
*/
typedef VOID (STDCALL *NETDEV_PARSE_VOICE_DATA_CALLBACK_PF)(IN LPVOID lpVoiceComHandle,
                                                            IN const LPNETDEV_WAVE_DATA_S lpWaveData,
                                                            IN LPVOID lpUserParam,
                                                            IN INT32 dwReserved
                                                            );

/**
* Parse Voice Data Callback\n
* @param [IN]  lpPlayHandle                 Preview\playback handle
* @param [IN]  cbPlayDecodeVideoCALLBACK     Data callback function
* @param [IN]  bContinue                     Continue or not
* @param [IN]  lpUserData                    User data
* @return TRUE means success, and any other value means failure.
* @note
* - To shut the callback function, set the second parameter as NULL.
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_SetParseVoiceDataCB(IN LPVOID  lpPlayHandle,
                                                                IN NETDEV_PARSE_VOICE_DATA_CALLBACK_PF cbDecodeVideoCB,
                                                                IN INT32   bContinue,
                                                                IN LPVOID  lpUserParam
                                                                );

/*************** live view service*************************************************/

/*************** Begin playback service********************************************/

/**
*  Query recording files according to file type and time
* @param [IN]  lpUserID      User login ID
* @param [IN]  pstFindCond    Search condition
* @return Return 0 indicates failure,Other values are used as NETDEV_FindClose Function param.
Recording search service number. 0 means failure. Other values are used as the handle parameters of functions like NETDEV_FindClose.
* @note This function returns the video query business number,If the return value is not 0, the query video file is successful�?
*/
NETDEV_API NEWINTERFACE LPVOID STDCALL NETDEV_FindFile(IN LPVOID lpUserID,
                                                       IN LPNETDEV_FILECOND_S pstFindCond
                                                       );

/**
* Obtain the information of found files one by one.
* @param [IN]  lpFindHandle      File Find Handle File search handle
* @param [OUT] pstFindData       Pointer to save file information
* @return   TRUE means success, and any other value means failure.
* @note Return failure explains the end of the query A returned failure indicates the end of search.
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_FindNextFile(IN LPVOID lpFindHandle,
                                                         OUT LPNETDEV_FINDDATA_S pstFindData
                                                         );

/**
* Close file search and release resources
* @param [IN] lpFindHandle   File Find Handle File search handle
* @return   TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_FindClose(IN LPVOID lpFindHandle);


/**
* Play back recording files by name
* @param [IN] lpUserID           User login ID
* @param [IN] pstPlayBackInfo    Pointer to recording playback structure, see LPNETDEV_PLAYBACKINFO_S
* @return   TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE LPVOID STDCALL NETDEV_PlayBackByName(IN LPVOID lpUserID,
                                                             IN LPNETDEV_PLAYBACKINFO_S pstPlayBackInfo
                                                             );

/**
* Play back recording by time. 
* @param [IN] lpUserID           User login ID
* @param [IN] pstPlayBackCond    Pointer to playback-by-time structure, see LPNETDEV_PLAYBACKCOND_S
* @return   TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE LPVOID STDCALL NETDEV_PlayBackByTime(IN LPVOID lpUserID,
                                                             IN LPNETDEV_PLAYBACKCOND_S pstPlayBackInfo
                                                             );

/**
* Stop playback service
* @param [IN] lpPlayHandle   Playback handle
* @return   TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_StopPlayBack(IN LPVOID lpPlayHandle);

/**
* Download recordings by file name
* @param [IN]  lpUserID              User login ID
* @param [IN]  pstPlayBackInfo       Pointer to recording playback structure, see LPNETDEV_PLAYBACKINFO_S
* @param [IN]  *pszSaveFileName      Downloaded file save path on PC, must be an absolute path (including file name)
* @param [IN]  dwFormat              Recording file saving format
* @return  Return 0 indicates failure,Other values are used as NETDEV_StopGetFile Function param. Download handle. 0 means failure. Other values are used as the handle parameters of functions like NETDEV_StopGetFile.
* @note
*/
NETDEV_API NEWINTERFACE LPVOID STDCALL NETDEV_GetFileByName(IN LPVOID  lpUserID,
                                                            IN LPNETDEV_PLAYBACKINFO_S pstPlayBackInfo,
                                                            IN char    *pszSaveFileName,
                                                            IN INT32   dwFormat
                                                            );


/**
*  Download recordings by time
* @param [IN]  lpUserID                 User login ID
* @param [IN]  pstPlayBackCond          Pointer to playback-by-time structure, see LPNETDEV_PLAYBACKCOND_S
* @param [IN]  *pszSaveFileName         Downloaded file save path on PC, must be an absolute path (including file name)
* @param [IN]  dwFormat                 Recording file saving format
* @return , Return 0 indicates failure,Other values are used as NETDEV_StopGetFile Function param. Download handle. 0 means failure. Other values are used as the handle parameters of functions like NETDEV_StopGetFile.
* @note
*/
NETDEV_API NEWINTERFACE LPVOID STDCALL NETDEV_GetFileByTime(IN LPVOID lpUserID, 
                                                            IN LPNETDEV_PLAYBACKCOND_S pstPlayBackCond, 
                                                            IN char *pszSaveFileName, 
                                                            IN INT32 dwFormat
                                                            );

/**
* Stop downloading recording files
* @param [IN]  lpPlayHandle   Playback handle
* @return   TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_StopGetFile(IN LPVOID lpPlayHandle);


/**
* Control recording playback status.
* @param [IN]  lpPlayHandle     Playback or download handle
* @param [IN]  dwControlCode    Command for controlling recording playback status, see NETDEV_VOD_PLAY_CTRL_E
* @param [INOUT]  lpBuffer      Pointer to input/output parameters. For playing speed, see NETDEV_VOD_PLAY_STATUS_E. The type of playing time: INT64.
* @return   TRUE means success, and any other value means failure.
* @note  When playing, pause or resume videos, set IpBuffer as NULL.
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_PlayBackControl(IN LPVOID   lpPlayHandle,
                                                            IN INT32    dwControlCode,
                                                            INOUT LPVOID lpBuffer
                                                            );




/*********** End playback service ************************************************ */

/***********Begin PTZ control ************************************************* */
/**
* PTZ preset operation (preview required)
* @param [IN]  lpPlayHandle          Live preview handle
* @param [IN]  dwPTZPresetCmd        PTZ preset operation commands, see NETDEV_PTZ_PRESETCMD_E
* @param [IN]  pszPresetName         Preset name
* @param [IN]  dwPresetID            Preset number (starting from 1). Up to 255 presets are supported.
* @return   TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_PTZPreset(IN LPVOID lpPlayHandle,
                                                      IN INT32  dwPTZPresetCmd,
                                                      IN CHAR   *pszPresetName,
                                                      IN INT32  dwPresetID
                                                      );

/**
* PTZ preset operation (preview not required)
* @param [IN]  lpUserID              User login ID
* @param [IN]  dwChannelID           Channel ID
* @param [IN]  dwPTZPresetCmd        PTZ preset operation commands, see NETDEV_PTZ_PRESETCMD_E
* @param [IN]  pszPresetName         Preset name
* @param [IN]  dwPresetID            Preset number (starting from 1). Up to 255 presets are supported.
* @return   TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_PTZPreset_Other(IN LPVOID   lpUserID,
                                                            IN INT32    dwChannelID,
                                                            IN INT32    dwPTZPresetCmd,
                                                            IN CHAR     *pszPresetName,
                                                            IN INT32    dwPresetID
                                                            );

/**
*   PTZ control operation (preview required)
* @param [IN]  lpPlayHandle          Live preview handle
* @param [IN]  dwPTZCommand          control commands, see #NETDEV_PTZ_E
* @param [IN]  dwSpeed               Speed of PTZ control, which is configured according to the speed control value of different decoders. Value ranges from 1 to 9.
* @return   TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_PTZControl(IN LPVOID    lpPlayHandle,
                                                       IN INT32     dwPTZCommand,
                                                       IN INT32     dwSpeed
                                                       );


/**
*  PTZ control operation (preview not required)
* @param [IN]  lpUserID              User login ID
* @param [IN]  dwChannelID           Channel ID
* @param [IN]  dwPTZCommand         PTZ control commands, see #NETDEV_PTZ_E
* @param [IN]  dwSpeed              Speed of PTZ control, which is configured according to the speed control value of different decoders. Value ranges from 1 to 9.
* @return   TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_PTZControl_Other(IN LPVOID  lpUserID,
                                                             IN INT32   dwChannelID,
                                                             IN INT32   dwPTZCommand,
                                                             IN INT32   dwSpeed
                                                             );

/**
* Get PTZ preset patrol route
* @param [IN]   lpUserID             User login ID
* @param [IN]   dwChannelID          Channel ID
* @param [OUT]  pstCruiseList        Patrol route list
* @return    TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_PTZGetCruise(IN LPVOID  lpUserID,
                                                         IN INT32   dwChannelID,
                                                         OUT LPNETDEV_CRUISE_LIST_S pstCruiseList
                                                         );

/**
*  PTZ preset patrol operation (preview not required)
* @param [IN]  lpUserID              User login ID
* @param [IN]  dwChannelID           Channel ID
* @param [IN]  dwPTZCruiseCmd        PTZ patrol operation commands, see #NETDEV_PTZ_CRUISECMD_E
* @param [IN]  pstCruiseInfo         PTZ patrol route information, see #LPNETDEV_CRUISE_INFO_S
* @return    TRUE means success, and any other value means failure.
* @note
* - 1. Patrol route. Up to 16 routes are supported (starting from 1).
* - 2. Patrol point. Up to 32 points are supported (starting from 1).
* - 3.Preset (max 255), time (max 255) and speed (max 40).
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_PTZCruise_Other(IN LPVOID lpUserID,
                                                            IN INT32 dwChannelID,
                                                            IN INT32 dwPTZCruiseCmd,
                                                            IN LPNETDEV_CRUISE_INFO_S pstCruiseInfo
                                                            );


/**
*   PTZ preset patrol operation (preview required)
* @param [IN]  lpPlayHandle          Live preview handle
* @param [IN]  dwPTZCruiseCmd         PTZ patrol operation commands, see NETDEV_PTZ_CRUISECMD_E
* @param [IN]  pstCruiseInfo          PTZ patrol route information, see #LPNETDEV_CRUISE_INFO_S
* @return    TRUE means success, and any other value means failure.
* @note
* - 1.Patrol route ID cannot be modified.
* - 2.  New routes are added one after another.
* - 3. When deleting, starting or stopping patrol, enter patrol route ID in pstCruiseInfo.
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_PTZCruise(IN LPVOID lpPlayHandle,
                                                      IN INT32 dwPTZCruiseCmd,
                                                      IN LPNETDEV_CRUISE_INFO_S pstCruiseInfo
                                                      );


/**
* Get PTZ patrol route
* @param [IN]   lpUserID             User login ID
* @param [IN]   dwChannelID          Channel ID
* @param [OUT]  pstTrackCruiseInfo   Patrol route list, see #LPNETDEV_PTZ_TRACK_INFO_S
* @return    TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_PTZGetTrackCruise(IN LPVOID  lpUserID,
                                                              IN INT32   dwChannelID,
                                                              OUT LPNETDEV_PTZ_TRACK_INFO_S pstTrackCruiseInfo
                                                              );

/**
* PTZ route patrol operation (preview not required)
* @param [IN]  lpUserID              User login ID
* @param [IN]  dwChannelID           Channel ID
* @param [IN]  dwPTZCruiseCmd        PTZ route patrol operation commands, see #NETDEV_PTZ_TRACKCMD_E
* @param [INOUT]  pszTrackCruiseName           Route patrol name, suggested length #NETDEV_LEN_64
* @return    TRUE means success, and any other value means failure.
* @note
* - 1.Only one patrol route allowed.
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_PTZTrackCruise(IN LPVOID lpUserID,
                                                           IN INT32 dwChannelID,
                                                           IN INT32 dwPTZTrackCruiseCmd,
                                                           INOUT CHAR *pszTrackCruiseName
                                                           );

/**
* Drag to zoom in and out (preview required)
* @param [IN]  lpPlayHandle          Live preview handle
* @param [IN]  pstPtzOperateArea     Drag-to-zoom structure information
* @return   TRUE means success, and any other value means failure.
* @note  In our NVR, this interface is supported only when our camera is connected through private protocol.
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_PTZSelZoomIn(IN LPVOID lpPlayHandle, 
                                                         IN LPNETDEV_PTZ_OPERATEAREA_S pstPtzOperateArea
                                                         );

/**
* Drag to zoom in and out(preview not required)
* @param lpUserID                    User login ID
* @param [IN]  dwChannelID           Channel ID
* @param [IN]  pstPtzOperateArea     Drag-to-zoom structure information
* @return   TRUE means success, and any other value means failure.
* @note  In our NVR, this interface is supported only when our camera is connected through private protocol.
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_PTZSelZoomIn_Other(IN LPVOID lpUserID,
                                                               IN INT32 dwChannelID,
                                                               IN LPNETDEV_PTZ_OPERATEAREA_S pstPtzOperateArea
                                                               );

/**
* PTZ Home position (preview not required)
* @param [IN]  lpUserID                   User login ID
* @param [IN]  dwChannelID                Channel ID
* @param [IN]  dwPTZHomePositionCmd       PTZ home position control commond #NETDEV_PTZ_HOMEPOSITIONCMD_E
* @return   TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_PTZHomePosition_Other(IN LPVOID lpUserID, 
                                                                  IN INT32 dwChannelID, 
                                                                  IN INT32 dwPTZHomePositionCmd
                                                                  );

/**
* PTZ Home position (preview required)
* @param [IN]  lpRealHandle             Live preview handle
* @param [IN]  dwPTZHomePositionCmd     home position control commond #NETDEV_PTZ_HOMEPOSITIONCMD_E
* @return   TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_PTZHomePosition(IN LPVOID lpRealHandle, 
                                                            IN INT32 dwPTZHomePositionCmd
                                                            );
/**
* PTZ absolute move
* @param [IN]  lpUserID                    User login ID
* @param [IN]  dwChannelID                 Channel ID
* @param [IN]  pstAbsoluteMove             PTZ absolute move info
* @return   TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_PTZAbsoluteMove(IN LPVOID lpUserID,
                                                            IN INT32 dwChannelID,
                                                            IN LPNETDEV_PTZ_ABSOLUTE_MOVE_S pstAbsoluteMove
                                                            );

/**********  End PTZ control ************************************************/

/**********  Begin remote parameter configuration ***********************/
/**
* Obtain device capability
* @param [IN]   lpUserID                 User login ID
* @param [IN]  dwChannelID               Channel ID
* @param [IN]   dwCommand                NETDEV_CAPABILITY_COMMOND_E
* @param [OUT]  lpOutBuffer              Pointer to buffer that receives data
* @param [OUT]  dwOutBufferSize          Length (in byte) of buffer that receives data, cannot be 0.
* @param [OUT]  pdwBytesReturned         Pointer to length of received data, cannot be NULL.
* @return   TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_GetDeviceCapability(IN LPVOID lpUserID,
                                                                IN INT32 dwChannelID,
                                                                IN INT32 dwCommand,
                                                                OUT LPVOID lpOutBuffer,
                                                                OUT INT32  dwOutBufferSize,
                                                                OUT INT32  *pdwBytesReturned
                                                                );

/**
* Get configuration information of device
* @param [IN]   lpUserID                 User login ID
* @param [IN]   dwChannelID              Channel ID
* @param [IN]   dwCommand                Device configuration commands, see #NETDEV_CONFIG_COMMAND_E
* @param [OUT]  lpOutBuffer              Pointer to buffer that receives data
* @param [OUT]  dwOutBufferSize          Length (in byte) of buffer that receives data, cannot be 0.
* @param [OUT]  pdwBytesReturned         Pointer to length of received data, cannot be NULL.
* @return   TRUE means success, and any other value means failure.
* @note
* - 1. Route ID cannot be modified.
* - 2. New routes are added one after another.
* - 3. When deleting, starting or stoping a patrol route, enter route ID in pstCruiseInfo.
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_GetDevConfig(IN LPVOID  lpUserID,
                                                         IN INT32   dwChannelID,
                                                         IN INT32   dwCommand,
                                                         OUT LPVOID lpOutBuffer,
                                                         OUT INT32  dwOutBufferSize,
                                                         OUT INT32  *pdwBytesReturned
                                                         );

/**
* Modify device configuration information
* @param [IN]   lpUserID             User login ID
* @param [IN]   dwChannelID          Channel ID
* @param [IN]   dwCommand            Device configuration commands, see #NETDEV_CONFIG_COMMAND_E
* @param [IN]   lpInBuffer           Pointer to buffer of input data
* @param [IN]   dwInBufferSize       Length of input data buffer (byte)
* @return   TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_SetDevConfig(IN LPVOID  lpUserID,
                                                         IN INT32   dwChannelID,
                                                         IN INT32   dwCommand,
                                                         IN LPVOID  lpInBuffer,
                                                         IN INT32   dwInBufferSize
                                                         );



/**************  End remote parameter configuration ******************************/
/**
* reboot\n
* Restart device\n
* @param [IN]  lpUserID      User login ID
* @return   TRUE means success, and any other value means failure.
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_Reboot(IN LPVOID lpUserID);

/**
* Restore to factory default settings
* @param [IN]  lpUserID      User login ID
* @return   TRUE means success, and any other value means failure.
* @note . Restore all parameters to factory settings, except network settings and user settings.
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_RestoreConfig(IN LPVOID lpUserID);

/**
* Get error codes
* @return  Error codes
*/
NETDEV_API NEWINTERFACE INT32 STDCALL NETDEV_GetLastError();

/**
* Get alarm information from the device
* @param [IN]  lpUserID         User login ID
* @param [IN]  dwPullWaitTime  Alarm wait time (s)
* @param [INOUT] pdwListCnt     Maximum number of alarms. When working as an input parameter, it indicates the length of alarm information list; when working as an output parameter, it indicates the actual number of alarms.
* @param [OUT]   pstPullAlarmList    List of alarm information. The memory should be allocated in advance.
* @return   TRUE means success, and any other value means failure.
* note:  Calling the function will block login and logout. It is not recommended to wait for a long time.
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_PullAlarm(IN LPVOID lpUserID, 
                                                      IN INT32 dwPullWaitTime, 
                                                      INOUT INT32 *pdwListCnt, 
                                                      OUT LPNETDEV_PULLALARM_INFO_S pstPullAlarmList
                                                      );

/**
*  Snapshot without preview
* @param [IN]  lpUserID              User login ID
* @param [IN]  dwChannelID           Channel ID
* @param [IN]  dwStreamType;         Stream type, see enumeration #NETDEV_LIVE_STREAM_INDEX_E 
* @param [IN]  pszFileName          File path to save images (including file name)
* @param [IN]  dwCaptureMode           Image saving format, see #NETDEV_PICTURE_FORMAT_E
* @return    TRUE means success, and any other value means failure.
* @note
        Only JPG format is supported.
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_CaptureNoPreview(IN LPVOID lpUserID,
                                                             IN INT32 dwChannelID,
                                                             IN INT32 dwStreamType,
                                                             IN CHAR *pszFileName,
                                                             IN INT32 dwCaptureMode
                                                             );

/**
* Dynamically create an I frame\n 
* @param [IN] lpUserID         User login ID
* @param [IN] dwChannelID      Channel ID
* @param [IN] dwStreamType     See enumeration NETDEV_LIVE_STREAM_INDEX_E
* @return NETDEV_E_SUCCEED    NETDEV_E_SUCCEED means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_MakeKeyFrame(IN LPVOID lpUserID,
                                                         IN INT32 dwChannelID,
                                                         IN INT32 dwStreamType
                                                         );

/**
* Set keep-alive parameters
* @param [IN]  dwWaitTime              Waiting time
* @param [IN]  dwTrytimes              Connecting attempts
* @return   TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_SetConnectTime(IN INT32 dwWaitTime,
                                                           IN INT32 dwTrytimes
                                                           );

/**
* Set device name
* @param [IN] lpUserID          User login ID
* @param [IN] pszDeviceName     Dev Name  Device name
* @return    TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_ModifyDeviceName(IN LPVOID lpUserID,
                                                             IN CHAR *pszDeviceName
                                                             );

/**
* Get UPnP net state info
* @param [IN]   lpUserID      User login ID
* @param [IN]   pstNatState   UPnP nat state info
* @return    TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_GetUpnpNatState(IN LPVOID lpUserID,
                                                            OUT LPNETDEV_UPNP_NAT_STATE_S pstNatState
                                                            );

/**
* Set UPnP net state info
* @param [IN]   lpUserID                   User login ID
* @param [IN]   pstNatState                UPnP nat state info
* @return    TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_SetUpnpNatState(IN LPVOID lpUserID,
                                                            IN LPNETDEV_UPNP_NAT_STATE_S pstNatState
                                                            );

/**
* Set log path
* @param [IN]   pszLogPath    Log path (file name not included)
* @return    TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_SetLogPath(IN CHAR *pszLogPath);

/**
* Get device System time configuration
* @param [IN]  pstSystemTimeInfo      Pointer to time configuration structure
* @return    TRUE means success, and any other value means failure.
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_GetSystemTimeCfg(IN LPVOID lpUserID,
                                                             OUT LPNETDEV_TIME_CFG_S pstSystemTimeInfo
                                                             );

/**
* Set device system time configuration
* @param [IN]  pstSystemTimeInfo      Pointer to time configuration structure
* @return    TRUE means success, and any other value means failure.
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_SetSystemTimeCfg(IN LPVOID lpUserID,
                                                             IN LPNETDEV_TIME_CFG_S pstSystemTimeInfo
                                                             );

/**
* Set timeout
* @param [IN]  pstRevTimeout          Pointer to timeout
* @return      TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_SetRevTimeOut( IN LPNETDEV_REV_TIMEOUT_S pstRevTimeout);


/**
* User login to cloud account
* @param [IN]  pszCloudSrvUrl         Cloud server URL 
* @param [IN]  pszUserName            Cloud account name
* @param [IN]  pszPassWord            Cloud account password 
* @return   Returned user ID. 1 means failure, any other value is a user ID.
* @note 
*/
NETDEV_API NEWINTERFACE LPVOID STDCALL NETDEV_LoginCloud(IN CHAR *pszCloudSrvUrl,
                                                         IN CHAR *pszUserName,
                                                         IN CHAR *pszPassWord
                                                         );

/**
* Cloud device login
* @param [IN]  lpUserID               Cloud account login ID 
* @param [IN]  pCloudInfo             Cloud device login info 
* @param [OUT] pstDevInfo             Pointer to device info structure
* @return Returned user ID. 1 means failure, any other value is a user ID.
* @note 
    1.The szDevicePassword field in pCloudInfo must be filled in.
    2.Deprecated, call NETDEV_LoginCloudDevEx().
*/
NETDEV_API NEWINTERFACE LPVOID STDCALL NETDEV_LoginCloudDev(IN LPVOID lpUserID,
                                                            IN LPNETDEV_CLOUD_DEV_LOGIN_S pstCloudInfo, 
                                                            OUT LPNETDEV_DEVICE_INFO_S pstDevInfo
                                                            );

/**
* Cloud device login
* @param [IN]  lpUserID               Cloud account login ID 
* @param [IN]  pCloudInfo             Cloud device login info 
* @param [OUT] pstDevInfo             Pointer to device info structure
* @return Returned user ID. 1 means failure, any other value is a user ID.
* @note 
    1.The szDevicePassword field in pCloudInfo must be filled in.
*/
NETDEV_API NEWINTERFACE LPVOID STDCALL NETDEV_LoginCloudDevEx(IN LPVOID lpUserID,
                                                              IN LPNETDEV_CLOUD_DEV_LOGIN_EX_S pstCloudInfo, 
                                                              OUT LPNETDEV_DEVICE_INFO_S pstDevInfo
                                                              );


/**
* Cloud device login with dynamic password
* @param [IN]  lpUserID               ID Cloud account login ID
* @param [IN]  pCloudInfo             Cloud device login info
* @param [OUT] pstDevInfo              Pointer to device info structure
* @return  Returned user ID. 1 means failure, any other value is a user ID.
* @note 
    1.The szDevicePassword field in pCloudInfo needs not to be filled in.
    2.Deprecated, call NETDEV_ LoginByDynamicEx().
*/
NETDEV_API NEWINTERFACE LPVOID STDCALL NETDEV_LoginByDynamic(IN LPVOID lpUserID,
                                                             IN LPNETDEV_CLOUD_DEV_LOGIN_S pstCloudInfo,
                                                             OUT LPNETDEV_DEVICE_INFO_S pstDevInfo
                                                             );

/**
* Cloud device login with dynamic password
* @param [IN]  lpUserID               Cloud account login ID
* @param [IN]  pCloudInfo             Cloud device login info
* @param [OUT] pstDevInfo              Pointer to device info structure
* @return  Returned user ID. 1 means failure, any other value is a user ID.
* @note 
    1.The szDevicePassword field in pCloudInfo needs not to be filled in.
*/
NETDEV_API NEWINTERFACE LPVOID STDCALL NETDEV_LoginByDynamicEx(IN LPVOID lpUserID,
                                                               IN LPNETDEV_CLOUD_DEV_LOGIN_EX_S pstCloudInfo,
                                                               OUT LPNETDEV_DEVICE_INFO_S pstDevInfo
                                                               );

/**
*  Query device list under a cloud account
* @param [IN]  lpUserID             User login ID
* @return ,Return 0 indicates failure,Other values are used as NETDEV_FindNextCloudDevInfo.NETDEV_FindCloseDevList Function param.
Service ID. 0 means failure, any other value will be used as parameter of functions including NETDEV_FindNextCloudDevInfo and NETDEV_FindCloseDevList.
* @note  The function’s return value is the service number to search cloud device list. 0 means success:
    1.Use above service number as input parameter lpFindHandle for NETDEV_FindNextCloudDevInfo.
    2.After searching, use above service number as input parameter lpFindHandle for NETDEV_FindCloseCloudDevList.Call NETDEV_FindCloseCloudDevList to release resource and close search.
*   3.Deprecated, call NETDEV_ FindCloudDevListEx().
*/
NETDEV_API NEWINTERFACE LPVOID STDCALL NETDEV_FindCloudDevList(IN LPVOID lpUserID);


/**
*    Obtain info about detected devices one by one
* @param [IN]  lpFindHandle            Search handle
* @param [OUT] pstDevInfo              Pointer to saved device info
* @return   TRUE means success, and any other value means failure.
* @note 
    1.Return failure explains the end of the query A returned failure indicates the end of search.
    2.Deprecated, call NETDEV_ FindNextCloudDevInfoEx().
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_FindNextCloudDevInfo(IN LPVOID lpFindHandle,
                                                                 OUT LPNETDEV_CLOUD_DEV_INFO_S pstDevInfo
                                                                 );

/**
* Stop search and release resource 
* @param [IN] lpFindHandle  Find Handle File search handle
* @return   TRUE means success, and any other value means failure.
* @note
    1.Deprecated, call NETDEV_ FindCloseCloudDevListEx().
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_FindCloseCloudDevList(IN LPVOID lpFindHandle);

/**
* Query device list under a cloud account
* @param [IN]  lpUserID             User login ID
* @return Return 0 indicates failure,Other values are used as NETDEV_FindNextCloudDevInfo.NETDEV_FindCloseDevList Function param.
Service ID. 0 means failure, any other value will be used as parameter of functions including NETDEV_FindNextCloudDevInfo and NETDEV_FindCloseDevList.
*/
NETDEV_API NEWINTERFACE LPVOID STDCALL NETDEV_FindCloudDevListEx(IN LPVOID lpUserID);

/**
* Obtain info about detected devices one by one
* @param [IN]  lpFindHandle          Search handle
* @param [OUT] pstDevInfo            Pointer to saved device info
* @return   TRUE means success, and any other value means failure.
* @note Return failure explains the end of the query A returned failure indicates the end of search.
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_FindNextCloudDevInfoEx(IN LPVOID lpFindHandle,
                                                                   OUT LPNETDEV_CLOUD_DEV_INFO_EX_S pstDevInfo
                                                                   );

/**
* Stop search and release resource 
* @param [IN] lpFindHandle  Find Handle File search handle
* @return   TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_FindCloseCloudDevListEx(IN LPVOID lpFindHandle);

/**
* Obtain cloud device info by register code
* @param [IN]  lpUserID               User login ID
* @param [IN]  pszRegisterCode        Register code
* @param [IN]  pstDevInfo             Cloud device info
* @return     TRUE means success, any other value indicates failure.
* @note  Discarded interface, suggested use NETDEV_GetCloudDevBasicInfoByRegCode
    1.Deprecated, call NETDEV_ GetCloudDevInfoByRegCodeEx().   
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_GetCloudDevInfoByRegCode(IN LPVOID lpUserID,
                                                                     IN CHAR *pszRegisterCode,
                                                                     OUT LPNETDEV_CLOUD_DEV_INFO_S pstDevInfo
                                                                     );

/**
* Obtain cloud device info by register code
* @param [IN]  lpUserID              User login ID
* @param [IN]  pszRegisterCode       Register code
* @param [IN]  pstDevInfo             Cloud device info
* @return     TRUE means success, any other value indicates failure.
* @note    Discarded interface, suggested use NETDEV_GetCloudDevBasicInfoByRegCode
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_GetCloudDevInfoByRegCodeEx(IN LPVOID lpUserID,
                                                                       IN CHAR *pszRegisterCode,
                                                                       OUT LPNETDEV_CLOUD_DEV_INFO_EX_S pstDevInfo
                                                                       );

/**
* Obtain cloud device info by device name
* @param [IN]  lpUserID              User login ID
* @param [IN]  pszDevName            Device name
* @param [IN]  pstDevInfo            Cloud device info
* @return     TRUE means success, any other value indicates failure.
* @note  
    1.Deprecated, call NETDEV_ GetCloudDevInfoByNameEx().
    2. Discarded interface, suggested use NETDEV_GetCloudDevBasicInfoByName
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_GetCloudDevInfoByName(IN LPVOID lpUserID,
                                                                  IN CHAR *pszDevName,
                                                                  OUT LPNETDEV_CLOUD_DEV_INFO_S pstDevInfo
                                                                  );

/**
* Obtain cloud device info by device name
* @param [IN]  lpUserID              User login ID
* @param [IN]  pszDevName            Device name
* @param [IN]  pstDevInfo            Cloud device info
* @return     TRUE means success, any other value indicates failure.
* @note   Discarded interface, suggested use  NETDEV_GetCloudDevBasicInfoByName
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_GetCloudDevInfoByNameEx(IN LPVOID lpUserID,
                                                                    IN CHAR *pszDevName,
                                                                    OUT LPNETDEV_CLOUD_DEV_INFO_EX_S pstDevInfo
                                                                    );

/**
*  Start voice broadcast
* @param [IN]  lpUserID          User login ID
* @param [IN]  dwChannelID       Channel ID
* @return  Returned user ID. 0 means failure, and any other value is a user ID.
* @note  Voice broadcast and two-way audio for one channel are available.
*/
NETDEV_API NEWINTERFACE LPVOID STDCALL NETDEV_StartVoiceBroadcast(IN LPVOID lpUserID, 
                                                                  IN INT32 dwChannelID
                                                                  );

/**
*  Stop voice broadcast
* @param [IN]  lpPlayHandle    voice broadcast handle
* @return   TRUE means success, any other value indicates failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_StopVoiceBroadcast(IN LPVOID lpPlayHandle);

/**
*  Start manual record
* @param [IN]   lpUserID                 User login ID
* @param [IN]   pstManualRecordCfg       Manual record config
* @return   TRUE means success, any other value indicates failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_StartManualRecord(IN LPVOID lpUserID,
                                                              IN LPNETDEV_MANUAL_RECORD_CFG_S pstManualRecordCfg
                                                              );
/**
*  Stop manual record
* @param [IN]   lpUserID                 User login ID
* @param [IN]   pstManualRecordCfg       Manual record config
* @return   TRUE means success, any other value indicates failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_StopManualRecord(IN LPVOID lpUserID,
                                                             IN LPNETDEV_MANUAL_RECORD_CFG_S pstManualRecordCfg
                                                             );


/**
*  Query video distribution information by month 
* @param [IN]   lpUserID             User login ID
* @param [IN]   dwChannelID           Channel ID
* @param [IN]   pstMonthInfo          Month information
* @param [OUT]   pstMonthStatus       Video status in the month
* @return   TRUE means success, any other value indicates failure.
* @note 
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_QuickSearch(IN LPVOID lpUserID, 
                                                        IN INT32 dwChannelID , 
                                                        IN LPNETDEV_MONTH_INFO_S pstMonthInfo,
                                                        OUT LPNETDEV_MONTH_STATUS_S pstMonthStatus
                                                        );

/**
* Get daynums of Specify Channel
* @param [IN]   lpUserID                    User login ID
* @param [IN]   dwChannelID                 Channel ID
* @param [OUT]   dwDayNums                  Video daynums
* @return TRUE means success, any other value indicates failure.
* @note�?
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_GetVideoDayNums(IN LPVOID lpUserID, 
                                                            IN INT32 dwChannelID ,
                                                            OUT UINT32 *dwDayNums);
/**
* Obtain traffic statistic
* @param [IN]   lpUserID                 User login ID
* @param [OUT]  pstPeopleCounter         People counting list
* @return   TRUE means success, any other value indicates failure.
* @note none
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_GetTrafficStatistic(IN LPVOID lpUserID,
                                                                IN LPNETDEV_TRAFFIC_STATISTICS_COND_S pstStatisticCond,
                                                                OUT LPNETDEV_TRAFFIC_STATISTICS_DATA_S pstTrafficStatistic
                                                                );

/**
*  Set log file size and number
* @param [IN] dwLogFileSize      The size of single log file
* @param [IN] dwLogFileNum       Log file number
* @return   TRUE means success, any other value indicates failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_ConfigLogFile(IN INT32 dwLogFileSize,
                                                          IN INT32 dwLogFileNum
                                                          );

/**
*  Obtain geolocation info
* @param [IN]   lpUserID                ID User login ID
* @param [IN]   dwChannelID             Channel ID
* @param [OUT]  pstGPSInfo              Geolocation info
* @return   TRUE means success, and any other value means failure.
* @note none
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_GetGeolocationInfo(IN LPVOID lpUserID,
                                                               IN INT32 dwChannelID,
                                                               OUT LPNETDEV_GEOLACATION_INFO_S pstGPSInfo
                                                               );

/**
* Obtain wifi sniffer mac list
* @param [IN]   lpUserID                ID User login ID
* @param [IN]   dwChannelID             Channel ID
* @param [OUT]  pstMACList               Wifi sniffer Mac address array
* @return   TRUE means success, and any other value means failure.
* @note none
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_GetWifiSnifferMacList(IN LPVOID lpUserID,
                                                                  IN INT32 dwChannelID,
                                                                  OUT LPNETDEV_WIFISNIFFER_MAC_LIST_S pstMACList
                                                                  );

/**
* Obtain compass info
* @param [IN]   lpUserID                ID User login ID
* @param [IN]   dwChannelID             Channel ID
* @param [OUT]  pfCompassInfo           Electronic compass info
* @return   TRUE means success, and any other value means failure.
* @note none
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_GetCompassInfo(IN LPVOID lpUserID,
                                                           IN INT32 dwChannelID,
                                                           OUT FLOAT *pfCompassInfo
                                                           );

/**
*  Obtain Live view stream url
* @param [IN]  lpUserID             ID User login ID
* @param [IN]  dwChannelID          Channel ID
* @param [IN]  dwStreamType         Stream Type, #Stream type see enumeration#NETDEV_LIVE_STREAM_INDEX_E
* @param [OUT] pszStreamUrl         StreamURL Stream URL,The length must exceed NETDEV_LEN_260
* @return   TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_GetStreamUrl(IN LPVOID  lpUserID, 
                                                         IN INT32   dwChannelID,
                                                         IN INT32   dwStreamType,
                                                         OUT CHAR   *pszStreamUrl
                                                         );

/**
*  Obtain replay url
* @param [IN]  lpUserID             ID User login ID
* @param [IN]  dwChannelID          Channel ID
* @param [IN]  dwStreamType         Stream Type , Stream type see enumeration#NETDEV_LIVE_STREAM_INDEX_E
* @param [OUT] pszReplayUrl  Stream URL, The length must exceed NETDEV_LEN_260
* @return   TRUE means success, and any other value means failure.
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_GetReplayUrl(IN LPVOID  lpUserID, 
                                                         IN INT32   dwChannelID,
                                                         IN INT32   dwStreamType,
                                                         OUT CHAR   *pszReplayUrl
                                                         );



/**
* Fast Real Play By Url\n
* @param [IN]  lpUserID             User Login ID
* @param [IN]  pszUrl               streamURL
* @param [IN]  pstPreviewInfo       Preview Info,#NETDEV_PROTOCAL_E,NETDEV_LIVE_STREAM_INDEX_E.
* @param [IN]  cbRealDataCallBack   ,CallBack
* @param [IN]  lpUserData           , User Data
* @return return User Login ID,return 0 is Failed ,Other values indicate the returned user ID value.
* @note
*/
NETDEV_API NEWINTERFACE LPVOID STDCALL NETDEV_FastRealPlayByUrl(IN LPVOID lpUserID,
                                                                IN CHAR *pszUrl,
                                                                IN LPNETDEV_PREVIEWINFO_S pstPreviewInfo,
                                                                IN NETDEV_SOURCE_DATA_CALLBACK_PF cbPlayDataCallBack,
                                                                IN LPVOID lpUserData
                                                                );


/**
* Play back recording by url. 
* @param [IN] lpUserID           User login ID
* @param [IN]  pszUrl            stream URL
* @param [IN] pstPlayBackParam    LPNETDEV_PLAYBACKPARAM_S Pointer to playback-by-time structure, see LPNETDEV_PLAYBACKPARAM_S
* @return return User Login ID,return 0 is Failed ,Other values indicate the returned user ID value.
* @note
*/
NETDEV_API NEWINTERFACE LPVOID STDCALL NETDEV_FastPlayBackByUrl( IN LPVOID lpUserID,
                                                                IN CHAR *pszUrl,
                                                                IN LPNETDEV_PLAYBACKPARAM_S pstPlayBackParam
                                                                );


/**
* Search NVR log by log type and time
* @param [IN]  lpUserID               ID User login ID
* @param [IN]  pstLogFindCond         Log search condition
* @return Other values are used as NETDEV_CloseFindLog Function param�?
Log search service number. NETDEV_E_FAILED means failure, and any other value is used as the parameter of functions like NETDEV_CloseFindLog.
* @note
*/
NETDEV_API NEWINTERFACE LPVOID STDCALL NETDEV_FindLogInfoList(IN LPVOID lpUserID,
                                                              IN LPNETDEV_FIND_LOG_COND_S pstLogFindCond
                                                              );

/**
* Find Next Log Info Obtain logone by one
* @param [IN]  lFindHandle            Log search handle
* @param [OUT] pstFindData            Pointer to saved log info
* @return  NETDEV_E_SUCCEED means success, and any other value means failure
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_FindNextLogInfo(IN LPVOID lpFindHandle,
                                                            OUT LPNETDEV_LOG_INFO_S pstLogInfo
                                                            );

/**
* Close log search and release resource
* @param [IN]  lFindHandle            File Find Handle File search handle
* @return  NETDEV_E_SUCCEED means success, and any other value means failure
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_FindCloseLogInfo(IN LPVOID lpFindHandle);


/**
* reset people counting
* @param [IN]   lpUserID              User login ID
* @param [IN]   dwChannelID           Channel ID
* @return  TRUE means success, and any other value means failure.
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_ResetPassengerFlow(IN LPVOID lpUserID,
                                                               IN INT32 dwChannelID
                                                               );



/**
* Add Cloud Org
* @param [IN] lpUserID                  Cloud Login ID
* @param [IN] dwParentOrgID             Parent Org ID
* @param [IN] pszOrgName                Org Name
* @param [OUT] pdwOrgID                 new Org ID
* @return TRUE means success, and any other value means failure
* @note 
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_AddCloudOrg(IN LPVOID lpUserID,
                                                        IN INT32 dwParentOrgID,
                                                        IN CHAR* pszOrgName,
                                                        OUT INT32 *pdwOrgID
                                                        );

/**
* Modify Cloud Org
* @param [IN] lpUserID                  Cloud Login ID
* @param [IN] dwOrgID                   Org ID
* @param [IN] pszOrgName                Org Name
* @return TRUE means success, and any other value means failure
* @note 
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_ModifyCloudOrg(IN LPVOID lpUserID,
                                                           IN INT32 dwOrgID,
                                                           IN CHAR* pszOrgName
                                                           );

/**
* Delete Cloud Org
* @param [IN] lpUserID              Cloud Login ID
* @param [IN] dwOrgID               Org ID
* @param [IN] dwDeleteMode          Delete Mode
* @return TRUE means success, and any other value means failure
* @note 
*        Mode 1，Delete all sub organizations under the organization. If these organizations have devices, they are classified under the root node root�?
*        Mode 2，If the organization has other sub organizations or equipment, it is not allowed to delete
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_DeleteCloudOrg(IN LPVOID lpUserID,
                                                           IN INT32 dwOrgID,
                                                           IN INT32 dwDeleteMode
                                                           );

/**
* Get Cloud Org List.\n
* @param [IN]  lpUserID             Cloud Login ID
* @param [OUT] pstOrgList           Org List
* @return  TRUE means success, and any other value means failure
* @note  
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_GetCloudOrgList(IN LPVOID lpUserID,
                                                            OUT LPNETDEV_CLOUD_ORG_LIST_S pstOrgList
                                                            );



/**
* Add Cloud Device.\n
* @param [IN]  lpUserID             ID User login ID
* @param [IN]  pszDevRegisterCode   Dev Register Code
* @param [IN]  pszDevName           Dev Name
* @param [OUT] pstDevBase           Cloud Dev Base
* @return  TRUE means success, and any other value means failure
* @note  
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_AddCloudDevice(IN LPVOID lpUserID,
                                                           IN CHAR *pszDevRegisterCode,
                                                           IN CHAR *pszDevName,
                                                           OUT LPNETDEV_CLOUD_DEV_BASE_INFO_S pstDevBase
                                                           );

/**
* Modify Cloud Dev Name.\n
* @param [IN]  lpUserID             ID User login ID
* @param [IN]  pszDevName           Dev Name
* @return  TRUE means success, and any other value means failure
* @note  
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_ModifyCloudDevName(IN LPVOID lpUserID,
                                                               IN CHAR *pszDevUserName,
                                                               IN CHAR *pszDevName
                                                               );

/**
* Modify Cloud Share Dev Name..\n
* @param [IN]  lpUserID             ID User login ID
* @param [IN]  pszDevUserName       Cloud Dev ID
* @param [IN]  pszDevName           Dev Name
* @return  TRUE means success, and any other value means failure
* @note  
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_ModifyCloudShareDevName(IN LPVOID lpUserID,
                                                                    IN CHAR *pszDevUserName,
                                                                    IN CHAR *pszDevName
                                                                    );

/**
* Delete Cloud Device.\n
* @param [IN]  lpUserID             ID User login ID
* @param [IN]  pszDevUserName       Cloud Dev ID
* @return  TRUE means success, and any other value means failure
* @note  
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_DeleteCloudDevice(IN LPVOID lpUserID,
                                                              IN CHAR *pszDevUserName
                                                              );


/**
* Add Device Org
* @param [IN] lpUserID                  Cloud Login ID
* @param [IN] pstCloudDevBindInfo       Cloud Dev Bind Info
* @param [IN] dwOrgID                   Org ID
* @return TRUE means success, and any other value means failure
* @note 
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_AddDevice2Org(IN LPVOID lpUserID,
                                                          IN LPNETDEV_CLOUD_DEV_BASE_INFO_S pstCloudDevBindInfo,
                                                          IN INT32 dwOrgID
                                                          );

/**
* Get Cloud Dev Population
* @param [IN]  lpUserID                         Cloud Login ID
* @param [OUT] pstCloudDevPopulInfo             Cloud Dev Population Info
* @return  TRUE means success, and any other value means failure
* @note  
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_GetCloudDevPopulation(IN LPVOID lpUserID,
                                                                  OUT LPNETDEV_CLOUD_DEV_POPUL_INFO_S pstCloudDevPopulInfo
                                                                  );


/**
* Find Cloud Dev Chl List
* @param [IN] lpUserID                      Cloud Login ID
* @param [IN] pszDeviceSN                   Cloud Device SN
* @return  Query Handler,Return 0 indicates failure，Other values are used as NETDEV_FindNextCloudDevChlList、NETDEV_FindCloseCloudDevChlList Function param�?
* @note
*/
NETDEV_API NEWINTERFACE LPVOID STDCALL NETDEV_FindCloudDevChlList(IN LPVOID lpUserID,
                                                                  IN CHAR* pszDeviceSN
                                                                  );

/**
* Find Next Cloud Dev Chl Info
* @param [IN]  lpFindHandle             Find Handle 
* @param [OUT] pstCloudDevChlInfo       Cloud Dev Chl Info
* @return TRUE means success, and any other value means failure 
* @note 
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_FindNextCloudDevChlInfo(IN LPVOID lpFindHandle, 
                                                                    OUT LPNETDEV_CLOUD_DEV_CHL_INFO_S pstCloudDevChlInfo
                                                                    );

/**
* Find Close Cloud Dev Chl List
* @param [IN] lpFindHandle                              Find Handle 
* @return TRUE means success, and any other value means failure
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_FindCloseCloudDevChlList(IN LPVOID lpFindHandle);

/**
* Set ClientID
* @param [IN] pszClientID                              Client ID 
* @return TRUE means success, and any other value means failure
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_SetClientID(IN CHAR *pszClientID);


/**
* Set T2U PayLoad
* @param [IN]   dwT2UPayload         T2U Payload,MTU:101-1500 ，defaute 1500�?
* @return TRUE means success, and any other value means failure TRUE means success, and any other value means failure.
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_SetT2UPayLoad(IN INT32 dwT2UPayload);


/**
* Get xw Channels Num\n
* @param [IN]  lpUserID                     User Login ID
* @param [OUT] pstChannels                  Channel Num
* @return TRUE means success, and any other value means failure
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_GetChannelsNum(IN LPVOID lpUserID, 
                                                              OUT LPNETDEV_XW_CHANNELS_NUM_S pstChannels
                                                              );
/**
* Get XW Channels Info List\n
* @param [IN]  lpUserID                     User Login ID
* @param [INOUT] pstChannelsList            Channels List
* @return TRUE means success, and any other value means failure
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_GetChannelsInfoList(IN LPVOID   lpUserID,
                                                                   INOUT LPNETDEV_XW_CHANNELS_LIST_S pstChannelsList
                                                                   );


/**
* Get XW Capability\n
* @param [IN]  lpUserID                     User Login ID
* @param [OUT] pstCapInfo                   Capability info
* @return TRUE means success, and any other value means failure
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_GetCapability(IN LPVOID lpUserID, 
                                                             OUT LPNETDEV_XW_CAP_INFO_S pstCapInfo
                                                             );

/**
* Get Last Change\n
* @param [IN]  lpUserID                     User Login ID
* @param [OUT] pudwLastChange               Last Change
* @return TRUE means success, and any other value means failure
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_GetLastChange(IN LPVOID lpUserID, 
                                                             OUT UINT32 *pudwLastChange
                                                             );

/**
* Delete All Cfg\n
* @param [IN]  lpUserID                     User Login ID
* @return TRUE means success, and any other value means failure
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_DeleteAllCfg(IN LPVOID lpUserID);

/**
* Find TVWall Cfg List
* @param [IN] lpUserID                      User Login ID
* @return  Query Handler,Return to NULL is failure，Other values are used as NETDEV_XW_FindNextTVWallCfg、NETDEV_XW_FindCloseTVWallCfg Function param�?
* @note 
*/
NETDEV_API NEWINTERFACE LPVOID STDCALL NETDEV_XW_FindTVWallCfgList(IN LPVOID lpUserID);

/**
* Find Next TVWall Cfg
* @param [IN]  lpFindHandle                 Find Handle 
* @param [OUT] pstTVWallCfg                 TVWall Cfg info 
* @return TRUE means success, and any other value means failure
* @note Return failure explains the end of the query
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_FindNextTVWallCfg(IN LPVOID lpFindHandle, 
                                                                 OUT LPNETDEV_XW_TVWALL_CFG_S pstTVWallCfg
                                                                 );

/**
* Find Close TVWall Cfg
* @param [IN] lpFindHandle                   File Find Handle File search handle
* @return TRUE means success, and any other value means failure
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_FindCloseTVWallCfg(IN LPVOID lpFindHandle);

/**
* Create TVWall Cfg\n
* @param [IN]  lpUserID                     User Login ID
* @param [INOUT] pstTVWallCfg               TVWall Cfg info，return TvWall ID
* @param [OUT]   pudwLastChange           
* @return TRUE means success, and any other value means failure
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_CreateTVWallCfg(IN LPVOID lpUserID, 
                                                               INOUT LPNETDEV_XW_TVWALL_CFG_S pstTVWallCfg,
                                                               OUT UINT32 *pudwLastChange
                                                               );

/**
* Get TVWall Cfg\n
* @param [IN]  lpUserID                     User Login ID
* @param [INOUT] pstTVWallCfg               TVWall Cfg info，input TvWall ID
* @return TRUE means success, and any other value means failure
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_GetTVWallCfg(IN LPVOID lpUserID,
                                                            INOUT LPNETDEV_XW_TVWALL_CFG_S pstTVWallCfg
                                                            );

/**
* Modify TVWall Cfg\n
* @param [IN]  lpUserID                     User Login ID
* @param [IN]  pstTVWallCfg                 TVWall Cfg info，input TvWall ID
* @param [OUT] pudwLastChange              
* @return TRUE means success, and any other value means failure
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_ModifyTVWallCfg(IN LPVOID lpUserID,
                                                               IN LPNETDEV_XW_TVWALL_CFG_S pstTVWallCfg,
                                                               OUT UINT32 *pudwLastChange
                                                               );

/**
* Delete TVWall Cfg\n
* @param [IN]  lpUserID                     User Login ID
* @param [IN]  udwTvWallID                  TvWall ID
* @param [OUT] pudwLastChange               
* @return TRUE means success, and any other value means failure
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_DeleteTVWallCfg(IN LPVOID lpUserID, 
                                                               IN UINT32 udwTvWallID,
                                                               OUT UINT32 *pudwLastChange
                                                               );


/**
* Find Scene Cfg List
* @param [IN] lpUserID                      User Login ID
* @param [IN] udwTvWallID                   TvWall ID
* @return  Query Handler,Return to NULL is failure，Other values are used as NETDEV_XW_FindNextSceneCfg、NETDEV_XW_FindCloseSceneCfg Function param�?
* @note 
*/
NETDEV_API NEWINTERFACE LPVOID STDCALL NETDEV_XW_FindSceneCfgList(IN LPVOID lpUserID,
                                                                  IN UINT32 udwTvWallID
                                                                  );

/**
* Find Next Scene Cfg
* @param [IN]  lpFindHandle                 Find Handle 
* @param [OUT] pstSceneShortInfo            Scene Info 
* @return TRUE means success, and any other value means failure
* @note Return failure explains the end of the query
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_FindNextSceneCfg(IN LPVOID lpFindHandle, 
                                                                OUT LPNETDEV_XW_SCENE_INFO_SHORT_S pstSceneShortInfo
                                                                );

/**
* Find Close Scene Cfg
* @param [IN] lpFindHandle                   File Find Handle
* @return TRUE means success, and any other value means failure
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_FindCloseSceneCfg(IN LPVOID lpFindHandle);

/**
* Create Scene Info\n
* @param [IN]  lpUserID                     User Login ID
* @param [IN]  udwTvWallID                  TvWall ID
* @param [INOUT] pstSceneBase               input Scene Name，output ID
* @param [OUT] pudwLastChange            
* @return TRUE means success, and any other value means failure
* @note  
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_CreateSceneInfo(IN LPVOID lpUserID, 
                                                               IN UINT32 udwTvWallID,
                                                               INOUT LPNETDEV_XW_SCENE_INFO_BASE_S pstSceneBase,
                                                               OUT UINT32 *pudwLastChange
                                                               );


/**
* Get Scene Info\n
* @param [IN]  lpUserID                     User Login ID
* @param [IN]  udwSceneID                   Scene ID
* @param [OUT] pstSceneDetailInfo           Scene Detail Info
* @return TRUE means success, and any other value means failure
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_GetSceneInfo(IN LPVOID lpUserID, 
                                                            IN UINT32 udwSceneID,
                                                            OUT LPNETDEV_XW_SCENE_INFO_DETAIL_S pstSceneDetailInfo
                                                            );

/**
* Modify Scene Info\n
* @param [IN]  lpUserID                     User Login ID
* @param [IN]  udwTvWallID                  TvWall ID
* @param [IN]  udwSceneID                   Scene ID
* @param [OUT] pudwLastChange              
* @return TRUE means success, and any other value means failure
* @note 
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_ModifySceneInfo(IN LPVOID lpUserID,
                                                               IN UINT32 udwTvWallID,
                                                               IN UINT32 udwSceneID,
                                                               OUT UINT32 *pudwLastChange
                                                               );

/**
* Delete Scene Info\n
* @param [IN]  lpUserID                     User Login ID
* @param [IN]  udwTvWallID                  TvWall ID
* @param [IN]  udwSceneID                   Scene ID
* @param [OUT] pudwLastChange             
* @return TRUE means success, and any other value means failure
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_DeleteSceneInfo(IN LPVOID lpUserID,
                                                               IN UINT32 udwTvWallID,
                                                               IN UINT32 udwSceneID,
                                                               OUT UINT32 *pudwLastChange
                                                               );

/**
* Set Current Scene ID\n
* @param [IN]  lpUserID                     User Login ID
* @param [IN]  udwTvWallID                  TvWall ID
* @param [IN]  udwSceneID                   Scene ID
* @param [OUT] pudwLastChange          
* @return TRUE means success, and any other value means failure
* @note �?
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_SetCurrentSceneID(IN LPVOID lpUserID, 
                                                                 IN UINT32 udwTvWallID,
                                                                 IN UINT32 udwSceneID,
                                                                 OUT UINT32 *pudwLastChange
                                                                 );

/**
* Get Current Scene ID\n
* @param [IN]  lpUserID                     User Login ID
* @param [IN]  udwTvWallID                  TvWall ID
* @param [OUT] pudwSceneID                  SceneID
* @return TRUE means success, and any other value means failure
* @note return sence ID�?
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_GetCurrentSceneID(IN LPVOID lpUserID, 
                                                                 IN UINT32 udwTvWallID,
                                                                 OUT UINT32 *pudwSceneID);

/**
* Get Current Scene Info\n
* @param [IN]  lpUserID                     User Login ID
* @param [IN]  udwTvWallID                  TvWall ID
* @param [OUT] pstSceneDetailInfo           Scene Detail Info
* @return TRUE means success, and any other value means failure
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_GetCurrentSceneInfo(IN LPVOID lpUserID, 
                                                                   IN UINT32 udwTvWallID, 
                                                                   OUT LPNETDEV_XW_SCENE_INFO_DETAIL_S pstSceneDetailInfo
                                                                   );

/**
* Delete Current Scene Info\n
* @param [IN]  lpUserID                     User Login ID
* @param [IN]  dwTimeOut                    TimeOut(s)  10s~60s
* @param [IN]  udwTvWallID                  TvWall ID
* @return TRUE means success, and any other value means failure
* @note 
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_DeleteCurrentSceneInfo(IN LPVOID lpUserID,
                                                                      IN INT32 dwTimeOut,
                                                                      IN UINT32 udwTvWallID
                                                                      ); 

/**
* Set Scene Plan\n
* @param [IN]  lpUserID                     User Login ID
* @param [IN]  udwTvWallID                  TvWall ID
* @param [IN]  pstScenePlan                 Scene Plan
* @param [OUT] pudwLastChange             
* @return TRUE means success, and any other value means failure
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_SetScenePlan(IN LPVOID lpUserID, 
                                                            IN UINT32 udwTvWallID, 
                                                            IN LPNETDEV_XW_SCENE_PLAN_S pstScenePlan,
                                                            OUT UINT32 *pudwLastChange
                                                            );

/**
* Get Scene Plan\n
* @param [IN]  lpUserID                     User Login ID
* @param [IN]  udwTvWallID                  TvWall ID
* @param [OUT] pstScenePlan                 Scene Plan 
* @return TRUE means success, and any other value means failure
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_GetScenePlan(IN LPVOID lpUserID, 
                                                            IN UINT32 udwTvWallID, 
                                                            OUT LPNETDEV_XW_SCENE_PLAN_S pstScenePlan
                                                            );


/**
* Find window List
* @param [IN] lpUserID                      User Login ID
* @param [IN] udwTvWallID                   TvWall ID
* @return  Query Handler,Return to NULL is failure，Other values are used as NETDEV_XW_FindNextWndInfo、NETDEV_XW_FindCloseWndInfo Function param�?
* @note 
*/
NETDEV_API NEWINTERFACE LPVOID STDCALL NETDEV_XW_FindWndList(IN LPVOID lpUserID, 
                                                             IN UINT32 udwTvWallID
                                                             );

/**
* Find Next window
* @param [IN]  lpFindHandle                 Find Handle 
* @param [OUT] pstWndInfo                   window info 
* @return TRUE means success, and any other value means failure
* @note Return failure explains the end of the query
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_FindNextWnd(IN LPVOID lpFindHandle, 
                                                           OUT LPNETDEV_XW_SCENE_WND_INFO_S pstWndInfo
                                                           );

/**
* Find Close window
* @param [IN] lpFindHandle                   File Find Handle
* @return TRUE means success, and any other value means failure
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_FindCloseWnd(IN LPVOID lpFindHandle);

/**
* Create window\n
* @param [IN]  lpUserID                     User Login ID
* @param [IN]  udwTvWallID                  TvWall ID
* @param [INOUT]  pstWndInfo                 window info
* @param [OUT] pudwLastChange               
* @return TRUE means success, and any other value means failure
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_CreateWnd(IN LPVOID lpUserID,
                                                         IN UINT32 udwTvWallID, 
                                                         INOUT LPNETDEV_XW_SCENE_WND_INFO_S pstWndInfo,
                                                         OUT UINT32 *pudwLastChange
                                                         );


/**
* Get Window info\n
* @param [IN]  lpUserID                     User Login ID
* @param [IN]  udwTvWallID                  TvWall ID
* @param [INOUT]  pstWndInfo                window info,input Window ID
* @return TRUE means success, and any other value means failure
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_GetWnd(IN LPVOID lpUserID,
                                                      IN UINT32 udwTvWallID, 
                                                      INOUT LPNETDEV_XW_SCENE_WND_INFO_S pstWndInfo
                                                      );

/**
* Modify window\n
* @param [IN]  lpUserID                     User Login ID
* @param [IN]  udwTvWallID                  TvWall ID
* @param [INOUT]  pstWndInfo                window info,input Window ID
* @param [OUT] pudwLastChange               
* @return TRUE means success, and any other value means failure
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_ModifyWnd(IN LPVOID lpUserID, 
                                                         IN UINT32 udwTvWallID, 
                                                         INOUT LPNETDEV_XW_SCENE_WND_INFO_S pstWndInfo,
                                                         OUT UINT32 *pudwLastChange
                                                         );

/**
* Delete window\n
* @param [IN]  lpUserID                     User Login ID
* @param [IN]  udwTvWallID                  TvWall ID
* @param [IN]  udwWndID                     Window ID
* @param [OUT] pudwLastChange              
* @return TRUE means success, and any other value means failure
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_DeleteWnd(IN LPVOID lpUserID, 
                                                         IN UINT32 udwTvWallID,
                                                         IN UINT32 udwWndID,
                                                         OUT UINT32 *pudwLastChange
                                                         );

/**
* Find Virtual LED List
* @param [IN]   lpUserID                      User login ID
* @param [IN]   udwTvWallID                   TvWall ID
* @return Task no,Return to NULL is failure,Other values are used as NETDEV_XW_FindNextVirtualLED,NETDEV_XW_FindCloseVirtualLED Function param�?
* @note none
*/
NETDEV_API NEWINTERFACE LPVOID STDCALL NETDEV_XW_FindVirtualLEDList(IN LPVOID lpUserID,
                                                                    IN UINT32 udwTvWallID
                                                                    );


/**
* Find Next Virtual LED\n
* @param [IN]   lpFindHandle                 Find Handle
* @param [OUT]  pstVirtualLEDInfo            Virtual LED Info
* @return TRUE means success, and any other value means failure
* @note none
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_FindNextVirtualLED(IN LPVOID lpFindHandle,
                                                                  OUT LPNETDEV_XW_VIRTUAL_LED_INFO_S pstVirtualLEDInfo
                                                                  );

/**
* Find Close Virtual LED FindHandle\n
* @param [IN]   lpFindHandle                Find Handle
* @return TRUE means success, and any other value means failure
* @note none
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_FindCloseVirtualLED(IN LPVOID lpFindHandle);

/**
* Create Virtual LED
* @param [IN]   lpUserID                      User login ID
* @param [IN]   udwTvWallID                   TvWall ID
* @param [INOUT]  pstVirtualLEDInfo           Virtual LED Info
* @param [OUT]  pudwLastChange            
* @return TRUE means success, and any other value means failure
* @note none
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_CreateVirtualLED(IN LPVOID lpUserID,
                                                                IN UINT32 udwTvWallID,
                                                                INOUT LPNETDEV_XW_VIRTUAL_LED_INFO_S pstVirtualLEDInfo,
                                                                OUT UINT32 *pudwLastChange
                                                                );

/**
* @Delete All Virtual LED
* @param [IN]   lpUserID                      User login ID
* @param [IN]   udwTvWallID                   TvWall ID
* @param [OUT]  pudwLastChange         
* @return TRUE means success, and any other value means failure
* @note none
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_DeleteAllVirtualLED(IN LPVOID lpUserID,
                                                                   IN UINT32 udwTvWallID,
                                                                   OUT UINT32 *pudwLastChange
                                                                   );

/**
* Get Virtual LED
* @param [IN]   lpUserID                      User login ID
* @param [IN]   udwTvWallID                   TvWall ID
* @param [INOUT]  pstVirtualLEDInfo           Virtual LED Info
* @return TRUE means success, and any other value means failure
* @note none
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_GetVirtualLED(IN LPVOID lpUserID,
                                                             IN UINT32 udwTvWallID,
                                                             INOUT LPNETDEV_XW_VIRTUAL_LED_INFO_S pstVirtualLEDInfo
                                                             );
/**
* @Set irtual LED
* @param [IN]   lpUserID                      User login ID
* @param [IN]   udwTvWallID                   TvWall ID
* @param [OUT]  pstVirtualLEDInfo             Virtual LED info
* @param [OUT]  pudwLastChange             
* @return TRUE means success, and any other value means failure
* @note none
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_SetVirtualLED(IN LPVOID lpUserID,
                                                             IN UINT32 udwTvWallID,
                                                             IN LPNETDEV_XW_VIRTUAL_LED_INFO_S pstVirtualLEDInfo,
                                                             OUT UINT32 *pudwLastChange
                                                             );
/**
* @Delete One Virtual LED
* @param [IN]   lpUserID                      User login ID
* @param [IN]   udwTvWallID                   TvWall ID
* @param [IN]   udwLedlID                     Virtual LED ID
* @param [OUT]  pudwLastChange              
* @return TRUE means success, and any other value means failure
* @note none
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_DeleteOneVirtualLED(IN LPVOID lpUserID,
                                                                   IN UINT32 udwTvWallID,
                                                                   IN UINT32 udwLedlID,
                                                                   OUT UINT32 *pudwLastChange
                                                                   );

/**
* Start RealPlay
* @param [IN]  lpUserID                       
* @param [IN]  pstDisplayerID                TvWall ID、Window ID
* @param [IN]  pstVideoSource                VideoSource
* @param [OUT]  *pudwTaskNo                  Task No
* @return TRUE means success, and any other value means failure
* @note 
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_StartRealPlay(IN LPVOID lpUserID, 
                                                             IN LPNETDEV_XW_DISPLAYER_ID_S pstDisplayerID,
                                                             IN LPNETDEV_XW_VIDEO_SOURCE_S pstVideoSource,
                                                             OUT UINT32 *pudwTaskNo
                                                             );

/**
* Stop RealPlay
* @param [IN]  lpUserID                      User Login ID 
* @param [IN]  pstDisplayerID                TvWall ID、Window ID
* @param [IN]  udwTaskNo                     Task No
* @return TRUE means success, and any other value means failure
* @note 
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_StopRealPlay(IN LPVOID lpUserID,
                                                            IN LPNETDEV_XW_DISPLAYER_ID_S pstDisplayerID,
                                                            IN UINT32 udwTaskNo
                                                            );
/**
* Stop RealPlay (Without Task No)
* @param [IN]  lpUserID                      User Login ID 
* @param [IN]  pstDisplayerID                TvWall ID、Window ID
* @return TRUE means success, and any other value means failure
* @note 
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_StopRealPlayWithoutTaskNo(IN LPVOID lpUserID,
                                                                         IN LPNETDEV_XW_DISPLAYER_ID_S pstDisplayerID
                                                                         );
/**
* Start Playback
* @param [IN]  lpUserID                      User Login ID 
* @param [IN]  pstDisplayerID                TvWall ID 、Window ID
* @param [IN]  pstChannels                   Channel list  
* @param [OUT]  *pudwTaskNo                  Task No
* @return TRUE means success, and any other value means failure
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_StartPlayback(IN LPVOID lpUserID, 
                                                             IN LPNETDEV_XW_DISPLAYER_ID_S pstDisplayerID,
                                                             IN LPNETDEV_XW_CHANNELS_S pstChannels,
                                                             OUT UINT32 *pudwTaskNo
                                                             );

/**
* Stop Playback
* @param [IN]  lpUserID                     Playback ID
* @param [IN]  pstDisplayerID               TvWall ID、Window ID
* @param [IN]  udwTaskNo                    Task No
* @return TRUE means success, and any other value means failure
* @note 
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_StopPlayback(IN LPVOID lpUserID,
                                                            IN LPNETDEV_XW_DISPLAYER_ID_S pstDisplayerID,
                                                            IN UINT32 udwTaskNo
                                                            );

/**
* Control Playback
* @param [IN]  lpUserID                     Playback ID
* @param [IN]  pstDisplayerID               TvWall ID、Window ID
* @param [IN]  pstPlaybackParam             Playback Param
* @return TRUE means success, and any other value means failure
* @note 
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_ControlPlayback(IN LPVOID lpUserID,
                                                               IN LPNETDEV_XW_DISPLAYER_ID_S pstDisplayerID,
                                                               IN LPNETDEV_XW_PLAYBACK_PARAM_S pstPlaybackParam
                                                               );

/**
* Start passive decode
* @param [IN]   lpUserID                    User login ID
* @para, [IN]   pstDisplayerID              Displayer ID
* @param [IN]   pstVideoSource              VideoSource
* @param [OUT]  pudwTaskNo                  Task No
* @return TRUE means success, and any other value means failure
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_StartPassiveDecode(IN LPVOID lpUserID,
                                                               IN LPNETDEV_XW_DISPLAYER_ID_S pstDisplayerID,
                                                               IN LPNETDEV_XW_VIDEO_SOURCE_S pstVideoSource,
                                                               OUT UINT32 *pudwTaskNo
                                                               );

/**
* Send data to passive decode channel
* @param [IN]   lpUserID                   User login ID
* @param [IN]   udwTaskNO                  Task NO
* @param [IN]   pstSendData                Send Data 
* @return TRUE means success, and any other value means failure
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_SendPassiveData(IN LPVOID lpUserID,
                                                            IN UINT32 udwTaskNo,
                                                            IN LPNETDEV_PASSIVE_SEND_S pstSendData
                                                            );

/**
* Stop passive decode
* @param [IN]   lpUserID                   User login ID
* @param [IN]   udwTaskNO                  Task NO
* @return TRUE means success, and any other value means failure
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_StopPassiveDecode(IN LPVOID lpUserID,
                                                              IN UINT32 udwTaskNO
                                                              );


/**
* Batch create  Window
* @param [IN] lpUserID                  
* @param [IN] udwTvWallID               TvWall ID
* @param [IN] pstSenceWndList           Window info list
* @param [OUT] pstResultInfo            Result Info list
* @return   TRUE means success, and any other value means failure.
* @note 
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_CreateBatchWnd(IN LPVOID lpUserID,
                                                              IN UINT32 udwTvWallID, 
                                                              IN LPNETDEV_XW_SENCE_BATCH_WND_LIST_S pstSenceWndList,
                                                              OUT LPNETDEV_XW_SENCE_BATCH_RESULT_LIST_S pstResultInfoList
                                                              );

/**
* Batch Delete window
* @param [IN] lpUserID                  
* @param [IN] dwTimeOut                 TimeOut(s)  10s~60s
* @param [IN] udwTvWallID               TvWall ID
* @param [INOUT] pstWinInfoList         Window Info List
* @return   TRUE means success, and any other value means failure.
* @note 
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_DeleteBatchWnd(IN LPVOID lpUserID,
                                                              IN INT32 dwTimeOut,
                                                              IN UINT32 udwTvWallID, 
                                                              INOUT LPNETDEV_XW_SENCE_BATCH_RESULT_LIST_S pstWinInfoList
                                                              );

/*
* Zoom Screen
* @param [IN] LPVOID lpUserID                                       User Login ID
* @param [IN] UINT32 udwTvWallID                                    TvWall ID
* @param [IN] UINT32 udwWndID                                       Window ID
* @param [IN] LPNETDEV_XW_SCREEN_ZOOM_INFO_S *pstScreenZoomInfo     Zoom Screen info 
* @return  NETDEV_E_SUCCEED, Other details of the error code 
* @note:
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_ZoomScreen(IN LPVOID lpUserID,
                                                          IN UINT32 udwTvWallID,
                                                          IN UINT32 udwWndID,
                                                          IN LPNETDEV_XW_SCREEN_ZOOM_INFO_S pstScreenZoomInfo
                                                          );


/*
* Get Sceen Ctrl Param
* @param [IN] LPVOID lpUserID                                       User Login ID
* @param [IN] UINT32 udwTvWallID                                    TvWall ID
* @param [OUT] LPNETDEV_XW_SCREEN_CTRL_PARAM_INFO_S *pstScreenCtrlParamInfo    Screen Ctrl Param Info
* @return  NETDEV_E_SUCCEED, Other details of the error code 
* @note:
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_GetSceenCtrlParam(IN LPVOID lpUserID,
                                                                 IN UINT32 udwTvWallID,
                                                                 OUT LPNETDEV_XW_SCREEN_CTRL_PARAM_INFO_S pstScreenCtrlParamInfo
                                                                 );

/*
* Set Sceen Ctrl Param
* @param [IN] LPVOID lpUserID                                       User Login ID
* @param [IN] UINT32 udwTvWallID                                    TvWall ID
* @param [IN] LPNETDEV_XW_SCREEN_CTRL_PARAM_INFO_S pstScreenCtrlParamInfo,    Screen Ctrl Param Info
* @param [OUT] UINT32 *pudwLastChange 
* @return  NETDEV_E_SUCCEED, Other details of the error code 
* @note:
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_SetSceenCtrlParam(IN LPVOID lpUserID,
                                                                 IN UINT32 udwTvWallID,
                                                                 IN LPNETDEV_XW_SCREEN_CTRL_PARAM_INFO_S pstScreenCtrlParamInfo,
                                                                 OUT UINT32* pudwLastChange);

/*
* Manual Switch Power
* @param [IN] LPVOID lpUserID                                       User Login ID
* @param [IN] UINT32 udwTvWallID                                    TvWall ID
* @param [IN] LPNETDEV_XW_MANUAL_SWITCH_POWER_S  pstManualSwitchPower,    Manual Switch Power param 
* @return  NETDEV_E_SUCCEED, Other details of the error code 
*   @note:
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_ManualSwitchPower(IN LPVOID lpUserID,
                                                                 IN UINT32 udwTvWallID,
                                                                 IN LPNETDEV_XW_MANUAL_SWITCH_POWER_S pstManualSwitchPower);

/*
* delay Switch Power
* @param  [IN] LPVOID lpUserID                                         User Login ID
* @param  [IN] UINT32 udwTvWallID                                     TvWall ID
* @param  [IN] LPNETDEV_XW_DELAY_SWITCH_POWER_S  pstDelaySwitchPower,  Delay Switch Power param 
* @return  NETDEV_E_SUCCEED, Other details of the error code 
* @note:
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_DelaySwitchPower(IN LPVOID lpUserID,
                                                                IN UINT32 udwTvWallID,
                                                                IN LPNETDEV_XW_DELAY_SWITCH_POWER_S pstDelaySwitchPower);

/*
* Del Delay Switch Power\n
* @param [IN] LPVOID lpUserID                                       User Login ID
* @param [IN] UINT32 udwTvWallID                                    TvWall ID
* @return  NETDEV_E_SUCCEED, Other details of the error code 
*   @note:
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_DelDelaySwitchPower(IN LPVOID lpUserID,
                                                                   IN UINT32 udwTvWallID);


/*
* Get Timing Switch Power\n
* @param [IN] LPVOID lpUserID                                           User Login ID
* @param [IN] UINT32 udwTvWallID                                        TvWall ID 
* @param [OUT] LPNETDEV_XW_TIMING_SWITCH_POWER_S pstTimingSwitchPower   Timing Switch Power info
* @return  NETDEV_E_SUCCEED, Other details of the error code 
* @note:
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_GetTimingSwitchPower(IN LPVOID lpUserID,
                                                                    IN UINT32 udwTvWallID,
                                                                    OUT LPNETDEV_XW_TIMING_SWITCH_POWER_S pstTimingSwitchPower);


/*
* Set timing Switch Power\n
* @param [IN] LPVOID lpUserID                                           User Login ID
* @param [IN] UINT32 udwTvWallID                                        TvWall ID
* @param [IN] LPNETDEV_XW_TIMING_SWITCH_POWER_S pstTimingSwitchPower,   Timing Switch Power info
* @param [OUT] UINT32 *pudwLastChange,Last Change 
* @return  NETDEV_E_SUCCEED, Other details of the error code 
*   @note:
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_XW_SetTimingSwitchPower(IN LPVOID lpUserID,
                                                                    IN UINT32 udwTvWallID,
                                                                    IN LPNETDEV_XW_TIMING_SWITCH_POWER_S pstTimingSwitchPower,
                                                                    OUT UINT32 *pudwLastChange);



/**
* Find Alarm SnapShot URL\n
* @param [IN]  lpUserID                     User Login ID
* @param [IN]  pstAlarmSnapShotCond         Alarm SnapShot Cond
* @return  Query Handler,Return to NULL is failure，Other values are used as NETDEV_GetNextAlarmSnapShotURL、NETDEV_CloseGetAlarmSnapShotURL Function param�?
* @note
*/
NETDEV_API NEWINTERFACE LPVOID STDCALL NETDEV_FindAlarmSnapShotURL(IN LPVOID lpUserID,
                                                                   IN LPNETDEV_ALARM_SNAPSHOT_COND_S pstAlarmSnapShotCond
                                                                   );

/**
* Find Next Alarm SnapShot\n
* @param [IN]  lpFindHandle                      Query Handler
* @param [OUT]  pstAlarmPicInfo                  Alarm snapShot info
* @return  TRUE means success, and any other value means failure
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_FindNextAlarmSnapShotURL(IN LPVOID lpFindHandle,
                                                                     OUT LPNETDEV_ALARM_SNAPSHOT_PIC_S pstAlarmPicInfo
                                                                     );

/**
* Close Alarm SnapShot FindHandle\n
* @param [IN]  lpFindHandle                      Query Handler
* @return  TRUE means success, and any other value means failure
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_FindCloseAlarmSnapShotURL(IN LPVOID lpFindHandle
                                                                      );

/**
* Save alarm and grab\n
* @param [IN]  lpUserID                     user login ID
* @param [IN]  pstPicFileInfo               Alarm picture info
* @return  TRUE means success, and any other value means failure
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_SaveSnapShotFile(IN LPVOID lpUserID,
                                                             IN LPNETDEV_PIC_FILE_INFO_S pstPicFileInfo
                                                             );

/**
*  Set write log flag
* @param [IN]   bWriteLogFlag,  write log flag  TRUE:write log,FALSE：no write lo
* @return VOID
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_SetWriteLogFlag(IN BOOL bWriteLogFlag);

/************************************************************************/
/*                     user management                                    */
/************************************************************************/

/* BIT define */
#ifndef BIT0
#define BIT0  (0x1 << 0)
#define BIT1  (0x1 << 1)
#define BIT2  (0x1 << 2)
#define BIT3  (0x1 << 3)
#define BIT4  (0x1 << 4)
#define BIT5  (0x1 << 5)
#define BIT6  (0x1 << 6)
#define BIT7  (0x1 << 7)
#define BIT8  (0x1 << 8)
#define BIT9  (0x1 << 9)
#define BIT10 (0x1 << 10)
#define BIT11 (0x1 << 11)
#define BIT12 (0x1 << 12)
#define BIT13 (0x1 << 13)
#define BIT14 (0x1 << 14)
#define BIT15 (0x1 << 15)
#define BIT16 (0x1 << 16)
#define BIT17 (0x1 << 17)
#define BIT18 (0x1 << 18)
#define BIT19 (0x1 << 19)
#define BIT20 (0x1 << 20)
#define BIT21 (0x1 << 21)
#define BIT22 (0x1 << 22)
#define BIT23 (0x1 << 23)
#define BIT24 (0x1 << 24)
#define BIT25 (0x1 << 25)
#define BIT26 (0x1 << 26)
#define BIT27 (0x1 << 27)
#define BIT28 (0x1 << 28)
#define BIT29 (0x1 << 29)
#define BIT30 (0x1 << 30)
#define BIT31 (0x1 << 31)

#define BIT(nr)     (1UL << (nr))
#endif  /* BIT define */

/**
* @enum tagNETDEVChnPermission
* @brief Chn Permission enum
* @attention Bit 
*/
typedef enum tagNETDEVChnPermission
{
    NETDEV_CHN_PERMISSION_LIVE                  = BIT0,                 /* Live and voice*/
    NETDEV_CHN_PERMISSION_PTZ                   = BIT1,                 /* ptz */
    NETDEV_CHN_PERMISSION_PLAYBACK              = BIT2,                 /* playback */
    NETDEV_CHN_PERMISSION_MANU_RECORD           = BIT3,                 /* manu recode */
    NETDEV_CHN_PERMISSION_LOCAL_BACK            = BIT4,                 /* local back */

    NETDEV_CHN_PERMISSION_INVALID               = 0XFFFFFFFF        /*  invalid   */
}NETDEV_CHN_PERMISSION_TYPE_E;

/**
* @struct tagNETDEVChnPermissionInfo
* @brief Chn Permission Info
* @attention  none
*/
typedef struct tagNETDEVChnPermissionInfo
{
    INT32    dwChannelID;               /* Channel ID */
    INT32    dwPermission;              /* Chn Permission, reference to #NETDEV_CHN_PERMISSION_TYPE_E */
    BYTE     byRes[256];                /* Reserved */
}NETDEV_CHN_PERMISSION_INFO_S, *LPNETDEV_CHN_PERMISSION_INFO_S;

/**
* @enum tagNETDEVUserLevel
* @brief User level, only administrator users can modify permissions
* @attention none
*/
typedef enum tagNETDEVUserLevel
{
    NETDEV_USER_LEVEL_ADMINISTRATOR  = 0,           /* Administrator , not configurable*/
    NETDEV_USER_LEVEL_OPERATOR       = 1,           /*  operator  */
    NETDEV_USER_LEVEL_USER           = 2,           /* user */
    NETDEV_USER_LEVEL_Default        = 3            /*  Default User, not configurable */
}NETDEV_USER_LEVEL_E;

/**
* @enum tagNETDEVUserBasePermission
* @brief Base Permission
* @attention None 
*/
typedef enum tagNETDEVUserBasePermission
{
    NETDEV_USER_BASE_PER_CONFIG           = BIT0,           /* config*/
    NETDEV_USER_BASE_PER_UPGRADE          = BIT1,           /* upgrade */
    NETDEV_USER_BASE_PER_LOG              = BIT2,           /* Log view and export  */
    NETDEV_USER_BASE_PER_REBOOT           = BIT3            /* reboot */
}NETDEV_USER_BASE_PERMISSION_E;

/**
 * @struct tagNETDEVUserDetailInfo
 * @brief User Detail Info
 * @attention 
 */
typedef struct tagNETDEVUserDetailInfo
{
    UINT32                         udwLevel;                                          /* User Level  # NETDEV_USER_LEVEL_E*/
    CHAR                           szUserName[NETDEV_LEN_64];                         /*  User Name No modification is supported, and when a single information is obtained as a reference [1~18]*/
    CHAR                           szPassword[NETDEV_LEN_256];                        /* password, add used [0~256]*/
    UINT32                         udwBasePermission;                                 /* Base Permission�?NETDEV_USER_BASE_PERMISSION_E ,Permissions are described by BIT bit*/
    UINT32                         udwNum;                                            /* Number of video input channels */
    NETDEV_CHN_PERMISSION_INFO_S   astChnPermission[NETDEV_CHANNEL_MAX];              /* Channel permissions list */
    BYTE                           byRes[256];                                        /* Reserved */
}NETDEV_USER_DETAIL_INFO_S, *LPNETDEV_USER_DETAIL_INFO_S;

/**
 * @struct tagNETDEVUserModifyDetailInfo
 * @brief Modify User Detail Info
 * @attention 
 */
typedef struct tagNETDEVUserModifyDetailInfo
{
    NETDEV_USER_DETAIL_INFO_S      stUserInfo;
    BOOL                           bIsModifyPassword;                                 /* Whether to modify a password and assign a value when it is modified */
    BOOL                           bIsModifyOther;                                    /* Whether administrators modify other users and assign values when modifying */
    CHAR                           szNewPassword[NETDEV_LEN_256];                     /* New password (used when modifying the password)，[0~256] */
    CHAR                           szCurrentPassword[NETDEV_LEN_256];                 /* The password that is currently used to modify the password is carried*/
    BYTE                           byRes[256];                                        /* Reserved */
}NETDEV_USER_MODIFY_DETAIL_INFO_S, *LPNETDEV_USER_MODIFY_DETAIL_INFO_S;

/**
* Get User Detail Info\n
* @param [IN]   lpUserID                    ID User login ID
* @param [INOUT]   pstUserDetailInfo        User Info reference to #NETDEV_USER_DETAIL_INFO_S
* @return  TRUE means success, and any other value means failure
* @note   szUsername is Input param
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_GetUserDetailInfo(IN LPVOID lpUserID,
                                                              INOUT LPNETDEV_USER_DETAIL_INFO_S pstUserDetailInfo
                                                              );

/**
* Create User Info\n
* @param [IN]   lpUserID                ID User login ID
* @param [IN]   pstUserDetailInfo       User Info reference to #NETDEV_USER_DETAIL_INFO_S
* @return  TRUE means success, and any other value means failure
* @note
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_CreateUser(IN LPVOID lpUserID,
                                                       IN LPNETDEV_USER_DETAIL_INFO_S pstUserDetailInfo
                                                       );

/**
* Modify User Info\n
* @param [IN]   lpUserID                 User login ID
* @param [IN]   pstUserInfo              User Info reference to #NETDEV_USER_INFO_S
* @return  TRUE means success, and any other value means failure
* @note
    1、Administrator users only support modification of privileges, administrators modify other user info
    2、Operators and ordinary users can only modify their passwords
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_ModifyUser(IN LPVOID lpUserID,
                                                       IN LPNETDEV_USER_MODIFY_DETAIL_INFO_S pstUserInfo
                                                       );

/**
* Delete User Info\n
* @param [IN]   lpUserID               ID User login ID
* @param [IN]   pszUserName            User Name
* @return  TRUE means success, and any other value means failure
* @note none
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_DeleteUser(IN LPVOID lpUserID,
                                                       IN CHAR *pszUserName
                                                       );

/**
 * @struct tagNETDEVUserDetailList
 * @brief User info list
 * @attention 
 */
typedef struct tagNETDEVUserDetailList
{
    UINT32                         udwNum;                                            /* User num */
    NETDEV_USER_DETAIL_INFO_S      astUserInfo[NETDEV_LEN_64];                        /* User list */
    BYTE                           byRes[128];                                        /* Reserved */
}NETDEV_USER_DETAIL_LIST_S, *LPNETDEV_USER_DETAIL_LIST_S;

/**
* Get all the user information\n
* @param [IN]   lpUserID                     User login ID
* @param [OUT]   pstUserDetailList           user info, reference to#LPNETDEV_USER_DETAIL_LIST_S
* @return TRUE means success, and any other value means failure
* @note 
*/
NETDEV_API NEWINTERFACE BOOL STDCALL NETDEV_GetUserDetailList(IN LPVOID lpUserID,
                                                              OUT LPNETDEV_USER_DETAIL_LIST_S pstUserDetailList
                                                              );



/****************************************************** user management  End*****************************************************************/

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _NETDEV_NET_SDK_H_ */

