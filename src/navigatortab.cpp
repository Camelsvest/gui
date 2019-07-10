#include "navigatortab.h"

#define CTRL_NAVIGATOR_TAB  ("NVGTCTRL_TAB")

NavigatorTab::NavigatorTab()
    : CtrlWnd(CTRL_NAVIGATOR_TAB)
{
}

NavigatorTab::~NavigatorTab()
{
}

int NavigatorTab::onCreate(WPARAM wParam, LPARAM lParam)
{
   // return DefaultMainWinProc(getHandle(), MSG_PAINT, wParam, lParam);
   return 0;
}

int NavigatorTab::onDraw(HDC hdc)
{
    RECT rc;
    DWORD mainColor;
    
    if (!getClientRect(rc))
        return -1;
        
    mainColor = getWindowElementAttr(WE_MAINC_THREED_BODY);
     
    getWindowElementRender()->draw_3dbox(hdc, &rc, mainColor, LFRDR_BTN_STATUS_NORMAL);
  
    return 0;
}