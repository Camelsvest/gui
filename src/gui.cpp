#include <assert.h>
#include <stdio.h>
#include "gui.h"
#include "debuglog.h"
GUI::GUI()
	: m_pMainWindow(NULL)
{
}

GUI::~GUI()
{
	if (m_pMainWindow)
		m_pMainWindow->releaseInstance();
}

bool GUI::init()
{
	bool ret = false;
	ENTER_FUNCTION;
	if (m_pMainWindow == NULL)
	{
		m_pMainWindow = MainWindow::getInstance();
		if (m_pMainWindow)
		{
		    if (!::ServerStartup (0, 0, 0))
			{
		        fprintf(stderr, "Can not start the server of MiniGUI-Processes.\n");		        
		    }
			else
			{
				ret = true;
				LOG_PRINT("server start up successed.\r\n");
			}
		}
	}
	OUT_FUNCTION;
	return ret;
}

int GUI::run()
{
	int ret = -1;

	ENTER_FUNCTION;
	
	if (m_pMainWindow != NULL)
	{	
		if (m_pMainWindow->createWnd(0, 0, 800, 600))
			ret = m_pMainWindow->run();
	}
	
	OUT_FUNCTION;
	
	return ret;
}

void GUI::uninit(){
	if (m_pMainWindow != NULL){
		m_pMainWindow->cleanUp();
	}
}

