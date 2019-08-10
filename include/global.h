#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#include <mgncs/mgncs.h>
#include <mgeff/mgeff.h>

#include <mgeff/mgeff.h>
#include <mgncs4touch/mgncs4touch.h>
#include <mgncs4touch/mtouchdebug.h>

#define SCREEN_W       800
#define SCREEN_H       600

#define PAGE_FIRST  	1
#define PAGE_SECOND     2
#define PAGE_THIRD  	3
#define PAGE_FOUR       4
#define PAGE_FIVE       5

#define IDC_MAINWND     103
#define IDC_MLEDIT      104
#define IDC_NAVIGATOR   105
#define IDC_NAVIGATOR_TAB	106
#define IDC_NAVIGATOR_PAGE1	107
#define IDC_NAVIGATOR_PAGE2	108
#define IDC_NAVIGATOR_PAGE3	109
#define IDC_NAVIGATOR_PAGE4	110
#define IDC_SYSINFO 111

#define IDC_NAVIGATOR_HOMEPAGE_AUDIOMEMO    201
#define IDC_NAVIGATOR_HOMEPAGE_OPENGATE     202
#define IDC_NAVIGATOR_HOMEPAGE_OPENDOOR     203

#define ID_BUTTON_0 204
#define ID_BUTTON_1 205
#define ID_BUTTON_2 206
#define ID_BUTTON_3 207

#define MSG_NVGT_BASEINDEX	(MSG_USER + 1000)
#define MSG_INIT_SKIN  (MSG_NVGT_BASEINDEX + 1)   

#define ID_SPINBOX_ONE 300
#define ID_SPINBOX_TWO 301

#define ID_PANEL_GROUP_0 400
#define ID_PANEL_GROUP_1 401

#define IDC_CUSTOM_TOOL 500
#define IDC_TOOLBAR 501 
#define IDC_CONTAINER 502
#define IDC_PROMPT 503

#endif
