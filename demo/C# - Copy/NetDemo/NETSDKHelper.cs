﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using GeneralDef;
using NetDemo;

namespace NETSDKHelper
{

    /* define enum start */
    public enum NETDEV_CHANNEL_STATUS_E
    {
        NETDEV_CHL_STATUS_OFFLINE   = 0,       /* Channel offline */
        NETDEV_CHL_STATUS_ONLINE    = 1,       /* Channel online */
        NETDEV_CHL_STATUS_UNBIND    = 2,       /* Channel unbind */

        NETDEV_CHL_STATUS_INVALID
    }

    public enum NETDEV_DEVICETYPE_E
    {
        NETDEV_DTYPE_UNKNOWN = 0,                   /* Unknown type */
        NETDEV_DTYPE_IPC = 1,                       /* IPC range */
        NETDEV_DTYPE_IPC_FISHEYE = 2,               /* Fisheye IPC*/
        NETDEV_DTYPE_IPC_ECONOMIC_FISHEYE = 3,      /* Economic fisheye IPC */
        NETDEV_DTYPE_NVR = 101,                     /* NVR range */
        NETDEV_DTYPE_NVR_BACKUP = 102,              /* NVR back up */
        NETDEV_DTYPE_HNVR = 103,                    /* Mixture NVR */
        NETDEV_DTYPE_DC = 201,                      /* DC range */
        NETDEV_DTYPE_DC_ADU = 202,                  /* ADU range */
        NETDEV_DTYPE_EC = 301,                      /* EC range */
        NETDEV_DTYPE_VMS = 501,                     /* VMS range */

        NETDEV_DTYPE_INVALID = 0xFFFF               /* Invalid value */
    }

    public enum NETDEV_LIVE_STREAM_INDEX_E
    {
        NETDEV_LIVE_STREAM_INDEX_MAIN  = 0,   /* Main stream */
        NETDEV_LIVE_STREAM_INDEX_AUX   = 1,   /* Sub stream */
        NETDEV_LIVE_STREAM_INDEX_THIRD = 2,   /* Third stream */

        NETDEV_LIVE_STREAM_INDEX_INVALID
    }

    public enum NETDEV_PROTOCAL_E
    {
        NETDEV_TRANSPROTOCAL_RTPUDP = 0,         /* UDP */
        NETDEV_TRANSPROTOCAL_RTPTCP = 1          /* TCP */
    }

    public enum NETDEV_PICTURE_FLUENCY_E
    {
        NETDEV_PICTURE_REAL                 = 0,                /* Real-time first */
        NETDEV_PICTURE_FLUENCY              = 1,                /* Fluency first */
        NETDEV_PICTURE_BALANCE_NEW          = 3,                /* Balance */
        NETDEV_PICTURE_RTMP_FLUENCY         = 4,                /* RTMP fluency first */

        NETDEV_PICTURE_FLUENCY_INVALID      = 0xff              /* Invalid value */
    }

    public enum NETDEV_PTZ_E
    {
        NETDEV_PTZ_FOCUSNEAR_STOP       =0x0201,       /* Focus near stop */
        NETDEV_PTZ_FOCUSNEAR            =0x0202,       /* Focus near */
        NETDEV_PTZ_FOCUSFAR_STOP        =0x0203,       /* Focus far stop */
        NETDEV_PTZ_FOCUSFAR             =0x0204,       /* Focus far */

        NETDEV_PTZ_ZOOMTELE_STOP        = 0x0301,       /* Zoom in stop */
        NETDEV_PTZ_ZOOMTELE             = 0x0302,       /* Zoom in */
        NETDEV_PTZ_ZOOMWIDE_STOP        = 0x0303,       /* Zoom out stop */
        NETDEV_PTZ_ZOOMWIDE             = 0x0304,       /* Zoom out */
        NETDEV_PTZ_TILTUP               = 0x0402,       /* Tilt up */
        NETDEV_PTZ_TILTDOWN             = 0x0404,       /* Tilt down */
        NETDEV_PTZ_PANRIGHT             = 0x0502,       /* Pan right */
        NETDEV_PTZ_PANLEFT              = 0x0504,       /* Pan left */
        NETDEV_PTZ_LEFTUP               = 0x0702,       /* Move up left */
        NETDEV_PTZ_LEFTDOWN             = 0x0704,       /* Move down left */
        NETDEV_PTZ_RIGHTUP              = 0x0802,       /* Move up right */
        NETDEV_PTZ_RIGHTDOWN            = 0x0804,       /* Move down right */

        NETDEV_PTZ_ALLSTOP              = 0x0901,       /* All-stop command word */
        NETDEV_PTZ_FOCUS_AND_IRIS_STOP  = 0x0907,       /* Focus & Iris-stop command word */
        NETDEV_PTZ_MOVE_STOP            = 0x0908,       /* move stop command word */
        NETDEV_PTZ_ZOOM_STOP            = 0x0909,       /* zoom stop command word */

        NETDEV_PTZ_TRACKCRUISE          = 0x1001,       /* Start route patrol*/
        NETDEV_PTZ_TRACKCRUISESTOP      = 0x1002,       /* Stop route patrol*/
        NETDEV_PTZ_TRACKCRUISEREC       = 0x1003,       /* Start recording route */
        NETDEV_PTZ_TRACKCRUISERECSTOP   = 0x1004,       /* Stop recording route */
        NETDEV_PTZ_TRACKCRUISEADD       = 0x1005,       /* Add patrol route */
        NETDEV_PTZ_TRACKCRUISEDEL       = 0x1006,       /* Delete patrol route */

        NETDEV_PTZ_AREAZOOMIN           = 0x1101,       /* Zoom in area */
        NETDEV_PTZ_AREAZOOMOUT          = 0x1102,       /* Zoom out area */
        NETDEV_PTZ_AREAZOOM3D           = 0x1103,       /* 3D positioning */

        NETDEV_PTZ_BRUSHON              = 0x0A01,       /* Wiper on */
        NETDEV_PTZ_BRUSHOFF             = 0x0A02,       /* Wiper off */

        NETDEV_PTZ_LIGHTON              = 0x0B01,       /* Lamp on */
        NETDEV_PTZ_LIGHTOFF             = 0x0B02,       /* Lamp off */

        NETDEV_PTZ_HEATON               = 0x0C01,       /* Heater on */
        NETDEV_PTZ_HEATOFF              = 0x0C02,       /* Heater off */

        NETDEV_PTZ_SNOWREMOINGON        = 0x0E01,       /* Snowremoval on */
        NETDEV_PTZ_SNOWREMOINGOFF       = 0x0E02,       /* Snowremoval off  */

        NETDEV_PTZ_INVALID

    }

    public enum NETDEV_PICTURE_FORMAT_E
    {
        NETDEV_PICTURE_BMP = 0,                  /* bmp */
        NETDEV_PICTURE_JPG = 1,                  /* jpg */

        NETDEV_PICTURE_INVALID
    }

    public enum NETDEV_MEDIA_FILE_FORMAT_E
    {
        NETDEV_MEDIA_FILE_MP4                    = 0,    /* MP4(+)  mp4 media file (Audio + Video) */
        NETDEV_MEDIA_FILE_TS                     = 1,    /* TS(+)   TS media file (Audio + Video) */
        NETDEV_MEDIA_FILE_MP4_ADD_TIME           = 2,    /* MP4(+) ,  MP4 media file with time in file name (Audio + Video) */
        NETDEV_MEDIA_FILE_TS_ADD_TIME            = 3,    /* TS(+) ,  TS media file with time in file name (Audio + Video) */
        NETDEV_MEDIA_FILE_AUDIO_TS               = 4,    /* TS()   TS audio file (Only audio) */
        NETDEV_MEDIA_FILE_AUDIO_MP4              = 5,    /* MP4()   MP4 audio file (Only audio) */
        NETDEV_MEDIA_FILE_AUDIO_TS_ADD_TIME      = 6,    /* TS(),  TS audio file with time in file name (Only audio) */
        NETDEV_MEDIA_FILE_AUDIO_MP4_ADD_TIME     = 7,    /* MP4(),  MP4 audio file with time in file name (Only audio) */
        NETDEV_MEDIA_FILE_MP4_ADD_RCD_TIME       = 8,    /* MP4 media file with start and end times in file name (Audio + Video)*/
        NETDEV_MEDIA_FILE_TS_ADD_RCD_TIME        = 9,    /* TS media file with start and end times in file name (Audio + Video)*/
        NETDEV_MEDIA_FILE_AUDIO_MP4_ADD_RCD_TIME = 10,   /* MP4 audio file with start and end times in file name (Only audio)*/
        NETDEV_MEDIA_FILE_AUDIO_TS_ADD_RCD_TIME  = 11,   /* TS audio file with start and end times in file name (Only audio)*/
        NETDEV_MEDIA_FILE_VIDEO_MP4_ADD_RCD_TIME = 12,   /* mp4 media file (Only video) */
        NETDEV_MEDIA_FILE_VIDEO_TS_ADD_RCD_TIME  = 13,   /* ts media file (Only video) */

        NETDEV_MEDIA_FILE_AVI                    = 14,   /* AVI media file (Audio + Video) */
        NETDEV_MEDIA_FILE_AVI_ADD_TIME           = 15,   /* AVI media file with start and end times in file name (Audio + Video)*/
        NETDEV_MEDIA_FILE_AUDIO_AVI              = 16,   /* AVI audio file (Only audio) */
        NETDEV_MEDIA_FILE_AUDIO_AVI_ADD_TIME     = 17,   /* AVI audio file with time in file name (Only audio)*/
        NETDEV_MEDIA_FILE_AVI_ADD_RCD_TIME       = 18,   /* AVI audio file with start and end times in file name (Audio + Video)*/
        NETDEV_MEDIA_FILE_AUDIO_AVI_ADD_RCD_TIME = 19,   /* AVI audio file with start and end times in file name (Only audio)*/
        NETDEV_MEDIA_FILE_VIDEO_AVI_ADD_RCD_TIME = 20,   /* AVI media file (Only video) */

        NETDEV_MEDIA_FILE_INVALID
    }

    public enum NETDEV_PLAN_STORE_TYPE_E
    {
        NETDEV_TYPE_STORE_TYPE_ALL                  = 0,            /* All */

        NETDEV_EVENT_STORE_TYPE_MOTIONDETECTION     = 4,            /* Motion detection */
        NETDEV_EVENT_STORE_TYPE_DIGITALINPUT        = 5,            /* Digital input */
        NETDEV_EVENT_STORE_TYPE_VIDEOLOSS           = 7,            /* Video loss */

        NETDEV_TYPE_STORE_TYPE_INVALID              = 0xFF          /* Invalid value */
    }

    public enum NETDEV_E_DOWNLOAD_SPEED_E
    {
        NETDEV_DOWNLOAD_SPEED_ONE           = 0,                /* 1x */
        NETDEV_DOWNLOAD_SPEED_TWO           = 1,                /* 2x */
        NETDEV_DOWNLOAD_SPEED_FOUR          = 2,                /* 4x */
        NETDEV_DOWNLOAD_SPEED_EIGHT         = 3,                /* 8x */
        NETDEV_DOWNLOAD_SPEED_TWO_IFRAME    = 4,                /* I  I2x */
        NETDEV_DOWNLOAD_SPEED_FOUR_IFRAME   = 5,                /* I  I4x */
        NETDEV_DOWNLOAD_SPEED_EIGHT_IFRAME  = 6,                /* I  I8x */
        NETDEV_DOWNLOAD_SPEED_HALF          = 7                 /* 1/2  1/2x */
    }

    public enum NETDEV_VOD_PLAY_STATUS_E
    {
        /**   Play status */
        NETDEV_PLAY_STATUS_16_BACKWARD          = 0,            /* 16  Backward at 16x speed */
        NETDEV_PLAY_STATUS_8_BACKWARD           = 1,            /* 8  Backward at 8x speed */
        NETDEV_PLAY_STATUS_4_BACKWARD           = 2,            /* 4  Backward at 4x speed */
        NETDEV_PLAY_STATUS_2_BACKWARD           = 3,            /* 2  Backward at 2x speed */
        NETDEV_PLAY_STATUS_1_BACKWARD           = 4,            /* Backward at normal speed */
        NETDEV_PLAY_STATUS_HALF_BACKWARD        = 5,            /* 1/2  Backward at 1/2 speed */
        NETDEV_PLAY_STATUS_QUARTER_BACKWARD     = 6,            /* 1/4  Backward at 1/4 speed */
        NETDEV_PLAY_STATUS_QUARTER_FORWARD      = 7,            /* 1/4  Play at 1/4 speed */
        NETDEV_PLAY_STATUS_HALF_FORWARD         = 8,            /* 1/2  Play at 1/2 speed */
        NETDEV_PLAY_STATUS_1_FORWARD            = 9,            /* Forward at normal speed */
        NETDEV_PLAY_STATUS_2_FORWARD            = 10,           /* 2  Forward at 2x speed */
        NETDEV_PLAY_STATUS_4_FORWARD            = 11,           /* 4  Forward at 4x speed */
        NETDEV_PLAY_STATUS_8_FORWARD            = 12,           /* 8  Forward at 8x speed */
        NETDEV_PLAY_STATUS_16_FORWARD           = 13,           /* 16  Forward at 16x speed */
        NETDEV_PLAY_STATUS_2_FORWARD_IFRAME     = 14,           /* 2(I) Forward at 2x speed(I frame) */
        NETDEV_PLAY_STATUS_4_FORWARD_IFRAME     = 15,           /* 4(I) Forward at 4x speed(I frame) */
        NETDEV_PLAY_STATUS_8_FORWARD_IFRAME     = 16,           /* 8(I) Forward at 8x speed(I frame) */
        NETDEV_PLAY_STATUS_16_FORWARD_IFRAME    = 17,           /* 16(I) Forward at 16x speed(I frame) */
        NETDEV_PLAY_STATUS_2_BACKWARD_IFRAME    = 18,           /* 2(I) Backward at 2x speed(I frame) */
        NETDEV_PLAY_STATUS_4_BACKWARD_IFRAME    = 19,           /* 4(I) Backward at 4x speed(I frame) */
        NETDEV_PLAY_STATUS_8_BACKWARD_IFRAME    = 20,           /* 8(I) Backward at 8x speed(I frame) */
        NETDEV_PLAY_STATUS_16_BACKWARD_IFRAME   = 21,           /* 16(I) Backward at 16x speed(I frame) */
        NETDEV_PLAY_STATUS_INTELLIGENT_FORWARD  = 22,           /* Intelligent forward */
        NETDEV_PLAY_STATUS_1_FRAME_FORWD        = 23,           /* Forward at 1 frame speed */
        NETDEV_PLAY_STATUS_1_FRAME_BACK         = 24,           /* Backward at 1 frame speed */
        NETDEV_PLAY_STATUS_40_FORWARD           = 25,           /* Forward at 40x speed*/

        NETDEV_PLAY_STATUS_32_FORWARD_IFRAME    = 26,           /* Forward at 32x speed(I frame)*/
        NETDEV_PLAY_STATUS_32_BACKWARD_IFRAME   = 27,           /* Backward at 32x speed(I frame)*/
        NETDEV_PLAY_STATUS_64_FORWARD_IFRAME    = 28,           /* Forward at 64x speed(I frame)*/
        NETDEV_PLAY_STATUS_64_BACKWARD_IFRAME   = 29,           /* Backward at 64x speed(I frame)*/
        NETDEV_PLAY_STATUS_128_FORWARD_IFRAME   = 30,           /* Forward at 128x speed(I frame)*/
        NETDEV_PLAY_STATUS_128_BACKWARD_IFRAME  = 31,           /* Backward at 128x speed(I frame)*/
        NETDEV_PLAY_STATUS_256_FORWARD_IFRAME   = 32,           /* Forward at 256x speed(I frame)*/
        NETDEV_PLAY_STATUS_256_BACKWARD_IFRAME  = 33,           /* Backward at 256x speed(I frame)*/

        NETDEV_PLAY_STATUS_32_FORWARD           = 34,           /* Forward at 32x speed */
        NETDEV_PLAY_STATUS_32_BACKWARD          = 35,           /* Backward at 32x speed */

        NETDEV_PLAY_STATUS_INVALID
    }

    public enum NETDEV_VOD_PLAY_CTRL_E
    {
        NETDEV_PLAY_CTRL_PLAY            = 0,           /* Play */
        NETDEV_PLAY_CTRL_PAUSE           = 1,           /* Pause */
        NETDEV_PLAY_CTRL_RESUME          = 2,           /* Resume */
        NETDEV_PLAY_CTRL_GETPLAYTIME     = 3,           /* Obtain playing time */
        NETDEV_PLAY_CTRL_SETPLAYTIME     = 4,           /* Configure playing time */
        NETDEV_PLAY_CTRL_GETPLAYSPEED    = 5,           /* Obtain playing speed */
        NETDEV_PLAY_CTRL_SETPLAYSPEED    = 6,           /* Configure playing speed */
        NETDEV_PLAY_CTRL_SINGLE_FRAME    = 7            /* Configure single frame playing speed */
    }

    public enum NETDEV_CONFIG_COMMAND_E
    {
        NETDEV_GET_DEVICECFG                = 100,              /* #NETDEV_DEVICE_BASICINFO_S  Get device information, see #NETDEV_DEVICE_BASICINFO_S */
        NETDEV_SET_DEVICECFG                = 101,              /* Reserved */

        NETDEV_GET_NTPCFG                   = 110,              /* NTP,#NETDEV_SYSTEM_NTP_INFO_S  Get NTP parameter, see #NETDEV_SYSTEM_NTP_INFO_S */
        NETDEV_SET_NTPCFG                   = 111,              /* NTP,#NETDEV_SYSTEM_NTP_INFO_S  Set NTP parameter, see #NETDEV_SYSTEM_NTP_INFO_S */

