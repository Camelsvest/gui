#ifndef _NCSCTRL_NAVIGATOR_H_
#define _NCSCTRL_NAVIGATOR_H_

#include "navigatorpage.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

    /**
     * \defgroup Control_Navigator mNavigator
     * @{
     */

/**
 * \def NCSCTRL_NAVIGATOR
 * \brief The control class name of mNavigator.
 */
#define NCSCTRL_NAVIGATOR        NCSCLASSNAME("navigator")

/**
 * \def NCSS_NVGTR_SHIFT
 * \brief The bits used by mNavigator in style.
 */
#define NCSS_NVGTR_SHIFT  NCSS_WIDGET_SHIFT+3

#define NCSS_NVGTR_BTNMASK         (0x0003<<NCSS_WIDGET_SHIFT)
#define NCSS_NVGTR_TABMASK         (0x0004<<NCSS_WIDGET_SHIFT)

/**
 * \def NCSS_NVGTR_COMPACTTAB
 * \brief A simple property sheet control. All tabs of the controls will have
 *        the same width.
 */
#define NCSS_NVGTR_SIMPLE          (0x0000<<NCSS_WIDGET_SHIFT)

/**
 * \def NCSS_NVGTR_COMPACTTAB
 * \brief Compact tab style. The width of a tab is adaptive to the tab title.
 */
#define NCSS_NVGTR_COMPACTTAB      (0x0001<<NCSS_WIDGET_SHIFT)

/**
 * \def NCSS_NVGTR_SCROLLABLE
 * \brief Tab can be scrolled by scrolled button.
 */
#define NCSS_NVGTR_SCROLLABLE      (0x0002<<NCSS_WIDGET_SHIFT)

/**
 * \def NCSS_NVGTR_TOP
 * \brief Top tab style. Tabs will be located at the top of the propsheet.
 */
#define NCSS_NVGTR_TOP             (0x0000<<NCSS_WIDGET_SHIFT)

/**
 * \def NCSS_NVGTR_BOTTOM
 * \brief Bottom tab style. Tabs will be located at the bottom of the
 *        propsheet.
 */
#define NCSS_NVGTR_BOTTOM          (0x0004<<NCSS_WIDGET_SHIFT)

typedef struct _mNavigator mNavigator;
typedef struct _mNavigatorClass mNavigatorClass;
typedef struct _mNavigatorRenderer mNavigatorRenderer;

#define mNavigatorHeader(className) \
	mWidgetHeader(className)        \
    int     minTabWidth;            \
    int     maxTabWidth;            \
    int     scrollTabWidth;         \
    RECT    headRect;               \
    int     pageCount;              \
    BOOL    btnShow;                \
    mNavigatorPage*  active;        \
    mNavigatorPage*  firstView;     \
    int     tabMargin;

/**
 * \struct mNavigator
 * \brief propsheet control mananager a group of \a mNavigatorPage, inherited from mWidget.
 *
 *      - minTabWidth \n
 *        The minimum width of tab.
 *
 *      - maxTabWidth \n
 *        The maximum width of tab.
 *
 *      - scrollTabWidth \n
 *        The effective width of tabs.
 *
 *      - headRect \n
 *        The rectange of header, which is used to show all tabs.
 *
 *      - pageCount \n
 *        The number of pages.
 *
 *      - btnShow \n
 *        The flag whether show scrollable button or not.
 *
 *      - active \n
 *        The pointer to active page \a mNavigatorPage.
 *
 *      - firstView \n
 *        The pointer to first view page \a mNavigatorPage.
 *
 *      - tabMargin \n
 *        The intervals between current and next tab.
 */
struct _mNavigator
{
	mNavigatorHeader(mNavigator)
};

#define mNavigatorClassHeader(clsName, parentClass)    \
	mWidgetClassHeader(clsName, parentClass)           \
    int (*getPageIndex)(clsName*, mNavigatorPage* page);        \
    mNavigatorPage* (*getPageByIndex)(clsName*, int pageIndex); \
    mNavigatorPage* (*addPage)(clsName*, const PDLGTEMPLATE dlgTemplate, const NCS_EVENT_HANDLER* handlers);\
    BOOL (*removePageByIndex)(clsName*, int pageIndex);\
    BOOL (*removePage)(clsName*, mNavigatorPage* page);         \
    mNavigatorPage* (*getNextPage)(clsName*, mNavigatorPage* page);      \
    mNavigatorPage* (*getPrevPage)(clsName*, mNavigatorPage* page);      \
    int (*broadCastMsg)(clsName*, DWORD param1, DWORD param2);

