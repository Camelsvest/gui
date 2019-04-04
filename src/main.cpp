#include "gui.h"

int MiniGUIMain(int argc, const char *argv[])
{
	GUI gui;

#ifdef _MGRM_PROCESSES
	JoinLayer(NAME_DEF_LAYER, "GUI-DESKTOP", 0, 0);
#endif

	if (gui.init())
		gui.run();

	return 0;
}

