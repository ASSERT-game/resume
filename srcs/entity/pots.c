/***************************************************************************
 * FILENAME:    pots.c
 * DESCRIPTION: Creates a pot entity.
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

void	pot_init(t_entity *pot, int x, int y, SDL_Surface *collision_map)
{
	pot->sprite = SDLX_Sprite_Static(ASSETS"pot.png");
	pot->sprite.dst = SDLX_NULL_SELF;
	pot->sprite._dst = (SDL_Rect){x, y, 16, 16};

	pot->world_x = x;
	pot->world_y = y;

	pot->isActive = SDL_TRUE;
	pot->update = pot_update;

	new_static_sprite(&(pot->sprite), 1, 1, 1, 1, 1, 1, collision_map);
}

void	pot_update(t_entity *pot, int world_x, int world_y)
{
	pot->sprite._dst.x = pot->world_x - world_x;
	pot->sprite._dst.y = pot->world_y - world_y;
	fill_priority(&(pot->sprite));

	SDLX_RenderQueue_Add(NULL, &(pot->sprite));
}
