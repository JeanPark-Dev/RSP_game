/*ENCE260 Assignment Part II
  Written by Jinyoung Park 15648768
  Rock_Scissor_Paper
  ---------------------------------- 
  File: game.c
  definition of type of symbols (rock, scissors, papers)
*/

#ifndef GET_RESULT_H
#define GET_RESULT_H

#include "symbols.h"
#include "results.h"

result_t result(symbol_t mine, symbol_t theirs);

#endif