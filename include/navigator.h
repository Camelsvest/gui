#ifndef _NAVIGATOR_H_
#define _NAVIGATOR_H_

#include <list>
#include "navigatorpage.h"
#include "navigatortab.h"

#define MSG_NVGT_BASEINDEX	(MSG_USER + 1000)

#define IDC_PROPSHEET 100
#define IDC_SYSINFO     101
#define IDC_REFRESH     102

#define ID_BUTTON_0 200
#define ID_BUTTON_1 201
#define ID_BUTTON_2 202
#define ID_BUTTON_3 203


#define ID_SPINBOX_ONE 300
#define ID_SPINBOX_TWO 301

#define ID_PANEL_GROUP_0 400
#define ID_PANEL_GROUP_1 401


#define PAGE_FIRST  	1
#define PAGE_SECOND     2
#define PAGE_THIRD  	3
#define PAGE_FOUR       4
#define PAGE_FIVE       5


#define CTRL_NAVIGATOR  ("NVGTCTRL")

class Navigator : public CtrlWnd {

public:
    Navigator();    
    Navigator(mMainWnd* mainwnd);
    
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
    
    mPropSheet *m_propsheet;
};

#endif
