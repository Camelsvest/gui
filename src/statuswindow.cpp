#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "statuswindow.h"
#include "debuglog.h"

StatusWindow *StatusWindow::m_pInstance = NULL;

StatusWindow:: StatusWindow():
			m_hStatusWnd(HWND_INVALID){

}



StatusWindow::~StatusWindow(){
}



StatusWindow* StatusWindow::getInstance(){
	if (m_pInstance == NULL)
		m_pInstance = new StatusWindow();
	
	return m_pInstance;
}

bool StatusWindow::createStatusWindow(HWND hWnd){
	bool bRet;
	RECT rc;
	
	ENTER_FUNCTION;
	
	bRet = registerStatusWindowControl();
	if (!bRet)
		return false;

	GetWindowRect(hWnd, &rc);

	m_hStatusWnd = ::CreateWindow(STATUSWND_CTRL_NAME, "", WS_VISIBLE | WS_CHILD, IDC_CTRL_STATUSWND, rc.left, \
			rc.bottom - STATUSWND_HEIGHT, rc.right, STATUSWND_HEIGHT, hWnd, 0L);
	if (m_hStatusWnd == HWND_INVALID)
		bRet = false;

	EXIT_FUNCTION;
	return bRet;
}


int StatusWindow::StatusWndControlProc(HWND hWnd,int message,WPARAM wParam,LPARAM lParam ){
	StatusWindow * pThis = getInstance();
	
	switch (message)
	{
		case MSG_CREATE:
			pThis->onCreate (hWnd, wParam, lParam);		
			break;

		 case MSG_PAINT:
		 	pThis->onPaint (hWnd, wParam, lParam);
			//return 0;
		 	break;

		 case MSG_COMMAND:
		 	pThis->onCommand(wParam, lParam);
		 	break;
	}
	return DefaultWindowProc(hWnd, message, wParam, lParam);
}

bool StatusWindow::registerStatusWindowControl(){
	bool bRet;
	WNDCLASS StatusWndCtl;
	
    StatusWndCtl.spClassName = STATUSWND_CTRL_NAME;
    StatusWndCtl.dwStyle     = WS_NONE;
    StatusWndCtl.dwExStyle   = WS_EX_NONE;
    StatusWndCtl.hCursor     = GetSystemCursor(0);
    StatusWndCtl.iBkColor    = COLOR_lightwhite;
    StatusWndCtl.WinProc     = StatusWndControlProc;

    bRet = RegisterWindowClass(&StatusWndCtl);
	return bRet;
	
}

void StatusWindow::unregisterStatusWindowControl(){
	::UnregisterWindowClass (STATUSWND_CTRL_NAME);
}

void StatusWindow::onCreate(HWND hWnd,WPARAM wParam,LPARAM lParam){
	int pos;

	ENTER_FUNCTION;
	pos = (g_rcScr.right - 216)/2 ; 
	
	CreateWindow(CTRL_BUTTON, "Next>>", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CHECKED, IDC_CTRL_STATUSWND_ONE, (g_rcScr.right - pos -72), 4, 64, 20, hWnd, 0);
	
	CreateWindow(CTRL_BUTTON, "Home", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CHECKED, IDC_CTRL_STATUSWND_ONE, (g_rcScr.right - pos -72 - 72), 4, 64, 20, hWnd, 0);
	
	CreateWindow(CTRL_BUTTON, "Back<<", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CHECKED, IDC_CTRL_STATUSWND_ONE, (g_rcScr.right - pos -72 - 72 - 72), 4, 64, 20, hWnd, 0);	

	EXIT_FUNCTION;
}

void StatusWindow::onCommand(WPARAM wParam,LPARAM lParam){

}

void StatusWindow::onPaint(HWND hWnd,WPARAM wParam,LPARAM lParam){
	
}

void StatusWindow::cleanUp (){
	ENTER_FUNCTION;
	unregisterStatusWindowControl ();

	if (m_pInstance){
		free (m_pInstance);
		m_pInstance = NULL;
	}
	EXIT_FUNCTION;
	
}


