/***************************************************************************
 * FILENAME:    player.c
 * DESCRIPTION: Handles the player loop
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 05Nov2021
***************************************************************************/

#include "main.h"

void	player_dash(int *dx, int *dy, int *state)
{
	int temp = 0;

	if (SDLX_GAME_PRESS(g_GameInput, g_GameInput_prev, A) && !(*state & STATE_AIM))
	{
		double angle = SDL_atan2(g_GameInput.GameInput.leftaxis.y, g_GameInput.GameInput.leftaxis.x);

		temp = (SDL_cos(angle) * 32);
		temp -= temp % 4;
		*dx += temp;
		temp = (SDL_sin(angle) * 32);
		temp -= temp % 4;
		*dy += temp;
	}
	(void)state;
}

void	player_aim(int *state)
{
	if (g_GameInput.GameInput.button_left_trigger)
	{
		*state = STATE_AIM;
	}
}

void	player_move(int *dx, int *dy, int *state)
{
	if (*state & STATE_AIM)
		return ;

	if (g_GameInput.GameInput.button_DPAD_LEFT)
		*dx -= PLAYER_SPEED;
	if (g_GameInput.GameInput.button_DPAD_RIGHT)
		*dx += PLAYER_SPEED;
	if (g_GameInput.GameInput.button_DPAD_UP)
		*dy -= PLAYER_SPEED;
	if (g_GameInput.GameInput.button_DPAD_DOWN)
		*dy += PLAYER_SPEED;
}


/*
** For aim targeting the function might need collidable data in order
** to increase the accuracy of the player and make the combat
** follow more closely the players intent.
*/
void	player_use_spec(int *state, int x, int y)
{
	static int	timer;
	static SDLX_Sprite	sprite;
	static SDL_Point	vel;

	if (sprite.sprite_data == NULL)
	{
		fetch_attack_ui_sprite(&(sprite.sprite_data), 7);
		sprite.dst = &(sprite._dst);
		sprite._dst.w = 16;
		sprite._dst.h = 16;
	}

	if (SDLX_GAME_PRESS(g_GameInput, g_GameInput_prev, B) && timer == 0)
	{
		SDL_Log("Fired Special");
		timer = 15;
		sprite._dst.x = x + 8;
		sprite._dst.y = y + 8;

		double angle = SDL_atan2(g_GameInput.GameInput.leftaxis.y, g_GameInput.GameInput.leftaxis.x);

		vel.x = (SDL_cos(angle) * 24);
		vel.x -= vel.x % 1;
		vel.y = (SDL_sin(angle) * 24);
		vel.y -= vel.y % 1;
	}

	if (timer > 0)
	{
		timer--;
		SDLX_RenderQueue_Add(NULL, &(sprite));
		sprite._dst.x += vel.x;
		sprite._dst.y += vel.y;
	}


	(void)state;
}