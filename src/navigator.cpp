#include "navigator.h"

#define DEFAULT_TAB_HEIGHT  48

Navigator::Navigator()
    : m_tabHeight(DEFAULT_TAB_HEIGHT)
    , m_ActivatePageIterator(m_nvgtPageList.end())
{
}

Navigator::~Navigator()
{
}

int Navigator::wndProc(int message, WPARAM wParam, LPARAM lParam)
{
    int ret = 0;
    
    switch (message)
    {
    case MSG_CREATE:
        ret = onCreate(wParam, lParam);
        break;

    case MSG_PAINT:
        ret = onPaint(wParam, lParam);
        break;
        
    case MSG_NVGT_ADDPAGE:
        ret = onAddPage(wParam, lParam);
        break;

    case MSG_NCPAINT:        
    default:
        ret = DefaultMainWinProc(getHandle(), message, wParam, lParam);
        break;
    }


    return ret;    
}

int Navigator::onCreate(WPARAM wParam, LPARAM lParam)
{
    
    return 0;
}

int Navigator::onPaint(WPARAM wParam, LPARAM lParam)
{
    int ret;
    HDC hdc = beginPaint();

    ret = onDraw(hdc);
    endPaint(hdc);

    return ret;
}

int Navigator::onDraw(HDC hdc)
{
    int ret;

    ret = drawTabBar(hdc);
    if (ret == 0)
        drawActivatePage(hdc);

    return 0;
}

int Navigator::drawTabBar(HDC hdc)
{
    RECT rc;
    DWORD mainColor;
    
    if (!getClientRect(rc))
        return -1;
        
    if (rc.bottom < m_tabHeight)
        return -1;

    mainColor = getWindowElementAttr(WE_MAINC_THREED_BODY);
    rc.bottom = m_tabHeight;
    
    getWindowElementRender()->draw_3dbox(hdc, &rc, mainColor, LFRDR_BTN_STATUS_NORMAL);

    return 0;
}

int Navigator::drawActivatePage(HDC hdc)
{
    return 0;
}

int Navigator::onAddPage(WPARAM wParam, LPARAM lParam)
{
    bool activated;
    NavigatorPage *page;

    page = (NavigatorPage *)lParam;
    m_nvgtPageList.push_back(page);

    activated = (wParam != 0);

    if (!activated)
        m_ActivatePageIterator = m_nvgtPageList.begin();
    else
        m_ActivatePageIterator = --m_nvgtPageList.end(); // current page is activated
        
    return 0;
}

bool Navigator::registerNavigatorControl()
{
    WNDCLASS wndClass;

    wndClass.spClassName = CTRL_NAVIGATOR;
    wndClass.dwStyle     = WS_NONE;
    wndClass.dwExStyle   = WS_EX_NONE;
    wndClass.hCursor     = GetSystemCursor (0);
    wndClass.iBkColor    = GetWindowElementPixel (HWND_NULL, WE_MAINC_THREED_BODY);
    wndClass.WinProc     = Wnd::wndProc;

    return (::RegisterWindowClass (&wndClass) == TRUE);
}

void Navigator::unregisterNavigatorControl()
{
    ::UnregisterWindowClass(CTRL_NAVIGATOR);
}

