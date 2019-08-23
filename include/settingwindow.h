#ifndef __SETTING_WINDOW_H__

#define __SETTING_WINDOW_H__

#include "global.h"

#define SETTING_WND_X 0
#define SETTING_WND_Y 0

#define SETTING_WND_W 200
#define SETTING_WND_H 100

class SettingWindow {
	
	public:
		SettingWindow ();
	    ~SettingWindow ();
	protected:

    private:
		
		HWND m_hwnd;

};
#endif
