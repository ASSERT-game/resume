/***************************************************************************
 * FILENAME:    utils.c
 * DESCRIPTION: Utility Functions.
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 10Nov2021
***************************************************************************/

#include "main.h"

uint32_t	lerp32(double percent, uint32_t start, uint32_t end)
{
	uint32_t result;

	result = ((end - start) * percent);
	return (result);
}

void	world_align(SDLX_Sprite *sprite, int x, int y, int world_x, int world_y, int sort_bonus)
{
	sprite->_dst.x = x - world_x;
	sprite->_dst.y = y - world_y;
	fill_priority(sprite);
	sprite->sort += sort_bonus;
}

void	radial_attract(int dx, int dy, int radius, int speed, double *x, double *y)
{
	double	angle;

	if (dx * dx + dy * dy < radius * radius)
	{
		angle = SDL_atan2(dy, dx);
		*x -= SDL_cos(angle) * speed;
		*y -= SDL_sin(angle) * speed;
	}
}