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
	SDLX_Sprite	*sprite;
	SDLX_Sprite	*cooldown_sprite;
	int			type;
	char		*name;

	int			damage;
	int			sec_damage;
	int			super_damage;

	int			cooldown;
	int			current;

	int			super;
}				t_main_attacks;

typedef struct	s_potion
{
	SDLX_Sprite	*sprite;
	char		*name;
	int			type;

	int			int_effect;

	void		*meta;

	SDL_bool	used;
}				t_potion;

typedef struct	s_player
{
	SDLX_Sprite	sprite;

	double		local_x;
	double		local_y;

	int			max_hp;
	int			hp;

	int			max_mp;
	int			mp;

	int				attack_no;
	t_main_attacks	main_attacks[3];

	int				max_potion;
	int				potion_no;
	int				potion_curr;
	t_potion		*potions;

}				t_player;

#endif