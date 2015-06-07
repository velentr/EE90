/*
 * pwm.h
 *
 * Open and close the dog bowl with PWM.
 *
 * This file contains functions for using the PWM module for opening and closing
 * the dog bowl. The PWM port is connected to a servo motor, so changing the PWM
 * to a specific duty cycle will move the servo to the corresponding position.
 *
 * Peripherals Used:
 *      PWM
 *
 * Pins Used:
 *      PB7
 *
 * Revision History:
 *      05 Jun 2015     Brian Kubisiak      Initial revision.
 */

#ifndef _PWM_H_
#define _PWM_H_


/*
 * init_pwm
 *
 * Description: Initializes the PWM controlling the servo motor for
 *              opening/closing the dog bowl. This will set up the PWM pin for
 *              use and initialize the servo to a closed position.
 *
 * Notes:       The PWM uses the pin PB7; using this pin somewhere else could
 *              cause problems.
 */
void init_pwm(void);

/*
 * pwm_open
 *
 * Description: Open the dog bowl by moving the servo to a set open position.
 *              The servo is controlled by changing the duty cycle on the PWM
 *              output.
 *
 * Notes:       This function can be called multiple times in a row with no
 *              effect.
 */
void pwm_open(void);

/*
 * pwm_close
 *
 * Description: Close the dog bowl by moving the servo to a set closed position.
 *              The servo is controlled by changing the duty cycle on the PWM
 *              output.
 *
 * Notes:       This function can be called multiple times in a row with no
 *              effect.
 */
void pwm_close(void);


#endif /* end of include guard: _PWM_H_ */
