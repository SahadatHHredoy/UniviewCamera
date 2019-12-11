using System;
using NETSDKHelper;
using System.Collections.Generic;
using System.Drawing;
using System.Runtime.InteropServices;

namespace GeneralDef
{
    public class NETDEMO
    {
        public const int REAL_PANEL_MAX_SIZE = 16;//16
        public const int PLAYBACK_PANEL_MAX_SIZE = 4;

        public const int NETDEV_IPV4_LEN_MAX = 16;
        public const int NETDEV_USERNAME_LEN_260 = 260;
        public const int NETDEV_SERIAL_NUMBER_LEN_64 = 64;
        public const int NETDEV_MODEL_LEN_64 = 64;

        /*   Common length */
        public const int NETDEV_LEN_4 = 4;
        public const int NETDEV_LEN_8 = 8;
        public const int NETDEV_LEN_16 = 16;
        public const int NETDEV_LEN_32 = 32;
        public const int NETDEV_LEN_64 = 64;
        public const int NETDEV_LEN_128 = 128;
        public const int NETDEV_LEN_132 = 132;
        public const int NETDEV_LEN_260 = 260;

        public const int NETDEV_MAX_PRESET_NUM = 255; /*预置位总数*/

        /*TreeView图标索引*/
        public const int NETDEV_TREEVIEW_IMAGE_CLOUND_ROOT = 0;
        public const int NETDEV_TREEVIEW_IMAGE_LOCAL_DEVICE_ON = 1;
        public const int NETDEV_TREEVIEW_IMAGE_LOCAL_DEVICE_OFF = 2;
        public const int NETDEV_TREEVIEW_IMAGE_CLOUD_DEVICE_ON = 3;
        public const int NETDEV_TREEVIEW_IMAGE_CLOUD_DEVICE_OFF = 4;
        public const int NETDEV_TREEVIEW_IMAGE_CHL_DEVICE_ON = 5;
        public const int NETDEV_TREEVIEW_IMAGE_CHL_DEVICE_OFF = 6;

        public const int NETDEMO_DOWNLOAD_TIME_COUNT = 5;/*如果下载一个视频超过5次时间进度都没有变化，说明下载出问题，用于下载回放时*/

        public static bool NETDEMO_DOWNLOAD_TIMER_MUX_FLAG = false;/*控制定时器多线程同步,默认为没有线程执行*/
        public static bool NETDEMO_DOWNLOAD_TIMER_STOP_ALL = false;/*停止下载*/

        //public static bool NETDEMO_SELECTED_CHANGED_FlAG = true;/*是否允许presetIDCobBox_SelectedIndexChanged事件触发*/

        /*treeview节点级别*/
        public enum TREENODE_LEVEL_E
        {
            TREENODE_ROOT_LEVEL = 0,
            TREENODE_DEVICE_LEVEL = 1,
            TREENODE_CHANNEL_LEVEL = 2
        }

        public enum NETDEV_LOGIN_TYPE_E
        {
            NETDEV_NEW_LOGIN = 0,         /* new Login */
            NETDEV_AGAIN_LOGIN = 1          /* again Login */
        }

        public enum NETDEMO_MONITOR_TYPE_E
        {
            NETDEMO_MONITOR_SINGLE_SCREEN = 0,
            NETDEMO_MONITOR_ALL_SCREEN = 1
        }

        public class NETDEMO_UPDATE_TIME_INFO
        {
            public IntPtr  lpHandle;
            public Int64 tBeginTime;
            public Int64 tEndTime;
            public Int64 tCurTime;
            public Int32 dwCount;
            public String strFileName;
            public String strFilePath;
            public bool downLoad_status;
        }

        /*用于视频流配置质量Quality*/
        public static NETDEV_VIDEO_QUALITY_E[] gastVideoQualityMap = 
        {
            NETDEV_VIDEO_QUALITY_E.NETDEV_VQ_L0,
            NETDEV_VIDEO_QUALITY_E.NETDEV_VQ_L1, 
            NETDEV_VIDEO_QUALITY_E.NETDEV_VQ_L2, 
            NETDEV_VIDEO_QUALITY_E.NETDEV_VQ_L3, 
            NETDEV_VIDEO_QUALITY_E.NETDEV_VQ_L4, 
            NETDEV_VIDEO_QUALITY_E.NETDEV_VQ_L5, 
            NETDEV_VIDEO_QUALITY_E.NETDEV_VQ_L6, 
            NETDEV_VIDEO_QUALITY_E.NETDEV_VQ_L7, 
            NETDEV_VIDEO_QUALITY_E.NETDEV_VQ_L8, 
            NETDEV_VIDEO_QUALITY_E.NETDEV_VQ_L9
        };

