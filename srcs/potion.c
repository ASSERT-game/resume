/***************************************************************************
 * FILENAME:    potion.c
 * DESCRIPTION: Functions for potions
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

void	potion_red(t_potion *potion)
{
	t_player *player;

	fetch_potion_sprite(&(potion->sprite.sprite_data), 0);
	potion->name = SDL_strdup("Red Potion");
	potion->sprite.dst = &(potion->sprite._dst);
	potion->sprite._dst = (SDL_Rect){297, 195, 8, 12};
	potion->sprite.sort = 1000;
	potion->isUsed = SDL_FALSE;

	player = g_SDLX_Context.meta1;
	potion->loc = &(player->health.value);
	potion->value = 20;
	potion->op = SDLX_AXM_ADD;
}

void	potion_blue(t_potion *potion)
{
	t_player *player;

	fetch_potion_sprite(&(potion->sprite.sprite_data), 1);
	potion->name = SDL_strdup("Blue Potion");
	potion->sprite.dst = &(potion->sprite._dst);
	potion->sprite._dst = (SDL_Rect){297, 195, 8, 12};
	potion->sprite.sort = 1000;
	potion->isUsed = SDL_FALSE;

	player = g_SDLX_Context.meta1;
	potion->loc = &(player->mana.value);
	potion->value = 30;
	potion->op = SDLX_AXM_ADD;
}

void	potion_green(t_potion *potion)
{
	t_player *player;

	fetch_potion_sprite(&(potion->sprite.sprite_data), 2);
	potion->name = SDL_strdup("Green Potion");
	potion->sprite.dst = &(potion->sprite._dst);
	potion->sprite._dst = (SDL_Rect){297, 195, 8, 12};
	potion->sprite.sort = 1000;
	potion->isUsed = SDL_FALSE;

	player = g_SDLX_Context.meta1;
	potion->loc = &(player->health.value);
	potion->value = 50;
	potion->op = SDLX_AXM_ADD;
}

void	potion_yellow(t_potion *potion)
{
	t_player *player;

	fetch_potion_sprite(&(potion->sprite.sprite_data), 3);
	potion->name = SDL_strdup("Yellow Potion");
	potion->sprite.dst = &(potion->sprite._dst);
	potion->sprite._dst = (SDL_Rect){297, 195, 8, 12};
	potion->sprite.sort = 1000;
	potion->isUsed = SDL_FALSE;

	player = g_SDLX_Context.meta1;
	potion->loc = &(player->health.value);
	potion->value = 100;
	potion->op = SDLX_AXM_ADD;
}

void	potion_init(t_potion **potion, size_t amount)
{
	t_potion	*res;

	res = SDL_calloc(amount + 1, sizeof(*res));

	potion_red(		&(res[0]));
	potion_blue(	&(res[1]));
	potion_red(		&(res[2]));
	potion_yellow(	&(res[3]));
	potion_yellow(	&(res[4]));
	potion_blue(	&(res[5]));
	potion_green(	&(res[6]));

	*potion = res;
}

void	potion_update(t_player *player)
{
	t_potion	*potion_curr;

	if (SDLX_GAME_PRESS(g_GameInput, g_GameInput_prev, num0) && player->potion_no > 1)
	{
		SDL_Log("Potion Left");
		player->potion_curr--;
		player->potion_curr += player->max_potion;
		player->potion_curr %= player->max_potion;
		while (player->potions[player->potion_curr].isUsed)
		{
			player->potion_curr--;
			player->potion_curr += player->max_potion;
			player->potion_curr %= player->max_potion;
		}
	}

	if (SDLX_GAME_PRESS(g_GameInput, g_GameInput_prev, num1) && player->potion_no > 1)
	{
		SDL_Log("Potion Right");
		player->potion_curr++;
		player->potion_curr += player->max_potion;
		player->potion_curr %= player->max_potion;
		while (player->potions[player->potion_curr].isUsed)
		{
			player->potion_curr++;
			player->potion_curr += player->max_potion;
			player->potion_curr %= player->max_potion;
		}
	}

	if (SDLX_GAME_PRESS(g_GameInput, g_GameInput_prev, num3) && player->potion_no > 0)
	{
		SDL_Log("Drinking Potion");
		potion_curr = &(player->potions[player->potion_curr]);
		SDLX_xlogic[potion_curr->op](potion_curr->loc, potion_curr->value);
		player->potions[player->potion_curr].isUsed = SDL_TRUE;
		player->potion_no--;

		while (player->potions[player->potion_curr].isUsed && player->potion_no > 1)
		{
			player->potion_curr++;

			player->potion_curr += player->max_potion;
			player->potion_curr %= player->max_potion;
		}
		player->potion_curr += player->max_potion;
		player->potion_curr %= player->max_potion;
	}

	// SDL_Log("This %d and %d", player->potion_curr, player->potion_no);
	if (player->potion_no > 0)
		SDLX_RenderQueue_Add(NULL, &(player->potions[player->potion_curr].sprite));

	SDLX_RenderQueue_Add(NULL, &(player->potion_hud));
}