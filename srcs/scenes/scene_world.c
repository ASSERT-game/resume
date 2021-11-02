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

}				t_world;

void	*world_init(SDLX_scene_cxt *context, SDL_UNUSED void *vp_scene)
{
	t_world	*world;

	world = SDLX_NewScene(sizeof(*world), context, ASSETS"main_bg.png", world_close, world_update);

	SDLX_Button_Init(&(world->tutorial_move), fetch_tooltip_sprite, 1, (SDL_Rect){100, 150, 96 / 2, 80 / 2}, NULL);
	world->tutorial_move.get_focus_fn = tooltip_move_focus;
	world->tutorial_move.update_fn = tooltip_update;
	world->tutorial_move.meta = &(g_SDLX_Context.ticks_num2);

	g_SDLX_Context.ticks_num2 = 0;

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
	SDLX_toDPAD(&(g_GameInput), SDLX_AxisConvert(&(g_GameInput.GameInput.leftaxis)));

	SDLX_Button_Update_noDraw(&(world->tutorial_move));
	(void)context;
	(void)vp_scene;
	return (NULL);
}
