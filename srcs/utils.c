/***************************************************************************
 * FILENAME:    utils.c
 * DESCRIPTION: Utility Functions.
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

uint32_t	lerp32(double percent, uint32_t start, uint32_t end)
{
	uint32_t result;

	result = ((end - start) * percent);
	return (result);
}