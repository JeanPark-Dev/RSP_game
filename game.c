/*author Jinyoung Park*/

#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "ir_uart.h"


#define PACER_RATE 500
#define MESSAGE_RATE 10


void display_character (symbol_t character)
{
    char buffer[2];

    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}

typedef enum {
	PAPER = 'P',
	SCISSORS = 'S',
	ROCK = 'R'
} symbol_t;

typedef enum {
	WIN,
	LOSE,
	DRAW
} result_t;

char character;

result_t result(symbol_t mine, symbol_t theirs) {
	if (mine == theirs) {
		return DRAW;
	}
	if (mine == PAPER && theirs == ROCK) {
		return WIN;
	} else {
		return LOSE;
	}
	
	if (mine == ROCK && theirs == SCISSORS) {
		return WIN;
	} else {
		return LOSE;
	}
	
	if (mine == SCISSORS && theirs == PAPER) {
		return WIN;
	} else {
		return LOSE;
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


int main (void)
{
	char sent = 0;
	char received = 0;
	char ready = 0;
	char text_set = 0;

	int current_state = 0;
	symbol_t received_symbol;
	symbol_t my_symbol = ROCK;
	symbol_t their_symbol;


	/* Initialize everything*/
	system_init ();
    //char character;
    uint8_t status = 0;

    int final_result = 0;
    //int current_state = 0;

    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    //tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
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
		

		if (ready == 0){
			my_symbol = cSelection(my_symbol);
			display_character(my_symbol);

			if(navswitch_push_event_p(NAVSWITCH_PUSH)){
				tinygl_clear();
				ready = 1;
			}
		} else {
			ir_uart_putc(my_symbol);
			sent = 1;
		}

		if (received == 0){
			if(ir_uart_read_ready_p()){
				received_symbol = ir_uart_getc;
				if (received_symbol == PAPER ||
					received_symbol == ROCK ||
					received_symbol == SCISSORS){
					their_symbol = ir_uart_getc;
					received = 1;
				} 
			}
		}
		
		//use while loop to keep search any signal that sent from opponent
		if (sent == 1 && received == 0){
			tinygl_text("wait")	;
			while(1){
				if(ir_uart_read_ready_p()){
					received_symbol = ir_uart_getc;
					if (received_symbol == PAPER ||
						received_symbol == ROCK ||
						received_symbol == SCISSORS){
						their_symbol = ir_uart_getc;
						received = 1;
						
					} 
					break;
				}
			}
		}






		if (current_state != 1) {
			display_character (character);
		}
		if(navswitch_push_event_p (NAVSWITCH_PUSH)){
			ir_uart_putc(my_symbol);
		
		if (ir_uart_read_ready_p() == false){
			;
		}  
		if(ir_uart_read_ready_p() == true){
    			uint8_t received;
			received = ir_uart_getc();
			current_state = 1;
			final_result = result(status, received);
			if (final_result == 2 ) {
				tinygl_text("D");
			} else if (final_result == 1) {
				tinygl_text("W");
			} else if (final_result == 0) {
				tinygl_text("L");
			}
		}
	}	



/*
		if (ir_uart_read_ready_p() == true ){
			received = ir_uart_getc();
			current_state = 1;
			final_result = result(status, received);
			if (final_result == 2) {
				tinygl_text("DRAW");
			} else if(final_result == 1) {
				tinygl_text("WIN");
			} else {
				tinygl_text("LOSE");
			}
		}
*/
	}
    return 0;
}
