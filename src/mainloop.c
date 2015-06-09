/*
 * mainloop.c
 *
 * Main loop for the dog bowl.
 *
 * This file contains the main loop for controlling access to the dog bowl. It
 * acts like a finite state machine, opening the bowl only when an object is
 * nearby and the FFT analysis gets a match. The bowl is then closed once the
 * proximity sensors are no longer active.
 *
 * Revision History:
 *      05 Jun 2015     Brian Kubisiak      Initial revision.
 */

#include <avr/interrupt.h>

#include "adc.h"
#include "data.h"
#include "fft.h"
#include "proximity.h"
#include "pwm.h"


/*
 * state
 *
 * Description: Data type for representing the current state of the dog bowl. It
 *              can be waiting for input, performing Fourier analysis, opening
 *              the bowl, or reseting the data.
 *
 * Notes:       This is used by the main loop FSM for determining what to do
 *              with hardware events. To see the transitions, read the
 *              documentation or the switch statement in the main loop.
 */
typedef enum _state {
    INIT_STATE, FFT_STATE, OPEN_STATE, RESET_STATE
} state;


/*
 * main
 *
 * Description: The main loop for the program is a finite state machine that
 *              polls the inputs (the data buffer and proximity sensors) to
 *              determine when to transition between states. For a full
 *              description of the FSM, see the documentation.
 *
 * Notes:       This main loop is not very efficient because it polls the inputs
 *              and runs some of the functions several times in a row.
 */
int main(void)
{
    state curstate = INIT_STATE;
    complex *buf;

    /* Initialize the peripherals used by the main loop. */
    init_adc();
    init_prox_gpio();
    init_pwm();

    DDRC = 0xFF;

    /* Turn on interrupts. */
    sei();

    /* Loop forever, until reset is applied or power is take away. */
    for (;;)
    {
        /* Determine the actions to perform as well as the next state based on
         * the current state. */
        switch (curstate)
        {
        case INIT_STATE:
            /* If data is ready and the proximity sensors are tripped, start the
             * data analysis. */
            if (is_data_collected() && is_obj_nearby()) {
                curstate = FFT_STATE;
            }
            /* If the data is ready, but the sensors are not tripped, then we
             * can ignore the noise. Reset the buffer and start waiting again.
             */
            else if (is_data_collected() && !is_obj_nearby()) {
                curstate = RESET_STATE;
            }
            /* Else, data is not collected; keep waiting in this state. */
            break;
        case FFT_STATE:
            /* Get the buffer of data and perform an FFT on the data. */
            buf = adc_get_buffer();
            fft(buf);

            /* Check that the recorded frequency spectrum matches the stored
             * spectrum. */
            if (is_fft_match(buf)) {
                /* If the spectrum matches, open the bowl. */
                curstate = OPEN_STATE;
            }
            else {
                /* Else, reset the data. */
                curstate = RESET_STATE;
            }
            break;
        case OPEN_STATE:
            /* Open the bowl after identifying the dog. */
            pwm_open();

            /* Wait until the proximity sensors are no longer tripped before
             * closing the bowl. */
            if (!is_obj_nearby()) {
                curstate = RESET_STATE;
            }
            break;
        case RESET_STATE:
            /* Close the dog bowl. */
            pwm_close();

            /* Reset the data collection. */
            adc_reset_buffer();

            /* Go back to waiting for data. */
            curstate = INIT_STATE;
            break;
        default:
            /* By default, go to the initial state. This should never happen. */
            curstate = INIT_STATE;
            break;
        }
    }

    return 0;
}
