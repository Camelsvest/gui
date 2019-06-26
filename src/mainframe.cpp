#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "mainframe.h"
#include "statuswindow.h"
#include "taskwindow.h"
#include "debuglog.h"

MainFrame *MainFrame::m_pInstance = NULL;
WNDPROC MainFrame::m_btnProc = NULL;

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

int MainFrame::mainFrameCtlControlProc(HWND hWnd,int message,WPARAM wParam,LPARAM lParam){
	MainFrame *pThis = getInstance();
	switch (message){
		case MSG_CREATE: //创建窗口
			LOG_PRINT ("MSG_CREATE\r\n");
			pThis->onCreate(hWnd, wParam, lParam);
			break;

		case MSG_PAINT: //绘制窗口
			LOG_PRINT ("MSG_PAINT\r\n");
			pThis->onPaint(hWnd, wParam, lParam);
			//return 0;here can not return 
			break;
			
		case MSG_ERASEBKGND:
			pThis->onEraseBkgnd(wParam, lParam);
			return 0;
			
		case MSG_COMMAND:
			pThis->onCommand(wParam, lParam);
			return 0;
			break;
			
		case MSG_KEYDOWN: //键盘按下按键
			pThis->onKeyDown(wParam, lParam);
			return 0;
			
		case MSG_LBUTTONDOWN:
			LOG_PRINT ("MSG_LBUTTONDOWN\r\n");
			break;

		case MSG_LBUTTONUP:
			LOG_PRINT ("MSG_LBUTTONUP\r\n");
			break;

		case MSG_CLOSE:
			LOG_PRINT ("MSG_CLOSE\r\n");
			pThis->onClose ();
			return 0;
		default:
			break;
			
	}
	return DefaultWindowProc(hWnd, message, wParam, lParam);
}
bool MainFrame::createMainFrame(HWND hwnd){
	bool bRet = true;
	RECT rc;
	
	ENTER_FUNCTION;

	GetWindowRect(hwnd, &rc);
	
	m_pBmpBkGnd = (BITMAP *)calloc (1, sizeof(BITMAP));

	if (LoadBitmap (HDC_SCREEN, m_pBmpBkGnd, MAINFRAME_BKGND_PIC)){

		LOG_PRINT ("Load bit map err\r\n");
		return false;
	}
	
	bRet = registerMainFrameControl();
	if (!bRet)
		return false;

	m_hMainFrame = ::CreateWindow(MAINFRAME_CTRL_NAME,"", WS_CHILD | WS_VISIBLE, IDC_MAINFRAMEWND, \
		rc.left, TASKWND_HEIGHT, rc.right, (rc.bottom - TASKWND_HEIGHT-STATUSWND_HEIGHT), hwnd, 0);
	if (m_hMainFrame == HWND_INVALID)
		bRet = false;


	if (LoadBitmap (HDC_SCREEN, &m_pBmpArray[0], MAINFRAME_BTN_BMP_NAME_1)){
		LOG_PRINT ("Load bit map err.\r\n");
		return false;
	}

	if (LoadBitmap (HDC_SCREEN, &m_pBmpArray[1], MAINFRAME_BTN_BMP_NAME_2)){
		LOG_PRINT ("Load bit map err.\r\n");
		return false;
	}

	if (LoadBitmap (HDC_SCREEN, &m_pBmpArray[2], MAINFRAME_BTN_BMP_NAME_3)){
		LOG_PRINT ("Load bit map err.\r\n");
		return false;
	}
	
	if (LoadBitmap (HDC_SCREEN, &m_pBmpArray[3], MAINFRAME_BTN_BMP_NAME_7)){

		LOG_PRINT ("Load bit err\r\n");
		return false;
	}

	if (LoadBitmap (HDC_SCREEN, &m_pBmpArray[4], MAINFRAME_BTN_BMP_NAME_9)){
	
			LOG_PRINT ("Load bit err\r\n");
			return false;
	}
	
	if (LoadBitmap (HDC_SCREEN, &m_pBmpArray[5], MAINFRAME_BTN_BMP_NAME_11)){
	
			LOG_PRINT ("Load bit err\r\n");
			return false;
	}

	
	if (LoadBitmap (HDC_SCREEN, &m_pBmpArray[6], MAINFRAME_BTN_BMP_NAME_13)){
	
			LOG_PRINT ("Load bit err\r\n");
			return false;
	}

	if (LoadBitmap (HDC_SCREEN, &m_pBmpArray[7], MAINFRAME_BTN_BMP_NAME_15)){
	
			LOG_PRINT ("Load bit err\r\n");
			return false;
	}

	
	if (LoadBitmap (HDC_SCREEN, &m_pBmpArray[8], MAINFRAME_BTN_BMP_NAME_17)){
	
			LOG_PRINT ("Load bit err\r\n");
			return false;
	}

	if (LoadBitmap (HDC_SCREEN, &m_pBmpArray[9], MAINFRAME_BTN_BMP_NAME_19)){
	
			LOG_PRINT ("Load bit err\r\n");
			return false;
	}

	if (LoadBitmap (HDC_SCREEN, &m_pBmpArray[11], MAINFRAME_BTN_BMP_NAME_4)){
		
			LOG_PRINT ("Load bit err\r\n");
			return false;
	}
	
	if (LoadBitmap (HDC_SCREEN, &m_pBmpArray[12], MAINFRAME_BTN_BMP_NAME_5)){
		
			LOG_PRINT ("Load bit err\r\n");
			return false;
	}	

	if (LoadBitmap (HDC_SCREEN, &m_pBmpArray[10], MAINFRAME_BTN_BMP_NAME_6)){
	
			LOG_PRINT ("Load bit err\r\n");
			return false;
	}

	EXIT_FUNCTION;

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
    MainFrameCtl.WinProc     = mainFrameCtlControlProc;

    bRet = RegisterWindowClass(&MainFrameCtl);
	return bRet;
}

