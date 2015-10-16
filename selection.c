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
<<<<<<< HEAD
symbolType cSelection(symbolType my_symbol)
=======
symbolType cSelection(symbolType mySym)
>>>>>>> 4226c591c4568aa795d8315876156f4d5c847a37
{
	int status = 0;

	if (mySym == ROCK)
	{
		status = 0;
	} else if (mySym == PAPER)
	{
		status = 1;
	} else if(mySym == SCISSORS)
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
		mySym = ROCK;
	}
	if (status == 1)
	{
		mySym = PAPER;
	}
	if (status == 2)
	{
		mySym = SCISSORS;
	}
	return mySym;
}
