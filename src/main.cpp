#include "gui.h"
#include "logging.h"

int MiniGUIMain(int argc, const char *argv[])
{
  GUI gui;

  logging_init(NULL);

#ifdef _MGRM_PROCESSES
  JoinLayer(NAME_DEF_LAYER, "GUI-DESKTOP", 0, 0);
#endif

  if (gui.init())
    gui.run();
	
  gui.uninit();

  logging_uninit();
    
  return 0;
}

