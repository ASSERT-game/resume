/***************************************************************************
 * FILENAME:    attack_ui.c
 * DESCRIPTION: File that handles the ui for the main attack.
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

void sword_attack_ui(t_main_attacks *attack, void *meta)
{
	fetch_attack_ui_sprite(&(attack->sprite.sprite_data), 1);
	attack->name = SDL_strdup("Sword");
	attack->sprite.dst = &(attack->sprite._dst);
	// attack->sprite._dst = (SDL_Rect){250, 190, 24, 24};
	(void)meta;
}

void spell_attack_ui(t_main_attacks *attack, void *meta)
{
	fetch_attack_ui_sprite(&(attack->sprite.sprite_data), 2);
	attack->name = SDL_strdup("Spell");
	attack->sprite.dst = &(attack->sprite._dst);
	// attack->sprite._dst = (SDL_Rect){250, 190, 24, 24};
	(void)meta;
}

void spear_attack_ui(t_main_attacks *attack, void *meta)
{
	fetch_attack_ui_sprite(&(attack->sprite.sprite_data), 3);
	attack->name = SDL_strdup("Spear");
	attack->sprite.dst = &(attack->sprite._dst);
	// attack->sprite._dst = (SDL_Rect){250, 190, 24, 24};
	(void)meta;
}

void	main_attack_ui_init(t_player *player)
{
	sword_attack_ui(&(player->main_attacks[0]), NULL);
	spell_attack_ui(&(player->main_attacks[1]), NULL);
	spear_attack_ui(&(player->main_attacks[2]), NULL);

	player->attack_curr = 0;
}

void	main_attack_ui_update(t_player *player)
{
	if (SDLX_GAME_PRESS(g_GameInput, g_GameInput_prev, num8))
	{
		SDL_Log("Weapon Left");
		player->attack_curr--;
		player->attack_curr += 3;
		player->attack_curr %= 3;
		while (player->main_attacks[player->attack_curr].name == NULL)
		{
			player->attack_curr += 3;
			player->attack_curr %= 3;

			player->attack_curr--;
		}
	}

	if (SDLX_GAME_PRESS(g_GameInput, g_GameInput_prev, num7))
	{
		SDL_Log("Weapon Right");
		player->attack_curr++;
		player->attack_curr += 3;
		player->attack_curr %= 3;
		while (player->main_attacks[player->attack_curr].name == NULL)
		{
			player->attack_curr += 3;
			player->attack_curr %= 3;

			player->attack_curr++;
		}
	}

	player->main_attacks[player->attack_curr].sprite._dst = (SDL_Rect){252, 189, 24, 24};
	SDLX_RenderQueue_Add(NULL, &(player->main_attacks[player->attack_curr].sprite));

	int	next;
	int	prev;

	if (player->attack_curr == 2)
	{
		next = 0;
		prev = 1;
	}
	else if (player->attack_curr == 0)
	{
		next = 1;
		prev = 2;
	}
	else
	{
		next = player->attack_curr + 1;
		prev = player->attack_curr - 1;
	}

	player->main_attacks[next].sprite._dst = (SDL_Rect){268, 184, 16, 16};
	SDLX_RenderQueue_Add(NULL, &(player->main_attacks[next].sprite));
	player->main_attacks[prev].sprite._dst = (SDL_Rect){240, 201, 16, 16};
	SDLX_RenderQueue_Add(NULL, &(player->main_attacks[prev].sprite));
}




void bomb_spec_ui(t_special *special, void *meta)
{
	fetch_attack_ui_sprite(&(special->sprite.sprite_data), 4);
	special->name = SDL_strdup("Bomb");
	special->sprite.dst = &(special->sprite._dst);
	// special->sprite._dst = (SDL_Rect){250, 190, 24, 24};
	(void)meta;
}

void fireball_spec_ui(t_special *special, void *meta)
{
	fetch_attack_ui_sprite(&(special->sprite.sprite_data), 5);
	special->name = SDL_strdup("Fireball");
	special->sprite.dst = &(special->sprite._dst);
	// special->sprite._dst = (SDL_Rect){250, 190, 24, 24};
	(void)meta;
}

void hook_spec_ui(t_special *special, void *meta)
{
	fetch_attack_ui_sprite(&(special->sprite.sprite_data), 6);
	special->name = SDL_strdup("Hook Shot");
	special->sprite.dst = &(special->sprite._dst);
	// special->sprite._dst = (SDL_Rect){250, 190, 24, 24};
	(void)meta;
}

void ice_spec_ui(t_special *special, void *meta)
{
	fetch_attack_ui_sprite(&(special->sprite.sprite_data), 7);
	special->name = SDL_strdup("Ice Arrow");
	special->sprite.dst = &(special->sprite._dst);
	// special->sprite._dst = (SDL_Rect){250, 190, 24, 24};
	(void)meta;
}

void	spec_ui_init(t_player *player)
{
	bomb_spec_ui(&(player->specials[0]), NULL);
	fireball_spec_ui(&(player->specials[1]), NULL);
	hook_spec_ui(&(player->specials[2]), NULL);
	ice_spec_ui(&(player->specials[3]), NULL);

	player->special_no = 4;
	player->special_curr = 0;
}

void	special_ui_update(t_player *player)
{
	int	prev;
	int	next;

	if (SDLX_GAME_PRESS(g_GameInput, g_GameInput_prev, num5))
	{
		SDL_Log("Special Left");
		player->special_curr--;
	}

	if (SDLX_GAME_PRESS(g_GameInput, g_GameInput_prev, num6))
	{
		SDL_Log("Special Right");
		player->special_curr++;
	}

	player->special_curr = (player->special_curr + player->special_no) % player->special_no;

	prev = player->special_curr + player->special_no - 1;
	next = prev + 2;

	prev %= player->special_no;
	next %= player->special_no;

	player->specials[player->special_curr].sprite._dst = (SDL_Rect){12, 29, 16, 16};
	SDLX_RenderQueue_Add(NULL, &(player->specials[player->special_curr].sprite));

	player->specials[prev].sprite._dst = (SDL_Rect){5,  23, 16, 16};
	player->specials[next].sprite._dst = (SDL_Rect){19, 38, 16, 16};
	if (player->special_no >= 3)
	{
		SDLX_RenderQueue_Add(NULL, &(player->specials[prev].sprite));

		SDLX_RenderQueue_Add(NULL, &(player->specials[next].sprite));
	}
	else if (player->special_no == 2)
	{
		SDLX_RenderQueue_Add(NULL, &(player->specials[next].sprite));
	}
}