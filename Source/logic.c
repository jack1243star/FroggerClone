/* Name:          Frogger Clone Game Logic Source File             *
 * File name:     logic.c                                          *
 * Author:        Jack Yang                                        *
 * Created:       2014-11-09                                       *
 * Last modified: 2014-11-09                                       *
 * Description:   Game logic component of the program.             */

#include <stdlib.h>
#include "logic.h"

/* Quit flag */
int quit = 0;
/* Game map */
int map[80][60];
/* Game map mutex */
SDL_mutex* mapLock = NULL;

/* Frog coords */
int frogX, frogY;
/* Game update delay */
int delay = 300;

/* Update game state */
static void update_game(void);
/* Game win */
static void game_win(void);
/* Game lose */
static void game_lose(void);

/* Initialize game state. Returns non-zero on error. */
int init_game(void){
	/* Loop counter */
	int i, j;
	
	/* Create map lock */
	mapLock = SDL_CreateMutex();
	if (mapLock == NULL){
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
			"SDL_CreateTexture Failure",
			SDL_GetError(),
			NULL);
		return -1;
	}

	/* Draw land */
	for (i = 0; i < 80; i++){
		map[i][0] = 0;
		map[i][1] = 0;
		map[i][58] = 0;
		map[i][59] = 0;
	}

	/* Draw river */
	for (i = 0; i < 80; i++)
		for (j = 2; j < 58; j++)
			map[i][j] = 1;

	/* Draw random logs */
	for (i = 0; i < 80; i++)
		update_game();

	/* Put frog */
	frogX = 40;
	frogY = 59;

	return 0;
}

/* Update game state */
static void update_game(void){
	/* Loop counter */
	int i, j;

	/* Lock map mutex */
	if (SDL_LockMutex(mapLock) == 0){
		/* Shift logs left */
		for (i = 0; i < 79; i++)
			for (j = 2; j < 58; j += 2)
				map[i][j] = map[i + 1][j];
		/* Shift logs right */
		for (i = 79; i > 0; i--)
			for (j = 3; j < 58; j += 2)
				map[i][j] = map[i - 1][j];

		/* Draw new logs */
		for (j = 2; j < 58; j += 2){
			if (map[78][j] == 2){
				/* Was log */
				map[79][j] = rand() % 3 == 0 ? 1 : 2;
			}
			else {
				/* Was river */
				map[79][j] = rand() % 3 != 0 ? 1 : 2;
			}
		}
		for (j = 3; j < 58; j += 2){
			if (map[1][j] == 2){
				/* Was log */
				map[0][j] = rand() % 3 == 0 ? 1 : 2;
			}
			else {
				/* Was river */
				map[0][j] = rand() % 3 != 0 ? 1 : 2;
			}
		}

		/* Update frog */
		if (frogY > 1 && frogY < 58){
			if (frogY % 2 == 0){
				if (frogX > 0)
					frogX = frogX - 1;
			} else {
				if (frogX < 79)
					frogX = frogX + 1;
			}
		}
		/* Check frog coords */
		if (map[frogX][frogY] == 1)
			game_lose();
		/* Unlock map mutex */
		SDL_UnlockMutex(mapLock);
	} else {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
		                         "SDL_LockMutex Failure",
		                         SDL_GetError(),
		                         NULL);
		quit = 1;
	}
	return;
}

/* Game thread function */
int game_thread(void* args){
	Uint32 lastUpdate = 0;

	/* Unused argument*/
	(void)args;

	/* Update game when some time passed */
	while (!quit){
		if (SDL_GetTicks() - delay > lastUpdate){
			update_game();
			lastUpdate = SDL_GetTicks();
		}
	}
	return 0;
}

/* Move frog */
void move_frog(char direction){
	switch (direction){
	case 'w':
		frogY = frogY - 1;
		break;
	case 's':
		frogY = frogY + 1;
		break;
	case 'a':
		frogX = frogX - 1;
		break;
	case 'd':
		frogX = frogX + 1;
		break;
	default:
		break;
	}
	/* Lock map mutex */
	if (SDL_LockMutex(mapLock) == 0){
		/* Check frog coords */
		if (frogY < 2)
			game_win();
		if (map[frogX][frogY] == 1)
			game_lose();
		/* Unlock map mutex */
		SDL_UnlockMutex(mapLock);
	} else {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
		                         "SDL_LockMutex Failure",
		                         SDL_GetError(),
		                         NULL);
		quit = 1;
	}
}

/* Game win */
static void game_win(void){
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
	                         "You win!",
	                         "Congradulations! You beat this game.",
	                         NULL);
	exit(EXIT_SUCCESS);
}

/* Game lose */
static void game_lose(void){
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
	                         "Game Over",
	                         "Sorry! You lost this game.",
							 NULL);
	exit(EXIT_SUCCESS);
}