/**
 * \struct mNavigatorClass
 * \brief The virtual function table of mNavigator.
 *
 *  - int (*\b getPageIndex)(mNavigator *self, mNavigatorPage* page);\n
 *    Get the index of specified \a page.
 *      \param page       The pointer to mNavigatorPage.
 *      \return           The index of page for success, otherwise -1.
 *
 *  - mNavigatorPage* (*\b getPageByIndex)(mNavigator *self, int pageIndex);\n
 *    Get the pointer of page according to page index \a pageIndex.
 *      \param pageIndex  The index of page.
 *      \return           The pointer to page for success, otherwise NULL.
 *
 *  - mNavigatorPage* (*\b addPage)(mNavigator *self, const PDLGTEMPLATE dlgTemplate,
 *                              const NCS_EVENT_HANDLER* handlers);\n
 *    Add a page to propsheet according to DLGTEMPLATE and handlers.
 *      \param dlgTemplate    The pointer to dialog template.
 *      \param handlers       The pointer to event handlers.
 *      \return               The pointer to page for success, otherwise NULL.
 *      \sa NCS_EVENT_HANDLER
 *
 *  - BOOL (*\b removePageByIndex)(mNavigator *self, int pageIndex);\n
 *    Remove a page according to page index \a pageIndex.
 *      \param pageIndex  The index of page.
 *      \return           TRUE for success, otherwise FALSE.
 *
 *  - BOOL (*\b removePage)(mNavigator *self, mNavigatorPage* page);\n
 *    Remove a page according to the pointer to \a page.
 *      \param page       The pointer to mNavigatorPage.
 *      \return           TRUE for success, otherwise FALSE.
 *
 *  - mNavigatorPage* (*\b getNextPage)(mNavigator *self, mNavigatorPage* page); \n
 *    Get the next page.
 *      \param page       The pointer to mNavigatorPage.
 *      \return           The pointer to next page.
 *
 *  - mNavigatorPage* (*\b getPrevPage)(mNavigator *self, mNavigatorPage* page); \n
 *    Get the previous page.
 *      \param page       The pointer to mNavigatorPage.
 *      \return           The pointer to previous page.
 *
 *  - int (*\b broadCastMsg)(mNavigator *self, DWORD param1, DWORD param2); \n
 *    Broadcast message to all pages.
 *      \param param1     The first parameter of broadcast message.
 *      \param param2     The second parameter of broadcast message.
 *      \return           The index + 1 of page which has been broken the message,
 *                        Zero indicates no page asserts an error.
 */
struct _mNavigatorClass
{
	mNavigatorClassHeader(mNavigator, mWidget)
};

/**
 * \enum ncsNvgtrFlags
 * \brief The flag of mNavigator. It is used by mNavigatorRenderer.
 */
enum ncsNvgtrFlags
{
    /**
     * The flag of border.
     */
    NCSF_NVGTR_BORDER,

    /**
     * The flag of tab.
     */
    NCSF_NVGTR_TAB,

    /**
     * The flag of left scrollable button.
     */
    NCSF_NVGTR_LEFT,

    /**
     * The flag of right scrollable button.
     */
    NCSF_NVGTR_RIGHT,

    /**
     * The flag of page.
     */
    NCSF_NVGTR_PAGE,

    /**
     * The maximum value of flags.
     */
    NCSF_NVGTR_MAX,
};

#define mNavigatorRendererHeader(clsName, parentClass)                      \
	mWidgetRendererHeader(clsName, parentClass)                             \
    void (*resetHeadArea) (clsName*, RECT* rcClient, DWORD style);          \
    void (*getRect)(clsName*, RECT* rcClient, RECT *rcResult, int which);   \
    void (*drawBorder)(clsName*, HDC hdc, RECT *rcBorder);                  \
    void (*drawScrollBtn)(clsName*, HDC hdc, RECT *rcBtn, int which);       \
    void (*drawTab)(clsName*, HDC hdc, RECT* rcTab, const char* title, HICON hIcon, BOOL active);