        public enum NETDEV_ALARM_TYPE_E
        {
            /* 有恢复类型的告警  Recoverable alarms */
            NETDEV_ALARM_MOVE_DETECT                        = 1,            /* 运动检测告警  Motion detection alarm */
            NETDEV_ALARM_VIDEO_LOST                         = 2,            /* 视频丢失告警  Video loss alarm */
            NETDEV_ALARM_VIDEO_TAMPER_DETECT                = 3,            /* 遮挡侦测告警  Tampering detection alarm */
            NETDEV_ALARM_INPUT_SWITCH                       = 4,            /* 输入开关量告警  boolean input alarm */
            NETDEV_ALARM_TEMPERATURE_HIGH                   = 5,            /* 高温告警  High temperature alarm */
            NETDEV_ALARM_TEMPERATURE_LOW                    = 6,            /* 低温告警  Low temperature alarm */
            NETDEV_ALARM_AUDIO_DETECT                       = 7,            /* 声音检测告警  Audio detection alarm */
            NETDEV_ALARM_DISK_ABNORMAL                      = 8,            /* 磁盘异常 Disk abnormal */
            NETDEV_ALARM_DISK_OFFLINE                       = 9,            /* 磁盘下线 Disk online (兼容以前版本,不维护) */
            NETDEV_ALARM_DISK_ONLINE                        = 10,           /* 磁盘上线 Disk online */
            NETDEV_ALARM_DISK_STORAGE_WILL_FULL             = 11,           /* 磁盘存储空间即将满 Disk StorageGoingfull */
            NETDEV_ALARM_DISK_STORAGE_IS_FULL               = 12,           /* 存储空间满 StorageIsfull */
            NETDEV_ALARM_DISK_RAID_DISABLED                 = 13,           /* 阵列损坏 RAIDDisabled */
            NETDEV_ALARM_DISK_RAID_DEGRADED                 = 14,           /* 阵列衰退 RAIDDegraded */
            NETDEV_ALARM_DISK_RAID_RECOVERED                = 15,           /* 阵列恢复正常 RAIDDegraded */

            /* NVR及接入设备状态上报  Status report of NVR and access device 100~199 */
            NETDEV_ALARM_REPORT_DEV_ONLINE                  = 100,          /* 设备上线  Device online */
            NETDEV_ALARM_REPORT_DEV_OFFLINE                 = 101,          /* 设备下线  Device offline */
            NETDEV_ALARM_REPORT_DEV_VIDEO_LOSS              = 102,          /* 视频丢失  Video loss */
            NETDEV_ALARM_REPORT_DEV_VIDEO_LOSS_RECOVER      = 103,          /* 视频丢失恢复  Video loss recover */
            NETDEV_ALARM_REPORT_DEV_REBOOT                  = 104,          /* 设备重启  Device restart */
            NETDEV_ALARM_REPORT_DEV_SERVICE_REBOOT          = 105,          /* 服务重启  Service restart */
            NETDEV_ALARM_REPORT_DEV_DELETE_CHL              = 106,          /* 通道删除  Delete channel */

            /* 实况业务异常上报  Live view exception report 200~299 */
            NETDEV_ALARM_NET_FAILED                         = 200,          /* 会话网络错误 Network error */
            NETDEV_ALARM_NET_TIMEOUT                        = 201,          /* 会话网络超时 Network timeout */
            NETDEV_ALARM_SHAKE_FAILED                       = 202,          /* 会话交互错误 Interaction error */
            NETDEV_ALARM_STREAMNUM_FULL                     = 203,          /* 流数已经满 Stream full */
            NETDEV_ALARM_STREAM_THIRDSTOP                   = 204,          /* 第三方停止流 Third party stream stopped */
            NETDEV_ALARM_FILE_END                           = 205,          /* 文件结束 File ended */
            NETDEV_ALARM_RTMP_CONNECT_FAIL                  = 206,          /* RTMP连接失败 RTMP connect fail */
            NETDEV_ALARM_RTMP_INIT_FAIL                     = 207,          /* RTMP初始化失败 RTMP init fail*/

