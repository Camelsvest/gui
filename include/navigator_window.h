#ifndef _NAVIGATOR_WINDOW_H_
#define _NAVIGATOR_WINDOW_H_

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#include <mgncs/mgncs.h>
#include "navigator.h"


#define MSG_NVGT_BASEINDEX	(MSG_USER + 1000)


#define IDC_SYSINFO     101
#define IDC_REFRESH     102

#define ID_BUTTON_0 200
#define ID_BUTTON_1 201
#define ID_BUTTON_2 202
#define ID_BUTTON_3 203


#define ID_SPINBOX_ONE 300
#define ID_SPINBOX_TWO 301

#define ID_PANEL_GROUP_0 400
#define ID_PANEL_GROUP_1 401


#define PAGE_FIRST  	1
#define PAGE_SECOND     2
#define PAGE_THIRD  	3
#define PAGE_FOUR       4
#define PAGE_FIVE       5


class NavigatorWindow      {

public:
    NavigatorWindow();
    virtual ~NavigatorWindow();
    
	bool createWindow(HWND hMainWnd, RECT *rc);
    
protected:
    static void page_onInitPage(mWidget* self, DWORD add_data);
    static int page_onShowPage(mWidget* self, HWND hwnd, int show_cmd);
    static int page_onSheetCmd(mWidget* self, DWORD wParam, DWORD lParam);
    static void page_onDestroy(mWidget* self, DWORD wParam, DWORD lParam);

private:
    void onInitPage(mWidget* self, int pageType);
    
	bool registerAllPictures();
	void unregisterAllPictures();
    
private:   
    mNavigator *m_navigator;

    static NCS_EVENT_HANDLER m_pageHandlers[];

    typedef struct _mPageData
    {
        NavigatorWindow   *pThis;
        DWORD       data;           
    } mPageData;

	BITMAP m_bmpAudioMemo;   

};

#endif
