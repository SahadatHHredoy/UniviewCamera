using NETSDKHelper;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace NetDemo
{
    public partial class NETDEMO : Form
    {
       public IntPtr Handle = IntPtr.Zero;
       IntPtr lpDevHandle = IntPtr.Zero;
        public NETDEMO()
        {
            int iRet = NETDEVSDK.NETDEV_Init();
            InitializeComponent();
        }
        public void GetUTF8Buffer(string inputString, int bufferLen, out byte[] utf8Buffer)
        {
            utf8Buffer = new byte[bufferLen];
            byte[] tempBuffer = System.Text.Encoding.UTF8.GetBytes(inputString);
            for (int i = 0; i < tempBuffer.Length; ++i)
            {
                utf8Buffer[i] = tempBuffer[i];
            }
        }
        public void Button1_Click(object sender, EventArgs e)
        {
            String strTemp = string.Copy("D:\\");
            DateTime oDate = DateTime.Now;
            String strCurTime = oDate.ToString("yyMMddHHmmss", DateTimeFormatInfo.InvariantInfo);
            strTemp += "192.168.1.1";
            strTemp += "_";
            strTemp += 2;
            strTemp += "_";
            strTemp += strCurTime;
            byte[] picSavePath;
            GetUTF8Buffer(strTemp, NETDEVSDK.NETDEV_LEN_260, out picSavePath);
            int iRet = NETDEVSDK.NETDEV_CapturePicture(Handle, picSavePath, (int)NETDEV_PICTURE_FORMAT_E.NETDEV_PICTURE_JPG);
            if (NETDEVSDK.FALSE == iRet)
            {
                MessageBox.Show("Capture Failed");
                NETDEVSDK.NETDEV_StopRealPlay(lpDevHandle);
                NETDEVSDK.NETDEV_Logout(lpDevHandle);
                return;

            }
            NETDEVSDK.NETDEV_StopRealPlay(lpDevHandle);
            NETDEVSDK.NETDEV_Logout(lpDevHandle);
            Image img = Image.FromFile(strTemp + ".jpg");
            pictureBox1.ImageLocation = strTemp + ".jpg";
            pictureBox1.Height = img.Height;
            pictureBox1.Width = img.Width;
            this.Height = img.Height;
            this.Width = img.Width;
        }

   

        private void Button2_Click(object sender, EventArgs e)
        {
            //Our Code
            NETDEV_DEVICE_INFO_S pstDevInfo = new NETDEV_DEVICE_INFO_S();
       
            lpDevHandle = NETDEVSDK.NETDEV_Login("192.168.1.20", 80, "admin", "123456", ref pstDevInfo);
            if (lpDevHandle == IntPtr.Zero)
            {
                MessageBox.Show("login Error");
                return;
            }

            NETDEV_PREVIEWINFO_S stPreviewInfo = new NETDEV_PREVIEWINFO_S();
            stPreviewInfo.dwChannelID = 1;
            stPreviewInfo.dwLinkMode = (int)NETDEV_PROTOCAL_E.NETDEV_TRANSPROTOCAL_RTPTCP;
            stPreviewInfo.dwStreamType = (int)NETDEV_LIVE_STREAM_INDEX_E.NETDEV_LIVE_STREAM_INDEX_MAIN;
            stPreviewInfo.hPlayWnd = lpDevHandle;
             Handle = NETDEVSDK.NETDEV_RealPlay(lpDevHandle, ref stPreviewInfo, IntPtr.Zero, IntPtr.Zero);
            if (Handle == IntPtr.Zero)
            {
                MessageBox.Show("NNETDEV_RealPlay error");
                NETDEVSDK.NETDEV_StopRealPlay(lpDevHandle);
                NETDEVSDK.NETDEV_Logout(lpDevHandle);
                return;
            }
            MessageBox.Show("Connected");
        }
    }
}
