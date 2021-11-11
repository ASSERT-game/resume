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
	SDL_Surface *collision;

	int			local_x;
	int			local_y;

	t_player	player;

	SDLX_Sprite	hud;

	t_entity	wall1;
	t_entity	wall2;
	t_entity	wall3;
	t_entity	wall4;

	t_entity	pot1;
	t_entity	pot2;
	t_entity	pot3;
	t_entity	pot4;
	t_entity	pot5;
	t_entity	pot6;
	t_entity	pot7;
	t_entity	pot8;

	t_entity	chest;

	t_bar		health;
	t_bar		mana;
	t_player		exist[100000];
}				t_world;

#include <stdio.h>

void	*world_init(SDLX_scene_cxt *context, SDL_UNUSED void *vp_scene)
{
	t_world	*world;
	SDLX_Sprite	*level;

	world = SDLX_NewScene(sizeof(*world), context, ASSETS"world_start.png", world_close, world_update);
	level = SDLX_GetBackground();

	level->sprite_data->_src = (SDL_Rect){64, 80, 320, 224};
	level->sprite_data->src = &(level->sprite_data->_src);

	world->space = level->sprite_data->src;

	SDLX_Button_Init(&(world->tutorial_move), fetch_tooltip_sprite, 1, (SDL_Rect){(320 + 48) / 2, 96, 96 / 2, 80 / 2}, NULL);
	world->tutorial_move.get_focus_fn = tooltip_move_focus;
	world->tutorial_move.update_fn = tooltip_update;
	world->tutorial_move.meta = &(g_SDLX_Context.ticks_num2);
	world->tutorial_move.sprite.sort = 1000;

	g_SDLX_Context.ticks_num2 = 0;

	world->local_x = 16 * 9;
	world->local_y = 16 * 7;

	world->player.sprite = SDLX_Sprite_Static(ASSETS"character.png");
	world->player.sprite.dst = SDLX_NULL_SELF;
	world->player.sprite._dst.w = 32;
	world->player.sprite._dst.h = 32;

	world->player.max_potion = 7;
	world->player.potion_no = 7;
	world->player.potion_curr = 0;

	spec_ui_init(&(world->player));
	main_attack_ui_init(&(world->player));
	potion_init(&(world->player.potions), 7);
	crosshair_init(&(world->player.crosshair));

	world->collision = IMG_Load(ASSETS"collision.png");

	world->hud = SDLX_Sprite_Static(ASSETS"hud.png");
	world->hud.sort = 999;

	chest_init(&(world->chest), 208, 112, world->collision);

	static_environment_init(&(world->wall1), 176, 96, world->collision);
	static_environment_init(&(world->wall2), 176, 64, world->collision);
	static_environment_init(&(world->wall3), 256, 96, world->collision);
	static_environment_init(&(world->wall4), 256, 64, world->collision);

	pot_init(&(world->pot1), 192, 		96 + 16 * 4, world->collision);
	pot_init(&(world->pot2), 192, 		96 + 16 * 6, world->collision);
	pot_init(&(world->pot3), 192, 		96 + 16 * 8, world->collision);
	pot_init(&(world->pot4), 192, 		96 + 16 * 10, world->collision);
	pot_init(&(world->pot5), 192 + 48,	96 + 16 * 4, world->collision);
	pot_init(&(world->pot6), 192 + 48,	96 + 16 * 6, world->collision);
	pot_init(&(world->pot7), 192 + 48,	96 + 16 * 8, world->collision);
	pot_init(&(world->pot8), 192 + 48,	96 + 16 * 10, world->collision);


	SDL_LockSurface(world->collision);

	init_bar_system(&(world->health), 0, fetch_bar_sprite, 100, (SDL_Rect){5, -4, 32 * 3, 32}, 16, 3);
	init_bar_system(&(world->mana), 5, fetch_bar_sprite, 100, (SDL_Rect){12, 21, 80, 32}, 16, 12);
	(void)context;
	(void)vp_scene;
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
	t_world	*world;

	world = vp_scene;

	resume_joystick_to_gameinput();
	SDLX_toTriggers(&(g_GameInput));

	int	dx, dy;
	Uint8 *pixels = world->collision->pixels;

	dx = 0;
	dy = 0;
	world->player.state = STATE_NONE;
	if (world->player.stunned_tick > 0)
		world->player.state = STATE_STUNNED;

	player_aim(&(world->player.state));
	player_use_spec(&(world->player.state), world->player.sprite._dst.x, world->player.sprite._dst.y);
	player_move(&(dx), &(dy), &(world->player.state));
	player_dash(&(dx), &(dy), &(world->player.state));

	SDLX_Button_Update_noDraw(&(world->tutorial_move));

	int width = world->collision->w * 4;
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

	chest_update(&(world->chest), world->space->x, world->space->y);

	pot_update(&(world->pot1), world->space->x, world->space->y);
	pot_update(&(world->pot2), world->space->x, world->space->y);
	pot_update(&(world->pot3), world->space->x, world->space->y);
	pot_update(&(world->pot4), world->space->x, world->space->y);
	pot_update(&(world->pot5), world->space->x, world->space->y);
	pot_update(&(world->pot6), world->space->x, world->space->y);
	pot_update(&(world->pot7), world->space->x, world->space->y);
	pot_update(&(world->pot8), world->space->x, world->space->y);

	static_environment_update(&(world->wall1), world->space->x, world->space->y);
	static_environment_update(&(world->wall2), world->space->x, world->space->y);
	static_environment_update(&(world->wall3), world->space->x, world->space->y);
	static_environment_update(&(world->wall4), world->space->x, world->space->y);

	move_viewport(&(world->local_x), &(world->local_y), &(world->space->x), &(world->space->y));

	world->player.sprite._dst.x = world->local_x - 8;
	world->player.sprite._dst.y = world->local_y - 8;

	update_crosshair(&(world->player), world->player.sprite._dst.x, world->player.sprite._dst.y);

	potion_update(&(world->player));
	special_ui_update(&(world->player));
	main_attack_ui_update(&(world->player));

	SDLX_RenderQueue_Add(NULL, &(world->hud));
	SDLX_RenderQueue_Add(NULL, &(world->player.sprite));

	if (g_GameInput.GameInput.button_RIGHTSHOULDER)
		world->mana.value += 1;

	if (SDLX_GAME_PRESS(g_GameInput, g_GameInput_prev, LEFTSHOULDER))
		increase_bar_system(&(world->mana), 32, 32, SDL_FALSE);

	if (SDLX_GAME_PRESS(g_GameInput, g_GameInput_prev, B))
		world->mana.value -= 10;

	bar_system_update(&(world->health));
	bar_system_update(&(world->mana));

	world->player.sprite.sort = world->local_y / 4 + 5;

	SDL_qsort(default_RenderQueue.content, default_RenderQueue.index, sizeof(default_RenderQueue.content), compare_priority);

	if (world->player.stunned_tick > 0)
		world->player.stunned_tick--;

	// view_player_collision(world->local_x, world->local_y);
	// view_map_collisions(world->collision, world->space->x, world->space->y);

	return (NULL);
}
