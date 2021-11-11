/***************************************************************************
 * FILENAME:    environment.c
 * DESCRIPTION: Functions that update stationary environment entities.
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

void	static_environment_update(t_entity *env, int world_x, int world_y)
{
	env->sprite._dst.x = env->world_x - world_x;
	env->sprite._dst.y = env->world_y - world_y;
	fill_priority(&(env->sprite));

	SDLX_RenderQueue_Add(NULL, &(env->sprite));
}

void	static_environment_init(t_entity *env, int x, int y, SDL_Surface *collision_map)
{
	env->sprite = SDLX_Sprite_Static(ASSETS"wall.png");
	env->sprite.dst = SDLX_NULL_SELF;
	env->sprite._dst = (SDL_Rect){x, y, 16, 48};

	env->world_x = x;
	env->world_y = y;

	new_static_sprite(&(env->sprite), 1, 3, 2, 8, 1, 1, collision_map);
}

void	static_environment_ll_init(t_entity *env, int x, int y, SDL_Surface *collision_map)
{
	env->sprite = SDLX_Sprite_Static(ASSETS"left_log.png");
	env->sprite.dst = SDLX_NULL_SELF;
	env->sprite._dst = (SDL_Rect){x, y, 32, 80};

	env->world_x = x;
	env->world_y = y;

	new_static_sprite(&(env->sprite), 2, 5, 0, 8, 0, 6, collision_map);
}

void	static_environment_rl_init(t_entity *env, int x, int y, SDL_Surface *collision_map)
{
	env->sprite = SDLX_Sprite_Static(ASSETS"right_log.png");
	env->sprite.dst = SDLX_NULL_SELF;
	env->sprite._dst = (SDL_Rect){x + 32, y, 32, 80};

	env->world_x = x + 32;
	env->world_y = y;

	new_static_sprite(&(env->sprite), 2, 5, 0, 8, 3, 3, collision_map);
}