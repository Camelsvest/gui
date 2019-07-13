#include <assert.h>
#include <stdexcept>
#include "navigator.h"
#include "navigatorres.h"
#include "navigatorskin.h"
#include "navigatorhomepage.h"
#include "logging.h"


#define DEFAULT_TAB_HEIGHT  48


static char *nvgtAllPictures[] = 
{
    NAVIGATOR_SKIN_TAB_BG,
    NAVIGATOR_SKIN_PAGE_BG,
    NAVIGATOR_SKIN_HOME_PAGE_BG,
    NAVIGATOR_SKIN_HOME_PAGE_BTN_AUDIOMEMO
};

Navigator::Navigator()
    : CtrlWnd(CTRL_NAVIGATOR)
    , m_nvgtTab(NULL)
    , m_ActivatePageIterator(m_nvgtPageList.end())
{
    NavigatorPage *page;

    if (!registerAllPictures())
        throw new std::invalid_argument("Failed to register all pictures.");

    page = new NavigatorPage("Page1", 0);
    if (page == NULL)
        throw new std::runtime_error("Failed to allocate memory for NavigatorPage: Page1.");
    addPage(page);
    
    page = new NavigatorHomePage("Page2", 0);
    if (page == NULL)
        throw new std::runtime_error("Failed to allocate memory for NavigatorPage: Page2.");

    addPage(page, true);

}

Navigator::~Navigator()
{
    NvgtPageList::iterator itera;
    NavigatorPage *page;
    
    for (itera = m_nvgtPageList.begin(); itera != m_nvgtPageList.end(); itera++)
    {
        page = *itera;
        delete page;
    }
    
    unregisterAllPictures();
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

    case MSG_INIT_SKIN:
        ret = onInitSkin(wParam, lParam);
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

    return sendMessage(MSG_INIT_SKIN, 0, 0);
   
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

bool Navigator::registerAllPictures()
{
    unsigned int i;
    
    bool ret = true;
    
    if (0 == ::SetResPath("./res/"))
    {
        for (i = 0; i < sizeof(nvgtAllPictures)/sizeof(nvgtAllPictures[0]); i++)
        {
            if (::RegisterResFromFile(HDC_SCREEN, nvgtAllPictures[i]) == FALSE)
            {
                logging_error("Failed to register resource: %s.\r\n", nvgtAllPictures[i]);
                ret = false;
                break;
            }
        }
    }
    else
    {
        logging_error("Failed to register path for resource files.\r\n");
        ret = false;
    }

    return ret;
}

void Navigator::unregisterAllPictures()
{
    unsigned int i;

    for (i = 0; i < sizeof(nvgtAllPictures)/sizeof(nvgtAllPictures[0]); i++)
    {
        ::UnregisterRes(nvgtAllPictures[i]);
    }
}

int Navigator::onInitSkin(WPARAM wParam, LPARAM lParam)
{
    setWindowElementAttr(WE_LFSKIN_WND_BKGND, (DWORD)NAVIGATOR_SKIN_PAGE_BG);
    return 0;
}

