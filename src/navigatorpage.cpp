#include <stdlib.h>
#include <stdexcept>
#include "navigatorskin.h"
#include "navigatorpage.h"

#define CTRL_NAVIGATOR_PAGE  ("NVGTCTRL_PAGE")

WNDPROC NavigatorPage::m_btnDefaultWndProc = NULL;

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
    initSkins();
    return 0;   
}

int NavigatorPage::onDraw(HDC hdc)
{
    DWORD mainColor;
    RECT rc;    

    if (getClientRect(rc))
    {
        mainColor = getWindowElementAttr(WE_MAINC_THREED_BODY);
        
        getWindowElementRender()->draw_3dbox(hdc, &rc, mainColor, LFRDR_BTN_STATUS_NORMAL);
    }

    return 0;
}

int NavigatorPage::initSkins()
{
    setWindowElementAttr(WE_LFSKIN_WND_BKGND, (DWORD)NAVIGATOR_SKIN_PAGE_BG);
    return 0;
}

int NavigatorPage::defaultButtonProc(HWND hwnd, int message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case MSG_ERASEBKGND:
        return 0;
    default:
        if (m_btnDefaultWndProc)
            return m_btnDefaultWndProc(hwnd, message, wParam, lParam);
        else
            return 0;
    }
}

void NavigatorPage::setButtonWndProc(HWND hButton)
{
    m_btnDefaultWndProc = ::SetWindowCallbackProc(hButton, NavigatorPage::defaultButtonProc);
}


