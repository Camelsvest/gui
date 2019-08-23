#include <assert.h>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include "mainwindow.h"
#include "navigator_window.h"
#include "infobarwindow.h"
#include "navigatorres.h"
#include "navigatorskin.h"
#include "logging.h"

static NCS_RDR_INFO spin_rdr_info[] = 
{
	{"fashion", "fashion", NULL},
};
	
static NCS_RDR_INFO prop_rdr_info[] =
{
    {"classic", "skin", NULL},
};

static DLGTEMPLATE PageSysInfo =
{
    WS_BORDER | WS_CAPTION,
    WS_EX_NONE,
    0, 0, 0, 0,
    "",
    0, 0,
    0, NULL,
    0
};

static DLGTEMPLATE PageSysInfoTemp =
{
    WS_BORDER | WS_CAPTION,
    WS_EX_NONE,
    0, 0, 0, 0,
    "",
    0, 0,
    1, NULL,
    0
};

static CTRLDATA CtrlSysInfo [] =
{
    {
        CTRL_STATIC,
        WS_VISIBLE| SS_LEFT,
        300, 150, 80, 20,
        IDC_SYSINFO,
        "static",
        0
	}
};

static NCS_WND_TEMPLATE page_first_propsheet[] = {
	{
		NCSCTRL_BUTTON, 
		IDC_BUTTON_0,
		40, 200, BTN_W, BTN_H,
		WS_VISIBLE | NCSS_BUTTON_IMAGE,
		WS_EX_NONE,
		"",
		NULL,
		NULL,
		NULL,
	   	NULL,	
		0,
		0,
        0xFF0000FF,
	}
};

static NCS_WND_TEMPLATE page_second_propsheet[] = {
	{
		NCSCTRL_BUTTON, 
		IDC_BUTTON_1,
		150, 200, BTN_W, BTN_H,
		WS_VISIBLE | NCSS_BUTTON_IMAGE,
		WS_EX_NONE,
		"",
		NULL,
		NULL,
		NULL,
	   	NULL,	
		0,
		0,
        0xFF0000FF,
	}
};


static NCS_WND_TEMPLATE page_first[] = {
	{
		NCSCTRL_BUTTON, 
		IDC_BUTTON_0,
		(SCREEN_W-BTN_INTERVAL*2-BTN_W*3)/2, (SCREEN_H-INFOBAR_H-NGT_TITLE_H-BTN_H)/2, BTN_W, BTN_H,
		WS_VISIBLE | NCSS_BUTTON_IMAGE,
		WS_EX_NONE,
		"",
		NULL,
		NULL,
		NavigatorWindow::m_btnHandlers,
	   	NULL,	
		0,
		0,
        0xFF0000FF,
	},
	{
		NCSCTRL_BUTTON, 
		IDC_BUTTON_1,
		(SCREEN_W-BTN_INTERVAL*2-BTN_W*3)/2 + BTN_W + BTN_INTERVAL, (SCREEN_H-INFOBAR_H-NGT_TITLE_H-BTN_H)/2, BTN_W, BTN_H,
		WS_VISIBLE | NCSS_BUTTON_IMAGE,
		WS_EX_NONE,
		"",
		NULL,
		NULL,
		NavigatorWindow::m_btnHandlers,
		NULL,
		0, 
		0,
        0xFFFF0000,
	},
	{
		NCSCTRL_BUTTON, 
		IDC_BUTTON_2,
		(SCREEN_W-BTN_INTERVAL*2-BTN_W*3)/2 +2* BTN_W + 2*BTN_INTERVAL, (SCREEN_H-INFOBAR_H-NGT_TITLE_H-BTN_H)/2, BTN_W, BTN_H,
		WS_VISIBLE | NCSS_BUTTON_IMAGE,
		WS_EX_NONE,
		"",
		NULL,
		NULL,
		NavigatorWindow::m_btnHandlers,
	   	NULL,
		0,	
		0,
        0xFFFF0000,
	}
};

