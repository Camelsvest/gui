#ifndef _NAVIGATOR_HOME_PAGE_H_
#define _NAVIGATOR_HOME_PAGE_H_

#include "navigatorpage.h"

class NavigatorHomePage : public NavigatorPage
{
public:
    NavigatorHomePage(const char *pszTitle, HICON hIcon);
    virtual ~NavigatorHomePage();

protected:
    virtual int onCreate(WPARAM wParam, LPARAM lParam);


        
private:
    int initSkins();
    
private:
    HWND    m_btnAudioMemoHome;
    HWND    m_btnOpenGate;
    HWND    m_btnOpenDoor;

};

#endif
