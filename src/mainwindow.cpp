#include <assert.h>
#include <stdlib.h>

#include "mainwindow.h"

MainWindow::MainWindow()
	: m_hMainWnd(HWND_INVALID)
{
}

MainWindow::~MainWindow()
{
}

bool MainWindow::Create(int iLeft, int iTop, int iRight, int iBottom)
{
	MAINWINCREATE CreateInfo;
	bool bRet = false;
	
	if (m_hMainWnd == NULL)
	{
		memset(&CreateInfo, 0, sizeof(CreateInfo));
		
		CreateInfo.dwStyle = WS_VISIBLE;
		CreateInfo.dwExStyle = WS_EX_CLIPCHILDREN;
		CreateInfo.spCaption = NULL;
		CreateInfo.hMenu = 0;
		CreateInfo.hCursor = ::GetSystemCursor(0);
		CreateInfo.hIcon = 0;
		CreateInfo.MainWindowProc = MainWindow::WndProc;
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

void MainWindow::Destroy()
{
	if (m_hMainWnd != HWND_INVALID)
	{
		::DestroyMainWindow(m_hMainWnd);
		::PostQuitMessage(m_hMainWnd);

		m_hMainWnd = HWND_INVALID;
	}

	return;
}

int MainWindow::WndProc(HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case MSG_CREATE:
		onCreate(wParam, lParam);
		break;

	case MSG_NCREATE:
		break;

	case MSG_PAINT:
		onPaint(wParam, lParam);
	}

	return ::DefaultMainWinProc(hWnd, message, wParam, lParam);
}

int MainWindow::onCreate(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

int MainWindow::onPaint(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

