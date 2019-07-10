#include <stdexcept>
#include "ctrlwnd.h"

CtrlWnd::CtrlWnd(const char *pszWndClassName)
    : m_nRefCount(0)
    , m_wndClassName(pszWndClassName)
{  
    if (m_nRefCount <= 0)
    {
        if (!registerWndClass(m_wndClassName.c_str()))
        {
            std::string str;
            str = "Failed to register wndClass: ";
            str += m_wndClassName;
            throw new std::logic_error(str);
        }
    }
    ++m_nRefCount;    
}

CtrlWnd::~CtrlWnd()
{
    --m_nRefCount;
    if (m_nRefCount <= 0)
        unregisterWndClass(m_wndClassName.c_str());
}

bool CtrlWnd::createWindow(int id, int left, int top, int width, int height, HWND hParent)
{
    return Wnd::createWindow(
            m_wndClassName.c_str(),
            "",
            WS_CHILD | WS_VISIBLE | WS_BORDER,
            0,
            id,
            left,
            top,
            width,
            height,
            hParent);
}


