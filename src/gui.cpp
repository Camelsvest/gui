#include <assert.h>
#include "gui.h"

GUI::GUI()
	: m_pMainWindow(NULL)
{
}

GUI::~GUI()
{
	if (m_pMainWindow)
		delete m_pMainWindow;
}

bool GUI::init()
{
    bool ret = false;

    ::SetDefaultWindowElementRenderer("skin");

    if (m_pMainWindow == NULL)
    {
        m_pMainWindow = new MainWindow();
        ret = m_pMainWindow->create();
    }

    return ret;
}

int GUI::run()
{
    if (m_pMainWindow)
    {
        m_pMainWindow->run();
        return 0;
    }

    return -1;
}

void GUI::uninit()
{
    if (m_pMainWindow)
    {
        ::MainWindowThreadCleanup((HWND)m_pMainWindow);
        
        delete m_pMainWindow;
        m_pMainWindow = NULL;
    }
}
