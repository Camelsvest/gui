#include <assert.h>
#include <stdexcept>
#include "navigator.h"
#include "navigatorres.h"
#include "logging.h"

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
    RECT rc, rcTab, rcPage;    
    NavigatorPage *activatePage;
        
    if (!getClientRect(&rc))
        return -1;
    else
        logging_trace("Client size %d, %d, %d, %d.\r\n", rc.left, rc.top, rc.right, rc.bottom);
    
    assert(m_nvgtTab == NULL);

    rcTab.top = 5;
    rcTab.left = 5;
    rcTab.right = rc.right - 5;
    rcTab.bottom = DEFAULT_TAB_HEIGHT - 5;
    
    m_nvgtTab = new NavigatorTab;
    succeed = m_nvgtTab->createWindow(IDC_NAVIGATOR_TAB,  rcTab.left, rcTab.top, rcTab.right - rcTab.left, rcTab.bottom - rcTab.top, getHandle());
    if (!succeed)
        return -1;
    else
    {
        logging_trace("Succeed to create \"NavigatorTab\" @(%d, %d, %d, %d)\r\n",
            rcTab.left, rcTab.top, rcTab.right, rcTab.bottom);
    }
    
    rcPage.left = 5;
    rcPage.top = DEFAULT_TAB_HEIGHT + 5;
    rcPage.right = rc.right - 5;
    rcPage.bottom = rc.bottom - 5;
    
    activatePage = *m_ActivatePageIterator;
    if (activatePage)
    {
        succeed = activatePage->createWindow(IDC_NAVIGATOR_PAGE2, rcPage.left, rcPage.top, rcPage.right - rcPage.left, rcPage.bottom - rcPage.top, getHandle());
        if (!succeed)
            return -1;
        else
        {
            logging_trace("Succeed to create \"NavigatorPage\" @(%d, %d, %d, %d)\r\n",
                rcPage.left, rcPage.top, rcPage.right - rcPage.left, rcPage.bottom - rcPage.top);
        }
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


