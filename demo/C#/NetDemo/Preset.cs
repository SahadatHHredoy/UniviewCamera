using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using NETSDKHelper;

namespace NetDemo
{
    public partial class Preset : Form
    {
        NetDemo m_oNetDemo;
        public Preset(NetDemo netDemo)
        {
            InitializeComponent();
            this.m_oNetDemo = netDemo;
        }

        private void okBtn_Click(object sender, EventArgs e)
        {
            if (m_oNetDemo.m_curSelectedTreeChannelIndex == -1)
            {
                return;
            }

            int  dwChannelID = m_oNetDemo.m_curSelectedTreeChannelIndex + 1;
            IntPtr lpHandle = m_oNetDemo.getDeviceInfoList()[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_lpDevHandle;

            
            if (IntPtr.Zero == lpHandle)
            {
                MessageBox.Show("Device Handle is 0 ","warning");
                return;
            }

            String szPresetName;

            Int32 lPresetID = -1;
            try
            {
                lPresetID = Convert.ToInt32(this.presetIDText.Text);
            }
            catch (FormatException)
            {
                return;
            }

            szPresetName = this.presetNameText.Text;

            if(0 >= lPresetID || lPresetID > NETDEVSDK.NETDEV_MAX_PRESET_NUM)
            {
                MessageBox.Show("Preset ID invalid.","warning");
                return;
            }

            int bRet = NETDEVSDK.NETDEV_PTZPreset_Other(lpHandle, dwChannelID, (int)NETDEV_PTZ_PRESETCMD_E.NETDEV_PTZ_SET_PRESET, szPresetName, lPresetID);
            if (NETDEVSDK.TRUE != bRet)
            {
                m_oNetDemo.showFailLogInfo(m_oNetDemo.getDeviceInfoList()[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Set preset", NETDEVSDK.NETDEV_GetLastError());
            }
            else
            {
                m_oNetDemo.showSuccessLogInfo(m_oNetDemo.getDeviceInfoList()[m_oNetDemo.m_curSelectedTreeDeviceIndex].m_ip + " chl:" + (m_oNetDemo.m_curSelectedTreeChannelIndex + 1), "Set preset");

                m_oNetDemo.presetGetBtn_Click(null, null);
                this.Close();
            }
        }

        private void CancelBtn_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
