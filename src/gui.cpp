#include <assert.h>
#include "gui.h"
#include "vdpskin.h"
#include "logging.h"

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
             
    ::ncsInitialize ();
    ::ncsInitVDPSkinRenderers();

    //    ::SetDefaultWindowElementRenderer("skin");
    
    if (m_pMainWindow == NULL)
    {
#ifndef USE_MNCS		
        m_pMainWindow = new MainWindow();
        ret = m_pMainWindow->create();
#else
        m_pMainWindow = MainWindow::getInstance();
        ret = m_pMainWindow->ncscreate();
#endif
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

	logging_trace("ncsUninitialize is invoked\r\n");
	::ncsUninitialize ();	
    }

}
