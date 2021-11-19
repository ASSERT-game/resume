/***************************************************************************
 * FILENAME:    main_loader.c
 * DESCRIPTION: Loads the General World Scene.
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

void	environment_entities_load(void)
{
	entity_system	*system;
	SDL_Surface		*collision_map;

	system = g_SDLX_Context.meta2;
	collision_map = system->collision_map;

	scoregrave_init(	spawn_entity_addr(system, ET_ENVIRONMENT), 176, 96);
	// static_environment_init(	spawn_entity_addr(system, ET_ENVIRONMENT), 176, 96, collision_map);
	// static_environment_init(	spawn_entity_addr(system, ET_ENVIRONMENT), 176, 64, collision_map);
	// static_environment_init(	spawn_entity_addr(system, ET_ENVIRONMENT), 256, 96, collision_map);
	// static_environment_init(	spawn_entity_addr(system, ET_ENVIRONMENT), 256, 64, collision_map);
	// static_environment_rl_init(	spawn_entity_addr(system, ET_ENVIRONMENT), 64, 240, collision_map);
	// static_environment_ll_init(	spawn_entity_addr(system, ET_ENVIRONMENT), 64, 240, collision_map);

}

void	interactable_entities_load(void)
{
	entity_system	*system;
	SDL_Surface		*collision_map;

	system = g_SDLX_Context.meta2;
	collision_map = system->collision_map;
	// chest_init(	spawn_entity_addr(system, ET_INTERACTABLE), 208, 112, collision_map);
	pot_init(	spawn_entity_addr(system, ET_INTERACTABLE), 64, 144, collision_map);
	pot_init(	spawn_entity_addr(system, ET_INTERACTABLE), 64, 240, collision_map);
	pot_init(	spawn_entity_addr(system, ET_INTERACTABLE), 416, 144, collision_map);
	pot_init(	spawn_entity_addr(system, ET_INTERACTABLE), 416, 240, collision_map);

	// skullball_init(spawn_entity_addr(system, ET_INTERACTABLE), 240, 196);
	skullball_init(spawn_entity_addr(system, ET_INTERACTABLE), 240 + 16, 196);
	skullball_init(spawn_entity_addr(system, ET_INTERACTABLE), 240 - 16, 196);

	skullghost_init(spawn_entity_addr(system, ET_INTERACTABLE), 144, 64);
	skullghost_init(spawn_entity_addr(system, ET_INTERACTABLE), 336, 64);
	skullghost_init(spawn_entity_addr(system, ET_INTERACTABLE), 144, 304);
	skullghost_init(spawn_entity_addr(system, ET_INTERACTABLE), 336, 304);

	skullghost_init(spawn_entity_addr(system, ET_INTERACTABLE), 144 + 32, 64);
	skullghost_init(spawn_entity_addr(system, ET_INTERACTABLE), 336 - 32, 64);
	skullghost_init(spawn_entity_addr(system, ET_INTERACTABLE), 144 + 32, 304);
	skullghost_init(spawn_entity_addr(system, ET_INTERACTABLE), 336 - 32, 304);
	// pot_init(	spawn_entity_addr(system, ET_INTERACTABLE), 192 + 48,	96 + 16 * 4, collision_map);
	// pot_init(	spawn_entity_addr(system, ET_INTERACTABLE), 192 + 48,	96 + 16 * 6, collision_map);
	// pot_init(	spawn_entity_addr(system, ET_INTERACTABLE), 192 + 48,	96 + 16 * 8, collision_map);
	// pot_init(	spawn_entity_addr(system, ET_INTERACTABLE), 192 + 48,	96 + 16 * 10, collision_map);
}

void	drop_entities_load(void)
{
	entity_system	*system;
	SDL_Surface		*collision_map;

	system = g_SDLX_Context.meta2;
	collision_map = system->collision_map;
	spawner_purple_init(spawn_entity_addr(system, ET_DROPS), 144, 144);
	spawner_purple_init(spawn_entity_addr(system, ET_DROPS), 144, 240);
	spawner_purple_init(spawn_entity_addr(system, ET_DROPS), 336, 144);
	spawner_purple_init(spawn_entity_addr(system, ET_DROPS), 336, 240);
	// spawner_purple_init(spawn_entity_addr(system, ET_DROPS), 128, 128);
	// init_heart_pickup(spawn_entity_addr(system, ET_DROPS), 128, 128);
	// init_heart_pickup(spawn_entity_addr(system, ET_DROPS), 128 + 128, 128);
	// init_heart_pickup(spawn_entity_addr(system, ET_DROPS), 128, 128 + 64);
	// init_heart_pickup(spawn_entity_addr(system, ET_DROPS), 128 + 128, 128 + 64);
	// init_heart_pickup(spawn_entity_addr(system, ET_DROPS), 128 + 32, 128);
}