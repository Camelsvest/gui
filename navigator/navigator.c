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

/*for page handle*/
#define IDC_PAGE    20

BOOL RegisterNavigatorComponent()
{
    if(!ncsRegisterComponent(
            (mComponentClass*)MGNCS_INIT_CLASS(mNavigatorPage), 
            WS_HSCROLL | WS_VSCROLL,
            WS_EX_NONE,
            IDC_ARROW,
            WE_MAINC_THREED_BODY))
		return FALSE;
    
	if(!ncsRegisterComponent(	
            (mComponentClass*)MGNCS_INIT_CLASS(mNavigator), 
            WS_NONE,
            WS_EX_NONE,
            IDC_ARROW,
            WE_MAINC_THREED_BODY))
        return FALSE;

    return TRUE;                
}

BOOL UnregisterNavigatorComponent()
{
    if (!UnregisterWindowClass(Class(mNavigatorPage).className))
        return FALSE;

    if (!UnregisterWindowClass(Class(mNavigator).className))
        return FALSE;

    return TRUE;
}

static void mNavigator_construct (mNavigator *self, DWORD addData)
{
    RECT rcClient;
	g_stmWidgetCls.construct((mWidget*)self,  addData);

    GetClientRect (self->hwnd, &rcClient);

    self->minTabWidth = 16;
    self->active = self->firstView = NULL;
    self->pageCount = 0;
    self->tabMargin = 8;
    self->btnShow = FALSE;
    self->scrollTabWidth = RECTW(rcClient);
}

#define NEXTPAGE(self, page) \
    _c(self)->getNextPage(self, page)

#define PREVPAGE(self, page) \
    _c(self)->getPrevPage(self, page)

static mNavigatorPage* createPage (mNavigator* self,
        PDLGTEMPLATE dlgTemplate, DWORD style,
        const NCS_EVENT_HANDLER *handlers)
{
    mNavigatorPage*  page;
    DWORD   exStyle;
    RECT    rcClient, rcPage;

    if (GetWindowExStyle(self->hwnd) & WS_EX_TRANSPARENT)
        exStyle = WS_EX_TRANSPARENT | WS_EX_USEPARENTRDR;
    else
        exStyle = WS_EX_USEPARENTRDR;

    GetClientRect(self->hwnd, &rcClient);
    self->renderer->getRect(self, &rcClient, &rcPage, NCSF_NVGTR_PAGE);

    page = (mNavigatorPage*)ncsCreateWindow (
                        NCSCTRL_NAVIGATORPAGE,
                        dlgTemplate->caption,
                        WS_NONE, /* WS_VISIBLE */
                        exStyle,
                        IDC_PAGE,
                        rcPage.left, rcPage.top,
                        RECTW(rcPage), RECTH(rcPage),
                        self->hwnd,
                        NULL,
                        NULL,
                        (NCS_EVENT_HANDLER*)handlers,
                        dlgTemplate->dwAddData);

    if (!page) {
        logging_error("createPage Error> create page window error. \n ");
        return NULL;
    }

    _c(page)->setIcon(page, dlgTemplate->hIcon);

    if (!_c(page)->addIntrinsicControls(page,
                dlgTemplate->controls, dlgTemplate->controlnr)) {
        logging_error("createPage Error> set controls error. \n ");
        DestroyWindow(page->hwnd);
        return NULL;
    }

    SendMessage (page->hwnd, MSG_INITPAGE, 0, dlgTemplate->dwAddData);

    return page;
}

