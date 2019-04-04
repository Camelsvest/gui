#include "gui.h"


int MiniGUIMain(int argc, const char *argv[])
{


#ifdef _MGRM_PROCESSES
	JoinLayer(NAME_DEF_LAYER, "GUI-DESKTOP", 0, 0);
#endif

	
	return 0;
}