        NETDEV_GET_NTPCFG_EX                = 112,              /* NTP,#NETDEV_SYSTEM_NTP_INFO_LIST_S  Get NTP parameter, see #NETDEV_SYSTEM_NTP_INFO_LIST_S */
        NETDEV_SET_NTPCFG_EX                = 113,              /* NTP,#NETDEV_SYSTEM_NTP_INFO_LIST_S  Set NTP parameter, see #NETDEV_SYSTEM_NTP_INFO_LIST_S */

        NETDEV_GET_STREAMCFG                = 120,              /* #NETDEV_VIDEO_STREAM_INFO_S  Get video encoding parameter, see #NETDEV_VIDEO_STREAM_INFO_S */
        NETDEV_SET_STREAMCFG                = 121,              /* #NETDEV_VIDEO_STREAM_INFO_S  Set video encoding parameter, see #NETDEV_VIDEO_STREAM_INFO_S */

        NETDEV_GET_STREAMCFG_EX             = 122,              /* #NETDEV_VIDEO_STREAM_INFO_LIST_S  Get video encoding parameter, see #NETDEV_VIDEO_STREAM_INFO_LIST_S */
        NETDEV_SET_STREAMCFG_EX             = 123,              /* #NETDEV_VIDEO_STREAM_INFO_LIST_S  Set video encoding parameter, see #NETDEV_VIDEO_STREAM_INFO_LIST_S */

        NETDEV_GET_VIDEOMODECFG             = 124,              /* #NETDEV_VIDEO_MODE_INFO_S */
        NETDEV_SET_VIDEOMODECFG             = 125,              /* #NETDEV_VIDEO_MODE_INFO_S */

        NETDEV_GET_PTZPRESETS               = 130,              /* #NETDEV_PTZ_ALLPRESETS_S  Get PTZ preset, see #NETDEV_PTZ_ALLPRESETS_S */

        NETDEV_GET_OSDCFG                   = 140,              /* OSD,#NETDEV_VIDEO_OSD_CFG_S  Get OSD configuration information, see #NETDEV_VIDEO_OSD_CFG_S */
        NETDEV_SET_OSDCFG                   = 141,              /* OSD,#NETDEV_VIDEO_OSD_CFG_S  Set OSD configuration information, see #NETDEV_VIDEO_OSD_CFG_S */

        NETDEV_GET_OSD_CONTENT_CFG          = 144,              /* #NETDEV_OSD_CONTENT_S  Get OSD configuration information, see #NETDEV_OSD_CONTENT_S */
        NETDEV_SET_OSD_CONTENT_CFG          = 145,              /* #NETDEV_OSD_CONTENT_S  Set OSD configuration information, see #NETDEV_OSD_CONTENT_S */
        NETDEV_GET_OSD_CONTENT_STYLE_CFG    = 146,              /* #NETDEV_OSD_CONTENT_STYLE_S  Get OSD content style, see #NETDEV_OSD_CONTENT_STYLE_S */
        NETDEV_SET_OSD_CONTENT_STYLE_CFG    = 147,              /* #NETDEV_OSD_CONTENT_STYLE_S  Set OSD content style, see #NETDEV_OSD_CONTENT_STYLE_S */

        NETDEV_GET_ALARM_OUTPUTCFG          = 150,              /* #NETDEV_ALARM_OUTPUT_LIST_S  Get boolean configuration information, see #NETDEV_ALARM_OUTPUT_LIST_S */
        NETDEV_SET_ALARM_OUTPUTCFG          = 151,              /* #NETDEV_ALARM_OUTPUT_LIST_S  Set boolean configuration information, see #NETDEV_ALARM_OUTPUT_LIST_S */
        NETDEV_TRIGGER_ALARM_OUTPUT         = 152,              /* #NETDEV_TRIGGER_ALARM_OUTPUT_S        Trigger boolean, see #NETDEV_TRIGGER_ALARM_OUTPUT_S */
        NETDEV_GET_ALARM_INPUTCFG           = 153,              /* #NETDEV_ALARM_INPUT_LIST_S   Get the number of boolean inputs, see #NETDEV_ALARM_INPUT_LIST_S */
        NETDEV_GET_MANUAL_ALARM_CFG         = 154,              /* #NETDEV_OUTPUT_SWITCH_ALARM_STATUS_LIST_S  Get manual alarm boolean configuration information, see #NETDEV_OUTPUT_SWITCH_ALARM_STATUS_LIST_S*/
        NETDEV_SET_MANUAL_ALARM_CFG         = 155,              /* #NETDEV_OUTPUT_SWITCH_MANUAL_ALARM_INFO_S  Set manual alarm boolean configuration information, see #NETDEV_OUTPUT_SWITCH_MANUAL_ALARM_INFO_S */

        NETDEV_GET_IMAGECFG                 = 160,              /* #NETDEV_IMAGE_SETTING_S  Get image configuration information, see #NETDEV_IMAGE_SETTING_S */
        NETDEV_SET_IMAGECFG                 = 161,              /* #NETDEV_IMAGE_SETTING_S  Set image configuration information, see #NETDEV_IMAGE_SETTING_S */

        NETDEV_GET_NETWORKCFG               = 170,              /* #NETDEV_NETWORKCFG_S  Get network configuration information, see #NETDEV_NETWORKCFG_S */
        NETDEV_SET_NETWORKCFG               = 171,              /* #NETDEV_NETWORKCFG_S  Set network configuration information, see #NETDEV_NETWORKCFG_S */

        NETDEV_GET_PRIVACYMASKCFG           = 180,              /* #NETDEV_PRIVACY_MASK_CFG_S  Get privacy mask configuration information, see #NETDEV_PRIVACY_MASK_CFG_S */
        NETDEV_SET_PRIVACYMASKCFG           = 181,              /* #NETDEV_PRIVACY_MASK_CFG_S  Set privacy mask configuration information, see #NETDEV_PRIVACY_MASK_CFG_S */
        NETDEV_DELETE_PRIVACYMASKCFG        = 182,              /* Delete privacy mask configuration information */

        NETDEV_GET_TAMPERALARM              = 190,              /* #NETDEV_TAMPER_ALARM_INFO_S  Get tamper alarm configuration information, see #NETDEV_TAMPER_ALARM_INFO_S */
        NETDEV_SET_TAMPERALARM              = 191,              /* #NETDEV_TAMPER_ALARM_INFO_S  Set tamper alarm configuration information, see #NETDEV_TAMPER_ALARM_INFO_S */

        NETDEV_GET_MOTIONALARM              = 200,              /* #NETDEV_MOTION_ALARM_INFO_S  Get motion alarm configuration information, see #NETDEV_MOTION_ALARM_INFO_S */
        NETDEV_SET_MOTIONALARM              = 201,              /* #NETDEV_MOTION_ALARM_INFO_S  Set motion alarm configuration information, see #NETDEV_MOTION_ALARM_INFO_S */

        NETDEV_GET_CROSSLINEALARM           = 202,              /* #NETDEV_CROSS_LINE_ALARM_INFO_S Get Cross Line alarm configuration information, see #NETDEV_CROSS_LINE_ALARM_INFO_S*/
        NETDEV_SET_CROSSLINEALARM           = 203,              /* #NETDEV_CROSS_LINE_ALARM_INFO_S Set Cross Line alarm configuration information, see #NETDEV_CROSS_LINE_ALARM_INFO_S*/

        NETDEV_GET_INTRUSIONALARM           = 204,              /* #NETDEV_INTRUSION_ALARM_INFO_S Get intrusion alarm configuration information, see #NETDEV_INTRUSION_ALARM_INFO_S*/
        NETDEV_SET_INTRUSIONALARM           = 205,              /* #NETDEV_INTRUSION_ALARM_INFO_S Set intrusion alarm configuration information, see #NETDEV_INTRUSION_ALARM_INFO_S*/

        NETDEV_GET_DISKSINFO                = 210,              /* #NETDEV_GET_DISKS_INFO_S  Get disks information, see #NETDEV_GET_DISKS_INFO_S */

        NETDEV_GET_PTZSTATUS                = 220,              /* #NETDEV_PTZ_STATUS_S Get PTZ status,  see #NETDEV_PTZ_STATUS_S  */

        NETDEV_GET_FOCUSINFO                = 230,              /* #NETDEV_FOCUS_INFO_S Get focus info, see #NETDEV_FOCUS_INFO_S */
        NETDEV_SET_FOCUSINFO                = 231,              /* #NETDEV_FOCUS_INFO_S Set focus info, see #NETDEV_FOCUS_INFO_S */

        NETDEV_GET_IRCUTFILTERINFO          = 240,              /* #NETDEV_IRCUT_FILTER_INFO_S Get IRcut filter info, see #NETDEV_IRCUT_FILTER_INFO_S */
        NETDEV_SET_IRCUTFILTERINFO          = 241,              /* #NETDEV_IRCUT_FILTER_INFO_S Set IRcut filter info, see #NETDEV_IRCUT_FILTER_INFO_S */

        NETDEV_GET_DEFOGGINGINFO            = 250,              /* #NETDEV_DEFOGGING_INFO_S Get defogging info, see #NETDEV_DEFOGGING_INFO_S */
        NETDEV_SET_DEFOGGINGINFO            = 251,              /* #NETDEV_DEFOGGING_INFO_S Set defogging info, see #NETDEV_DEFOGGING_INFO_S */

        NETDEV_GET_RECORDPLANINFO           = 252,              /* #NETDEV_RECORD_PLAN_CFG_INFO_S */
        NETDEV_SET_RECORDPLANINFO           = 253,              /* #NETDEV_RECORD_PLAN_CFG_INFO_S */

        NETDEV_GET_DST_CFG                  = 260,              /* #NETDEV_DST_CFG_S Get defogging info, see #NETDEV_DST_CFG_S */
        NETDEV_SET_DST_CFG                  = 261,              /* #NETDEV_DST_CFG_S Set defogging info, see #NETDEV_DST_CFG_S */

        NETDEV_GET_AUDIOIN_CFG              = 262,              /* #NETDEV_AUDIO_INPUT_CFG_INFO_S get audio input config info see #NETDEV_AUDIO_INPUT_CFG_INFO_S */
        NETDEV_SET_AUDIOIN_CFG              = 263,              /* #NETDEV_AUDIO_INPUT_CFG_INFO_S set audio input config info see #NETDEV_AUDIO_INPUT_CFG_INFO_S */

        NETDEV_SET_DNS_CFG                  = 270,              /* #NETDEV_DNS_INFO_S Set DNS info see #NETDEV_DNS_INFO_S*/
        NETDEV_GET_DNS_CFG                  = 271,              /* #NETDEV_DNS_INFO_S Get DNS info see #NETDEV_DNS_INFO_S*/

        NETDEV_SET_NETWORK_CARDS            = 272,              /* #NETDEV_NETWORK_CARD_INFO_S set device networkcards infos see #NETDEV_NETWORK_CARD_INFO_S*/
        NETDEV_GET_NETWORK_CARDS            = 273,              /* #NETDEV_NETWORK_CARD_INFO_S get device networkcards infos see #NETDEV_NETWORK_CARD_INFO_S*/

        NETDEV_CFG_INVALID                  = 0xFFFF            /* Invalid value */

    }

    
    public enum NETDEV_PTZ_PRESETCMD_E
    {
        NETDEV_PTZ_SET_PRESET   = 0,            /* Set preset */
        NETDEV_PTZ_CLE_PRESET   = 1,            /* Clear preset */
        NETDEV_PTZ_GOTO_PRESET  = 2             /* Go to preset */
    }


    public enum NETDEV_PTZ_CRUISECMD_E
    {
        NETDEV_PTZ_ADD_CRUISE    = 0,         /* Add patrol route */
        NETDEV_PTZ_MODIFY_CRUISE = 1,         /* Edit patrol route */
        NETDEV_PTZ_DEL_CRUISE    = 2,         /* Delete patrol route */
        NETDEV_PTZ_RUN_CRUISE    = 3,         /* Start patrol */
        NETDEV_PTZ_STOP_CRUISE   = 4          /* Stop patrol */
    }

    
    public enum NETDEV_DISK_WORK_STATUS_E
    {
        NETDEV_DISK_WORK_STATUS_EMPTY       = 0,            /* Empty */
        NETDEV_DISK_WORK_STATUS_UNFORMAT    = 1,            /* Unformat */
        NETDEV_DISK_WORK_STATUS_FORMATING   = 2,            /* Formating */
        NETDEV_DISK_WORK_STATUS_RUNNING     = 3,            /* Running */
        NETDEV_DISK_WORK_STATUS_HIBERNATE   = 4,            /* Hibernate */
        NETDEV_DISK_WORK_STATUS_ABNORMAL    = 5,            /* Abnormal */
        NETDEV_DISK_WORK_STATUS_UNKNOWN     = 6,            /* Unknown */

        NETDEV_DISK_WORK_STATUS_INVALID                     /* Invalid value */
    }


    public enum NETDEV_PROTOCOL_TYPE_E
    {
        NETDEV_PROTOCOL_TYPE_HTTP  = 0,
        NETDEV_PROTOCOL_TYPE_HTTPS = 1,
        NETDEV_PROTOCOL_TYPE_RTSP  = 2
    }


    public enum NETDEV_VIDEO_QUALITY_E
    {
        NETDEV_VQ_L0 = 0,                    /* Highest */
        NETDEV_VQ_L1 = 1,
        NETDEV_VQ_L2 = 4,                    /* Higher */
        NETDEV_VQ_L3 = 8,
        NETDEV_VQ_L4 = 12,                   /* Medium */
        NETDEV_VQ_L5 = 16,
        NETDEV_VQ_L6 = 20,                   /* Low */
        NETDEV_VQ_L7 = 24,
        NETDEV_VQ_L8 = 28,                   /* Lower */
        NETDEV_VQ_L9 = 31,                   /* Lowest */

        NETDEV_VQ_LEVEL_INVALID = -1         /* Valid */
    }

    public enum NETDEV_BOOLEAN_MODE_E
    {
        NETDEV_BOOLEAN_MODE_OPEN   = 1,                         /* Always open */
        NETDEV_BOOLEAN_MODE_CLOSE  = 2,                         /* Always closed */
        NETDEV_BOOLEAN_MODE_INVALID
    }

    public enum NETDEV_LOG_SUB_TYPE_E
    {
        NETDEV_LOG_ALL_SUB_TYPES                     = 0x0101,          /* All information logs */

        /* Information logs */
        NETDEV_LOG_MSG_HDD_INFO                     = 300,              /* HDD information */
        NETDEV_LOG_MSG_SMART_INFO                   = 301,              /* S.M.A.R.T  S.M.A.R.T information */
        NETDEV_LOG_MSG_REC_OVERDUE                  = 302,              /* Expired recording deletion */
        NETDEV_LOG_MSG_PIC_REC_OVERDUE              = 303,              /* Expired image deletion */

        /*notification logs */
        NETDEV_LOG_NOTICE_IPC_ONLINE                = 310,              /* Device online */
        NETDEV_LOG_NOTICE_IPC_OFFLINE               = 311,              /* Device offline */
        NETDEV_LOG_NOTICE_ARRAY_RECOVER             = 312,              /* arrayRecover */
        NETDEV_LOG_NOTICE_INIT_ARRARY               = 313,              /* initializeArray */
        NETDEV_LOG_NOTICE_REBUILD_ARRARY            = 314,              /*  rebuildArray */
        NETDEV_LOG_NOTICE_POE_PORT_STATUS           = 315,              /*  poePortStatus */
        NETDEV_LOG_NOTICE_NETWORK_PORT_STATUS       = 316,              /*  networkPortStatus */
        NETDEV_LOG_NOTICE_DISK_ONLINE               = 317,              /* Disk online */


        /* ID  Sub type log ID of alarm logs */
        NETDEV_LOG_ALARM_MOTION_DETECT              = 350,              /* Motion detection alarm */
        NETDEV_LOG_ALARM_MOTION_DETECT_RESUME       = 351,              /* Motion detection alarm recover */
        NETDEV_LOG_ALARM_VIDEO_LOST                 = 352,              /* Video loss alarm */
        NETDEV_LOG_ALARM_VIDEO_LOST_RESUME          = 353,              /* Video loss alarm recover */
        NETDEV_LOG_ALARM_VIDEO_TAMPER_DETECT        = 354,              /* Tampering detection alarm */
        NETDEV_LOG_ALARM_VIDEO_TAMPER_RESUME        = 355,              /* Tampering detection alarm recover */
        NETDEV_LOG_ALARM_INPUT_SW                   = 356,              /* Boolean input alarm */
        NETDEV_LOG_ALARM_INPUT_SW_RESUME            = 357,              /* Boolean input alarm recover */
        NETDEV_LOG_ALARM_IPC_ONLINE                 = 358,              /* Device online */
        NETDEV_LOG_ALARM_IPC_OFFLINE                = 359,              /* Device offline */

