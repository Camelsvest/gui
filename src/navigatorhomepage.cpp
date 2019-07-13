#include <assert.h>
#include "navigatorres.h"
#include "navigatorskin.h"
#include "navigatorhomepage.h"

NavigatorHomePage::NavigatorHomePage(const char *pszTitle, HICON hIcon)
    : NavigatorPage(pszTitle, hIcon)
    , m_btnAudioMemoHome(HWND_INVALID)
    , m_btnOpenGate(HWND_INVALID)
    , m_btnOpenDoor(HWND_INVALID)
{
}

NavigatorHomePage::~NavigatorHomePage()
{
}

int NavigatorHomePage::onCreate(WPARAM wParam, LPARAM lParam)
{
    initSkins();

    m_btnAudioMemoHome = createSubWindow(CTRL_BUTTON, "", WS_VISIBLE | BS_PUSHBUTTON,
        WS_EX_NONE, IDC_NAVIGATOR_HOMEPAGE_AUDIOMEMO, 20, 20, 140, 140, "Audio Memo");
    assert(m_btnAudioMemoHome != HWND_INVALID);

    ::SetWindowElementAttr(m_btnAudioMemoHome, WE_LFSKIN_PUSHBUTTON, 
        (DWORD)NAVIGATOR_SKIN_HOME_PAGE_BTN_AUDIOMEMO);
    
    setButtonWndProc(m_btnAudioMemoHome);
    
    return 0;
}

int NavigatorHomePage::initSkins()
{
    setWindowElementAttr(WE_LFSKIN_WND_BKGND, (DWORD)NAVIGATOR_SKIN_HOME_PAGE_BG);

    return 0;
}