void MainFrame::unregisterMainFrameControl(){
	::UnregisterWindowClass(MAINFRAME_CTRL_NAME);
}

int MainFrame::defButtonProc (HWND hWnd, int message, WPARAM wParam, LPARAM lParam){
	HDC hdc;
	
	static int status[3] =  {0, 0, 0};
	
	MainFrame *pThis = getInstance();

	if (message == MSG_ERASEBKGND){
		return 0;
	}
	else if (message == MSG_LBUTTONDOWN){
		if ( hWnd == pThis->m_hWndInMainFrame[0] ){ 
			status[0] = 1;
		}else if (hWnd == pThis->m_hWndInMainFrame[1]){
			status[1] = 1;
		
		}else if (hWnd == pThis->m_hWndInMainFrame[2]){
			status[2] = 1;
		}
	}
	else if (message == MSG_LBUTTONUP) {
		if ( hWnd == pThis->m_hWndInMainFrame[0] ){ 
			status[0] = 0;
		}else if (hWnd == pThis->m_hWndInMainFrame[1]){
			status[1] = 0;
		
		}else if (hWnd == pThis->m_hWndInMainFrame[2]){
			status[2] = 0;
		}

	}
	else if (message == MSG_MOUSEMOVEIN){

	}
	else if (message == MSG_PAINT){
		
		LOG_PRINT ("MSG_PAINT\r\n");
		hdc = BeginPaint (hWnd);
		
		if ( hWnd == pThis->m_hWndInMainFrame[2] ){ 
			LOG_PRINT ("2->hWnd = 0x%x\r\n", hWnd);
			if (status[2] == 0)
				FillBoxWithBitmap (hdc, 0, 0, 120, 120,&(pThis->m_pBmpArray[2]));//put bmp in button
			else
				FillBoxWithBitmap (hdc, 0, 0, 120, 120,&(pThis->m_pBmpArray[10]));
			
		}else if ( hWnd == pThis->m_hWndInMainFrame[0] ){
			LOG_PRINT ("0->hWnd = 0x%x\r\n", hWnd);
			if (status[0] == 0)
				FillBoxWithBitmap (hdc, 0, 0, 120, 120,&(pThis->m_pBmpArray[0]));//put bmp in button
			else
				FillBoxWithBitmap (hdc, 0, 0, 120, 120,&(pThis->m_pBmpArray[11]));

		}else if (  hWnd == pThis->m_hWndInMainFrame[1] ){
           	LOG_PRINT ("1->hWnd = 0x%x\r\n", hWnd);
			if (status[1] == 0)
				FillBoxWithBitmap (hdc, 0, 0, 120, 120,&(pThis->m_pBmpArray[1]));//put bmp in button
			else
				FillBoxWithBitmap (hdc, 0, 0, 120, 120,&(pThis->m_pBmpArray[12]));
		}
		
		EndPaint(hWnd, hdc);
		
		//return 0; //can not return 
	}

	return (*m_btnProc)(hWnd, message, wParam, lParam);
}

