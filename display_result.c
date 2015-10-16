/*ENCE260 Assignment Part II
  Written by Jinyoung Park 15648768, Sam Taylor
  Rock_Scissor_Paper
  ----------------------------------
  File: display._result.c
*/

#include "system.h"
#include "display_result.h"
#include "get_result.h"
#include "results.h"
#include "symbols.h"
#include "tinygl.h"


void display_result(int text_set, symbolType mySym, symbolType thSym)
{
	if(result(mySym, thSym) == WIN)
			{
				
				if(text_set == 0)
				{
					tinygl_text("WINNER");
					text_set = 1;
				}
			} else if (result(mySym, thSym) == LOSE)
			{
				if(text_set == 0)
				{
					tinygl_text("LOSSER");
					text_set = 1;
				}
			} else if (result(mySym, thSym) == DRAW)
			{
				if(text_set == 0)
				{
					tinygl_text("DRAW");
					text_set = 1;
				}
			}
}