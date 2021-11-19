/***************************************************************************
 * FILENAME:    pickups.c
 * DESCRIPTION: Deals with items that are picked up by the player.
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 11Nov2021
***************************************************************************/

#include "main.h"

typedef struct	s_pickup
{
	SDL_bool	collected;

	int			timer;

	int			*to;
	int			op;
	int			value;

	SDLX_collision	collision;
}				t_pickup;

SDL_bool	heart_detect_collide(void *self, void *with, SDL_UNUSED void *data, SDL_UNUSED void *data2)
{
	SDL_bool		result;
	SDLX_collision	*hitbox;
	t_entity		*pickup;
	t_pickup		*heart;

	hitbox = with;
	pickup = self;
	result = SDL_FALSE;
	heart = pickup->meta;

	// SDL_SetRenderDrawColor(SDLX_GetDisplay()->renderer, 0, 255, 0, 255);
	// SDL_RenderDrawRect(SDLX_GetDisplay()->renderer, &(hitbox->hitbox));
	// SDL_RenderDrawRect(SDLX_GetDisplay()->renderer, &(heart->collision.hitbox));
	if (hitbox->type == C_MELEE)
	{
		if (SDL_HasIntersection(&(heart->collision.hitbox), &(hitbox->hitbox)) == SDL_TRUE)
			result = SDL_TRUE;
	}
	return (result);
}

void	*heart_engage_collision(void *self, void *with, SDL_UNUSED void *data, SDL_UNUSED void *data2)
{
	t_entity		*pickup;
	t_player		*player;
	SDLX_collision	*hitbox;

	double			angle;
	int				x, y;

	hitbox = with;
	pickup = self;
	player = g_SDLX_Context.meta1;
	if (hitbox->type == C_MELEE)
	{
		x = pickup->world_x + 2;
		y = pickup->world_y + 2;
		angle = SDL_atan2(pickup->sprite._dst.y - player->sprite._dst.y - 8, pickup->sprite._dst.x - player->sprite._dst.x - 8);
		init_coin_pickup(spawn_entity_addr(g_SDLX_Context.meta2, ET_DROPS),  x + SDL_cos(angle) * 15, y + SDL_sin(angle) * 15);
		pickup->isActive = SDL_FALSE;
	}
	return (NULL);
}

void	init_heart_pickup(t_entity *pickup, int x, int y)
{
	t_pickup	*heart;

	pickup->sprite._dst = (SDL_Rect){x, y, 16, 16};
	pickup->sprite.dst = SDLX_NULL_SELF;

	pickup->world_x = x;
	pickup->world_y = y;

	pickup->update = heart_pickup_update;
	pickup->isActive = SDL_TRUE;

	pickup->meta = &(pickup->alloc);
	SDL_assert(sizeof(pickup->alloc) >= sizeof(t_pickup));
	heart = pickup->meta;

	heart->collision.hitbox_ptr = &(heart->collision.hitbox);
	heart->collision.detect = NULL;
	heart->collision.engage = heart_engage_collision;
	heart->collision.originator = pickup;
	heart->collected = SDL_FALSE;
}

void	init_red_heart_pickup(t_entity *pickup, int x, int y)
{
	t_pickup	*heart;
	t_player	*player;

	fetch_pickup_sprite(&(pickup->sprite.sprite_data), 2);
	init_heart_pickup(pickup, x, y);

	heart = pickup->meta;

	heart->value = 10;
	heart->op = SDLX_AXM_ADD;
	player = g_SDLX_Context.meta1;
	heart->to = &(player->health.value);
}

void	init_yellow_heart_pickup(t_entity *pickup, int x, int y)
{
	t_pickup	*heart;
	t_player	*player;

	fetch_pickup_sprite(&(pickup->sprite.sprite_data), 1);
	init_heart_pickup(pickup, x, y);

	heart = pickup->meta;

	heart->value = 1000;
	heart->op = SDLX_AXM_ADD;
	player = g_SDLX_Context.meta1;
	heart->to = &(player->health.value);
}

