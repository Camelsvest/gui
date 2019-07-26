#include <stdexcept>
#include "ctrlwnd.h"
#include "registeredwndclasses.h"

CtrlWnd::CtrlWnd(const char *pszWndClassName)
    : m_wndClassName(pszWndClassName)
{  
    int refCount;
    RegisteredWndClasses *instance = RegisteredWndClasses::getInstance();
    if (instance)
    {            
        refCount = instance->addRefWndClass(pszWndClassName);
        if (refCount == 1)  // first time
        {
            if (!registerWndClass(pszWndClassName))
            {
                std::string msg;
                msg = "Failed to register wndClass: ";
                msg += pszWndClassName;

                throw new std::logic_error(msg);
            }
        }
    }
}

CtrlWnd::~CtrlWnd()
{
    RegisteredWndClasses *instance = RegisteredWndClasses::getInstance();
    if (instance)
    {
        instance->releaseWndClass(m_wndClassName.c_str());
    }
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


