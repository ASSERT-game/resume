/***************************************************************************
 * FILENAME:    sprite_scoregoal.c
 * DESCRIPTION: Fetches the score goal sprite
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

SDLX_Sprite_Data *carve_scoregoal_sprite(void)
{
	size_t				i;
	SDL_Texture			*texture;
	SDLX_Sprite_Data	*result;

	result = SDL_calloc(2, sizeof(*result));
	texture = SDLX_LoadTexture(ASSETS"skullgoal.png");

	i = 0;
	result[i].texture = texture;
	result[i]._src = (SDL_Rect){0, 0, 32, 36};
	result[i].src = &(result[i]._src);
	result[i].cycle = 1;
	i++;

	result[i].texture = texture;
	result[i]._src = (SDL_Rect){0, 36, 32, 36};
	result[i].src = &(result[i]._src);
	result[i].cycle = 1;
	i++;

	return (result);
}

int		fetch_scoregoal_sprite(SDLX_Sprite_Data **dst, int no)
{
	static SDLX_Sprite_Data	*sprite_arr;

	if (sprite_arr == NULL)
		sprite_arr = carve_scoregoal_sprite();

	if (no == 0)		{ *dst = &(sprite_arr[0]); }
	if (no == 1)		{ *dst = &(sprite_arr[1]); }

	return (EXIT_SUCCESS);
}