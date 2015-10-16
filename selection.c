/*ENCE260 Assignment Part II
  Written by Jinyoung Park 15648768
  Rock_Scissor_Paper
  ----------------------------------
  File: selection.c
*/

#include "selection.h"
#include "navswitch.h"

#include "system.h"
#include "pacer.h"



//change the current symbol status of player and select
symbolType cSelection(symbolType my_symbol)
{
	int status = 0;

	if (my_symbol == ROCK)
	{
		status = 0;
	} else if (my_symbol == PAPER)
	{
		status = 1;
	} else if(my_symbol == SCISSORS)
	{
		status = 2;
	}


	if (navswitch_push_event_p (NAVSWITCH_WEST))
			status += 1;

	if (navswitch_push_event_p (NAVSWITCH_EAST))
	{
		if (status == 0)
		{
			status = 2;
		} else {
			status -= 1;
		}
	}

	status = status % 3;
	if (status == 0)
	{
		my_symbol = ROCK;
	}
	if (status == 1)
	{
		my_symbol = PAPER;
	}
	if (status == 2)
	{
		my_symbol = SCISSORS;
	}
	return my_symbol;
}
