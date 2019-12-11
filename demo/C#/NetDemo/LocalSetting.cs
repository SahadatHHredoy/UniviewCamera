using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using NETSDKHelper;

namespace NetDemo
{
    public partial class LocalSetting : Form
    {
        public static String m_strPicSavePath = null;
        public static String m_strLocalRecordPath = null;
        public static String m_strLogPath = null;
        public static Int32 m_iWaitTime = 0;
        public static Int32 m_iTryTimes = 0;
        public static Int32 m_ireceiveTimeOut = 0;
        public static Int32 m_ifileTimeOut = 0;
        public static NETDEV_REV_TIMEOUT_S stRevTimeout = new NETDEV_REV_TIMEOUT_S();

        public static bool m_bAutoSaveFlag = true;
        public static bool m_bFailSaveFlag = true;
        public static bool m_bSuccessSaveFlag = true;

        public LocalSetting(/*NetDemo netDemo*/)
        {
            InitializeComponent();
            logFilePathText.Text = m_strLogPath;
            snapshotFilePathText.Text = m_strPicSavePath;
            LocalRecordPathText.Text = m_strLocalRecordPath;
            waitTimeText.Text = Convert.ToString(m_iWaitTime);
            tryTimesText.Text = Convert.ToString(m_iTryTimes);
            receiveTimeOutText.Text = Convert.ToString(m_ireceiveTimeOut);
            fileTimeOutText.Text = Convert.ToString(m_ifileTimeOut);
            AutoSaveCkBox.Checked = m_bAutoSaveFlag;
            failureLogCkBox.Checked = m_bFailSaveFlag;
            SuccessLogCkBox.Checked = m_bSuccessSaveFlag;
        }

        public static void setPath(String picturePath,String recordPath,String logPath)
        {
            try
            {
                if (!Directory.Exists(picturePath))
                {
                    Directory.CreateDirectory(picturePath);
                }

                if (!Directory.Exists(recordPath))
                {
                    Directory.CreateDirectory(recordPath);
                }

                if (!Directory.Exists(logPath))
                {
                    Directory.CreateDirectory(logPath);
                    int bRet = NETDEVSDK.NETDEV_SetLogPath(logPath);
                    if (NETDEVSDK.TRUE != bRet)
                    {
                        MessageBox.Show("Set log path fail: " + NETDEVSDK.NETDEV_GetLastError(), "warning");
                    }
                    else
                    {
                        m_strLogPath = logPath;
                        MessageBox.Show("Set log path Success", "warning");
                    }
                }
                else
                {
                    m_strLogPath = logPath;
                }

                m_strPicSavePath = picturePath;
                m_strLocalRecordPath = recordPath;
            }
            catch (Exception)
            {
                MessageBox.Show("create path fail","warning");
            }
        }

        private void SavePathSettingBtn_Click(object sender, EventArgs e)
        {
            setPath(snapshotFilePathText.Text,LocalRecordPathText.Text,logFilePathText.Text);
        }

        public static void setKeepLiveTime(Int32 iWaitTime, Int32 iTryTime)
        {
            try
            {
               int bRet = NETDEVSDK.NETDEV_SetConnectTime(iWaitTime, iTryTime);
               if (NETDEVSDK.TRUE != bRet)
               {
                   MessageBox.Show("Set Connect Time fail" + NETDEVSDK.NETDEV_GetLastError(), "warning");
                   return;
               }
               m_iWaitTime = iWaitTime;
               m_iTryTimes = iTryTime;
            }
            catch (FormatException)
            {
            
            }  

        }

        private void saveKeepLiveSttingBtn_Click(object sender, EventArgs e)
        {
            setKeepLiveTime(Convert.ToInt32(waitTimeText.Text), Convert.ToInt32(tryTimesText.Text));
        }

        public static void setTimeOut(Int32 iReceiveTimeOut, Int32 iFileTimeOut)
        {
            stRevTimeout.dwRevTimeOut = iReceiveTimeOut;
            stRevTimeout.dwFileReportTimeOut = iFileTimeOut;
            int iRet = NETDEVSDK.NETDEV_SetRevTimeOut(ref stRevTimeout);
            if (NETDEVSDK.TRUE != iRet)
            {
                MessageBox.Show("Set Connect Time fail" + NETDEVSDK.NETDEV_GetLastError(),"warning");
                return;
            }
            m_ireceiveTimeOut = iReceiveTimeOut;
            m_ifileTimeOut = iFileTimeOut;
        }

        private void saveTimeOutSettingBtn_Click(object sender, EventArgs e)
        {
            setTimeOut(Convert.ToInt32(receiveTimeOutText.Text), Convert.ToInt32(fileTimeOutText.Text));
        }

        public static void setOperLog(bool bAutoSaveCkBox, bool bFailureLogCkBox, bool bSuccessLogCkBox)
        {
            m_bAutoSaveFlag = bAutoSaveCkBox;
            m_bFailSaveFlag = bFailureLogCkBox;
            m_bSuccessSaveFlag = bSuccessLogCkBox;
        }

        public void saveOperLogSettingBtn_Click(object sender, EventArgs e)
        {
            setOperLog(AutoSaveCkBox.Checked, failureLogCkBox.Checked, SuccessLogCkBox.Checked);
        }
    }

    public class LogMessage
    {
        public static void failLog(string deviceInfo, string logInfo, int errorCode)
        {
            StreamWriter sw = createLogFile();
            if (sw == null)
            {
                return;
            }

            sw.WriteLine(DateTime.Now.ToString() + "  [" + deviceInfo + "]  [Fail] : " + logInfo + "  [error] : " + errorCode);
            sw.Close();
        }

        public static void sucessLog(string deviceInfo, string logInfo)
        {
            StreamWriter sw = createLogFile();
            if (sw == null)
            {
                return;
            }

            sw.WriteLine(DateTime.Now.ToString() + "  [" + deviceInfo + "]  [Success] : " + logInfo);
            sw.Close();
        }

        public static StreamWriter createLogFile()
        {
            string strLogFile = "";
            strLogFile += (LocalSetting.m_strLogPath + DateTime.Now.Year + DateTime.Now.Month + DateTime.Now.Day + ".log");

            StreamWriter sw = null;
            try
            {
                sw = new StreamWriter(strLogFile, true);
            }
            catch (Exception)
            {
                return null;
            }

            return sw;
        }
    }
}
