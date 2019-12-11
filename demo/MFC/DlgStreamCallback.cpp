// DlgStreamCallback.cpp 
//

#include "stdafx.h"
#include "NetDemo.h"
#include "DlgStreamCallback.h"


// CDlgStreamCallback

IMPLEMENT_DYNAMIC(CDlgStreamCallback, CDialog)

CDlgStreamCallback::CDlgStreamCallback(CWnd* pParent /*=NULL*/)
    : CDialog(CDlgStreamCallback::IDD, pParent),
    m_bStreamClosed(TRUE),
    m_bDecodeClosed(TRUE),
    m_bDisplayClosed(TRUE),
    m_bParseClosed(TRUE)
{
}

CDlgStreamCallback::~CDlgStreamCallback()
{
}

void CDlgStreamCallback::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgStreamCallback, CDialog)
    ON_BN_CLICKED(IDC_BUTTON_REALTIME_REG, &CDlgStreamCallback::OnBnClickedButtonRealtimeReg)
    ON_BN_CLICKED(IDC_BUTTON_REALTIME_CLOSE, &CDlgStreamCallback::OnBnClickedButtonRealtimeClose)
    ON_BN_CLICKED(IDC_BUTTON_DECODE_REG, &CDlgStreamCallback::OnBnClickedButtonDecodeReg)
    ON_BN_CLICKED(IDC_BUTTON_DECODE_CLOSE, &CDlgStreamCallback::OnBnClickedButtonDecodeClose)
    ON_BN_CLICKED(IDC_BUTTON_DISPLAY_REG, &CDlgStreamCallback::OnBnClickedButtonDisplayReg)
    ON_BN_CLICKED(IDC_BUTTON_DISPLAY_CLOSE, &CDlgStreamCallback::OnBnClickedButtonDisplayClose)
    ON_BN_CLICKED(IDC_BUTTON_FRAME_REG, &CDlgStreamCallback::OnBnClickedButtonFrameReg)
    ON_BN_CLICKED(IDC_BUTTON_FRAME_CLOSE, &CDlgStreamCallback::OnBnClickedButtonFrameClose)
END_MESSAGE_MAP()


// stream callback functions' definitions
void STDCALL pfnNetDEV_PlayDataCB(LPVOID        lpPlayHandle,
                                  const BYTE    *pucBuffer,
                                  INT32         dwBufSize,
                                  INT32         dwMediaDataType,
                                  LPVOID        lpUserParam
                                  )
{
    // get wanted data from [param]dwBufSize and [param]dwMediaDataType
    CString strOut;
    strOut.Format("\r\n-----  source buffer length is [%d], the type is %d  -----", dwBufSize, dwMediaDataType);

    return;
}

void STDCALL pfnNetDEV_DecodeDataCB(LPVOID lpPlayHandle,
                                    const NETDEV_PICTURE_DATA_S *pstPictureData,
                                    LPVOID lpUserParam
                                    )
{
    // get wanted data from [param]pstPictureData
    if (0 == pstPictureData->dwPicHeight || 0 == pstPictureData->dwPicWidth)
    {
        return ;
    }

    CHAR* szDataBuf = new CHAR[pstPictureData->dwPicHeight * pstPictureData->dwPicWidth * 3 / 2];
    memset(szDataBuf, 0,pstPictureData->dwPicHeight * pstPictureData->dwPicWidth * 3 / 2);

    INT32 dwHeight = pstPictureData->dwPicHeight;
    INT32 dwWidth = pstPictureData->dwPicWidth;

    INT32 dwOffset = 0;
    INT32 dwIndex = 0;
    for (dwIndex = 0; dwIndex < dwHeight; dwIndex++)
    {
        memcpy(szDataBuf + dwOffset, pstPictureData->pucData[0] + dwIndex * pstPictureData->dwLineSize[0], dwWidth);
        dwOffset += dwWidth;
    }
    for (dwIndex = 0; dwIndex < dwHeight / 2; dwIndex++)
    {
        memcpy(szDataBuf + dwOffset, pstPictureData->pucData[1] + dwIndex * pstPictureData->dwLineSize[1], dwWidth / 2);
        dwOffset += dwWidth / 2;
    }
    for (dwIndex = 0; dwIndex < dwHeight / 2; dwIndex++)
    {
        memcpy(szDataBuf + dwOffset, pstPictureData->pucData[2] + dwIndex * pstPictureData->dwLineSize[2], dwWidth / 2);
        dwOffset += dwWidth / 2;
    }

    FILE* fp;
    /* 因YUV数据较大，故此处以wb+方式打开文件，所以只会写入一帧数据 */
    fp = fopen("YUVData.yuv", "wb+");
    fwrite((CHAR*)szDataBuf, dwHeight * dwWidth * 3 / 2, 1, fp);
    fclose(fp);

    delete [] szDataBuf;

    return;
}

