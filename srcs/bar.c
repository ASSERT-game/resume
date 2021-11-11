/***************************************************************************
 * FILENAME:    bar.c
 * DESCRIPTION: General Function that handles bar systems.
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

void	resize_healthbar(SDLX_Sprite *fill, SDLX_Sprite *back_fill, int *current, int out_of, SDL_Rect bar)
{
	if ((*current) > out_of)
		(*current) = out_of;

	fill->_dst.w = lerp32(((double)(*current)) / out_of, bar.x, bar.x + bar.w);

	if (back_fill->_dst.w > fill->_dst.w)
		back_fill->_dst.w--;
	else if (back_fill->_dst.w < fill->_dst.w)
		back_fill->_dst.w = fill->_dst.w;

	(void)bar;
}

void	increase_bar_system(t_bar *bar, int amount, int sprite_amount, SDL_bool animate)
{
	int		total_width;

	bar->desired_pos.w += sprite_amount;

	total_width = bar->middle_extender.sprite_data->_src.w;

	bar->middle_extender._dst.w = (bar->desired_pos.w - bar->start.sprite_data->_src.w - bar->end.sprite_data->_src.w);

	bar->middle_extender._dst.x = bar->start._dst.x + bar->start._dst.w;
	bar->end._dst.x = bar->middle_extender._dst.x + bar->middle_extender._dst.w;

	bar->middle_extender._dst.y = bar->desired_pos.y;

	bar->fill._dst.y = bar->desired_pos.y;
	bar->back_fill._dst.y = bar->desired_pos.y;

	bar->max_value += amount;

	if (animate == SDL_TRUE)
	{
		bar->start.current += 1;
		bar->middle_extender.current += 1;
		bar->end.current += 1;
	}
}

void	init_bar_system(t_bar *bar, int start_no, int (*sprite_fn)(SDLX_Sprite_Data **, int), int max, SDL_Rect desired_pos, int offset_left, int offset_right)
{
	int		total_width;
	double	width_scale;
	double	height_scale;

	bar->value = max;
	bar->prev_value = max;

	bar->offset_left = offset_left;
	bar->offset_right = offset_right;
	bar->desired_pos = desired_pos;
	sprite_fn(&(bar->start.sprite_data), start_no);
	sprite_fn(&(bar->middle_extender.sprite_data), start_no + 1);
	sprite_fn(&(bar->end.sprite_data), start_no + 2);

	sprite_fn(&(bar->fill.sprite_data), start_no + 3);
	sprite_fn(&(bar->back_fill.sprite_data), start_no + 4);


	bar->start.dst = SDLX_NULL_SELF;
	bar->middle_extender.dst = SDLX_NULL_SELF;
	bar->end.dst = SDLX_NULL_SELF;
	bar->fill.dst = SDLX_NULL_SELF;
	bar->back_fill.dst = SDLX_NULL_SELF;

	bar->start.sort = 990;
	bar->middle_extender.sort = 990;
	bar->end.sort = 990;

	bar->fill.sort = 992;
	bar->back_fill.sort = 991;

	total_width = bar->start.sprite_data->_src.w + bar->middle_extender.sprite_data->_src.w + bar->middle_extender.sprite_data->_src.w;
	// SDL_assert(total_width <= bar->desired_pos.w);

	width_scale = (double)bar->desired_pos.w / (double)total_width;
	height_scale = (double)bar->desired_pos.h / (double)bar->start.sprite_data->_src.h;

	bar->start._dst.x = bar->desired_pos.x;
	bar->start._dst.y = bar->desired_pos.y;
	bar->start._dst.h = bar->start.sprite_data->_src.h * height_scale;
	bar->start._dst.w = bar->start.sprite_data->_src.w * width_scale;

	bar->end._dst.y = bar->desired_pos.y;
	bar->end._dst.h = bar->end.sprite_data->_src.h * height_scale;
	bar->end._dst.w = bar->end.sprite_data->_src.w * width_scale;


	bar->fill._dst.h = bar->desired_pos.h * height_scale;
	bar->fill._dst.x = (bar->desired_pos.x + bar->offset_left);
	bar->back_fill._dst.h = bar->desired_pos.h * height_scale;
	bar->back_fill._dst.x = (bar->desired_pos.x + bar->offset_left);

	bar->middle_extender._dst.h = bar->middle_extender.sprite_data->_src.h * height_scale;

	bar->desired_pos.w = 0;

	SDL_Rect fill_size;

	increase_bar_system(bar, max, desired_pos.w, SDL_FALSE);
	fill_size = bar->desired_pos;
	fill_size.x += bar->offset_left;
	fill_size.w -= (bar->offset_left + bar->offset_right);
	resize_healthbar(&(bar->fill), &(bar->back_fill), &(bar->value), bar->max_value, fill_size);
}

void	bar_system_update(t_bar *bar)
{
	SDL_Rect fill_size;

	fill_size = bar->desired_pos;
	fill_size.x += bar->offset_left;
	fill_size.w -= (bar->offset_left + bar->offset_right);
	resize_healthbar(&(bar->fill), &(bar->back_fill), &(bar->value), bar->max_value, fill_size);

	SDLX_RenderQueue_Add(NULL, &(bar->start));
	SDLX_RenderQueue_Add(NULL, &(bar->middle_extender));
	SDLX_RenderQueue_Add(NULL, &(bar->end));

	SDLX_RenderQueue_Add(NULL, &(bar->fill));
	SDLX_RenderQueue_Add(NULL, &(bar->back_fill));
}