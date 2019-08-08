#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>

#include <mgncs.h>
#include "navigator.h"
#include "logging.h"

#define ICON_OFFSET 2

extern mWidgetRenderer skin_widget_renderer;

static void skin_resetHeadArea (mNavigator *self, RECT* rcClient, DWORD style)
{
    int height, minHeight, maxHeight = 256;
    DWORD key;
    PBITMAP pBmp;

    minHeight = 16 + 4 + 2* ICON_OFFSET;
    key = ncsGetElement((mWidget*)self, NCS_IMAGE_PRPSHT_TAB);
    pBmp = GetBitmapFromRes (key);
    if (pBmp) {
        height = (pBmp->bmHeight>>2) + 2*(ICON_OFFSET+1);
    }
    else {
        height = minHeight;
    }
    if (height < minHeight)
        height = minHeight;

    if (height > maxHeight)
        height = maxHeight;

    self->headRect.left = 0;
    self->headRect.right = RECTWP(rcClient);

    if ((style&NCSS_NVGTR_TABMASK) == NCSS_NVGTR_BOTTOM) {
        self->headRect.bottom = RECTHP(rcClient);
    }
    else {
        self->headRect.bottom = height;
    }

    self->headRect.top = self->headRect.bottom - height;
    self->maxTabWidth = RECTW(self->headRect);
    self->scrollTabWidth = RECTW(self->headRect) - 2*16;
}

static void skin_getRect(mNavigator *self,
        RECT* rcClient, RECT* rcResult, int which)
{
    int     btnSize = 16;
    int     tabBorder = 2;
    DWORD   style = GetWindowStyle (self->hwnd);
    char    msg[][32] = {
        "NCSF_NVGTR_BORDER",
        "NCSF_NVGTR_TAB",
        "NCSF_NVGTR_LEFT",
        "NCSF_NVGTR_RIGHT",
        "NCSF_NVGTR_PAGE"
    };        
        
        
    ENTER_FUNCTION;
    
    switch (which)
    {
        case NCSF_NVGTR_BORDER:
        {
            RECT rcWin;
            GetWindowRect (self->hwnd, &rcWin);

            rcResult->left = 0;
            rcResult->right = self->headRect.right;

            if ((style & NCSS_NVGTR_TABMASK) == NCSS_NVGTR_BOTTOM) {
                rcResult->top = 0;
                rcResult->bottom = RECTH(rcWin) - RECTH(self->headRect) + tabBorder;
            }
            else {
                rcResult->top = self->headRect.bottom - tabBorder;
                rcResult->bottom = RECTH(rcWin) ;
            }
            break;
        }
        case NCSF_NVGTR_PAGE:
        {
            rcResult->left = tabBorder;
            rcResult->right = rcClient->right - tabBorder;

            if ((style & NCSS_NVGTR_TABMASK) == NCSS_NVGTR_BOTTOM) {
                rcResult->top = tabBorder;
            }
            else {
                rcResult->top = self->headRect.bottom;
            }
            rcResult->bottom = rcResult->top + RECTHP(rcClient)
                - RECTH(self->headRect) - 2 * tabBorder;
            break;
        }
        case NCSF_NVGTR_TAB:
        {
            rcResult->top = self->headRect.top;
            rcResult->bottom = self->headRect.bottom;

            if ((style&NCSS_NVGTR_BTNMASK) == NCSS_NVGTR_SCROLLABLE
                    &&self->btnShow) {
                rcResult->left = self->headRect.left + btnSize;
                rcResult->right = self->headRect.right - btnSize;
            }
            else {
                rcResult->left = self->headRect.left;
                rcResult->right = self->headRect.right;
            }

            break;
        }
        case NCSF_NVGTR_LEFT:
            if ((style&NCSS_NVGTR_BTNMASK) == NCSS_NVGTR_SCROLLABLE
                    &&self->btnShow) {
                rcResult->left = self->headRect.left;
                rcResult->right = rcResult->left + btnSize;
                rcResult->top = self->headRect.top;
                rcResult->bottom = self->headRect.bottom;
            }
            else {
                SetRectEmpty(rcResult);
            }
            break;

        case NCSF_NVGTR_RIGHT:
            if ((style&NCSS_NVGTR_BTNMASK) == NCSS_NVGTR_SCROLLABLE
                    &&self->btnShow) {
                rcResult->right = self->headRect.right;
                rcResult->left = rcResult->right - btnSize;
                rcResult->top = self->headRect.top;
                rcResult->bottom = self->headRect.bottom;
            }
            else {
                SetRectEmpty(rcResult);
            }
            break;

        default:
            break;
    }

    logging_trace("%s: rcResult(left = %d, top = %d, right = %d, bottom = %d)\r\n", 
        msg[which], rcResult->left, rcResult->top, rcResult->right, rcResult->bottom);
    
    EXIT_FUNCTION;
    return;
}