/**
 * \struct mNavigatorRenderer
 * \brief The structure of mNavigator renderer, which inheried from mWidgetRenderer.
 *
 *  - void (*\b resetHeadArea) (mNavigator *self, RECT* rcClient, DWORD style);\n
 *    According to client area and control style, reset the rectangle of header
 *    which is used to show all tabs.
 *      \param rcClient   The pointer to a RECT strucutre which contains the client area.
 *      \param style      The style of control.
 *
 *  - void (*\b getRect)(mNavigator *self, RECT* rcClient, RECT *rcResult, int which);\n
 *    Get the rectangle of specified region \a which.
 *      \param rcClient   The pointer to a RECT strucutre which contains the client area.
 *      \param rcResult   The pointer to a RECT strucutre which contains the result area.
 *      \param which      The flag of area, can be one of the following values:
 *                          - NCSF_NVGTR_BORDER \n Border.
 *                          - NCSF_NVGTR_TAB \n    Tab.
 *                          - NCSF_NVGTR_LEFT \n   Left scrollable button.
 *                          - NCSF_NVGTR_RIGHT \n  Right scrollable button.
 *                          - NCSF_NVGTR_PAGE \n   Page.
 *
 *  - void (*\b drawBorder)(mNavigator *self, HDC hdc, RECT *rcBorder);\n
 *    Draw border.
 *      \param hdc        The device context.
 *      \param rcBorder   The pointer to a RECT strucutre which contains the border area.
 *
 *  - void (*\b drawScrollBtn)(mNavigator *self, HDC hdc, RECT *rcBtn, int which);\n
 *    Draw scrollable button.
 *      \param hdc        The device context.
 *      \param rcBtn      The pointer to a RECT strucutre which contains the button area.
 *      \param which      The status of scrollable button, can be one of the following values:
 *                          - NCSR_ARROW_LEFT
 *                          - NCSR_ARROW_RIGHT
 *
 *  - void (*\b drawTab)(mNavigator *self, HDC hdc, RECT* rcTab, const char* title, HICON hIcon, BOOL active); \n
 *    Draw tab.
 *      \param hdc        The device context.
 *      \param rcTab      The pointer to a RECT strucutre which contains the tab area.
 *      \param title      The pointer to the tab title.
 *      \param hIcon      The handle of the tab icon.
 *      \param active     The status of tab.
 *
 */
struct  _mNavigatorRenderer {
	mNavigatorRendererHeader(mNavigator, mWidget)
};

/**
 * \var g_stmNavigatorCls
 * \brief The instance of mNavigatorClass.
 *
 * \sa mNavigatorClass
 */
MGNCS_EXPORT extern mNavigatorClass g_stmNavigatorCls;

/**
 * \enum mNavigatorNotify
 * \brief The notification code id of mNavigator.
 */
enum mNavigatorNotify
{
	/**
	 * \brief the active page changed
	 *
	 */
    NCSN_NVGTR_ACTIVECHANGED = NCSN_WIDGET_MAX + 1,
    /**
     * The maximum value of mNavigator notification code id.
     */
    NCSN_NVGTR_MAX
};


/**
 * \enum mNavigatorProp
 * \brief The properties of mNavigator
 */
enum mNavigatorProp
{
	/**
	 * \brief Set the minimum width of tab
	 *  - Type int
	 *  - Read Write
	 *  - set the minimum width of tab
	 *
	 */
	NCSP_NVGTR_MINTABWIDTH = NCSP_WIDGET_MAX + 1,
	/**
	 * \brief Set the tab margin
	 *  - Type int
	 *  - Read Write
	 *  - set the margin of tab
	 *
	 */
	NCSP_NVGTR_TABMARGIN,
	/**
	 * \brief Set the active page
	 *  - Type mNavigatorPage*
	 *  - Read Write
	 *  - set the active page pointer
	 *
	 */
    NCSP_NVGTR_ACTIVEPAGE,
	/**
	 * \brief Set the active page id
	 *  - Type int
	 *  - Read Write
	 *  - set the active page id
	 *
	 */
    NCSP_NVGTR_ACTIVEPAGEIDX,
	/**
	 * \brief Set the first view page
	 *  - Type mNavigatorPage*
	 *  - Read
	 *  - set the first view page pointer
	 *
	 */
    NCSP_NVGTR_FIRSTVIEWPAGE,
	/**
	 * \brief Set the first visible page
	 *  - Type int
	 *  - Read
	 *  - set the index of first visible page
	 *
	 */
    NCSP_NVGTR_FIRSTVIEWPAGEIDX,
	/**
	 * \brief Set the number of pages
	 *  - Type int
	 *  - Read
	 *  - set the number of pages
	 *
	 */
	NCSP_NVGTR_PAGECOUNT,
	NCSP_NVGTR_MAX
};

void test1();

BOOL RegisterNavigatorComponent();
BOOL UnregisterNavigatorComponent();
BOOL InitNavigatorSkinRenderer();

    /** @} end of Control_Navigator */
#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* _NCSCTRL_NAVIGATOR_H_ */