void STDCALL pfnNetDEV_DisplayDataCB(LPVOID lpHandle,
                                     LPVOID hdc,
                                     LPVOID lpUserParam
                                     )
{
    // get wanted data from [param]hdc
    CString strOut;
    strOut.Format("\r\n----------  display is [%d]  ---------\n", (INT32 *) hdc);

    return;
}

void STDCALL pfnNetDEV_ParseDataCB(LPVOID lpPlayHandle,
                                   const NETDEV_PARSE_VIDEO_DATA_S *pstParseVideoData,
                                   LPVOID lpUserParam
                                   )
{
    // get wanted data from [param]pstParseVideoData
    CString strOut;
    strOut.Format("\r\n-------  parse time is [%u]  ----\n", pstParseVideoData->tTimeStamp);

    return;
}


void CDlgStreamCallback::OnBnClickedButtonRealtimeReg()
{
    INT32 dwCurWinID = ga_pMainDlg->GetCurWinID();
    CPlayWnd* pPlayWnd = (CPlayWnd *)ga_pMainDlg->m_oScreenPannel.GetPage(dwCurWinID);
    LPVOID lpPlayHandle = pPlayWnd->GetSplitHandle();

    if (NULL != lpPlayHandle)
    {
        BOOL bRet = NETDEV_SetPlayDataCallBack(lpPlayHandle, pfnNetDEV_PlayDataCB, TRUE, (LPVOID) this);
        if (TRUE != bRet)
        {
            NETDEMO_LOG_ERROR(NULL, "Register stream callback");
            m_bStreamClosed = TRUE;

            return;
        }

        m_bStreamClosed = FALSE;
        NETDEMO_LOG_SUCC(NULL, "Register stream callback, get wanted data in self-defined callback function");

        return;
    }

    MessageBox("Please start the realplay first.");
    NETDEMO_LOG_ERROR(NULL, "No realplay handle");

    return;
}
void CDlgStreamCallback::OnBnClickedButtonRealtimeClose()
{
    INT32 dwCurWinID = ga_pMainDlg->GetCurWinID();
    CPlayWnd* pPlayWnd = (CPlayWnd *)ga_pMainDlg->m_oScreenPannel.GetPage(dwCurWinID);
    LPVOID lpPlayHandle = pPlayWnd->GetSplitHandle();

    if (NULL != lpPlayHandle)
    {
        BOOL bRet = NETDEV_SetPlayDataCallBack(lpPlayHandle, NULL, TRUE, NULL);
        if (TRUE != bRet)
        {
            NETDEMO_LOG_ERROR(NULL, "Close stream callback");
            m_bStreamClosed = FALSE;
            return;
        }

        NETDEMO_LOG_SUCC(NULL, "Close stream callback");
        m_bStreamClosed = TRUE;

        return;
    }

    MessageBox("Please start the realplay first.");
    NETDEMO_LOG_ERROR(NULL, "No realplay handle");

    return;
}

void CDlgStreamCallback::OnBnClickedButtonDecodeReg()
{
    INT32 dwCurWinID = ga_pMainDlg->GetCurWinID();
    CPlayWnd* pPlayWnd = (CPlayWnd *)ga_pMainDlg->m_oScreenPannel.GetPage(dwCurWinID);
    LPVOID lpPlayHandle = pPlayWnd->GetSplitHandle();

    if (NULL != lpPlayHandle)
    {
        BOOL bRet = NETDEV_SetPlayDecodeVideoCB(lpPlayHandle, pfnNetDEV_DecodeDataCB, TRUE, (LPVOID) this);
        if (TRUE != bRet)
        {
            NETDEMO_LOG_ERROR(NULL, "Register decode callback");
            m_bDecodeClosed = TRUE;

            return;
        }

        NETDEMO_LOG_SUCC(NULL, "Register decode callback, get wanted data in self-defined callback function");
        m_bDecodeClosed = FALSE;

        return;
    }

    MessageBox("Please start the realplay first.");
    NETDEMO_LOG_ERROR(NULL, "No realplay handle");

    return;
}

void CDlgStreamCallback::OnBnClickedButtonDecodeClose()
{
    INT32 dwCurWinID = ga_pMainDlg->GetCurWinID();
    CPlayWnd* pPlayWnd = (CPlayWnd *)ga_pMainDlg->m_oScreenPannel.GetPage(dwCurWinID);
    LPVOID lpPlayHandle = pPlayWnd->GetSplitHandle();

    if (NULL != lpPlayHandle)
    {
        BOOL bRet = NETDEV_SetPlayDecodeVideoCB(lpPlayHandle, NULL, TRUE, NULL);
        if (TRUE != bRet)
        {
            NETDEMO_LOG_ERROR(NULL, "Close decode callback");
            m_bDecodeClosed = FALSE;

            return;
        }

        NETDEMO_LOG_SUCC(NULL, "Close decode callback");
        m_bDecodeClosed = TRUE;

        return;
    }

    MessageBox("Please start the realplay first.");
    NETDEMO_LOG_ERROR(NULL, "No realplay handle");

    return;
}