        /* ID  Sub type log ID of exception logs */
        NETDEV_LOG_EXCEP_DISK_ONLINE                = 400,              /* Disk online */
        NETDEV_LOG_EXCEP_DISK_OFFLINE               = 401,              /* Disk offline */
        NETDEV_LOG_EXCEP_DISK_ERR                   = 402,              /* Disk exception */
        NETDEV_LOG_EXCEP_STOR_ERR                   = 403,              /* Storage error */
        NETDEV_LOG_EXCEP_STOR_ERR_RECOVER           = 404,              /* Storage error recover */
        NETDEV_LOG_EXCEP_STOR_DISOBEY_PLAN          = 405,              /* Not stored as planned */
        NETDEV_LOG_EXCEP_STOR_DISOBEY_PLAN_RECOVER  = 406,              /* Not stored as planned recover */
        NETDEV_LOG_EXCEP_ILLEGAL_ACCESS             = 407,              /* Illegal access */
        NETDEV_LOG_EXCEP_IP_CONFLICT                = 408,              /* IP  IP address conflict */
        NETDEV_LOG_EXCEP_NET_BROKEN                 = 409,              /* Network disconnection */
        NETDEV_LOG_EXCEP_PIC_REC_ERR                = 410,              /* ,  Failed to get captured image */
        NETDEV_LOG_EXCEP_VIDEO_EXCEPTION            = 411,              /* ()  Video input exception (for analog channel only) */
        NETDEV_LOG_EXCEP_VIDEO_MISMATCH             = 412,              /* Video standards do not match */
        NETDEV_LOG_EXCEP_RESO_MISMATCH              = 413,              /* Encoding resolution and front-end resolution do not match */
        NETDEV_LOG_EXCEP_TEMP_EXCE                  = 414,              /* Temperature exception */
        NETDEV_LOG_EXCEP_RUNOUT_RECORD_SPACE        = 415,              /* runOutOfRecordSpace */
        NETDEV_LOG_EXCEP_RUNOUT_IMAGE_SPACE         = 416,              /* runOutOfImageSpace */
        NETDEV_LOG_EXCEP_OUT_RECORD_SPACE           = 417,              /* recordSpaceUsedUp */
        NETDEV_LOG_EXCEP_OUT_IMAGE_SPACE            = 418,              /* imageSpaceUsedUp */
        NETDEV_LOG_EXCEP_ANRIDISASSEMBLY            = 419,              /* antiDisassembly Alarm */
        NETDEV_LOG_EXCEP_ANRIDISASSEMBLY_RECOVER    = 420,              /* antiDisassembly AlarmClear*/
        NETDEV_LOG_EXCEP_ARRAY_DAMAGE               = 421,              /* arrayDamage */
        NETDEV_LOG_EXCEP_ARRAY_DEGRADE              = 422,              /* arrayDegrade */
        NETDEV_LOG_EXCEP_RECORD_SNAPSHOT_ABNOR      = 423,              /* recordSnapshotAbnormal */
        NETDEV_LOG_EXCEP_NET_BROKEN_RECOVER         = 424,              /* networkDisconnectClear */
        NETDEV_LOG_EXCEP_IP_CONFLICT_RECOVER        = 425,              /* ipConflictClear */

        /* ID  Sub type log ID of operation logs */
        /* Services */
        NETDEV_LOG_OPSET_LOGIN                      = 450,              /* User login */
        NETDEV_LOG_OPSET_LOGOUT                     = 451,              /* Log out */
        NETDEV_LOG_OPSET_USER_ADD                   = 452,              /* Add user */
        NETDEV_LOG_OPSET_USER_DEL                   = 453,              /* Delete user */
        NETDEV_LOG_OPSET_USER_MODIFY                = 454,              /* Modify user */
        NETDEV_LOG_OPSET_START_REC                  = 455,              /* Start recording */
        NETDEV_LOG_OPSET_STOP_REC                   = 456,              /* Stop recording */
        NETDEV_LOG_OPSETR_PLAY_DOWNLOAD             = 457,              /* /  Playback and download */
        NETDEV_LOG_OPSET_DOWNLOAD                   = 458,              /* Download */
        NETDEV_LOG_OPSET_PTZCTRL                    = 459,              /* PTZ control */
        NETDEV_LOG_OPSET_PREVIEW                    = 460,              /* Live preview */
        NETDEV_LOG_OPSET_REC_TRACK_START            = 461,              /* Start recording route */
        NETDEV_LOG_OPSET_REC_TRACK_STOP             = 462,              /* Stop recording route */
        NETDEV_LOG_OPSET_START_TALKBACK             = 463,              /* Start two-way audio */
        NETDEV_LOG_OPSET_STOP_TALKBACK              = 464,              /* Stop two-way audio */
        NETDEV_LOG_OPSET_IPC_ADD                    = 465,              /* IPC  Add IP camera */
        NETDEV_LOG_OPSET_IPC_DEL                    = 466,              /* IPC  Delete IP camera */
        NETDEV_LOG_OPSET_IPC_SET                    = 467,              /* IPC  Modify IP camera */
        NETDEV_LOG_OPSET_IPC_QUICK_ADD              = 468,              /* quickAddIpc*/
        NETDEV_LOG_OPSET_IPC_ADD_BY_NETWORK         = 469,              /* addIpcByNetwork */
        NETDEV_LOG_OPSET_IPC_MOD_IP                 = 470,              /* modifyIpcAddr */

        /* Configurations */
        NETDEV_LOG_OPSET_DEV_BAS_CFG                = 500,              /* Basic device information */
        NETDEV_LOG_OPSET_TIME_CFG                   = 501,              /* Device time */
        NETDEV_LOG_OPSET_SERIAL_CFG                 = 502,              /* Device serial port */
        NETDEV_LOG_OPSET_CHL_BAS_CFG                = 503,              /* Basic channel configuration */
        NETDEV_LOG_OPSET_CHL_NAME_CFG               = 504,              /* Channel name configuration */
        NETDEV_LOG_OPSET_CHL_ENC_VIDEO              = 505,              /* Video encoding configuration */
        NETDEV_LOG_OPSET_CHL_DIS_VIDEO              = 506,              /* Video display configuration */
        NETDEV_LOG_OPSET_PTZ_CFG                    = 507,              /* PTZ configuration */
        NETDEV_LOG_OPSET_CRUISE_CFG                 = 508,              /* Patrol route configuration */
        NETDEV_LOG_OPSET_PRESET_CFG                 = 509,              /* Preset configuration */
        NETDEV_LOG_OPSET_VIDPLAN_CFG                = 510,              /* Recording schedule configuration */
        NETDEV_LOG_OPSET_MOTION_CFG                 = 511,              /* Motion detection configuration */
        NETDEV_LOG_OPSET_VIDLOSS_CFG                = 512,              /* Video loss configuration */
        NETDEV_LOG_OPSET_COVER_CFG                  = 513,              /* Tampering detection configuration */
        NETDEV_LOG_OPSET_MASK_CFG                   = 514,              /* Privacy mask configuration */
        NETDEV_LOG_OPSET_SCREEN_OSD_CFG             = 515,              /* OSD  OSD overlay configuration */
        NETDEV_LOG_OPSET_ALARMIN_CFG                = 516,              /* Alarm input configuration */
        NETDEV_LOG_OPSET_ALARMOUT_CFG               = 517,              /* Alarm output configuration */
        NETDEV_LOG_OPSET_ALARMOUT_OPEN_MAN          = 518,              /* ,  Manually enable alarm output, GUI */
        NETDEV_LOG_OPSET_ALARMOUT_CLOSE_MAN         = 519,              /* ,  Manually disable alarm input, GUI */
        NETDEV_LOG_OPSET_ABNORMAL_CFG               = 520,              /* Exception configuration */
        NETDEV_LOG_OPSET_HDD_CFG                    = 521,              /* HDD configuration */
        NETDEV_LOG_OPSET_NET_IP_CFG                 = 522 ,             /* TCP/IP  TCP/IP configuration */
        NETDEV_LOG_OPSET_NET_PPPOE_CFG              = 523,              /* PPPOE  PPPOE configuration */
        NETDEV_LOG_OPSET_NET_PORT_CFG               = 524,              /* Port configuration */
        NETDEV_LOG_OPSET_NET_DDNS_CFG               = 525,              /* DDNS  DDNS configuration */
        NETDEV_LOG_OPSET_AUDIO_DETECT               = 527,              /* searchExtendDisk */
        NETDEV_LOG_OPSET_SEARCH_EX_DISK             = 528,              /* searchExtendDisk */
        NETDEV_LOG_OPSET_ADD_EX_DISK                = 529,              /* addExtendDisk */
        NETDEV_LOG_OPSET_DEL_EX_DISK                = 530,              /*  deleteExtendDisk */
        NETDEV_LOG_OPSET_SET_EX_DISK                = 531,              /* setExtendDisk */
        NETDEV_LOG_OPSET_LIVE_BY_MULTICAST          = 532,              /*  liveViewByMulticast */
        NETDEV_LOG_OPSET_BISC_DEV_INFO              = 533,              /*  setBasicDeviceInfo */
        NETDEV_LOG_OPSET_PREVIEW_CFG                = 534,              /* SetPreviewOnNvr */
        NETDEV_LOG_OPSET_SET_EMAIL                  = 535,              /* setEmail */
        NETDEV_LOG_OPSET_TEST_EMAIL                 = 536,              /* testEmail */
        NETDEV_LOG_OPSET_SET_IPCONTROL              = 537,              /*  setIPControl */
        NETDEV_LOG_OPSET_PORT_MAP                   = 538,              /* setPortMap */
        NETDEV_LOG_OPSET_ADD_TAG                    = 539,              /*  addTag */
        NETDEV_LOG_OPSET_DEL_TAG                    = 540,              /* 删除录像标签  deleteTag */
        NETDEV_LOG_OPSET_MOD_TAG                    = 541,              /* 修改录像标签  modifyTag */
        NETDEV_LOG_OPSET_LOCK_RECORD                = 542,              /* 录像锁定  lockRecord */
        NETDEV_LOG_OPSET_UNLOCK_RECORD              = 543,              /* 录像解锁定  unlockRecord */
        NETDEV_LOG_OPSET_DDNS_UPDATE_SUCCESS        = 545,              /* DDNS更新成功  DDNSUpdateSuccess */
        NETDEV_LOG_OPSET_DDNS_INCORRECT_ID          = 546,              /* DDNS更新失败，错误的用户名密码  DDNSUpdateFailedIncorrectUsernamePassword */
        NETDEV_LOG_OPSET_DDNS_DOMAIN_NAME_NOT_EXIST = 547,              /* DDNS更新失败，域名不存在  DDNSUpdateFailedDomainNameNotExist */
        NETDEV_LOG_OPSET_DDNS_UPDATE_FAIL           = 548,              /* DDNS更新失败  DDNSUpdateFailed */
        NETDEV_LOG_OPSET_HTTP_CFG                   = 549,              /* HTTPS配置  setHttps */
        NETDEV_LOG_OPSET_IP_OFFLINE_ALARM_CFG       = 550,              /* IPC离线报警配置  testDDNSDomain */
        NETDEV_LOG_OPSET_TELNET_CFG                 = 551,              /* Telnet配置  setTelnet */
        NETDEV_LOG_OPSET_TEST_DDNS_DOMAIN           = 552,              /* DDNS域名检测  testDDNSDomain */
        NETDEV_LOG_OPSET_DDNS_DOMAIN_CONFLICT       = 553,              /* DDNS域名冲突  DDNSDomainInvalid */
        NETDEV_LOG_OPSET_DDNS_DOMAIN_INVALID        = 554,              /* DDNS域名不合法  setDDNS */
        NETDEV_LOG_OPSET_DEL_PRESET                 = 555,              /* 删除预置位  deletePreset */
        NETDEV_LOG_OPSET_PTZ_3D_POSITION            = 556,              /* 云台3D定位  ptz3DPosition */
        NETDEV_LOG_OPSET_SNAPSHOT_SCHEDULE_CFG      = 557,              /* 抓图计划配置  setSnapshotSchedule */
        NETDEV_LOG_OPSET_IMAGE_UPLOAD_SCHEDULE_CFG  = 558,              /* 图片上传计划配置  setImageUploadSchedule */
        NETDEV_LOG_OPSET_FTP_CFG                    = 559,              /* FTP服务器配置  setFtpServer */
        NETDEV_LOG_OPSET_TEST_FTP_SERVER            = 560,              /* FTP服务器连接测试  testFtpServer */
        NETDEV_LOG_OPSET_START_MANUAL_SNAPSHOT      = 561,              /* 手动抓图开启  startManualSnapshot */
        NETDEV_LOG_OPSET_CLOSE_MANUAL_SNAPSHOT      = 562,              /* 手动抓图关闭  endManualSnapshot */
        NETDEV_LOG_OPSET_SNAPSHOT_CFG               = 563,              /* 抓图参数配置  setSnapshot */
        NETDEV_LOG_OPSET_ADD_HOLIDAY                = 564,             /* 添加假日  addHoliday */
        NETDEV_LOG_OPSET_DEL_HOLIDAY                = 565,              /* 删除假日  deleteHoliday */
        NETDEV_LOG_OPSET_MOD_HOLIDAY                = 566,              /* 修改假日  modifyHoliday */
        NETDEV_LOG_OPSET_ONOFF_HOLIDAY              = 567,              /* 开启/关闭假日  enableDisableHoliday */
        NETDEV_LOG_OPSET_ALLOCATE_SPACE             = 568,              /* 容量配置  allocateSpace */
        NETDEV_LOG_OPSET_HDD_FULL_POLICY_CFG        = 569,              /* 满策略配置  setHddFullPolicy */
        NETDEV_LOG_OPSET_AUDIO_STREAM_CFG           = 570,              /* 音频流配置  setAudioStream */
        NETDEV_LOG_OPSET_ARRAY_PROPERTY_CFG         = 571,              /* 阵列属性配置  setArrayProperty */
        NETDEV_LOG_OPSET_HOT_SPACE_DISK_CFG         = 572,              /* 热备盘配置  setHotSpaceDisk */
        NETDEV_LOG_OPSET_CREAT_ARRAY                = 573,              /* 手动创建阵列  createArray */
        NETDEV_LOG_OPSET_ONE_CLICK_CREAT_ARRAY      = 574,              /* 一键创建阵列  oneClickCreateArray */
        NETDEV_LOG_OPSET_REBUILD_ARRAY              = 575,              /* 重建阵列  rebuildArray */
        NETDEV_LOG_OPSET_DEL_ARRAY                  = 576,              /* 删除阵列  deleteArray */
        NETDEV_LOG_OPSET_ENABLE_RAID                = 577,              /* 开启RAID模式  enableRaid */
        NETDEV_LOG_OPSET_DISABLE_RAID               = 578,              /* 关闭RAID模式  disableRaid */
        NETDEV_LOG_OPSET_TEST_SMART                 = 579,              /* S.M.A.R.T检测  testSmart */
        NETDEV_LOG_OPSET_SMART_CFG                  = 580,              /* S.M.A.R.T配置  setSmart */
        NETDEV_LOG_OPSET_BAD_SECTOR_DETECT          = 581,              /* 坏道检测  badSectorDetect */
        NETDEV_LOG_OPSET_AUDIO_ALARM_DURATION       = 582,              /* 配置声音报警时长  setAudioAlarmDuration */
        NETDEV_LOG_OPSET_CLR_AUDIO_ALARM            = 583,             /* 清除声音报警  clearAudioAlarm */
        NETDEV_LOG_OPSET_IPC_TIME_SYNC_CFG          = 584,              /* 配置同步摄像机时间  setIpcTimeSync */
        NETDEV_LOG_OPSET_ENABLE_DISK_GROUP          = 585,              /* 开启盘组  enableDiskGroup */
        NETDEV_LOG_OPSET_DISABLE_DISK_GRRUOP        = 586,              /* 关闭盘组  disableDiskGroup */
        NETDEV_LOG_OPSET_ONVIF_AUTH_CFG             = 587,              /* ONVIF认证配置  setOnvifAuth */
        NETDEV_LOG_OPSET_8021X_CFG                  = 588,              /* 配置802.1X  set8021x */
        NETDEV_LOG_OPSET_ARP_PROTECTION_CFG         = 589,              /* 配置ARP防攻击  setArpProtection */
        NETDEV_LOG_OPSET_SMART_BASIC_INFO_CFG       = 590,             /* 智能报警基本信息配置  setSmartBasicInfo */
        NETDEV_LOG_OPSET_CROSS_LINE_DETECT_CFG      = 591,              /* 越界检测配置  setCrossLineDetection */
        NETDEV_LOG_OPSET_INSTRUSION_DETECT_CFG      = 592,              /* 区域入侵配置  setIntrusionDetection */
        NETDEV_LOG_OPSET_PEOPLE_COUNT_CFG           = 593,              /* 客流量配置  setPeopleCount */
        NETDEV_LOG_OPSET_FACE_DETECT_CFG            = 594,              /* 人脸检测配置  setFaceDetection */
        NETDEV_LOG_OPSET_FISHEYE_CFG                = 595,              /* 鱼眼配置  setFisheye */
        NETDEV_LOG_OPSET_CUSTOM_PROTOCOL_CFG        = 596,              /* 自定义协议配置  setCustomProtocol */
        NETDEV_LOG_OPSET_BEHAVIOR_SEARCH            = 597,              /* 行为检索  behaviorSearch */
        NETDEV_LOG_OPSET_FACE_SEARCH                = 598,              /* 人脸检索  faceSearch */
        NETDEV_LOG_OPSET_PEOPLE_COUNT               = 599,              /* 客流量统计  peopleCount */

