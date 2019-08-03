#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include "wnd.h"
#include "navigator.h"

class MainWindow {
public:
    static MainWindow* getInstance();
    static void release();
    
    bool ncscreate();
    bool ncscreateMainWindow(const char *pszCaption, HMENU hMenu,
        HCURSOR hCursor, HICON hIcon, DWORD dwStyle, DWORD dwExStyle,
        int x, int y, int w, int  h);
    
    void ncsshowWindow();
    void run();

    HWND handle() { return m_hMainWnd; }
    
protected:   
	MainWindow();
	virtual ~MainWindow();

    BOOL onCreate(HWND hParent);

    static BOOL main_onCreate(mWidget* self, DWORD dwAddData );
    static BOOL main_onClose(mWidget* self, int message);

private:
    HMENU createMenu();
    HMENU createMenuFile();
    HMENU createMenuAbout();
    
    
private:
    Navigator m_Navigator;
    
    HWND m_hMainWnd;
    static MainWindow* m_pInstance;
    static NCS_EVENT_HANDLER m_mainHandlers[];

};


#endif
