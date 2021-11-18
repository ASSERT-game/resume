/***************************************************************************
 * FILENAME:    entity_system.c
 * DESCRIPTION: General entity management functions.
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 13Nov2021
***************************************************************************/

#include "main.h"

#define DEFAULT_E_SIZE (200)

void	spawn_component_init(e_component *component)
{
	component->index = 0;
	component->capacity = DEFAULT_E_SIZE;
	SDLX_CALLOC_M(component->entities, component->capacity);
}

void	*entity_system_init(entity_system *main_spawner)
{
	main_spawner->collision_map = IMG_Load(ASSETS"collision_map.png");

	spawn_component_init(&(main_spawner->drops));
	spawn_component_init(&(main_spawner->enemies));
	spawn_component_init(&(main_spawner->environment));
	spawn_component_init(&(main_spawner->projectiles));
	spawn_component_init(&(main_spawner->interactables));

	return (main_spawner);
}

t_entity	*spawn_entity_addr(entity_system *main_spawner, int kind)
{
	size_t	ix;
	e_component	*bucket;

	ix = 0;
	if (kind == ET_PROJECTILE)
		bucket = &(main_spawner->projectiles);
	else if (kind == ET_INTERACTABLE)
		bucket = &(main_spawner->interactables);
	else if (kind == ET_ENVIRONMENT)
		bucket = &(main_spawner->environment);
	else if (kind == ET_DROPS)
		bucket = &(main_spawner->drops);
	else
		bucket = &(main_spawner->enemies);


	while (ix < bucket->capacity && bucket->entities[ix].isActive == SDL_TRUE)
		ix++;

	SDL_assert(ix < bucket->capacity);
	return (&(bucket->entities[ix]));
}

void	update_entity_list(e_component component, int cam_x, int cam_y)
{
	size_t		ix;
	t_entity	*entity;

	ix = 0;
	while (ix < component.capacity)
	{
		entity = &(component.entities[ix]);
		if (entity->isActive == SDL_TRUE)
			entity->update(entity, cam_x, cam_y);

		ix++;
	}
}

void		update_entities(entity_system *main_spawner, int cam_x, int cam_y)
{
	update_entity_list(main_spawner->drops, cam_x, cam_y);
	update_entity_list(main_spawner->enemies, cam_x, cam_y);
	update_entity_list(main_spawner->projectiles, cam_x, cam_y);
	update_entity_list(main_spawner->environment, cam_x, cam_y);
	update_entity_list(main_spawner->interactables, cam_x, cam_y);
}
