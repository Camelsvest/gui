#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>

#include <mgncs.h>
#include "navigatorpage.h"
#include "logging.h"

static void mNavigatorPage_construct (mNavigatorPage *self,DWORD addData)
{
	g_stmContainerCls.construct((mContainer*)self,  addData);

    self->titleWidth = 0;
    self->hIcon = 0;
}

static const char* mNavigatorPage_getTitle(mNavigatorPage* self)
{
    return GetWindowCaption(self->hwnd);
}



/* +------------+------------+------------+------------+   <- TAB
 * |            |            |            |            |   
 * |   Icon1    |   Icon2    |   Icon3    |    Icon4   |   
 * |   text1    |   text2    |   text3    |    text4   |
 * |            |            |            |            |
 * +------------+------------+------------+------------+   <- Page
 * |            |            |            |            |
 * |            |            |            |            |
 * |            |            |            |            |
 * |            |            |            |            |
 * |            |            |            |            |
 * +------------+------------+------------+------------+
 */

static void mNavigatorPage_getTitleWidth (mNavigatorPage* self, HDC hdc)
{
    int     icon_heigh, icon_width = 0, width = 0;
    SIZE    ext;
    char*   title;

    ENTER_FUNCTION;
    
    title = (char*)GetWindowCaption(self->hwnd);

    if (title) {
        GetTextExtent (hdc, title, -1, &ext);
        width = ext.cx;
        logging_trace("Text width = %d\r\n", width);
    }

    if (self->hIcon && GetIconSize(self->hIcon, &icon_width, &icon_heigh)) {
        logging_trace("Icon width = %d\r\n", icon_width);
        if (icon_width > width)
            width = icon_width;
    }

    self->titleWidth = width;

    logging_trace("%s: titleWidth = %d\r\n", __FUNCTION__, width);

    EXIT_FUNCTION;
}

BOOL mNavigatorPage_setTitle(mNavigatorPage* self, const char* title)
{
    return SetWindowCaption(self->hwnd, title);
}

int mNavigatorPage_getTitleLength(mNavigatorPage* self)
{
    return strlen(GetWindowCaption(self->hwnd));
}

static void mNavigatorPage_showPage (mNavigatorPage* self, int showCmd)
{
    HWND focus;

    ShowWindow (self->hwnd, showCmd);

    focus = GetNextDlgTabItem (self->hwnd, (HWND)0, 0);
    if (SendMessage (self->hwnd, MSG_SHOWPAGE, (WPARAM)focus, (LPARAM)showCmd)
            && showCmd == SW_SHOW) {
        if (focus) SetFocus(focus);
    }
}

BOOL mNavigatorPage_setIcon(mNavigatorPage* self, HICON icon)
{
    if (self == NULL)
        return FALSE;

    self->hIcon = icon;
    return TRUE;
}

HICON mNavigatorPage_getIcon(mNavigatorPage* self)
{
    if (self == NULL)
        return 0;

    return self->hIcon;
}

BOOL mNavigatorPage_callUserHandler(mNavigatorPage *self, void* handler, UINT message, WPARAM wParam, LPARAM lParam, LRESULT *pret)
{
	if(handler == NULL)
		return FALSE;

	switch(message)
	{
	case MSG_INITPAGE:
		((NCS_CB_ONINITNVGTRPAGE)handler)(self, lParam);
        return TRUE;

	case MSG_SHOWPAGE:
		*pret = ((NCS_CB_ONSHOWNVGTRPAGE)handler)(self, (HWND)wParam, (int)lParam);
		return TRUE;

	case MSG_SHEETCMD:
		*pret = ((NCS_CB_ONNVGTRCMD)handler)(self, (DWORD)wParam, (DWORD)lParam);
		return TRUE;
	}

	return Class(mContainer).callUserHandler((mContainer*)self, handler, message, wParam, lParam, pret);
}

BEGIN_CMPT_CLASS(mNavigatorPage, mContainer)
    CLASS_METHOD_MAP(mNavigatorPage, construct);
    CLASS_METHOD_MAP(mNavigatorPage, showPage);
    CLASS_METHOD_MAP(mNavigatorPage, getTitleWidth);
    CLASS_METHOD_MAP(mNavigatorPage, setTitle);
    CLASS_METHOD_MAP(mNavigatorPage, getTitle);
    CLASS_METHOD_MAP(mNavigatorPage, setIcon);
    CLASS_METHOD_MAP(mNavigatorPage, getIcon);
    CLASS_METHOD_MAP(mNavigatorPage, getTitleLength);
	CLASS_METHOD_MAP(mNavigatorPage, callUserHandler)
	SET_DLGCODE(DLGC_WANTTAB | DLGC_WANTARROWS)
END_CMPT_CLASS
