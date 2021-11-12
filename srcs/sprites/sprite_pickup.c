/***************************************************************************
 * FILENAME:    sprite_pickup.c
 * DESCRIPTION: Fetches the heart pickup sprite
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 11Nov2021
***************************************************************************/

#include "main.h"

SDLX_Sprite_Data *carve_pickup_sprite(void)
{
	size_t				i;
	SDL_Texture			*texture;
	SDLX_Sprite_Data	*result;

	result = SDL_calloc(19, sizeof(*result));
	texture = SDLX_LoadTexture(ASSETS"heart_pickup.png");

	i = 0;
	while (i < 12)
	{
		result[i].texture = texture;
		result[i]._src = (SDL_Rect){i * 16, 0, 16, 16};
		result[i].src = &(result[i]._src);
		result[i].cycle = 12;

		i++;
	}

	while (i < 12 + 7)
	{
		result[i].texture = texture;
		result[i]._src = (SDL_Rect){(i - 12) * 16, 16, 16, 16};
		result[i].src = &(result[i]._src);
		result[i].cycle = 7;

		i++;
	}

	return (result);
}

int		fetch_pickup_sprite(SDLX_Sprite_Data **dst, int no)
{
	static SDLX_Sprite_Data	*sprite_arr;

	if (sprite_arr == NULL)
		sprite_arr = carve_pickup_sprite();

	if (no == 0)		{ *dst = &(sprite_arr[0]); }
	else if (no == 1)	{ *dst = &(sprite_arr[12]); }

	return (EXIT_SUCCESS);
}