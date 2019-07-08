#include "navigator.h"

Navigator::Navigator()
    : m_ActivatePageIterator(m_nvgtPageList.end())
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
    HWND hwnd = getHandle();
    HDC hdc = ::BeginPaint(hwnd);

    ret = onDraw(hdc);
    ::EndPaint(hwnd, hdc);

    return ret;
}

int Navigator::onDraw(HDC hdc)
{
    RECT rc;
    DWORD mainColor;
    HWND hwnd = getHandle();

    mainColor = ::GetWindowElementAttr (hwnd, WE_MAINC_THREED_BODY);

    if (getClientRect(rc))
    {
        rc.bottom = 50;
        ((WINDOWINFO*)GetWindowInfo (hwnd))->we_rdr->draw_3dbox(hdc, 
            &rc, mainColor, LFRDR_BTN_STATUS_NORMAL);
    }

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

