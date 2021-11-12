/***************************************************************************
 * FILENAME:    SDLX_dynamic_logic.c
 * DESCRIPTION: Decalres the functions used to allow dynamic logic.
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 12Nov2021
***************************************************************************/

#include "SDLX.h"

SDLX_dynamic_logic_fn	*SDLX_dlogic_table[] =
{
	SDLX_dynamic_NOP,
	SDLX_dynamic_EQL,
	SDLX_dynamic_ADD,
	SDLX_dynamic_SUB,
	SDLX_dynamic_MUL,
	SDLX_dynamic_DIV,
	SDLX_dynamic_MOD,
	SDLX_dynamic_XOR,
	SDLX_dynamic_AND,
	SDLX_dynamic_OR,
	SDLX_dynamic_LS,
	SDLX_dynamic_RS,
};

void	SDLX_dynamic_NOP(SDL_UNUSED int *loc, SDL_UNUSED int val){	return ; }
void	SDLX_dynamic_EQL(int *loc, int val){	(*loc)   = val; }
void	SDLX_dynamic_ADD(int *loc, int val){	(*loc)  += val; }
void	SDLX_dynamic_SUB(int *loc, int val){	(*loc)  -= val; }
void	SDLX_dynamic_MUL(int *loc, int val){	(*loc)  *= val; }
void	SDLX_dynamic_DIV(int *loc, int val){	(*loc)  /= val; }
void	SDLX_dynamic_MOD(int *loc, int val){	(*loc)  %= val; }
void	SDLX_dynamic_XOR(int *loc, int val){	(*loc)  ^= val; }
void	SDLX_dynamic_AND(int *loc, int val){	(*loc)  &= val; }
void	SDLX_dynamic_OR(int *loc, int val){		(*loc)  |= val; }
void	SDLX_dynamic_LS(int *loc, int val){		(*loc) <<= val; }
void	SDLX_dynamic_RS(int *loc, int val){		(*loc) >>= val; }

void	SDLX_load_dynamic_logic(void)
{
	SDL_assert(SDLX_dlogic_table[SDLX_DYNAMIC_NOP] == SDLX_dynamic_NOP);
	SDL_assert(SDLX_dlogic_table[SDLX_DYNAMIC_EQL] == SDLX_dynamic_EQL);
	SDL_assert(SDLX_dlogic_table[SDLX_DYNAMIC_ADD] == SDLX_dynamic_ADD);
	SDL_assert(SDLX_dlogic_table[SDLX_DYNAMIC_SUB] == SDLX_dynamic_SUB);
	SDL_assert(SDLX_dlogic_table[SDLX_DYNAMIC_MUL] == SDLX_dynamic_MUL);
	SDL_assert(SDLX_dlogic_table[SDLX_DYNAMIC_DIV] == SDLX_dynamic_DIV);
	SDL_assert(SDLX_dlogic_table[SDLX_DYNAMIC_MOD] == SDLX_dynamic_MOD);
	SDL_assert(SDLX_dlogic_table[SDLX_DYNAMIC_XOR] == SDLX_dynamic_XOR);
	SDL_assert(SDLX_dlogic_table[SDLX_DYNAMIC_AND] == SDLX_dynamic_AND);
	SDL_assert(SDLX_dlogic_table[SDLX_DYNAMIC_OR]  == SDLX_dynamic_OR);
	SDL_assert(SDLX_dlogic_table[SDLX_DYNAMIC_SHIFT_LEFT]  == SDLX_dynamic_LS);
	SDL_assert(SDLX_dlogic_table[SDLX_DYNAMIC_SHIFT_RIGHT]  == SDLX_dynamic_RS);

	SDL_Log("Dynamic Logic Table Loaded");
}