/***************************************************************************
 * FILENAME:    scoregrave.c
 * DESCRIPTION: The scoregrave entity
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 17Nov2021
***************************************************************************/

#include "main.h"

typedef struct	s_scoregrave
{
	int			which;
	void		*(gravescore[4]);
}				t_scoregrave;

void	null_update(t_entity *self, int world_x, int world_y)
{
	(void)self;
	(void)world_x;
	(void)world_y;
}

void	update_grave(t_entity *self, int world_x, int world_y)
{
	fetch_scoregoal_sprite(&(self->sprite.sprite_data), 0);
	world_align(&(self->sprite), self->world_x, self->world_y, world_x, world_y, 0);
	SDLX_RenderQueue_Add(NULL, &(self->sprite));
}

void	score_grave_update(t_entity *self, int world_x, int world_y)
{
	t_scoregrave	*scoregrave;
	t_entity		*active_grave;

	scoregrave = self->meta;
	update_grave(scoregrave->gravescore[0], world_x, world_y);
	update_grave(scoregrave->gravescore[1], world_x, world_y);
	update_grave(scoregrave->gravescore[2], world_x, world_y);
	update_grave(scoregrave->gravescore[3], world_x, world_y);

	if (g_SDLX_Context.ticks_num2 % 100 == 0)
	{
		scoregrave->which++;
		scoregrave->which %= 4;
	}

	active_grave = scoregrave->gravescore[scoregrave->which];
	fetch_scoregoal_sprite(&(active_grave->sprite.sprite_data), 1);

	(void)world_x;
	(void)world_y;
}

void	grave_init(void *ptr, int x, int y)
{
	t_entity *grave;

	grave = ptr;
	grave->isActive = SDL_TRUE;
	grave->update = null_update;

	grave->world_x = x;
	grave->world_y = y;

	fetch_scoregoal_sprite(&(grave->sprite.sprite_data), 0);
	grave->sprite.dst = SDLX_NULL_SELF;
	grave->sprite._dst.w = 32;
	grave->sprite._dst.h = 36;
}

void	scoregrave_init(t_entity *grave_m, int world_x, int world_y)
{
	t_scoregrave	*graves;

	grave_m->isActive = SDL_TRUE;
	grave_m->update = score_grave_update;
	grave_m->world_x = world_x;
	grave_m->world_y = world_y;
	grave_m->meta = grave_m->alloc;

	graves = grave_m->meta;
	graves->which = 2;
	graves->gravescore[0] = spawn_entity_addr(g_SDLX_Context.meta2, ET_ENVIRONMENT);
	grave_init(graves->gravescore[0], 80, 64);
	graves->gravescore[1] = spawn_entity_addr(g_SDLX_Context.meta2, ET_ENVIRONMENT);
	grave_init(graves->gravescore[1], 384, 64);
	graves->gravescore[2] = spawn_entity_addr(g_SDLX_Context.meta2, ET_ENVIRONMENT);
	grave_init(graves->gravescore[2], 384, 288);
	graves->gravescore[3] = spawn_entity_addr(g_SDLX_Context.meta2, ET_ENVIRONMENT);
	grave_init(graves->gravescore[3], 80, 288);

	SDL_assert(sizeof(grave_m->alloc) >= sizeof(t_scoregrave));
}