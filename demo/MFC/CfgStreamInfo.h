#pragma once


// CCfgStreamInfo 

class CCfgStreamInfo : public CDialog
{
    DECLARE_DYNAMIC(CCfgStreamInfo)

public:
    CCfgStreamInfo(CWnd* pParent = NULL);
    virtual ~CCfgStreamInfo();

    enum { IDD = IDD_CFG_STREAM };
    void ReadGlobeToVideoStream();

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()

    void getStreamInfo();

    void showByIndex(INT32 dwIndex);

private:
    INT32 m_dwBitRate;
    INT32 m_dwFrameRate;
    INT32 m_dwGOP;
    INT32 m_dwResHight;
    INT32 m_dwResWidth;
    CComboBox m_oCBoxStreamIndex;
    CComboBox m_oCBoxEncodeFormat;
    CComboBox m_oCBoxQuality;
    NETDEV_VIDEO_STREAM_INFO_S m_astStreamInfo[3];

public:
    afx_msg void OnBnClickedSaveVideoStream();
    afx_msg void OnBnClickedRefresh();
    afx_msg void OnCbnSelchangeComboStreamIndex();
    afx_msg void OnCbnSelchangeComboEncodeFormat();
    afx_msg void OnCbnSelchangeComboQuality();
};
