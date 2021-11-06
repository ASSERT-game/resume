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

	t_player	player;

	SDLX_Sprite	hud;
}				t_world;

void	*world_init(SDLX_scene_cxt *context, SDL_UNUSED void *vp_scene)
{
	t_world	*world;
	SDLX_Sprite	*level;

	world = SDLX_NewScene(sizeof(*world), context, ASSETS"world_start.png", world_close, world_update);
	level = SDLX_GetBackground();

	level->sprite_data->_src = (SDL_Rect){(64), 64, 320, 224};
	level->sprite_data->src = &(level->sprite_data->_src);

	world->space = level->sprite_data->src;

	SDLX_Button_Init(&(world->tutorial_move), fetch_tooltip_sprite, 1, (SDL_Rect){(320 + 48) / 2, 80, 96 / 2, 80 / 2}, NULL);
	world->tutorial_move.get_focus_fn = tooltip_move_focus;
	world->tutorial_move.update_fn = tooltip_update;
	world->tutorial_move.meta = &(g_SDLX_Context.ticks_num2);

	g_SDLX_Context.ticks_num2 = 0;

	world->local_x = 144;
	world->local_y = 96;

	world->player.sprite = SDLX_Sprite_Static(ASSETS"character.png");
	world->player.sprite.dst = SDLX_NULL_SELF;

	world->player.max_potion = 7;
	world->player.potion_no = 7;
	world->player.potion_curr = 0;

	spec_ui_init(&(world->player));
	main_attack_ui_init(&(world->player));
	potion_init(&(world->player.potions), 7);
	crosshair_init(&(world->player.crosshair));


	world->hud = SDLX_Sprite_Static(ASSETS"hud.png");

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

	SDLX_JoyStick_toDPAD(g_GameInput.GameInput.leftaxis,
		&(g_GameInput.GameInput.button_DPAD_LEFT), &(g_GameInput.GameInput.button_DPAD_RIGHT),
		&(g_GameInput.GameInput.button_DPAD_UP), &(g_GameInput.GameInput.button_DPAD_DOWN)
	);

	SDLX_JoyStick_toDPAD(g_GameInput.GameInput.rightaxis,
		&(g_GameInput.GameInput.button_num0), &(g_GameInput.GameInput.button_num1),
		&(g_GameInput.GameInput.button_num2), &(g_GameInput.GameInput.button_num3)
	);

	SDLX_toTriggers(&(g_GameInput));

	world->player.state = STATE_NONE;

	int	dx, dy;

	dx = 0;
	dy = 0;

	player_aim(&(world->player.state));
	player_use_spec(&(world->player.state), world->player.sprite._dst.x, world->player.sprite._dst.y);
	player_move(&(dx), &(dy), &(world->player.state));
	player_dash(&(dx), &(dy), &(world->player.state));

	SDLX_Button_Update_noDraw(&(world->tutorial_move));

	world->local_x += dx;
	world->local_y += dy;

	SDL_Rect	bound = {(128 - 16) * DISPLAY_SCALE, (80 - 16) * DISPLAY_SCALE, (320 - 256) * DISPLAY_SCALE, (224 - 160) * DISPLAY_SCALE};
	SDL_Rect	player = {(world->local_x) * DISPLAY_SCALE, (world->local_y) * DISPLAY_SCALE, 16 * DISPLAY_SCALE, 16 * DISPLAY_SCALE};

	if (player.y < bound.y && world->space->y - 4 >= 0)
	{
		world->space->y -= 4;
		world->local_y += 4;
	}

	if (player.y > bound.y + bound.h && world->space->y + 224 + 4 <= 384)
	{
		world->space->y += 4;
		world->local_y -= 4;
	}

	if (player.x > bound.x + bound.w && world->space->x + 320 + 4 < 448)
	{
		world->space->x += 4;
		world->local_x -= 4;
	}

	if (player.x < bound.x && world->space->x - 4 > 0)
	{
		world->space->x -= 4;
		world->local_x += 4;
	}

	world->player.sprite._dst.x = player.x / DISPLAY_SCALE - 7;
	world->player.sprite._dst.y = player.y / DISPLAY_SCALE - 8;
	world->player.sprite._dst.w = 32;
	world->player.sprite._dst.h = 32;

	update_crosshair(&(world->player), world->player.sprite._dst.x, world->player.sprite._dst.y);

	potion_update(&(world->player));
	special_ui_update(&(world->player));
	main_attack_ui_update(&(world->player));

	SDLX_RenderQueue_Add(NULL, &(world->hud));
	SDLX_RenderQueue_Add(NULL, &(world->player.sprite));

	SDL_SetRenderDrawColor(SDLX_GetDisplay()->renderer, 255, 0, 0, 0);
	SDL_RenderDrawRect(SDLX_GetDisplay()->renderer, &(bound));
	SDL_RenderDrawRect(SDLX_GetDisplay()->renderer, &(player));

	(void)context;
	(void)vp_scene;
	return (NULL);
}
