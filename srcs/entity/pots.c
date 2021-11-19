/***************************************************************************
 * FILENAME:    pots.c
 * DESCRIPTION: Creates a pot entity.
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

typedef struct	s_pickup
{
	SDL_bool	collected;
	int			state;

	int			timer;

	int			*to;
	int			op;
	int			value;

	SDLX_collision	collision;
}				t_pickup;

SDL_bool	pot_detect_collide(void *self, void *with, SDL_UNUSED void *data, SDL_UNUSED void *data2)
{
	SDL_bool		result;
	SDLX_collision	*hitbox;
	t_entity		*pickup;
	t_pickup		*pot;

	hitbox = with;
	pickup = self;
	result = SDL_FALSE;
	pot = pickup->meta;

	// SDL_SetRenderDrawColor(SDLX_GetDisplay()->renderer, 0, 255, 0, 255);
	// SDL_RenderDrawRect(SDLX_GetDisplay()->renderer, &(hitbox->hitbox));
	// SDL_RenderDrawRect(SDLX_GetDisplay()->renderer, &(pot->collision.hitbox));
	if (hitbox->type == C_MELEE)
	{
		if (SDL_HasIntersection(&(pot->collision.hitbox), &(hitbox->hitbox)) == SDL_TRUE)
			result = SDL_TRUE;
	}
	return (result);
}

void	*pot_engage_collision(void *self, void *with, SDL_UNUSED void *data, SDL_UNUSED void *data2)
{
	t_entity		*pickup;
	t_pickup		*pot;
	t_player		*player;
	SDLX_collision	*hitbox;

	double			angle;
	int				x, y;

	hitbox = with;
	pickup = self;
	pot = pickup->meta;
	player = g_SDLX_Context.meta1;
	if (hitbox->type == C_MELEE)
	{
		x = pickup->world_x + 2;
		y = pickup->world_y + 2;
		angle = SDL_atan2(pickup->sprite._dst.y - player->sprite._dst.y - 8, pickup->sprite._dst.x - player->sprite._dst.x - 8);
		init_red_heart_pickup(spawn_entity_addr(g_SDLX_Context.meta2, ET_DROPS),  x + SDL_cos(angle) * 25, y + SDL_sin(angle) * 25);
		init_coin_pickup(spawn_entity_addr(g_SDLX_Context.meta2, ET_DROPS),  x + SDL_cos(angle) * 10, y + SDL_sin(angle) * 25);
		init_coin_pickup(spawn_entity_addr(g_SDLX_Context.meta2, ET_DROPS),  x + SDL_cos(angle) * 25, y + SDL_sin(angle) * 10);
		fetch_pot_sprite(&(pickup->sprite.sprite_data), 1);
		pot->timer = 0;
		pot->collected = SDL_TRUE;
		pot->state = 1;
	}
	return (NULL);
}

void	pot_init(t_entity *pot, int x, int y, SDL_Surface *collision_map)
{
	t_pickup	*pot_meta;

	// pot->sprite = SDLX_Sprite_Static(ASSETS"pot.png");
	fetch_pot_sprite(&(pot->sprite.sprite_data), 2);
	pot->sprite.dst = SDLX_NULL_SELF;
	pot->sprite._dst = (SDL_Rect){x, y, 16, 16};

	pot->world_x = x;
	pot->world_y = y;

	pot->isActive = SDL_TRUE;
	pot->update = pot_update;

	pot->meta = &(pot->alloc);
	pot_meta = pot->meta;

	pot_meta->collision.hitbox_ptr = &(pot_meta->collision.hitbox);

	pot_meta->collision.detect = pot_detect_collide;
	pot_meta->collision.engage = pot_engage_collision;
	pot_meta->collision.originator = pot;

	new_static_sprite(&(pot->sprite), 1, 1, 1, 1, 1, 1, collision_map);

	SDL_assert(sizeof(pot->alloc) >= sizeof(t_pickup));
}

void	pot_update(t_entity *pot, int world_x, int world_y)
{
	t_pickup	*pot_meta;

	world_align(&(pot->sprite), pot->world_x, pot->world_y, world_x, world_y, 0);

	pot_meta = pot->meta;
	if (pot_meta->state == 1 && pot_meta->timer > 200)
	{
		fetch_pot_sprite(&(pot->sprite.sprite_data), 4);
		pot->sprite.current = 0;
		pot_meta->state = 2;
	}

	if (pot->sprite.current == 5 && pot_meta->state == 2)
	{
		fetch_pot_sprite(&(pot->sprite.sprite_data), 2);
		pot_meta->collected = SDL_FALSE;
		pot_meta->state = 2;
	}

	pot_meta->timer++;
	pot->sprite.current++;
	SDLX_RenderQueue_Add(NULL, &(pot->sprite));
	pot_meta->collision.hitbox = pot->sprite._dst;

	if (pot_meta->collected == SDL_FALSE)
		SDLX_CollisionBucket_add(NULL, &(pot_meta->collision));
}
