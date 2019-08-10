#ifndef __INFOBAR_WINDOW_H__
#define __INFOBAR_WINDOW_H__

#include "global.h"

#define CUSTOM_CTRL_NAME "CUSTOM_TOOL_CTROL"

#define INFOBAR_W  SCREEN_W
#define INFOBAR_H  46
#define INFOBAR_X  0
#define INFOBAR_Y  (SCREEN_H-INFOBAR_H)

#define INFOBARMAP_MAX 1

#define ITEM_NUM 3

class InfoBarWindow {

    public:
        InfoBarWindow ();
        virtual ~InfoBarWindow ();

        BOOL createWindow (HWND hwnd, RECT *rc);
        BOOL ncscreateWindow (HWND hwnd, RECT *rc);
        
        enum TB_INDEX {
            TB_1 = 0,
            TB_2,
            TB_3,
            TB_4,
            TB_5,
            TB_6,
            TB_MAX 
        };

    private:

        BOOL registerCtrClass();
        void unregisterCtrlClass();
        void loadRes ();
        void unloadRes ();
        void onCreate (HWND hwnd);
        static LRESULT CustomControlProc (HWND hWnd, UINT message,WPARAM wParam,LPARAM lParam); 
        
        static BOOL container_onCommand(mWidget* self, int id, int nc, HWND hCtrl);


    private:
        static NCS_EVENT_HANDLER container_handlers[];
        HWND m_hWnd;
        // resource bitmap
        PBITMAP m_infobarBmp[TB_MAX];
};


#endif

