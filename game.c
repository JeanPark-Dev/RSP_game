//Author: Jinyoung Park
//15648768

#include "system.h"
#include "ir_uart.h"
#include "pacer.h"
#include "pio.h"
#include "navswitch.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"

#define PACER_RATE 500
#define MESSAGE_RATE 10


void RSP_choice (int16_t* status) {
  if (navswitch_push_event_p (NAVSWITCH_WEST)){
    *status -= *status ;
  }
  if (navswitch_push_event_p (NAVSWITCH_NORTH)){
    *status += *status ;
  }
  *status = *status % 3;
}

void display_character (int status)
{
    char buffer[2];
    char character;
    if (status == 0) {
      character = 'P';
    }
    if (status == 1) {
      character = 'R';
    }
    if (status == 1) {
      character = 'S';
    }

    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}




int main(void){
  int16_t status = 0;
  system_init ();
    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);

    /* TODO: Initialise navigation switch driver.  */
	navswitch_init();
    pacer_init (PACER_RATE);

    while(1)
  {
    pacer_wait();
    tinygl_update();
    navswitch_update();
    RSP_choice(&status);


  }

}
