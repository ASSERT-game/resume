/***************************************************************************
 * FILENAME:    input.c
 * DESCRIPTION:  Has the keymapper.
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 31Oct2021
***************************************************************************/

#include "main.h"

SDLX_iMap	*resume_key_map(size_t *size)
{
	static SDLX_iMap	key_map[] =
	{
		(SDLX_iMap){&BMAP(button_START),	1, SDL_SCANCODE_SPACE},
		(SDLX_iMap){&BMAP(button_START),	1, SDL_SCANCODE_KP_ENTER},
		(SDLX_iMap){&BMAP(button_START),	1, SDL_SCANCODE_ESCAPE},

		(SDLX_iMap){&BMAP(button_num1),	1, SDL_SCANCODE_1},
		(SDLX_iMap){&BMAP(button_num2),	1, SDL_SCANCODE_2},
		(SDLX_iMap){&BMAP(button_num3),	1, SDL_SCANCODE_3},
		(SDLX_iMap){&BMAP(button_num4),	1, SDL_SCANCODE_4},
	};

	*size = sizeof(key_map) / sizeof(*key_map);
	return (&key_map[0]);
}

SDLX_iMap	*resume_pad_map(size_t *size)
{
	static SDLX_iMap	key_map[] =
	{
		(SDLX_iMap){&BMAP(button_num1),	1, SDL_CONTROLLER_BUTTON_DPAD_LEFT},
		(SDLX_iMap){&BMAP(button_num3),	1, SDL_CONTROLLER_BUTTON_DPAD_RIGHT},
		(SDLX_iMap){&BMAP(button_num2),	1, SDL_CONTROLLER_BUTTON_DPAD_UP},
		(SDLX_iMap){&BMAP(button_num4),	1, SDL_CONTROLLER_BUTTON_DPAD_DOWN},

		(SDLX_iMap){&BMAP(button_num1),	1, SDL_CONTROLLER_BUTTON_Y},
		(SDLX_iMap){&BMAP(button_num2),	1, SDL_CONTROLLER_BUTTON_X},
		(SDLX_iMap){&BMAP(button_num3),	1, SDL_CONTROLLER_BUTTON_B},
		(SDLX_iMap){&BMAP(button_num4),	1, SDL_CONTROLLER_BUTTON_A},

		(SDLX_iMap){&BMAP(button_primleft),	1, SDL_CONTROLLER_BUTTON_DPAD_LEFT},
		(SDLX_iMap){&BMAP(button_primleft),	1, SDL_CONTROLLER_BUTTON_DPAD_RIGHT},
		(SDLX_iMap){&BMAP(button_primleft),	1, SDL_CONTROLLER_BUTTON_DPAD_UP},
		(SDLX_iMap){&BMAP(button_primleft),	1, SDL_CONTROLLER_BUTTON_DPAD_DOWN},

		(SDLX_iMap){&BMAP(button_START),	1, SDL_CONTROLLER_BUTTON_START},
	};

	*size = sizeof(key_map) / sizeof(*key_map);
	return (&key_map[0]);
}