            /* 无布防24小时有效的告警  Valid alarms within 24 hours without arming schedule */
            NETDEV_ALARM_ALLTIME_FLAG_START                 = 400,          /* 无布防告警开始标记  Start marker of alarm without arming schedule */
            NETDEV_ALARM_STOR_ERR                           = 401,          /* 存储错误  Storage error */
            NETDEV_ALARM_STOR_DISOBEY_PLAN                  = 402,          /* 未按计划存储  Not stored as planned */

            /* 无恢复类型的告警  Unrecoverable alarms */
            NETDEV_ALARM_NO_RECOVER_FLAG_START              = 500,          /* 无恢复类型告警开始标记  Start marker of unrecoverable alarm */
            NETDEV_ALARM_DISK_ERROR                         = 501,          /* 磁盘错误  Disk error */
            NETDEV_ALARM_ILLEGAL_ACCESS                     = 502,          /* 非法访问  Illegal access */
            NETDEV_ALARM_LINE_CROSS                         = 503,          /* 越界告警  Line cross */
            NETDEV_ALARM_OBJECTS_INSIDE                     = 504,          /* 区域入侵  Objects inside */
            NETDEV_ALARM_FACE_RECOGNIZE                     = 505,          /* 人脸识别  Face recognize */
            NETDEV_ALARM_IMAGE_BLURRY                       = 506,          /* 图像虚焦  Image blurry */
            NETDEV_ALARM_SCENE_CHANGE                       = 507,          /* 场景变更  Scene change */
            NETDEV_ALARM_SMART_TRACK                        = 508,          /* 智能跟踪  Smart track */
            NETDEV_ALARM_LOITERING_DETECTOR                 = 509,          /* 徘徊检测  Loitering Detector */
            NETDEV_ALARM_BANDWIDTH_CHANGE                   = 526,          /* Bandwidth change */
            NETDEV_ALARM_ALLTIME_FLAG_END                   = 600,          /* 无布防告警结束标记  End marker of alarm without arming schedule */
            NETDEV_ALARM_MEDIA_CONFIG_CHANGE                = 601,          /* 编码参数变更 media configurationchanged */
            NETDEV_ALARM_REMAIN_ARTICLE                     = 602,          /*物品遗留告警  Remain article*/
            NETDEV_ALARM_PEOPLE_GATHER                      = 603,          /* 人员聚集告警 People gather alarm*/
            NETDEV_ALARM_ENTER_AREA                         = 604,          /* 进入区域 Enter area*/
            NETDEV_ALARM_LEAVE_AREA                         = 605,          /* 离开区域 Leave area*/
            NETDEV_ALARM_ARTICLE_MOVE                       = 606,          /* 物品搬移 Article move*/
            /* 告警恢复  Alarm recover */
            NETDEV_ALARM_RECOVER_BASE                       = 1000,         /* 告警恢复基数  Alarm recover base */
            NETDEV_ALARM_MOVE_DETECT_RECOVER                = 1001,         /* 运动检测告警恢复  Motion detection alarm recover */
            NETDEV_ALARM_VIDEO_LOST_RECOVER                 = 1002,         /* 视频丢失告警恢复  Video loss alarm recover */
            NETDEV_ALARM_VIDEO_TAMPER_RECOVER               = 1003,         /* 遮挡侦测告警恢复  Tampering detection alarm recover */
            NETDEV_ALARM_INPUT_SWITCH_RECOVER               = 1004,         /* 输入开关量告警恢复  Boolean input alarm recover */
            NETDEV_ALARM_TEMPERATURE_RECOVER                = 1005,         /* 温度告警恢复  Temperature alarm recover */
            NETDEV_ALARM_AUDIO_DETECT_RECOVER               = 1007,         /* 声音检测告警恢复  Audio detection alarm recover */
            NETDEV_ALARM_DISK_ABNORMAL_RECOVER              = 1008,         /* 磁盘异常恢复 Disk abnormal recover */
            NETDEV_ALARM_DISK_OFFLINE_RECOVER               = 1009,         /* 磁盘离线恢复 Disk online recover */
            NETDEV_ALARM_DISK_ONLINE_RECOVER                = 1010,         /* 磁盘上线恢复 Disk online recover */
            NETDEV_ALARM_DISK_STORAGE_WILL_FULL_RECOVER     = 1011,         /* 磁盘存储空间即将满恢复 Disk StorageGoingfull recover */
            NETDEV_ALARM_DISK_STORAGE_IS_FULL_RECOVER       = 1012,         /* 存储空间满恢复 StorageIsfull recover */
            NETDEV_ALARM_DISK_RAID_DISABLED_RECOVER         = 1013,         /* 阵列损坏恢复 RAIDDisabled recover */
            NETDEV_ALARM_DISK_RAID_DEGRADED_RECOVER         = 1014,         /* 阵列衰退恢复 RAIDDegraded recover */

