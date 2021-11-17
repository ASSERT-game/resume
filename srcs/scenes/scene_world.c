/***************************************************************************
 * FILENAME:    scene_world.c
 * DESCRIPTION: The entire world level.
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 31Oct2021
***************************************************************************/

#include "main.h"

typedef struct	s_world
{

	SDLX_button	tutorial_move;
	SDLX_button	tutorial_dash;
	SDLX_button	tutorial_slash;

	SDL_Rect	*space;

	int			local_x;
	int			local_y;

	t_player	player;

	entity_system		main_spawner;
}				t_world;

#include <stdio.h>

void	*world_init(SDLX_scene_cxt *context, SDL_UNUSED void *vp_scene)
{
	t_world	*world;
	SDLX_Sprite	*level;

	g_SDLX_Context.ticks_num2 = 0;
	world = SDLX_NewScene(sizeof(*world), context, ASSETS"world_start.png", world_close, world_update);

	level = SDLX_GetBackground();
	level->sprite_data->src = &(level->sprite_data->_src);
	level->sprite_data->_src = (SDL_Rect){64, 80, 320, 224};

	world->space = level->sprite_data->src;

	SDLX_Button_Init(&(world->tutorial_move), fetch_tooltip_sprite, 1, (SDL_Rect){(320 + 48) / 2, 96, 96 / 2, 80 / 2}, NULL);
	world->tutorial_move.get_focus_fn = tooltip_move_focus;
	world->tutorial_move.update_fn = tooltip_update;
	world->tutorial_move.meta = &(g_SDLX_Context.ticks_num2);
	world->tutorial_move.sprite.sort = 10000;

	world->local_x = 16 * 9;
	world->local_y = 16 * 7;
	player_init(&(world->player), world->local_x, world->local_y);

	g_SDLX_Context.meta2 = entity_system_init(&(world->main_spawner));

	drop_entities_load();
	environment_entities_load();
	interactable_entities_load();

	return (NULL);
}

void	*world_close(SDL_UNUSED SDLX_scene_cxt *context, void *vp_scene)
{
	(void)context;
	(void)vp_scene;
	return (NULL);
}

void	*world_update(SDL_UNUSED SDLX_scene_cxt *context, void *vp_scene)
{
	int	dx, dy;
	Uint8 *pixels;
	t_world	*world;

	world = vp_scene;
	resume_joystick_to_gameinput();
	SDLX_toTriggers(&(g_GameInput));

	world->player.state = STATE_NONE;
	if (world->player.stunned_tick > 0)
		world->player.state = STATE_STUNNED;

	dx = 0;
	dy = 0;
	player_aim(&(world->player));
	player_attack(&(world->player));
	player_use_spec(&(world->player.state), world->player.sprite._dst.x, world->player.sprite._dst.y);
	player_move(&(dx), &(dy), &(world->player.state));
	player_dash(&(dx), &(dy), &(world->player.state));

	pixels = world->main_spawner.collision_map->pixels;
	int width = world->main_spawner.collision_map->w * 4;
	if (	pixels[((world->local_y + world->space->y) / 4) * width + ((world->local_x + dx + world->space->x) / 4) * 4] == 0xFF
		||	pixels[((world->local_y + world->space->y) / 4) * width + ((world->local_x + dx + 12 + world->space->x) / 4) * 4] == 0xFF
		||	pixels[((world->local_y + world->space->y + 8) / 4) * width + ((world->local_x + dx + 12 + world->space->x) / 4) * 4] == 0xFF
		||	pixels[((world->local_y + world->space->y + 8) / 4) * width + ((world->local_x + dx + world->space->x) / 4) * 4] == 0xFF
		||	pixels[((world->local_y + 12 + world->space->y) / 4) * width + ((world->local_x + dx + world->space->x) / 4) * 4] == 0xFF
		||	pixels[((world->local_y + 12 + world->space->y) / 4) * width + ((world->local_x + dx + 12 + world->space->x) / 4) * 4] == 0xFF)
		dx = 0;
	else
		world->local_x += dx;

	if (	pixels[((world->local_y + dy + world->space->y) / 4) * width + ((world->local_x + world->space->x) / 4) * 4] == 0xFF
		||	pixels[((world->local_y + dy + world->space->y) / 4) * width + ((world->local_x + 12 + world->space->x) / 4) * 4] == 0xFF
		||	pixels[((world->local_y + dy + 12 + world->space->y) / 4) * width + ((world->local_x + world->space->x) / 4) * 4] == 0xFF
		||	pixels[((world->local_y + dy + world->space->y) / 4) * width + ((world->local_x + world->space->x + 8) / 4) * 4] == 0xFF
		||	pixels[((world->local_y + dy + 12 + world->space->y) / 4) * width + ((world->local_x + world->space->x + 8) / 4) * 4] == 0xFF
		||	pixels[((world->local_y + dy + 12 + world->space->y) / 4) * width + ((world->local_x + 12 + world->space->x) / 4) * 4] == 0xFF)
		dy = 0;
	else
		world->local_y += dy;

	world->player.sprite._dst.x = world->local_x - 8;
	world->player.sprite._dst.y = world->local_y - 8;
	world->player.sprite.sort = (world->local_y / 4 + 5) * 100;

	SDLX_Button_Update_noDraw(&(world->tutorial_move));

	update_entities(&(world->main_spawner), world->space->x, world->space->y);

	move_viewport(&(world->local_x), &(world->local_y), &(world->space->x), &(world->space->y));

	potion_update(&(world->player));
	special_ui_update(&(world->player));
	main_attack_ui_update(&(world->player));
	bar_system_update(&(world->player.mana));
	bar_system_update(&(world->player.health));
	update_crosshair(&(world->player), world->player.sprite._dst.x, world->player.sprite._dst.y);

	SDLX_RenderQueue_Add(NULL, &(world->player.sprite));
	// SDLX_RenderQueue_Add(NULL, &(world->player.sprite));



	if (g_GameInput.GameInput.button_RIGHTSHOULDER)
		world->player.mana.value += 1;

	if (SDLX_GAME_PRESS(g_GameInput, g_GameInput_prev, LEFTSHOULDER))
		increase_bar_system(&(world->player.mana), 32, 32, SDL_FALSE);

	if (SDLX_GAME_PRESS(g_GameInput, g_GameInput_prev, B))
		world->player.mana.value -= 10;

	if (g_SDLX_Context.ticks_num2 % 20 == 0)
	{
		init_heart_pickup(spawn_entity_addr(g_SDLX_Context.meta2, ET_DROPS), rand() % 448, rand() % 384);
	}

	// SDL_Log("Score: %d", world->player.coins);



	// view_player_collision(world->local_x, world->local_y);
	// view_map_collisions(world->collision, world->space->x, world->space->y);
	SDL_qsort(default_RenderQueue.content, default_RenderQueue.index, sizeof(default_RenderQueue.content), compare_priority);
	SDLX_CollisionBucket_Flush(NULL);

	return (NULL);
}
