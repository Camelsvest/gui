#include <stdlib.h>
#include "navigatorpage.h"

NavigatorPage::NavigatorPage(const char *pszTitle, HICON hIcon)
    : m_title(pszTitle)
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

int NavigatorPage::onPaint(WPARAM wParam, LPARAM lParam)
{
    DWORD mainColor;
    RECT rc;    
    HDC hdc;

    if (getClientRect(rc))
    {
        hdc = beginPaint();
        mainColor = getWindowElementAttr(WE_MAINC_THREED_BODY);
        rc.top += 1;
        rc.left += 1;
        rc.right -= 1;
        rc.bottom -= 1;
        
        getWindowElementRender()->draw_3dbox(hdc, &rc, mainColor, LFRDR_BTN_STATUS_NORMAL);

        endPaint(hdc);        
    }

    return 0;
}


