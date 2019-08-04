/*
    The implementation of mPropsheet control.

    This file is part of mGNCS, a component for MiniGUI.

    Copyright (C) 2008~2018, Beijing FMSoft Technologies Co., Ltd.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Or,

    As this program is a library, any link to this program must follow
    GNU General Public License version 3 (GPLv3). If you cannot accept
    GPLv3, you need to be licensed from FMSoft.

    If you have got a commercial license of this program, please use it
    under the terms and conditions of the commercial license.

    For more information about the commercial license, please refer to
    <http://www.minigui.com/en/about/licensing-policy/>.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>

#include <mgncs.h>
#include "mnavigatorpage.h"


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

static void mNavigatorPage_getTitleWidth (mNavigatorPage* self, HDC hdc)
{
    int     width = 0;
    SIZE    ext;
    char*   title;

    title = (char*)GetWindowCaption(self->hwnd);

    if (title) {
        GetTextExtent (hdc, title, -1, &ext);
        width = ext.cx;
    }

    if (self->hIcon) {
        width += 16;
    }

    self->titleWidth = width;
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
		((NCS_CB_ONINITPAGE)handler)(self, lParam);
        return TRUE;

	case MSG_SHOWPAGE:
		*pret = ((NCS_CB_ONSHOWPAGE)handler)(self, (HWND)wParam, (int)lParam);
		return TRUE;

	case MSG_SHEETCMD:
		*pret = ((NCS_CB_ONSHEETCMD)handler)(self, (DWORD)wParam, (DWORD)lParam);
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
