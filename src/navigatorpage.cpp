#include <stdlib.h>
#include <stdexcept>
#include "navigatorpage.h"

#define CTRL_NAVIGATOR_PAGE  ("NVGTCTRL_PAGE")

NavigatorPage::NavigatorPage(const char *pszTitle, HICON hIcon)
    : CtrlWnd(CTRL_NAVIGATOR_PAGE)
    , m_title(pszTitle)
    , m_icon(hIcon)
{
}

NavigatorPage::~NavigatorPage()
{
}

int NavigatorPage::onCreate(WPARAM wParam, LPARAM lParam)
{
    return 0;   
}

int NavigatorPage::onDraw(HDC hdc)
{
    DWORD mainColor;
    RECT rc;    

    if (getClientRect(rc))
    {
        mainColor = getWindowElementAttr(WE_MAINC_THREED_BODY);
        rc.top += 5;
        rc.left += 5;
        rc.right -= 5;
        rc.bottom -= 5;
        
        getWindowElementRender()->draw_3dbox(hdc, &rc, mainColor, LFRDR_BTN_STATUS_NORMAL);
    }

    return 0;
}


