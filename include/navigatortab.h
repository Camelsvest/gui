#ifndef _NAVIGATOR_TAB_H_
#define _NAVIGATOR_TAB_H_

#include "ctrlwnd.h"

class NavigatorTab : public CtrlWnd
{
public:
	NavigatorTab();
	virtual ~NavigatorTab();

protected:
    virtual int onCreate(WPARAM wParam, LPARAM lParam);
    virtual int onDraw(HDC hdc);
};

#endif
