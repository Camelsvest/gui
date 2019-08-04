#include <assert.h>
#include "gui.h"
#include "vdpskin.h"
#include "trace.h"

GUI::GUI()
	: m_pMainWindow(NULL)
{
}

GUI::~GUI()
{
	if (m_pMainWindow)
	    m_pMainWindow->release();
}

bool GUI::init()
{
    bool ret = false;
             
    ::ncsInitialize ();
    ::ncsInitVDPSkinRenderers();

    //    ::SetDefaultWindowElementRenderer("skin");
    
    if (m_pMainWindow == NULL)
    {
        m_pMainWindow = MainWindow::getInstance();
        ret = m_pMainWindow->ncscreate();
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
        ::MainWindowThreadCleanup(m_pMainWindow->handle());
        
        m_pMainWindow->release();
        m_pMainWindow = NULL;

        ::ncsUninitVDPSkinRenderers();
    	logging_trace("ncsUninitialize is invoked\r\n");       
    	::ncsUninitialize ();	
    }

}
