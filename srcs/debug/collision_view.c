/***************************************************************************
 * FILENAME:    collision_view.c
 * DESCRIPTION: Functions that allow collision boxes to be seen.
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

void	view_map_collisions(SDL_Surface *image, int px, int py)
{
	int i = 0;
	int j = 0;
	SDL_Rect	immove;
	Uint8 *pixels = image->pixels;

	immove.w = 4 * DISPLAY_SCALE;
	immove.h = 4 * DISPLAY_SCALE;
	while (i < image->h)
	{
		j = 0;
		while (j < image->w)
		{
			if (pixels[i * image->w * 4 + j * 4] == 0xFF)
			{
				immove.x = j * 4 * DISPLAY_SCALE - px * DISPLAY_SCALE;
				immove.y = i * 4 * DISPLAY_SCALE - py * DISPLAY_SCALE;
				// SDL_RenderFillRect(SDLX_GetDisplay()->renderer, &(immove));
				SDL_RenderDrawRect(SDLX_GetDisplay()->renderer, &(immove));
			}
			j++;
		}
		i++;
	}
}

void	view_player_collision(int x, int y)
{
	SDL_Rect	player = {x * DISPLAY_SCALE, y * DISPLAY_SCALE, 16 * DISPLAY_SCALE, 16 * DISPLAY_SCALE};
	SDL_RenderDrawRect(SDLX_GetDisplay()->renderer, &(player));
}