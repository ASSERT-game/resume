/***************************************************************************
 * FILENAME:    sprite_potions.c
 * DESCRIPTION: Sprite potion functions
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 04Nov2021
***************************************************************************/

#include "main.h"

SDLX_Sprite_Data *carve_potion_sprite(void)
{
	size_t				i;
	SDL_Texture			*texture;
	SDLX_Sprite_Data	*result;

	result = SDL_calloc(4, sizeof(*result));
	texture = SDLX_LoadTexture(ASSETS"potion.png");


	i = 0;
	while (i < 4)
	{
		result[i].texture = texture;
		result[i]._src = (SDL_Rect){0, i * 12, 8, 12};
		result[i].src = &(result[i]._src);
		result[i].cycle = 1;

		i++;
	}

	return (result);
}

int		fetch_potion_sprite(SDLX_Sprite_Data **dst, int no)
{
	static SDLX_Sprite_Data	*sprite_arr;

	if (sprite_arr == NULL)
		sprite_arr = carve_potion_sprite();

	if (no == 0)		{ *dst = &(sprite_arr[0]); }
	else if (no == 1)	{ *dst = &(sprite_arr[1]); }
	else if (no == 2)	{ *dst = &(sprite_arr[2]); }
	else if (no == 3)	{ *dst = &(sprite_arr[3]); }

	return (EXIT_SUCCESS);
}