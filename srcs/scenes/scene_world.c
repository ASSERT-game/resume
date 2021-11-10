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

	SDL_Rect	clamp;
	SDL_Rect	*space;

	int			local_x;
	int			local_y;

	int			local_x_prev;
	int			local_y_prev;

	t_player	player;

	SDLX_Sprite	hud;
	SDL_Surface *collision;

	SDLX_Sprite	wall1;
	SDLX_Sprite	wall2;
	SDLX_Sprite	wall3;
	SDLX_Sprite	wall4;

	SDLX_Sprite	pot1;
	SDLX_Sprite	pot2;
	SDLX_Sprite	pot3;
	SDLX_Sprite	pot4;
	SDLX_Sprite	pot5;
	SDLX_Sprite	pot6;
	SDLX_Sprite	pot7;
	SDLX_Sprite	pot8;

	SDLX_Sprite	chest;
	t_player		exist[100000];
}				t_world;

#include <stdio.h>

void	*world_init(SDLX_scene_cxt *context, SDL_UNUSED void *vp_scene)
{
	t_world	*world;
	SDLX_Sprite	*level;

	world = SDLX_NewScene(sizeof(*world), context, ASSETS"world_start.png", world_close, world_update);
	level = SDLX_GetBackground();

	level->sprite_data->_src = (SDL_Rect){64, 64, 320, 224};
	level->sprite_data->src = &(level->sprite_data->_src);

	world->space = level->sprite_data->src;

	SDLX_Button_Init(&(world->tutorial_move), fetch_tooltip_sprite, 1, (SDL_Rect){(320 + 48) / 2, 80, 96 / 2, 80 / 2}, NULL);
	world->tutorial_move.get_focus_fn = tooltip_move_focus;
	world->tutorial_move.update_fn = tooltip_update;
	world->tutorial_move.meta = &(g_SDLX_Context.ticks_num2);

	g_SDLX_Context.ticks_num2 = 0;

	world->local_x = 16 * 9;
	world->local_y = 16 * 8;

	world->local_x = 16 * 0;
	world->local_y = 16 * 0;

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

	world->collision = IMG_Load(ASSETS"finer_collision.png");

	world->hud = SDLX_Sprite_Static(ASSETS"hud.png");
	world->hud.sort = 999;

	world->wall1 = SDLX_Sprite_Static(ASSETS"wall.png");
	world->wall1.dst = SDLX_NULL_SELF;
	world->wall1._dst = (SDL_Rect){176, 96, 16, 48};
	new_static_sprite(&(world->wall1), 1, 3, 2, 8, 1, 1, world->collision);

	world->wall2 = SDLX_Sprite_Static(ASSETS"wall.png");
	world->wall2.dst = SDLX_NULL_SELF;
	world->wall2._dst = (SDL_Rect){176 + 16 * 5, 96, 16, 48};
	new_static_sprite(&(world->wall2), 1, 3, 2, 8, 1, 1, world->collision);

	world->wall3 = SDLX_Sprite_Static(ASSETS"wall.png");
	world->wall3.dst = SDLX_NULL_SELF;
	world->wall3._dst = (SDL_Rect){176 + 16 * 5, 96 - 32, 16, 48};
	new_static_sprite(&(world->wall3), 1, 3, 2, 8, 1, 1, world->collision);

	world->wall4 = SDLX_Sprite_Static(ASSETS"wall.png");
	world->wall4.dst = SDLX_NULL_SELF;
	world->wall4._dst = (SDL_Rect){176, 96 - 32, 16, 48};
	new_static_sprite(&(world->wall4), 1, 3, 2, 8, 1, 1, world->collision);

	world->pot1 = SDLX_Sprite_Static(ASSETS"pot.png");
	world->pot1.dst = SDLX_NULL_SELF;
	world->pot1._dst = (SDL_Rect){176 + 16, 96  + 16 * 4, 16, 16};
	new_static_sprite(&(world->pot1), 1, 1, 1, 1, 1, 1, world->collision);
	world->pot2 = SDLX_Sprite_Static(ASSETS"pot.png");
	world->pot2.dst = SDLX_NULL_SELF;
	world->pot2._dst = (SDL_Rect){176 + 16, 96  + 16 * 6, 16, 16};
	new_static_sprite(&(world->pot2), 1, 1, 1, 1, 1, 1, world->collision);
	world->pot3 = SDLX_Sprite_Static(ASSETS"pot.png");
	world->pot3.dst = SDLX_NULL_SELF;
	world->pot3._dst = (SDL_Rect){176 + 16, 96  + 16 * 8, 16, 16};
	new_static_sprite(&(world->pot3), 1, 1, 1, 1, 1, 1, world->collision);
	world->pot4 = SDLX_Sprite_Static(ASSETS"pot.png");
	world->pot4.dst = SDLX_NULL_SELF;
	world->pot4._dst = (SDL_Rect){176 + 16, 96  + 16 * 10, 16, 16};
	new_static_sprite(&(world->pot4), 1, 1, 1, 1, 1, 1, world->collision);
	world->pot5 = SDLX_Sprite_Static(ASSETS"pot.png");
	world->pot5.dst = SDLX_NULL_SELF;
	world->pot5._dst = (SDL_Rect){176 + 16 * 4, 96  + 16 * 4, 16, 16};
	new_static_sprite(&(world->pot5), 1, 1, 1, 1, 1, 1, world->collision);
	world->pot6 = SDLX_Sprite_Static(ASSETS"pot.png");
	world->pot6.dst = SDLX_NULL_SELF;
	world->pot6._dst = (SDL_Rect){176 + 16 * 4, 96  + 16 * 6, 16, 16};
	new_static_sprite(&(world->pot6), 1, 1, 1, 1, 1, 1, world->collision);
	world->pot7 = SDLX_Sprite_Static(ASSETS"pot.png");
	world->pot7.dst = SDLX_NULL_SELF;
	world->pot7._dst = (SDL_Rect){176 + 16 * 4, 96  + 16 * 8, 16, 16};
	new_static_sprite(&(world->pot7), 1, 1, 1, 1, 1, 1, world->collision);
	world->pot8 = SDLX_Sprite_Static(ASSETS"pot.png");
	world->pot8.dst = SDLX_NULL_SELF;
	world->pot8._dst = (SDL_Rect){176 + 16 * 4, 96  + 16 * 10, 16, 16};
	new_static_sprite(&(world->pot8), 1, 1, 1, 1, 1, 1, world->collision);

	world->chest = SDLX_Sprite_Static(ASSETS"chest.png");
	world->chest.dst = SDLX_NULL_SELF;
	world->chest._dst = (SDL_Rect){208, 112, 32, 16};
	new_static_sprite(&(world->chest), 2, 1, 1, 1, 2, 2, world->collision);

	// SDL_LockSurface(world->collision);
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

	SDL_Log("Here");

	int	dx, dy;
	Uint8 *pixels = world->collision->pixels;

	world->wall1._dst.x = 176 - world->space->x;
	world->wall1._dst.y = 96 - world->space->y;
	world->wall2._dst.x = 176 + 16 * 5 - world->space->x;
	world->wall2._dst.y = 96 - world->space->y;
	world->wall3._dst.x = 176 - world->space->x;
	world->wall3._dst.y = 96 - 32 - world->space->y;
	world->wall4._dst.x = 176 + 16 * 5 - world->space->x;
	world->wall4._dst.y = 96 - 32 - world->space->y;

	world->pot1._dst.x = 176 + 16 - world->space->x;
	world->pot1._dst.y = 96 + 64 - world->space->y;
	world->pot2._dst.x = 176 + 16 - world->space->x;
	world->pot2._dst.y = 96 + 16 * 6 - world->space->y;
	world->pot3._dst.x = 176 + 16 - world->space->x;
	world->pot3._dst.y = 96 + 16 * 8 - world->space->y;
	world->pot4._dst.x = 176 + 16 - world->space->x;
	world->pot4._dst.y = 96 + 16 * 10 - world->space->y;

	world->pot5._dst.x = 176 + 16 * 4 - world->space->x;
	world->pot5._dst.y = 96  + 16 * 4 - world->space->y;
	world->pot6._dst.x = 176 + 16 * 4 - world->space->x;
	world->pot6._dst.y = 96 + 16 * 6 - world->space->y;
	world->pot7._dst.x = 176 + 16 * 4 - world->space->x;
	world->pot7._dst.y = 96 + 16 * 8 - world->space->y;
	world->pot8._dst.x = 176 + 16 * 4 - world->space->x;
	world->pot8._dst.y = 96 + 16 * 10 - world->space->y;

	world->chest._dst.x = 208 - world->space->x;
	world->chest._dst.y = 112 - world->space->y;

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

	move_viewport(&(world->local_x), &(world->local_y), &(world->space->x), &(world->space->y));

	world->player.sprite._dst.x = world->local_x - 8;
	world->player.sprite._dst.y = world->local_y - 8;

	update_crosshair(&(world->player), world->player.sprite._dst.x, world->player.sprite._dst.y);

	potion_update(&(world->player));
	special_ui_update(&(world->player));
	main_attack_ui_update(&(world->player));

	SDLX_RenderQueue_Add(NULL, &(world->hud));
	SDLX_RenderQueue_Add(NULL, &(world->player.sprite));

	SDLX_RenderQueue_Add(NULL, &(world->wall1));
	SDLX_RenderQueue_Add(NULL, &(world->wall2));
	SDLX_RenderQueue_Add(NULL, &(world->wall3));
	SDLX_RenderQueue_Add(NULL, &(world->wall4));
	SDLX_RenderQueue_Add(NULL, &(world->pot1));
	SDLX_RenderQueue_Add(NULL, &(world->pot2));
	SDLX_RenderQueue_Add(NULL, &(world->pot3));
	SDLX_RenderQueue_Add(NULL, &(world->pot4));
	SDLX_RenderQueue_Add(NULL, &(world->pot5));
	SDLX_RenderQueue_Add(NULL, &(world->pot6));
	SDLX_RenderQueue_Add(NULL, &(world->pot7));
	SDLX_RenderQueue_Add(NULL, &(world->pot8));
	SDLX_RenderQueue_Add(NULL, &(world->chest));

	world->player.sprite.sort = world->local_y / 4 + 5;

	fill_priority(&(world->wall1));
	fill_priority(&(world->wall2));
	fill_priority(&(world->wall3));
	fill_priority(&(world->wall4));
	fill_priority(&(world->pot1));
	fill_priority(&(world->pot2));
	fill_priority(&(world->pot3));
	fill_priority(&(world->pot4));
	fill_priority(&(world->pot5));
	fill_priority(&(world->pot6));
	fill_priority(&(world->pot7));
	fill_priority(&(world->pot8));
	fill_priority(&(world->chest));

	SDL_Log("End");

	SDL_qsort(default_RenderQueue.content, default_RenderQueue.index, sizeof(default_RenderQueue.content), compare_priority);

	if (world->player.stunned_tick > 0)
		world->player.stunned_tick--;

	world->local_x_prev = world->local_x;
	world->local_y_prev = world->local_y;

	view_player_collision(world->local_x, world->local_y);
	view_map_collisions(world->collision, world->space->x, world->space->y);

	return (NULL);
}
