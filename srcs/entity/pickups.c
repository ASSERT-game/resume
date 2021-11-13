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
	t_player	*player;
	SDL_bool	collected;

	int			*to;
	int			op;
	int			value;

	SDLX_collision	collision;
}				t_pickup;

void	init_heart_pickup(t_entity *pickup, int x, int y)
{
	t_pickup	*heart;

	fetch_pickup_sprite(&(pickup->sprite.sprite_data), 0);
	pickup->sprite._dst = (SDL_Rect){x, y, 16, 16};
	pickup->sprite.dst = SDLX_NULL_SELF;

	pickup->world_x = x;
	pickup->world_y = y;

	SDL_memset(pickup->alloc, 0, sizeof(pickup->alloc));
	pickup->meta = &(pickup->alloc);
	heart = pickup->meta;
	heart->collected = SDL_FALSE;

	heart->op = SDLX_AXM_ADD;
	heart->value = -10;

	heart = pickup->meta;
	heart->player = g_SDLX_Context.meta1;
	heart->to = &(heart->player->health.value);

	SDL_assert(sizeof(pickup->alloc) >= sizeof(t_pickup));
}

SDL_bool	pot_collide(void *self, void *with, SDL_UNUSED void *data, SDL_UNUSED void *data2)
{
	SDL_bool		result;
	SDLX_collision	*hitbox;
	t_entity		*pickup;
	t_pickup		*heart;

	hitbox = with;
	pickup = self;
	result = SDL_FALSE;
	heart = pickup->meta;
	if (hitbox == &(heart->collision))
		return (result);

	SDL_SetRenderDrawColor(SDLX_GetDisplay()->renderer, 0, 255, 0, 255);
	SDL_RenderDrawRect(SDLX_GetDisplay()->renderer, &(hitbox->hitbox));
	SDL_RenderDrawRect(SDLX_GetDisplay()->renderer, &(heart->collision.hitbox));

	if (hitbox->type == C_MELEE)
	{
		if (SDL_HasIntersection(&(heart->collision.hitbox), &(hitbox->hitbox)) == SDL_TRUE)
		{
			SDL_Log("Pot Collides");
			result = SDL_TRUE;
		}
	}
	return (result);
}

void	*pot_react(void *self, void *with, SDL_UNUSED void *data, SDL_UNUSED void *data2)
{
	t_entity		*pickup;
	t_pickup		*heart;
	SDLX_collision	*hitbox;
	SDLX_collision	*self_hitbox;

	hitbox = with;
	self_hitbox = self;
	pickup = self;
	heart = pickup->meta;
	if (hitbox->type == C_MELEE)
	{
		SDL_Log("Pot Collides with Sword");
		heart->collected = SDL_TRUE;
		pickup->sprite.current = 6;
	}
	return (NULL);
}

void	heart_pickup_update(t_entity *pickup, int world_x, int world_y)
{
	t_pickup		*heart;
	t_player	*player;
	int			dx, dy;
	double		angle;

	heart = pickup->meta;
	player = heart->player;

	dx = pickup->world_x - (player->sprite._dst.x + world_x + 8);
	dy = pickup->world_y - (player->sprite._dst.y + world_y + 8);

	if (heart->collected == SDL_FALSE)
	{
		if (dx * dx + dy * dy < 64 * 64)
		{
			angle = SDL_atan2(dy, dx);
			pickup->world_x -= SDL_cos(angle) * 4;
			pickup->world_y -= SDL_sin(angle) * 4;
		}

		pickup->sprite._dst.x = pickup->world_x - world_x;
		pickup->sprite._dst.y = pickup->world_y - world_y;
		fill_priority(&(pickup->sprite));
		pickup->sprite.sort++;
	}
	else if (heart->collected == SDL_TRUE && pickup->sprite.current == 6)
	{
		init_heart_pickup(pickup, player->sprite._dst.x, player->sprite._dst.y);
		return ;
	}

	if ((dx * dx + dy * dy < 7 * 7) && heart->collected == SDL_FALSE)
	{
		SDLX_xlogic[heart->op](heart->to, heart->value);
		fetch_pickup_sprite(&(pickup->sprite.sprite_data), 3);
		pickup->sprite.current = -1;
		pickup->sprite.sort = 10000;
		heart->collected = SDL_TRUE;
	}

	pickup->sprite.current++;
	SDLX_RenderQueue_Add(NULL, &(pickup->sprite));

	heart->collision.hitbox_ptr = &(heart->collision.hitbox);
	heart->collision.hitbox = pickup->sprite._dst;

	heart->collision.detect = pot_collide;
	heart->collision.engage = pot_react;
	heart->collision.originator = pickup;

	SDLX_CollisionBucket_add(NULL, &(heart->collision));
}
