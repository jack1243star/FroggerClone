/* Name:          Frogger Clone Main Source File                   *
 * File name:     main.c                                           *
 * Author:        Jack Yang                                        *
 * Created:       2014-11-09                                       *
 * Last modified: 2014-11-09                                       *
 * Description:   Entry point of the program.                      */

#include <stdlib.h>
#include <SDL.h>

#include "graphics.h"
#include "events.h"
#include "logic.h"

int main(int argc, char* argv[])
{
	/* Unused arguments */
	(void)argc;
	(void)argv;

	/* Initialize SDL */
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
		                         "SDL_Init Failure",
		                         SDL_GetError(),
		                         NULL);
		return EXIT_FAILURE;
	}

	/* Initialize game state */
	init_game();
	/* Initialize graphics */
	if (init_graphics() != 0){
		return EXIT_FAILURE;
	}

	/* Start game logic thread */
	SDL_CreateThread(game_thread, "GameLogic", NULL);

	/* Main Loop */
	while (!quit){
		/* Handle events*/
		handle_event();
		/* Render graphics */
		update_graphics();
	}

	return EXIT_SUCCESS;
}
