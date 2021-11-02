/***************************************************************************
 * FILENAME:    sprite_tooltip.c
 * DESCRIPTION: Fetches the sprites for the tooltips.
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 01Nov2021
***************************************************************************/

#include "main.h"

/***************************************************************************
 * FILENAME:    level_sprite.c
 * DESCRIPTION: Handles the Sprites for Coins
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 22Jun2021
***************************************************************************/

#include "main.h"

SDLX_Sprite_Data *carve_tooltip_sprite(void)
{
	size_t				i;
	size_t				j;
	SDL_Texture			*texture;
	SDLX_Sprite_Data	*result;

	result = SDL_calloc(34, sizeof(*result));
	texture = SDLX_LoadTexture(ASSETS"tooltip_move.png");

	i = 0;
	/* The Cooldown Icon */
	result[i].texture = texture;
	result[i]._src = (SDL_Rect){0, 0, 96, 80};
	result[i].src = &(result[i]._src);
	result[i].cycle = 1;
	i++;

	j = 0;
	while (j < 13)
	{
		result[i].texture = texture;
		result[i]._src = (SDL_Rect){96 * j, 80, 96, 80};
		result[i].src = &(result[i]._src);
		result[i].cycle = 13;
		// result[i].skip = 1;
		i++;
		j++;
	}

	j = 0;
	while (j < 13)
	{
		result[i].texture = texture;
		result[i]._src = (SDL_Rect){96 * j, 160, 96, 80};
		result[i].src = &(result[i]._src);
		result[i].cycle = 13;
		// result[i].skip = 1;
		i++;
		j++;
	}

	j = 0;
	while (j < 7)
	{
		result[i].texture = texture;
		result[i]._src = (SDL_Rect){96 * j, 240, 96, 80};
		result[i].src = &(result[i]._src);
		result[i].cycle = 7;
		i++;
		j++;
	}

	return (result);
}

int		fetch_tooltip_sprite(SDLX_Sprite_Data **dst, int no)
{
	static SDLX_Sprite_Data	*sprite_arr;

	if (sprite_arr == NULL)
		sprite_arr = carve_tooltip_sprite();

	if (no == 0)		{ *dst = &(sprite_arr[0]); }
	else if (no == 1)	{ *dst = &(sprite_arr[1]); }
	else if (no == 2)	{ *dst = &(sprite_arr[14]); }
	else if (no == 3)	{ *dst = &(sprite_arr[27]); }

	return (EXIT_SUCCESS);
}