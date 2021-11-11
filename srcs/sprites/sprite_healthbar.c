/***************************************************************************
 * FILENAME:    sprite_healthbar.c
 * DESCRIPTION: Gets the healthbar sprite
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 10Nov2021
***************************************************************************/

#include "main.h"


SDLX_Sprite_Data *carve_bar_sprite(void)
{
	size_t				i;
	SDL_Texture			*texture;
	SDLX_Sprite_Data	*result;

	result = SDL_calloc(10, sizeof(*result));
	texture = SDLX_LoadTexture(ASSETS"health_bar.png");

	i = 0;
	/* The Start Bar */
	result[i].texture = texture;
	result[i]._src = (SDL_Rect){0, 0, 32, 32};
	result[i].src = &(result[i]._src);
	result[i].cycle = 1;
	i++;

	/* The Middle Bar */
	result[i].texture = texture;
	result[i]._src = (SDL_Rect){32, 0, 32, 32};
	result[i].src = &(result[i]._src);
	result[i].cycle = 1;
	i++;

	/* The End Bar */
	result[i].texture = texture;
	result[i]._src = (SDL_Rect){64, 0, 32, 32};
	result[i].src = &(result[i]._src);
	result[i].cycle = 1;
	i++;


	/* The Fill */
	result[i].texture = texture;
	result[i]._src = (SDL_Rect){0, 32, 32, 32};
	result[i].src = &(result[i]._src);
	result[i].cycle = 1;
	i++;

	/* The Back Fill */
	result[i].texture = texture;
	result[i]._src = (SDL_Rect){32, 32, 32, 32};
	result[i].src = &(result[i]._src);
	result[i].cycle = 1;
	i++;




	/* The Start Bar */
	result[i].texture = texture;
	result[i]._src = (SDL_Rect){0, 64, 32, 32};
	result[i].src = &(result[i]._src);
	result[i].cycle = 1;
	i++;

	/* The Middle Bar */
	result[i].texture = texture;
	result[i]._src = (SDL_Rect){32, 64, 32, 32};
	result[i].src = &(result[i]._src);
	result[i].cycle = 1;
	i++;

	/* The End Bar */
	result[i].texture = texture;
	result[i]._src = (SDL_Rect){64, 64, 16, 32};
	result[i].src = &(result[i]._src);
	result[i].cycle = 1;
	i++;


	/* The Fill */
	result[i].texture = texture;
	result[i]._src = (SDL_Rect){0, 32 + 64, 16, 32};
	result[i].src = &(result[i]._src);
	result[i].cycle = 1;
	i++;

	/* The Back Fill */
	result[i].texture = texture;
	result[i]._src = (SDL_Rect){16, 32 + 64, 16, 32};
	result[i].src = &(result[i]._src);
	result[i].cycle = 1;
	i++;

	return (result);
}

int		fetch_bar_sprite(SDLX_Sprite_Data **dst, int no)
{
	static SDLX_Sprite_Data	*sprite_arr;

	if (sprite_arr == NULL)
		sprite_arr = carve_bar_sprite();

	if (no == 0)		{ *dst = &(sprite_arr[0]); }
	else if (no == 1)	{ *dst = &(sprite_arr[1]); }
	else if (no == 2)	{ *dst = &(sprite_arr[2]); }
	else if (no == 3)	{ *dst = &(sprite_arr[3]); }
	else if (no == 4)	{ *dst = &(sprite_arr[4]); }

	else if (no == 5)	{ *dst = &(sprite_arr[5]); }
	else if (no == 6)	{ *dst = &(sprite_arr[6]); }
	else if (no == 7)	{ *dst = &(sprite_arr[7]); }
	else if (no == 8)	{ *dst = &(sprite_arr[8]); }
	else if (no == 9)	{ *dst = &(sprite_arr[9]); }

	return (EXIT_SUCCESS);
}