void CDlgStreamCallback::OnBnClickedButtonDisplayReg()
{
    INT32 dwCurWinID = ga_pMainDlg->GetCurWinID();
    CPlayWnd* pPlayWnd = (CPlayWnd *)ga_pMainDlg->m_oScreenPannel.GetPage(dwCurWinID);
    LPVOID lpPlayHandle = pPlayWnd->GetSplitHandle();

    if (NULL != lpPlayHandle)
    {
        BOOL bRet = NETDEV_SetPlayDisplayCB(lpPlayHandle, pfnNetDEV_DisplayDataCB, (LPVOID) this);
        if (TRUE != bRet)
        {
            NETDEMO_LOG_ERROR(NULL, "Register display callback");
            m_bDisplayClosed = TRUE;

            return;
        }

        NETDEMO_LOG_SUCC(NULL, "Register display callback, get wanted data in self-defined callback function");
        m_bDisplayClosed = FALSE;

        return;
    }

    MessageBox("Please start the realplay first.");
    NETDEMO_LOG_ERROR(NULL, "No realplay handle");

    return;
}

void CDlgStreamCallback::OnBnClickedButtonDisplayClose()
{
    INT32 dwCurWinID = ga_pMainDlg->GetCurWinID();
    CPlayWnd* pPlayWnd = (CPlayWnd *)ga_pMainDlg->m_oScreenPannel.GetPage(dwCurWinID);
    LPVOID lpPlayHandle = pPlayWnd->GetSplitHandle();

    if (NULL != lpPlayHandle)
    {
        BOOL bRet = NETDEV_SetPlayDisplayCB(lpPlayHandle, NULL, NULL);
        if (TRUE != bRet)
        {
            NETDEMO_LOG_ERROR(NULL, "Close display callback");
            m_bDisplayClosed = FALSE;

            return;
        }

        NETDEMO_LOG_SUCC(NULL, "Close display callback");
        m_bDisplayClosed = TRUE;

        return;
    }

    MessageBox("Please start the realplay first.");
    NETDEMO_LOG_ERROR(NULL, "No realplay handle");

    return;
}

void CDlgStreamCallback::OnBnClickedButtonFrameReg()
{
    INT32 dwCurWinID = ga_pMainDlg->GetCurWinID();
    CPlayWnd* pPlayWnd = (CPlayWnd *)ga_pMainDlg->m_oScreenPannel.GetPage(dwCurWinID);
    LPVOID lpPlayHandle = pPlayWnd->GetSplitHandle();

    if (NULL != lpPlayHandle)
    {
        BOOL bRet = NETDEV_SetPlayParseCB(lpPlayHandle, pfnNetDEV_ParseDataCB, TRUE, (LPVOID) this);
        if (TRUE != bRet)
        {
            NETDEMO_LOG_ERROR(NULL, "Register parse callback");
            m_bParseClosed = TRUE;

            return;
        }

        NETDEMO_LOG_SUCC(NULL, "Register parse callback, get wanted data in self-defined callback function");
        m_bParseClosed = FALSE;

        return;
    }

    MessageBox("Please start the realplay first.");
    NETDEMO_LOG_ERROR(NULL, "No realplay handle");

    return;
}

void CDlgStreamCallback::OnBnClickedButtonFrameClose()
{
    INT32 dwCurWinID = ga_pMainDlg->GetCurWinID();
    CPlayWnd* pPlayWnd = (CPlayWnd *)ga_pMainDlg->m_oScreenPannel.GetPage(dwCurWinID);
    LPVOID lpPlayHandle = pPlayWnd->GetSplitHandle();

    if (NULL != lpPlayHandle)
    {
        BOOL bRet = NETDEV_SetPlayParseCB(lpPlayHandle, NULL, TRUE, NULL);
        if (TRUE != bRet)
        {
            NETDEMO_LOG_ERROR(NULL, "Close parse callback");
            m_bParseClosed = FALSE;

            return;
        }

        NETDEMO_LOG_SUCC(NULL, "Close parse callback");
        m_bParseClosed = TRUE;

        return;
    }

    MessageBox("Please start the realplay first.");
    NETDEMO_LOG_ERROR(NULL, "No realplay handle");

    return;
}

void CDlgStreamCallback::CloseAllCallback()
{
    if (FALSE == m_bStreamClosed)
    {
        OnBnClickedButtonRealtimeClose();
    }
    if (FALSE == m_bDecodeClosed)
    {
        OnBnClickedButtonDecodeClose();
    }
    if (FALSE == m_bDisplayClosed)
    {
        OnBnClickedButtonDisplayClose();
    }
    if (FALSE == m_bParseClosed)
    {
        OnBnClickedButtonFrameClose();
    }

    return;
}