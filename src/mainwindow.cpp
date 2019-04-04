#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "mainwindow.h"

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
	
	if (m_hMainWnd == HWND_INVALID)
	{
		memset(&CreateInfo, 0, sizeof(CreateInfo));
		
		CreateInfo.dwStyle = WS_VISIBLE;
		CreateInfo.dwExStyle = WS_EX_CLIPCHILDREN;
		CreateInfo.spCaption = NULL;
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

	return bRet;
	
}

void MainWindow::destroyWnd()
{
	if (m_hMainWnd != HWND_INVALID)
	{
		::DestroyMainWindow(m_hMainWnd);
		::PostQuitMessage(m_hMainWnd);

		m_hMainWnd = HWND_INVALID;
	}

	return;
}

int MainWindow::wndProc(HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
	MainWindow *pThis = getInstance();
	
	switch(message)
	{
	case MSG_CREATE:
		pThis->onCreate(wParam, lParam);
		break;

	case MSG_NCCREATE:
		break;

	case MSG_PAINT:
		pThis->onPaint(wParam, lParam);
		break;

	default:
		break;
	}

	return DefaultMainWinProc(hWnd, message, wParam, lParam);
}

int MainWindow::onCreate(WPARAM wParam, LPARAM lParam)
{
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
