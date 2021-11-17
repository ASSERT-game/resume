/***************************************************************************
 * FILENAME:    structs.h
 * DESCRIPTION: The structs for the game in general.
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 03Nov2021
***************************************************************************/

#ifndef STRUCTS_H
# define STRUCTS_H

#include "SDLX.h"

typedef	enum	e_tooltips
{
	TOOLTIP_NONE		= 0b00000000,
	TOOLTIP_CONTROLS	= 0b00000001,

	TOOLTIP_ALL			= 0b11111111,
}				t_tooltips;

typedef struct	s_projectile
{
	SDLX_Sprite		sprite;
	SDLX_collision	hitbox;
	SDL_FPoint		position;

	SDL_Point		vel;
	SDL_bool		isActive;
}				t_projectile;

typedef struct	s_attacks
{
	size_t		capacity;

	t_projectile	*projectiles;
}				t_attacks;

typedef struct	s_main_attacks
{
	SDLX_Sprite	use;
	SDLX_Sprite	sprite;
	SDLX_Sprite	cooldown_sprite;
	int			type;
	char		*name;

	int			damage;
	int			sec_damage;
	int			super_damage;

	int			cooldown;
	int			current;

	int			super;
}				t_main_attacks;

typedef struct	s_special
{
	SDLX_Sprite	sprite;
	SDLX_Sprite	cooldown_sprite;
	int			type;
	char		*name;

	int			damage;

	int			cooldown;
	int			current;
}				t_special;

typedef struct	s_potion
{
	SDLX_Sprite	sprite;
	char		*name;
	int			type;

	int			int_effect;

	void		*meta;

	SDL_bool	isUsed;

	int			*loc;
	int			op;
	int			value;
}				t_potion;

typedef enum	e_player_state
{
	STATE_NONE		= 0b00000000,
	STATE_IDLE		= 0b00000001,
	STATE_WALK		= 0b00000010,
	STATE_ATTACK	= 0b00000100,
	STATE_DAMAGE	= 0b00001000,
	STATE_DEAD		= 0b00010000,
	STATE_AIM		= 0b00100000,
	STATE_STUNNED	= 0b01000000,
}				e_player_state;

typedef struct	s_bar
{
	SDLX_Sprite	start;
	SDLX_Sprite	middle_extender;
	SDLX_Sprite	end;

	SDLX_Sprite	fill;
	SDLX_Sprite	back_fill;

	SDL_Rect	desired_pos;
	int			offset_left;
	int			offset_right;

	int			max_value;
	int			value;
	int			prev_value;
}				t_bar;

typedef struct	s_player
{
	SDLX_Sprite	sprite;

	SDLX_Sprite	crosshair;

	double		local_x;
	double		local_y;

	t_bar		health;
	t_bar		mana;

	int				attack_curr;
	t_main_attacks	*current_attack;
	t_main_attacks	main_attacks[3];

	SDLX_Sprite		potion_hud;
	int				max_potion;
	int				potion_no;
	int				potion_curr;
	t_potion		*potions;

	int				special_no;
	int				special_curr;
	t_special		specials[4];

	int				state;
	int				stunned_tick;

	t_attacks		*attacks;

	t_projectile	attack;

	int				last_facing_angle;

	int				bits;
	int				coins;
}				t_player;

enum	e_collision_types
{
	/* The lower bits are box type and how to interpret box types */

	C_RECT			= 0b00000000000000000001, /* Regular Rectangle */
	C_ARECT			= 0b00000000000000000010, /* Angled Rectangle */
	C_CIRCLE		= 0b00000000000000000100, /* Circle Collision */

	/* The following bits are categorical types */

	C_PLAYER		= 0b00000000000000001000, /* Player */
	C_PROJECTILE	= 0b00000000000000010000, /* Player Projectile */
	C_MELEE			= 0b00000000000000100000, /* Player Melee */
	C_FIELD			= 0b00000000000001000000, /* Player Melee */
	C_E_PROJECTILE	= 0b00000000000010000000, /* Enemy Projectile */
	C_E_BODY		= 0b00000000000100000000, /* Enemy Body */
	C_DESTRUCTABLE	= 0b00000000001000000000, /* Enemy Body */

	C_DEAD			= 0b00000000010000000000, /* Dead / No-Collide */
	C_NONE			= C_DEAD, /* Dead / No-Collide */
};

typedef struct	s_entity
{
	SDL_bool	isActive;
	SDLX_Sprite	sprite;

	double		world_x;
	double		world_y;

	int			state;

	void		*meta;

	void		(*update)(struct s_entity *, int, int);

	char		alloc[256];
}				t_entity;

enum		e_entity_type
{
	ET_NONE,
	ET_DROPS,
	ET_ENEMY,
	ET_PROJECTILE,
	ET_INTERACTABLE,
	ET_ENVIRONMENT,
};

typedef struct	e_component
{
	int			type;

	size_t		index;
	size_t		capacity;

	t_entity	*entities;
}				e_component;

typedef struct	entity_system
{
	SDL_Surface		*collision_map;

	e_component		drops;
	e_component		enemies;
	e_component		projectiles;
	e_component		environment;
	e_component		interactables;
}				entity_system;

#endif