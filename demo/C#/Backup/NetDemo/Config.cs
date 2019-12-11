using GeneralDef;
using System;
using System.Collections.Generic;
using NETSDKHelper;
using System.Runtime.InteropServices;

namespace NetDemo
{
    public class Config
    {
        private const int MAXMOTIONOBJECTSIZE = 100;
        public enum CONFIG_TYPE_E
        {
            CONFIG_BASIC_TYPE = 0,
            CONFIG_NETWORK_TYPE = 1,
            CONFIG_VIDEO_TYPE = 2,
            CONFIG_IMAGE_TYPE = 3,
            CONFIG_OSD_TYPE = 4,
            CONFIG_IO_TYPE = 5,
            CONFIG_PRIVACY_MASK_TYPE = 6,
            CONFIG_MOTION_TYPE = 7,
            CONFIG_TEMPER_TYPE = 8
        }

        private NetDemo m_oNetDemo;
        private int m_curCfgTabIndex = 0;
        private List<DeviceInfo> m_deviceInfoList = null;

        public Config(NetDemo oNetDemo)
        {
            m_oNetDemo = oNetDemo;
            m_deviceInfoList = oNetDemo.getDeviceInfoList();
        }

        //config tab
        public void cfgTabSwitch(int index)
        {
            m_curCfgTabIndex = index;
            switch (index)
            {
                case (int)CONFIG_TYPE_E.CONFIG_BASIC_TYPE:
                    getBasicInfo();
                    break;
                case (int)CONFIG_TYPE_E.CONFIG_NETWORK_TYPE:
                    getNetworkInfo();
                    break;
                case (int)CONFIG_TYPE_E.CONFIG_VIDEO_TYPE:
                    getVideoInfo();
                    break;
                case (int)CONFIG_TYPE_E.CONFIG_IMAGE_TYPE:
                    getIamgeInfo();
                    break;
                case (int)CONFIG_TYPE_E.CONFIG_OSD_TYPE:
                    getOSDInfo();
                    break;
                case (int)CONFIG_TYPE_E.CONFIG_IO_TYPE:
                    getIOInfo();
                    break;
                case (int)CONFIG_TYPE_E.CONFIG_PRIVACY_MASK_TYPE:
                    getPrivacyMaskInfo();
                    break;
                case (int)CONFIG_TYPE_E.CONFIG_MOTION_TYPE:
                    getMotionInfo();
                    break;
                case (int)CONFIG_TYPE_E.CONFIG_TEMPER_TYPE:
                    getTemperInfo();
                    break;
                default:
                    break;

            }
        }

        /*************************** Basic Cfg start *****************************/
        /*获取基本配置信息*/
        private void getBasicInfo()
        {
            if (m_oNetDemo.m_curSelectedTreeChannelIndex < 0)
            {
                //m_netDemo.m_curSelectedTreeChannelIndex = 0;

                return;
            }

            if (m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_basicInfo.existFlag == false)
            {
                refreshBasicInfo();
            }
            else
            {
                readBasicInfo();
            }
        }

        public void refreshBasicInfo()
        {
            /* Get Device System time */
            NETDEV_TIME_CFG_S stTimeCfg = new NETDEV_TIME_CFG_S();
            int iRet = NETDEVSDK.NETDEV_GetSystemTimeCfg(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_lpDevHandle, ref stTimeCfg);
            if (NETDEVSDK.TRUE != iRet)
            {
                m_oNetDemo.showFailLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Get device system time", NETDEVSDK.NETDEV_GetLastError());
                return;
            }
            else
            {
                m_oNetDemo.showSuccessLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Get device system time");
                m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_basicInfo.stSystemTime = stTimeCfg;
            }

            m_oNetDemo.showSystemTime(stTimeCfg);

            /* Get Device name */
            NETDEV_DEVICE_BASICINFO_S stDeviceInfo = new NETDEV_DEVICE_BASICINFO_S();
            Int32 dwBytesReturned = 0;
            iRet = NETDEVSDK.NETDEV_GetDevConfig(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_lpDevHandle, m_oNetDemo.m_curSelectedTreeChannelIndex + 1, (int)NETDEV_CONFIG_COMMAND_E.NETDEV_GET_DEVICECFG, ref stDeviceInfo, Marshal.SizeOf(stDeviceInfo), ref dwBytesReturned);
            if (NETDEVSDK.TRUE != iRet)
            {
                m_oNetDemo.showFailLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Get device name", NETDEVSDK.NETDEV_GetLastError());
                return;
            }

            m_oNetDemo.showSuccessLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Get device name");

            m_oNetDemo.showDeviceName(stDeviceInfo.szDeviceName);
            m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_basicInfo.szDeviceName = stDeviceInfo.szDeviceName;
            
            /* Get disk info */
            NETDEV_DISK_INFO_LIST_S stDiskInfoList = new NETDEV_DISK_INFO_LIST_S();
            iRet = NETDEVSDK.NETDEV_GetDevConfig(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_lpDevHandle, m_oNetDemo.m_curSelectedTreeChannelIndex + 1, (int)NETDEV_CONFIG_COMMAND_E.NETDEV_GET_DISKSINFO, ref stDiskInfoList, Marshal.SizeOf(stDiskInfoList), ref dwBytesReturned);
            if (NETDEVSDK.TRUE != iRet)
            {
                m_oNetDemo.showFailLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Get disk info", NETDEVSDK.NETDEV_GetLastError());
                return;
            }

            m_oNetDemo.showSuccessLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Get disk info");

            m_oNetDemo.showDiskInfoList(stDiskInfoList);
            m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_basicInfo.stDiskInfoList = stDiskInfoList;

            m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_basicInfo.existFlag = true;
        }

