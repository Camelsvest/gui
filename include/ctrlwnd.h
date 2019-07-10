#ifndef _CTRL_WND_H_
#define _CTRL_WND_H_

#include <string>
using namespace std;

#include "wnd.h"

class CtrlWnd : public Wnd {
public:
	CtrlWnd(const char *pszWndClassName);
	virtual ~CtrlWnd();

	bool createWindow(int id, int left, int top, int width, int height, HWND hParent);

private:
	int m_nRefCount;
	std::string m_wndClassName;
};

#endif
