/* Name:          Frogger Clone Events Source File                 *
 * File name:     events.c                                         *
 * Author:        Jack Yang                                        *
 * Created:       2014-11-09                                       *
 * Last modified: 2014-11-09                                       *
 * Description:   Events component of the program.                 */

#include "events.h"

/* SDL data structure */
static SDL_Event event;

/* Handle events */
void handle_event(void){
	static int dragging = 0;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			/* Exit the program */
			quit = 1;
			return;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_w:
				move_frog('w');
				break;
			case SDLK_s:
				move_frog('s');
				break;
			case SDLK_a:
				move_frog('a');
				break;
			case SDLK_d:
				move_frog('d');
				break;
			case SDLK_q:
				quit = 1;
				break;
			default:
				break;
			}
			break;
		case SDL_MOUSEMOTION:
			if (event.motion.x < 100 && dragging)
				delay = event.motion.x * 5;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.motion.x < 100 && event.motion.y > 590)
				dragging = 1;
			break;
		case SDL_MOUSEBUTTONUP:
			dragging = 0;
			break;
		default:
			break;
		}
	}
}
