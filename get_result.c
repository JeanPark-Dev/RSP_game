/*ENCE260 Assignment Part II
  Written by Jinyoung Park 15648768
  Rock_Scissor_Paper
  ---------------------------------- 
  File: game.c
  definition of type of symbols (rock, scissors, papers)
*/

#include "get_result.h"
#include "symbols.h"
#include "results.h"

#include "system.h"
#include "pacer.h"
#include "tinygl.h"

result_t result(symbol_t mine, symbol_t theirs) {
	if (mine == theirs) {
		return DRAW;
	} else {
		if (mine == PAPER) {
			if(theirs == SCISSORS){
				return LOSE;
			} 
			if (theirs == ROCK){
				return WIN;
			}
		} else if (mine == SCISSORS) {
			if (theirs == ROCK){
				return LOSE;
			}
			if (theirs == PAPER) {
				return WIN;
			}
		} else if (mine == ROCK) {
			if (theirs == PAPER){
				return LOSE;
			}
			if (theirs == SCISSORS){
				return WIN;
			}
		}
		return 0;
	}
}