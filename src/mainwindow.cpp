#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "mainwindow.h"
#include "debuglog.h"

MainWindow *MainWindow::m_pInstance = NULL;

MainWindow * MainWindow::getInstance()
{
	if (m_pInstance == NULL)
		m_pInstance = new MainWindow();

	return m_pInstance;	
}

MainWindow::MainWindow()
	: m_hMainWnd(HWND_INVALID)
{
}

MainWindow::~MainWindow()
{	
}

void MainWindow::releaseInstance()
{
	if (m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}


bool MainWindow::isCreatedWnd()
{
	return (m_hMainWnd != HWND_INVALID);
}

bool MainWindow::createWnd(int iLeft, int iTop, int iRight, int iBottom)
{
	MAINWINCREATE CreateInfo;
	bool bRet = false;
	ENTER_FUNCTION;
	if (m_hMainWnd == HWND_INVALID)
	{
		memset(&CreateInfo, 0, sizeof(CreateInfo));
		
		CreateInfo.dwStyle = WS_VISIBLE;
		CreateInfo.dwExStyle = WS_EX_CLIPCHILDREN;
		CreateInfo.spCaption = "";
		CreateInfo.hMenu = 0;
		CreateInfo.hCursor = ::GetSystemCursor(0);
		CreateInfo.hIcon = 0;
		CreateInfo.MainWindowProc = MainWindow::wndProc;
		CreateInfo.lx = iLeft;
		CreateInfo.ty = iTop;
		CreateInfo.rx = iRight;
		CreateInfo.by = iBottom;
		CreateInfo.iBkColor = COLOR_lightwhite;
		CreateInfo.dwAddData = 0;
		CreateInfo.hHosting = HWND_DESKTOP;
		m_hMainWnd = ::CreateMainWindow(&CreateInfo);
		if (m_hMainWnd != HWND_INVALID)
			bRet = true;
	}

	EXIT_FUNCTION;

	return bRet;
	
}

void MainWindow::destroyWnd(HWND hWnd)
{
	ENTER_FUNCTION;
	if (m_hMainWnd != HWND_INVALID)
	{
		if (TaskWindow::getInstance() != NULL)
			TaskWindow::getInstance()->cleanUp();
		
		if (MainFrame::getInstance() != NULL)
			MainFrame::getInstance()->cleanUp();
		
		if (StatusWindow::getInstance () != NULL)
			StatusWindow::getInstance ()->cleanUp();
		
		::DestroyAllControls(hWnd);
		::DestroyMainWindow(hWnd);
		::PostQuitMessage(hWnd);
	}
	EXIT_FUNCTION;
	return;
}

int MainWindow::wndProc(HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
	MainWindow *pThis = getInstance();
	
	switch(message)
	{
	case MSG_CREATE:
		pThis->onCreate(hWnd, wParam, lParam);
		break;

	case MSG_NCCREATE:
		break;

	case MSG_COMMAND:
		pThis->onCommand (wParam, lParam);
		break;
	case MSG_PAINT:
		pThis->onPaint(wParam, lParam);
		break;

	case MSG_CLOSE:
		LOG_PRINT ("MSG_CLOSE\r\n");
		if (MessageBox(hWnd, "Are you sure to qiut", "MessageBox", MB_YESNOCANCEL | MB_ICONQUESTION | MB_BASEDONPARENT) == IDYES)
			pThis->destroyWnd(hWnd);
		return 0;
	default:
		break;
	}

	return DefaultMainWinProc(hWnd, message, wParam, lParam);
}

int MainWindow::onCommand (WPARAM wParam, LPARAM lParam)
{
	return 0;
}

int MainWindow::onCreate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	bool bRet;

	bRet = TaskWindow::getInstance()->createTaskWindow(hWnd);
	if (!bRet){
		LOG_ERR("create task window failed.\r\n");
		return -1;
	}	
	
	bRet = MainFrame::getInstance()->createMainFrame (hWnd);
	if (!bRet){
		LOG_ERR("create main frame failed.\r\n");
		return -1;
	}

	bRet = StatusWindow::getInstance()->createStatusWindow(hWnd);
	if (!bRet){
		LOG_ERR ("create status window failed.\r\n");
		return -1;
	}
	return 0;
}

int MainWindow::onPaint(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

int MainWindow::run()
{
	MSG msg;
	int ret = -1;

	if (m_hMainWnd != HWND_INVALID)
	{
		while(::GetMessage(&msg, m_hMainWnd))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}

		ret = 0;
	}
	
	return ret;
}

void MainWindow::cleanUp(){
	if (m_hMainWnd != HWND_INVALID)
		::MainWindowThreadCleanup (m_hMainWnd);


	m_hMainWnd = HWND_INVALID;
	
}
