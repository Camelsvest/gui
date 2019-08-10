#include <assert.h>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include "mainwindow.h"
#include "infobarwindow.h"
#include "logging.h"


// image
static const char* infobar_img_path[] =
{
    "res/tux.png",
    "res/usb.png",
    "res/realplayer.png",
    "res/prev.png",
    "res/play.png",
    "res/next.png",
    "res/pause.png"
};

static const char* caption[] = {                                                                                                                                    
 "0", "1", "2", "3", "4", "5","6", "7", "8", "9"
};

static const char* hint[] =
{
   "Picture 0", "Picture 1", "Picture 2", "Picture 3", "Picture 4", 
   "Picture 5", "Picture 6", "Picture 7", "Picture 8", "Picture 9"
};

static NCS_WND_TEMPLATE ncsCtrls[] = {
    {
        NCSCTRL_STATIC,
        IDC_PROMPT,
        0, 0, 120, 40,
        WS_VISIBLE,
        WS_EX_NONE,
        "test...",
        NULL,
        NULL,
        NULL,
        NULL,
        0,
        0
    }
};	

InfoBarWindow::InfoBarWindow():m_hWnd(HWND_INVALID)
{
	
}


InfoBarWindow::~InfoBarWindow()
{
	unloadRes();
	unregisterCtrlClass();
}


BOOL InfoBarWindow::createWindow (HWND hwnd, RECT *rc)
{
	ENTER_CLASS_FUNCTION(CUSTOM_CTRL_NAME);
	
	loadRes();
	registerCtrClass();
	
	m_hWnd = ::CreateWindow(CUSTOM_CTRL_NAME, "", 
				   WS_CHILD | WS_VISIBLE, IDC_CUSTOM_TOOL,
				   rc->left, rc->bottom - INFOBAR_H, rc->right, INFOBAR_H, 
				   hwnd, (DWORD)this);
	
	if (m_hWnd == HWND_INVALID)
		return FALSE;

	EXIT_CLASS_FUNCTION(CUSTOM_CTRL_NAME);
	return TRUE;
	
}

BOOL InfoBarWindow::ncscreateWindow(HWND hwnd, RECT *rc)
{

	logging_trace("rc.left=%d, rc.top=%d, rc.right=%d, rc.bottom=%d\r\n",  rc->left, rc->top, rc->right, rc->bottom);

	
	mContainer *container = (mContainer *)ncsCreateWindow (NCSCTRL_CONTAINER,
							"Container",
							WS_BORDER | WS_VISIBLE,
							WS_EX_NONE,
							IDC_CONTAINER,
							rc->left, rc->bottom - INFOBAR_H, rc->right, INFOBAR_H, hwnd,
							NULL, NULL, container_handlers, 0);
	if (container ==NULL)
		return FALSE;
		
	_c(container)->addChildren(container, ncsCtrls,
                sizeof(ncsCtrls)/sizeof(NCS_WND_TEMPLATE));

	
	return TRUE;
}

LRESULT InfoBarWindow::CustomControlProc(HWND hWnd, UINT message,WPARAM wParam,LPARAM lParam)
{	
	InfoBarWindow * pb = NULL;
	switch (message){
		
		case MSG_CREATE:
			pb = reinterpret_cast<InfoBarWindow *>(lParam);
			logging_trace("%s %s %d->MSG_CREATE\r\n", __FILE__, __FUNCTION__, __LINE__);
			pb->onCreate(hWnd);
			pb = NULL;
			break;
	
		default:
			break;
			//logging_trace("%s %s %d\r\n", __FILE__, __FUNCTION__, __LINE__);
	}
		
	
	return ::DefaultWindowProc(hWnd, message, wParam, lParam);
}

BOOL InfoBarWindow::registerCtrClass()
{
	WNDCLASS cc;

    cc.spClassName = CUSTOM_CTRL_NAME;
    cc.dwStyle     = WS_NONE;
    cc.dwExStyle   = WS_EX_NONE;
    cc.hCursor     = ::GetSystemCursor(0);
    cc.iBkColor    = ::GetWindowElementColor (WE_MAINC_THREED_BODY); ;
    cc.WinProc     = CustomControlProc;

    return ::RegisterWindowClass(&cc); 
}
void InfoBarWindow::unregisterCtrlClass()
{
	::UnregisterWindowClass(CUSTOM_CTRL_NAME);
}


void InfoBarWindow::loadRes ()
{
	for (int i = 0; i < TB_MAX; ++i)
		m_infobarBmp[i] = (PBITMAP) LoadResource(infobar_img_path[i], RES_TYPE_IMAGE, (DWORD)HDC_SCREEN);
}

void InfoBarWindow::unloadRes ()
{
    for (int i = 0; i < TB_MAX; ++i)
    	ReleaseRes(Str2Key(infobar_img_path[i]));
}

void InfoBarWindow::onCreate(HWND hWnd)
{
	RECT rc;
	COOLBARITEMINFO item; 
	int i;
	HWND m_hToolBar;

	GetClientRect (hWnd, &rc);
	ENTER_CLASS_FUNCTION(CUSTOM_CTRL_NAME);
	
	logging_trace("rc.left=%d, rc.top=%d, rc.right=%d, rc.bottom=%d\r\n",  rc.left, rc.top, rc.right, rc.bottom);
	m_hToolBar = CreateWindow (CTRL_COOLBAR,
					 "",
					 /*WS_CHILD |*/ WS_VISIBLE | WS_EX_TRANSPARENT,
					 IDC_TOOLBAR,
					 rc.right - 200, 10 , 200, INFOBAR_H - 20,
					 hWnd,
					 0);
	
	 //item.ItemType = TYPE_TEXTITEM;
	 item.ItemType = TYPE_BMPITEM;
	 item.dwAddData = 0;
	 for (i = 0; i < ITEM_NUM; i++) {
		 item.Bmp = m_infobarBmp[i];
		 item.insPos = i;
		 item.id = i;
		 item.Caption = caption[i];
		 //item.Caption = "";
		 item.ItemHint = hint[i];
		 SendMessage (m_hToolBar, CBM_ADDITEM, 0, (LPARAM)&item);
		 if (i == 3)
			 SendMessage (m_hToolBar, CBM_ENABLE, i, FALSE);
	 }

	 
	 EXIT_CLASS_FUNCTION(CUSTOM_CTRL_NAME);
		
}

NCS_EVENT_HANDLER InfoBarWindow::container_handlers[]= {
	{MSG_COMMAND, reinterpret_cast<void*>(InfoBarWindow::container_onCommand)},
	{0, NULL}
};

BOOL InfoBarWindow::container_onCommand(mWidget* self, int id, int nc, HWND hCtrl)
{
    return FALSE;
}


