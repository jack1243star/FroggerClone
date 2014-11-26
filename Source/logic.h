/* Name:          Frogger Clone Game Logic Header File             *
 * File name:     logic.h                                          *
 * Author:        Jack Yang                                        *
 * Created:       2014-11-09                                       *
 * Last modified: 2014-11-09                                       *
 * Description:   Game logic component of the program.             */

#ifndef LOGIC_H
#define LOGIC_H

#include <SDL.h>

/* Quit flag */
extern int quit;
/* Game map */
extern int map[80][60];
/* Game map mutex */
extern SDL_mutex* mapLock;
/* Frog coords */
extern int frogX, frogY;
/* Game update delay */
extern int delay;

/* Initialize game state. Returns non-zero on error. */
int init_game(void);
/* Game thread function */
int game_thread(void* args);
/* Move frog */
void move_frog(char direction);

#endif
