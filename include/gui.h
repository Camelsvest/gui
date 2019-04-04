#ifndef _GUI_H_
#define _GUI_H_

#include "mainwindow.h"

class GUI {
public:
	GUI();
	virtual ~GUI();

private:
    MainWindow* m_pMainWindow;
};

#endif
