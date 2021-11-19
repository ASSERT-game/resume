/***************************************************************************
 * FILENAME:    skullghost.c
 * DESCRIPTION: Functionality for the skull ghost entity
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 18Nov2021
***************************************************************************/

#include "main.h"

typedef struct	s_skullghost
{
	int			target_x;
	int			target_y;

	int			current;
	int			state;
}				t_skullghost;

void	new_ghost_target(SDL_Rect bounds, int *dst_x, int *dst_y)
{
	*dst_x = rand() % (bounds.w - bounds.x) + bounds.x;
	*dst_y = rand() % (bounds.h - bounds.y) + bounds.y;
}

void	skullghost_update(t_entity *self, int world_x, int world_y)
{
	t_skullghost	*skullghost;
	int				dx, dy;
	double			angle;

	skullghost = self->meta;
	if (skullghost->state == 0 && skullghost->current >= 60)
	{
		new_ghost_target((SDL_Rect){96, 64, 400, 288}, &(skullghost->target_x), &(skullghost->target_y));
		skullghost->current = 0;
		skullghost->state = 1;
	}

	dx = skullghost->target_x - self->world_x;
	dy = skullghost->target_y - self->world_y;
	if (skullghost->state == 1 && SDL_abs(dx) <= 16 && SDL_abs(dy) <= 16)
	{
		skullghost->state = 2;
		skullghost->current = 0;
	}

	if (skullghost->state == 2 && skullghost->current >= 20)
		skullghost->state = 0;

	if (skullghost->state == 1)
	{
		angle = SDL_atan2(dy, dx);
		dx = (SDL_cos(angle) * 2);
		dy = (SDL_sin(angle) * 2);

		self->world_x += dx;
		self->world_y += dy;

		angle = SDLX_Radian_to_Degree(angle);
		angle += 360;
		angle = (int)(angle) % 360;
		self->sprite.flip = SDL_FLIP_NONE;
		if (90 < angle && angle < 270)
			self->sprite.flip = SDL_FLIP_HORIZONTAL;
	}

	skullghost->current++;
	self->sprite.current++;
	world_align(&(self->sprite), self->world_x, self->world_y, world_x, world_y, 30);
	SDLX_RenderQueue_Add(NULL, &(self->sprite));
}

void	skullghost_init(t_entity *self, int x, int y)
{
	t_skullghost *skullghost;

	self->isActive = SDL_TRUE;
	fetch_ghost_sprite(&(self->sprite.sprite_data), 0);
	self->sprite.dst = SDLX_NULL_SELF;
	self->sprite._dst = (SDL_Rect){x, y, 16, 21};

	self->world_x = x;
	self->world_y = y;
	self->meta = self->alloc;
	self->update = skullghost_update;

	skullghost = self->meta;
	new_ghost_target((SDL_Rect){64, 48, 416, 320}, &(skullghost->target_x), &(skullghost->target_y));
	skullghost->current = 0;
	skullghost->state = 0;
}