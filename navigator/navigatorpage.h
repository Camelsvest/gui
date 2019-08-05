#ifndef _NCSCTRL_NAVIGATOR_PAGE_H_
#define _NCSCTRL_NAVIGATOR_PAGE_H_

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/**
 * \defgroup Control_Page mNavigatorPage
 * @{
 */

/**
 * \def NCSCTRL_PAGE
 * \brief The control class name of mNavigatorPage.
 */
#define NCSCTRL_NAVIGATORPAGE           NCSCLASSNAME("navigator_page")

typedef struct _mNavigatorPage mNavigatorPage;
typedef struct _mNavigatorPageClass mNavigatorPageClass;
typedef struct _mNavigatorPageRenderer mNavigatorPageRenderer;

/**
 * \def NCSS_PAGE_SHIFT
 * \brief The bits used by mNavigatorPage in style.
 */
#define NCSS_PAGE_SHIFT NCSS_CTNR_SHIFT

#define mNavigatorPageHeader(className)  \
	mContainerHeader(className) \
    int     titleWidth;         \
    HICON   hIcon;


/**
 * \struct mNavigatorPage
 * \brief The control structure of mNavigatorPage, which derived from mContainer.
 *        It is a control which will be used as page in mNavigatorPage. Please
 *        don't use it separately.
 *
 *      - titleWidth \n
 *        The width of page title.
 *
 *      - hIcon \n
 *        The handle of icon.
 */
struct _mNavigatorPage
{
	mNavigatorPageHeader(mNavigatorPage)
};

#define mNavigatorPageClassHeader(clsName, parentClass)         \
	mContainerClassHeader(clsName, parentClass)        \
    const char* (*getTitle)(clsName* self);            \
    BOOL (*setTitle)(clsName* self, const char* title);\
    int (*getTitleLength)(clsName* self);              \
    int (*getTitleWidth)(clsName* self, HDC hdc);      \
    BOOL (*setIcon)(clsName* self, HICON icon);        \
    HICON (*getIcon)(clsName* self);                   \
    void (*showPage)(clsName* self, int showCmd);

/**
 * \struct mNavigatorPageClass
 * \brief The virtual function table of mNavigatorPage, which derived from mContainerClass.
 *
 *  - const char* (*\b getTitle)(mNavigatorPage *self);\n
 *    Get the title of page.
 *      \return           The pointer to the title of page.
 *
 *  - BOOL (*\b setTitle)(mNavigatorPage *self, const char* title);\n
 *    Set the title of specified page \a self.
 *      \param title      The pointer to the new title of page.
 *      \return           TRUE for success, otherwise FALSE.
 *
 *  - int (*\b getTitleLength)(mNavigatorPage *self);\n
 *    Get the length of a page title.
 *      \return           The length of the page title.
 *
 *  - int (*\b getTitleWidth)(mNavigatorPage *self, HDC hdc);\n
 *    Get the width of a page title in specified device context.
 *      \param hdc        The device context.
 *      \return           The width of the page title.
 *
 *  - void (*\b showPage) (mNavigatorPage *self, int showCmd);\n
 *    Shows or hides a page.
 *      \param showCmd    The show command, can be one of the following values:
 *                          - SW_SHOW\n The page will be shown.
 *                          - SW_HIDE\n The page will be hidden.
 *
 *  - BOOL (*\b setIcon)(mNavigatorPage *self, HICON icon);\n
 *    Set the handle of page icon.
 *      \param icon       The handle of ICON.
 *      \return           TRUE for success, otherwise FALSE.
 *
 *  - HICON (*\b getIcon)(mNavigatorPage *self);\n
 *    Get the handle of page icon.
 *      \return           The handle of ICON.
 */
struct _mNavigatorPageClass
{
	mNavigatorPageClassHeader(mNavigatorPage, mContainer)
};

/**
 * \var typedef void (*NCS_CB_ONINITPAGE)(mNavigatorPage *self, DWORD addData);
 * \brief the callback of the event MSG_INITPAGE. Initialize the
 *        controls in page.
 *
 * \param self     The pointer to mContainer.
 * \param addData   The additional data in DLGTEMPLATE structure
 *                  passed through addPage in mNavigatorPageClass.
 *
 * \note It need to be implemented by user.
 */
typedef void (*NCS_CB_ONINITNVGTRPAGE)(mNavigatorPage *self, DWORD addData);

/**
 * \var typedef int (*NCS_CB_ONSHOWPAGE)(mNavigatorPage *self, HWND focusChild, int showCmd);
 * \brief the callback of the event MSG_SHOWPAGE. Shows or hides page.
 *
 * \param self      The pointer to mContainer.
 * \param focusChild The handle to the child which will gain the
 *                   input focus when showing the page.
 * \param showCmd    The show command, can be one of the following values:
 *                      - SW_SHOW\n The page will be shown.
 *                      - SW_HIDE\n The page will be hidden.
 *
 * \return           Nonzero for success, zero for failure.
 * \note It need to be implemented by user.
 */
typedef int (*NCS_CB_ONSHOWNVGTRPAGE)(mNavigatorPage *self, HWND focusChild, int showCmd);

/**
 * \var typedef int (*NCS_CB_ONSHEETCMD)(mNavigatorPage *self, DWORD param1, DWORD param2);
 * \brief the callback of the MSG_SHEETCMD. Process broadcast message.
 *
 * \param self      The pointer to mContainer.
 * \param param1     The param info1 of function broadCastMsg in mNavigatorPageClass.
 * \param param2     The param info2 of function broadCastMsg in mNavigatorPageClass.
 *
 * \return           zero for broadcasting message for other pages continuing,
 *                   Nonzero for end of broadcasting message.
 *
 * \note It need to be implemented by user.
 */
typedef int (*NCS_CB_ONNVGTRCMD)(mNavigatorPage *self, DWORD param1, DWORD param2);

#define mNavigatorPageRendererHeader(clsName, parentClass) \
	mContainerRendererHeader(clsName, parentClass)

/**
 * \struct mNavigatorPageRenderer
 * \brief The renderer structure of mNavigatorPage, which inheried from mContainerRenderer.
 */
struct  _mNavigatorPageRenderer {
	 mNavigatorPageRendererHeader(mNavigatorPage, mContainer)
};


/**
 * \var g_stmNavigatorPageCls
 * \brief The instance of mNavigatorPageClass.
 *
 * \sa mNavigatorPageClass
 */
MGNCS_EXPORT extern mNavigatorPageClass g_stmNavigatorPageCls;

    /** @} end of Control_Page*/
#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* _NCSCTRL_NAVIGATOR_PAGE_H_ */