        /* Maintenance */
        NETDEV_LOG_OPSET_START_DVR                  = 600,              /* Start up*/
        NETDEV_LOG_OPSET_STOP_DVR                   = 601,              /* Shut down */
        NETDEV_LOG_OPSET_REBOOT_DVR                 = 602,              /* Restart device */
        NETDEV_LOG_OPSET_UPGRADE                    = 603,              /* Version upgrade */
        NETDEV_LOG_OPSET_LOGFILE_EXPORT             = 604,              /* Export log files */
        NETDEV_LOG_OPSET_CFGFILE_EXPORT             = 605,              /* Export configuration files */
        NETDEV_LOG_OPSET_CFGFILE_IMPORT             = 606,              /* Import configuration files */
        NETDEV_LOG_OPSET_CONF_SIMPLE_INIT           = 607,              /* Export configuration files */
        NETDEV_LOG_OPSET_CONF_ALL_INIT              = 608,               /* Restore to factory settings */
        NETDEV_LOG_OPSET_VCA_BACKUP = 700,              /* 智能备份  vcaBackup */
        NETDEV_LOG_OPSET_3G4G_CFG = 701,              /* 3G/4G配置  set3g4g */
        NETDEV_LOG_OPSET_MOUNT_EXTENDED_DISK = 702,              /* 加载扩展硬盘 Mount extended disk*/
        NETDEV_LOG_OPSET_UNMOUNT_EXTENDED_DISK = 703,              /* 卸载扩展硬盘 Unmount extended disk*/
        NETDEV_LOG_OPSET_FORCE_USER_OFFLINE = 704,              /* 强制用户下线 Force user off line*/

        NETDEV_LOG_OPSET_AUTO_FUNCTION = 709,              /* 自动维护  autoFunction */
        NETDEV_LOG_OPSET_IPC_UPRAGDE = 710,              /* 摄像机升级  ipcUpgrade */
        NETDEV_LOG_OPSET_RESTORE_IPC_DEFAULTS = 711,              /* 摄像机恢复默认配置  restoreIpcDefaults */
        NETDEV_LOG_OPSET_ADD_TRANSACTION = 712,              /* 添加交易配置  addTransaction */
        NETDEV_LOG_OPSET_MOD_TRANSACTION = 713,              /* 修改交易配置  modifyTransaction */
        NETDEV_LOG_OPSET_DEL_TRANSACTION = 714,              /* 删除交易配置  deleteTransaction */
        NETDEV_LOG_OPSET_POS_OSD = 715,              /* POS显示配置设置  setPosOsd */
        NETDEV_LOG_OPSET_ADD_HOT_SPACE_DEV = 716,              /* 添加备机  addHotSpaceDevice */
        NETDEV_LOG_OPSET_DEL_HOT_SPACE_DEV = 717,              /* 删除备机  deleteHotSpaceDevice */
        NETDEV_LOG_OPSET_MOD_HOT_SPACE_DEV = 718,              /* 修改备机  modifyHotSpaceDevice */
        NETDEV_LOG_OPSET_DEL_WORK_DEV = 719,              /* 删除工作机  deleteWorkDevice */
        NETDEV_LOG_OPSET_WORKMODE_TO_NORMAL_CFG = 720,              /* 设置工作机模式  SetWorkModeToNormal */
        NETDEV_LOG_OPSET_WORKMODE_TO_HOTSPACE_CFG = 721,              /* 设置备机模式  SetWorkModeToHotSpace */
        NETDEV_LOG_OPSET_AUTO_GUARD_CFG = 723,              /* 守望配置  setAutoGuard */
        NETDEV_LOG_OPSET_MULTICAST_CFG = 724,              /* 组播配置  SetMulticast */
        NETDEV_LOG_OPSET_DEFOCUS_DETECT_CFG = 725,              /* 虚焦检测配置 Set defocus detection*/
        NETDEV_LOG_OPSET_SCENECHANGE_CFG = 726,              /* 场景变更配置 Set scene change detection*/
        NETDEV_LOG_OPSET_AUTO_TRCAK_CFG = 727,              /* 智能跟踪配置 Set auto tracking*/
        NETDEV_LOG_OPSET_SORT_CAMERA_CFG = 728,              /* 通道排序 Sort camera*/
        NETDEV_LOG_OPSET_WATER_MARK_CFG = 729              /* 视频水印配置 Set watermark*/     

    }

    public enum NETDEV_EXCEPTION_TYPE_E
    {
        /* Playback exceptions report 300~399 */
        NETDEV_EXCEPTION_REPORT_VOD_END             = 300,          /* Playback ended*/
        NETDEV_EXCEPTION_REPORT_VOD_ABEND           = 301,          /* Playback exception occured */
        NETDEV_EXCEPTION_REPORT_BACKUP_END          = 302,          /* Backup ended */
        NETDEV_EXCEPTION_REPORT_BACKUP_DISC_OUT     = 303,          /* Disk removed */
        NETDEV_EXCEPTION_REPORT_BACKUP_DISC_FULL    = 304,          /* Disk full */
        NETDEV_EXCEPTION_REPORT_BACKUP_ABEND        = 305,          /* Backup failure caused by other reasons */

        NETDEV_EXCEPTION_EXCHANGE                   = 0x8000,       /* Exception occurred during user interaction (keep-alive timeout) */
        NETDEV_EXCEPTION_REPORT_ALARM_INTERRUPT     = 0x8001,       /* Alarm report abnormal end ,keep live failure or long connection disconnection*/

        NETDEV_EXCEPTION_REPORT_INVALID             = 0xFFFF        /* Invalid value */
    }

    public enum NETDEV_FORM_TYPE_E
    {
        NETDEV_FORM_TYPE_DAY    = 0,            /* Form type : Day */
        NETDEV_FORM_TYPE_WEEK   = 1,            /* Form type : Week */
        NETDEV_FORM_TYPE_MONTH  = 2,            /* Form type : Month */
        NETDEV_FORM_TYPE_YEAR   = 3,            /* Form type : Year */
        NETDEV_FORM_TYPE_BUTT
    }

    /* define enum end */

    /* define struct start */

