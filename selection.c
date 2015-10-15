/*ENCE260 Assignment Part II
  Written by Jinyoung Park 15648768
  Rock_Scissor_Paper
  ---------------------------------- 
  File: game.c
  definition of type of symbols (rock, scissors, papers)
*/

#include "selection.h"
#include "navswitch.h"

#include "system.h"
#include "pacer.h"




symbol_t cSelection(symbol_t my_symbol){
	int status = 0;

	if (my_symbol == ROCK){
		status = 0;
	} else if (my_symbol == PAPER){
		status = 1;
	} else if(my_symbol == SCISSORS){
		status = 2;
	}


	if (navswitch_push_event_p (NAVSWITCH_WEST))
			status += 1;

		if (navswitch_push_event_p (NAVSWITCH_EAST)) {
			if (status == 0) {
				status = 2;
			} else {
				status -= 1;
			}
		}

	status = status % 3;
		if (status == 0) {
			my_symbol = ROCK;
		}
		if (status == 1) {
			my_symbol = PAPER;
		}
		if (status == 2) {
			my_symbol = SCISSORS;
		}
	return my_symbol;
}