            NETDEV_ALARM_STOR_ERR_RECOVER                   = 1201,         /* 存储错误恢复  Storage error recover */
            NETDEV_ALARM_STOR_DISOBEY_PLAN_RECOVER          = 1202,         /* 未按计划存储恢复  Not stored as planned recover */

            NETDEV_ALARM_IMAGE_BLURRY_RECOVER               = 1506,         /* 图像虚焦告警恢复  Image blurry recover */
            NETDEV_ALARM_SMART_TRACK_RECOVER                = 1508,         /* 智能跟踪告警恢复  Smart track recover */

            NETDEV_ALARM_IP_CONFLICT = 1509,         /* IP冲突异常告警 */
            NETDEV_ALARM_IP_CONFLICT_CLEARED = 1510,         /* IP冲突异常告警恢复 */

            /* Smart信息 */
            NETDEV_ALARM_SMART_READ_ERROR_RATE = 1511,        /* 底层数据读取错误率 */
            NETDEV_ALARM_SMART_SPIN_UP_TIME = 1512,        /*  主轴起旋时间  */
            NETDEV_ALARM_SMART_START_STOP_COUNT = 1513,        /* 启停计数 */
            NETDEV_ALARM_SMART_REALLOCATED_SECTOR_COUNT = 1514,        /* 重映射扇区计数  */
            NETDEV_ALARM_SMART_SEEK_ERROR_RATE = 1515,        /* 寻道错误率 */
            NETDEV_ALARM_SMART_POWER_ON_HOURS = 1516,        /* 通电时间累计，出厂后通电的总时间，一般磁盘寿命三万小时 */
            NETDEV_ALARM_SMART_SPIN_RETRY_COUNT = 1517,        /* 主轴起旋重试次数 */
            NETDEV_ALARM_SMART_CALIBRATION_RETRY_COUNT = 1518,        /* 磁头校准重试计数 */
            NETDEV_ALARM_SMART_POWER_CYCLE_COUNT = 1519,        /* 通电周期计数 */
            NETDEV_ALARM_SMART_POWEROFF_RETRACT_COUNT = 1520,        /* 断电返回计数 */
            NETDEV_ALARM_SMART_LOAD_CYCLE_COUNT = 1521,        /* 磁头加载计数 */
            NETDEV_ALARM_SMART_TEMPERATURE_CELSIUS = 1522,        /* 温度 */
            NETDEV_ALARM_SMART_REALLOCATED_EVENT_COUNT = 1523,        /* 重映射事件计数 */
            NETDEV_ALARM_SMART_CURRENT_PENDING_SECTOR = 1524,        /* 当前待映射扇区计数 */
            NETDEV_ALARM_SMART_OFFLINE_UNCORRECTABLE = 1525,        /* 脱机无法校正的扇区计数 */
            NETDEV_ALARM_SMART_UDMA_CRC_ERROR_COUNT = 1526,        /* 奇偶校验错误率  */
            NETDEV_ALARM_SMART_MULTI_ZONE_ERROR_RATE = 1527,        /* 多区域错误率 */

            NETDEV_ALARM_INVALID                            = 0xFFFF        /* 无效值  Invalid value */
        }

