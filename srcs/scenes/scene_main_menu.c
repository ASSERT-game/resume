/***************************************************************************
 * FILENAME:    scene_main_menu.c
 * DESCRIPTION: Scene for the main menu
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 30Oct2021
***************************************************************************/

#include "main.h"

typedef	struct	s_main_menu_scene
{
	SDLX_Sprite			tittle;

	SDLX_button	play;
}				t_main_menu_scene;

void	*main_menu_init(SDLX_scene_cxt *context, SDL_UNUSED void *vp_scene)
{
	t_main_menu_scene *scene;

	scene = SDLX_NewScene(sizeof(*scene), context, ASSETS"main_men.png", main_menu_close, main_menu_update);

	g_SDLX_Context.background_color = (SDL_Color){51, 50, 61, 255};

	// scene->tittle = SDLX_Sprite_Static(ASSETS"tittle_c.png");
	// scene->tittle._dst = (SDL_Rect){MID_PLAY_WIDTH - 132 - 5, 40, 264, 180};
	// scene->tittle.dst = SDLX_NULL_SELF;

	// SDLX_Button_Init(&(scene->play), fetch_ui_sprite, PLAY_NORM, (SDL_Rect){(PLAY_WIDTH - 23 * UI_ENLARGE) / 2, 275, 23 * UI_ENLARGE, 11 * UI_ENLARGE}, NULL);
	// SDLX_Style_Button(&(scene->play), PLAY_NORM, PLAY_HOVER);
	// scene->play.meta = context;
	// scene->play.meta1 = level_select_init;
	// scene->play.trigger_fn = button_trigger_scene_switch;

	return (NULL);
}

void	*main_menu_close(SDL_UNUSED SDLX_scene_cxt *context, void *vp_scene)
{
	t_main_menu_scene *scene;

	scene = vp_scene;

	SDL_free(context->background.sprite_data);
	SDLX_free_null(&(context->scene_meta));
	SDLX_ClearBackground();

	if (g_SDLX_Context.extra_num8 & TOOLTIP_CONTROLS)
		g_SDLX_Context.init_fn = TT_controls_init;
	else
		g_SDLX_Context.init_fn = world_init;

	return (NULL);
}

void	*main_menu_update(SDL_UNUSED SDLX_scene_cxt *context, void *vp_scene)
{
	// t_main_menu_scene *scene;

	// scene = vp_scene;

	// SDLX_RenderQueue_Add(NULL, &(scene->tittle));
	// SDLX_Button_Update(&(scene->play));

	if (SDLX_GAME_PRESS(g_GameInput, g_GameInput_prev, START))
		g_SDLX_Context.shouldChange = SDL_TRUE;

	(void)vp_scene;
	(void)context;
	return (NULL);
}
