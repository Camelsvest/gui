#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "taskwindow.h"
#include "debuglog.h"

TaskWindow *TaskWindow::m_pInstance = NULL;

TaskWindow::TaskWindow(){

}

TaskWindow::~TaskWindow(){
}

TaskWindow* TaskWindow::getInstance(){
	
	if (m_pInstance == NULL)
		m_pInstance = new TaskWindow();

	return m_pInstance;
}

void TaskWindow::releaseInstance(){
		if (m_pInstance){
		delete m_pInstance;
		m_pInstance = NULL;
	}
}

int TaskWindow::taskWndControlProc(HWND hWnd,int message,WPARAM wParam,LPARAM lParam ){
	TaskWindow *pThis = getInstance();
	switch (message){

		case MSG_CREATE:
			pThis->onCreate(hWnd, wParam, lParam);
			break;
		case MSG_COMMAND:
			pThis->onCommand(wParam, lParam);
			break;
		case MSG_PAINT:
			pThis->onPaint(wParam,lParam);
			break;
		case MSG_CLOSE:
			pThis->onClose();
			return 0;
		default:
			break;

	}
	return DefaultWindowProc(hWnd, message, wParam, lParam);
}
bool TaskWindow::createTaskWindow(HWND hwnd){
	RECT rc;
	
	ENTER_FUNCTION; 
	
	registerTaskWindowControl();
	::GetWindowRect(hwnd, &rc);
	m_hTaskWnd = ::CreateWindow(TASKWND_CTRL_NAME, "", WS_CHILD | WS_VISIBLE, IDC_TASKWND, rc.left, rc.top, rc.right, TASKWND_HEIGHT, hwnd, 0);
	m_hMainWnd = hwnd;
	EXIT_FUNCTION;
	return true;
}

bool TaskWindow::registerTaskWindowControl(){
	WNDCLASS TskWinCtl;

    TskWinCtl.spClassName = TASKWND_CTRL_NAME;
    TskWinCtl.dwStyle     = WS_NONE;
    TskWinCtl.dwExStyle   = WS_EX_NONE;
    TskWinCtl.hCursor     = ::GetSystemCursor(0);
    TskWinCtl.iBkColor    = ::GetWindowElementColor (WE_MAINC_THREED_BODY); ;
    TskWinCtl.WinProc     = taskWndControlProc;

    return ::RegisterWindowClass(&TskWinCtl); 
}

void TaskWindow::unregisterTaskWindowControl(){
	::UnregisterWindowClass(TASKWND_CTRL_NAME);
}

int TaskWindow::onCreate(HWND hWnd,WPARAM wParam, LPARAM lParam){
	
	::CreateWindow(CTRL_BUTTON, TASKWND_BTN_EXIT, WS_CHILD | WS_VISIBLE /*| WS_EX_TRANSPARENT*/, IDC_EXIT, 0, 0, 60, TASKWND_HEIGHT, hWnd, 0);
	return 0;
}

int TaskWindow::onCommand (WPARAM wParam, LPARAM lParam){ 
	int id = LOWORD(wParam);
	int code = HIWORD(wParam);
	switch (id){
		case IDC_EXIT:
			if (code == BN_CLICKED)
			{
				::SendMessage(m_hTaskWnd, MSG_CLOSE, 0, 0L);
			}
			break;	
			
	}
	return 0;
}

int TaskWindow::onPaint(WPARAM wParam, LPARAM lParam){
	ENTER_FUNCTION;

	EXIT_FUNCTION;
	return 0;
}

void TaskWindow::onClose(){
	ENTER_FUNCTION;
	
	::SendMessage(m_hMainWnd, MSG_CLOSE, 0, 0L); //发送给主窗口
	
	EXIT_FUNCTION;
}

void TaskWindow::cleanUp(){
	ENTER_FUNCTION;
	m_hTaskWnd = HWND_INVALID;
	getInstance()->unregisterTaskWindowControl();
	getInstance()->releaseInstance();
	EXIT_FUNCTION;
}

