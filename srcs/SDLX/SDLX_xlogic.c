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

SDLX_dynamic_logic_fn	*SDLX_xlogic[] =
{
	SDLX_axm_NOP,
	SDLX_axm_EQL,
	SDLX_axm_ADD,
	SDLX_axm_SUB,
	SDLX_axm_MUL,
	SDLX_axm_DIV,
	SDLX_axm_MOD,
	SDLX_axm_XOR,
	SDLX_axm_AND,
	SDLX_axm_OR,
	SDLX_axm_LS,
	SDLX_axm_RS,
};

void	SDLX_axm_NOP(SDL_UNUSED int *loc, SDL_UNUSED int val){	return ; }
void	SDLX_axm_EQL(int *loc, int val){	(*loc)   = val; }
void	SDLX_axm_ADD(int *loc, int val){	(*loc)  += val; }
void	SDLX_axm_SUB(int *loc, int val){	(*loc)  -= val; }
void	SDLX_axm_MUL(int *loc, int val){	(*loc)  *= val; }
void	SDLX_axm_DIV(int *loc, int val){	(*loc)  /= val; }
void	SDLX_axm_MOD(int *loc, int val){	(*loc)  %= val; }
void	SDLX_axm_XOR(int *loc, int val){	(*loc)  ^= val; }
void	SDLX_axm_AND(int *loc, int val){	(*loc)  &= val; }
void	SDLX_axm_OR(int *loc, int val){		(*loc)  |= val; }
void	SDLX_axm_LS(int *loc, int val){		(*loc) <<= val; }
void	SDLX_axm_RS(int *loc, int val){		(*loc) >>= val; }

void	SDLX_load_xlogic(void)
{
	SDL_assert(SDLX_xlogic[SDLX_AXM_NOP]			== SDLX_axm_NOP);
	SDL_assert(SDLX_xlogic[SDLX_AXM_EQL]			== SDLX_axm_EQL);
	SDL_assert(SDLX_xlogic[SDLX_AXM_ADD]			== SDLX_axm_ADD);
	SDL_assert(SDLX_xlogic[SDLX_AXM_SUB]			== SDLX_axm_SUB);
	SDL_assert(SDLX_xlogic[SDLX_AXM_MUL]			== SDLX_axm_MUL);
	SDL_assert(SDLX_xlogic[SDLX_AXM_DIV]			== SDLX_axm_DIV);
	SDL_assert(SDLX_xlogic[SDLX_AXM_MOD]			== SDLX_axm_MOD);
	SDL_assert(SDLX_xlogic[SDLX_AXM_XOR]			== SDLX_axm_XOR);
	SDL_assert(SDLX_xlogic[SDLX_AXM_AND]			== SDLX_axm_AND);
	SDL_assert(SDLX_xlogic[SDLX_AXM_OR]				== SDLX_axm_OR);
	SDL_assert(SDLX_xlogic[SDLX_AXM_SHIFT_LEFT]		== SDLX_axm_LS);
	SDL_assert(SDLX_xlogic[SDLX_AXM_SHIFT_RIGHT]	== SDLX_axm_RS);

	SDL_Log("Dynamic Logic Table Loaded");
}