int  MainFrame::onCreate(HWND hWnd,WPARAM wParam, LPARAM lParam){

	MainFrame *pThis = getInstance();

	/*GRIDVIEWDATA gridViewData;
	gridViewData.nr_rows = 1;
	gridViewData.nr_cols = 7;
	gridViewData.row_height = 36;
	gridViewData.col_width  = 60;

	CreateWindowEx(CTRL_GRIDVIEW, "Grid_View", WS_CHILD | WS_VISIBLE , WS_EX_NONE, IDC_CTRL_MAINFRAME_GRIDVIEW,\
		0, 0, 800, 36, hWnd, (DWORD)&gridViewData);
	*/
	m_hWndInMainFrame[0] = CreateWindow(CTRL_BUTTON, " ", WS_CHILD | WS_VISIBLE , IDC_CTRL_MAINFRAME_ONE, 190, 190, 120, 120, hWnd, 0);
	m_btnProc = SetWindowCallbackProc(m_hWndInMainFrame[0], defButtonProc);
	m_hWndInMainFrame[1] = CreateWindow(CTRL_BUTTON, " ", WS_CHILD | WS_VISIBLE , IDC_CTRL_MAINFRAME_TWO, 340, 190, 120, 120, hWnd, 0);
	SetWindowCallbackProc(m_hWndInMainFrame[1], defButtonProc);
	m_hWndInMainFrame[2] = CreateWindow(CTRL_BUTTON, " ", WS_CHILD | WS_VISIBLE , IDC_CTRL_MAINFRAME_THREE, 490, 190, 120, 120, hWnd, 0);
	SetWindowCallbackProc(m_hWndInMainFrame[2], defButtonProc);
	
	m_hWndInMainFrame[3] = CreateWindow (CTRL_BUTTON, "ONE", WS_CHILD | WS_VISIBLE | BS_BITMAP, IDC_CTRL_MAINFRAME_TWO, 0, 0, 60, 36, hWnd, (DWORD)(&(pThis->m_pBmpArray[3])));
	//SetWindowCallbackProc(m_hWndInMainFrame[3], defButtonProc);

	m_hWndInMainFrame[4] = CreateWindow (CTRL_BUTTON, "TWO", WS_CHILD | WS_VISIBLE | BS_BITMAP, IDC_CTRL_MAINFRAME_FOUR, 60, 0, 60, 36, hWnd, (DWORD)(&(pThis->m_pBmpArray[4])));
	//SetWindowCallbackProc(m_hWndInMainFrame[4], defButtonProc);
	
	m_hWndInMainFrame[5] = CreateWindow (CTRL_BUTTON, "THREE", WS_CHILD | WS_VISIBLE | BS_BITMAP, IDC_CTRL_MAINFRAME_FIVE, 120, 0, 60, 36, hWnd, (DWORD)(&(pThis->m_pBmpArray[5])));
	//SetWindowCallbackProc(m_hWndInMainFrame[5], defButtonProc);
	
	m_hWndInMainFrame[6] = CreateWindow (CTRL_BUTTON, "FOUR", WS_CHILD | WS_VISIBLE | BS_BITMAP, IDC_CTRL_MAINFRAME_SIX, 180, 0, 60, 36, hWnd, (DWORD)(&(pThis->m_pBmpArray[6])));
	//SetWindowCallbackProc(m_hWndInMainFrame[6], defButtonProc);
	
	m_hWndInMainFrame[7] = CreateWindow (CTRL_BUTTON, "FIVE", WS_CHILD | WS_VISIBLE | BS_BITMAP, IDC_CTRL_MAINFRAME_SEVEN, 240, 0, 60, 36, hWnd, (DWORD)(&(pThis->m_pBmpArray[7])));
	//SetWindowCallbackProc(m_hWndInMainFrame[7], defButtonProc);
	
	m_hWndInMainFrame[8] = CreateWindow (CTRL_BUTTON, "SIX", WS_CHILD | WS_VISIBLE | BS_BITMAP, IDC_CTRL_MAINFRAME_EIGHT, 300, 0, 60, 36, hWnd, (DWORD)(&(pThis->m_pBmpArray[8])));
	//SetWindowCallbackProc(m_hWndInMainFrame[8], defButtonProc);
	
	m_hWndInMainFrame[9] = CreateWindow (CTRL_BUTTON, "SEVEN", WS_CHILD | WS_VISIBLE | BS_BITMAP, IDC_CTRL_MAINFRAME_NINE, 360, 0, 60, 36, hWnd, (DWORD)(&(pThis->m_pBmpArray[9])));
	//SetWindowCallbackProc(m_hWndInMainFrame[9], defButtonProc);
	return 0;
}

