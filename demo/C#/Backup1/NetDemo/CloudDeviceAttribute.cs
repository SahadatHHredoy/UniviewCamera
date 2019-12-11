using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using GeneralDef;

namespace NetDemo
{
    public partial class CloudDeviceAttribute : Form
    {
        //DeviceInfo device Info;
        public CloudDeviceAttribute(DeviceInfo deviceInfo)
        {
            InitializeComponent();

            this.ServerUrlText.Text = deviceInfo.m_cloudUrl;
            this.userNameText.Text = deviceInfo.m_cloudUserName;
            this.passwordText.Text = deviceInfo.m_cloudPassword;
            this.deviceIPText.Text = deviceInfo.m_stCloudDevInfo.szIPAddr;
            this.devicePortText.Text = Convert.ToString(deviceInfo.m_stCloudDevInfo.dwDevPort);
            this.deviceUserNameText.Text = deviceInfo.m_stCloudDevInfo.szDevUserName;
            this.devicenameText.Text = deviceInfo.m_stCloudDevInfo.szDevName;
            this.deviceModelText.Text = deviceInfo.m_stCloudDevInfo.szDevModel;
            this.deviceSerialNumText.Text = deviceInfo.m_stCloudDevInfo.szDevSerialNum;
            this.organizationIDText.Text = Convert.ToString(deviceInfo.m_stCloudDevInfo.dwOrgID);
        }
    }
}
