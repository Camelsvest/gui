#include <string.h>
#include <stdexcept>

#include "mainwindow.h"
#include "navigatorres.h"

#define STR_CAP             "Notebook"
#define STR_FILE             "File"
#define STR_NEW              "New"
#define STR_OPEN             "Open"
#define STR_SAVE             "Save"
#define STR_SAVE_AS          "Save As"
#define STR_PRINT            "Print"
#define STR_EXIT             "Exit"

#define STR_SEARCH           "Search"     
#define STR_FIND             "Find"    
#define STR_FIND_NEXT        "Find Next"

#define STR_EDIT             "Edit"
#define STR_UNDO             "Undo"
#define STR_CUT              "Cut"
#define STR_COPY             "Copy"
#define STR_PASTE            "Paste"
#define STR_DELETE           "Delete"
#define STR_SELECT_ALL       "Select All"
#define STR_INSERT_DATE      "Insert Date"
#define STR_AUTO_WRAP        "Auto Wrap"

#define STR_VIEW             "View"
#define STR_MODIFY_CFG       "Config"
#define STR_DFL_CHAR_SET     "Default Char Set"
#define STR_HELP             "Help"
#define STR_ABOUT            "about notebook"
#define STR_ABOUT_INFO       "notebook version 0.6\n"

#define STR_OK               "Ok"
#define STR_CANCEL           "Cancel"
#define STR_SAVE_OR_NOT      "Save or Not Save?"
#define STR_FILE_OPEN_FAILED "File Open Failed!" 
#define STR_FILE_SAVE_FAILED "File Save Failed!"
#define STR_FILE_TRUNCTED    "File Trunctd" 
#define STR_FILE_NOT_EXIST   "File Not Exist!"
#define STR_FILE_NOT_READABLE    "File not Readable"
#define STR_FILE_NOT_WRITABLE    "File not Writable"

#define STR_NEW_NOTEBOOK_SIZE    "New notebook size"
#define STR_SPECIFY_VALID_SIZE        "Please specify valid notebook size."
#define STR_SPECIFY_NEW_WIN_SIZE      "Please specify new window size."
#define STR_COL_NUM                      "Collum:"
#define STR_ROW_NUM                      "Row:"
#define STR_MODIFIED_IS_SAVE             "File Modified, Save or Not?"

#define IDM_NEW         301
#define IDM_OPEN        120
#define IDM_SAVE        130
#define IDM_SAVEAS      140
#define IDM_PRINT       150
#define IDM_EXIT        160
#define IDM_ABOUT       410
#define IDM_ABOUT_THIS  411

MainWindow* MainWindow::m_pInstance = NULL;


static BOOL main_onCreate(mMainWnd* self, DWORD dwAddData );
static BOOL main_onClose(mWidget* self, int message);
static BOOL main_onDestroy(mWidget* self, int message);
static BOOL main_onEraseBk(mWidget *self, HDC hdc, const PRECT clip);
static BOOL main_onLbuttonDownHandler(mWidget *self, int message, int x, int y, DWORD keyStatus);
static BOOL main_onLbuttonUpHandler(mWidget *self, int message, int x, int y, DWORD keyStatus);
static BOOL main_onLbuttonDownHandler(mWidget *self, int message, int x, int y, DWORD keyStatus);


static BOOL main_onCreate(mMainWnd* self, DWORD dwAddData )
{
	MainWindow *pMainWindow;
	Navigator *nvgt;
	
	fprintf (stdout, "%s %s->ENTER FUNCTION\r\n", __FILE__, __FUNCTION__);
	
	pMainWindow = MainWindow::getInstance();
	
	nvgt = new Navigator(self);
	if (nvgt){
		pMainWindow->setM_nvgt(nvgt);
	}

	fprintf (stdout, "%s %s->EXIT FUNCTION\r\n", __FILE__, __FUNCTION__);
	return true;
}

static BOOL main_onClose(mWidget* self, int message)
{
	return true;
}

static BOOL main_onDestroy(mWidget* self, int message)
{
	return true;
}

static BOOL main_onEraseBk(mWidget *self, HDC hdc, const PRECT clip){
return true;
}

static BOOL main_onLbuttonDownHandler(mWidget *self, int message, int x, int y, DWORD keyStatus){
	
	fprintf (stdout, "%s %s->ENTER FUNCTION\r\n", __FILE__, __FUNCTION__);

	
	fprintf (stdout, "%s %s->EXIT FUNCTION\r\n", __FILE__, __FUNCTION__);
	return true;
}

