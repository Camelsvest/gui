#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

class MainWindow {
public:
    static MainWindow * getInstance();
    static void releaseInstance();
    
    bool        isCreatedWnd();
    bool        createWnd(int iLeft,int iTop,int iRight,int iBottom);
	void        destroyWnd();

    int         run();

protected:
    MainWindow();
    virtual ~MainWindow();
    
	static int	wndProc(HWND hWnd, int message, WPARAM wParam, LPARAM lParam);

	int         onCreate(WPARAM wParam, LPARAM lParam);
	int         onPaint(WPARAM wParam, LPARAM lParam);
	
private:
    HWND                m_hMainWnd;
    static MainWindow   *m_pInstance;
};

#endif
