#if !defined(__GUI_H__)
#define __GUI_H__

#include <unistd.h>
#include "SDL2/SDL.h"

#include "board.h"

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600

extern SDL_Event event;

void gui_run(Board board);

#endif // __GUI_H__