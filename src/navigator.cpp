#include <assert.h>
#include <stdexcept>
#include "navigator.h"
#include "navigatorres.h"

#define DEFAULT_TAB_HEIGHT  48

Navigator::Navigator()
    : CtrlWnd(CTRL_NAVIGATOR)
    , m_nvgtTab(NULL)
    , m_ActivatePageIterator(m_nvgtPageList.end())
{
    NavigatorPage *page;

    page = new NavigatorPage("Page1", 0);
    addPage(page);

    page = new NavigatorPage("Page2", 0);
    addPage(page);
}

Navigator::~Navigator()
{
}

int Navigator::wndProc(int message, WPARAM wParam, LPARAM lParam)
{
    int ret = 0;
    
    switch (message)
    {
    case MSG_CREATE:
        ret = onCreate(wParam, lParam);
        break;

    case MSG_PAINT:
        ret = onPaint(wParam, lParam);
        break;
        
    case MSG_NCPAINT:        
    default:
        ret = DefaultMainWinProc(getHandle(), message, wParam, lParam);
        break;
    }


    return ret;    
}

int Navigator::onCreate(WPARAM wParam, LPARAM lParam)
{
    bool succeed;
    RECT rc;    
    NavigatorPage *activatePage;
        
    if (!getClientRect(&rc))
        return -1;

    assert(m_nvgtTab == NULL);
    m_nvgtTab = new NavigatorTab;
    succeed = m_nvgtTab->createWindow(IDC_NAVIGATOR_TAB, 0, 0, rc.right, DEFAULT_TAB_HEIGHT, getHandle());
    if (!succeed)
        return -1;
    

    activatePage = *m_ActivatePageIterator;
    if (activatePage)
    {
        succeed = activatePage->createWindow(IDC_NAVIGATOR_PAGE2, 0, DEFAULT_TAB_HEIGHT+1, rc.right, rc.bottom, getHandle());
        if (!succeed)
            return -1;
    }
        
    return 0;
}

bool Navigator::addPage(NavigatorPage *page, bool activated)
{
    m_nvgtPageList.push_back(page);

    if (!activated)
        m_ActivatePageIterator = m_nvgtPageList.begin();
    else
        m_ActivatePageIterator = --m_nvgtPageList.end(); // current page is activated
        
    return true;
}

bool Navigator::delPage(NavigatorPage *page)
{
    m_nvgtPageList.remove(page);
    return true;
}


