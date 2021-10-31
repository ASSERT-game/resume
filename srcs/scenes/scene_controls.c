/***************************************************************************
 * FILENAME:    scene_controls.c
 * DESCRIPTION: Tooltip menu for the controls
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

void	*TT_controls_init(SDLX_scene_cxt *context, SDL_UNUSED void *vp_scene)
{
	(void)context;
	(void)vp_scene;

	SDL_Log("Tooltip");
	g_SDLX_Context.update_fn = TT_controls_update;
	return (NULL);
}

void	*TT_controls_close(SDL_UNUSED SDLX_scene_cxt *context, void *vp_scene)
{
	SDL_Log("Tooltip Closes");
	(void)context;
	(void)vp_scene;
	return (NULL);
}

void	*TT_controls_update(SDL_UNUSED SDLX_scene_cxt *context, void *vp_scene)
{
	SDL_Log("Tooltip Updates");
	(void)context;
	(void)vp_scene;
	return (NULL);
}