    //
    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_DEVICE_INFO_S
    {
        public Int32 dwDevType;
        public Int16 wAlarmInputNum;                   /* Number of alarm inputs */
        public Int16 wAlarmOutputNum;                  /* Number of alarm outputs */
        public Int32 dwChannelNum;                      /* Number of Channels */
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 48)]
        public byte[] szReserve;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_CLOUD_DEV_INFO_EX_S
    {        
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = GeneralDef.NETDEMO.NETDEV_IPV4_LEN_MAX)]  
        public string    szIPAddr;                                                          /* IP Device IP */
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = GeneralDef.NETDEMO.NETDEV_USERNAME_LEN_260)]
        public string    szDevUserName;                                                     /* Device username */
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = GeneralDef.NETDEMO.NETDEV_LEN_260)]  
        public string    szDevName;                                                         /* Device name */
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = GeneralDef.NETDEMO.NETDEV_MODEL_LEN_64)]
        public string    szDevModel;                                                        /* Device model */
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = GeneralDef.NETDEMO.NETDEV_SERIAL_NUMBER_LEN_64)]
        public string    szDevSerialNum;                                                     /* Device serial number */
        public Int32     dwOrgID;                                                                    /* ID Home organization ID */
        public Int32     dwDevPort;                                                                  /* Device port */
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 128)]
        public string    byRes;                                 /* */
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_CLOUD_DEV_LOGIN_S
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 64)]
        public string szDeviceName;                   /* Device name */
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 64)]
        public string szDevicePassword;               /* Device password */
        public Int32 dwT2UTimeout;                                 /* T2U Time out,default 15s */
    };

    /**/
    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_ALARM_INFO_S
    {
        public Int32   dwAlarmType;                    /* ,#NETDEV_ALARM_TYPE_E  Alarm type, see enumeration #NETDEV_ALARM_TYPE_E */
        public Int64   tAlarmTime;                     /* Alarm time */
        public Int32   dwChannelID;                    /* ,NVR  Channel ID for NVR */
        public UInt16  wIndex;                         /* ,  Index number,  disk slot index number */
        public string  pszName;                       /* , Alarm source name, alarm input/output name */
        public Int32   dwTotalBandWidth;               /* ,MBps */
        public Int32   dwUnusedBandwidth;              /* ,MBps */
        public Int32   dwTotalStreamNum;               /* */
        public Int32   dwFreeStreamNum;                /* */
        public Int32   dwMediaMode;                    /* ,#NETDEV_MEDIA_MODE_E */
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 10)]
        public string  byRes;                          /* Reserved */
    }

    /**/
    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_DISCOVERY_DEVINFO_S
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = GeneralDef.NETDEMO.NETDEV_LEN_64)]
        public string    szDevAddr;                            /* Device address */
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = GeneralDef.NETDEMO.NETDEV_LEN_64)]
        public string    szDevModule;                          /* Device model */  
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = GeneralDef.NETDEMO.NETDEV_LEN_64)]
        public string    szDevSerailNum;                       /* Device serial number */
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = GeneralDef.NETDEMO.NETDEV_LEN_64)]
        public string    szDevMac;                             /* MAC  Device MAC address */ 
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = GeneralDef.NETDEMO.NETDEV_LEN_64)]
        public string    szDevName;                            /* Device name */
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = GeneralDef.NETDEMO.NETDEV_LEN_64)]
        public string    szDevVersion;                         /* Device version */
        public NETDEV_DEVICETYPE_E  enDevType;                              /* Device type */
        public Int32   dwDevPort;                                           /* Device port number */
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = GeneralDef.NETDEMO.NETDEV_LEN_64)]
        public string    szManuFacturer;                       /* Device manufacture */
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = GeneralDef.NETDEMO.NETDEV_LEN_64)]
        public string    szActiveCode;                         /* activeCode */
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = GeneralDef.NETDEMO.NETDEV_LEN_64)]
        public string    szCloudUserName; 
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 68)]
        public string    byRes;                                          /* Reserved */
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_VIDEO_CHL_DETAIL_INFO_S
    {
        public Int32 dwChannelID;
        public Int32 bPtzSupported;          /* Whether ptz is supported */
        public Int32 enStatus;        /* Channel status */    
        public Int32 dwStreamNum;     /* Number of streams */
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = GeneralDef.NETDEMO.NETDEV_LEN_64)]
        public string szChnName;                       /* Device serial number */
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
        public byte[] szReserve;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_PREVIEWINFO_S
    {
        public Int32 dwChannelID;                    /* ID  Channel ID */
        public Int32 dwStreamType;                   /* #NETDEV_LIVE_STREAM_INDEX_E  Stream type, see enumeration #NETDEV_LIVE_STREAM_INDEX_E */
        public Int32 dwLinkMode;                     /* #NETDEV_PROTOCAL_E  Transport protocol, see enumeration #NETDEV_PROTOCAL_E */
        public IntPtr hPlayWnd;                      /* Play window handle */
        public Int32 dwFluency;                      /* #NETDEV_PICTURE_FLUENCY_E  image play fluency*/
        public Int32 dwStreamMode;                   /* #NETDEV_STREAM_MODE_E  start stream mode see #NETDEV_STREAM_MODE_E*/
        public Int32 dwLiveMode;                     /* #NETDEV_PULL_STREAM_MODE_E  Rev. Flow pattern */
        public Int32 dwDisTributeCloud;              /* #NETDEV_DISTRIBUTE_CLOUD_SRV_E distribution  */
        public Int32 dwallowDistribution;                    /* allow or no distribution*/
    
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 244)]
        public byte[] szReserve;                    /* Reserved */
    }
    
    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_FILECOND_S
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = GeneralDef.NETDEMO.NETDEV_LEN_64)]
        public String szFileName;                    /* Recording file name */
        public Int32 dwChannelID;                    /* Channel ID */
        public Int32 dwStreamType;                   /* ,#NETDEV_LIVE_STREAM_INDEX_E  Stream type, see enumeration #NETDEV_LIVE_STREAM_INDEX_E */
        public Int32 dwFileType;                     /* Recording storage type, see enumeration #NETDEV_PLAN_STORE_TYPE_E */
        public Int64 tBeginTime;                     /* Start time */
        public Int64 tEndTime;                       /* End time */
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 36)]
        public byte[] szReserve;                    /* Reserved */
    }


    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_FINDDATA_S
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 256)]
        public String    szFileName;               /* Recording file name */
        public Int64 tBeginTime;                                     /* Start time */
        public Int64 tEndTime;                                       /* End time */
        public byte byFileType;                                     /* Recording storage type */
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 171)]
        public byte[] szReserve;                    /* Reserved */
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_PLAYBACKINFO_S
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = GeneralDef.NETDEMO.NETDEV_LEN_260)]
        public String    szName;         /* Playback control block name*/
        public Int64   tBeginTime;                     /* Playback start time */
        public Int64   tEndTime;                       /* Playback end time */
        public Int32   dwLinkMode;                     /* #NETDEV_PROTOCAL_E  Transport protocol, see enumeration #NETDEV_PROTOCAL_E */
        public IntPtr  hPlayWnd;                       /* Play window handle */
        public Int32   dwFileType;                     /* #NETDEV_PLAN_STORE_TYPE_E  Recording storage type, see enumeration #NETDEV_PLAN_STORE_TYPE_E */
        public Int32   dwDownloadSpeed;                /* #NETDEV_E_DOWNLOAD_SPEED_E  Download speed, see enumeration #NETDEV_E_DOWNLOAD_SPEED_E */
        public Int32   dwStreamMode;                 /* stream mode see #NETDEV_STREAM_MODE_E */
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 252)]
        public byte[] szReserve;                    /* Reserved */
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_PLAYBACKCOND_S
    {
        public Int32 dwChannelID;                /* Playback channel */
        public Int64 tBeginTime;                 /* Playback start time */
        public Int64 tEndTime;                   /* Playback end time */
        public Int32 dwLinkMode;                 /* #NETDEV_PROTOCAL_E  Transport protocol, see enumeration #NETDEV_PROTOCAL_E */
        public IntPtr hPlayWnd;                   /* Play window handle */
        public Int32 dwFileType;                 /*#NETDEV_PLAN_STORE_TYPE_E  Recording storage type, see enumeration #NETDEV_PLAN_STORE_TYPE_E */
        public Int32 dwDownloadSpeed;            /* #NETDEV_E_DOWNLOAD_SPEED_E */
        public Int32 dwStreamMode;                 /* stream mode see #NETDEV_STREAM_MODE_E */
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 252)]
        public byte[] szReserve;                    /* Reserved */
    }


    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_PTZ_PRESET_S
    {
        public Int32 dwPresetID;                                 /* ID  Preset ID */
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = NETDEVSDK.NETDEV_LEN_32)]
        public String szPresetName;                /* Preset name */
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_PTZ_ALLPRESETS_S
    {
        public Int32               dwSize;                             /* Total number of presets */
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = GeneralDef.NETDEMO.NETDEV_MAX_PRESET_NUM)]
        public NETDEV_PTZ_PRESET_S[] astPreset;   /* Structure of preset information */
    }

    public struct NETDEV_PTZ_TRACK_INFO_S
    {
        public Int32 dwTrackNum;                                               /* Number of existing patrol routes */
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = NETDEVSDK.NETDEV_LEN_64)]
        public String  TrackName;  /* Route name */
    }


    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_CRUISE_INFO_S
    {
        public Int32 dwCuriseID;                                     /* ID  Route ID */
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = NETDEVSDK.NETDEV_LEN_32)]
        public string szCuriseName;                    /* Route name */
        public Int32 dwSize;                                         /* Number of presets included in the route */
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = NETDEVSDK.NETDEV_MAX_CRUISEPOINT_NUM)]
        public NETDEV_CRUISE_POINT_S[] astCruisePoint;     /* Information of presets included in the route */
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_NETWORKCFG_S
    {
        public Int32 dwMTU;                                         /* MTU value */
        public Int32 dwIPv4DHCP;                                    /* DHCP of IPv4 */
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = NETDEVSDK.NETDEV_LEN_32)]
        public string Ipv4AddressStr;                                /* IP address of IPv4 */
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = NETDEVSDK.NETDEV_LEN_32)]
        public string szIPv4GateWay;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = NETDEVSDK.NETDEV_LEN_32)]
        public string szIPv4SubnetMask;                          /* Gateway of IPv4 */
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 480)]
        public byte[] byRes;                                        /* Reserved */
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_UPNP_NAT_STATE_S
    {
        public Int32 dwSize;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = NETDEVSDK.NETDEV_LEN_16)]
        public NETDEV_UPNP_PORT_STATE_S[] astUpnpPort;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_UPNP_PORT_STATE_S
    {
        public NETDEV_PROTOCOL_TYPE_E eType;
        public Int32 bEnbale;
        public Int32 dwPort;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
        public byte[] byRes;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_SYSTEM_IPADDR_S
    {
        public Int32 eIPType;                            /* #NETDEV_HOSTTYPE_E  Protocol type, see enumeration #NETDEV_HOSTTYPE_E */
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = NETDEVSDK.NETDEV_LEN_132)]
        public string szIPAddr;           /* IP  IP address */
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_VIDEO_STREAM_INFO_S
    {
        public NETDEV_LIVE_STREAM_INDEX_E enStreamType;       /* Stream index */
        public Int32 bEnableFlag;        /* Enable or not */
        public Int32 dwHeight;           /* -Height  Video encoding resolution - Height */
        public Int32 dwWidth;            /* -Width  Video encoding resolution - Width */
        public Int32 dwFrameRate;        /* Video encoding configuration frame rate */
        public Int32 dwBitRate;          /* Bit rate */
        public NETDEV_VIDEO_CODE_TYPE_E enCodeType;         /* Video encoding format */
        public NETDEV_VIDEO_QUALITY_E enQuality;          /* Image quality */
        public Int32 dwGop;              /* I  I-frame interval */
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = NETDEVSDK.NETDEV_LEN_32)]
        public byte[] byRes;                            /* Reserved */
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_VIDEO_STREAM_INFO_LIST_S
    {
        public UInt32 udwNum;                                /* Number of video stream */
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = NETDEVSDK.NETDEV_LEN_16)]
        public NETDEV_VIDEO_STREAM_INFO_EX_S astVideoStreamInfoList;/* Video stream list*/
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_VIDEO_STREAM_INFO_EX_S
    {
        public string  bEnabled;                                                                  /* 视频流是否启用编码 Enable encoding for video stream or not*/
        public UInt32 udwStreamID;                                                             /* 码流索引，参见枚举NETDEV_LIVE_STREAM_INDEX_E。 Stream index. For enumeration, seeNETDEV_LIVE_STREAM_INDEX_E*/
        public UInt32 udwMainStreamType;                                                       /* 主码流类型，参见NETDEV_MAIN_STREAM_TYPE_E。 Main stream. See NETDEV_MAIN_STREAM_TYPE_E for reference */
        public NETDEV_VIDEO_ENCODE_INFO_S stVideoEncodeInfo;                                   /* 视频编码参数信息 Video encoding parameter*/
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_VIDEO_ENCODE_INFO_S
    {
        public string bEnableSVCMode;                        /* SVC配置,0：关闭,1：开启 SVC configuration. 0-Off, 1-On*/
        public UInt32 udwEncodeFormat;                     /* 视频编码格式信息，参见枚举NETDEV_VIDEO_CODE_TYPE_E。  Video Compression. For enumeration, seeNETDEV_VIDEO_CODE_TYPE_E*/
        public UInt32 udwWidth;                            /* 图像宽度 Image width*/
        public UInt32 udwHeight;                           /* 图像高度 Image height*/
        public UInt32 udwBitrate;                          /* 码率 Bit rate*/
        public UInt32 udwBitrateType;                      /* 码率类型，参见NETDEV_BIT_RATE_TYPE_E。 Bitrate type. See NETDEV_BIT_RATE_TYPE_E for reference */
        public UInt32 udwFrameRate;                        /* 帧率 Frame rate*/
        public UInt32 udwGopType;                          /* Gop模式,参见NETDEV_GOP_TYPE_E。 GOP mode. See NETDEV_GOP_TYPE_E for reference */
        public UInt32 udwIFrameInterval;                   /* I帧间隔，范围根据能力来定 I Frame Interval. The range depends on capability*/
        public UInt32 udwImageQuality;                     /* 图像质量，范围[1, 9]，9代表图像质量最高 Image quality, ranges from 1 to 9. 9 means the highest quality*/
        public UInt32 udwSmoothLevel;                      /* 码流平滑等级，范围[1,9]，1代表平滑级别最低 Smoothing level, ranges from 1 to 9. 1 means the lowest level*/
        public UInt32 udwSmartEncodeMode;                  /* 智能编码模式，参见NETDEV_SMART_ENCODE_MODE_E。 Smart encoding mode. See NETDEV_SMART_ENCODE_MODE_E for reference*/
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_VIDEO_MODE_INFO_S
    {
        public Int32 udwWidth;                                      /* 图像宽度 Image width*/
        public Int32 udwHeight;                                     /* 图像高度 Image height*/
        public Int32 udwFrameRate;                                  /* 图像帧率 Image frame rate*/
    }


    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_OSD_CONTENT_STYLE_S
    {
        public UInt32 udwFontStyle;                         /* 字体形式，参见枚举NETDEV_OSD_FONT_STYLE_E。  Font style. For enumeration, seeNETDEV_OSD_FONT_STYLE_E*/
        public UInt32 udwFontSize;                          /* 字体大小，参见枚举NETDEV_OSD_FONT_SIZE_E。  Font Size. For enumeration, seeNETDEV_OSD_FONT_SIZE_E*/
        public UInt32 udwColor;                             /* 颜色 Color*/
        public UInt32 udwDateFormat;                        /* 日期格式，参见枚举NETDEV_OSD_DATE_FORMAT_E。  Date Format. For enumeration, seeNETDEV_OSD_DATE_FORMAT_E */
        public UInt32 udwTimeFormat;                        /* 时间格式，参见枚举NETDEV_OSD_TIME_FORMAT_E。  Date Format. For enumeration, seeNETDEV_OSD_DATE_FORMAT_E */
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = NETDEVSDK.NETDEV_LEN_8)]
        public UInt32 audwFontAlignList;                   /* 区域内字体对齐，固定8个区域，IPC支持,参见枚举NETDEV_OSD_ALIGN_E。  Font align in area, 8 areasfixed, IPcamera supported. For enumeration, seeNETDEV_OSD_ALIGN_E */
        public UInt32 udwMargin;                            /* 边缘空的字符数，IPC支持，参见枚举NETDEV_OSD_MIN_MARGIN_E。  Number of character with margin, IP camera supported. For enumeration, seeNETDEV_OSD_MIN_MARGIN_E */

    }



    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_IMAGE_SETTING_S
    {
        public Int32 dwContrast;                   /* Contrast */
        public Int32 dwBrightness;                 /* Brightness */
        public Int32 dwSaturation;                 /* Saturation */
        public Int32 dwSharpness;                  /* Sharpness */
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 252)]
        public byte[] byRes;                            /* Reserved */
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_OSD_TEXT_OVERLAY_S
    {
        public Int32 bEnableFlag;                /** OSD, BOOL_TRUE,BOOL_FALSE * Enable OSD text overlay, BOOL_TRUE means enable and BOOL_FALSE means disable */
        public NETDEV_AREA_SCOPE_S     stAreaScope;                /** OSD * OSD text overlay area coordinates */
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = NETDEVSDK.NETDEV_OSD_TEXT_MAX_LEN)]
        public byte[]                    OSDText;    /** OSD * OSD text overlay name strings */
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
        public byte[] byRes;                            /* Reserved */
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_VIDEO_OSD_CFG_S
    {
        public NETDEV_OSD_TIME_S         stTimeOSD;        /* OSD  Information of channel time OSD */
        public NETDEV_OSD_TEXT_OVERLAY_S stNameOSD;        /* OSD  Information of channel name OSD */
        public Int16                     wTextNum;         /* OSD  Text OSD number */
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = NETDEVSDK.NETDEV_OSD_TEXTOVERLAY_NUM)]
        public NETDEV_OSD_TEXT_OVERLAY_S[] astTextOverlay;   /* OSD  Information of channel OSD text overlay */
    }



    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_ALARM_INPUT_LIST_S
    {
        public Int32 dwSize;                                           /* Number of input alarms */
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = NETDEVSDK.NETDEV_MAX_ALARM_IN_NUM)]
        public NETDEV_ALARM_INPUT_INFO_S[] astAlarmInputInfo;       /* Configuration information of input alarms */
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_ALARM_OUTPUT_INFO_S
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = NETDEVSDK.NETDEV_LEN_64)]
        public string szName;                                           /* Boolean name */
        public Int32 dwChancelId;                                       /* Channel number */
        public Int32 enDefaultStatus;                                   /* Default status of boolean output, see enumeration #NETDEV_BOOLEAN_MODE_E */
        public Int32 dwDurationSec;                                     /* Alarm duration (s) */
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_ALARM_INPUT_INFO_S
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = NETDEVSDK.NETDEV_LEN_64)]
        public string szName;                                                  /* Name of input alarm */
    }

    /**
 * @struct tagPrivacyMaskPara
 * @brief  Privacy mask configuration information
 * @attention
 */
    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_PRIVACY_MASK_CFG_S
    {
        public Int32 dwSize;                                     /* Mask area number */ 
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = NETDEVSDK.NETDEV_MAX_PRIVACY_MASK_AREA_NUM)]
        public NETDEV_PRIVACY_MASK_AREA_INFO_S[] astArea;  /* Mask area parameters */
    }

    /**
 * @struct tagAreaInfo
 * @brief  Definition of area configuration structure 
 * @attention
 */
    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_PRIVACY_MASK_AREA_INFO_S
    {
        public Int32 bIsEanbled;           /* Enable or not. */
        public Int32 dwTopLeftX;           /* X [0, 10000]  Upper left corner X [0, 10000]  */
        public Int32 dwTopLeftY;           /* Y [0, 10000]  Upper left corner Y [0, 10000]  */
        public Int32 dwBottomRightX;       /* X [0, 10000]  Lower right corner x [0, 10000] */
        public Int32 dwBottomRightY;       /* Y [0, 10000]  Lower right corner y [0, 10000] */
        public Int32 dwIndex;              /* Index. */
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_SCREENINFO_COLUMN_S
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = NETDEVSDK.NETDEV_SCREEN_INFO_COLUMN)]
        public Int16[] columnInfo;
    }
    /**
 * @struct tagNETDEVMotionAlarmInfo
 * @brief 
 * @attention  None
 */
    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_MOTION_ALARM_INFO_S
    {
        public Int32   dwSensitivity;                                                     /* Sensitivity */
        public Int32   dwObjectSize;                                                      /* Objection Size */
        public Int32   dwHistory;                                                         /* History */
        [MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.Struct, SizeConst = NETDEVSDK.NETDEV_SCREEN_INFO_ROW)]
        public NETDEV_SCREENINFO_COLUMN_S[] awScreenInfo;   /* Screen Info */
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
        public byte[] byRes;                            /* Reserved */
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_TAMPER_ALARM_INFO_S
    {
        public Int32 dwSensitivity;                               /* Sensitivity */
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
        public byte[] byRes;                                       /* Reserved */
    }


    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_DEVICE_BASICINFO_S
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = NETDEVSDK.NETDEV_LEN_64)]
        public string szDevModel;                     /* Device model */
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = NETDEVSDK.NETDEV_LEN_64)]
        public string szSerialNum;                    /* Hardware serial number */
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = NETDEVSDK.NETDEV_LEN_64)]
        public string szFirmwareVersion;              /* Software version */
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = NETDEVSDK.NETDEV_LEN_64)]
        public string szMacAddress;                   /* IPv4Mac  MAC address of IPv4 */
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = NETDEVSDK.NETDEV_LEN_64)]
        public string szDeviceName;                   /* Device name */
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 448)]
        public byte[] byRes;                                    /* Reserved */
    }

    public struct NETDEV_PASSENGER_FLOW_STATISTIC_DATA_S
    {
        public Int32 dwChannelID;                  /* Channel ID */
        public Int64 tReportTime;                  /* unix Report time */
        public Int32 tInterval;                    /* Interval time */
        public Int32 dwEnterNum;                   /* Enter num */
        public Int32 dwExitNum;                    /* Exit num */
        public Int32 dwTotalEnterNum;              /* Total enter num */
        public Int32 dwTotalExitNum;               /* Total exit num */
    }

    public struct NETDEV_TRAFFIC_STATISTICS_COND_S
    {
        public Int32 dwChannelID;            /* Channel ID */
        public Int32 dwStatisticsType;       /* # NETDEV_TRAFFIC_STATISTICS_TYPE_E Statistics type */
        public Int32 dwFormType;             /* # NETDEV_FORM_TYPE_E Form type */
        public Int64 tBeginTime;             /* Begin time */
        public Int64 tEndTime;               /* End time */
    }

    public struct NETDEV_TRAFFIC_STATISTICS_DATA_S
    {
        public Int32  dwSize;                                          /* */
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = NETDEVSDK.NETDEV_PEOPLE_CNT_MAX_NUM)]
        public Int32[]  adwEnterCount;        /* */
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = NETDEVSDK.NETDEV_PEOPLE_CNT_MAX_NUM)]
        public Int32[]  adwExitCount;         /* */
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_RECT_S
    {
        public Int32 dwLeft;                               /* X axis left point value [0,10000] */
        public Int32 dwTop;                                /* Y axis top point value [0,10000] */
        public Int32 dwRight;                              /* X axis right point value [0,10000] */
        public Int32 dwBottom;                             /* Y axis bottom point value [0,10000] */
    }
    /* define struct end */
    



    public enum NETDEV_CAMERA_TYPE_E
    {
        NETDEV_CAMERA_TYPE_FIX = 0,           
        NETDEV_CAMERA_TYPE_PTZ = 1,           

        NETDEV_CAMERA_TYPE_INVALID = 0xFF        
    }

    public enum NETDEV_RENDER_SCALE_E
    {
        NETDEV_RENDER_SCALE_FULL = 0,                
        NETDEV_RENDER_SCALE_PROPORTION = 1,          

        NETDEV_RENDER_SCALE_BUTT = 0xFF
    }

    public enum NETDEV_VIDEO_CODE_TYPE_E
    {
        NETDEV_VIDEO_CODE_MJPEG = 0,          /* MJPEG */
        NETDEV_VIDEO_CODE_H264 = 1,          /* H.264 */
        NETDEV_VIDEO_CODE_H265 = 2,          /* H.265 */
        NETDEV_VIDEO_CODE_INVALID
    };


    public enum NETDEV_HOSTTYPE_E
{
        NETDEV_NETWORK_HOSTTYPE_IPV4 = 0,               /* IPv4 */
        NETDEV_NETWORK_HOSTTYPE_IPV6 = 1,               /* IPv6 */
        NETDEV_NETWORK_HOSTTYPE_DNS  = 2                /* DNS */
};
    public enum NETDEV_RELAYOUTPUT_STATE_E
{
        NETDEV_BOOLEAN_STATUS_ACTIVE    = 0,            /* Triggered */
        NETDEV_BOOLEAN_STATUS_INACTIVE  = 1             /* Not triggered */
};

    public enum NETDEV_OSD_TIME_FORMAT_CAP_E
{
        NETDEV_OSD_TIME_FORMAT_CAP_HHMMSS = 0,          /* HH:mm:ss */
        NETDEV_OSD_TIME_FORMAT_CAP_HH_MM_SS_PM          /* hh:mm:ss tt */

};


  public enum NETDEV_TIME_ZONE_E
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
};
enum NETDEV_ALARM_TYPE_E
{
  /*********************************************************************** */
  /* Alarm                                                            */
  /*********************************************************************** */
  /* Recoverable alarms */
  NETDEV_ALARM_MOVE_DETECT = 1,            /* Motion detection alarm */
  NETDEV_ALARM_VIDEO_LOST = 2,            /* Video loss alarm */
  NETDEV_ALARM_VIDEO_TAMPER_DETECT = 3,            /* Tampering detection alarm */
  NETDEV_ALARM_INPUT_SWITCH = 4,            /* boolean input alarm */
  NETDEV_ALARM_TEMPERATURE_HIGH = 5,            /* High temperature alarm */
  NETDEV_ALARM_TEMPERATURE_LOW = 6,            /* Low temperature alarm */
  NETDEV_ALARM_AUDIO_DETECT = 7,            /* Audio detection alarm */
  NETDEV_ALARM_DISK_ABNORMAL = 8,            /* Disk abnormal*/
  NETDEV_ALARM_DISK_OFFLINE = 9,            /* Disk offline*/
  NETDEV_ALARM_DISK_ONLINE = 10,           /* 磁盘上线 Disk online */
  NETDEV_ALARM_DISK_STORAGE_WILL_FULL = 11,           /* 磁盘存储空间即将满 Disk StorageGoingfull */
  NETDEV_ALARM_DISK_STORAGE_IS_FULL = 12,           /* 存储空间满 StorageIsfull */
  NETDEV_ALARM_DISK_RAID_DISABLED = 13,           /* 阵列损坏 RAIDDisabled */
  NETDEV_ALARM_DISK_RAID_DEGRADED = 14,           /* 阵列衰退 RAIDDegraded */
  NETDEV_ALARM_DISK_RAID_RECOVERED = 15,           /* 阵列恢复正常 RAIDDegraded */

  /* Status report of NVR and access device 100~199 */
  NETDEV_ALARM_REPORT_DEV_ONLINE = 100,          /* Device online */
  NETDEV_ALARM_REPORT_DEV_OFFLINE = 101,          /* Device offline */
  NETDEV_ALARM_REPORT_DEV_VIDEO_LOSS = 102,          /* Video loss */
  NETDEV_ALARM_REPORT_DEV_VIDEO_LOSS_RECOVER = 103,          /* Video loss recover */
  NETDEV_ALARM_REPORT_DEV_REBOOT = 104,          /* Device restart */
  NETDEV_ALARM_REPORT_DEV_SERVICE_REBOOT = 105,          /* Service restart */
  NETDEV_ALARM_REPORT_DEV_DELETE_CHL = 106,          /* Delete channel */

  /* Live view exception report 200~299 */
  NETDEV_ALARM_NET_FAILED = 200,          /* Network error */
  NETDEV_ALARM_NET_TIMEOUT = 201,          /* Network timeout */
  NETDEV_ALARM_SHAKE_FAILED = 202,          /* Interaction error */
  NETDEV_ALARM_STREAMNUM_FULL = 203,          /* Stream full */
  NETDEV_ALARM_STREAM_THIRDSTOP = 204,          /* Third party stream stopped */
  NETDEV_ALARM_FILE_END = 205,          /* File ended */
  NETDEV_ALARM_RTMP_CONNECT_FAIL = 206,          /* RTMP connect fail */
  NETDEV_ALARM_RTMP_INIT_FAIL = 207,          /*RTMP init fail*/


  /* Valid alarms within 24 hours without arming schedule */
  NETDEV_ALARM_ALLTIME_FLAG_START = 400,          /* Start marker of alarm without arming schedule */
  NETDEV_ALARM_STOR_ERR = 401,          /* Storage error */
  NETDEV_ALARM_STOR_DISOBEY_PLAN = 402,          /* Not stored as planned */

