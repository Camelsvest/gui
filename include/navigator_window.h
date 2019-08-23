#ifndef _NAVIGATOR_WINDOW_H_
#define _NAVIGATOR_WINDOW_H_

#include "global.h"
#include "navigator.h"

#define BTN_INTERVAL 20
#define BTN_W 140
#define BTN_H 140
#define NGT_TITLE_H 80

class NavigatorWindow      {
public:
    NavigatorWindow();
    virtual ~NavigatorWindow();
    
	bool createWindow(HWND hMainWnd, RECT *rc);
    
	enum NAVIGATOR_BMP_INDEX {
				AUDIODEMO_BMP_INDEX = 0,
		        OPENGATE_BMP_INDEX,
			    OPENDOOR_BMP_INDEX,
				BACKGROUD_BMP_INDEX,
					
				NAVIGATOR_BMP_MAX = 7
			};
	static NCS_EVENT_HANDLER m_btnHandlers[];
protected:
    static void page_onInitPage(mWidget* self, DWORD add_data);
    static int page_onShowPage(mWidget* self, HWND hwnd, int show_cmd);
    static int page_onSheetCmd(mWidget* self, DWORD wParam, DWORD lParam);
    static void page_onDestroy(mWidget* self, DWORD wParam, DWORD lParam);

	static BOOL btn_Cb (mMainWnd *self, mButton *sender, int id, DWORD param);
	static int btn_onDown (mWidget* self, DWORD wParam, DWORD lParam);
	static int btn_onUp (mWidget* self, DWORD wParam, DWORD lParam);
	static void btn_onPaint (mWidget *self, HDC hdc, const CLIPRGN* inv);
	static int page_onEraseBkGndPage(mWidget* self, HDC hdc, const RECT *rc);

private:
    void onInitPage(mWidget* self, int pageType);
	void loadRes ();
	void unloadRes ();
	bool registerAllPictures();
	void unregisterAllPictures();
    
private:   
    mNavigator *m_navigator;
	static mPropSheet *m_propsheet;

	static NCS_EVENT_HANDLER m_pageHandlers[];
	static NCS_EVENT_HANDLER m_pageHandlers_second[];

	static char* navigator_img_path[NAVIGATOR_BMP_MAX];
	static PBITMAP m_navigatorBmp[NAVIGATOR_BMP_MAX];
	static HWND m_hBtn[6];

    typedef struct _mPageData
    {
        NavigatorWindow   *pThis;
        DWORD       data;           
    } mPageData;
};

#endif