static void updateNavigator (mNavigator* self)
{
    mNavigatorPage   *page, *tmp, *list;
    int     tabWidth = 0;

    ENTER_FUNCTION;
    
    list = NEXTPAGE(self, NULL);

    /*set btnShow status*/
    page = list;
    self->btnShow = FALSE;

    while (page) {
        tabWidth += page->titleWidth;

        if (tabWidth > self->scrollTabWidth) {
            self->btnShow = TRUE;
            self->maxTabWidth = self->scrollTabWidth;
            break;
        }
        page = NEXTPAGE(self, page);
    }

    if (self->firstView == NULL || self->btnShow == FALSE) {
        self->firstView = list;
    }

    //firstView should be previous to active page
    if (self->active) {
        page = NEXTPAGE(self, self->active);

        while (page) {
            if (page == self->firstView) {
                self->firstView = self->active;
                break;
            }
            page = NEXTPAGE(self, page);
        }
    }

    page = self->firstView;

    while (page) {
        tmp = page;
        tabWidth = 0;

        while (tmp) {
            tabWidth += tmp->titleWidth;

            if (tmp == self->active) {
                if (tabWidth <= self->maxTabWidth) {
                    return;
                }
            }
            tmp = NEXTPAGE(self, tmp);
        }

        self->firstView = NEXTPAGE(self, self->firstView);
        page = self->firstView;
    }

    EXIT_FUNCTION;
}

static void calcScrollPageTitleWidth (HDC hdc, mNavigator* self, mNavigatorPage* page)
{
    ENTER_FUNCTION;
    
    _c(page)->getTitleWidth(page, hdc);

    page->titleWidth += self->tabMargin;
    logging_trace("%s: titleWidth + tabMargin(%d) = %d\r\n", __FUNCTION__, self->tabMargin, page->titleWidth);

    if (page->titleWidth < self->minTabWidth) {
        page->titleWidth = self->minTabWidth;
    }

    if (page->titleWidth > self->scrollTabWidth) {
        page->titleWidth = self->scrollTabWidth;
    }

    EXIT_FUNCTION;
}

static void recalcTabWidths (mNavigator* self, DWORD style)
{
    mNavigatorPage*  page;
    HDC     hdc;

    ENTER_FUNCTION;
    
    if (self->pageCount == 0)
    {
        EXIT_FUNCTION;
        return;
    }

    if (style & NCSS_NVGTR_COMPACTTAB) {
        int totalWidth = 0;

        hdc = GetClientDC (self->hwnd);
        page = NEXTPAGE(self, NULL);

        while (page) {
            page->titleWidth = 0;
            _c(page)->getTitleWidth(page, hdc);
            page->titleWidth += self->tabMargin;

            if (page->titleWidth < self->minTabWidth) {
                page->titleWidth = self->minTabWidth;
            }

            totalWidth += page->titleWidth;

            if (totalWidth > RECTW(self->headRect)) {
                int tmpWidth;
                totalWidth -= page->titleWidth;
                tmpWidth = RECTW(self->headRect) - totalWidth;
                if (tmpWidth >= self->minTabWidth)
                    page->titleWidth = tmpWidth;
                break;
            }
            page = NEXTPAGE(self, page);
        }
        ReleaseDC (hdc);
        self->maxTabWidth = totalWidth;
    }
    else {
        int width = RECTW(self->headRect)/self->pageCount;
        int remainder = RECTW(self->headRect)%self->pageCount;
        int i = 0;

        page = NEXTPAGE(self, NULL);
        while(page) {
            page->titleWidth = width;
            if (i < remainder) {
                page->titleWidth ++;
                i++;
            }
            page = NEXTPAGE(self, page);
        }

        self->maxTabWidth = RECTW(self->headRect);
    }

    EXIT_FUNCTION;
}

