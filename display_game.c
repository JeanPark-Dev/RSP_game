/*ENCE260 Assignment Part II
  Written by Jinyoung Park 15648768
  Rock_Scissor_Paper
  ---------------------------------- 
  File: game.c
  definition of type of symbols (rock, scissors, papers)
*/

#include "system.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "pacer.h"

#include "display_game.h"
#include "symbols.h"

void display_character (symbol_t character)
{
    char buffer[2];

    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}