static NCS_WND_TEMPLATE page_four[] = {
	{
		NCSCTRL_BUTTON, 
		IDC_BUTTON_0,
		10, 10, 72, 72,
		WS_VISIBLE,
		WS_EX_NONE,
		"",
		NULL,
		NULL,
		NULL,
		0, 
		0,
		0,
        0xFF0000FF,
	},
	{
		NCSCTRL_BUTTON, 
		IDC_BUTTON_1,
		180, 10, 72, 72,
		WS_VISIBLE,
		WS_EX_NONE,
		"",
		NULL,
		NULL,
		NULL,
		0,
		0, 
		0,
        0xFFFF0000,
	}
};

static NCS_WND_TEMPLATE page_third[] = {
	{
		NCSCTRL_SPINBOX ,
		ID_SPINBOX_ONE,
		150, 10, 150, 20,
		WS_VISIBLE | NCSS_SPNBOX_HORIZONTAL | NCSS_SPNBOX_STRING,
		WS_EX_NONE,
		"spinbox",
		NULL, //props,
		spin_rdr_info, //NULL, //rdr_info
		NULL, //handlers,
		NULL, //controls
		0,
		0 //add data
	},
    {
		NCSCTRL_SPINBOX ,
		ID_SPINBOX_TWO,
		150, 40, 150, 20,
		WS_VISIBLE | NCSS_SPNBOX_VERTICAL | NCSS_SPNBOX_STRING,
		WS_EX_NONE,
		"spinbox",
		NULL, //props,
		spin_rdr_info, //NULL, //rdr_info
		NULL, //handlers,
		NULL, //controls
		0,
		0 //add data
	}
};

NCS_RDR_ELEMENT btn_rdr_elements[] =
{
		{ NCS_MODE_USEFLAT, 1},
		{ -1, 0}
};

static NCS_RDR_INFO btn_rdr_info[] = {
		{ "fashion", "fashion", btn_rdr_elements}
};

static NCS_WND_TEMPLATE page_second[] = {
	
	{
		NCSCTRL_PROPSHEET,
		IDC_PROPSHEET,
		1, 1, 784, 400,
		WS_VISIBLE | NCSS_PRPSHT_COMPACTTAB,
		WS_EX_NONE,
		"PropSheet",
		NULL,		 //props,
		btn_rdr_info, //rdr_info
		NULL,		 //handlers,
		NULL,		 //controls
		0,
		0			 //add data
	},

	//START_DCL_DEF_PUSHBUTTON
	{
		NCSCTRL_BUTTON,
		IDC_BUTTON_0,
		30, 420, 80, 25,
		WS_BORDER | BS_PUSHBUTTON | WS_VISIBLE,
		WS_EX_NONE,
		"Disable",
		NULL,		 //props,
		btn_rdr_info, //rdr_info
		NULL,		 //handlers,
		NULL,		 //controls
		0,
		0			 //add data
	},
//END_DCL_DEF_PUSHBUTTON
//START_DCL_IMAGEBUTTON
	{
		NCSCTRL_BUTTON,
		IDC_BUTTON_1,
		150, 420, 80, 25,
		WS_VISIBLE | NCSS_BUTTON_IMAGE,
		WS_EX_NONE,
		"Enable",
		NULL,		 //props,
		btn_rdr_info, //rdr_info
		NULL,		 //handlers,
		NULL,		 //controls
		0,
		0			 //add data
	},
//END_DCL_IMAGEBUTTON
//START_DCL_AUTOCHECKBTN
	{
		NCSCTRL_BUTTON,
		IDC_BUTTON_2,
		270, 420, 80, 25,
		WS_VISIBLE  | NCSS_BUTTON_AUTOCHECK | NCSS_BUTTON_CHECKABLE,
		WS_EX_NONE,
		"Auto button",
		NULL,		 //props,
		btn_rdr_info, //rdr_info
		NULL,		 //handlers,
		NULL,		 //controls
		0,
		0			 //add data
	},
//END_DCL_AUTOCHECKBTN
//START_DCL_3DAUTOCHECKBTN
	{
		NCSCTRL_BUTTON,
		IDC_BUTTON_3,
		390, 420, 80, 25,
		WS_VISIBLE | NCSS_BUTTON_AUTOCHECK | NCSS_BUTTON_CHECKABLE \
			| NCSS_BUTTON_3DCHECK,
		WS_EX_NONE,
		"3D button",
		NULL,		 //props,
		btn_rdr_info, //rdr_info
		NULL,		 //handlers,
		NULL,		 //controls
		0,
		0			 //add data
	},
//END_DCL_3DAUTOCHECKBTN
};

