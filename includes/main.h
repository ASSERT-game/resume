/***************************************************************************
 * FILENAME:    main.h
 * DESCRIPTION: Main Header file included in most files.
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 30Oct2021
***************************************************************************/

#ifndef MAIN_H
# define MAIN_H

# include "SDLX.h"

# define ASSETS "assets/"

SDLX_iMap	*resume_pad_map(size_t *size);
SDLX_iMap	*resume_key_map(size_t *size);

void	*main_menu_init(SDLX_scene_cxt *context, SDL_UNUSED void *vp_scene);
void	*main_menu_close(SDL_UNUSED SDLX_scene_cxt *context, void *vp_scene);
void	*main_menu_update(SDL_UNUSED SDLX_scene_cxt *context, void *vp_scene);

void	*world_init(SDLX_scene_cxt *context, SDL_UNUSED void *vp_scene);
void	*world_close(SDL_UNUSED SDLX_scene_cxt *context, void *vp_scene);
void	*world_update(SDL_UNUSED SDLX_scene_cxt *context, void *vp_scene);

void	*TT_controls_init(SDLX_scene_cxt *context, SDL_UNUSED void *vp_scene);
void	*TT_controls_close(SDL_UNUSED SDLX_scene_cxt *context, void *vp_scene);
void	*TT_controls_update(SDL_UNUSED SDLX_scene_cxt *context, void *vp_scene);

int		fetch_tooltip_sprite(SDLX_Sprite_Data **dst, int no);

void	*tooltip_update(SDLX_button *button, void *meta, size_t meta_length);
SDL_bool	tooltip_move_focus(SDLX_button *button, void *meta, size_t meta_length);

typedef	enum	e_tooltips
{
	TOOLTIP_NONE		= 0b00000000,
	TOOLTIP_CONTROLS	= 0b00000001,

	TOOLTIP_ALL			= 0b11111111,
}				t_tooltips;

#endif