static BOOL changeActivePage(mNavigator* self,
        mNavigatorPage* page, DWORD style, BOOL reCount)
{
    HDC hdc;

    ENTER_FUNCTION;
    
    if (!page) {
        EXIT_FUNCTION;
        return FALSE;
    }

    if (page != self->active) {
        /*hide active page*/
        if (self->active) {
            _c((self->active))->showPage (self->active, SW_HIDE);
        }

        /*change active page*/
        self->active = page;

        /*change firstView page for scrollable style*/
        if ((style&NCSS_NVGTR_BTNMASK) == NCSS_NVGTR_SCROLLABLE) {

            hdc = GetClientDC (self->hwnd);
            calcScrollPageTitleWidth (hdc, self, page);
            ReleaseDC (hdc);

            updateNavigator(self);
        }

        /*notify parent activeChanged*/
        ncsNotifyParent ((mWidget*)self, NCSN_NVGTR_ACTIVECHANGED);

        /*show new active page*/
        _c(page)->showPage (page, SW_SHOW);

        if (((style&NCSS_NVGTR_BTNMASK) != NCSS_NVGTR_SCROLLABLE)
                && reCount) {
            recalcTabWidths (self, style);
        }

        InvalidateRect (self->hwnd, &(self->headRect), TRUE);

        EXIT_FUNCTION;
        return TRUE;
    }

    EXIT_FUNCTION;
    return FALSE;
}

static int mNavigator_onSizeChanged(mNavigator* self, RECT* prcClient)
{
    DWORD   style = GetWindowStyle (self->hwnd);
    mNavigatorPage   *page = NEXTPAGE(self, NULL);
    RECT    rcPage;
	RECT    rcClient = {0, 0, RECTWP(prcClient), RECTHP(prcClient)};

    ENTER_FUNCTION;

    self->renderer->resetHeadArea(self, &rcClient, style);

    if ((style&NCSS_NVGTR_BTNMASK) != NCSS_NVGTR_SCROLLABLE) {
        recalcTabWidths (self, style);
    }
    else {
        self->scrollTabWidth = RECTW(self->headRect);
        updateNavigator(self);
    }

    if (page)
        self->renderer->getRect (self, &rcClient, &rcPage, NCSF_NVGTR_PAGE);

    while(page) {
        MoveWindow (page->hwnd, rcPage.left, rcPage.top,
                RECTW(rcPage), RECTH(rcPage), page == self->active);
        page = NEXTPAGE(self, page);
    }

    InvalidateRect (self->hwnd, &(self->headRect), TRUE);

    EXIT_FUNCTION;
    
    return 0;
}

static int mNavigator_onLButtonDown(mNavigator* self,
        int x, int y, DWORD key_flags)
{
    DWORD   style;
    mNavigatorPage*  page = NULL;
    RECT    rcClient, rcResult, rcTab;

    if (!PtInRect (&(self->headRect), x, y))
        return 1;

    style = GetWindowStyle (self->hwnd);
    GetClientRect(self->hwnd, &rcClient);

    self->renderer->getRect(self, &rcClient, &rcResult, NCSF_NVGTR_TAB);

    if (!PtInRect (&rcResult, x, y)) {
        if (!self->btnShow) {
            return 1;
        }
        self->renderer->getRect(self, &rcClient, &rcResult, NCSF_NVGTR_LEFT);
        if (!PtInRect (&rcResult, x, y)) {
            self->renderer->getRect(self, &rcClient, &rcResult, NCSF_NVGTR_RIGHT);
            if (!PtInRect (&rcResult, x, y)) {
                return 1;
            }
            else {
                /*right*/
                page = NEXTPAGE(self, self->active);
            }
        }
        else {
            /*left*/
            page = PREVPAGE(self, self->active);
        }
    }
    else {
        /*tab*/
        if ((style & NCSS_NVGTR_BTNMASK) == NCSS_NVGTR_SCROLLABLE) {
            page = self->firstView;
        }
        else  {
            page = NEXTPAGE(self, NULL);
        }

        rcTab.right = rcResult.left;
        rcTab.top = rcResult.top;
        rcTab.bottom = rcResult.bottom;
        while (page) {
            rcTab.left = rcTab.right;
            rcTab.right += page->titleWidth;

            if (rcTab.right > rcResult.right) {
                page = NULL;
                break;
            }

            if (PtInRect (&rcTab, x, y)) {
                break;
            }

            page = NEXTPAGE(self, page);
        }
    }

    if (!page)
        return 1;

    changeActivePage(self, page, style, FALSE);
	return 0;
}

