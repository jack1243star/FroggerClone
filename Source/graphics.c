/* Name:          Frogger Clone Graphics Source File               *
 * File name:     graphics.c                                       *
 * Author:        Jack Yang                                        *
 * Created:       2014-11-09                                       *
 * Last modified: 2014-11-09                                       *
 * Description:   Graphics component of the program.               */

#include "graphics.h"

/* Set bit masks of pixels according to endianness */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
static const Uint32 rmask = 0xff000000;
static const Uint32 gmask = 0x00ff0000;
static const Uint32 bmask = 0x0000ff00;
static const Uint32 amask = 0x000000ff;
#else
static const Uint32 rmask = 0x000000ff;
static const Uint32 gmask = 0x0000ff00;
static const Uint32 bmask = 0x00ff0000;
static const Uint32 amask = 0xff000000;
#endif

/* SDL data structures */
static SDL_Window*   sdlWindow;
static SDL_Renderer* sdlRenderer;
static SDL_Texture*  sdlTexture;
static SDL_Surface*  sdlSurface;

/* Screen width */
static const int width = 800;
/* Screen height */
static const int height = 600;

/* Initialize graphics. Returns non-zero on error. */
int init_graphics(void){
	/* Create window */
	sdlWindow = SDL_CreateWindow("Frogger Clone",
	                             SDL_WINDOWPOS_UNDEFINED,
	                             SDL_WINDOWPOS_UNDEFINED,
	                             width, height,
	                             SDL_WINDOW_OPENGL);
	if (sdlWindow == 0){
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
		                         "SDL_CreateWindow Failure",
		                         SDL_GetError(),
		                         NULL);
		return -1;
	}
	/* Create renderer */
	sdlRenderer = SDL_CreateRenderer(sdlWindow, -1,
	                                 SDL_RENDERER_ACCELERATED |
	                                 SDL_RENDERER_PRESENTVSYNC);
	if (sdlRenderer == NULL){
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
		                         "SDL_CreateRenderer Failure",
		                         SDL_GetError(),
		                         NULL);
		return -1;
	}
	/* Create texture */
	sdlTexture = SDL_CreateTexture(sdlRenderer,
	                               SDL_PIXELFORMAT_ABGR8888,
	                               SDL_TEXTUREACCESS_STREAMING,
	                               width, height);
	if (sdlTexture == 0){
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
		                         "SDL_CreateTexture Failure",
		                         SDL_GetError(),
		                         NULL);
		return -1;
	}
	/* Create surface */
	sdlSurface = SDL_CreateRGBSurface(0, width, height, 32,
	                                  rmask, gmask, bmask, amask);
	if (sdlSurface == NULL){
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
		                         "SDL_CreateRBGSurface Failure",
		                         SDL_GetError(),
		                         NULL);
		return -1;
	}

	return 0;
}

/* Update graphics */
void update_graphics(void){
	/* Loop counter */
	int i, j, k, l;

	/* Lock map mutex */
	if (SDL_LockMutex(mapLock) == 0){
		/* Render map */
		for (i = 0; i < 80; i++){
			for (j = 0; j < 60; j++){
				switch (map[i][j]){
				case 0:
					/* Land */
					for (k = i * 10; k < i * 10 + 10; k++)
						for (l = j * 10; l < j * 10 + 10; l++)
							putpixel(sdlSurface,
							         SDL_MapRGB(sdlSurface->format, 150, 75, 0),
							         k, l);
					break;
				case 1:
					/* Water */
					for (k = i * 10; k < i * 10 + 10; k++)
						for (l = j * 10; l < j * 10 + 10; l++)
							putpixel(sdlSurface,
							SDL_MapRGB(sdlSurface->format, 0, 0, 240),
							k, l);
					break;
				case 2:
					/* Log */
					for (k = i * 10; k < i * 10 + 10; k++)
						for (l = j * 10 + 1; l < j * 10 + 9; l++)
							putpixel(sdlSurface,
							SDL_MapRGB(sdlSurface->format, 175, 90, 50),
							k, l);
					break;
				default:
					for (k = i * 10; k < i * 10 + 10; k++)
						for (l = j * 10; l < j * 10 + 10; l++)
							putpixel(sdlSurface,
							SDL_MapRGB(sdlSurface->format, 0, 0, 0),
							k, l);
					break;
				}
			}
		}
		/* Unlock map mutex */
		SDL_UnlockMutex(mapLock);
	}
	else {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
			"SDL_CreateTexture Failure",
			SDL_GetError(),
			NULL);
		quit = 1;
	}

	/* Draw frog */
	for (k = frogX * 10; k < frogX * 10 + 10; k++)
		for (l = frogY * 10 + 1; l < frogY * 10 + 9; l++)
			putpixel(sdlSurface,
			         SDL_MapRGB(sdlSurface->format, 0, 255, 0),
			         k, l);

	/* Draw slide bar */
	for (i = 0; i < 100; i++)
		for (j = 590; j < 600; j++)
			if (i > delay / 5){
				putpixel(sdlSurface,
				         SDL_MapRGB(sdlSurface->format, 255, 255, 255),
				         i, j);
			} else {

				putpixel(sdlSurface,
				         SDL_MapRGB(sdlSurface->format, 255, 0, 0),
				         i, j);
			}

	/* Upload texture */
	SDL_UpdateTexture(sdlTexture,
	                  NULL,
	                  sdlSurface->pixels,
	                  sdlSurface->pitch);
	/* Render texture */
	SDL_RenderClear(sdlRenderer);
	SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, NULL);
	SDL_RenderPresent(sdlRenderer);
}

/* Put a pixel on a 32-bit surface */
void putpixel(SDL_Surface* surface, Uint32 color, int x, int y){
	Uint32* pixels = (Uint32*)surface->pixels;
	Uint32* pixel = pixels + y * surface->pitch / 4 + x;
	*pixel = color;
}