        private void readBasicInfo()
        {
            m_oNetDemo.showSystemTime(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_basicInfo.stSystemTime);
            m_oNetDemo.showDeviceName(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_basicInfo.szDeviceName);
            m_oNetDemo.showDiskInfoList(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_basicInfo.stDiskInfoList);
        }

        public void saveStstemTime(int timeZone,string Date, String time)
        {
            /* Save system time */
            NETDEV_TIME_CFG_S stTimeCfg = new NETDEV_TIME_CFG_S();
            stTimeCfg.stTime.dwYear = Convert.ToInt32(Date.Split('/')[0]);
            stTimeCfg.stTime.dwMonth = Convert.ToInt32(Date.Split('/')[1]);
            stTimeCfg.stTime.dwDay = Convert.ToInt32(Date.Split('/')[2]);

            stTimeCfg.stTime.dwHour = Convert.ToInt32(time.Split(':')[0]);
            stTimeCfg.stTime.dwMinute = Convert.ToInt32(time.Split(':')[1]);
            stTimeCfg.stTime.dwSecond = Convert.ToInt32(time.Split(':')[2]);

            stTimeCfg.dwTimeZone = (NETDEV_TIME_ZONE_E)timeZone;

            int iRet = NETDEVSDK.NETDEV_SetSystemTimeCfg(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_lpDevHandle, ref stTimeCfg);
            if(NETDEVSDK.TRUE != iRet)
            {
                m_oNetDemo.showFailLogInfo(m_oNetDemo.getDeviceInfoList()[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Save device system time", NETDEVSDK.NETDEV_GetLastError());
                return;
            }
            m_oNetDemo.showSuccessLogInfo(m_oNetDemo.getDeviceInfoList()[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Save device system time");

            m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_basicInfo.stSystemTime = stTimeCfg;
        }

        public void saveDeviceName(String deviceName)
        {
            int iRet = NETDEVSDK.NETDEV_ModifyDeviceName(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_lpDevHandle, deviceName);
            if (NETDEVSDK.TRUE != iRet)
            {
                m_oNetDemo.showFailLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Save device name", NETDEVSDK.NETDEV_GetLastError());
                return;
            }
            m_oNetDemo.showSuccessLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Save device name");
            m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_basicInfo.szDeviceName = deviceName;
        }

        /*************************** Basic Cfg end *****************************/
        

        /*************************** Network Cfg start *****************************/
        private void getNetworkInfo()
        {
            if (m_oNetDemo.m_curSelectedTreeChannelIndex < 0)
            {
                //m_netDemo.m_curSelectedTreeChannelIndex = 0;

                return;
            }

            if (m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_networkInfo.existFlag == false)
            {
                refreshNetworkInfo();
            }
            else
            {
                readNetworkInfo();
            }
        }

        public void refreshNetworkInfo()
        {
            /* Get Network Config */
            NETDEV_NETWORKCFG_S stNetworkcfg = new NETDEV_NETWORKCFG_S();

            Int32 dwBytesReturned = 0;
            int iRet = NETDEVSDK.NETDEV_GetDevConfig(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_lpDevHandle, m_oNetDemo.m_curSelectedTreeChannelIndex + 1, (int)NETDEV_CONFIG_COMMAND_E.NETDEV_GET_NETWORKCFG, ref stNetworkcfg, Marshal.SizeOf(stNetworkcfg), ref dwBytesReturned);
            if (NETDEVSDK.TRUE != iRet)
            {
                m_oNetDemo.showFailLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Get network cfg", NETDEVSDK.NETDEV_GetLastError());
                return;
            }
            m_oNetDemo.showSuccessLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Get network cfg");

            m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_networkInfo.stNetWorkIP = stNetworkcfg;
            m_oNetDemo.showBaseNetworkInfo(stNetworkcfg);

            /* Get protocal port */
            NETDEV_UPNP_NAT_STATE_S stNatState = new NETDEV_UPNP_NAT_STATE_S();

            iRet = NETDEVSDK.NETDEV_GetUpnpNatState(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_lpDevHandle, ref stNatState);
            if (NETDEVSDK.TRUE != iRet)
            {
                m_oNetDemo.showFailLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Get upnp nat state", NETDEVSDK.NETDEV_GetLastError());
                return;
            }
            m_oNetDemo.showSuccessLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Get upnp nat state");

            m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_networkInfo.stNetWorkPort = stNatState;
            m_oNetDemo.showPortNetworkInfo(stNatState);

            /* Get NTP config */
            NETDEV_SYSTEM_NTP_INFO_S stNTPInfo = new NETDEV_SYSTEM_NTP_INFO_S();

            /* Failed to return Get information when NTP is not enabled for the NVR. Please perform Set operation first. */
            iRet = NETDEVSDK.NETDEV_GetDevConfig(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_lpDevHandle, m_oNetDemo.m_curSelectedTreeChannelIndex + 1, (int)NETDEV_CONFIG_COMMAND_E.NETDEV_GET_NTPCFG, ref stNTPInfo, Marshal.SizeOf(stNTPInfo), ref dwBytesReturned);
            if (NETDEVSDK.TRUE != iRet)
            {
                m_oNetDemo.showFailLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Get NTP cfg", NETDEVSDK.NETDEV_GetLastError());
                return;
            }
            m_oNetDemo.showSuccessLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Get NTP cfg");

            m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_networkInfo.stNetWorkNTP = stNTPInfo;
            m_oNetDemo.showNTPNetworkInfo(stNTPInfo);

            m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_networkInfo.existFlag = true;
        }

        private void readNetworkInfo()
        {
            m_oNetDemo.showBaseNetworkInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_networkInfo.stNetWorkIP);
            m_oNetDemo.showPortNetworkInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_networkInfo.stNetWorkPort);
            m_oNetDemo.showNTPNetworkInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_networkInfo.stNetWorkNTP);
        }

        public void saveBaseNetworkInfo(NETDEV_NETWORKCFG_S stNetworkSetcfg)
        {
            int iRet = NETDEVSDK.NETDEV_SetDevConfig(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_lpDevHandle, m_oNetDemo.m_curSelectedTreeChannelIndex + 1, (int)NETDEV_CONFIG_COMMAND_E.NETDEV_SET_NETWORKCFG, ref stNetworkSetcfg, Marshal.SizeOf(stNetworkSetcfg));
            if (NETDEVSDK.TRUE != iRet)
            {
                m_oNetDemo.showFailLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Save network cfg", NETDEVSDK.NETDEV_GetLastError());
                return;
            }
            m_oNetDemo.showSuccessLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Save network cfg");

            m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_networkInfo.stNetWorkIP = stNetworkSetcfg;
        }

        public void savePortNetworkInfo(NETDEV_UPNP_NAT_STATE_S stNatState)
        {
            int iRet = NETDEVSDK.NETDEV_SetUpnpNatState(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_lpDevHandle, ref stNatState);
            if (NETDEVSDK.TRUE != iRet)
            {
                m_oNetDemo.showFailLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Save upnp nat state", NETDEVSDK.NETDEV_GetLastError());
                return;
            }
            m_oNetDemo.showSuccessLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Save upnp nat state");

            m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_networkInfo.stNetWorkPort = stNatState;
        }

        public void saveNTPNetworkInfo(NETDEV_SYSTEM_NTP_INFO_S stNTPInfo)
        {
            int iRet = NETDEVSDK.NETDEV_SetDevConfig(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_lpDevHandle, m_oNetDemo.m_curSelectedTreeChannelIndex + 1, (int)NETDEV_CONFIG_COMMAND_E.NETDEV_SET_NTPCFG, ref stNTPInfo, Marshal.SizeOf(stNTPInfo));
            if (NETDEVSDK.TRUE != iRet)
            {
                m_oNetDemo.showFailLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Set NTP cfg", NETDEVSDK.NETDEV_GetLastError());
                return;
            }
            m_oNetDemo.showSuccessLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Set NTP cfg");

            m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_networkInfo.stNetWorkNTP = stNTPInfo;
        }

        /*************************** Network Cfg end *****************************/


        /*************************** video Cfg start *****************************/
        private void getVideoInfo()
        {
            if (m_oNetDemo.m_curSelectedTreeChannelIndex < 0)
            {
                //m_netDemo.m_curSelectedTreeChannelIndex = 0;

                return;
            }

            if (m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_videoStreamInfo.existFlag == false)
            {
                refreshVideoInfo();
            }
            else
            {
                readVideoInfo();
            }
        }

        public void refreshVideoInfo()
        {
            /* Get video stream info */
            Int32 dwBytesReturned = 0;

            for (Int32 i = 0; i < 3; i++)
            {
                NETDEV_VIDEO_STREAM_INFO_S stStreamInfo = new NETDEV_VIDEO_STREAM_INFO_S();
                stStreamInfo.enStreamType = (NETDEV_LIVE_STREAM_INDEX_E)i;

                int iRet = NETDEVSDK.NETDEV_GetDevConfig(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_lpDevHandle, m_oNetDemo.m_curSelectedTreeChannelIndex + 1, (int)NETDEV_CONFIG_COMMAND_E.NETDEV_GET_STREAMCFG, ref stStreamInfo, Marshal.SizeOf(stStreamInfo), ref dwBytesReturned);
                if (NETDEVSDK.TRUE != iRet)
                {
                    m_oNetDemo.showFailLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Get stream info, stream type : " + stStreamInfo.enStreamType, NETDEVSDK.NETDEV_GetLastError());
                }
                m_oNetDemo.showSuccessLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Get stream info, stream type : " + stStreamInfo.enStreamType);

                m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_videoStreamInfo.videoStreamInfoList[i] = stStreamInfo;
            }

            m_oNetDemo.showVideoInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_videoStreamInfo.videoStreamInfoList[0]);/*默认显示主流*/
            m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_videoStreamInfo.existFlag = true;
        }

