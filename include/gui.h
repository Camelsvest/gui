#ifndef _GUI_H_
#define _GUI_H_

#include "mainwindow.h"

class GUI {
public:
	GUI();
	virtual ~GUI();

    bool    init();
    int     run();

private:
    MainWindow* m_pMainWindow;
};

#endif
