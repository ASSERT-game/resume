/***************************************************************************
 * FILENAME:    sprite_skullball.c
 * DESCRIPTION: Fetches the skullball sprite
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 18Nov2021
***************************************************************************/

#include "main.h"

SDLX_Sprite_Data *carve_skullball_sprite(void)
{
	size_t				i;
	SDL_Texture			*texture;
	SDLX_Sprite_Data	*result;

	result = SDL_calloc(11, sizeof(*result));
	texture = SDLX_LoadTexture(ASSETS"skullball.png");

	i = 0;
	result[i].texture = texture;
	result[i]._src = (SDL_Rect){0, 0, 16, 16};
	result[i].src = &(result[i]._src);
	result[i].cycle = 1;
	i++;

	while (i < 11)
	{
		result[i].texture = texture;
		result[i]._src = (SDL_Rect){(i - 1) * 16, 16, 16, 16};
		result[i].src = &(result[i]._src);
		result[i].cycle = 10;
		i++;
	}

	return (result);
}

int		fetch_skullball_sprite(SDLX_Sprite_Data **dst, int no)
{
	static SDLX_Sprite_Data	*sprite_arr;

	if (sprite_arr == NULL)
		sprite_arr = carve_skullball_sprite();

	if (no == 0)		{ *dst = &(sprite_arr[0]); }
	if (no == 1)		{ *dst = &(sprite_arr[1]); }

	return (EXIT_SUCCESS);
}