static NCS_WND_TEMPLATE _ctrl_group1[] = {
	{
		NCSCTRL_BUTTON, 
		IDC_BUTTON_0,
		30, 40, 80, 30,
		WS_VISIBLE,
		WS_EX_NONE,
		"RED 1",
		NULL,
		NULL,
		NULL,
		NULL,
        0,
	},
	{
		NCSCTRL_BUTTON, 
		IDC_BUTTON_1,
		30, 110, 80, 30,
		WS_VISIBLE,
		WS_EX_NONE,
		"RED 2",
		NULL,
		NULL,
		NULL,
		NULL,
        0,
	},
};

static NCS_WND_TEMPLATE _ctrl_group2[] = {
	{
		NCSCTRL_BUTTON, 
		IDC_BUTTON_2,
		30, 40, 80, 30,
		WS_VISIBLE,
		WS_EX_NONE,
		"BLUE 1",
		NULL,
		NULL,
		NULL,
		NULL,
        0,
	},
	{
		NCSCTRL_BUTTON, 
		IDC_BUTTON_3,
		30, 110, 80, 30,
		WS_VISIBLE,
		WS_EX_NONE,
		"BLUE 2",
		NULL,
		NULL,
		NULL,
		NULL,
        0,
	},
};
// END_OF_BLUEGROUP

// START_OF_PANEL
static NCS_WND_TEMPLATE page_five[] = {
	{
		NCSCTRL_PANEL, 
		ID_PANEL_GROUP_0,
		10, 10, 140, 180,
		WS_VISIBLE,
		WS_EX_NONE,
		"Red Group",
		NULL,
		NULL,
		NULL,
		_ctrl_group1, 
		sizeof(_ctrl_group1)/sizeof(NCS_WND_TEMPLATE),
		0,
        0xFF0000FF,
	},
	{
		NCSCTRL_PANEL, 
		ID_PANEL_GROUP_1,
		160, 10, 140, 180,
		WS_VISIBLE,
		WS_EX_NONE,
		"Blue Group",
		NULL,
		NULL,
		NULL,
		_ctrl_group2,
		sizeof(_ctrl_group2)/sizeof(NCS_WND_TEMPLATE), 
		0,
        0xFFFF0000,
	},
};

PBITMAP NavigatorWindow::m_navigatorBmp[NAVIGATOR_BMP_MAX] = {NULL};
HWND NavigatorWindow::m_hBtn[6] = {0};
mPropSheet* NavigatorWindow::m_propsheet =  NULL;

char* NavigatorWindow::navigator_img_path[NAVIGATOR_BMP_MAX] = {
	"./res/vdp_home_audiomemo.png",
	"./res/vdp_home_opendoor.png",
	"./res/vdp_home_opengate.png",
	"./res/content_bg.png",
	"./res/vdp_home_audiomemo_over.png",
	"./res/vdp_home_opendoor_over.png",
	"./res/vdp_home_opengate_over.png"	
};

NCS_EVENT_HANDLER NavigatorWindow::m_pageHandlers[] =
{
	{MSG_INITPAGE,  reinterpret_cast<void*>(NavigatorWindow::page_onInitPage)},
	{MSG_SHOWPAGE,  reinterpret_cast<void*>(NavigatorWindow::page_onShowPage)},
	{MSG_SHEETCMD,  reinterpret_cast<void*>(NavigatorWindow::page_onSheetCmd)},
	{MSG_DESTROY,   reinterpret_cast<void*>(NavigatorWindow::page_onDestroy)},
	{MSG_ERASEBKGND, reinterpret_cast<void*>(NavigatorWindow::page_onEraseBkGndPage)},
	{0 , NULL }
};

NCS_EVENT_HANDLER NavigatorWindow::m_btnHandlers[] = 
{
	{MSG_LBUTTONDOWN, reinterpret_cast<void*>(NavigatorWindow::btn_onDown)},
	{MSG_LBUTTONUP,   reinterpret_cast<void*>(NavigatorWindow::btn_onUp)},
	//{MSG_PAINT,   reinterpret_cast<void*>(NavigatorWindow::btn_onPaint)},
	{0, NULL}
};

