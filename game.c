#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "ir_uart.h"


#define PACER_RATE 500
#define MESSAGE_RATE 10


void display_character (char character)
{
    char buffer[2];

    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}


uint8_t result(uint8_t mine, uint8_t theirs) {
	if (mine == theirs) {
		return 2;
	}
	if (mine == 0 && theirs == 1) {
		return 0;
	} else {
		return 1;
	}
	
	if (mine == 1 && theirs == 2) {
		return 0;
	} else {
		return 1;
	}
	
	if (mine == 2 && theirs == 0) {
		return 0;
	} else {
		return 1;
	}
}

int main (void)
{
	system_init ();
    char character;
    uint8_t status = 0;

    int final_result = 0;
    
    int current_state = 0;

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
		pacer_wait ();
		tinygl_update ();
		navswitch_update ();
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
			character = 'R';
		}
		if (status == 1) {
			character = 'P';
		}
		if (status == 2) {
			character = 'S';
		}
		if (current_state != 1) {
			display_character (character);
		}
		if(navswitch_push_event_p (NAVSWITCH_PUSH)){
			ir_uart_putc(status) ;
		while(1){
		if (ir_uart_read_ready_p() == false){
			tinygl_text("v");
		} else if(ir_uart_read_ready_p() == true){
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