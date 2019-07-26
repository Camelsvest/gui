#include <assert.h>
#include "gui.h"
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
	
    ::SetDefaultWindowElementRenderer("skin");
	fprintf(stdout, "%s %s->ncsInitialize is invoked\r\n", __FILE__, __FUNCTION__);
	::ncsInitialize ();
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
	fprintf(stdout, "%s %s->ENTER FUNCTION\r\n", __FILE__, __FUNCTION__);
    if (m_pMainWindow)
    {
        ::MainWindowThreadCleanup((HWND)m_pMainWindow);
        
        delete m_pMainWindow;
        m_pMainWindow = NULL;
		fprintf(stdout, "%s %s->ncsUninitialize is invoked\r\n", __FILE__, __FUNCTION__);
		::ncsUninitialize ();
		
    }
	fprintf(stdout, "%s %s->EXIT FUNCTION\r\n", __FILE__, __FUNCTION__);
}
