/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: home <home@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 02:31:10 by home              #+#    #+#             */
/*   Updated: 2021/11/05 23:16:34 by home             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

#ifdef EMCC
	#include <emscripten.h>
#endif

void	game_start(void *context)
{
	g_SDLX_Context.scene_meta = context;

	g_SDLX_Context.shouldQuit = SDL_FALSE;

	g_SDLX_Context.init_fn = world_init;
	// g_SDLX_Context.init_fn = main_menu_init;

	g_SDLX_Context.extra_num8 = TOOLTIP_ALL;

	// TTF_Init();
	// context->def_font = TTF_OpenFont(ASSETS"chary___.ttf", 150);
	// context->def_font_outline = TTF_OpenFont(ASSETS"chary___.ttf", 150);
	// TTF_SetFontOutline(context->def_font_outline, 3);

	g_GameInput.key_mapper.map_arr = resume_key_map(&(g_GameInput.key_mapper.amount));
	g_GameInput.pad_mapper.map_arr = resume_pad_map(&(g_GameInput.pad_mapper.amount));
}

int	main(void)
{
	int		ptr;

	SDLX_GetDisplay();
	game_start(&ptr);

	#ifdef EMCC
		emscripten_set_main_loop_arg(main_loop, (void *)&(context), 0, SDL_TRUE);
	#else
		while (g_SDLX_Context.shouldQuit == SDL_FALSE)
			SDLX_MainSceneLoop_Post(&(g_SDLX_Context));
	#endif

	return (EXIT_SUCCESS);
}