        private void readVideoInfo()
        {
            m_oNetDemo.showVideoInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_videoStreamInfo.videoStreamInfoList[0]);/*默认显示主流*/
        }

        public void saveVideoInfo(NETDEV_VIDEO_STREAM_INFO_S stStreamInfo)
        {
            int iRet = NETDEVSDK.NETDEV_SetDevConfig(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_lpDevHandle, m_oNetDemo.m_curSelectedTreeChannelIndex + 1, (int)NETDEV_CONFIG_COMMAND_E.NETDEV_SET_STREAMCFG, ref stStreamInfo, Marshal.SizeOf(stStreamInfo));
            if (NETDEVSDK.TRUE != iRet)
            {
                m_oNetDemo.showFailLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Save stream info", NETDEVSDK.NETDEV_GetLastError());
                m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_videoStreamInfo.existFlag = false;
                return;
            }
            m_oNetDemo.showSuccessLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Save stream info");

        }
        /*************************** video Cfg end *****************************/


        /*************************** Image Cfg start *****************************/
        private void getIamgeInfo()
        {
            if (m_oNetDemo.m_curSelectedTreeChannelIndex < 0)
            {
                //m_netDemo.m_curSelectedTreeChannelIndex = 0;

                return;
            }

            if (m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_imageInfo.existFlag == false)
            {
                refreshImageInfo();
            }
            else
            {
                readImageInfo();
            }
        }