static void skin_drawBorder(mNavigator *self, HDC hdc, RECT* rcBorder)
{
    DWORD color, light_c, darker_c, darkest_c;

    color = ncsGetElement((mWidget*)self, NCS_BGC_3DBODY);
	light_c   = ncsCommRDRCalc3dboxColor(color, NCSR_COLOR_LIGHTEST);
	darker_c  = ncsCommRDRCalc3dboxColor(color, NCSR_COLOR_DARKER);
	darkest_c = ncsCommRDRCalc3dboxColor(color, NCSR_COLOR_DARKEST);

    rcBorder->right--;
    rcBorder->bottom--;

    SetPenColor(hdc, DWORD2Pixel (hdc, light_c));
    MoveTo (hdc, rcBorder->left, rcBorder->bottom - 1);
    LineTo (hdc, rcBorder->left, rcBorder->top + 1);
    LineTo (hdc, rcBorder->right - 1, rcBorder->top + 1);

    SetPenColor (hdc, DWORD2Pixel (hdc, darkest_c));
    MoveTo (hdc, rcBorder->left, rcBorder->bottom);
    LineTo (hdc, rcBorder->right, rcBorder->bottom);
    LineTo (hdc, rcBorder->right, rcBorder->top + 1);

    SetPenColor (hdc, DWORD2Pixel (hdc, darker_c));
    MoveTo (hdc, rcBorder->left + 1, rcBorder->bottom - 1);
    LineTo (hdc, rcBorder->right - 1, rcBorder->bottom - 1);
    LineTo (hdc, rcBorder->right - 1, rcBorder->top + 2);

    return;
}

static void skin_drawScrollBtn(mNavigator *self, HDC hdc,
        RECT* rcBtn, int which)
{
	self->renderer->drawArrow(self, hdc, rcBtn, which, 0L, TRUE);
}

static void skin_drawTab(mNavigator *self, HDC hdc,
        RECT* rcTab, const char* title, HICON hIcon, BOOL active)
{
    int x, ty, by;
    DWORD key;
    DRAWINFO di;
    BOOL bottom;
	RECT rc;

    ENTER_FUNCTION;
    key = ncsGetElement((mWidget*)self, NCS_IMAGE_PRPSHT_TAB);
    if (!(di.bmp = GetBitmapFromRes (key))) {
        EXIT_FUNCTION;
        return;
    }

    bottom = (GetWindowStyle(self->hwnd) & NCSS_NVGTR_TABMASK) == NCSS_NVGTR_BOTTOM;

    di.nr_line  = 4;
    di.nr_col   = 1;
    di.idx_col  = 0;
    di.margin1  = 3;
    di.margin2  = 4;
    di.direct   = FALSE;
    di.flip     = bottom ? TRUE : FALSE;
    di.idx_line = 0;
    di.style    = DI_FILL_TILE;

    x = rcTab->left + 2;
    ty = rcTab->top;

    if (!active) {
        if (bottom) {
            ty -= 2;
            by = rcTab->bottom - 2;
        } else {
            ty += 2;
            by = rcTab->bottom;
        }

     } else {
        di.idx_line = 2;
        by = rcTab->bottom;
     }

    ncsSkinDraw (hdc, rcTab, &di);

    /* draw the ICON */
    ty += 2 + 2;
    if (hIcon) {
        int icon_x, icon_y;
        icon_x = RECTHP(rcTab) - 8;
        icon_y = icon_x;

        DrawIcon (hdc, x, ty, icon_x, icon_y, hIcon);
        x += icon_x;
        x += 2;
    }

    /* draw the TEXT */
    SetBkMode (hdc, BM_TRANSPARENT);
    SetRect(&rc, x, ty, rcTab->right, by);
    DrawText(hdc, title, -1, &rc, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

    EXIT_FUNCTION;
}


static void skin_navigator_class_init (mNavigatorRenderer* rdr)
{
	skin_widget_renderer.class_init((mWidgetRenderer*)rdr);
	rdr->resetHeadArea = skin_resetHeadArea;
	rdr->getRect       = skin_getRect;
	rdr->drawScrollBtn = skin_drawScrollBtn;
	rdr->drawBorder    = skin_drawBorder;
	rdr->drawTab       = skin_drawTab;
}

mNavigatorRenderer skin_navigator_renderer = {
    "",
	skin_navigator_class_init,
	&skin_widget_renderer,
};

BOOL InitNavigatorSkinRenderer(void)
{
	int i;
	NCS_RDR_ENTRY entries [] = {
		{ NCSCTRL_NAVIGATOR, (mWidgetRenderer *)(void *)(&skin_navigator_renderer) }
	};


	for(i=0; i< sizeof(entries)/sizeof(NCS_RDR_ENTRY); i++)
	{
		entries[i].renderer->class_init(entries[i].renderer);
		if(entries[i].renderer->init_self)
			entries[i].renderer->init_self(entries[i].renderer);
	}

	return ncsRegisterCtrlRDRs("skin", entries,
            sizeof(entries)/sizeof(NCS_RDR_ENTRY));
    
}
