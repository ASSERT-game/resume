/***************************************************************************
 * FILENAME:    chest.c
 * DESCRIPTION: Creates a chest entity
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

void	chest_init(t_entity *chest, int x, int y, SDL_Surface *collision_map)
{
	chest->sprite = SDLX_Sprite_Static(ASSETS"chest.png");
	chest->sprite.dst = SDLX_NULL_SELF;
	chest->sprite._dst = (SDL_Rect){x, y, 32, 16};

	chest->world_x = x;
	chest->world_y = y;

	chest->isActive = SDL_TRUE;
	chest->update = chest_update;

	new_static_sprite(&(chest->sprite), 2, 1, 1, 1, 2, 2, collision_map);
}

void	chest_update(t_entity *chest, int world_x, int world_y)
{
	chest->sprite._dst.x = chest->world_x - world_x;
	chest->sprite._dst.y = chest->world_y - world_y;
	fill_priority(&(chest->sprite));

	SDLX_RenderQueue_Add(NULL, &(chest->sprite));
}
