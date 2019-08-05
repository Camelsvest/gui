#include <assert.h>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include "mainwindow.h"
#include "navigator.h"
#include "navigator_window.h"
#include "navigatorres.h"
#include "navigatorskin.h"
#include "trace.h"


#define DEFAULT_TAB_HEIGHT  48


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

static CTRLDATA CtrlSysInfo [] =
{
    {
        CTRL_STATIC,
        WS_VISIBLE | SS_LEFT,
        0, 0, 370, 180,
        IDC_SYSINFO,
        "",
        0
    }
};

static NCS_WND_TEMPLATE page_first[] = {
	{
		NCSCTRL_BUTTON, 
		ID_BUTTON_0,
		10, 10, 140, 140,
		WS_VISIBLE | NCSS_BUTTON_IMAGE,
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
		ID_BUTTON_1,
		180, 10, 140, 140,
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

static NCS_WND_TEMPLATE page_four[] = {
	{
		NCSCTRL_BUTTON, 
		ID_BUTTON_0,
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
		ID_BUTTON_1,
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
//START_DCL_DEF_PUSHBUTTON
	{
		NCSCTRL_BUTTON,
		ID_BUTTON_0,
		30, 30, 80, 25,
		WS_BORDER | WS_VISIBLE,
		WS_EX_NONE,
		"button",
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
		ID_BUTTON_1,
		150, 30, 80, 25,
		WS_VISIBLE | NCSS_BUTTON_IMAGE,
		WS_EX_NONE,
		"Image",
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
		ID_BUTTON_2,
		30, 80, 80, 25,
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
		ID_BUTTON_3,
		150, 80, 80, 25,
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
		ID_BUTTON_0,
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
		ID_BUTTON_1,
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
		ID_BUTTON_2,
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
		ID_BUTTON_3,
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


NCS_EVENT_HANDLER NavigatorWindow::m_pageHandlers[] =
{
	{MSG_INITPAGE,  reinterpret_cast<void*>(NavigatorWindow::page_onInitPage)},
	{MSG_SHOWPAGE,  reinterpret_cast<void*>(NavigatorWindow::page_onShowPage)},
	{MSG_SHEETCMD,  reinterpret_cast<void*>(NavigatorWindow::page_onSheetCmd)},
	{MSG_DESTROY,   reinterpret_cast<void*>(NavigatorWindow::page_onDestroy)},
	{0 , NULL }
};

NavigatorWindow::NavigatorWindow()
    : m_propsheet(NULL)
{
    ::InitNavigatorSkinRenderer();
    ::RegisterNavigatorComponent();
}

NavigatorWindow::~NavigatorWindow()
{
    ::UnregisterNavigatorComponent();
}

bool NavigatorWindow::createWindow(HWND hParent, RECT *rc)
{    
    mPageData *pageData;
    
    bool ret = false;
    
	m_propsheet =(mPropSheet*) ncsCreateWindow (
        NCSCTRL_NAVIGATOR,
        "NavigatorWindow",     // caption
        WS_VISIBLE | NCSS_PRPSHT_SCROLLABLE, WS_EX_NONE,
        IDC_NAVIGATOR,
        rc->left, rc->top, rc->right, rc->bottom,
        hParent,
        NULL,           // NCS_PROP_ENTRY * props,
        prop_rdr_info,  // NCS_RDR_INFO * rdr_info,
        NULL,           // NCS_EVENT_HANDLER * handlers,
        0);

	if (!m_propsheet)
    {
        logging_error("Failed to create mPropsheet.\r\n");		
	}
    else
    {
		logging_trace("Succeed to create mPropsheet\r\n");
        
		PageSysInfo.controls = CtrlSysInfo;

		PageSysInfo.caption = "First Page";
        pageData = (mPageData *)malloc(sizeof(mPageData));
        logging_trace("Allocate pageData = %p\r\n", pageData);
        pageData->pThis = this;
        pageData->data = PAGE_FIRST;
	    PageSysInfo.dwAddData = (DWORD)pageData;
	    _c(m_propsheet)->addPage(m_propsheet, &PageSysInfo, m_pageHandlers);

	    PageSysInfo.caption = "Second Page";
        pageData = (mPageData *)malloc(sizeof(mPageData));
        logging_trace("Allocate pageData = %p\r\n", pageData);
        pageData->pThis = this;
        pageData->data = PAGE_SECOND;
	    PageSysInfo.dwAddData = (DWORD)pageData;
	    _c(m_propsheet)->addPage(m_propsheet, &PageSysInfo, m_pageHandlers);

	    PageSysInfo.caption = "Third Page";
        pageData = (mPageData *)malloc(sizeof(mPageData));
        logging_trace("Allocate pageData = %p\r\n", pageData);        
        pageData->pThis = this;
        pageData->data = PAGE_THIRD;
	    PageSysInfo.dwAddData = (DWORD)pageData;
	    _c(m_propsheet)->addPage(m_propsheet, &PageSysInfo, m_pageHandlers);

	    PageSysInfo.caption = "Four Page";
        pageData = (mPageData *)malloc(sizeof(mPageData));
        logging_trace("Allocate pageData = %p\r\n", pageData);        
        pageData->pThis = this;
        pageData->data = PAGE_FOUR;
	    PageSysInfo.dwAddData = (DWORD)pageData;        
 	    _c(m_propsheet)->addPage(m_propsheet, &PageSysInfo, m_pageHandlers);

	    PageSysInfo.caption = "Five Page";
        pageData = (mPageData *)malloc(sizeof(mPageData));
        logging_trace("Allocate pageData = %p\r\n", pageData);        
        pageData->pThis = this;
        pageData->data = PAGE_FIVE;
	    PageSysInfo.dwAddData = (DWORD)pageData;        
	    _c(m_propsheet)->addPage(m_propsheet, &PageSysInfo, m_pageHandlers);

		_c(m_propsheet)->setProperty(m_propsheet, NCSP_PRPSHT_TABMARGIN, 8);

        ret = true;
	}

    return ret;
                       
}

void NavigatorWindow::onInitPage(mWidget* self,int pageType)
{
	mButton* mb;

	ENTER_CLASS_FUNCTION("NavigatorWindow");

	switch(pageType){

		case PAGE_FIRST:
			_c(self)->addChildren(self, page_first, \
				sizeof(page_first)/sizeof(NCS_WND_TEMPLATE));
			
			if (LoadBitmapFromFile(HDC_SCREEN, &m_bmpAudioMemo, NAVIGATOR_SKIN_HOME_PAGE_BTN_AUDIOMEMO) != 0)				
				logging_error("%s:%u %s Can\'t load bitmap\r\n", __FILE__, __LINE__, __FUNCTION__);
			
			mb = (mButton*)ncsGetChildObj(self->hwnd, ID_BUTTON_0);
			if(mb)
            {
				_c(mb)->setProperty(mb, NCSP_BUTTON_IMAGE, (DWORD)&m_bmpAudioMemo);
				logging_trace("%s:%u %s setProperty\r\n", __FILE__, __LINE__, __FUNCTION__);
			}
			break;
            
		case PAGE_SECOND:
			_c(self)->addChildren(self, page_second, \
				sizeof(page_second)/sizeof(NCS_WND_TEMPLATE));
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
	
	EXIT_CLASS_FUNCTION("NavigatorWindow")

    return 1;
}

int NavigatorWindow::page_onSheetCmd(mWidget* self, DWORD wParam, DWORD lParam)
{
	
	ENTER_CLASS_FUNCTION("NavigatorWindow");
    if (wParam == IDC_REFRESH) {
       
    }
	
	EXIT_CLASS_FUNCTION("NavigatorWindow")
    return 0;
}

void NavigatorWindow::page_onDestroy(mWidget* self, DWORD wParam, DWORD lParam)
{
    mPageData *pageData;
    
    ENTER_CLASS_FUNCTION("NavigatorWindow");
    pageData = (mPageData *)::GetWindowAdditionalData(self->hwnd);
    if (pageData)
    {
        logging_trace("free pageData: %p\n", pageData);
        free(pageData);
    }
    EXIT_CLASS_FUNCTION("NavigatorWindow");
}
