#ifndef __STATUSWINDOW__
#define __STATUSWINDOW__

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#define STATUSWND_CTRL_NAME "statuswindow"
#define STATUSWND_HEIGHT 30

#define IDC_CTRL_STATUSWND 480

#define IDC_CTRL_STATUSWND_ONE (IDC_CTRL_STATUSWND + 1) 
#define IDC_CTRL_STATUSWND_TWO (IDC_CTRL_STATUSWND + 2)
#define IDC_CTRL_STATUSWND_THREE (IDC_CTRL_STATUSWND + 3)

class StatusWindow {
    public:

        static StatusWindow * getInstance();
        bool createStatusWindow(HWND hWnd);
        void cleanUp ();

    protected:
        StatusWindow ();
        ~StatusWindow ();

        bool registerStatusWindowControl();
        void unregisterStatusWindowControl();
        
        static int StatusWndControlProc(HWND hWnd,int message,WPARAM wParam,LPARAM lParam );
        void onCreate (HWND hWnd, WPARAM wParam, LPARAM lParam);
        void onCommand (WPARAM wParam, LPARAM lParam);
	    void onPaint(HWND hWnd, WPARAM wParam, LPARAM lParam);
        void onClose ();
     private:
        HWND m_hStatusWnd;
        HWND m_hMainWnd;
        static StatusWindow *m_pInstance;
        
};

#endif
