#ifndef _NAVIGATOR_PAGE_H_
#define _NAVIGATOR_PAGE_H_

#include <string>
#include "ctrlwnd.h"

class NavigatorPage : public CtrlWnd {
public:
    NavigatorPage(const char *pszTitle, HICON hIcon);
    virtual ~NavigatorPage();

    const char * getTitle() { return m_title.c_str(); }
    HICON getIcon() { return m_icon; }
	
protected:
    virtual int onCreate(WPARAM wParam, LPARAM lParam);
    virtual int onDraw(HDC hdc);

protected:
    std::string m_title;
    HICON       m_icon;
};

#endif
