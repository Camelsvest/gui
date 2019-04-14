#include "gui.h"
#include "debuglog.h"

int MiniGUIMain(int argc, const char *argv[])
{
	GUI gui;

	ENTER_FUNCTION;
	
#ifdef _MGRM_PROCESSES
	JoinLayer(NAME_DEF_LAYER, "GUI-DESKTOP", 0, 0);
	LOG_PRINT("GUI-DESKTOP\r\n");
#endif

	if (gui.init())
		gui.run();
	
		gui.uninit();
	
	OUT_FUNCTION;
	
	return 0;
}

