#ifndef __MAINFRAME_H__
#define __MAINFRAME_H__

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#define MAINFRAME_CTRL_NAME "mainframe"
#define MAINFRAME_BKGND_PIC "res/content_bg.png"
#define MAINFRAME_BTN_BMP_NAME_1 "res/vdp_home_audiomemo.png"
#define MAINFRAME_BTN_BMP_NAME_2 "res/vdp_home_opendoor.png"
#define MAINFRAME_BTN_BMP_NAME_3 "res/vdp_home_opengate.png"


#define MAINFRAME_BMP_NUM 16

#define IDC_MAINFRAMEWND 2000
#define IDC_CTRL_MAINFRAME            180
#define IDC_CTRL_MAINFRAME_ONE        181
#define IDC_CTRL_MAINFRAME_TOW        182
#define IDC_CTRL_MAINFRAME_THREE        183



class MainFrame {
public:

     static MainFrame* getInstance();
     static void releaseInstance();
     
     bool createMainFrame(HWND hwnd);
     void cleanUp();
protected:
     MainFrame();
    virtual ~MainFrame();
    bool registerMainFrameControl();
    void unregisterMainFrameControl();
    int  onCreate(HWND hWnd, WPARAM wParam, LPARAM lParam);
    int  onCommand (WPARAM wParam, LPARAM lParam);
	int  onPaint(WPARAM wParam, LPARAM lParam);
    int  onEraseBkgnd(WPARAM wParam, LPARAM lParam);
    static int MainFrameCtlControlProc(HWND hWnd,int message,WPARAM wParam,LPARAM lParam);

private:
   static MainFrame *m_pInstance;
   HWND m_hMainFrame;
   HWND m_hMainWnd;
   BITMAP *m_pBmpBkGnd;
   BITMAP *m_pBmpArray[16];
};
#endif
