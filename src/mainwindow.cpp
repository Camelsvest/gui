#include <string.h>
#include <stdexcept>

#include "mainwindow.h"
#include "navigatorres.h"
#include "logging.h"


MainWindow* MainWindow::m_pInstance = NULL;

NCS_EVENT_HANDLER MainWindow::m_mainHandlers [] = {
    {MSG_CREATE,        reinterpret_cast<void*>(MainWindow::main_onCreate)},
    {MSG_CLOSE,         reinterpret_cast<void*>(MainWindow::main_onClose)},
	{MSG_USER_DEF_1,    reinterpret_cast<void*>(MainWindow::main_onUser)},
    {0, NULL}
};

MainWindow::MainWindow()
    : m_hMainWnd(HWND_INVALID)
{
}

MainWindow::~MainWindow()
{
}

MainWindow* MainWindow::getInstance()
{
	if (m_pInstance == NULL)
		m_pInstance = new MainWindow();

	return m_pInstance;
}

void MainWindow::release()
{
    if (m_pInstance)
    {
        delete m_pInstance;
        m_pInstance = NULL;
    }
}

bool MainWindow::ncscreateMainWindow(
                    const char *pszCaption, HMENU hMenu, HCURSOR hCursor,
                    HICON hIcon, DWORD dwStyle, DWORD dwExStyle,
                    int x, int y, int w, int  h) {
    mWidget *widget;                
    ENTER_CLASS_FUNCTION("MainWindow");
    
    widget = ::ncsCreateMainWindow (
        NCSCTRL_MAINWND,
        pszCaption,
        dwStyle,
        dwExStyle,
        IDC_MAINWND, 
        x, y, w, h,
        HWND_DESKTOP,
        0, 0,
        NULL,
        NULL,
        m_mainHandlers,
        (DWORD)this);   // important !!!

    EXIT_CLASS_FUNCTION("MainWindow");

    if (widget != NULL)
    {
        m_hMainWnd = widget->hwnd;
        logging_trace("Create MainWindow: %p\r\n", m_hMainWnd);
        
        return true;
    }
    else
        return false;

}

bool MainWindow::ncscreate()
{
	return ncscreateMainWindow(
        "MainWindow",  
        NULL,
        GetSystemCursor(0),
        0, // hIcon
        WS_CAPTION | WS_BORDER | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_VISIBLE,
        0,  // dwExStyle
        0,
        0,
        SCREEN_W,
        SCREEN_H);
}

void MainWindow::ncsshowWindow(){
	MSG Msg;

    ENTER_CLASS_FUNCTION("MainWindow");
	if (m_hMainWnd == NULL)
		return;
	
	while (GetMessage (&Msg, m_hMainWnd)) {
        TranslateMessage (&Msg);
        DispatchMessage (&Msg);
    }

    EXIT_CLASS_FUNCTION("MainWindow");
}

void MainWindow::run()
{	
	ENTER_CLASS_FUNCTION("MainWindow");
    
	ncsshowWindow();

    EXIT_CLASS_FUNCTION("MainWindow");

    return;
}

void MainWindow::main_onUser (mWidget* self, int message, WPARAM wParam, LPARAM lParam)
{
	ENTER_CLASS_FUNCTION("MainWindow");

	EXIT_CLASS_FUNCTION("MainWindow");
	
	return;
}

BOOL MainWindow::main_onCreate(mWidget* self, DWORD dwAddData )
{   
    BOOL ret;
    MainWindow *pThis;
    
    ENTER_CLASS_FUNCTION("MainWindow");
    
	pThis = reinterpret_cast<MainWindow *>(dwAddData);
	ret = pThis->onCreate(self->hwnd);
    
    EXIT_CLASS_FUNCTION("MainWindow");
    
	return ret;
}

BOOL MainWindow::onCreate(HWND hWnd)
{
    RECT rc;
    GetClientRect(hWnd, &rc);

    if (!(m_Navigator.createWindow(hWnd, &rc)))
		return FALSE;
    return  m_InfoBarWindow.createWindow(hWnd, &rc) ? TRUE : FALSE;
}

BOOL MainWindow::main_onClose(mWidget* self, int message)
{
    ENTER_CLASS_FUNCTION("MainWindow");

    ::DestroyMainWindow(self->hwnd);
    ::PostQuitMessage(self->hwnd);

    EXIT_CLASS_FUNCTION("MainWindow");
    
    return TRUE;    
}

