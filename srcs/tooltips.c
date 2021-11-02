/***************************************************************************
 * FILENAME:    tooltips.c
 * DESCRIPTION: Utility functions about tooltips.
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

void	*tooltip_update(SDLX_button *button, void *meta, size_t meta_length)
{

	if (g_GameInput.pad_last == SDL_TRUE)
		button->sprite_fn(&(button->sprite.sprite_data), 2);
	else
		button->sprite_fn(&(button->sprite.sprite_data), 1);

	(void)meta;
	(void)meta_length;

	if (button->isTriggered == SDL_TRUE)
	{
		SDLX_RenderQueue_Add(button->render_dst, &(button->sprite));
		button->sprite.current++;
	}

	return (NULL);
}

void	*tooltip_fade(SDLX_button *button, void *meta, size_t meta_length)
{
	if (button->isDisabled != SDL_TRUE)
	{
		SDLX_RenderQueue_Add(button->render_dst, &(button->sprite));
		button->sprite.current++;
	}

	if (button->sprite.current + 1 >= button->sprite.sprite_data->cycle)
	{
		button->isDisabled = SDL_TRUE;
	}


	(void)meta;
	(void)meta_length;
	return (NULL);
}

SDL_bool	tooltip_move_focus(SDLX_button *button, void *meta, size_t meta_length)
{
	int	*ticks;

	ticks = button->meta;

	if (*ticks > 27)
		button->isTriggered |= SDL_TRUE;

	if (g_GameInput.GameInput.button_DPAD_DOWN
		|| g_GameInput.GameInput.button_DPAD_UP
		|| g_GameInput.GameInput.button_DPAD_LEFT
		|| g_GameInput.GameInput.button_DPAD_RIGHT)
	{
		if (button->update_fn != tooltip_fade)
			button->sprite.current = 0;
		if (button->isTriggered == SDL_FALSE)
			button->isDisabled = SDL_TRUE;

		button->sprite_fn(&(button->sprite.sprite_data), 3);
		button->update_fn = tooltip_fade;
	}

	(void)meta;
	(void)meta_length;
	return (SDL_FALSE);
}