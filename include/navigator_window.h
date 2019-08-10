#ifndef _NAVIGATOR_WINDOW_H_
#define _NAVIGATOR_WINDOW_H_

#include "global.h"
#include "navigator.h"
class NavigatorWindow      {

public:
    NavigatorWindow();
    virtual ~NavigatorWindow();
    
	bool createWindow(HWND hMainWnd, RECT *rc);
    
	        enum NAVIGATOR_BMP_INDEX {
			AUDIODEMO_BMP_INDEX = 0,
			BACKGROUD_BMP_INDEX,
			
			NAVIGATOR_BMP_MAX
			};
protected:
    static void page_onInitPage(mWidget* self, DWORD add_data);
    static int page_onShowPage(mWidget* self, HWND hwnd, int show_cmd);
    static int page_onSheetCmd(mWidget* self, DWORD wParam, DWORD lParam);
    static void page_onDestroy(mWidget* self, DWORD wParam, DWORD lParam);

	static int page_onEraseBkGndPage(mWidget* self, HDC hdc, const RECT *rc);
private:
    void onInitPage(mWidget* self, int pageType);
	void loadRes ();
	void unloadRes ();
	bool registerAllPictures();
	void unregisterAllPictures();
    
private:   
    mNavigator *m_navigator;
    static NCS_EVENT_HANDLER m_pageHandlers[];
	static char* navigator_img_path[NAVIGATOR_BMP_MAX];
	static PBITMAP m_navigatorBmp[NAVIGATOR_BMP_MAX];

    typedef struct _mPageData
    {
        NavigatorWindow   *pThis;
        DWORD       data;           
    } mPageData;
};

#endif
