#include <string.h>
#include <stdexcept>

#include "mainwindow.h"
#include "navigatorres.h"
#include "trace.h"

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

NCS_EVENT_HANDLER MainWindow::m_mainHandlers [] = {
    {MSG_CREATE,        reinterpret_cast<void*>(MainWindow::main_onCreate)},
    {MSG_CLOSE,         reinterpret_cast<void*>(MainWindow::main_onClose)},    
    {0, NULL}
};

MainWindow::MainWindow()
    : m_hMainWnd(HWND_INVALID)
{
}

MainWindow::~MainWindow()
{
}

MainWindow* MainWindow::getInstance()
{
	if (m_pInstance == NULL)
		m_pInstance = new MainWindow();

	return m_pInstance;
}

void MainWindow::release()
{
    if (m_pInstance)
    {
        delete m_pInstance;
        m_pInstance = NULL;
    }
}

bool MainWindow::ncscreateMainWindow(
                    const char *pszCaption, HMENU hMenu, HCURSOR hCursor,
                    HICON hIcon, DWORD dwStyle, DWORD dwExStyle,
                    int x, int y, int w, int  h) {
    mWidget *widget;                
    ENTER_CLASS_FUNCTION("MainWindow");
    
    widget = ::ncsCreateMainWindow (
        NCSCTRL_MAINWND,
        pszCaption,
        dwStyle,
        dwExStyle,
        IDC_MAINWND, 
        x, y, w, h,
        HWND_DESKTOP,
        hIcon, hMenu,
        NULL,
        NULL,
        m_mainHandlers,
        (DWORD)this);

    EXIT_CLASS_FUNCTION("MainWindow");

    if (widget != NULL)
    {
        m_hMainWnd = widget->hwnd;
        logging_trace("Create MainWindow: %p\r\n", m_hMainWnd);
        
        return true;
    }
    else
        return false;

}

bool MainWindow::ncscreate()
{
	return ncscreateMainWindow(
        "MainWindow",  
        createMenu(),
        GetSystemCursor(0),
        0, // hIcon
        WS_CAPTION | WS_BORDER | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_VISIBLE | WS_SYSMENU,
        0,  // dwExStyle
        0,
        0,
        800,
        600);
}

void MainWindow::ncsshowWindow(){
	MSG Msg;

    ENTER_CLASS_FUNCTION("MainWindow");
	if (m_hMainWnd == NULL)
		return;
	
	while (GetMessage (&Msg, m_hMainWnd)) {
        TranslateMessage (&Msg);
        DispatchMessage (&Msg);
    }

    EXIT_CLASS_FUNCTION("MainWindow");
}

void MainWindow::run()
{	
	ENTER_CLASS_FUNCTION("MainWindow");
    
	ncsshowWindow();

    EXIT_CLASS_FUNCTION("MainWindow");

    return;
}

BOOL MainWindow::main_onCreate(mWidget* self, DWORD dwAddData )
{   
    BOOL ret;
    MainWindow *pThis;
    
    ENTER_CLASS_FUNCTION("MainWindow");
    
	pThis = reinterpret_cast<MainWindow *>(dwAddData);
	ret = pThis->onCreate(self->hwnd);
    
    EXIT_CLASS_FUNCTION("MainWindow");
    
	return ret;
}

BOOL MainWindow::onCreate(HWND hWnd)
{
    RECT rc;
    GetClientRect(hWnd, &rc);

    return m_Navigator.createWindow(hWnd, &rc) ? TRUE : FALSE;
}

BOOL MainWindow::main_onClose(mWidget* self, int message)
{
    ENTER_CLASS_FUNCTION("MainWindow");

    ::DestroyMainWindow(self->hwnd);
    ::PostQuitMessage(self->hwnd);

    EXIT_CLASS_FUNCTION("MainWindow");
    
    return TRUE;    
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


