#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "mainframe.h"
#include "statuswindow.h"
#include "taskwindow.h"
#include "debuglog.h"

MainFrame *MainFrame::m_pInstance = NULL;

MainFrame::MainFrame()
{
	
}

MainFrame::~MainFrame()
{

}

void MainFrame::releaseInstance(){
		if (m_pInstance){
		delete m_pInstance;
		m_pInstance = NULL;
	}	
}

MainFrame* MainFrame::getInstance(){
	if (m_pInstance == NULL)
		m_pInstance = new  MainFrame();

	return m_pInstance;
}

int MainFrame::MainFrameCtlControlProc(HWND hWnd,int message,WPARAM wParam,LPARAM lParam){
	MainFrame *pThis = getInstance();
	switch (message){
		case MSG_CREATE:
			pThis->onCreate(hWnd, wParam, lParam);
			break;
		case MSG_PAINT:
			pThis->onPaint(wParam, lParam);
			break;
		case MSG_ERASEBKGND:
			pThis->onEraseBkgnd(wParam, lParam);
			return 0;
			//break;
		case MSG_LBUTTONDOWN:
			LOG_PRINT ("MSG_LBUTTONDOWN\r\n");
			break;

		case MSG_LBUTTONUP:
			LOG_PRINT ("MSG_LBUTTONUP\r\n");
			break;
			
		default:
			break;
			
	}
	return DefaultWindowProc(hWnd, message, wParam, lParam);
}
bool MainFrame::createMainFrame(HWND hwnd){
	bool bRet = true;
	RECT rc;
	int i = 0;
	
	ENTER_FUNCTION;
	bRet = registerMainFrameControl();
	if (!bRet)
		return false;
	
	GetWindowRect(hwnd, &rc);
	m_pBmpBkGnd = (BITMAP *)calloc (1, sizeof(BITMAP));

	for (; i < MAINFRAME_BMP_NUM; i++)
		m_pBmpArray[i] = (BITMAP *)calloc (1, sizeof(BITMAP));

	if (LoadBitmap (HDC_SCREEN, m_pBmpArray[0], MAINFRAME_BTN_BMP_NAME_1)){
		LOG_PRINT ("Load bit map err.\r\n");
		return false;
	}

	if (LoadBitmap (HDC_SCREEN, m_pBmpArray[1], MAINFRAME_BTN_BMP_NAME_2)){
		LOG_PRINT ("Load bit map err.\r\n");
		return false;
	}

	if (LoadBitmap (HDC_SCREEN, m_pBmpArray[2], MAINFRAME_BTN_BMP_NAME_3)){
		LOG_PRINT ("Load bit map err.\r\n");
		return false;
	}
		
	if (LoadBitmap (HDC_SCREEN, m_pBmpBkGnd, MAINFRAME_BKGND_PIC)){

		LOG_PRINT ("Load bit map err\r\n");
		return false;
	}
		           
	m_hMainFrame = ::CreateWindow(MAINFRAME_CTRL_NAME,"", WS_CHILD | WS_VISIBLE, IDC_MAINFRAMEWND, \
		rc.left, TASKWND_HEIGHT, rc.right, (rc.bottom - TASKWND_HEIGHT-STATUSWND_HEIGHT), hwnd, 0);
	if (m_hMainFrame == HWND_INVALID)
		bRet = false;
	
	OUT_FUNCTION;

	return bRet;
}

bool MainFrame::registerMainFrameControl(){
	bool bRet;
	WNDCLASS MainFrameCtl;
	
    MainFrameCtl.spClassName = MAINFRAME_CTRL_NAME;
    MainFrameCtl.dwStyle     = WS_NONE;
    MainFrameCtl.dwExStyle   = WS_EX_NONE;
    MainFrameCtl.hCursor     = GetSystemCursor(0);
    MainFrameCtl.iBkColor    = COLOR_lightwhite;//GetWindowElementColor (WE_MAINC_THREED_BODY); ;
    MainFrameCtl.WinProc     = MainFrameCtlControlProc;

    bRet = RegisterWindowClass(&MainFrameCtl);
	return bRet;
}

void MainFrame::unregisterMainFrameControl(){
	::UnregisterWindowClass(MAINFRAME_CTRL_NAME);
}

void MainFrame::cleanUp()
{
	unregisterMainFrameControl();

	if (m_pBmpBkGnd != NULL)
	{
		free (m_pBmpBkGnd);
		m_pBmpBkGnd = NULL;
	}
	
	
}


int  MainFrame::onCreate(HWND hWnd,WPARAM wParam, LPARAM lParam){
	
	
	CreateWindow(CTRL_BUTTON, "BUTTON1", WS_CHILD | WS_VISIBLE | BS_BITMAP , IDC_CTRL_MAINFRAME_ONE, 190, 190, 120, 120, hWnd, (DWORD)m_pBmpArray[0]);
	CreateWindow(CTRL_BUTTON, "BUTTON2", WS_CHILD | WS_VISIBLE | BS_BITMAP, IDC_CTRL_MAINFRAME_TOW, 340, 190, 120, 120, hWnd, (DWORD)m_pBmpArray[1]);
	CreateWindow(CTRL_BUTTON, "BUTTON3", WS_CHILD | WS_VISIBLE | BS_BITMAP, IDC_CTRL_MAINFRAME_THREE, 490, 190, 120, 120, hWnd, (DWORD)m_pBmpArray[2]);
	return 0;
}
int  MainFrame::onCommand (WPARAM wParam, LPARAM lParam){
	return 0;
}

int  MainFrame::onPaint(WPARAM wParam, LPARAM lParam){
	return 0;
}

int  MainFrame::onEraseBkgnd(WPARAM wParam, LPARAM lParam){
	HDC hdc;
	MainFrame *pMf = getInstance();
	
	hdc  = (HDC)wParam;
	const RECT* clip = (const RECT*) lParam;

	RECT rcTemp;


	ENTER_FUNCTION;
	
	hdc = GetClientDC(pMf->m_hMainFrame);

	if (clip){
	    rcTemp = *clip;
	    ScreenToClient(pMf->m_hMainFrame, &rcTemp.left, &rcTemp.top);
	    ScreenToClient(pMf->m_hMainFrame, &rcTemp.right, &rcTemp.bottom);
	    IncludeClipRect(hdc, &rcTemp);
	}else
	    GetClientRect(pMf->m_hMainFrame, &rcTemp);

	FillBoxWithBitmap(hdc, 0, 0, RECTW(rcTemp), RECTH(rcTemp), pMf->m_pBmpBkGnd);
	ReleaseDC(hdc);

	OUT_FUNCTION;
	return 0;

}

