/*ENCE260 Assignment Part II
  Written by Jinyoung Park 15648768
  Rock_Scissor_Paper
  ----------------------------------
  File: game.c
  Main function
*/

//including required header files
#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "ir_uart.h"

#include "symbols.h"
#include "results.h"
#include "display_game.h"
#include "selection.h"
#include "get_result.h"

#define PACER_RATE 500  //hertz
#define MESSAGE_RATE 10 //speed of message flowing

//main function
int main(void)
{
	//initialisation
	system_init ();

    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);

    navswitch_init();
    ir_uart_init();
    pacer_init (PACER_RATE);

    //status of communication among players
    int ready = 0;			//0 = message is not ready to send | 1 = ready
	int sent = 0;			//0 = message not sent  		   | 1 = sent
	int received = 0;		//0 = message not received 		   | 1 = received

	//prevent displaying game result more than 1 time
	int text_set = 0;

	//current symbols(status)
						//sym = symbol
	symbolType symReceived;
	symbolType mySym = ROCK;
	symbolType thSym;

    while(1)
    {
		tinygl_update ();
		navswitch_update ();

		if (!ready)
		{
			pacer_wait();
			mySym = cSelection(mySym);
			cDisplay(mySym);

			if (navswitch_push_event_p(NAVSWITCH_PUSH))
			{
				tinygl_clear();
				ready = 1;
			}
		} else if (ready) {
			ir_uart_putc(mySym);
			sent = 1;
		}

		if (!received)
		{
			if(ir_uart_read_ready_p())
			{
				symReceived = ir_uart_getc();

				//check whether the received symbol is one of three symbols
				if (symReceived == PAPER ||
					symReceived == ROCK  ||
					symReceived == SCISSORS)
				{
					thSym = symReceived;
					received = 1;
				}
			}
		}

		//display 'w' while wating
		if(sent && !received)
		{
			tinygl_text("w");
		}

		if (sent == 1 && received == 1)
		{
			//display the final status
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

			//Restart the game by pushing the navswitch button
			if (navswitch_push_event_p(NAVSWITCH_PUSH))
			{
				sent = 0;
				received = 0;
				ready = 0;
				text_set = 0;
				mySym = ROCK;
			}
		}
		tinygl_update();
	}
    return 0;
}