  /* Unrecoverable alarms */
  NETDEV_ALARM_NO_RECOVER_FLAG_START = 500,          /* 无恢复类型告警开始标记  Start marker of unrecoverable alarm */
  NETDEV_ALARM_DISK_ERROR = 501,          /* 磁盘错误  Disk error */
  NETDEV_ALARM_ILLEGAL_ACCESS = 502,          /* 非法访问  Illegal access */
  NETDEV_ALARM_LINE_CROSS = 503,          /* 越界告警  Line cross */
  NETDEV_ALARM_OBJECTS_INSIDE = 504,          /* 区域入侵  Objects inside */
  NETDEV_ALARM_FACE_RECOGNIZE = 505,          /* 人脸识别  Face recognize */
  NETDEV_ALARM_IMAGE_BLURRY = 506,          /* 图像虚焦  Image blurry */
  NETDEV_ALARM_SCENE_CHANGE = 507,          /* 场景变更  Scene change */
  NETDEV_ALARM_SMART_TRACK = 508,          /* 智能跟踪  Smart track */
  NETDEV_ALARM_LOITERING_DETECTOR = 509,          /* 徘徊检测  Loitering Detector */
  NETDEV_ALARM_BANDWIDTH_CHANGE = 526,          /* 带宽变更  Bandwidth change */
  NETDEV_ALARM_ALLTIME_FLAG_END = 600,          /* 无布防告警结束标记  End marker of alarm without arming schedule */
  NETDEV_ALARM_MEDIA_CONFIG_CHANGE = 601,          /* 编码参数变更 media configurationchanged */
  NETDEV_ALARM_REMAIN_ARTICLE = 602,          /*物品遗留告警  Remain article*/
  NETDEV_ALARM_PEOPLE_GATHER = 603,          /* 人员聚集告警 People gather alarm*/
  NETDEV_ALARM_ENTER_AREA = 604,          /* 进入区域 Enter area*/
  NETDEV_ALARM_LEAVE_AREA = 605,          /* 离开区域 Leave area*/
  NETDEV_ALARM_ARTICLE_MOVE = 606,          /* 物品搬移 Article move*/


  /* Alarm recover */
  NETDEV_ALARM_RECOVER_BASE = 1000,         /* Alarm recover base */
  NETDEV_ALARM_MOVE_DETECT_RECOVER = 1001,         /* Motion detection alarm recover */
  NETDEV_ALARM_VIDEO_LOST_RECOVER = 1002,         /* Video loss alarm recover */
  NETDEV_ALARM_VIDEO_TAMPER_RECOVER = 1003,         /* Tampering detection alarm recover */
  NETDEV_ALARM_INPUT_SWITCH_RECOVER = 1004,         /* Boolean input alarm recover */
  NETDEV_ALARM_TEMPERATURE_RECOVER = 1005,         /* Temperature alarm recover */
  NETDEV_ALARM_AUDIO_DETECT_RECOVER = 1007,         /* Audio detection alarm recover */
  NETDEV_ALARM_DISK_ABNORMAL_RECOVER = 1008,         /* Disk abnormal recover */
  NETDEV_ALARM_DISK_OFFLINE_RECOVER = 1009,         /* Disk online recover */
  NETDEV_ALARM_DISK_ONLINE_RECOVER = 1010,         /* 磁盘上线恢复 Disk online recover */
  NETDEV_ALARM_DISK_STORAGE_WILL_FULL_RECOVER = 1011,         /* 磁盘存储空间即将满恢复 Disk StorageGoingfull recover */
  NETDEV_ALARM_DISK_STORAGE_IS_FULL_RECOVER = 1012,         /* 存储空间满恢复 StorageIsfull recover */
  NETDEV_ALARM_DISK_RAID_DISABLED_RECOVER = 1013,         /* 阵列损坏恢复 RAIDDisabled recover */
  NETDEV_ALARM_DISK_RAID_DEGRADED_RECOVER = 1014,         /* 阵列衰退恢复 RAIDDegraded recover */

  NETDEV_ALARM_STOR_ERR_RECOVER = 1201,         /* Storage error recover */
  NETDEV_ALARM_STOR_DISOBEY_PLAN_RECOVER = 1202,         /* Not stored as planned recover */
  NETDEV_ALARM_IMAGE_BLURRY_RECOVER = 1506,         /* 图像虚焦告警恢复  Image blurry recover */
  NETDEV_ALARM_SMART_TRACK_RECOVER = 1508,         /* 智能跟踪告警恢复  Smart track recover */

  NETDEV_ALARM_IP_CONFLICT = 1509,         /* IP冲突异常告警 IP conflict exception alarm*/
  NETDEV_ALARM_IP_CONFLICT_CLEARED = 1510,         /* IP冲突异常告警恢复IP conflict exception alarm recovery */

  /* Smart信息 */
  NETDEV_ALARM_SMART_READ_ERROR_RATE = 1511,        /* 底层数据读取错误率 Error reding the underlying data*/
  NETDEV_ALARM_SMART_SPIN_UP_TIME = 1512,        /*  主轴起旋时间 Rotation time of spindle */
  NETDEV_ALARM_SMART_START_STOP_COUNT = 1513,        /* 启停计数 Rev. Stop counting*/
  NETDEV_ALARM_SMART_REALLOCATED_SECTOR_COUNT = 1514,        /* 重映射扇区计数 Remap sector count */
  NETDEV_ALARM_SMART_SEEK_ERROR_RATE = 1515,        /* 寻道错误率 Trace error rate */
  NETDEV_ALARM_SMART_POWER_ON_HOURS = 1516,        /* 通电时间累计，出厂后通电的总时间，一般磁盘寿命三万小时 Power up time*/
  NETDEV_ALARM_SMART_SPIN_RETRY_COUNT = 1517,        /* 主轴起旋重试次数  */
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

  NETDEV_ALARM_INVALID = 0xFFFF        /* Invalid value */
};

    /**
 * @enum tagNETDEVCFGCmd
 * @brief   Parameter configuration command words Enumeration definition
 * @attention  None
 */
    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_PARSE_VIDEO_DATA_S
    {
        public byte pucData;             /* Pointer to video data */
        public Int32 dwDataLen;            /* Video data length */
        public Int32 dwVideoFrameType;     /* NETDEV_VIDEO_FRAME_TYPE_E  Frame type, see enumeration #NETDEV_VIDEO_FRAME_TYPE_E */
        public Int32 dwVideoCodeFormat;    /* #NETDEV_VIDEO_CODE_TYPE_E  Video encoding format, see enumeration #NETDEV_VIDEO_CODE_TYPE_E */
        public Int32 dwHeight;             /* Video image height */
        public Int32 dwWidth;              /* Video image width */
        public Int64 tTimeStamp;           /* Time stamp (ms) */
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
        public byte[] byRes;              /* Reserved field*/
    };

    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_FACE_POSITION_INFO_S
    {
        public Int32 dwTopLeftX;           /* 左上角X [0, 10000]  Upper left corner X [0, 10000]  */
        public Int32 dwTopLeftY;           /* 左上角Y [0, 10000]  Upper left corner Y [0, 10000]  */
        public Int32 dwBottomRightX;       /* 右下角X [0, 10000]  Lower right corner x [0, 10000] */
        public Int32 dwBottomRightY;       /* 右下角Y [0, 10000]  Lower right corner y [0, 10000] */
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public byte[] byRes;              /*   Reserved field*/
    };

    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_TMS_FACE_SNAPSHOT_PIC_INFO_S
    {
        public Int32 udwFaceId;                                         /* 人脸ID */
        public IntPtr pcPicBuff;                                        /* 图片缓存，Base64编码(使用完后需在SDK内部free) */
        public Int32 udwPicBuffLen;                                     /* 图片缓存长度 */
        public Int32 enImgType;                                         /* 图像类型，参考枚举NETDEV_TMS_PERSION_IMAGE_TYPE_E */
        public Int32 enImgFormat;                                       /* 图像格式，参考枚举NETDEV_TMS_PERSION_IMAGE_FORMAT_E */
        NETDEV_FACE_POSITION_INFO_S stFacePos;                          /* 人脸坐标---画面坐标归一化：0-10000 ;  矩形左上和右下点："138,315,282,684" */
        public Int32 udwImageWidth;                                     /* 图像宽度 */
        public Int32 udwImageHeight;                                    /* 图像高度 */
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = NETDEVSDK.NETDEV_TMS_CAMER_ID_LEN)]
        public char[] szCamerID;                                        /* 相机编号 */
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = NETDEVSDK.NETDEV_TMS_FACE_RECORD_ID_LEN)]
        public char[] szRecordID;                                       /* 记录ID号 */
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = NETDEVSDK.NETDEV_TMS_FACE_TOLLGATE_ID_LEN)]
        public char[] szTollgateID;                                     /* 卡口编号 */
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = NETDEVSDK.NETDEV_TMS_PASSTIME_LEN)]
        public char[] szPassTime;                                       /* 经过时刻,YYYYMMDDHHMMSSMMM，时间按24小时制。第一组MM表示月，第二组MM表示分，第三组MMM表示毫秒 */
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 96)]
        public byte[] byRes;                                            /*   Reserved field*/
    };

    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_PICTURE_DATA_S
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
        public IntPtr[] pucData;                /* pucData[0]: Y plane pointer, pucData[1]: U plane pointer, pucData[2]: V plane pointer */
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
        public Int32[] dwLineSize;              /* ulLineSize[0]: Y line spacing, ulLineSize[1]: U line spacing, ulLineSize[2]: V line spacing */
        public Int32 dwPicHeight;                /* Picture height */
        public Int32 dwPicWidth;                 /* Picture width */
        public Int32 dwRenderTimeType;           /* Time data type for rendering */
        public Int64 tRenderTime;                /* Time data for rendering */
    };

    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_CLOUD_DEV_INFO_S
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = NETDEVSDK.NETDEV_IPV4_LEN_MAX)]
        public char[] szIPAddr;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = NETDEVSDK.NETDEV_LEN_64)]
        public char[] szDevUserName;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = NETDEVSDK.NETDEV_LEN_64)]
        public char[] szDevName;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = NETDEVSDK.NETDEV_LEN_64)]
        public char[] szDevModel;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = NETDEVSDK.NETDEV_LEN_64)]
        public char[] szDevSerialNum;

        public Int32 dwOrgID;                                    /* Organization ID */
        public Int32 dwDevPort;
    }

    //[StructLayout(LayoutKind.Sequential)]
    //public struct NETDEV_VIDEO_STREAM_INFO_S
    //{
    //    public Int32 enStreamType;       /* NETDEV_LIVE_STREAM_INDEX_E*/
    //    public Int32 bEnableFlag;        
    //    public Int32 dwHeight;           /* -Height */
    //    public Int32 dwWidth;            /* -Width */
    //    public Int32 dwFrameRate;        
    //    public Int32 dwBitRate;          
    //    public Int32 enCodeType;         /* NETDEV_VIDEO_CODE_TYPE_E*/
    //    public Int32 enQuality;          /* UW_VIDEO_QUALITY_E*/
    //    public Int32 dwGop;              /* I */
    //    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
    //    public byte[] szReserve;
    //}

    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_PTZ_OPERATEAREA_S
    {
        public Int32 dwBeginPointX;                           /* X[0,10000]  Area start point X value [0,10000] */
        public Int32 dwBeginPointY;                           /* Y[0,10000]  Area start point Y value [0,10000] */
        public Int32 dwEndPointX;                             /* X[0,10000]  Area end point X value [0,10000] */
        public Int32 dwEndPointY;                             /* Y [0,10000]  Area end point Y value [0,10000] */
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_CRUISE_POINT_S
{
        public Int32 dwPresetID;                     /* ID  Preset ID */
        public Int32 dwStayTime;                     /* Stay time */
        public Int32 dwSpeed;                        /* Speed */
        public Int32 dwReserve;                      /* Reserved */
};

    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_CRUISE_LIST_S
    {
        public Int32 dwSize;                                         /* Number of patrol routes */
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = NETDEVSDK.NETDEV_MAX_CRUISEROUTE_NUM)]
        public NETDEV_CRUISE_INFO_S[] astCruiseInfo;      /* Information of patrol routes */
    };

//    [StructLayout(LayoutKind.Sequential)]
//    public struct NETDEV_IMAGE_SETTING_S
//{
//        public Int32 dwContrast;                   /* Contrast */
//        public Int32 dwBrightness;                 /* Brightness */
//        public Int32 dwSaturation;                 /* Saturation */
//        public Int32 dwSharpness;                  /* Sharpness */
//        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 252)]
//        public byte[]  byRes;                     /* Reserved */
//};


    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_SYSTEM_NTP_INFO_S
{
        public Int32 bSupportDHCP;                      /* DHCP  Support DHCP or not */
        public NETDEV_SYSTEM_IPADDR_S stAddr;          /* NTP   NTP information */
};
    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_SYSTEM_NTP_INFO_LIST_S
    {
        public Int64 ulNum;                      /*  NTP Server Number */
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = NETDEVSDK.NETDEV_LEN_64)]
        public NETDEV_SYSTEM_IPADDR_INFO_S[] astNTPServerInfoList;          /* NTP   NTP information */
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
        public byte[]                    byRes;                               /* Reserved */
    };
    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_SYSTEM_IPADDR_INFO_S
    {
        public string bEnabled;                      /*NTP Server enable 0:unable  1:enable */
        public Int64  ulAddressType;                 /*Address type  0:IPv4  1:IPv6(Temporary does not support)  2:domain name(NVR and AIO support)*/
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = NETDEVSDK.NETDEV_LEN_64)]
        public string szIPAddress;                   /* The IP address of the NTP server ,character length range [0,64]. When address type is 0,the node must be selected. */
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = NETDEVSDK.NETDEV_LEN_64)]
        public string szDomainName;                  /*The domain name of the NTP server ,character length range [0,64]. When address type is 2,the node must be selected.*/

        public Int64 ulPort;                         /*NTP Port ,the range of [1-65535]. IPC does not support this configuration. */
        public Int64 ulSynchronizeInterval;          /*Synchronize Interval: The support range of NVR and VMS is 5/10/15/30 minutes ,1/2/3/6/12 hours ,1 day ,and 1 week.The support range of IPC is 30-3600 seconds.
                                                     All of the above time periods need to be converted to a time value in seconds.*/
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
        public byte[]  byRes;                               /* Reserved */
    };

    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_ALARM_OUTPUT_LIST_S
{   
        public Int32 dwSize;                                                 /* Number of booleans  */
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = NETDEVSDK.NETDEV_MAX_ALARM_OUT_NUM)]
        public NETDEV_ALARM_OUTPUT_INFO_S[]  astAlarmOutputInfo;           /* Boolean configuration information */
};

    [StructLayout(LayoutKind.Sequential)]
    public  struct NETDEV_TRIGGER_ALARM_OUTPUT_S
{
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = NETDEVSDK.NETDEV_LEN_64)]
        public string szName;          /* Boolean name */
        public NETDEV_RELAYOUTPUT_STATE_E  enOutputState;                  /* ,#NETDEV_RELAYOUTPUT_STATE_E  Trigger status, see enumeration #NETDEV_RELAYOUTPUT_STATE_E */
};

    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_AREA_SCOPE_S
{
        public Int32  dwLocateX;             /** x[0,10000] * Coordinates of top point x [0,10000] */
        public Int32  dwLocateY;             /** y[0,10000] * Coordinates of top point y [0,10000] */
};

    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_OSD_TIME_S
{
        public Int32                    bEnableFlag;        /** OSD BOOL_TRUEBOOL_FALSE * Enable time OSD, BOOL_TRUE means enable and BOOL_FALSE means disable */
        public Int32                    bWeekEnableFlag;    /** () * Display week or not (reserved) */
        public NETDEV_AREA_SCOPE_S     stAreaScope;        /**  * Area coordinates */
        public UInt32                  udwTimeFormat;      /** OSDNETDEV_OSD_TIME_FORMAT_E * Time OSD format, see NETDEV_OSD_TIME_FORMAT_E */
        public UInt32                  udwDateFormat;      /** OSDNETDEV_OSD_DATE_FMT_E * Date OSD format, see NETDEV_OSD_TIME_FORMAT_E */

};

//    [StructLayout(LayoutKind.Sequential)]
//    public struct NETDEV_OSD_TEXT_OVERLAY_S
//{
//        public bool                    bEnableFlag;                /** OSD BOOL_TRUEBOOL_FALSE * Enable OSD text overlay, BOOL_TRUE means enable and BOOL_FALSE means disable */
//        public NETDEV_AREA_SCOPE_S     stAreaScope;                /** OSD * OSD text overlay area coordinates */
//        [MarshalAs(UnmanagedType.ByValArray, SizeConst = NETDEVSDK.NETDEV_OSD_TEXT_MAX_LEN)]
//        public char[]                    szOSDText;    /** OSD * OSD text overlay name strings */
//        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
//        public byte[]                    byRes;                               /* Reserved */
//};


//    [StructLayout(LayoutKind.Sequential)]
//    public struct NETDEV_PRIVACY_MASK_AREA_INFO_S
//{
//        public Int32   bIsEanbled;           /* Enable or not. */
//        public Int32   dwTopLeftX;           /* X [0, 10000]  Upper left corner X [0, 10000]  */
//        public Int32   dwTopLeftY;           /* Y [0, 10000]  Upper left corner Y [0, 10000]  */
//        public Int32   dwBottomRightX;       /* X [0, 10000]  Lower right corner x [0, 10000] */
//        public Int32   dwBottomRightY;       /* Y [0, 10000]  Lower right corner y [0, 10000] */
//        public Int32   dwIndex;              /* Index */
//};

    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_VIDEO_EFFECT_S
{
    public Int32 dwContrast;                   /* Contrast */
    public Int32 dwBrightness;                 /* Brightness */
    public Int32 dwSaturation;                 /* Saturation */
    public Int32 dwHue;                        /* Hue */
    public Int32 dwGamma;                      /* Gamma */
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
    public byte[] byRes;                    /* Reserved */
};

    [StructLayout(LayoutKind.Sequential)]
    public struct array
{
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = NETDEVSDK.NETDEV_SCREEN_INFO_COLUMN)]
    public Int16[] wTemp;
}

