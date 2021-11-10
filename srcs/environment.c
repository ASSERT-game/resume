/***************************************************************************
 * FILENAME:    environment.c
 * DESCRIPTION: Adds objects to the environment with static collisions.
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

void	new_static_sprite(SDLX_Sprite *sprite, int tiles_x, int tiles_y, int bottom_padding, int top_padding, int left_padding, int right_padding, SDL_Surface *collision_map)
{
	Uint8		*pixels;
	SDL_Rect	*rect;

	rect = sprite->dst;
	if (sprite->dst == SDLX_NULL_SELF)
		rect = &(sprite->_dst);

	SDL_assert(rect->w >= tiles_x * 16);
	SDL_assert(rect->h >= tiles_y * 16);

	int	x_start, y_start;
	int	x_stop, y_stop;

	x_start = rect->x / 4 + left_padding;
	y_start = rect->y / 4 + top_padding;

	x_stop = rect->x / 4 + tiles_x * 4 - right_padding;
	y_stop = rect->y / 4 + tiles_y * 4 - bottom_padding;

	SDL_assert(x_start <= x_stop);
	SDL_assert(y_start <= y_stop);

	SDL_assert(0 <= x_start && x_start <= collision_map->w);
	SDL_assert(0 <= y_start && y_start <= collision_map->h);

	int	i;
	int	j;

	i = y_start;
	pixels = collision_map->pixels;
	while (i < y_stop)
	{
		j = x_start;
		while (j < x_stop)
		{
			pixels[i * collision_map->w * 4 + j * 4] = 0xFF;
			j++;
		}
		i++;
	}
}