NCS_EVENT_HANDLER NavigatorWindow::m_pageHandlers_second[] =
{
	{MSG_INITPAGE,  reinterpret_cast<void*>(NavigatorWindow::page_onInitPage)},
	{MSG_SHOWPAGE,  reinterpret_cast<void*>(NavigatorWindow::page_onShowPage)},
	{MSG_SHEETCMD,  reinterpret_cast<void*>(NavigatorWindow::page_onSheetCmd)},
};

NavigatorWindow::NavigatorWindow()
    : m_navigator(NULL)
{
    ::RegisterNavigatorComponent();
}

NavigatorWindow::~NavigatorWindow()
{
    ::UnregisterNavigatorComponent();
}

int NavigatorWindow::btn_onDown (mWidget* self, DWORD wParam, DWORD lParam)
{
	mButton* mb;

	ENTER_CLASS_FUNCTION("NavigatorWindow");

	mb =(mButton*)self;
	if (self->hwnd == m_hBtn[0])
	{
		_c(mb)->setProperty(mb, NCSP_BUTTON_IMAGE, (DWORD)m_navigatorBmp[4]);
	}
	else if (self->hwnd == m_hBtn[1])
	{
		_c(mb)->setProperty(mb, NCSP_BUTTON_IMAGE, (DWORD)m_navigatorBmp[5]);
	}
	else if (self->hwnd == m_hBtn[2])
	{
		_c(mb)->setProperty(mb, NCSP_BUTTON_IMAGE, (DWORD)m_navigatorBmp[6]);
	}
		
	EXIT_CLASS_FUNCTION("NavigatorWindow");
	return 0;
}

int NavigatorWindow::btn_onUp (mWidget* self, DWORD wParam, DWORD lParam)
{
	mButton* mb;
	ENTER_CLASS_FUNCTION("NavigatorWindow");
	
	mb = (mButton *)self; 
	if (self->hwnd == m_hBtn[0])
	{
		_c(mb)->setProperty(mb, NCSP_BUTTON_IMAGE, (DWORD)m_navigatorBmp[0]);	
	}
	else if (self->hwnd == m_hBtn[1])
	{
		_c(mb)->setProperty(mb, NCSP_BUTTON_IMAGE, (DWORD)m_navigatorBmp[1]);
	}
	else if (self->hwnd == m_hBtn[2])
	{
		_c(mb)->setProperty(mb, NCSP_BUTTON_IMAGE, (DWORD)m_navigatorBmp[2]);
	}
	EXIT_CLASS_FUNCTION("NavigatorWindow");

	return 0;
}

void NavigatorWindow:: btn_onPaint (mWidget *self, HDC hdc, const CLIPRGN* inv)
{
	ENTER_CLASS_FUNCTION("NavigatorWindow");

	EXIT_CLASS_FUNCTION("NavigatorWindow");

}

