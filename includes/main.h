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

# include "structs.h"
# include <stdlib.h>

# define ASSETS "assets/"

SDLX_iMap	*resume_pad_map(size_t *size);
SDLX_iMap	*resume_key_map(size_t *size);
void		resume_joystick_to_gameinput(void);

void	*main_menu_init(SDLX_scene_cxt *context, SDL_UNUSED void *vp_scene);
void	*main_menu_close(SDL_UNUSED SDLX_scene_cxt *context, void *vp_scene);
void	*main_menu_update(SDL_UNUSED SDLX_scene_cxt *context, void *vp_scene);

void	*world_init(SDLX_scene_cxt *context, SDL_UNUSED void *vp_scene);
void	*world_close(SDL_UNUSED SDLX_scene_cxt *context, void *vp_scene);
void	*world_update(SDL_UNUSED SDLX_scene_cxt *context, void *vp_scene);

void	*TT_controls_init(SDLX_scene_cxt *context, SDL_UNUSED void *vp_scene);
void	*TT_controls_close(SDL_UNUSED SDLX_scene_cxt *context, void *vp_scene);
void	*TT_controls_update(SDL_UNUSED SDLX_scene_cxt *context, void *vp_scene);

int		fetch_bar_sprite(SDLX_Sprite_Data **dst, int no);
int		fetch_sword_sprite(SDLX_Sprite_Data **dst, int no);
int		fetch_pickup_sprite(SDLX_Sprite_Data **dst, int no);
int		fetch_potion_sprite(SDLX_Sprite_Data **dst, int no);
int		fetch_tooltip_sprite(SDLX_Sprite_Data **dst, int no);
int		fetch_attack_ui_sprite(SDLX_Sprite_Data **dst, int no);

void		*tooltip_update(SDLX_button *button, void *meta, size_t meta_length);
SDL_bool	tooltip_move_focus(SDLX_button *button, void *meta, size_t meta_length);

void	potion_init(t_potion **potion_ptr, size_t amount);
void	potion_update(t_player *player);

void	main_attack_ui_init(t_player *player);
void	main_attack_ui_update(t_player *player);

void	spec_ui_init(t_player *player);
void	special_ui_update(t_player *player);

void	player_init(t_player *player, int x, int y);
void	player_aim(t_player *player);
void	player_attack(t_player *player);
void	player_dash(int *dx, int *dy, int *state);
void	player_move(int *dx, int *dy, int *state);
void	player_use_spec(int *state, int x, int y);

void	update_crosshair(t_player *player, int x, int y);
void	crosshair_init(SDLX_Sprite *crosshair);

void	move_viewport(int *px, int *py, int *ix, int *iy);

void	new_static_sprite(SDLX_Sprite *sprite, int tiles_x, int tiles_y, int bottom_padding, int top_padding, int left_padding, int right_padding, SDL_Surface *collision_map);

int		compare_priority(const void *a, const void *b);
void	fill_priority(SDLX_Sprite *sprite);

# define PLAYER_SPEED (4)


/*
** Entity Functions
*/

void	pot_update(t_entity *pot, int world_x, int world_y);
void	pot_init(t_entity *pot, int x, int y, SDL_Surface *collision_map);

void	static_environment_update(t_entity *env, int world_x, int world_y);
void	static_environment_init(t_entity *env, int x, int y, SDL_Surface *collision_map);

void	static_environment_rl_init(t_entity *env, int x, int y, SDL_Surface *collision_map);
void	static_environment_ll_init(t_entity *env, int x, int y, SDL_Surface *collision_map);

void	chest_update(t_entity *chest, int world_x, int world_y);
void	chest_init(t_entity *chest, int x, int y, SDL_Surface *collision_map);

void	init_coin_pickup(t_entity *pickup, int x, int y);
void	init_heart_pickup(t_entity *pickup, int x, int y);
void	coin_pickup_update(t_entity *pickup, int world_x, int world_y);
void	heart_pickup_update(t_entity *pickup, int world_x, int world_y);
void	particle_pickup_update(t_entity *pickup, int world_x, int world_y);

void	drop_entities_load(void);
void	environment_entities_load(void);
void	interactable_entities_load(void);

void		*entity_system_init(entity_system *main_spawner);
t_entity	*spawn_entity_addr(entity_system *main_spawner, int kind);
void		update_entities(entity_system *main_spawner, int cam_x, int cam_y);

void			init_attack_array(t_attacks *manager);
t_projectile	*spawn_projectile_addr(t_attacks *dst);


/*
** Bar System Functions
*/

void	resize_healthbar(SDLX_Sprite *fill, SDLX_Sprite *back_fill, int *current, int out_of, SDL_Rect bar);
void	increase_bar_system(t_bar *bar, int amount, int sprite_amount, SDL_bool animate);
void	init_bar_system(t_bar *bar, int start_no, int (*sprite_fn)(SDLX_Sprite_Data **, int), int max, SDL_Rect desired_pos, int offset_left, int offset_right);
void	bar_system_update(t_bar *bar);

/*
** Utility Functions
*/

uint32_t	lerp32(double percent, uint32_t start, uint32_t end);

/*
** Debug Functions
*/

void	view_map_collisions(SDL_Surface *image, int px, int py);
void	view_player_collision(int x, int y);

#endif