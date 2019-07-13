#ifndef _NAVIGATOR_H_
#define _NAVIGATOR_H_

#include <list>
#include "navigatorpage.h"
#include "navigatortab.h"

#define MSG_NVGT_BASEINDEX	(MSG_USER + 1000)

#define CTRL_NAVIGATOR  ("NVGTCTRL")

class Navigator : public CtrlWnd {

public:
    Navigator();
    virtual ~Navigator();

	bool addPage(NavigatorPage *page, bool activated = true);
	bool delPage(NavigatorPage *page);
	
protected:
	virtual int wndProc(int message, WPARAM wParam, LPARAM lParam);
    virtual int onCreate(WPARAM wParam, LPARAM lParam);

	int onInitSkin(WPARAM wParam, LPARAM lParam);

private:
	bool registerAllPictures();
	void unregisterAllPictures();
    
private:
	NavigatorTab *m_nvgtTab;
	
	typedef std::list<NavigatorPage *> NvgtPageList;
	NvgtPageList			m_nvgtPageList;
	NvgtPageList::iterator	m_ActivatePageIterator;
};

#endif