static BOOL main_onLbuttonUpHandler(mWidget *self, int message, int x, int y, DWORD keyStatus){
return true;
}

static BOOL main_onMouseMoveHandler(mWidget *self, int message, int x, int y, DWORD keyStatus){
return true;
}

static BOOL main_onPaint(mWidget* self, HDC hdc, const PCLIPRGN clipRgn){
return true;
}


//if use mgncs4touch to SpeedMeterMessageHandler in MSG_LBUTTONDOWN,MSG_LBUTTONUP and MSG_MOUSEMOVE
static NCS_EVENT_HANDLER main_handlers [] = {
    {MSG_CREATE, reinterpret_cast<void*>(main_onCreate)},
    {MSG_CLOSE, reinterpret_cast<void*>(main_onClose)},    
    {MSG_DESTROY,     reinterpret_cast<void*>(main_onDestroy)},
    //{MSG_LBUTTONDOWN, reinterpret_cast<void*>(main_onLbuttonDownHandler)}, 
    {MSG_LBUTTONUP,   reinterpret_cast<void*>(main_onLbuttonUpHandler)},
    {MSG_MOUSEMOVE,   reinterpret_cast<void*>(main_onMouseMoveHandler)},
    {MSG_PAINT, reinterpret_cast<void*>(main_onPaint)},
    {MSG_ERASEBKGND, reinterpret_cast<void*>(main_onEraseBk)},
    {0, NULL}
};


MainWindow::MainWindow()
    : m_hMLEditWnd(HWND_INVALID)
    , m_nvgt(NULL)
{
}

MainWindow::~MainWindow()
{
    if (m_nvgt)
        delete m_nvgt;
}

MainWindow* MainWindow::getInstance()
{
	if (m_pInstance == NULL)
		return new MainWindow();

	return m_pInstance;
}

Navigator* MainWindow::getM_nvgt(){
	return m_nvgt;
}

void MainWindow::setM_nvgt(Navigator* nvgt){
	m_nvgt = nvgt;
}

mWidget* MainWindow::getMwidget()
{
	return m_wMainWnd;
}


bool MainWindow::create()
{
    return createMainWindow(STR_CAP, createMenu(), GetSystemCursor(0), 0, 
        WS_CAPTION | WS_BORDER | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_VISIBLE | WS_SYSMENU,
        WS_EX_IMECOMPOSE, 0, 0, 800, 600);
}    

bool MainWindow::ncscreateMainWindow(const char *pszCaption, HMENU hMenu,
	HCURSOR hCursor, HICON hIcon, DWORD dwStyle, DWORD dwExStyle,
	int x, int y, int w, int  h){

	    m_wMainWnd = ncsCreateMainWindow (
        NCSCTRL_MAINWND, pszCaption,
        dwStyle,
        dwExStyle,
        1, 
        x, y, w, h,
        HWND_DESKTOP,
        0, 0,
        NULL,
        NULL,
        main_handlers,
        0);

		if (m_wMainWnd != NULL)
			return true;
		else
			return false;
}

bool MainWindow::ncscreate()
{
	return ncscreateMainWindow("main window", 0, GetSystemCursor(0), 0, 
        WS_CAPTION | WS_BORDER | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_VISIBLE | WS_SYSMENU,
        WS_EX_IMECOMPOSE, 0, 0, 800, 600);
}

void MainWindow::ncsshowWindow(){
	MSG Msg;
	fprintf(stdout, "%s %s->ENTER FUNCTION\r\n", __FILE__, __FUNCTION__);
	if (m_wMainWnd == NULL)
		return;
	
	while (GetMessage (&Msg, m_wMainWnd->hwnd)) {
        TranslateMessage (&Msg);
        DispatchMessage (&Msg);
    }

	
	fprintf(stdout, "%s %s->EXIT FUNCTION\r\n", __FILE__, __FUNCTION__);
}

void MainWindow::run()
{
	
	fprintf(stdout, "%s %s->ENTER FUNCTION\r\n", __FILE__, __FUNCTION__);
#ifndef USE_MNCS
    showWindow();
#else
	ncsshowWindow();
#endif
	fprintf(stdout, "%s %s->EXIT FUNCTION\r\n", __FILE__, __FUNCTION__);

    return;
}

int MainWindow::onCreate(WPARAM wParam, LPARAM lParam)
{
    RECT client;
    getClientRect(&client);
    
    m_hMLEditWnd = CreateWindow ("medit", 
                     "",  WS_CHILD | WS_VISIBLE | WS_BORDER | WS_HSCROLL | WS_VSCROLL,
                    IDC_MLEDIT, 0, 0, client.right, client.bottom-500, getHandle(), 0);

    m_nvgt = new Navigator;
    m_nvgt->createWindow(IDC_NAVIGATOR, 0, client.bottom-499, client.right, 499, getHandle());

    return 0;
}

