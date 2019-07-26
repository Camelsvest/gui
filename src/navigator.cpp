#include <assert.h>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include "mainwindow.h"
#include "navigator.h"
#include "navigatorres.h"
#include "navigatorskin.h"
#include "navigatorhomepage.h"
#include "logging.h"


#define DEFAULT_TAB_HEIGHT  48


static NCS_RDR_INFO spin_rdr_info[] = 
{
	{"fashion", "fashion", NULL},
};
	
static NCS_RDR_INFO prop_rdr_info[] =
{
    {"skin", "skin", NULL},
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

static char *nvgtAllPictures[] = 
{
    NAVIGATOR_SKIN_TAB_BG,
    NAVIGATOR_SKIN_PAGE_BG,
    NAVIGATOR_SKIN_HOME_PAGE_BG,
    NAVIGATOR_SKIN_HOME_PAGE_BTN_AUDIOMEMO
};

static void page_onInitPage(mWidget* self, DWORD add_data)
{
	mPage* page;
	mButton* mb;
	BITMAP bmp;
	int type;
	HWND hwnd;
	
	fprintf (stdout, "%s %s %d->ENTER FUNCTION\r\n", __FILE__, __FUNCTION__, __LINE__);

	page = (mPage*)self;

	type = (int)GetWindowAdditionalData(page->hwnd);
	//hwnd = GetDlgItem(_c(page)->getPanel(page), IDC_SYSINFO)

	switch(type){

		case PAGE_FIRST:
			_c(self)->addChildren(self, page_first, \
				sizeof(page_first)/sizeof(NCS_WND_TEMPLATE));
			
			if (LoadBitmapFromFile(HDC_SCREEN, &bmp, nvgtAllPictures[3]) != 0)				
				fprintf(stdout, "%s %s %d-> can not load bitmap\r\n", __FILE__, __FUNCTION__, __LINE__);
			
			mb = (mButton*)ncsGetChildObj(self->hwnd, ID_BUTTON_0);
			if(mb){
				_c(mb)->setProperty(mb, NCSP_BUTTON_IMAGE, (DWORD)&bmp);
				fprintf(stdout, "%s %s %d-> setProperty\r\n", __FILE__, __FUNCTION__, __LINE__);
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
		default:
			fprintf (stdout, "%s %s %d-> Have no type for propsheet\r\n", __FILE__, __FUNCTION__, __LINE__);

	
	}
		
	
	fprintf (stdout, "%s %s %d->EXIT FUNCTION\r\n", __FILE__, __FUNCTION__, __LINE__);
}

static int page_onShowPage(mWidget* self, HWND hwnd, int show_cmd)
{
	
	fprintf (stdout, "%s %s %d->ENTER FUNCTION\r\n", __FILE__, __FUNCTION__, __LINE__);
	
	fprintf (stdout, "%s %s %d->EXIT FUNCTION\r\n", __FILE__, __FUNCTION__, __LINE__);

    return 1;
}

static int page_onSheetCmd(mWidget* self, DWORD wParam, DWORD lParam)
{
	
	fprintf (stdout, "%s %s %d->ENTER FUNCTION\r\n", __FILE__, __FUNCTION__, __LINE__);
    if (wParam == IDC_REFRESH) {
       
    }
	
	fprintf (stdout, "%s %s %d->EXIT FUNCTION\r\n", __FILE__, __FUNCTION__, __LINE__);
    return 0;
}


static NCS_EVENT_HANDLER page_handlers[] =
{
	{MSG_INITPAGE, reinterpret_cast<void*>(page_onInitPage)},
	{MSG_SHOWPAGE, reinterpret_cast<void*>(page_onShowPage)},
	{MSG_SHEETCMD, reinterpret_cast<void*>(page_onSheetCmd)},
	{0 , NULL }
};

Navigator::Navigator()
    : CtrlWnd(CTRL_NAVIGATOR)
    , m_nvgtTab(NULL)
    , m_ActivatePageIterator(m_nvgtPageList.end())
{
    NavigatorPage *page;

    if (!registerAllPictures())
        throw new std::invalid_argument("Failed to register all pictures.");

    page = new NavigatorPage("Page1", 0);
    if (page == NULL)
        throw new std::runtime_error("Failed to allocate memory for NavigatorPage: Page1.");
    addPage(page);
    
    page = new NavigatorHomePage("Page2", 0);
    if (page == NULL)
        throw new std::runtime_error("Failed to allocate memory for NavigatorPage: Page2.");

    addPage(page, true);

}

Navigator::Navigator(mMainWnd* mainwnd)
:CtrlWnd(CTRL_NAVIGATOR){
	
	fprintf (stdout, "%s %s %d->ENTER FUNCTION\r\n", __FILE__, __FUNCTION__, __LINE__);
	if (!mainwnd)
		return ;
	
	m_propsheet =(mPropSheet*) ncsCreateWindow (NCSCTRL_PROPSHEET,"", WS_VISIBLE | NCSS_PRPSHT_SCROLLABLE, WS_EX_NONE,
                       IDC_PROPSHEET,
                       0, 0, 490, 225, mainwnd->hwnd,
                       NULL, prop_rdr_info, NULL, 0);

	if (!m_propsheet){
		fprintf (stdout, "%s %s %d-> ncs create propsheet failure\r\n", __FILE__, __FUNCTION__, __LINE__);
		
	}else{
		fprintf (stdout, "%s %s %d-> ncs create propsheet succeed\r\n", __FILE__, __FUNCTION__, __LINE__);
		PageSysInfo.controls = CtrlSysInfo;
		PageSysInfo.caption = "First Page";
	    PageSysInfo.dwAddData = PAGE_FIRST;
	    _c(m_propsheet)->addPage(m_propsheet, &PageSysInfo, page_handlers);

	    PageSysInfo.caption = "Second Page";
	    PageSysInfo.dwAddData = PAGE_SECOND;
	    _c(m_propsheet)->addPage(m_propsheet, &PageSysInfo, page_handlers);

	    PageSysInfo.caption = "Third Page";
	    PageSysInfo.dwAddData = PAGE_THIRD;
	    _c(m_propsheet)->addPage(m_propsheet, &PageSysInfo, page_handlers);

	    PageSysInfo.caption = "Four Page";
	    PageSysInfo.dwAddData = PAGE_FOUR;
	    _c(m_propsheet)->addPage(m_propsheet, &PageSysInfo, page_handlers);

	    PageSysInfo.caption = "Five Page";
	    PageSysInfo.dwAddData = PAGE_FIVE;
	    _c(m_propsheet)->addPage(m_propsheet, &PageSysInfo, page_handlers);

		_c(m_propsheet)->setProperty(m_propsheet, NCSP_PRPSHT_TABMARGIN, 8);
	}
	fprintf (stdout, "%s %s %d->EXIT FUNCTION\r\n", __FILE__, __FUNCTION__, __LINE__);
}

Navigator::~Navigator()
{
    NvgtPageList::iterator itera;
    NavigatorPage *page;
    
    for (itera = m_nvgtPageList.begin(); itera != m_nvgtPageList.end(); itera++)
    {
        page = *itera;
        delete page;
    }
    
    unregisterAllPictures();
}

int Navigator::wndProc(int message, WPARAM wParam, LPARAM lParam)
{
    int ret = 0;
    
    switch (message)
    {
    case MSG_CREATE:
        ret = onCreate(wParam, lParam);
        break;

    case MSG_PAINT:
        ret = onPaint(wParam, lParam);
        break;

    case MSG_INIT_SKIN:
        ret = onInitSkin(wParam, lParam);
        break;
        
    case MSG_NCPAINT:        
    default:
        ret = DefaultMainWinProc(getHandle(), message, wParam, lParam);
        break;
    }


    return ret;    
}

int Navigator::onCreate(WPARAM wParam, LPARAM lParam)
{
    bool succeed;
    RECT rc, rcTab, rcPage;    
    NavigatorPage *activatePage;

    if (!getClientRect(&rc))
        return -1;
    else
        logging_trace("Client size %d, %d, %d, %d.\r\n", rc.left, rc.top, rc.right, rc.bottom);
    
    assert(m_nvgtTab == NULL);

    rcTab.top = 5;
    rcTab.left = 5;
    rcTab.right = rc.right - 5;
    rcTab.bottom = DEFAULT_TAB_HEIGHT - 5;
    
    m_nvgtTab = new NavigatorTab;
    succeed = m_nvgtTab->createWindow(IDC_NAVIGATOR_TAB,  rcTab.left, rcTab.top, rcTab.right - rcTab.left, rcTab.bottom - rcTab.top, getHandle());
    if (!succeed)
        return -1;
    else
    {
        logging_trace("Succeed to create \"NavigatorTab\" @(%d, %d, %d, %d)\r\n",
            rcTab.left, rcTab.top, rcTab.right, rcTab.bottom);
    }
    
    rcPage.left = 5;
    rcPage.top = DEFAULT_TAB_HEIGHT + 5;
    rcPage.right = rc.right - 5;
    rcPage.bottom = rc.bottom - 5;
    
    activatePage = *m_ActivatePageIterator;
    if (activatePage)
    {
        succeed = activatePage->createWindow(IDC_NAVIGATOR_PAGE2, rcPage.left, rcPage.top, rcPage.right - rcPage.left, rcPage.bottom - rcPage.top, getHandle());
        if (!succeed)
            return -1;
        else
        {
            logging_trace("Succeed to create \"NavigatorPage\" @(%d, %d, %d, %d)\r\n",
                rcPage.left, rcPage.top, rcPage.right - rcPage.left, rcPage.bottom - rcPage.top);
        }
    }

    return sendMessage(MSG_INIT_SKIN, 0, 0);
   
}

bool Navigator::addPage(NavigatorPage *page, bool activated)
{
    m_nvgtPageList.push_back(page);

    if (!activated)
        m_ActivatePageIterator = m_nvgtPageList.begin();
    else
        m_ActivatePageIterator = --m_nvgtPageList.end(); // current page is activated
        
    return true;
}

bool Navigator::delPage(NavigatorPage *page)
{
    m_nvgtPageList.remove(page);
    return true;
}

bool Navigator::registerAllPictures()
{
    unsigned int i;
    
    bool ret = true;
    
    if (0 == ::SetResPath("./res/"))
    {
        for (i = 0; i < sizeof(nvgtAllPictures)/sizeof(nvgtAllPictures[0]); i++)
        {
            if (::RegisterResFromFile(HDC_SCREEN, nvgtAllPictures[i]) == FALSE)
            {
                logging_error("Failed to register resource: %s.\r\n", nvgtAllPictures[i]);
                ret = false;
                break;
            }
        }
    }
    else
    {
        logging_error("Failed to register path for resource files.\r\n");
        ret = false;
    }

    return ret;
}

void Navigator::unregisterAllPictures()
{
    unsigned int i;

    for (i = 0; i < sizeof(nvgtAllPictures)/sizeof(nvgtAllPictures[0]); i++)
    {
        ::UnregisterRes(nvgtAllPictures[i]);
    }
}

int Navigator::onInitSkin(WPARAM wParam, LPARAM lParam)
{
    setWindowElementAttr(WE_LFSKIN_WND_BKGND, (DWORD)NAVIGATOR_SKIN_PAGE_BG);
    return 0;
}

