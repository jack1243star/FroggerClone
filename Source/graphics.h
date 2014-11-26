/* Name:          Frogger Clone Graphics Header File               *
 * File name:     graphics.h                                       *
 * Author:        Jack Yang                                        *
 * Created:       2014-11-09                                       *
 * Last modified: 2014-11-09                                       *
 * Description:   Graphics component of the program.               */

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>
#include "logic.h"

/* Initialize graphics. Returns non-zero on error. */
int init_graphics(void);
/* Update graphics */
void update_graphics(void);
/* Put a pixel on a 32-bit surface */
void putpixel(SDL_Surface* surface, Uint32 color, int x, int y);

#endif
