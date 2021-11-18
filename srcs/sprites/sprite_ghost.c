/***************************************************************************
 * FILENAME:    sprite_ghost.c
 * DESCRIPTION: Fetches the sprite data for the ghost
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

SDLX_Sprite_Data *carve_ghost_sprite(void)
{
	size_t				i;
	SDL_Texture			*texture;
	SDLX_Sprite_Data	*result;

	result = SDL_calloc(12, sizeof(*result));
	texture = SDLX_LoadTexture(ASSETS"ghost.png");

	i = 0;
	while (i < 6)
	{
		result[i].texture = texture;
		result[i]._src = (SDL_Rect){i * 16, 0, 16, 21};
		result[i].src = &(result[i]._src);
		result[i].cycle = 6;

		i++;
	}

	while (i < 12)
	{
		result[i].texture = texture;
		result[i]._src = (SDL_Rect){(i - 6) * 16, 0, 16, 21};
		result[i].src = &(result[i]._src);
		result[i].cycle = 6;

		i++;
	}
	return (result);
}

int		fetch_ghost_sprite(SDLX_Sprite_Data **dst, int no)
{
	static SDLX_Sprite_Data	*sprite_arr;

	if (sprite_arr == NULL)
		sprite_arr = carve_ghost_sprite();

	if (no == 0)		{ *dst = &(sprite_arr[0]); }
	if (no == 1)		{ *dst = &(sprite_arr[6]); }

	return (EXIT_SUCCESS);
}