bool NavigatorWindow::createWindow(HWND hParent, RECT *rc)
{    
    mPageData *pageData;
    mNavigatorPage *navigatorPage;
    HICON hIcon;
    
    bool ret = false;

    loadRes ();

	m_navigator =(mNavigator*) ncsCreateWindow (
        NCSCTRL_NAVIGATOR,
        "NavigatorWindow",     // caption
        WS_VISIBLE | NCSS_NVGTR_SIMPLE | NCSS_NVGTR_TOP, WS_EX_NONE,
        IDC_NAVIGATOR,
        rc->left, rc->top, rc->right, rc->bottom - INFOBAR_H,
        hParent,
        NULL,           // NCS_PROP_ENTRY * props,
        prop_rdr_info,  // NCS_RDR_INFO * rdr_info,
        NULL,           // NCS_EVENT_HANDLER * handlers,
        0);

	if (!m_navigator)
    {
        logging_error("Failed to create mNavigator.\r\n");		
	}
    else
    {
		logging_trace("Succeed to create mNavigator\r\n");
 		       
		PageSysInfo.controls = CtrlSysInfo;

		PageSysInfo.caption = "First Page";
        pageData = (mPageData *)malloc(sizeof(mPageData));
        logging_trace("Allocate pageData = %p\r\n", pageData);
        pageData->pThis = this;
        pageData->data = PAGE_FIRST;
	    PageSysInfo.dwAddData = (DWORD)pageData;

	    navigatorPage = _c(m_navigator)->addPage(m_navigator, &PageSysInfo, m_pageHandlers);
        hIcon = ::LoadIconFromFile(HDC_SCREEN, PAGE_ICON_FILE1, 0);
        if (hIcon)
            _c(navigatorPage)->setIcon(navigatorPage, hIcon);

	    PageSysInfo.caption = "Second Page";
        pageData = (mPageData *)malloc(sizeof(mPageData));
        logging_trace("Allocate pageData = %p\r\n", pageData);
        pageData->pThis = this;
        pageData->data = PAGE_SECOND;
	    PageSysInfo.dwAddData = (DWORD)pageData;
	    navigatorPage = _c(m_navigator)->addPage(m_navigator, &PageSysInfo, m_pageHandlers);
        hIcon = ::LoadIconFromFile(HDC_SCREEN, PAGE_ICON_FILE2, 0);
        if (hIcon)
            _c(navigatorPage)->setIcon(navigatorPage, hIcon);       

	    PageSysInfo.caption = "Third Page";
        pageData = (mPageData *)malloc(sizeof(mPageData));
        logging_trace("Allocate pageData = %p\r\n", pageData);        
        pageData->pThis = this;
        pageData->data = PAGE_THIRD;
	    PageSysInfo.dwAddData = (DWORD)pageData;
	    navigatorPage = _c(m_navigator)->addPage(m_navigator, &PageSysInfo, m_pageHandlers);
        hIcon = ::LoadIconFromFile(HDC_SCREEN, PAGE_ICON_FILE3, 0);
        if (hIcon)
            _c(navigatorPage)->setIcon(navigatorPage, hIcon);        

	    PageSysInfo.caption = "Four Page";
        pageData = (mPageData *)malloc(sizeof(mPageData));
        logging_trace("Allocate pageData = %p\r\n", pageData);        
        pageData->pThis = this;
        pageData->data = PAGE_FOUR;
	    PageSysInfo.dwAddData = (DWORD)pageData;        
 	    navigatorPage = _c(m_navigator)->addPage(m_navigator, &PageSysInfo, m_pageHandlers);
        hIcon = ::LoadIconFromFile(HDC_SCREEN, PAGE_ICON_FILE4, 0);
        if (hIcon)
            _c(navigatorPage)->setIcon(navigatorPage, hIcon);        

	    PageSysInfo.caption = "Five Page";
        pageData = (mPageData *)malloc(sizeof(mPageData));
        logging_trace("Allocate pageData = %p\r\n", pageData);        
        pageData->pThis = this;
        pageData->data = PAGE_FIVE;
	    PageSysInfo.dwAddData = (DWORD)pageData;        
	    navigatorPage = _c(m_navigator)->addPage(m_navigator, &PageSysInfo, m_pageHandlers);
        hIcon = ::LoadIconFromFile(HDC_SCREEN, PAGE_ICON_FILE5, 0);
        if (hIcon)
            _c(navigatorPage)->setIcon(navigatorPage, hIcon);

		_c(m_navigator)->setProperty(m_navigator, NCSP_NVGTR_TABMARGIN, 2);

        ret = true;
	}

    EXIT_CLASS_FUNCTION("NavigatorWindow");
    
    return ret;                      
}

