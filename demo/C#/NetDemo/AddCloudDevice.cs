using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace NetDemo
{
    public partial class AddCloudDevice : Form
    {
        private NetDemo m_oNetDemo = null;
        public AddCloudDevice(NetDemo oNetDemo)
        {
            this.m_oNetDemo = oNetDemo;
            InitializeComponent();
        }

        private void OKBtn_Click(object sender, EventArgs e)
        {
            String strURL = this.URLText.Text;
            String strUserName = this.UserNameText.Text;
            String strPassword = this.PasswordText.Text;
            if (strURL.Equals("") || strUserName.Equals("") || strPassword.Equals(""))
            {
                return;
            }

            // login cloud device
            m_oNetDemo.loginCloudDevice(strURL, strUserName, strPassword);
            this.Close();
        }

        private void CannelBtn_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