        public void refreshImageInfo()
        {
            /* Get Image Config */
            Int32 dwBytesReturned = 0;
            NETDEV_IMAGE_SETTING_S stImageInfo = new NETDEV_IMAGE_SETTING_S();

            int iRet = NETDEVSDK.NETDEV_GetDevConfig(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_lpDevHandle, m_oNetDemo.m_curSelectedTreeChannelIndex + 1, (int)NETDEV_CONFIG_COMMAND_E.NETDEV_GET_IMAGECFG, ref stImageInfo, Marshal.SizeOf(stImageInfo), ref dwBytesReturned);
            if (NETDEVSDK.TRUE != iRet)
            {
                m_oNetDemo.showFailLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Get image info", NETDEVSDK.NETDEV_GetLastError());
                return;
            }
            m_oNetDemo.showSuccessLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Get image info");

            m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_imageInfo.imageInfo = stImageInfo;
            m_oNetDemo.showImageInfo(stImageInfo);
        
        }

        public void readImageInfo()
        {
            m_oNetDemo.showImageInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_imageInfo.imageInfo);
        }

        public void saveImageInfo(NETDEV_IMAGE_SETTING_S stImageInfo)
        {
            int iRet = NETDEVSDK.NETDEV_SetDevConfig(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_lpDevHandle, m_oNetDemo.m_curSelectedTreeChannelIndex + 1, (int)NETDEV_CONFIG_COMMAND_E.NETDEV_SET_IMAGECFG, ref stImageInfo, Marshal.SizeOf(stImageInfo));
            if (NETDEVSDK.TRUE != iRet)
            {
                m_oNetDemo.showFailLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Save image info", NETDEVSDK.NETDEV_GetLastError());
                return;
            }
            m_oNetDemo.showSuccessLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Save image info");

            m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_imageInfo.imageInfo = stImageInfo;
        }

        /*************************** Image Cfg end *****************************/


        /*************************** OSD Cfg start *****************************/
        private void getOSDInfo()
        {
            if (m_oNetDemo.m_curSelectedTreeChannelIndex < 0)
            {
                //m_netDemo.m_curSelectedTreeChannelIndex = 0;

                return;
            }

            if (m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_OSDInfo.existFlag == false)
            {
                refreshOSDInfo();
            }
            else
            {
                readOSDInfo();
            }
        }

        public void refreshOSDInfo()
        {
            /* Get OSD */
            NETDEV_VIDEO_OSD_CFG_S stOSDInfo = new NETDEV_VIDEO_OSD_CFG_S();
            stOSDInfo.astTextOverlay = new NETDEV_OSD_TEXT_OVERLAY_S[NETDEVSDK.NETDEV_OSD_TEXTOVERLAY_NUM];

            Int32 dwBytesReturned = 0;
            int iRet = NETDEVSDK.NETDEV_GetDevConfig(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_lpDevHandle, m_oNetDemo.m_curSelectedTreeChannelIndex + 1, (int)NETDEV_CONFIG_COMMAND_E.NETDEV_GET_OSDCFG, ref stOSDInfo, Marshal.SizeOf(stOSDInfo), ref dwBytesReturned);
            if(NETDEVSDK.TRUE != iRet)
            {
                m_oNetDemo.showFailLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Get OSD cfg fail", NETDEVSDK.NETDEV_GetLastError());
                return;
            }
            m_oNetDemo.showSuccessLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Get OSD cfg");

            m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_OSDInfo.OSDInfo = stOSDInfo;
            m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_OSDInfo.existFlag = true;

            m_oNetDemo.showOSDInfo(stOSDInfo);

        }

        private void readOSDInfo()
        {
            m_oNetDemo.showOSDInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_OSDInfo.OSDInfo);
        }

        public void saveOSDInfo(NETDEV_VIDEO_OSD_CFG_S stOSDInfo)
        {
            int iRet = NETDEVSDK.NETDEV_SetDevConfig(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_lpDevHandle, m_oNetDemo.m_curSelectedTreeChannelIndex + 1, (int)NETDEV_CONFIG_COMMAND_E.NETDEV_SET_OSDCFG, ref stOSDInfo, Marshal.SizeOf(stOSDInfo));
            if (NETDEVSDK.TRUE != iRet)
            {
                m_oNetDemo.showFailLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Save OSD cfg", NETDEVSDK.NETDEV_GetLastError());
                return;
            }
            m_oNetDemo.showSuccessLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Save OSD cfg");

            m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_OSDInfo.OSDInfo = stOSDInfo;
        }

        /*************************** OSD Cfg end *****************************/


        /*************************** IO Cfg start *****************************/
        private void getIOInfo()
        {
            if (m_oNetDemo.m_curSelectedTreeChannelIndex < 0)
            {
                //m_netDemo.m_curSelectedTreeChannelIndex = 0;

                return;
            }

            if (m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_IOInfo.existFlag == false)
            {
                refreshIOInfo();
            }
            else
            {
                readIOInfo();
            }
        }

        public void refreshIOInfo()
        {
            int iChannelID = 0;
            if (m_oNetDemo.m_curSelectedTreeChannelIndex < 0)
            {
                //m_netDemo.m_curSelectedTreeChannelIndex = 0;

                return;
            }

            if (m_oNetDemo.m_curSelectedTreeChannelIndex == 0)
            {

            }
            else
            {
                iChannelID = m_oNetDemo.m_curSelectedTreeChannelIndex + 1;
            }

            /* Get alarm input info */
            getAlarmInputInfo(iChannelID);

            /* Get alarm output info */
            getAlarmOutputInfo(iChannelID);

            m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_IOInfo.existFlag = true;
        }

        private void readIOInfo()
        {
            m_oNetDemo.showAlarmInputInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_IOInfo.stInPutInfo);
            m_oNetDemo.showAlarmOutputInfo(0);
        }

        public bool saveAlarmOutputInfo(NETDEV_ALARM_OUTPUT_INFO_S stAlarmOutputInfo)
        {
            int iRet = NETDEVSDK.NETDEV_SetDevConfig(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_lpDevHandle, m_oNetDemo.m_curSelectedTreeChannelIndex + 1, (int)NETDEV_CONFIG_COMMAND_E.NETDEV_SET_ALARM_OUTPUTCFG, ref stAlarmOutputInfo, Marshal.SizeOf(stAlarmOutputInfo));
            if (NETDEVSDK.TRUE != iRet)
            {
                m_oNetDemo.showFailLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Save alarm output", NETDEVSDK.NETDEV_GetLastError());
                return false;
            }

            m_oNetDemo.showSuccessLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Save alarm output");

            return true;
        }

        public void getAlarmInputInfo(int channelID)
        {
            NETDEV_ALARM_INPUT_LIST_S stAlarmInputList = new NETDEV_ALARM_INPUT_LIST_S();
            stAlarmInputList.astAlarmInputInfo = new NETDEV_ALARM_INPUT_INFO_S[NETDEVSDK.NETDEV_MAX_ALARM_IN_NUM];

            Int32 dwBytesReturned = 0;
            int iRet = NETDEVSDK.NETDEV_GetDevConfig(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_lpDevHandle, channelID, (int)NETDEV_CONFIG_COMMAND_E.NETDEV_GET_ALARM_INPUTCFG, ref stAlarmInputList, Marshal.SizeOf(stAlarmInputList), ref dwBytesReturned);
            if (NETDEVSDK.TRUE != iRet)
            {
                m_oNetDemo.showFailLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Get alarm input info", NETDEVSDK.NETDEV_GetLastError());
                m_oNetDemo.initIOCfgTab();
                return;
            }

            m_oNetDemo.showSuccessLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Get alarm input info");

            m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_IOInfo.stInPutInfo = stAlarmInputList;
            m_oNetDemo.showAlarmInputInfo(stAlarmInputList);
        }

        public void getAlarmOutputInfo(int channelID)
        {
            NETDEV_ALARM_OUTPUT_LIST_S stAlarmOutputList = new NETDEV_ALARM_OUTPUT_LIST_S();
            stAlarmOutputList.astAlarmOutputInfo = new NETDEV_ALARM_OUTPUT_INFO_S[NETDEVSDK.NETDEV_MAX_ALARM_OUT_NUM];
            
            Int32 dwBytesReturned = 0;
            int iRet = NETDEVSDK.NETDEV_GetDevConfig(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_lpDevHandle, channelID, (int)NETDEV_CONFIG_COMMAND_E.NETDEV_GET_ALARM_OUTPUTCFG, ref stAlarmOutputList, Marshal.SizeOf(stAlarmOutputList), ref dwBytesReturned);
            if (NETDEVSDK.TRUE != iRet)
            {
                m_oNetDemo.showFailLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Get alarm output info", NETDEVSDK.NETDEV_GetLastError());
                m_oNetDemo.initIOCfgTab();
                return;
            }

            m_oNetDemo.showSuccessLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Get alarm output info");

            m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_IOInfo.stOutPutInfo = stAlarmOutputList;
            m_oNetDemo.showAlarmOutputInfo(0);
        }
        /*************************** IO Cfg end *****************************/


        /*************************** Privacy Mask Cfg start *****************************/
        private void getPrivacyMaskInfo()
        {
            if (m_oNetDemo.m_curSelectedTreeChannelIndex < 0)
            {
                //m_netDemo.m_curSelectedTreeChannelIndex = 0;

                return;
            }

            if (m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_privacyMaskInfo.existFlag == false)
            {
                refreshPrivacyMaskInfo();
            }
            else
            {
                readPrivacyMaskInfo();
            }
        }

        public void refreshPrivacyMaskInfo()
        {
            Int32 dwBytesReturned = 0;

            NETDEV_PRIVACY_MASK_CFG_S stPrivacyMaskInfo = new NETDEV_PRIVACY_MASK_CFG_S();
            stPrivacyMaskInfo.astArea = new NETDEV_PRIVACY_MASK_AREA_INFO_S[NETDEVSDK.NETDEV_MAX_PRIVACY_MASK_AREA_NUM];
            int iRet = NETDEVSDK.NETDEV_GetDevConfig(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_lpDevHandle, m_oNetDemo.m_curSelectedTreeChannelIndex + 1, (int)NETDEV_CONFIG_COMMAND_E.NETDEV_GET_PRIVACYMASKCFG, ref stPrivacyMaskInfo, Marshal.SizeOf(stPrivacyMaskInfo), ref dwBytesReturned);
            if (NETDEVSDK.TRUE != iRet)
            {
                m_oNetDemo.showFailLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Get privacy mask cfg", NETDEVSDK.NETDEV_GetLastError());
                return;
            }

            m_oNetDemo.showSuccessLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Get privacy mask cfg");

            m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_privacyMaskInfo.privacyMaskInfo = stPrivacyMaskInfo;
            m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_privacyMaskInfo.existFlag = true;
            m_oNetDemo.showPrivacyMaskInfo(stPrivacyMaskInfo);
        }

        private void readPrivacyMaskInfo()
        {
            m_oNetDemo.showPrivacyMaskInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_privacyMaskInfo.privacyMaskInfo);
        }

        public void deletePrivacyMaskInfo(int index)
        {
            int iRet = NETDEVSDK.NETDEV_SetDevConfig(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_lpDevHandle, m_oNetDemo.m_curSelectedTreeChannelIndex + 1, (int)NETDEV_CONFIG_COMMAND_E.NETDEV_DELETE_PRIVACYMASKCFG, ref index, Marshal.SizeOf(index));
            if (NETDEVSDK.TRUE != iRet)
            {
                m_oNetDemo.showFailLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Delete privacy mask cfg", NETDEVSDK.NETDEV_GetLastError());
                return;
            }

            m_oNetDemo.showSuccessLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Delete privacy mask cfg");
        }

        public void savePrivacyMaskInfo(NETDEV_PRIVACY_MASK_CFG_S stPrivacyMaskInfo)
        {
            int iRet = NETDEVSDK.NETDEV_SetDevConfig(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_lpDevHandle, m_oNetDemo.m_curSelectedTreeChannelIndex + 1, (int)NETDEV_CONFIG_COMMAND_E.NETDEV_SET_PRIVACYMASKCFG, ref stPrivacyMaskInfo, Marshal.SizeOf(stPrivacyMaskInfo));
            if (NETDEVSDK.TRUE != iRet)
            {
                m_oNetDemo.showFailLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Save privacy mask cfg", NETDEVSDK.NETDEV_GetLastError());
                return;
            }

            m_oNetDemo.showSuccessLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Save privacy mask cfg");

            m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_privacyMaskInfo.privacyMaskInfo = stPrivacyMaskInfo;
        }

        /*************************** Privacy Mask Cfg end *****************************/


        /*************************** Motion Cfg start *****************************/
        private void getMotionInfo()
        {
            if (m_oNetDemo.m_curSelectedTreeChannelIndex < 0)
            {
                //m_netDemo.m_curSelectedTreeChannelIndex = 0;

                return;
            }

            if (m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_MotionAlarmInfo.existFlag == false)
            {
                refreshMotionInfo();
            }
            else
            {
                readMotionInfo();
            }
        }

        public void refreshMotionInfo()
        {
            NETDEV_MOTION_ALARM_INFO_S stMotionAlarmInfo = new NETDEV_MOTION_ALARM_INFO_S();
            stMotionAlarmInfo.awScreenInfo = new NETDEV_SCREENINFO_COLUMN_S[NETDEVSDK.NETDEV_SCREEN_INFO_ROW];

            for (int i = 0; i < NETDEVSDK.NETDEV_SCREEN_INFO_ROW; i++)
            {
                stMotionAlarmInfo.awScreenInfo[i].columnInfo = new short[NETDEVSDK.NETDEV_SCREEN_INFO_COLUMN];
            }

            Int32 dwBytesReturned = 0;
            int iRet = NETDEVSDK.NETDEV_GetDevConfig(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_lpDevHandle, m_oNetDemo.m_curSelectedTreeChannelIndex + 1, (int)NETDEV_CONFIG_COMMAND_E.NETDEV_GET_MOTIONALARM, ref stMotionAlarmInfo, Marshal.SizeOf(stMotionAlarmInfo), ref dwBytesReturned);
            if (NETDEVSDK.TRUE != iRet)
            {
                m_oNetDemo.showFailLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Get motion cfg", NETDEVSDK.NETDEV_GetLastError());
                return;
            }

            m_oNetDemo.showSuccessLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Get motion cfg");
            
            if (stMotionAlarmInfo.dwObjectSize > MAXMOTIONOBJECTSIZE)
            {
                stMotionAlarmInfo.dwObjectSize = MAXMOTIONOBJECTSIZE;
            }

            m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_MotionAlarmInfo.MotionAlarmInfo = stMotionAlarmInfo;
            m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_MotionAlarmInfo.existFlag = true;
            m_oNetDemo.showMotionInfo(ref stMotionAlarmInfo);
        }

        private void readMotionInfo()
        {
            m_oNetDemo.showMotionInfo(ref m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_MotionAlarmInfo.MotionAlarmInfo);
        }

        public void saveMotionInfo(ref NETDEV_MOTION_ALARM_INFO_S stMotionAlarmInfo)
        {
            int iRet = NETDEVSDK.NETDEV_SetDevConfig(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_lpDevHandle, m_oNetDemo.m_curSelectedTreeChannelIndex + 1, (int)NETDEV_CONFIG_COMMAND_E.NETDEV_SET_MOTIONALARM, ref stMotionAlarmInfo, Marshal.SizeOf(stMotionAlarmInfo));
            if (NETDEVSDK.TRUE != iRet)
            {
                m_oNetDemo.showFailLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Save motion cfg", NETDEVSDK.NETDEV_GetLastError());
                return;
            }

            m_oNetDemo.showSuccessLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Save motion cfg");

            m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_MotionAlarmInfo.MotionAlarmInfo = stMotionAlarmInfo;
        }
        /*************************** Motion Cfg end *****************************/


        /*************************** Temper Cfg start *****************************/
        private void getTemperInfo()
        {
            if (m_oNetDemo.m_curSelectedTreeChannelIndex < 0)
            {
                //m_netDemo.m_curSelectedTreeChannelIndex = 0;

                return;
            }

            if (m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_tamperAlarmInfo.existFlag == false)
            {
                refreshTemperInfo();
            }
            else
            {
                readTemperInfo();
            }
        }

        public void refreshTemperInfo()
        {
            NETDEV_TAMPER_ALARM_INFO_S stTamperAlarmInfo = new NETDEV_TAMPER_ALARM_INFO_S();
            Int32 dwBytesReturned = 0;
            int iRet = NETDEVSDK.NETDEV_GetDevConfig(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_lpDevHandle, m_oNetDemo.m_curSelectedTreeChannelIndex + 1, (int)NETDEV_CONFIG_COMMAND_E.NETDEV_GET_TAMPERALARM, ref stTamperAlarmInfo, Marshal.SizeOf(stTamperAlarmInfo), ref dwBytesReturned);
            if (NETDEVSDK.TRUE != iRet)
            {
                m_oNetDemo.showFailLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Get tamper info", NETDEVSDK.NETDEV_GetLastError());
                return;
            }

            m_oNetDemo.showSuccessLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Get tamper info");

            m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_tamperAlarmInfo.tamperAlarmInfo = stTamperAlarmInfo;
            m_oNetDemo.showTemperInfo(ref stTamperAlarmInfo);
            m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_tamperAlarmInfo.existFlag = true;
        }

        private void readTemperInfo()
        {
            m_oNetDemo.showTemperInfo(ref m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_tamperAlarmInfo.tamperAlarmInfo);
        }

        public void saveTemperInfo(NETDEV_TAMPER_ALARM_INFO_S stTamperAlarmInfo)
        {
            int iRet = NETDEVSDK.NETDEV_SetDevConfig(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_lpDevHandle, m_oNetDemo.m_curSelectedTreeChannelIndex + 1, (int)NETDEV_CONFIG_COMMAND_E.NETDEV_SET_TAMPERALARM, ref stTamperAlarmInfo, Marshal.SizeOf(stTamperAlarmInfo));
            if (NETDEVSDK.TRUE != iRet)
            {
                m_oNetDemo.showFailLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Save tamper info", NETDEVSDK.NETDEV_GetLastError());
                return;
            }

            m_oNetDemo.showSuccessLogInfo(m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Save tamper info");

            m_deviceInfoList[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_channelInfoList[m_oNetDemo.m_curSelectedTreeChannelIndex].m_tamperAlarmInfo.tamperAlarmInfo = stTamperAlarmInfo;
        }

        /*************************** Temper Cfg end *****************************/
    }
}