#ifndef _WND_H_
#define _WND_H_

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

class Wnd {
public:
	Wnd();
	virtual ~Wnd();

    bool registerWndClass(const char *pszWndClassName);
    void unregisterWndClass(const char *pszWndClassName);

    bool createMainWindow(const char *pszCaption, HMENU hMenu,
        HCURSOR hCursor, HICON hIcon, DWORD dwStyle, DWORD dwExStyle,
        int x, int y, int w, int  h);

    bool createWindow(const char *pszWndClassName, const char *pszCaption,
        DWORD dwStyle, DWORD dwExStyle, int id, int x, int y, int w, int  h,
        HWND hParentWnd);

	operator HWND() const
	{
		return m_hWnd;
	}

    HDC beginPaint() { return ::BeginPaint(m_hWnd); }
    void endPaint(HDC hdc) { ::EndPaint(m_hWnd, hdc); }
    
	HWND getHandle() { return m_hWnd; }
	int	messageBox(const char *pszText, const char *pszCaption, DWORD dwStyle);

    bool showWindow();

    DWORD getWindowElementAttr(int weAttrId);
    WINDOW_ELEMENT_RENDERER* getWindowElementRender();
	
protected:
	bool getClientRect(RECT &rc);
	bool getClientRect(RECT *rc);
	
	static int wndProc(HWND hWnd, int message, WPARAM wParam, LPARAM lParam);
	virtual int wndProc(int message, WPARAM wParam, LPARAM lParam);

	virtual int onCreate(WPARAM wParam, LPARAM lParam) = 0;
	virtual int onClose(WPARAM wParam, LPARAM lParam);
	virtual int onMaximize(WPARAM wParam, LPARAM lParam);
    virtual int onShowWindow(WPARAM wPara, LPARAM lParam);
	virtual int onPaint(WPARAM wParam, LPARAM lParam);
	virtual int onDraw(HDC hdc);
	
private:
	HWND	m_hWnd;

};

#endif
