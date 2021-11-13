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

#define DEFAULT_A_SIZE (200)

void	init_attack_array(t_attacks *manager) { manager->capacity = DEFAULT_A_SIZE; SDLX_CALLOC_M(manager->projectiles, manager->capacity); }

t_projectile	*spawn_projectile_addr(t_attacks *dst)
{
	size_t		ix;

	ix = 0;
	while (ix < dst->capacity && dst->projectiles[ix].isActive == SDL_TRUE)
		ix++;

	SDL_assert(ix < dst->capacity);
	return (&(dst->projectiles[ix]));
}