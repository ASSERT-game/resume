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

typedef struct	s_main_attacks
{
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

	int				max_potion;
	int				potion_no;
	int				potion_curr;
	t_potion		*potions;

	int				special_no;
	int				special_curr;
	t_special		specials[4];

	int				state;
	int				stunned_tick;

}				t_player;

typedef struct	s_entity
{
	SDLX_Sprite	sprite;

	double		world_x;
	double		world_y;

	int			state;

	void		*meta;

	char		alloc[64];
}				t_entity;

#endif