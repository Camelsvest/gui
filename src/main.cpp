#include "gui.h"

int MiniGUIMain(int argc, const char *argv[])
{
	GUI gui;

#ifdef _MGRM_PROCESSES
	JoinLayer(NAME_DEF_LAYER, "GUI-DESKTOP", 0, 0);
	LOG_PRINT("GUI-DESKTOP\r\n");
#endif

	if (gui.init())
		gui.run();
	
	gui.uninit();
	
	return 0;
}