static int mNavigator_onKeyDown(mNavigator* self, int scancode, int state)
{
    mNavigatorPage   *activePage = NULL;
    DWORD   style;

    if (!(state & KS_CTRL) || !NEXTPAGE(self, NULL))
        return 1;

    style = GetWindowStyle (self->hwnd);

    switch (scancode) {
        case SCANCODE_CURSORBLOCKDOWN:
        case SCANCODE_CURSORBLOCKRIGHT:
            activePage = NEXTPAGE(self, self->active);
            break;

        case SCANCODE_CURSORBLOCKUP:
        case SCANCODE_CURSORBLOCKLEFT:
            activePage = PREVPAGE(self, self->active);
            break;
    }

    if (activePage)
        changeActivePage(self, activePage, style, FALSE);

    return 0;
}

static mNavigatorPage* mNavigator_addPage(mNavigator* self,
        const PDLGTEMPLATE dlgTemplate,
        const NCS_EVENT_HANDLER * handlers)
{
    mNavigatorPage*  page;
    DWORD   style;

    ENTER_FUNCTION;
    
    if ((dlgTemplate ->controlnr > 0) && !dlgTemplate->controls) {
        logging_error("addPage Error> controls info error.\n");
        EXIT_FUNCTION;
        return NULL;
    }

    style = GetWindowStyle (self->hwnd);

    if ((style&NCSS_NVGTR_BTNMASK) != NCSS_NVGTR_SCROLLABLE) {
        if (RECTW(self->headRect) /(self->pageCount + 1) < self->minTabWidth) {
            logging_error("addPage Error> headRect width error.\n");
            EXIT_FUNCTION;
            return NULL;
        }
    }

    if (!(page = createPage (self, dlgTemplate, style, handlers))) {
        logging_error("addPage Error> create page error.\n");
        EXIT_FUNCTION;
        return NULL;
    }

    self->pageCount++;

    if (self->pageCount == 1) {
        /* only set the first page as the active page */
        changeActivePage(self, page, style, TRUE);
    }

    EXIT_FUNCTION;
    return page;
}

static BOOL mNavigator_removePage(mNavigator* self, mNavigatorPage* delPage)
{
    mNavigatorPage   *next, *prev = NULL;
    DWORD   style;
    BOOL    activeChanged = FALSE;

    if (!delPage)
        return FALSE;

    style = GetWindowStyle(self->hwnd);

    next = NEXTPAGE(self, delPage);

    if ((style & NCSS_NVGTR_BTNMASK) != NCSS_NVGTR_SCROLLABLE) {
        if (!next)
            prev = PREVPAGE(self, delPage);

        DestroyWindow (delPage->hwnd);
        self->pageCount --;
        recalcTabWidths (self, style);

        if (self->active == delPage) {
            if (!next)
                self->active = prev;
            else
                self->active = next;

            ncsNotifyParent ((mWidget*)self, NCSN_NVGTR_ACTIVECHANGED);
            if (self->active) {
                _c(self->active)->showPage(self->active, SW_SHOW);
            }
        }

        InvalidateRect (self->hwnd, &(self->headRect), TRUE);
    }
    else {
        if (self->active == delPage) {
            if (next) {
                self->active = next;
                if (self->firstView == delPage)
                    self->firstView = next;
            }
            else {
                prev = PREVPAGE(self, delPage);
                self->active = prev;
                if (self->firstView == delPage)
                    self->firstView = prev;
            }
            activeChanged = TRUE;
        }
        else {
            /*delPage isn't active page*/
            if (self->firstView == delPage) {
                if(next)
                    self->firstView = next;
                else
                    self->firstView = PREVPAGE(self, delPage);
            }
        }
        DestroyWindow (delPage->hwnd);
        self->pageCount--;

        if (NEXTPAGE(self, NULL))  updateNavigator(self);

        if (activeChanged)
            ncsNotifyParent ((mWidget*)self, NCSN_NVGTR_ACTIVECHANGED);

        if (self->active) {
            _c(self->active)->showPage(self->active, SW_SHOW);
        }

        InvalidateRect (self->hwnd, &(self->headRect), TRUE);
    }
    return TRUE;
}

