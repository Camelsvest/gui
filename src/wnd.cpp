#include <assert.h>
#include <wnd.h>

Wnd::Wnd()
    : m_hWnd(HWND_INVALID)
{
}

Wnd::~Wnd()
{
}

bool Wnd::createMainWindow(const char *pszCaption, HMENU hMenu,
    HCURSOR hCursor, HICON hIcon, DWORD dwStyle, DWORD dwExStyle,
    int x, int y, int w, int  h)
{
    HWND hMainWnd;
    MAINWINCREATE CreateInfo;
    bool ret = false;

    if (getHandle() == HWND_INVALID)
    {
        CreateInfo.dwStyle = dwStyle;     
        CreateInfo.dwExStyle = dwExStyle;
        CreateInfo.spCaption = pszCaption;
        CreateInfo.hMenu = hMenu;
        CreateInfo.hCursor = hCursor;
        CreateInfo.hIcon = hIcon;
        CreateInfo.MainWindowProc = Wnd::wndProc;
        CreateInfo.lx = x;
        CreateInfo.ty = y;
        CreateInfo.rx = w;
        CreateInfo.by = h;
        CreateInfo.iBkColor = COLOR_lightgray; 
        CreateInfo.dwAddData = (DWORD)this;
        CreateInfo.hHosting = HWND_DESKTOP;

        hMainWnd = ::CreateMainWindow(&CreateInfo);    // m_hMainWnd shall be assigned in mainWindowProc

        ret = (hMainWnd != HWND_INVALID);
    }

    return ret;    
}

bool Wnd::createWindow(const char *pszWndClassName, const char *pszCaption,
    DWORD dwStyle, DWORD dwExStyle, int id, int x, int y, int w, int  h, 
    HWND hParentWnd)
{
    HWND hWnd;

    hWnd = ::CreateWindowEx(pszWndClassName, pszCaption, dwStyle, dwExStyle, id, x, y, w, h, hParentWnd, (DWORD)this);
    return (hWnd != HWND_INVALID);        
}

int	Wnd::messageBox(const char *pszText, const char *pszCaption, DWORD dwStyle)
{
    return ::MessageBox(m_hWnd, pszText, pszCaption, dwStyle);
}

bool Wnd::showWindow()
{
    MSG Msg;
    
    if (m_hWnd == HWND_INVALID)
        return false;

    if (GetParent(m_hWnd) != 0)
        return false;
    
    while (::GetMessage (&Msg, getHandle()) ) {
        ::TranslateMessage (&Msg);
        ::DispatchMessage (&Msg);
    }

    return true;
}


int Wnd::wndProc(HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
    Wnd *pThis;

    pThis = (Wnd *)(::GetWindowAdditionalData(hWnd));
    if (pThis != NULL)
    {
        if (pThis->m_hWnd == HWND_INVALID)
            pThis->m_hWnd = hWnd;
        
        return pThis->wndProc(message, wParam, lParam);    
    }

    return -1;
}

int Wnd::wndProc(int message, WPARAM wParam, LPARAM lParam)
{
    int ret = 0;
    
    switch (message)
    {
    case MSG_CREATE:
        ret = onCreate(wParam, lParam);
        break;
        
    case MSG_CLOSE:
        ret = onClose(wParam, lParam);
        break;

    case MSG_MAXIMIZE:
        ret = onMaximize(wParam, lParam);
        break;

    case MSG_SHOWWINDOW:
        ret = onShowWindow(wParam, lParam);
        break;
            
    default:
        ret = DefaultMainWinProc(m_hWnd, message, wParam, lParam);
        break;
    }


    return ret;
}

int Wnd::onClose(WPARAM wParam, LPARAM lparam)
{
    ::DestroyMainWindow(m_hWnd);
    ::PostQuitMessage(m_hWnd);

    return 0;    
}

int Wnd::onMaximize(WPARAM wParam, LPARAM lparam)
{
    assert(false);

    return -1;
}

int Wnd::onShowWindow(WPARAM wParam, LPARAM lParam)
{
    assert(false);
    return -1;
}

