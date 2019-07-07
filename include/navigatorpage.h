#ifndef _NAVIGATOR_PAGE_H_
#define _NAVIGATOR_PAGE_H_

#include "wnd.h"

class NavigatorPage : public Wnd {
public:
    NavigatorPage();
    virtual ~NavigatorPage();

protected:
    virtual int onCreate(WPARAM wParam, LPARAM lParam);

protected:
    char    *m_title;
    HICON   m_icon;    
};

#endif