BOOL NavigatorWindow:: btn_Cb (mMainWnd *self, mButton *sender, int id, DWORD param)
{
	ENTER_CLASS_FUNCTION("NavigatorWindow");
	logging_trace ("%s:%u %s id= %d, param= %d\r\n", __FILE__, __LINE__, __FUNCTION__, id, (int)param);
	if (sender->hwnd == m_hBtn[4])
	{
		logging_trace ("set button disable\r\n");
		SendNotifyMessage (sender->hwnd, MSG_ENABLE, (WPARAM)FALSE, (LPARAM)NULL);
	}		
	else if (sender->hwnd == m_hBtn[5])
	{
		SendNotifyMessage (m_hBtn[4], MSG_ENABLE, (WPARAM)TRUE, (LPARAM)NULL);
	}
	EXIT_CLASS_FUNCTION("NavigatorWindow");
	return TRUE;
}
void NavigatorWindow::onInitPage(mWidget* self,int pageType)
{
	mButton* mb;
	mWidget* mW;

	int i;
	mPageData *pageData;	
	ENTER_CLASS_FUNCTION("NavigatorWindow");
	
	mW = (mWidget *)ncsGetParentObj (self->hwnd);
	
	if (mW->hwnd == m_navigator->hwnd){
		
		switch(pageType){

		case PAGE_FIRST:
			_c(self)->addChildren(self, page_first, \
				sizeof(page_first)/sizeof(NCS_WND_TEMPLATE));
					
			for (i = 0; i < 3; i++)
			{
				mb = (mButton*)ncsGetChildObj(self->hwnd, (IDC_BUTTON_0 + i));
				if(mb)
            	{
					_c(mb)->setProperty(mb, NCSP_BUTTON_IMAGE, (DWORD)m_navigatorBmp[i]);
					logging_trace("%s:%u %s setProperty\r\n", __FILE__, __LINE__, __FUNCTION__);	
					m_hBtn[i] = mb->hwnd;
				}
			}

			break;
            
		case PAGE_SECOND:

			_c(self)->addChildren(self, page_second, \
				sizeof(page_second)/sizeof(NCS_WND_TEMPLATE));
			
			for (i=0; i < 2; i++){

				mb = (mButton *)ncsGetChildObj (self->hwnd, IDC_BUTTON_0 + i);
				if (mb)
				{
					ncsAddEventListener ((mObject*)mb, (mObject*)self, (NCS_CB_ONOBJEVENT)btn_Cb, NCSN_WIDGET_CLICKED);	
					m_hBtn [4 + i] = mb->hwnd;
				}
			}
			
			m_propsheet = (mPropSheet *)ncsGetChildObj (self->hwnd, IDC_PROPSHEET);

			PageSysInfoTemp.controls = CtrlSysInfo;

			PageSysInfoTemp.caption = "CAMERAS";
        	pageData = (mPageData *)malloc(sizeof(mPageData));
        	pageData->pThis = this;
        	pageData->data = PAGE_FIRST;
	    	PageSysInfoTemp.dwAddData = (DWORD)pageData;

	    	_c(m_propsheet)->addPage(m_propsheet, &PageSysInfoTemp, m_pageHandlers_second);	

			PageSysInfoTemp.caption = "SNAPSHOTS";
        	pageData = (mPageData *)malloc(sizeof(mPageData));
        	pageData->pThis = this;
        	pageData->data = PAGE_SECOND;
	    	PageSysInfoTemp.dwAddData = (DWORD)pageData;

	    	_c(m_propsheet)->addPage(m_propsheet, &PageSysInfoTemp, m_pageHandlers_second);	
			_c(m_propsheet)->setProperty(m_propsheet, NCSP_PRPSHT_TABMARGIN, 2);
			break;
            
		case PAGE_THIRD:
			_c(self)->addChildren(self, page_third, \
				sizeof(page_third)/sizeof(NCS_WND_TEMPLATE));
			break;
            
		case PAGE_FOUR:
			_c(self)->addChildren(self, page_four, \
				sizeof(page_four)/sizeof(NCS_WND_TEMPLATE));
			break;
            
		case PAGE_FIVE:
			_c(self)->addChildren(self, page_five, \
				sizeof(page_five)/sizeof(NCS_WND_TEMPLATE));
            break;
                
		default:
			logging_error("%s:%u %s Haven\'t type for propsheet\r\n", __FILE__, __LINE__, __FUNCTION__);
            break;	
		}
	}
	else if(mW->hwnd == m_propsheet->hwnd){
		HWND hwnd;
		mPage* page;
		
		page = (mPage*)self;

		hwnd = GetDlgItem (_c(page)->getPanel(page),IDC_SYSINFO);

		switch (pageType){
			case PAGE_FIRST:
		   		//_c(self)->addChildren (self, page_first_propsheet, sizeof(page_first_propsheet)/sizeof(NCS_WND_TEMPLATE));
				SetWindowText (hwnd, "No Cameras");
				break;
			case PAGE_SECOND:
				//_c(self)->addChildren (self, page_second_propsheet, sizeof(page_second_propsheet)/sizeof(NCS_WND_TEMPLATE));
				SetWindowText (hwnd, "NoImages");
				break;

			default:
				break;	
		}		
	}

	EXIT_CLASS_FUNCTION("NavigatorWindow");

    return;
}

