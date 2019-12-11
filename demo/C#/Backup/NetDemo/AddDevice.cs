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
    public partial class AddDevice : Form
    {
        private NetDemo m_oNetDemo = null;

        public AddDevice(NetDemo oNetDemo)
        {
            this.m_oNetDemo = oNetDemo;
            InitializeComponent();
        }

        private void CannelBtn_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void OKBtn_Click(object sender, EventArgs e)
        {
            String strIPAddr = this.ipDomainNameText.Text;
            short sPort = 0;
            try
            {
                sPort = Convert.ToInt16(this.portText.Text);
            }
            catch (FormatException)
            {
                return;
            }
            catch (OverflowException)
            {
                return;
            }

            String strUserName = this.userNameText.Text;
            String strPassword = this.passwordText.Text;

            m_oNetDemo.LoginLocalDevice(strIPAddr, sPort, strUserName, strPassword);
            this.Close();
        }
    }
}
