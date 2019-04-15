#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "statuswindow.h"
#include "debuglog.h"



StatusWindow:: StatusWindow():
			m_hStatusWnd(HWND_INVALID),
			m_pInstance(NULL){

}



StatusWindow::~StatusWindow(){
	if (m_pInstance){
		free (m_pInstance);
		m_pInstance = NULL;
	}
}



StatusWindow* StatusWindow::getInstance(){
	if (m_pInstance == NULL)
		m_pInstance = new StatusWindow();
	
	return m_pInstance;
}


int StatusWindow::StatusWndControlProc(HWND hWnd,int message,WPARAM wParam,LPARAM lParam ){
	return DefaultWindowProc(hWnd, message, wParam, lParam);
}

bool StatusWindow::registerStatusWindowControl(){
	return true;
	
}

