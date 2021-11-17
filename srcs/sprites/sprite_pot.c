/***************************************************************************
 * FILENAME:    sprite_pot.c
 * DESCRIPTION: Fetches the pot sprite
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 17Nov2021
***************************************************************************/

#include "main.h"

SDLX_Sprite_Data *carve_pot_sprite(void)
{
	size_t				i;
	size_t				j;
	SDL_Texture			*texture;
	SDLX_Sprite_Data	*result;

	result = SDL_calloc(10, sizeof(*result));
	texture = SDLX_LoadTexture(ASSETS"pot.png");

	i = 0;

	result[i].texture = texture;
	result[i]._src = (SDL_Rect){0, 0, 16, 16};
	result[i].src = &(result[i]._src);
	result[i].cycle = 1;
	i++;
	result[i].texture = texture;
	result[i]._src = (SDL_Rect){16, 0, 16, 16};
	result[i].src = &(result[i]._src);
	result[i].cycle = 1;
	i++;
	result[i].texture = texture;
	result[i]._src = (SDL_Rect){0, 16, 16, 16};
	result[i].src = &(result[i]._src);
	result[i].cycle = 1;
	i++;
	result[i].texture = texture;
	result[i]._src = (SDL_Rect){16, 16, 16, 16};
	result[i].src = &(result[i]._src);
	result[i].cycle = 1;
	i++;

	j = 0;
	while (j < 6)
	{
		result[i].texture = texture;
		result[i]._src = (SDL_Rect){j * 16, 32, 16, 16};
		result[i].src = &(result[i]._src);
		result[i].cycle = 6;
		i++;
		j++;
	}

	return (result);
}

int		fetch_pot_sprite(SDLX_Sprite_Data **dst, int no)
{
	static SDLX_Sprite_Data	*sprite_arr;

	if (sprite_arr == NULL)
		sprite_arr = carve_pot_sprite();

	if (no == 0)		{ *dst = &(sprite_arr[0]); }
	else if (no == 1)		{ *dst = &(sprite_arr[1]); }
	else if (no == 2)		{ *dst = &(sprite_arr[2]); }
	else if (no == 3)		{ *dst = &(sprite_arr[3]); }
	else if (no == 4)		{ *dst = &(sprite_arr[4]); }

	return (EXIT_SUCCESS);
}