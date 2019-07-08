#ifndef _NAVIGATOR_PAGE_H_
#define _NAVIGATOR_PAGE_H_

#include <string>
#include "wnd.h"

class NavigatorPage : public Wnd {
public:
    NavigatorPage(const char *pszTitle, HICON hIcon);
    virtual ~NavigatorPage();

    const char * getTitle() { return m_title.c_str(); }
    HICON getIcon() { return m_icon; }

protected:
    virtual int onCreate(WPARAM wParam, LPARAM lParam);
    virtual int onPaint(WPARAM wParam, LPARAM lParam);

protected:
    std::string m_title;
    HICON       m_icon;
};

#endif
