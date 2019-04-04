#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

class MainWindow {
public:
    MainWindow();
    virtual ~MainWindow();

    bool        Create(int iLeft,int iTop,int iRight,int iBottom)(int iLeft, int iTop, int iRight, int iBottom);
	void        Destroy();

protected:
	static int	WndProc(HWND hWnd, int message, WPARAM wParam, LPARAM lParam);

	int         onCreate(WPARAM wParam, LPARAM lParam);
	int         onPaint(WPARAM wParam, LPARAM lParam);
	
private:
    HWND            m_hMainWnd;
};

#endif