        public enum NETDEV_EXCEPTION_TYPE_E
        {
            /* 回放业务异常上报  Playback exceptions report 300~399 */
            NETDEV_EXCEPTION_REPORT_VOD_END             = 300,          /* 回放结束  Playback ended*/
            NETDEV_EXCEPTION_REPORT_VOD_ABEND           = 301,          /* 回放异常  Playback exception occured */
            NETDEV_EXCEPTION_REPORT_BACKUP_END          = 302,          /* 备份结束  Backup ended */
            NETDEV_EXCEPTION_REPORT_BACKUP_DISC_OUT     = 303,          /* 磁盘被拔出  Disk removed */
            NETDEV_EXCEPTION_REPORT_BACKUP_DISC_FULL    = 304,          /* 磁盘已满  Disk full */
            NETDEV_EXCEPTION_REPORT_BACKUP_ABEND        = 305,          /* 其他原因导致备份失败   Backup failure caused by other reasons */

            NETDEV_EXCEPTION_EXCHANGE                   = 0x8000,       /* 用户交互时异常（用户保活超时）  Exception occurred during user interaction (keep-alive timeout) */

            NETDEV_EXCEPTION_REPORT_INVALID             = 0xFFFF        /* 无效值  Invalid value */
        }

        public struct NETDEMO_ALARM_INFO
        {
            public Int32 alarmType;
            public string reportAlarm;

            public NETDEMO_ALARM_INFO(int alarmTypeArg, string reportAlarmArg)
            {
                alarmType = alarmTypeArg;
                reportAlarm = reportAlarmArg;
            }
        }

