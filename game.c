/*ENCE260 Assignment Part II
  Written by Jinyoung Park 15648768
  Rock_Scissor_Paper */
  


#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "ir_uart.h"


#define PACER_RATE 500
#define MESSAGE_RATE 10

typedef enum {
	PAPER = 'P',
	SCISSORS = 'S',
	ROCK = 'R'
	//WAIT = 'w'
} symbol_t;

typedef enum {
	WIN,
	LOSE,
	DRAW
} result_t;



uint8_t sent = 0;
uint8_t received = 0;
uint8_t ready = 0;
uint8_t text_set = 0;

symbol_t received_symbol;
symbol_t my_symbol = ROCK;
symbol_t their_symbol = ROCK;






void display_character (symbol_t character)
{
    char buffer[2];

    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}


char character;

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

	}
}

symbol_t cSelection(symbol_t my_symbol){
	int status;

	if (my_symbol == ROCK){
		status = 0;
	} else if ( my_symbol == PAPER){
		status = 1;
	} else {
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

void state_update(void){
	navswitch_update();
	if(navswitch_push_event_p(NAVSWITCH_PUSH)){
		ready = 1;                                                                                                                                                                                                                                                                                
		//my_symbol = cSelection(my_symbol)

	}
}


int main (void)
{
	/* Initialize everything*/
	system_init ();
    //char character;
    //int status = 0;
    //int final_result = 0;
    //int current_state = 0;

    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    //tinygl_text_dir_set(TINYGL_TEXT_DIR_ROTATE);

    /* TODO: Initialise navigation switch driver.  */
    navswitch_init();
    ir_uart_init();
    pacer_init (PACER_RATE);

    while(1)
    {
    	//pacer_wait ();
		tinygl_update ();
		navswitch_update ();
		
		// if(ready == 0){
		// 	my_symbol = cSelection(my_symbol);
		// 	display_character(my_symbol);
		// }
		
		
		if (!ready){
			pacer_wait();
			my_symbol = cSelection(my_symbol);
			display_character(my_symbol);

			if(navswitch_push_event_p(NAVSWITCH_PUSH)){
				tinygl_clear();
				ready = 1;
				//ir_uart_putc(my_symbol);
			}
		} else if (ready) {
			ir_uart_putc(my_symbol);
			sent = 1;
		}

		if (!received){
			if(ir_uart_read_ready_p()){
				received_symbol = ir_uart_getc();
				if (received_symbol == PAPER ||
					received_symbol == ROCK  ||
					received_symbol == SCISSORS){
					their_symbol = ir_uart_getc();
					received = 1;
				} 
			}
		}
		
		// if(sent && !received){
		// 	//display_character(WAIT);
		// 	tinygl_text("w");
		// }

		if (sent == 1 && received == 1){
			//ir_uart_putc(my_symbol);
			if(result(my_symbol, their_symbol) == WIN) {
				if(text_set == 0){
					tinygl_text("WINNER");
					text_set = 1;
				}
			} else if (result(my_symbol, their_symbol) == LOSE) {
				if(text_set == 0){
					tinygl_text("LOSSER");
					text_set = 1;
				}
			} else if (result(my_symbol, their_symbol) == DRAW) {
				if(text_set == 0){
					tinygl_text("DRAW");
					text_set = 1;
				}
			}

			if (navswitch_push_event_p(NAVSWITCH_PUSH)){
				sent = 0;
				received = 0;
				ready = 0;
				text_set = 0;
				my_symbol = ROCK;
			}
		}
		tinygl_update();
	}
    return 0;
}

