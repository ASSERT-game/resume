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

typedef struct	s_heart
{
	t_player	*player;
	SDL_bool	collected;
}				t_heart;

void	init_heart_pickup(t_entity *pickup, int x, int y)
{
	t_heart	*heart;

	fetch_pickup_sprite(&(pickup->sprite.sprite_data), 0);
	pickup->sprite._dst = (SDL_Rect){x, y, 16, 16};
	pickup->sprite.dst = SDLX_NULL_SELF;

	pickup->world_x = x;
	pickup->world_y = y;
	SDL_Log("%p", pickup->sprite.sprite_data);


	SDL_memset(pickup->alloc, 0, sizeof(pickup->alloc));
	pickup->meta = &(pickup->alloc);
	heart = pickup->meta;
	heart->collected = SDL_FALSE;
}

void	heart_pickup_player(t_entity *pickup, t_player *player)
{
	t_heart	*heart;

	heart = pickup->meta;
	heart->player = player;
}

void	heart_pickup_update(t_entity *pickup, int world_x, int world_y)
{
	t_heart		*heart;
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
		heart_pickup_player(pickup, player);
		return ;
	}

	if ((dx * dx + dy * dy < 7 * 7) && heart->collected == SDL_FALSE)
	{
		player->health.value += 5;
		fetch_pickup_sprite(&(pickup->sprite.sprite_data), 1);
		pickup->sprite.current = -1;
		pickup->sprite.sort = 10000;
		heart->collected = SDL_TRUE;
	}

	pickup->sprite.current++;
	SDLX_RenderQueue_Add(NULL, &(pickup->sprite));
}