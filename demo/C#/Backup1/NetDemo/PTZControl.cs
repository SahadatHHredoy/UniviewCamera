using System;
using NETSDKHelper;

namespace NetDemo
{
    public class PTZControl
    {
        int m_speed = 1;

        public PTZControl()
        {

        }

        public void setPTZSpeed(int speed)
        {
            this.m_speed = speed;
        }

        public bool control(IntPtr lpPlayHandle,int PTZCommand)
        {
            if (NETDEVSDK.FALSE == NETDEVSDK.NETDEV_PTZControl(lpPlayHandle, PTZCommand, this.m_speed))
            {

                return false;
            }

            return true;
        }
        
        public bool control_Other(IntPtr lpHandle, int ChannelID, int PTZCommand)
        {
            if (NETDEVSDK.FALSE == NETDEVSDK.NETDEV_PTZControl_Other(lpHandle, ChannelID, PTZCommand, this.m_speed))
            {
                return false;
            }

            return true;
        }
        
    }
}