//    [StructLayout(LayoutKind.Sequential)]
//    public struct NETDEV_MOTION_ALARM_INFO_S
//{
//    public Int32  dwSensitivity;                                                     /* Sensitivity */
//    public Int32  dwObjectSize;                                                      /* Objection Size */
//    public Int32  dwHistory;                                                         /* History */
//    [MarshalAs(UnmanagedType.ByValArray, SizeConst = NETDEVSDK.NETDEV_SCREEN_INFO_ROW)]
//    public array[] awScreenInfo;                                                       /* Screen Info */
//    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
//    public byte[] byRes;                                                             /* Reserved */
//};


    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_TIME_S
{
    public Int32 dwYear;                       /* Year */
    public Int32 dwMonth;                      /* Month */
    public Int32 dwDay;                        /* Day */
    public Int32 dwHour;                       /* Hour */
    public Int32 dwMinute;                     /* Minute */
    public Int32 dwSecond;                     /* Second */
};

    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_TIME_CFG_S
{
    public NETDEV_TIME_ZONE_E dwTimeZone;                      /* see NETDEV_TIME_ZONE_E */
    public NETDEV_TIME_S stTime;                               /* Time */
    public Int32    bEnableDST;             /* 夏令时使能 DST enable */
    public NETDEV_TIME_DST_CFG_S   stTimeDSTCfg;           /* 夏令时配置 DST time config*/
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 220)]
    public byte[] byRes;                                       /* Reserved */
};
    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_TIME_DST_CFG_S
{
    public NETDEV_TIME_DST_S stBeginTime;        /* 夏令时开始时间 参见枚举#NETDEV_TIME_DST_S  DST begin time see enumeration NETDEV_TIME_DST_S */
    public NETDEV_TIME_DST_S stEndTime;          /* 夏令时结束时间 参见枚举#NETDEV_TIME_DST_S  DST end time see enumeration NETDEV_TIME_DST_S */
    public Int32 dwOffsetTime;       /* 夏令时节约时间 参见枚举# NETDEV_DST_OFFSET_TIME  DST saving time see enumeration NETDEV_DST_OFFSET_TIME */
};
    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_TIME_DST_S
{
    public Int32 dwMonth;              /* Month(1~12)*/
    public Int32 dwWeekInMonth;        /* 1 for the first week and 5 for the last week in the month */
    public Int32 dwDayInWeek;          /* 0 for Sunday and 6 for Saturday see enumeration NETDEV_DAY_IN_WEEK_E */
    public Int32 dwHour;               /* Hour */
};
    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_REV_TIMEOUT_S
{
    public Int32         dwRevTimeOut;                /* Set receive time out */
    public Int32         dwFileReportTimeOut;         /* Set file report time out*/
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
    public byte[] byRes;                              /* Reserved */
};

    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_DISK_INFO_S
{
    public Int32 dwDiskCabinetIndex;
    public Int32 dwSlotIndex;                                                      /* Slot Index */
    public Int32 dwTotalCapacity;                                                  /* Total Capacity*/
    public Int32 dwUsedCapacity;                                                   /* Used Capacity */
    public NETDEV_DISK_WORK_STATUS_E enStatus;                                                         /* Status */
    [MarshalAs(UnmanagedType.ByValTStr, SizeConst = NETDEVSDK.NETDEV_LEN_32)]
    public String szManufacturer;                                                 /* Manufacturer */
};

    [StructLayout(LayoutKind.Sequential)]
    public struct NETDEV_DISK_INFO_LIST_S
{
    public Int32 dwSize;                                  /*Disk number */
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = NETDEVSDK.NETDEV_DISK_MAX_NUM)]
    public NETDEV_DISK_INFO_S[] astDisksInfo;             /* Disk info*/
};


       public class NETDEVSDK
    {

        public  string dllLink = @"C:\Windows\System32\NetDEVSDK.dll";       /* 人脸ID缓存长度 */
        public const int NETDEV_TMS_FACE_ID_LEN = 16;       /* 人脸ID缓存长度 */
        public const int NETDEV_TMS_FACE_POSITION_LEN = 32;       /* 人脸位置字符串缓存长度 */
        public const int NETDEV_TMS_FACE_RECORD_ID_LEN = 32;       /* 记录ID缓存长度 */
        public const int NETDEV_TMS_CAMER_ID_LEN = 32;      /* 相机ID缓存长度 */
        public const int NETDEV_TMS_PASSTIME_LEN = 32;       /* 通过时间字符串缓存长度 */
        public const int NETDEV_TMS_FACE_TOLLGATE_ID_LEN = 32;       /* 卡口编号缓存长度 */

        /**********************************  Commonly used numerical macros *************** */

        /* Length of stream ID*/
        public const int NETDEV_STREAM_ID_LEN = 32;

        /* Length of filename */
        public const uint NETDEV_FILE_NAME_LEN = (256u);

        /* Maximum length of username */
        public const int NETDEV_USER_NAME_LEN = 32;

        /* Maximum length of password */
        public const int NETDEV_PASSWD_LEN = 64;

        /* Length of password and encrypted passcode for user login */
        public const int NETDEV_PASSWD_ENCRYPT_LEN = 64;

        /* Length of resource code string */
        public const int NETDEV_RES_CODE_LEN = 48;

        /* Maximum length of domain name */
        public const int NETDEV_DOMAIN_LEN = 64;

        /* Maximum length of device name */
        public const int NETDEV_DEVICE_NAME_LEN = 32;

        /* Maximum length of path */
        public const int NETDEV_PATH_LEN_WITHOUT_NAME = 64;

        /* Maximum length of path, including filename */
        public const int NETDEV_PATH_LEN = 128;

        /* Maximum length of email address */
        public const int NETDEV_EMAIL_NAME_ADDR = 32;

        /* Length of MAC address */
        public const int NETDEV_MAC_ADDR_LEN = 6;

        /* Length of endpoint called by gSOAP */
        public const int NETDEV_ENDPOINT_LEN = 96;

        /* Maximum length of session ID */
        public const int NETDEV_SESSION_ID_LEN = 16;

        /* Maximum length of URL */
        public const int NDE_MAX_URL_LEN = 512;

        /* Maximum number of alarm inputs */
        public const int  NETDEV_MAX_ALARM_IN_NUM = 64;

        /* Maximum number of alarm outputs */
        public const int NETDEV_MAX_ALARM_OUT_NUM = 64;

       /* Maximum number of people count */
       public  const int NETDEV_PEOPLE_CNT_MAX_NUM = 31;

        /* Common length */
        public const int NETDEV_LEN_4 = 4;
        public const int NETDEV_LEN_6 = 6;
        public const int NETDEV_LEN_8 = 8;
        public const int NETDEV_LEN_16 = 16;
        public const int NETDEV_LEN_32 = 32;
        public const int NETDEV_LEN_64 = 64;
        public const int NETDEV_LEN_128 = 128;
        public const int NETDEV_LEN_132 = 132;
        public const int NETDEV_LEN_256 = 256;
        public const int NETDEV_LEN_260 = 260;
        public const int NETDEV_LEN_1024 = 1024;
        /* Length of IP address string */
        public const uint NETDEV_IPADDR_STR_MAX_LEN = (64u);

        /* Length of IPV4 address string */
        public const int NETDEV_IPV4_LEN_MAX = 16;

        /* Length of IPV6 address string */
        public const int NETDEV_IPV6_LEN_MAX = 128;

        /* Length of common name string */
        public const uint NETDEV_NAME_MAX_LEN = (20u);

        /* Length of common code */
        public const uint NETDEV_CODE_STR_MAX_LEN = (48u);

        /* Maximum length of date string "2008-10-02 09:25:33.001 GMT" */
        public const uint NETDEV_MAX_DATE_STRING_LEN = (64u);

        /* Length of time string "hh:mm:ss" */
        public const uint NETDEV_SIMPLE_TIME_LEN = (12u);

        /* Length of date string "YYYY-MM-DD"*/
        public const uint NETDEV_SIMPLE_DATE_LEN = (12u);

        /* Number of scheduled time sections in a day */
        public const int NETDEV_PLAN_SECTION_NUM = 8;

        /* Total number of plans allowed in a week, including Monday to Sunday, and holidays */
        public const int NETDEV_PLAN_NUM_AWEEK = 8;

        /* Maximum number of motion detection areas allowed */
        public const int NETDEV_MAX_MOTION_DETECT_AREA_NUM = 4;

        /* Maximum number of privacy mask areas allowed */
        public const int NETDEV_MAX_PRIVACY_MASK_AREA_NUM = 8;

        /* Maximum number of tamper-proof areas allowed */
        public const int NETDEV_MAX_TAMPER_PROOF_AREA_NUM = 1;

        /* Maximum number of text overlays allowed for a channel */
        public const int NETDEV_MAX_TEXTOVERLAY_NUM = 6;

        /* Maximum number of video streams */
        public const int NETDEV_MAX_VIDEO_STREAM_NUM = 8;

        /* Month of the year */
        public const int NETDEV_MONTH_OF_YEAR = 12;

        /* Day of the month */
        public const int NETDEV_DAYS_OF_MONTH = 32;

        /* Length of device ID */
        public const int NETDEV_DEV_ID_LEN = 64;

        /* Length of device serial number */
        public const int NETDEV_SERIAL_NUMBER_LEN = 32;

        /* Maximum number of queries allowed at a time */
        public const int NETDEV_MAX_QUERY_NUM = 200;

        /* Total number of queries allowed */
        public const int NETDEV_MAX_QUERY_TOTAL_NUM = 2000;

        /* Maximum number of IP cameras */
        public const int NETDEV_MAX_IPC_NUM = 128;

        /* Maximum number of presets */
        public const int NETDEV_MAX_PRESET_NUM = 255;

        /* Maximum number of presets for preset patrol */
        public const int NETDEV_MAX_CRUISEPOINT_NUM = 32;

        /* Maximum number of routes for preset patrol */
        public const int NETDEV_MAX_CRUISEROUTE_NUM = 16;

        /* PTZ rotating speed */
        public const int NETDEV_MIN_PTZ_SPEED_LEVEL = 1;
        public const int NETDEV_MAX_PTZ_SPEED_LEVEL = 9;

        /* Maximum / Minimum values for image parameters (brightness, contrast, hue, saturation) */
        public const int NETDEV_MAX_VIDEO_EFFECT_VALUE = 255;
        public const int NETDEV_MIN_VIDEO_EFFECT_VALUE = 0;

        /* Minimum values for image parameters (Gama) */
        public const int NETDEV_MAX_VIDEO_EFFECT_GAMMA_VALUE = 10;

        /* Maximum connection timeout */
        public const int NETDEV_MAX_CONNECT_TIME_VALUE = 75000;

        /* Minimum connection timeout */
        public const int NETDEV_MIN_CONNECT_TIME_VALUE = 300;

        /* Maximum number of users */
        public const int NETDEV_MAX_USER_NUM = (256 + 32);

        /* Maximum number of channels allowed for live preview */
        public const int NETDEV_MAX_REALPLAY_NUM = 128;

        /* Maximum number of channels allowed for playback or download */
        public const int NETDEV_MAX_PALYBACK_NUM = 128;

        /* Maximum number of alarm channels */
        public const int NETDEV_MAX_ALARMCHAN_NUM = 128;

        /* Maximum number of channels allowed for formatting hard disk */
        public const int NETDEV_MAX_FORMAT_NUM = 128;

        /* Maximum number of channels allowed for file search */
        public const int NETDEV_MAX_FILE_SEARCH_NUM = 2000;

        /* Maximum number of channels allowed for log search */
        public const int NETDEV_MAX_LOG_SEARCH_NUM = 2000;

        /* Maximum number of channels allowed for creating transparent channels */
        public const int NETDEV_MAX_SERIAL_NUM = 2000;

        /* Maximum number of channels allowed for upgrade */
        public const int NETDEV_MAX_UPGRADE_NUM = 256;

        /* Maximum number of channels allowed for audio forwarding */
        public const int NETDEV_MAX_VOICE_COM_NUM = 256;

        /* Maximum number of channels allowed for audio broadcast */
        public const int NETDEV_MAX_VOICE_BROADCAST_NUM = 256;

        /* Maximum timeout, unit: ms */
        public const int NETDEV_MAX_CONNECT_TIME = 75000;

        /* Minimum timeout, unit: ms */
        public const int NETDEV_MIN_CONNECT_TIME = 300;

        /* Default timeout, unit: ms */
        public const int NETDEV_DEFAULT_CONNECT_TIME = 3000;

        /* Number of connection attempts */
        public const int NETDEV_CONNECT_TRY_TIMES = 1;

        /* User keep-alive interval */
        public const int NETDEV_KEEPLIVE_TRY_TIMES = 3;

        /* Number of OSD text overlays */
        public const int NETDEV_OSD_TEXTOVERLAY_NUM = 6;

        /* Length of OSD texts */
        public const int NETDEV_OSD_TEXT_MAX_LEN = (64 + 4);

        /* Maximum number of OSD type */
        public const int NETDEV_OSD_TYPE_MAX_NUM = 26;

        /* Maximum number of OSD time format type  */
        public const int NETDEV_OSD_TIME_FORMAT_MAX_NUM = 7;

        /* Maximum number of OSD date format type */
        public const int NETDEV_OSD_DATE_FORMAT_MAX_NUM = 15;

        /* Maximum number of alarms a user can get */
        public const int NETDEV_PULL_ALARM_MAX_NUM = 8;

        /* Maximum number of patrol routes allowed  */
        public const int NETDEV_TRACK_CRUISE_MAXNUM = 1;

        /* Minimum volume */
        public const int NETDEV_AUDIO_SOUND_MIN_VALUE = 0;

        /* Maximum volume */
        public const int NETDEV_AUDIO_SOUND_MAX_VALUE = 255;

        /* microphone Minimum volume */
        public const int NETDEV_MIC_SOUND_MIN_VALUE = 0;

        /* microphone Maximum volume */
        public const int NETDEV_MIC_SOUND_MAX_VALUE = 255;

        /* Screen Info Row */
        public const int NETDEV_SCREEN_INFO_ROW = 18;

        /* Screen Info Column */
        public const int NETDEV_SCREEN_INFO_COLUMN = 22;

        /* Length of IP */
        public const int NETDEV_IP_LEN = 64;


        /* Maximum length of URL */
        public const int NETDEV_BUFFER_MAX_LEN = 1024;

        /* Maximum number of channel */
        public const int NETDEV_CHANNEL_MAX = 512;

        /* Maximum number of days in a month */
        public const int NETDEV_MONTH_DAY_MAX = 31;

        /* Maximum number of resolution */
        public const int NETDEV_RESOLUTION_NUM_MAX = 32;

        /* Maximum number of encode type */
        public const int NETDEV_VIDEO_ENCODE_TYPE_MAX = 16;

        /* Length of wifi sniffer MAC  */
        public const int NETDEV_WIFISNIFFER_MAC_MAX_NUM = 64;

        /* Maximum number of wifi sniffer MAC array */
        public const int NETDEV_WIFISNIFFER_MAC_ARRY_MAX_NUM = 128;

        /* Maximum number of Disk */
        public const int NETDEV_DISK_MAX_NUM = 256;

        /* Maximum number of image quality level */
        public const int NETDEV_IMAGE_QUALITY_MAX_NUM = 9;

        /* Maximum number of bit rate mode */
        public const int NETDEV_BIT_RATE_TYPE_MAX_NUM = 2;

        /* Maximum number of video compression  */
        public const int NETDEV_ENCODE_FORMAT_MAX_NUM = 3;

        /*Maximum number of smart image encoding mode  */
        public const int NETDEV_SMART_ENCODE_MODEL_MAX_NUM = 3;

        /* Maximum number of GOP type */
        public const int NETDEV_GOP_TYPE_MAX_NUM = 4;

        public const int TRUE = 1;

        public const int FALSE = 0;
        public const int NETDEV_E_NONSUPPORT = 38;

        public static int m_bRouteRecording;
        public static int m_bTracking;

        /* error code start */

        public const int NETDEV_E_NO_RESULT = 41;          /* No result */
        public const int NETDEV_E_VIDEO_RESOLUTION_CHANGE = 1269;        /* Resolution changed */

        /* error code end */
  
        /*interface function start */

        [DllImport("msvcrt.dll", EntryPoint = "memcpy", CallingConvention = CallingConvention.Cdecl, SetLastError = false)]
        public static extern void MemCopy(byte[] dest, IntPtr src, int count);//字节数组到字节数组的拷贝

        [UnmanagedFunctionPointer(CallingConvention.StdCall, CharSet = CharSet.Ansi)]
        public delegate void NETDEV_FaceSnapshotCallBack_PF(IntPtr lpHandle, ref NETDEV_TMS_FACE_SNAPSHOT_PIC_INFO_S pstFaceSnapShotData, IntPtr lpUserParam);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_SetFaceSnapshotCallBack(IntPtr lpUserID, NETDEV_FaceSnapshotCallBack_PF cbFaceSnapshotCallBack, IntPtr lpUserData);

        [UnmanagedFunctionPointer(CallingConvention.StdCall, CharSet = CharSet.Ansi)]
        public delegate void NETDEV_AlarmMessCallBack_PF(IntPtr lpUserID, Int32 dwChannelID, NETDEV_ALARM_INFO_S stAlarmInfo, IntPtr lpBuf, Int32 dwBufLen, IntPtr lpUserData);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_SetAlarmCallBack(IntPtr lpUserID, NETDEV_AlarmMessCallBack_PF cbAlarmMessCallBack, IntPtr lpUserData);

        [UnmanagedFunctionPointer(CallingConvention.StdCall, CharSet = CharSet.Ansi)]
        public delegate void NETDEV_ExceptionCallBack_PF(IntPtr lpUserID, Int32 dwType, IntPtr lpExpHandle, IntPtr lpUserData);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_SetExceptionCallBack(NETDEV_ExceptionCallBack_PF cbExceptionCallBack, IntPtr lpUserData);

        [UnmanagedFunctionPointer(CallingConvention.StdCall, CharSet = CharSet.Ansi)]
        public delegate void NETDEV_DISCOVERY_CALLBACK_PF(IntPtr pstDevInfo,IntPtr lpUserData);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_SetDiscoveryCallBack(NETDEV_DISCOVERY_CALLBACK_PF cbDiscoveryCallBack, IntPtr lpUserData);

        [UnmanagedFunctionPointer(CallingConvention.StdCall, CharSet = CharSet.Ansi)]
        public delegate void NETDEV_PassengerFlowStatisticCallBack_PF(IntPtr lpUserID, IntPtr pstPassengerFlowData, IntPtr lpUserData);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_SetPassengerFlowStatisticCallBack(IntPtr lpUserID, NETDEV_PassengerFlowStatisticCallBack_PF cbPassengerFlowStatisticCallBack, IntPtr lpUserData);

      
        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_Init();

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_Cleanup();

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_QueryVideoChlDetailList(IntPtr lpUserID, ref int pdwChlCount, IntPtr pstVideoChlList);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern IntPtr NETDEV_LoginCloud(String pszCloudSrvUrl, String pszUserName, String pszPassWord);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern IntPtr NETDEV_LoginByDynamicEx(IntPtr lpUserID, ref NETDEV_CLOUD_DEV_LOGIN_S pCloudInfo, ref NETDEV_DEVICE_INFO_S pDevInfo);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern IntPtr NETDEV_FindCloudDevListEx(IntPtr lpUserID);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_FindNextCloudDevInfoEx(IntPtr lpFindHandle, ref NETDEV_CLOUD_DEV_INFO_EX_S pstDevInfo);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_FindCloseCloudDevListEx(IntPtr lpFindHandle);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_Discovery(String pszBeginIP, String pszEndIP);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern IntPtr NETDEV_RealPlay(IntPtr lpUserID, ref NETDEV_PREVIEWINFO_S pstPreviewInfo, IntPtr cbPlayDataCallBack, IntPtr lpUserData);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_StopRealPlay(IntPtr lpRealHandle);


        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_GetBitRate(IntPtr lpRealHandle, ref int pdwBitRate);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_GetFrameRate(IntPtr lpRealHandle, ref int pdwFrameRate);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_GetVideoEncodeFmt(IntPtr lpRealHandle, ref int pdwVideoEncFmt);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_GetResolution(IntPtr lpRealHandle, ref int pdwWidth, ref int pdwHeight);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_GetLostPacketRate(IntPtr lpRealHandle, ref int pulRecvPktNum, ref int pulLostPktNum);



        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_PTZControl(IntPtr lpPlayHandle, Int32 dwPTZCommand, Int32 dwSpeed);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_PTZControl_Other(IntPtr lpUserID, Int32 dwChannelID, Int32 dwPTZCommand, Int32 dwSpeed);


        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_CapturePicture(IntPtr lpRealHandle, byte[] szFileName, Int32 dwCaptureMode);



        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_SaveRealData(IntPtr lpRealHandle, byte[] szSaveFileName, Int32 dwFormat);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_StopSaveRealData(IntPtr lpRealHandle);


        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern IntPtr NETDEV_FindFile(IntPtr lpUserID, ref NETDEV_FILECOND_S pFindCond);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_FindNextFile(IntPtr lpFindHandle, ref NETDEV_FINDDATA_S lpFindData); /*NETDEV_FINDDATA_S*/

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_FindClose(IntPtr lpFindHandle);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_PlayBackControl(IntPtr lpPlayHandle, Int32 dwControlCode, ref Int64 pdwBuffer);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern IntPtr NETDEV_GetFileByTime(IntPtr lpUserID, ref NETDEV_PLAYBACKCOND_S pstPlayBackCond, byte[] pszSaveFileName, Int32 dwFormat);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_StopGetFile(IntPtr lpPlayHandle);


        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_PTZPreset_Other(IntPtr lpUserID, Int32 dwChannelID, Int32 dwPTZPresetCmd, String pszPresetName, Int32 dwPresetID);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_GetDevConfig(IntPtr lpUserID, Int32 dwChannelID, Int32 dwCommand, ref NETDEV_PTZ_ALLPRESETS_S lpOutBuffer, Int32 dwOutBufferSize, ref int pdwBytesReturned);
        
        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_SetUpnpNatState(IntPtr lpUserID, ref NETDEV_UPNP_NAT_STATE_S pstNatState);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_SetDevConfig(IntPtr lpUserID, Int32 dwChannelID, Int32 dwCommand, ref int index, int dwInBufferSize);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_SetDevConfig(IntPtr lpUserID, Int32 dwChannelID, Int32 dwCommand, ref NETDEV_MOTION_ALARM_INFO_S lpInBuffer, Int32 dwInBufferSize);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_GetDevConfig(IntPtr lpUserID, Int32 dwChannelID, Int32 dwCommand, ref NETDEV_MOTION_ALARM_INFO_S lpInBuffer, Int32 dwOutBufferSize, ref int pdwBytesReturned);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_GetDevConfig(IntPtr lpUserID, Int32 dwChannelID, Int32 dwCommand, ref NETDEV_TAMPER_ALARM_INFO_S lpOutBuffer, Int32 dwOutBufferSize, ref int pdwBytesReturned);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_SetDevConfig(IntPtr lpUserID, Int32 dwChannelID, Int32 dwCommand, ref NETDEV_TAMPER_ALARM_INFO_S lpInBuffer, Int32 dwInBufferSize);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_GetTrafficStatistic(IntPtr lpUserID, ref NETDEV_TRAFFIC_STATISTICS_COND_S pstStatisticCond, ref NETDEV_TRAFFIC_STATISTICS_DATA_S pstTrafficStatistic);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_SetConnectTime(Int32 dwWaitTime, Int32 dwTrytimes);
        
        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_SetPictureFluency(IntPtr lpPlayHandle,Int32 dwFluency);
        
        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_MakeKeyFrame(IntPtr lpUserID, Int32 dwChannelID, Int32 dwStreamType);
        
        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_GetSoundVolume(IntPtr lpPlayHandle, ref Int32 pdwVolume);   
        
        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_SoundVolumeControl(IntPtr lpPlayHandle, Int32 dwVolume);
        
        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_GetMicVolume(IntPtr lpPlayHandle, ref Int32 dwVolume);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_MicVolumeControl(IntPtr lpPlayHandle, Int32 dwVolume);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_OpenMic(IntPtr lpPlayHandle);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_CloseMic(IntPtr lpPlayHandle);
        /* interface function end */














        [UnmanagedFunctionPointer(CallingConvention.StdCall, CharSet = CharSet.Ansi)]
        public delegate void NETDEV_SOURCE_DATA_CALLBACK_PF(IntPtr lpRealHandle, ref byte pucBuffer, IntPtr dwBufSize, Int32 dwMediaDataType, IntPtr lpUserParam);

        [UnmanagedFunctionPointer(CallingConvention.StdCall, CharSet = CharSet.Ansi)]
        public delegate void NETDEV_DECODE_VIDEO_DATA_CALLBACK_PF(IntPtr lpRealHandle, ref NETDEV_PICTURE_DATA_S pstPictureData, IntPtr lpUserParam);

        [UnmanagedFunctionPointer(CallingConvention.StdCall, CharSet = CharSet.Ansi)]
        public delegate void NETDEV_DISPLAY_CALLBACK_PF(IntPtr lpRealHandle, IntPtr hdc, IntPtr lpUserParam);

        [UnmanagedFunctionPointer(CallingConvention.StdCall, CharSet = CharSet.Ansi)]
        public delegate void NETDEV_PARSE_VIDEO_DATA_CALLBACK_PF(IntPtr lpRealHandle, ref NETDEV_PARSE_VIDEO_DATA_S pstParseVideoData, IntPtr lpUserParam);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_GetSDKVersion();

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern IntPtr NETDEV_Login(String szDevIP, Int16 wDevPort, String szUserName, String szPassword, ref NETDEV_DEVICE_INFO_S pstDevInfo);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_Logout(IntPtr lpUserID);

        [DllImport("kernel32.dll", CharSet = CharSet.Auto)]
        public static extern void OutputDebugString(string message);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_PlaySound(IntPtr lpRealHandle);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_StopPlaySound(IntPtr lpRealHandle);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_ResetLostPacketRate(IntPtr lpRealHandle);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_CaptureNoPreview(IntPtr lpUserID, Int32 dwChannelID, Int32 dwStreamType, String szFileName, Int32 dwCaptureMode);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_SetRenderScale(IntPtr lpRealHandle, Int32 enRenderScale); /*NETDEV_RENDER_SCALE_E*/

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern IntPtr NETDEV_PlayBackByName(IntPtr lpUserID, ref NETDEV_PLAYBACKINFO_S pstPlayBackInfo);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern IntPtr NETDEV_PlayBackByTime(IntPtr lpUserID, ref NETDEV_PLAYBACKCOND_S pstPlayBackInfo);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_StopPlayBack(IntPtr lpPlayHandle);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern IntPtr NETDEV_GetFileByName(IntPtr lpUserID, ref NETDEV_PLAYBACKINFO_S pstPlayBackInfo, String szSaveFileName, Int32 dwFormat);


        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_PTZPreset(IntPtr lpPlayHandle, Int32 dwPTZPresetCmd, String pszPresetName, Int32 dwPresetID);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_SetDevConfig(IntPtr lpUserID, Int32 dwChannelID, Int32 dwCommand, IntPtr lpInBuffer, ref int dwInBufferSize);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_Reboot(IntPtr lpUserID);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_OpenSound(IntPtr lpRealHandle);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_CloseSound(IntPtr lpRealHandle);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_GetLastError();

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_PTZSelZoomIn_Other(IntPtr lpUserID, Int32 dwChannelID, ref NETDEV_PTZ_OPERATEAREA_S pstPtzOperateArea);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_PTZGetCruise(IntPtr lpUserID, Int32 dwChannelID, ref NETDEV_CRUISE_LIST_S pstCruiseList);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_PTZCruise_Other(IntPtr lpUserID, Int32 dwChannelID, Int32 dwPTZCruiseCmd, ref NETDEV_CRUISE_INFO_S pstCruiseInfo);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_PTZGetTrackCruise(IntPtr lpUserID, Int32 dwChannelID, ref NETDEV_PTZ_TRACK_INFO_S pstTrackCruiseInfo);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_PTZTrackCruise(IntPtr lpUserID, Int32 dwChannelID, Int32 dwPTZTrackCruiseCmd, string pszTrackCruiseName);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_SetDevConfig(IntPtr lpUserID, Int32 dwChannelID, Int32 dwCommand, ref NETDEV_VIDEO_STREAM_INFO_S lpInBuffer, Int32 dwInBufferSize);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_GetDevConfig(IntPtr lpUserID, Int32 dwChannelID, Int32 dwCommand, ref NETDEV_VIDEO_STREAM_INFO_S lpInBuffer, Int32 dwOutBufferSize, ref int pdwBytesReturned);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_SetDevConfig(IntPtr lpUserID, Int32 dwChannelID, Int32 dwCommand, ref NETDEV_IMAGE_SETTING_S lpInBuffer, Int32 dwInBufferSize);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_GetDevConfig(IntPtr lpUserID, Int32 dwChannelID, Int32 dwCommand, ref NETDEV_IMAGE_SETTING_S lpInBuffer, Int32 dwOutBufferSize, ref int pdwBytesReturned);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_SetDevConfig(IntPtr lpUserID, Int32 dwChannelID, Int32 dwCommand, ref NETDEV_SYSTEM_NTP_INFO_S lpInBuffer, Int32 dwInBufferSize);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_GetDevConfig(IntPtr lpUserID, Int32 dwChannelID, Int32 dwCommand, ref NETDEV_SYSTEM_NTP_INFO_S lpInBuffer, Int32 dwOutBufferSize, ref int pdwBytesReturned);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_SetDevConfig(IntPtr lpUserID, Int32 dwChannelID, Int32 dwCommand, ref NETDEV_NETWORKCFG_S lpInBuffer, Int32 dwInBufferSize);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_GetDevConfig(IntPtr lpUserID, Int32 dwChannelID, Int32 dwCommand, ref NETDEV_NETWORKCFG_S lpInBuffer, Int32 dwOutBufferSize, ref int pdwBytesReturned);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_SetDevConfig(IntPtr lpUserID, Int32 dwChannelID, Int32 dwCommand, ref NETDEV_ALARM_OUTPUT_INFO_S lpInBuffer, Int32 dwInBufferSize);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_GetDevConfig(IntPtr lpUserID, Int32 dwChannelID, Int32 dwCommand, ref NETDEV_ALARM_OUTPUT_INFO_S lpInBuffer, Int32 dwOutBufferSize, ref int pdwBytesReturned);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_SetDevConfig(IntPtr lpUserID, Int32 dwChannelID, Int32 dwCommand, ref NETDEV_TRIGGER_ALARM_OUTPUT_S lpInBuffer, Int32 dwInBufferSize);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_GetDevConfig(IntPtr lpUserID, Int32 dwChannelID, Int32 dwCommand, ref NETDEV_TRIGGER_ALARM_OUTPUT_S lpInBuffer, Int32 dwOutBufferSize, ref int pdwBytesReturned);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_SetDevConfig(IntPtr lpUserID, Int32 dwChannelID, Int32 dwCommand, ref NETDEV_VIDEO_OSD_CFG_S lpInBuffer, Int32 dwInBufferSize);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_GetDevConfig(IntPtr lpUserID, Int32 dwChannelID, Int32 dwCommand, ref NETDEV_VIDEO_OSD_CFG_S lpInBuffer, Int32 dwOutBufferSize, ref int pdwBytesReturned);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_GetDevConfig(IntPtr lpUserID, Int32 dwChannelID, Int32 dwCommand, ref NETDEV_ALARM_INPUT_LIST_S lpInBuffer, Int32 dwOutBufferSize, ref int pdwBytesReturned);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_GetDevConfig(IntPtr lpUserID, Int32 dwChannelID, Int32 dwCommand, ref NETDEV_ALARM_OUTPUT_LIST_S lpInBuffer, Int32 dwOutBufferSize, ref int pdwBytesReturned);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_GetDevConfig(IntPtr lpUserID, Int32 dwChannelID, Int32 dwCommand, ref NETDEV_DEVICE_BASICINFO_S lpInBuffer, Int32 dwOutBufferSize, ref int pdwBytesReturned);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_GetDevConfig(IntPtr lpUserID, Int32 dwChannelID, Int32 dwCommand, ref NETDEV_DISK_INFO_LIST_S lpInBuffer, Int32 dwOutBufferSize, ref int pdwBytesReturned);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_GetDevConfig(IntPtr lpUserID, Int32 dwChannelID, Int32 dwCommand, ref NETDEV_PRIVACY_MASK_CFG_S lpInBuffer, Int32 dwOutBufferSize, ref int pdwBytesReturned);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_SetDevConfig(IntPtr lpUserID, Int32 dwChannelID, Int32 dwCommand, ref NETDEV_PRIVACY_MASK_CFG_S lpInBuffer, Int32 dwInBufferSize);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_RestoreConfig(IntPtr lpUserID);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_GetVideoEffect(IntPtr lpRealHandle, ref NETDEV_VIDEO_EFFECT_S pstImageInfo);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_SetVideoEffect(IntPtr lpRealHandle, ref NETDEV_VIDEO_EFFECT_S pstImageInfo);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_SetDigitalZoom(IntPtr lpRealHandle, IntPtr hWnd, IntPtr pstRect);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_GetUpnpNatState(IntPtr lpUserID, ref NETDEV_UPNP_NAT_STATE_S pstNatState);


        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_ModifyDeviceName(IntPtr lpUserID, String strDeviceName);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_SetLogPath(String strLogPath);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_GetSystemTimeCfg(IntPtr lpUserID, ref NETDEV_TIME_CFG_S pstSystemTimeInfo);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_SetSystemTimeCfg(IntPtr lpUserID, ref NETDEV_TIME_CFG_S pstSystemTimeInfo);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_SetRevTimeOut(ref NETDEV_REV_TIMEOUT_S pstRevTimeout);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_SetPlayDecodeVideoCB(IntPtr lpRealHandle, IntPtr cbPlayDecodeVideoCallBack, Int32 bContinue, IntPtr lpUserData);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_SetPlayDataCallBack(IntPtr lpRealHandle, IntPtr cbPlayDataCallBack, Int32 bContinue, IntPtr lpUserData);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_SetPlayDisplayCB(IntPtr lpRealHandle, IntPtr cbPlayDisplayCallBack, IntPtr lpUserData);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_SetPlayParseCB(IntPtr lpRealHandle, IntPtr cbPlayParseCallBack, Int32 bContinue, IntPtr lpUserData);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern IntPtr NETDEV_StartVoiceCom(IntPtr lpUserID, Int32 dwChannelID, IntPtr cbPlayDataCallBack, IntPtr lpUserData);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_StopVoiceCom(IntPtr lpVoiceComHandle);
        
        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_GetCloudDevInfoByName(IntPtr lpUserID, String pszRegisterCode, ref NETDEV_CLOUD_DEV_INFO_S pstDevInfo);

        [DllImport(DllConfig.dllLink, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 NETDEV_GetCloudDevInfoByRegCode(IntPtr lpUserID, String pszRegisterName, ref NETDEV_CLOUD_DEV_INFO_S pstDevInfo);
    }
}