void NavigatorWindow::page_onInitPage(mWidget* self, DWORD add_data)
{
    NavigatorWindow *pThis;
    mPageData *pageData;

	
	ENTER_CLASS_FUNCTION("NavigatorWindow");

    pageData = (mPageData *)add_data;
   
    pThis = pageData->pThis;
    pThis->onInitPage(self, pageData->data);
	
	EXIT_CLASS_FUNCTION("NavigatorWindow");
}

int NavigatorWindow::page_onShowPage(mWidget* self, HWND hwnd, int show_cmd)
{
	
	ENTER_CLASS_FUNCTION("NavigatorWindow");
	
	EXIT_CLASS_FUNCTION("NavigatorWindow");

    return 1;
}

int NavigatorWindow::page_onSheetCmd(mWidget* self, DWORD wParam, DWORD lParam)
{
	
	ENTER_CLASS_FUNCTION("NavigatorWindow");
       
	
	EXIT_CLASS_FUNCTION("NavigatorWindow");
    return 0;
}

int NavigatorWindow::page_onEraseBkGndPage(mWidget* self, HDC hdc, const RECT *rc)
{
	HDC hdct;
	RECT rcClient;
	DWORD bkColor;
	gal_pixel old;
	mWidget* mW;

	ENTER_CLASS_FUNCTION("NavigatorWindow");

	mW = (mWidget *)ncsGetParentObj (self->hwnd);

	if (m_propsheet->hwnd == mW->hwnd)
		return 1;	

	if (hdc == (HDC)0)
		hdct = GetClientDC(self->hwnd);
	else
		hdct =hdc;

	GetClientRect(self->hwnd, &rcClient);
	bkColor = GetWindowBkColor (self->hwnd);
	old = SetBrushColor(hdct, bkColor);
	SetBitmapScalerType(hdct, BITMAP_SCALER_BILINEAR);
	//SetBitmapScalerType(hdc, BITMAP_SCALER_DDA);
	logging_trace("rc->left=%d, rc->top=%d, rc->right=%d, rc->bottom=%d\r\n",  rcClient.left, rcClient.top, rcClient.right, rcClient.bottom);
	
	FillBoxWithBitmap(hdct, rcClient.left, rcClient.top, RECTW(rcClient), RECTH(rcClient), m_navigatorBmp[BACKGROUD_BMP_INDEX]);
	
	SetBrushColor(hdct, old);
	if(hdc != hdct)
		ReleaseDC(hdct); 

	EXIT_CLASS_FUNCTION("NavigatorWindow");

	return 1;	
}

void NavigatorWindow::page_onDestroy(mWidget* self, DWORD wParam, DWORD lParam)
{
    HICON hIcon;
    mPageData *pageData;
    
    ENTER_CLASS_FUNCTION("NavigatorWindow");
    pageData = (mPageData *)::GetWindowAdditionalData(self->hwnd);
    if (pageData)
    {
        logging_trace("free pageData: %p\n", pageData);
        free(pageData);
    }

    hIcon = _c((mNavigatorPage *)self)->getIcon((mNavigatorPage *)self);
    if (hIcon)
        ::DestroyIcon(hIcon);
    
    EXIT_CLASS_FUNCTION("NavigatorWindow");
}

void NavigatorWindow::loadRes ()
{
	for (int i = 0; i < NAVIGATOR_BMP_MAX; ++i)
		m_navigatorBmp[i] = (PBITMAP) LoadResource(navigator_img_path[i], RES_TYPE_IMAGE, (DWORD)HDC_SCREEN);
}

void NavigatorWindow::unloadRes ()
{
	for (int i = 0; i < NAVIGATOR_BMP_MAX; ++i)
		ReleaseRes(Str2Key(navigator_img_path[i]));

}
