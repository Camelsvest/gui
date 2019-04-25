#ifndef __TASKWINDOW_H__
#define __TASKWINDOW_H__

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#define TASKWND_CTRL_NAME "taskwindow"
#define TASKWND_HEIGHT    30
#define TASKWND_BTN_EXIT "Exit"
#define IDC_TASKWND 1000
#define IDC_EXIT 1001



class TaskWindow {
public:
    
        static TaskWindow* getInstance();
        static void releaseInstance();
        bool createTaskWindow(HWND hwnd);
        void cleanUp();
protected:
        TaskWindow();
        virtual  ~TaskWindow();
        bool registerTaskWindowControl();
        void unregisterTaskWindowControl();
        int onCreate(HWND hWnd, WPARAM wParam, LPARAM lParam);
        int onCommand (WPARAM wParam, LPARAM lParam);
	    int onPaint(WPARAM wParam, LPARAM lParam);
        void onClose ();
        static int taskWndControlProc(HWND hWnd,int message,WPARAM wParam,LPARAM lParam );
private:
       static TaskWindow *m_pInstance;
       HWND m_hTaskWnd;
       HWND m_hMainWnd;
        
};


#endif