int  MainFrame::onCommand (WPARAM wParam, LPARAM lParam){
	int id = LOWORD(wParam);

	switch (id)
	{
		case IDC_CTRL_MAINFRAME_ONE:
			LOG_PRINT ("push botton\r\n");
			break;
	}
	return 0;
}

int  MainFrame::onPaint (HWND hWnd, WPARAM wParam, LPARAM lParam){
	//HDC hdc;

	//hdc = BeginPaint (hWnd);
	
	//FillBoxWithBitmap (hdc, 190, 190, 120, 120, &m_pBmpArray[0]);
	
	//FillBoxWithBitmap (hdc, 340, 190, 120, 120, &m_pBmpArray[1]);	
	
	//EndPaint(hWnd,hdc);

	
	return 0;
}

int MainFrame::onKeyDown(WPARAM wParam, LPARAM lParam){
	//int keyCode;
	//keyCode = LOWORD(wParam);//To get key code
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
	    ::ScreenToClient(pMf->m_hMainFrame, &rcTemp.left, &rcTemp.top);
	    ::ScreenToClient(pMf->m_hMainFrame, &rcTemp.right, &rcTemp.bottom);
	    ::IncludeClipRect(hdc, &rcTemp);
	}else
	    ::GetClientRect(pMf->m_hMainFrame, &rcTemp);

	::FillBoxWithBitmap(hdc, 0, 36/*TASKWND_HEIGHT*/, RECTW(rcTemp), RECTH(rcTemp), pMf->m_pBmpBkGnd);
	::ReleaseDC(hdc);

	EXIT_FUNCTION;
	return 0;

}

void MainFrame::onClose (){
	
}

void MainFrame::cleanUp() {
	ENTER_FUNCTION;
	::UnloadBitmap(m_pBmpBkGnd);
	unregisterMainFrameControl ();
	releaseInstance();
	EXIT_FUNCTION;
}
