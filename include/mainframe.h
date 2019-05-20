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
#define MAINFRAME_BTN_BMP_NAME_4 "res/vdp_home_audiomemo_over.png"
#define MAINFRAME_BTN_BMP_NAME_5 "res/vdp_home_opendoor_over.png"
#define MAINFRAME_BTN_BMP_NAME_6 "res/vdp_home_opengate_over.png"
#define MAINFRAME_BTN_BMP_NAME_7 "res/vdp_tab_icon_00.png"
#define MAINFRAME_BTN_BMP_NAME_8 "res/vdp_tab_icon_00s.png"
#define MAINFRAME_BTN_BMP_NAME_9 "res/vdp_tab_icon_01.png"
#define MAINFRAME_BTN_BMP_NAME_11 "res/vdp_tab_icon_02.png"
#define MAINFRAME_BTN_BMP_NAME_13 "res/vdp_tab_icon_03.png"
#define MAINFRAME_BTN_BMP_NAME_15 "res/vdp_tab_icon_04.png"
#define MAINFRAME_BTN_BMP_NAME_17 "res/vdp_tab_icon_05.png"
#define MAINFRAME_BTN_BMP_NAME_19 "res/vdp_tab_icon_06.png"


#define MAINFRAME_BMP_NUM 32

#define IDC_MAINFRAMEWND 2000
#define IDC_CTRL_MAINFRAME            180
#define IDC_CTRL_MAINFRAME_ONE        (IDC_CTRL_MAINFRAME + 1)
#define IDC_CTRL_MAINFRAME_TWO        (IDC_CTRL_MAINFRAME + 2)
#define IDC_CTRL_MAINFRAME_THREE      (IDC_CTRL_MAINFRAME + 3)
#define IDC_CTRL_MAINFRAME_FOUR       (IDC_CTRL_MAINFRAME + 4)
#define IDC_CTRL_MAINFRAME_FIVE       (IDC_CTRL_MAINFRAME + 5)
#define IDC_CTRL_MAINFRAME_SIX        (IDC_CTRL_MAINFRAME + 6)
#define IDC_CTRL_MAINFRAME_SEVEN      (IDC_CTRL_MAINFRAME + 7)
#define IDC_CTRL_MAINFRAME_EIGHT      (IDC_CTRL_MAINFRAME + 8)
#define IDC_CTRL_MAINFRAME_NINE       (IDC_CTRL_MAINFRAME + 9)

#define IDC_CTRL_MAINFRAME_GRIDVIEW   (IDC_CTRL_MAINFRAME + 10)

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
	int  onPaint(HWND hWnd, WPARAM wParam, LPARAM lParam);
    int  onEraseBkgnd(WPARAM wParam, LPARAM lParam);
    int  onKeyDown(WPARAM wParam,LPARAM lParam);
    void onClose();
    
    static int mainFrameCtlControlProc(HWND hWnd,int message,WPARAM wParam,LPARAM lParam);
    static int defButtonProc (HWND hwnd, int message, WPARAM wParam, LPARAM lParam);

private:
   static MainFrame *m_pInstance;
   static WNDPROC m_btnProc;
   HWND m_hMainFrame;
   HWND m_hWndInMainFrame[16];
   HWND m_hMainWnd;
   BITMAP *m_pBmpBkGnd;
   BITMAP m_pBmpArray[16];
   
};
#endif