static mNavigatorPage* mNavigator_getPrevPage(mNavigator* self, mNavigatorPage* page)
{
    HWND child, next;

    if (!page)
        return NULL;

    child = GetNextChild(self->hwnd, HWND_NULL);

    while (child && (child != HWND_INVALID)) {
        next = GetNextChild(self->hwnd, child);
        if (next == page->hwnd)
            return (mNavigatorPage*)GetWindowAdditionalData2(child);
        child = next;
    }

    return NULL;
}

static mNavigatorPage* mNavigator_getNextPage(mNavigator* self, mNavigatorPage* page)
{
    HWND child;

    if (!page) /*for first page*/
        child = GetNextChild(self->hwnd, HWND_NULL);
    else
        child = GetNextChild(self->hwnd, page->hwnd);

    if (child && (child != HWND_INVALID))
        return (mNavigatorPage*)GetWindowAdditionalData2(child);
    else
        return NULL;
}


static int mNavigator_broadCastMsg(mNavigator* self, DWORD info1, DWORD info2)
{
    int     idx = 0;
    mNavigatorPage*  page = NEXTPAGE(self, NULL);

    while (page) {
        if (SendMessage (page->hwnd, MSG_SHEETCMD, info1, info2))
            return idx + 1;
        idx++;
        page = NEXTPAGE(self, page);
    }
    return 0;
}

static BOOL mNavigator_setActivePage(mNavigator* self, mNavigatorPage *page)
{
    DWORD style;

    if (!page)
        return FALSE;

    style = GetWindowStyle(self->hwnd);
    return changeActivePage(self, page, style, FALSE);
}

static int mNavigator_getPageIndex(mNavigator* self, mNavigatorPage* page)
{
    int     idx = 0;
    HWND    list = GetNextChild (self->hwnd, HWND_NULL);

    while (list && (list != HWND_INVALID)) {
        if (list == page->hwnd)
            return idx;
        idx ++;
        list = GetNextChild(self->hwnd, list);
    }
    return -1;
}

static mNavigatorPage* mNavigator_getPageByIndex(mNavigator* self, int pageIndex)
{
    int     idx = 0;
    HWND    list = GetNextChild (self->hwnd, HWND_NULL);

    while (list && (list != HWND_INVALID)) {
        if (idx == pageIndex) {
            return (mNavigatorPage*)GetWindowAdditionalData2(list);
        }
        idx ++;
        list = GetNextChild(self->hwnd, list);
    }
    return NULL;
}

static BOOL mNavigator_setActivePageByIndex(mNavigator* self, int pageIndex)
{
    mNavigatorPage*  page;
    DWORD style;

    page = _c(self)->getPageByIndex(self, pageIndex);
    if (!page)
        return FALSE;

    style = GetWindowStyle(self->hwnd);

    return changeActivePage(self, page, style, FALSE);
}

static BOOL mNavigator_removePageByIndex(mNavigator* self, int pageIndex)
{
    mNavigatorPage*  page = _c(self)->getPageByIndex(self, pageIndex);
    return _c(self)->removePage(self, page);
}

static void recalcPageWidth(mNavigator* self)
{
    mNavigatorPage   *page = NEXTPAGE(self, NULL);
    HDC hdc;
    DWORD style = GetWindowStyle(self->hwnd);

    ENTER_FUNCTION;
    
    if ((style&NCSS_NVGTR_BTNMASK) == NCSS_NVGTR_SCROLLABLE) {
        hdc = GetClientDC (self->hwnd);
        while(page) {
            calcScrollPageTitleWidth (hdc, self, page);
            page = NEXTPAGE(self, page);
        }

        ReleaseDC (hdc);
        updateNavigator(self);
    }
    else {
        recalcTabWidths (self, style);
    }

    InvalidateRect (self->hwnd, &(self->headRect), TRUE);

    EXIT_FUNCTION;
}

