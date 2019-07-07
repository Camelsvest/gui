#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include "wnd.h"

class MainWindow : public Wnd {
public:
	MainWindow();
	virtual ~MainWindow();

	bool create();
    void run();
    
protected:
	int onCreate(WPARAM wParam, LPARAM lParam);
	int onShowWindow(WPARAM wParam, LPARAM lParam);
    int onClose(WPARAM wParam, LPARAM lParam);

private:
    HMENU createMenu();
    HMENU createMenuFile();
    HMENU createMenuAbout();
    
private:
	HWND	m_hMainWnd;
	HWND 	m_hMLEditWnd;
};


#endif
