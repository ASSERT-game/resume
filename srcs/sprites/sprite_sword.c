/***************************************************************************
 * FILENAME:    sprite_sword.c
 * DESCRIPTION: Fetches the sword sprite.
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 13Nov2021
***************************************************************************/

#include "main.h"

SDLX_Sprite_Data *carve_sword_sprite(void)
{
	size_t				i;
	SDL_Texture			*texture;
	SDLX_Sprite_Data	*result;

	result = SDL_calloc(8, sizeof(*result));
	texture = SDLX_LoadTexture(ASSETS"sword_attack.png");

	i = 0;
	while (i < 6)
	{
		result[i].texture = texture;
		result[i]._src = (SDL_Rect){i * 48, 0, 48, 48};
		result[i].src = &(result[i]._src);
		result[i].cycle = 6;

		i++;
	}

	result[i - 1].skip = 5;
	return (result);
}

int		fetch_sword_sprite(SDLX_Sprite_Data **dst, int no)
{
	static SDLX_Sprite_Data	*sprite_arr;

	if (sprite_arr == NULL)
		sprite_arr = carve_sword_sprite();

	if (no == 0)		{ *dst = &(sprite_arr[0]); }

	return (EXIT_SUCCESS);
}