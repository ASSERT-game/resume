/***************************************************************************
 * FILENAME:    queue_util.c
 * DESCRIPTION: Ensures the priority of the sprites as they are added to
 * 			the queue.
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

void	fill_priority(SDLX_Sprite *sprite)
{
	int	y;
	int	h;

	y = sprite->_dst.y;
	h = sprite->_dst.h;
	if (sprite->dst != SDLX_NULL_SELF)
	{
		y = sprite->dst->y;
		h = sprite->dst->h;
	}

	sprite->sort = (y / 4 + h / 4) * 100;
}

int	compare_priority(const void *a, const void *b)
{
	SDLX_Sprite	**sprite_a;
	SDLX_Sprite	**sprite_b;

	sprite_a = (SDLX_Sprite **)a;
	sprite_b = (SDLX_Sprite **)b;

	if ((*sprite_a)->sort > (*sprite_b)->sort)
		return (1);
	else
		return (-1);
}
