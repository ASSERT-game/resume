/***************************************************************************
 * FILENAME:    purp_sawner.c
 * DESCRIPTION: Spawner type entity for purple hearts.
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 17Nov2021
***************************************************************************/

#include "main.h"

typedef struct	s_spawner
{
	t_entity	*child;
	int			current;

	int			child_x;
	int			child_y;
	SDL_bool	isActive;
}				t_spawner;

void	purple_spawner_update(t_entity *self, int world_x, int world_y)
{
	t_spawner	*spawner;
	t_entity	*child;

	spawner = self->meta;

	if (spawner->isActive)
		spawner->current++;

	if (spawner->current > 150)
	{
		child = spawn_entity_addr(g_SDLX_Context.meta2, ET_DROPS);
		init_purple_heart_pickup(child, self->world_x, self->world_y);
		spawner->current = 0;
		spawner->isActive = SDL_FALSE;
		spawner->child = child;
	}

	if (spawner->child == NULL || spawner->child->isActive == SDL_FALSE)
		spawner->isActive = SDL_TRUE;

	if (spawner->isActive == SDL_FALSE && spawner->child != NULL
		&& (spawner->child->world_x != self->world_x || spawner->child->world_y != self->world_y))
		spawner->isActive = SDL_TRUE;

	(void)world_x;
	(void)world_y;
}

void	spawner_purple_init(t_entity *entity, int x, int y)
{
	t_spawner	*spawner;

	entity->world_x = x;
	entity->world_y = y;

	entity->isActive = SDL_TRUE;
	entity->update = purple_spawner_update;

	entity->meta = &(entity->alloc);
	spawner = entity->meta;
	spawner->isActive = SDL_TRUE;
}