static BOOL mNavigator_setProperty(mNavigator *self, int id, DWORD value)
{
    BOOL ret;
    
    ENTER_FUNCTION;
    
	if( id >= NCSP_NVGTR_MAX)
		return FALSE;

	switch(id)
	{
        case NCSP_NVGTR_ACTIVEPAGE:
            return mNavigator_setActivePage(self, (mNavigatorPage*)value);

        case NCSP_NVGTR_ACTIVEPAGEIDX:
            return mNavigator_setActivePageByIndex(self, value);

        case NCSP_NVGTR_TABMARGIN:
            if ((int)value > 0) {
                self->tabMargin = (int)value;
                recalcPageWidth(self);

                EXIT_FUNCTION;
                return TRUE;
            }

        case NCSP_NVGTR_MINTABWIDTH:
            if ((int)value > 0) {
                self->minTabWidth = (int)value;
                recalcPageWidth(self);

                EXIT_FUNCTION;
                return TRUE;
            }
	}

	ret = Class(mWidget).setProperty((mWidget*)self, id, value);

    EXIT_FUNCTION;
    return ret;
}

static DWORD mNavigator_getProperty(mNavigator* self, int id)
{
	if( id >= NCSP_NVGTR_MAX)
		return -1;

	switch (id)
    {
        case NCSP_NVGTR_TABMARGIN:
            return self->tabMargin;

        case NCSP_NVGTR_PAGECOUNT:
            return self->pageCount;

        case NCSP_NVGTR_MINTABWIDTH:
            return self->minTabWidth;

        case NCSP_NVGTR_ACTIVEPAGE:
            return (DWORD)self->active;

        case NCSP_NVGTR_ACTIVEPAGEIDX:
            return _c(self)->getPageIndex(self, self->active);

        case NCSP_NVGTR_FIRSTVIEWPAGE:
            return (DWORD)self->firstView;

        case NCSP_NVGTR_FIRSTVIEWPAGEIDX:
            return _c(self)->getPageIndex(self, self->firstView);
    }

	return Class(mWidget).getProperty((mWidget*)self, id);
}

static void mNavigator_onPaint (mNavigator* self, HDC hdc, const PCLIPRGN pinv_clip)
{
    mNavigatorPage   *page;
    DWORD   style;
    RECT    rcClient, destRect, tabRect;

    ENTER_FUNCTION;
    
    style = GetWindowStyle(self->hwnd);

    GetClientRect (self->hwnd, &rcClient);

    /* draw border */
    self->renderer->getRect(self, &rcClient, &destRect, NCSF_NVGTR_BORDER);
    self->renderer->drawBorder(self, hdc, &destRect);

    if ((style & NCSS_NVGTR_BTNMASK) == NCSS_NVGTR_SCROLLABLE) {
        page = self->firstView;
        if (self->btnShow) {
            self->renderer->getRect(self, &rcClient, &destRect, NCSF_NVGTR_LEFT);

            if (self->active == NEXTPAGE(self, NULL))
                self->renderer->drawScrollBtn(self, hdc, &destRect, NCSR_ARROW_LEFT | NCSRS_DISABLE);
            else
                self->renderer->drawScrollBtn(self, hdc, &destRect, NCSR_ARROW_LEFT);

            self->renderer->getRect(self, &rcClient, &destRect, NCSF_NVGTR_RIGHT);

            if (NEXTPAGE(self, self->active) == NULL)
                self->renderer->drawScrollBtn(self, hdc, &destRect, NCSR_ARROW_RIGHT | NCSRS_DISABLE);
            else
                self->renderer->drawScrollBtn(self, hdc, &destRect, NCSR_ARROW_RIGHT);
        }
    }
    else  {
        page = NEXTPAGE(self, NULL);
    }

    //get tab area
    self->renderer->getRect(self, &rcClient, &tabRect, NCSF_NVGTR_TAB);
    destRect.right = tabRect.left;
    destRect.top = tabRect.top;
    destRect.bottom = tabRect.bottom;

    while (page) {
        destRect.left = destRect.right;
        destRect.right += page->titleWidth;

        if (destRect.right > tabRect.right) //&& !(self->firstView == page))
            break;

        self->renderer->drawTab(self, hdc, &destRect,
                GetWindowCaption(page->hwnd), _c(page)->getIcon(page),
                page == self->active);

        page = NEXTPAGE(self, page);
    }

    EXIT_FUNCTION;
}

