#ifndef __STATUSWINDOW__
#define __STATUSWINDOW__

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#define STATUSWND_CTRL_NAME "statuswindow"
#define STATUSWND_HEIGHT 30
class StatusWindow {
    public:

        StatusWindow * getInstance();
        bool createStatusWindow();

    protected:
        StatusWindow ();
        ~StatusWindow ();

        bool registerStatusWindowControl();
        
        static int StatusWndControlProc(HWND hWnd,int message,WPARAM wParam,LPARAM lParam );

     private:
        HWND m_hStatusWnd;
        HWND m_hMainWnd;
        StatusWindow *m_pInstance;
        
};

#endif
