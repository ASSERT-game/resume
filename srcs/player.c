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

void	player_init(t_player *player, int x, int y)
{
	player->sprite = SDLX_Sprite_Static(ASSETS"character.png");
	player->sprite.dst = SDLX_NULL_SELF;
	player->sprite._dst.w = 32;
	player->sprite._dst.h = 32;
	player->sprite._dst.x = x;
	player->sprite._dst.y = y;

	player->max_potion = 7;
	player->potion_no = 7;
	player->potion_curr = 0;

	g_SDLX_Context.meta1 = player;

	spec_ui_init(player);
	main_attack_ui_init(player);
	potion_init(&(player->potions), 7);
	crosshair_init(&(player->crosshair));

	player->potion_hud = SDLX_Sprite_Static(ASSETS"hud.png");
	player->potion_hud.sort = 10000;

	init_bar_system(&(player->health), 0, fetch_bar_sprite, 100, (SDL_Rect){5, -4, 32 * 3, 32}, 17, 3);
	init_bar_system(&(player->mana), 5, fetch_bar_sprite, 100, (SDL_Rect){13, 21, 80, 32}, 14, 3);
}

/*
** This needs to check every 'step' creating a bounding
** collision box, else the player may be able to move
** into certain small collision boxes.
*/

void	player_dash(int *dx, int *dy, int *state)
{
	int		temp;
	double	angle;

	if (SDLX_GAME_PRESS(g_GameInput, g_GameInput_prev, A))
	{
		angle = SDL_atan2(g_GameInput.GameInput.leftaxis.y, g_GameInput.GameInput.leftaxis.x);

		temp = (SDL_cos(angle) * 24);
		temp -= temp % 4;
		*dx += temp;
		temp = (SDL_sin(angle) * 24);
		temp -= temp % 4;
		*dy += temp;


		*state &= ~(STATE_AIM);
	}
}

SDL_bool	sword_collide(void *self, void *with, SDL_UNUSED void *data, SDL_UNUSED void *data2)
{
	SDLX_collision	*hitbox;
	SDLX_collision	*self_hitbox;

	hitbox = with;
	self_hitbox = self;
	if (with == self)
		return (SDL_FALSE);

	SDL_SetRenderDrawColor(SDLX_GetDisplay()->renderer, 0, 255, 0, 255);
	SDL_RenderDrawRect(SDLX_GetDisplay()->renderer, &(hitbox->hitbox));
	SDL_RenderDrawRect(SDLX_GetDisplay()->renderer, &(self_hitbox->hitbox));

	if (SDL_HasIntersection(&(hitbox->hitbox), &(self_hitbox->hitbox)) == SDL_TRUE)
	{
		SDL_Log("Collides");
	}
	return (SDL_FALSE);
}

void	player_attack(t_player *player)
{
	t_main_attacks	*attack;

	attack = &(player->main_attacks[player->attack_curr]);
	if (SDLX_GAME_PRESS(g_GameInput, g_GameInput_prev, X))
	{
		if (attack->current >= attack->cooldown)
		{
			SDL_Log("Player Attacking with %s", attack->name);
			attack->current = 0;
			attack->use.current = 0;

			attack->use.angle = player->last_facing_angle;

			attack->use.flip = SDL_FLIP_NONE;
			attack->use.angle += 360;
			attack->use.angle = (int)(attack->use.angle) % 360;
			if (90 < attack->use.angle && attack->use.angle < 270)
			{
				attack->use.angle -= 180;
				attack->use.flip = SDL_FLIP_HORIZONTAL;
			}
		}
	}

	// SDL_Log("(%d, %d)", g_GameInput.GameInput.leftaxis.x, g_GameInput.GameInput.leftaxis.y);
	if (SDL_abs(g_GameInput.GameInput.leftaxis.y) > 14000 || SDL_abs(g_GameInput.GameInput.leftaxis.x) > 14000)
	{
		// SDL_Log("Changed (%d, %d)", g_GameInput.GameInput.leftaxis.x, g_GameInput.GameInput.leftaxis.y);
		player->last_facing_angle = SDLX_Radian_to_Degree(SDL_atan2(g_GameInput.GameInput.leftaxis.y, g_GameInput.GameInput.leftaxis.x));
	}

	if (attack->current < attack->cooldown)
	{
		SDL_SetRenderDrawColor(SDLX_GetDisplay()->renderer, 255, 0, 0, 255);
		SDL_RenderDrawRect(SDLX_GetDisplay()->renderer, &(player->sprite._dst));

		player->attack.hitbox.originator = &(player->attack.hitbox);
		player->attack.hitbox.hitbox = player->sprite._dst;
		player->attack.hitbox.hitbox_ptr = &(player->attack.hitbox.hitbox);
		player->attack.hitbox.detect = sword_collide;
		player->attack.hitbox.type = C_MELEE;
		SDLX_CollisionBucket_add(NULL, &(player->attack.hitbox));
	}

	SDLX_RenderQueue_Add(NULL, &(attack->use));

	attack->use.current++;
	attack->use._dst.x = player->sprite._dst.x + 16 - 24;
	attack->use._dst.y = player->sprite._dst.y + 16 - 24;
	attack->use.sort = player->sprite.sort;

	attack->current++;
	/* If (curr) is equal to (cooldown + 1) undo the (curr++) */
	attack->current -= (attack->current / (attack->cooldown + 1));
}

void	crosshair_init(SDLX_Sprite *crosshair)
{
	*crosshair = SDLX_Sprite_Static(ASSETS"crosshair.png");

	crosshair->dst = &(crosshair->_dst);
	crosshair->_dst = (SDL_Rect){0, 0, 64, 64};
	crosshair->sort = 1000;
}

void	update_crosshair(t_player *player, int x, int y)
{

	if (SDL_abs(g_GameInput.GameInput.leftaxis.y) > 14000 || SDL_abs(g_GameInput.GameInput.leftaxis.x) > 14000)
	{
		player->crosshair.angle = -SDLX_Radian_to_Degree(SDL_atan2(-g_GameInput.GameInput.leftaxis.y, g_GameInput.GameInput.leftaxis.x)) + 45;
	}

	player->crosshair.dst->x = x + 16 - 32;
	player->crosshair.dst->y = y + 16 - 32;

	if (player->state & STATE_AIM)
		SDLX_RenderQueue_Add(NULL, &(player->crosshair));
}

void	player_aim(t_player *player)
{
	if (g_GameInput.GameInput.button_left_trigger)
		player->state = STATE_AIM;
}

void	player_move(int *dx, int *dy, int *state)
{
	if ((*state & STATE_AIM) || (*state & STATE_STUNNED))
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
	t_player			*player;

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

		// double angle = SDL_atan2(g_GameInput.GameInput.leftaxis.y, g_GameInput.GameInput.leftaxis.x);

		player = g_SDLX_Context.meta1;
		double angle = SDLX_Degree_to_Radian(player->crosshair.angle - 45);

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