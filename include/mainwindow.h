#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include "wnd.h"
#include "navigator.h"

#define USE_MNCS

class MainWindow : public Wnd {
public:
	MainWindow();
	virtual ~MainWindow();
    static MainWindow* getInstance();
    Navigator * getM_nvgt();
    void        setM_nvgt(Navigator* nvgt);
    mWidget*    getMwidget();
	bool create();
    bool ncscreate();
    bool ncscreateMainWindow(const char *pszCaption, HMENU hMenu,
        HCURSOR hCursor, HICON hIcon, DWORD dwStyle, DWORD dwExStyle,
        int x, int y, int w, int  h);
    
    void ncsshowWindow();
    void run();
    
protected:
	int onCreate(WPARAM wParam, LPARAM lParam);
	int onShowWindow(WPARAM wParam, LPARAM lParam);
    int onClose(WPARAM wParam, LPARAM lParam);

private:
    HMENU createMenu();
    HMENU createMenuFile();
    HMENU createMenuAbout();
    
    
private:
    static MainWindow* m_pInstance;
    HWND	m_hMainWnd;
	HWND 	m_hMLEditWnd;

    mWidget* m_wMainWnd;
	Navigator *m_nvgt;
	
};


#endif
