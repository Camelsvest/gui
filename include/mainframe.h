#ifndef __MAINFRAME_H__
#define __MAINFRAME_H__

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#define MAINFRAME_CTRL_NAME "mainframe"
#define MAINFRAME_BKGND_PIC "res/content_bg.png"
#define IDC_MAINFRAMEWND 2000


class MainFrame {
public:

     static MainFrame* getInstance();
     bool createMainFrame(HWND hwnd);
     void cleanUp();
protected:
     MainFrame();
    virtual ~MainFrame();
    bool registerMainFrameControl();
    void unregisterMainFrameControl();
    int  onCreate(WPARAM wParam, LPARAM lParam);
    int  onCommand (WPARAM wParam, LPARAM lParam);
	int  onPaint(WPARAM wParam, LPARAM lParam);
    int  onEraseBkgnd(WPARAM wParam, LPARAM lParam);
    static int MainFrameCtlControlProc(HWND hWnd,int message,WPARAM wParam,LPARAM lParam);

private:
   static MainFrame *m_pInstance;
   HWND m_hMainFrame;
   HWND m_hMainWnd;
   BITMAP *m_pBmpBkGnd;
};
#endif