        public static NETDEMO_ALARM_INFO[] gastNETDemoAlarmInfo = 
        {
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_MOVE_DETECT,"Motion detection alarm"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_MOVE_DETECT_RECOVER,"Motion detection alarm recover"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_VIDEO_LOST,"Video loss alarm"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_VIDEO_TAMPER_DETECT,"Tampering detection alarm"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_VIDEO_TAMPER_RECOVER,"Tampering detection alarm recover"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_INPUT_SWITCH,"Boolean input alarm"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_TEMPERATURE_HIGH,"High temperature alarm"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_TEMPERATURE_LOW,"Low temperature alarm"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_AUDIO_DETECT,"Audio detection alarm"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_INPUT_SWITCH_RECOVER,"Boolean input alarm recover"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_REPORT_DEV_VIDEO_LOSS,"Video loss alarm"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_REPORT_DEV_VIDEO_LOSS_RECOVER,"Video loss alarm recover"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_REPORT_DEV_REBOOT,"Device restart"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_REPORT_DEV_SERVICE_REBOOT,"Service restart"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_REPORT_DEV_ONLINE,"Device online"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_REPORT_DEV_OFFLINE,"Device offline"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_REPORT_DEV_DELETE_CHL,"Delete channel"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_NET_FAILED,"Network timeout"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_SHAKE_FAILED,"Interaction error"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_NET_TIMEOUT,"Network error"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_DISK_OFFLINE_RECOVER,"Disk online"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_DISK_OFFLINE,"Disk offline"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_DISK_ONLINE_RECOVER,"Disk offline"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_DISK_ONLINE,"Disk online"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_MEDIA_CONFIG_CHANGE,"Media configuration changed"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_REMAIN_ARTICLE,"Remain article"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_PEOPLE_GATHER,"People gather alarm"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_ENTER_AREA,"Enter area"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_LEAVE_AREA,"Leave area"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_ARTICLE_MOVE,"Article move"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_DISK_ABNORMAL,"Disk abnormal"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_DISK_ABNORMAL_RECOVER,"Disk abnormal recover"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_DISK_STORAGE_WILL_FULL,"Disk storage will full"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_DISK_STORAGE_WILL_FULL_RECOVER,"Disk storage will full recover"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_DISK_STORAGE_IS_FULL,"Disk storage is full"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_DISK_STORAGE_IS_FULL_RECOVER,"Disk storage is full recover"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_DISK_RAID_DISABLED,"RAID disabled"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_DISK_RAID_DISABLED_RECOVER,"RAID disabled recover"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_DISK_RAID_DEGRADED,"RAID degraded"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_DISK_RAID_DEGRADED_RECOVER,"RAID degraded recover"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_DISK_RAID_RECOVERED,"RAID recovered"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_STREAMNUM_FULL,"Stream full"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_STREAM_THIRDSTOP,"Third party stream stopped"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_FILE_END,"File ended"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_RTMP_CONNECT_FAIL,"RTMP connection fail"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_RTMP_INIT_FAIL,"RTMP initialization fail"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_ALLTIME_FLAG_START,"Start marker of alarm without arming schedule"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_STOR_ERR,"Storage error"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_STOR_DISOBEY_PLAN,"Not stored as planned"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_NO_RECOVER_FLAG_START,"Start marker of unrecoverable alarm"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_DISK_ERROR,"Disk error"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_ILLEGAL_ACCESS,"Illegal access"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_ALLTIME_FLAG_END,"End marker of alarm without arming schedule"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_VIDEO_LOST_RECOVER,"Video loss alarm recover"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_TEMPERATURE_RECOVER,"Temperature alarm recover"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_AUDIO_DETECT_RECOVER,"Audio detection alarm recover"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_STOR_ERR_RECOVER,"Storage error recover"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_STOR_DISOBEY_PLAN_RECOVER,"Not stored as planned recover"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_IMAGE_BLURRY_RECOVER,"Image blurry recover"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_SMART_TRACK_RECOVER,"Smart track recover"),
            new NETDEMO_ALARM_INFO((int)NETDEV_EXCEPTION_TYPE_E.NETDEV_EXCEPTION_REPORT_VOD_END,"Playback ended"),
            new NETDEMO_ALARM_INFO((int)NETDEV_EXCEPTION_TYPE_E.NETDEV_EXCEPTION_REPORT_VOD_ABEND,"Playback exception occured"),
            new NETDEMO_ALARM_INFO((int)NETDEV_EXCEPTION_TYPE_E.NETDEV_EXCEPTION_REPORT_BACKUP_END,"Backup ended"),
            new NETDEMO_ALARM_INFO((int)NETDEV_EXCEPTION_TYPE_E.NETDEV_EXCEPTION_REPORT_BACKUP_DISC_OUT,"Disk removed"),
            new NETDEMO_ALARM_INFO((int)NETDEV_EXCEPTION_TYPE_E.NETDEV_EXCEPTION_REPORT_BACKUP_DISC_FULL,"Disk full"),
            new NETDEMO_ALARM_INFO((int)NETDEV_EXCEPTION_TYPE_E.NETDEV_EXCEPTION_REPORT_BACKUP_ABEND,"Backup failure caused by other reasons"),
            new NETDEMO_ALARM_INFO((int)NETDEV_EXCEPTION_TYPE_E.NETDEV_EXCEPTION_EXCHANGE,"Exception occurred during user interaction new NETDEMO_ALARM_INFO((int)keep-alive timeout)"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_BANDWIDTH_CHANGE,"Bandwidth change"),
            new NETDEMO_ALARM_INFO((int)NETDEVSDK.NETDEV_E_VIDEO_RESOLUTION_CHANGE,"Resolution changed"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_LINE_CROSS,"Line cross"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_OBJECTS_INSIDE,"Objects inside"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_FACE_RECOGNIZE,"Face recognize"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_IMAGE_BLURRY,"Image blurry"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_SCENE_CHANGE,"Scene change"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_SMART_TRACK,"Smart track"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_LOITERING_DETECTOR,"Loitering detector"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_IP_CONFLICT,"IP conflict exception alarm"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_IP_CONFLICT_CLEARED,"IP conflict exception alarm recovery"),
            new NETDEMO_ALARM_INFO((int)NETDEV_ALARM_TYPE_E.NETDEV_ALARM_SMART_READ_ERROR_RATE,"Error reding the underlying data")      
        };
    }

    /*循环监视信息*/
    public class CycleMonitorInfo
    {
        /*单个监视对象信息*/
        public struct CYCLE_MONITOR_CHANNEL_INFO_S
        {
            public int deviceIndex;
            public IntPtr devhandle;
            public int channelID;/*1 ~ &*/
        }

        public NETDEMO.NETDEMO_MONITOR_TYPE_E monitorType = NETDEMO.NETDEMO_MONITOR_TYPE_E.NETDEMO_MONITOR_SINGLE_SCREEN;
        public int panelNo = 0; /*0 ~ 15*/
        public int monitorCount = 0;
        public int intervalTime = 20;/*秒*/
        public List<CYCLE_MONITOR_CHANNEL_INFO_S> channelInfoList = new List<CYCLE_MONITOR_CHANNEL_INFO_S>();
    }

    public class PlayBackInfo
    {
        public IntPtr m_devHandle = IntPtr.Zero;
        public List<NETDEV_FINDDATA_S> m_findPlayBackDataList = new List<NETDEV_FINDDATA_S>();
        public int m_curSelectedChannelID = -1;
        public int m_curSelectedDeviceIndex = -1;
        public int m_nextPlayBackPanelIndex = 0;

        public System.Timers.Timer m_timer = new System.Timers.Timer(500);//初始化为100毫秒
    }

     public struct NETDEMO_BASIC_INFO_S
    {
         public bool existFlag;
        public NETDEV_TIME_CFG_S stSystemTime;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = NETDEVSDK.NETDEV_LEN_64)]
        public String szDeviceName;
        public NETDEV_DISK_INFO_LIST_S stDiskInfoList;
    }

     public struct NETDEMO_NETWORK_INFO_S
     {
         public bool existFlag;
         public NETDEV_NETWORKCFG_S stNetWorkIP;
         public NETDEV_UPNP_NAT_STATE_S stNetWorkPort;
         public NETDEV_SYSTEM_NTP_INFO_S stNetWorkNTP;
     }

    public struct NETDEMO_INPUT_INFO_S
    {
        public bool existFlag;
        public NETDEV_ALARM_INPUT_LIST_S stInPutInfo;
        public NETDEV_ALARM_OUTPUT_LIST_S stOutPutInfo;
    }

    public struct NETDEMO_VIDEO_STREAM_INFO_S
    {
        public bool existFlag;
        public NETDEV_VIDEO_STREAM_INFO_S[] videoStreamInfoList;
    }

    public struct NETDEMO_IMAGE_INFO_S
    {
        public bool existFlag;
        public NETDEV_IMAGE_SETTING_S imageInfo;
    }

    public struct NETDEMO_VIDEO_OSD_S
    {
        public bool existFlag;
        public NETDEV_VIDEO_OSD_CFG_S OSDInfo;
    }

    public struct NETDEMO_PRIVACY_MASK_INFO_S
    {
        public bool existFlag;
        public NETDEV_PRIVACY_MASK_CFG_S privacyMaskInfo;
    }

    public struct NETDEMO_MOTION_ALARM_INFO_S
    {
        public bool existFlag;
        public NETDEV_MOTION_ALARM_INFO_S MotionAlarmInfo;
    }

    public struct NETDEMO_TAMPER_ALARM_INFO_S
    {
        public bool existFlag;
        public NETDEV_TAMPER_ALARM_INFO_S tamperAlarmInfo;
    }

    public class ChannelInfo
    {
        public NETDEV_VIDEO_CHL_DETAIL_INFO_S m_devVideoChlInfo = new NETDEV_VIDEO_CHL_DETAIL_INFO_S();
        public NETDEV_CRUISE_LIST_S m_CruiseInfoList;
        public NETDEMO_BASIC_INFO_S m_basicInfo;
        public NETDEMO_NETWORK_INFO_S m_networkInfo;
        public NETDEMO_VIDEO_STREAM_INFO_S m_videoStreamInfo;
        public NETDEMO_IMAGE_INFO_S m_imageInfo;
        public NETDEMO_VIDEO_OSD_S m_OSDInfo;
        public NETDEMO_INPUT_INFO_S m_IOInfo;
        public NETDEMO_PRIVACY_MASK_INFO_S m_privacyMaskInfo;
        public NETDEMO_MOTION_ALARM_INFO_S m_MotionAlarmInfo;
        public NETDEMO_TAMPER_ALARM_INFO_S m_tamperAlarmInfo;

        public ChannelInfo()
        {
            /**/
            m_CruiseInfoList = new NETDEV_CRUISE_LIST_S();
            m_CruiseInfoList.astCruiseInfo = new NETDEV_CRUISE_INFO_S[NETDEVSDK.NETDEV_MAX_CRUISEROUTE_NUM];
            for (int i = 0; i < m_CruiseInfoList.astCruiseInfo.Length; i++)
            {
                m_CruiseInfoList.astCruiseInfo[i].astCruisePoint = new NETDEV_CRUISE_POINT_S[NETDEVSDK.NETDEV_MAX_CRUISEPOINT_NUM];
            }

            m_basicInfo = new NETDEMO_BASIC_INFO_S();
            m_basicInfo.existFlag = false;

            m_networkInfo = new NETDEMO_NETWORK_INFO_S();
            m_networkInfo.existFlag = false;
            m_networkInfo.stNetWorkPort.astUpnpPort = new NETDEV_UPNP_PORT_STATE_S[NETDEVSDK.NETDEV_LEN_16];

            m_videoStreamInfo = new NETDEMO_VIDEO_STREAM_INFO_S();
            m_videoStreamInfo.videoStreamInfoList = new NETDEV_VIDEO_STREAM_INFO_S[3];
            m_videoStreamInfo.existFlag = false;

            m_imageInfo = new NETDEMO_IMAGE_INFO_S();
            m_imageInfo.existFlag = false;

            m_OSDInfo = new NETDEMO_VIDEO_OSD_S();
            m_OSDInfo.existFlag = false;
            m_OSDInfo.OSDInfo.astTextOverlay = new NETDEV_OSD_TEXT_OVERLAY_S[NETDEVSDK.NETDEV_OSD_TEXTOVERLAY_NUM];

            m_IOInfo = new NETDEMO_INPUT_INFO_S();
            m_IOInfo.existFlag = false;
            m_IOInfo.stInPutInfo.astAlarmInputInfo = new NETDEV_ALARM_INPUT_INFO_S[NETDEVSDK.NETDEV_MAX_ALARM_IN_NUM];

            m_privacyMaskInfo = new NETDEMO_PRIVACY_MASK_INFO_S();
            m_privacyMaskInfo.existFlag = false;
            m_privacyMaskInfo.privacyMaskInfo.astArea = new NETDEV_PRIVACY_MASK_AREA_INFO_S[NETDEVSDK.NETDEV_MAX_PRIVACY_MASK_AREA_NUM];

            m_MotionAlarmInfo = new NETDEMO_MOTION_ALARM_INFO_S();
            m_MotionAlarmInfo.existFlag = false;
            m_MotionAlarmInfo.MotionAlarmInfo.awScreenInfo = new NETDEV_SCREENINFO_COLUMN_S[NETDEVSDK.NETDEV_SCREEN_INFO_ROW];
            for (int i = 0; i < NETDEVSDK.NETDEV_SCREEN_INFO_ROW; i++)
            {
                m_MotionAlarmInfo.MotionAlarmInfo.awScreenInfo[i].columnInfo = new short[NETDEVSDK.NETDEV_SCREEN_INFO_COLUMN];
            }

            m_tamperAlarmInfo = new NETDEMO_TAMPER_ALARM_INFO_S();
            m_tamperAlarmInfo.existFlag = false;
        }
    }

    public class DeviceInfo
    {
        //本地设备信息
        public String m_ip = null;
        public Int16 m_port = 0;
        public String m_userName = null;
        public String m_password = null;

        /*云设备信息*/
        public IntPtr m_lpCloudDevHandle = IntPtr.Zero;
        public String m_cloudUrl = null;
        public String m_cloudUserName = null;
        public String m_cloudPassword = null;
        public NETDEV_CLOUD_DEV_INFO_EX_S m_stCloudDevInfo;

        /*共用信息*/
        public IntPtr m_lpDevHandle = IntPtr.Zero;
        public Int32 m_channelNumber = 0;
        public NETDEV_DEVICE_INFO_S m_stDevInfo;//设备信息，用于登录出参

        public List<ChannelInfo> m_channelInfoList = new List<ChannelInfo>();

        //public List<NETDEV_VIDEO_CHL_DETAIL_INFO_S> m_devVideoChlInfoList = new List<NETDEV_VIDEO_CHL_DETAIL_INFO_S>();
        //public List<>  = new List<NETDEV_CRUISE_LIST_S>();

        public void initDeviceInfo()
        {
            m_lpCloudDevHandle = IntPtr.Zero;
            m_lpDevHandle = IntPtr.Zero;
            m_channelNumber = 0;
            m_channelInfoList.Clear();
        }
    }
}