void	init_purple_heart_pickup(t_entity *pickup, int x, int y)
{
	t_pickup	*heart;
	t_player	*player;

	fetch_pickup_sprite(&(pickup->sprite.sprite_data), 0);
	init_heart_pickup(pickup, x, y);

	heart = pickup->meta;

	heart->value = -20;
	heart->op = SDLX_AXM_ADD;
	player = g_SDLX_Context.meta1;
	heart->to = &(player->health.value);
	heart->collision.detect = heart_detect_collide;
}

void	init_coin_pickup(t_entity *pickup, int x, int y)
{
	t_pickup	*potion;
	t_player	*player;

	fetch_pickup_sprite(&(pickup->sprite.sprite_data), 4);
	pickup->sprite._dst = (SDL_Rect){x, y, 12, 12};
	pickup->sprite.dst = SDLX_NULL_SELF;

	pickup->world_x = x;
	pickup->world_y = y;

	pickup->isActive = SDL_TRUE;
	pickup->update = coin_pickup_update;

	pickup->meta = &(pickup->alloc);
	SDL_assert(sizeof(pickup->alloc) >= sizeof(t_pickup));
	potion = pickup->meta;

	potion->value = 1;
	potion->op = SDLX_AXM_ADD;
	potion->collected = SDL_FALSE;
	player = g_SDLX_Context.meta1;
	potion->to = &(player->coins);

	potion->timer = 0;
}

void	heart_pickup_update(t_entity *pickup, int world_x, int world_y)
{
	t_pickup	*heart;
	t_player	*player;
	int			dx, dy;

	heart = pickup->meta;

	player = g_SDLX_Context.meta1;
	dx = pickup->world_x - (player->sprite._dst.x + world_x + 8);
	dy = pickup->world_y - (player->sprite._dst.y + world_y + 8);
	radial_attract(dx, dy, 48, 3, &(pickup->world_x), &(pickup->world_y));
	world_align(&(pickup->sprite), pickup->world_x, pickup->world_y, world_x, world_y, 1);

	if ((dx * dx + dy * dy < 7 * 7))
	{
		SDLX_xlogic[heart->op](heart->to, heart->value);

		fetch_pickup_sprite(&(pickup->sprite.sprite_data), 3);
		pickup->sprite.current = -1;
		pickup->sprite.sort = 10000;
		pickup->update = particle_pickup_update;
	}

	pickup->sprite.current++;
	SDLX_RenderQueue_Add(NULL, &(pickup->sprite));
	heart->collision.hitbox = pickup->sprite._dst;
	SDLX_CollisionBucket_add(NULL, &(heart->collision));
}

void	coin_pickup_update(t_entity *pickup, int world_x, int world_y)
{
	t_pickup	*coin;
	t_player	*player;
	int			dx, dy;

	coin = pickup->meta;

	player = g_SDLX_Context.meta1;
	dx = pickup->world_x - (player->sprite._dst.x + world_x + 8);
	dy = pickup->world_y - (player->sprite._dst.y + world_y + 8);
	if (coin->timer >= 10)
		radial_attract(dx, dy, 64, 4, &(pickup->world_x), &(pickup->world_y));
	world_align(&(pickup->sprite), pickup->world_x, pickup->world_y, world_x, world_y, 1);

	if ((dx * dx + dy * dy < 7 * 7) && coin->timer >= 3)
	{
		SDLX_xlogic[coin->op](coin->to, coin->value);

		fetch_pickup_sprite(&(pickup->sprite.sprite_data), 3);
		pickup->sprite.current = -1;
		pickup->sprite.sort = 10000;
		pickup->update = particle_pickup_update;
	}

	coin->timer++;
	pickup->sprite.current++;
	SDLX_RenderQueue_Add(NULL, &(pickup->sprite));
}

void	particle_pickup_update(t_entity *pickup, SDL_UNUSED int world_x, SDL_UNUSED int world_y)
{
	if (pickup->sprite.current + 1 >= pickup->sprite.sprite_data->cycle)
		pickup->isActive = SDL_FALSE;
	else
	{
		SDLX_RenderQueue_Add(NULL, &(pickup->sprite));
		pickup->sprite.current++;
	}

}