static BOOL mNavigator_addChildren(mNavigator* self, NCS_WND_TEMPLATE * children, int count)
{
	DWORD exStyle = WS_EX_USEPARENTRDR;
	DWORD style;
	mNavigatorPage *page, *activePage = NULL;
	RECT  rcClient, rcPage;
	int i;

	if(!children || count <= 0)
		return FALSE;

	style = GetWindowStyle(self->hwnd);

	if(GetWindowExStyle(self->hwnd) & WS_EX_TRANSPARENT)
		exStyle |= WS_EX_TRANSPARENT;

	GetClientRect(self->hwnd, &rcClient);
	self->renderer->getRect(self, &rcClient, &rcPage, NCSF_NVGTR_PAGE);

	//create pages
	for(i=0; i<count; i++)
	{
		NCS_WND_TEMPLATE tmpl;
		if(!ncsIsChildClass(children[i].class_name, NCSCTRL_PAGE))
			continue;

		tmpl = children[i];
		tmpl.x = rcPage.left;
		tmpl.y = rcPage.top;
		tmpl.w = RECTW(rcPage);
		tmpl.h = RECTH(rcPage);
		tmpl.style &= ~WS_VISIBLE;
		tmpl.ex_style |= exStyle;

		page = (mNavigatorPage*)ncsCreateWindowIndirect(&tmpl, self->hwnd);
		if(!page)
			continue;

		if(activePage == NULL)
			activePage = page;
        else
        {
            HDC hdc = GetClientDC (self->hwnd);
            calcScrollPageTitleWidth (hdc, self, page);
            ReleaseDC (hdc);
        }

		SendMessage(page->hwnd, MSG_INITPAGE, 0, tmpl.user_data);
		self->pageCount ++;

	}

	if(!activePage)
		return FALSE;

	changeActivePage(self, activePage, style, TRUE);
	return TRUE;
}

BEGIN_CMPT_CLASS(mNavigator, mWidget)
    CLASS_METHOD_MAP(mNavigator, construct)
    CLASS_METHOD_MAP(mNavigator, onPaint)
    CLASS_METHOD_MAP(mNavigator, onLButtonDown)
    CLASS_METHOD_MAP(mNavigator, onSizeChanged)
    CLASS_METHOD_MAP(mNavigator, onKeyDown)
    CLASS_METHOD_MAP(mNavigator, addPage)
    CLASS_METHOD_MAP(mNavigator, removePage)
    CLASS_METHOD_MAP(mNavigator, removePageByIndex)
    CLASS_METHOD_MAP(mNavigator, getNextPage)
    CLASS_METHOD_MAP(mNavigator, getPrevPage)
    CLASS_METHOD_MAP(mNavigator, getPageIndex)
    CLASS_METHOD_MAP(mNavigator, getPageByIndex)
    CLASS_METHOD_MAP(mNavigator, broadCastMsg)
    CLASS_METHOD_MAP(mNavigator, setProperty)
    CLASS_METHOD_MAP(mNavigator, getProperty)
    CLASS_METHOD_MAP(mNavigator, addChildren)
	SET_DLGCODE( DLGC_WANTTAB | DLGC_WANTARROWS)
END_CMPT_CLASS