/***************************************************************************
 * FILENAME:    viewport.c
 * DESCRIPTION: Handles the view that the player has on a level.
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 09Nov2021
***************************************************************************/

#include "main.h"

#define VIEWPORT_SPEED (4)

void	move_viewport(int *px, int *py, int *ix, int *iy)
{
	int mod_x, mod_y;
	SDL_Rect	bound = {(128 - 16) * DISPLAY_SCALE, (80 + 16) * DISPLAY_SCALE, (320 - 256) * DISPLAY_SCALE, (224 - 160) * DISPLAY_SCALE};

/*
** The image is 384x448
** The window is 320x224
**
** Needs four conditionals because the viewport can be moved in four directions.
** So each direction must be tested to see if it is possible to move in that direction.
*/

	mod_x = 1;
	mod_y = 1;
	if ((*py) * DISPLAY_SCALE - bound.y < -100 || (*py) * DISPLAY_SCALE - bound.y - bound.h > 100)
		mod_y = 3;

	if ((*px) * DISPLAY_SCALE - bound.x < -100 || (*px) * DISPLAY_SCALE - bound.x - bound.w > 100)
		mod_x = 2;

	if ((*py) * DISPLAY_SCALE < bound.y && *iy - VIEWPORT_SPEED * mod_y >= 0) 					{ *iy -= VIEWPORT_SPEED * mod_y; *py += VIEWPORT_SPEED * mod_y; }
	if ((*px) * DISPLAY_SCALE < bound.x && *ix - VIEWPORT_SPEED * mod_x >= 0)					{ *ix -= VIEWPORT_SPEED * mod_x; *px += VIEWPORT_SPEED * mod_x; }
	if ((*py) * DISPLAY_SCALE > bound.y + bound.h && *iy + 224 + VIEWPORT_SPEED * mod_y <= 400)	{ *iy += VIEWPORT_SPEED * mod_y; *py -= VIEWPORT_SPEED * mod_y; }
	if ((*px) * DISPLAY_SCALE > bound.x + bound.w && *ix + 320 + VIEWPORT_SPEED * mod_x <= 496)	{ *ix += VIEWPORT_SPEED * mod_x; *px -= VIEWPORT_SPEED * mod_x; }

	SDL_SetRenderDrawColor(SDLX_GetDisplay()->renderer, 255, 0, 0, 0);
	// SDL_RenderDrawRect(SDLX_GetDisplay()->renderer, &(bound));
}