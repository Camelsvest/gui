#ifndef _NAVIGATOR_H_
#define _NAVIGATOR_H_

#include <list>
#include "navigatorpage.h"

#define MSG_NVGT_BASEINDEX	(MSG_USER + 1000)
#define MSG_NVGT_ADDPAGE	(MSG_NVGT_BASEINDEX + 1)
#define MSG_NVGT_DELPAGE	(MSG_NVGT_BASEINDEX + 2)

#define CTRL_NAVIGATOR  ("NVGTCTRL")

class Navigator : public Wnd {

public:
    Navigator();
    virtual ~Navigator();

    static bool registerNavigatorControl();
    static void unregisterNavigatorControl();

protected:
	virtual int wndProc(int message, WPARAM wParam, LPARAM lParam);
    virtual int onCreate(WPARAM wParam, LPARAM lParam);
	virtual int onPaint(WPARAM wParam, LPARAM lParam);
	virtual int onAddPage(WPARAM wParam, LPARAM lParam);

private:
    virtual int onDraw(HDC hdc);
	
private:
    int	m_tabHeiht;

	typedef std::list<NavigatorPage *> NvgtPageList;
	NvgtPageList			m_nvgtPageList;
	NvgtPageList::iterator	m_ActivatePageIterator;
};

#endif