int MainWindow::onShowWindow(WPARAM wParam, LPARAM lParam)
{
    if (m_hMLEditWnd != HWND_INVALID)
        SetFocus (m_hMLEditWnd);
    
    return 0;
}

int MainWindow::onClose(WPARAM wParam, LPARAM lParam)
{
    if (IDYES == messageBox("Are you sure?", "Quit", MB_ICONQUESTION|MB_YESNO))
        return Wnd::onClose(wParam, lParam);
    else
        return -1;
}


HMENU MainWindow::createMenu()
{
    HMENU hmnu;
    MENUITEMINFO mii;

    hmnu = CreateMenu();

    memset (&mii, 0, sizeof(MENUITEMINFO));
    mii.type        = MFT_STRING;
    mii.id          = 100;
    mii.typedata    = (DWORD)STR_FILE;
    mii.hsubmenu    = createMenuFile ();

    InsertMenuItem(hmnu, 0, TRUE, &mii);

    mii.type        = MFT_STRING;
    mii.id          = 110;
    mii.typedata    = (DWORD)STR_HELP;
    mii.hsubmenu    = createMenuAbout ();
    InsertMenuItem(hmnu, 1, TRUE, &mii);
                       
    return hmnu;
    
}

HMENU MainWindow::createMenuFile(void)
{
    HMENU hmnu;
    MENUITEMINFO mii;
    memset (&mii, 0, sizeof(MENUITEMINFO));
    mii.type        = MFT_STRING;
    mii.id          = 0;
    mii.typedata    = (DWORD)STR_FILE;
    hmnu = CreatePopupMenu (&mii);
    
    memset (&mii, 0, sizeof(MENUITEMINFO));
    mii.type        = MFT_STRING;
    mii.state       = 0;
    mii.id          = IDM_NEW;
    mii.typedata    = (DWORD)STR_NEW;
    InsertMenuItem(hmnu, 0, TRUE, &mii);
    
    mii.type        = MFT_STRING;
    mii.state       = 0;
    mii.id          = IDM_OPEN;
    mii.typedata    = (DWORD)STR_OPEN;
    InsertMenuItem(hmnu, 1, TRUE, &mii);
    
    mii.type        = MFT_STRING;
    mii.state       = 0;
    mii.id          = IDM_SAVE;
    mii.typedata    = (DWORD)STR_SAVE;
    InsertMenuItem(hmnu, 2, TRUE, &mii);
    
    mii.type        = MFT_STRING;
    mii.state       = 0;
    mii.id          = IDM_SAVEAS;
    mii.typedata    = (DWORD)STR_SAVE_AS;
    InsertMenuItem(hmnu, 3, TRUE, &mii);

    mii.type        = MFT_SEPARATOR;
    mii.state       = 0;
    mii.id          = 0;
    mii.typedata    = 0;
    InsertMenuItem(hmnu, 4, TRUE, &mii);

    mii.type        = MFT_STRING;
    mii.state       = 0;
    mii.id          = IDM_PRINT;
    mii.typedata    = (DWORD)STR_PRINT;
    InsertMenuItem(hmnu, 5, TRUE, &mii);
    
    mii.type        = MFT_SEPARATOR;
    mii.state       = 0;
    mii.id          = 0;
    mii.typedata    = 0;
    InsertMenuItem(hmnu, 6, TRUE, &mii);

    mii.type        = MFT_STRING;
    mii.state       = 0;
    mii.id          = IDM_EXIT;
    mii.typedata    = (DWORD)STR_EXIT;
    InsertMenuItem(hmnu, 7, TRUE, &mii);

    return hmnu;
}

HMENU MainWindow::createMenuAbout(void)
{
    HMENU hmnu;
    MENUITEMINFO mii;
    memset (&mii, 0, sizeof(MENUITEMINFO));
    mii.type        = MFT_STRING;
    mii.id          = 0;
    mii.typedata    = (DWORD)STR_HELP;
    hmnu = CreatePopupMenu (&mii);
    
    memset (&mii, 0, sizeof(MENUITEMINFO));
    mii.type        = MFT_STRING ;
    mii.state       = 0;
    mii.id          = IDM_ABOUT_THIS;
    mii.typedata    = (DWORD)STR_ABOUT;
    InsertMenuItem(hmnu, 0, TRUE, &mii);
    
    return hmnu;
}


