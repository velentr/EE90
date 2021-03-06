/*
 * proximity.h
 *
 * Code for detecting proximity of the dog using the GPIO pins.
 *
 * This file contains an interface for detecting whether or not there is an
 * object detected by the ultrasonic rangefinders. The rangefinders feed into
 * comparators, which are connected to GPIO pins on the microcontroller; the
 * functions in this file will read the status off the GPIO pins to determine
 * whether or not anything is detected by the ultrasonic rangefinders.
 *
 * Peripherals Used:
 *      GPIO
 *
 * Pins Used:
 *      PA[0..7]
 *
 * Revision History:
 *      05 Jun 2015     Brian Kubisiak      Initial revision.
 *      08 Jun 2015     Brian Kubisiak      Changed polarity of signals.
 */

#ifndef _PROXIMITY_H_
#define _PROXIMITY_H_


/*
 * init_prox_gpio
 *
 * Description: This function initializes the GPIO pins so that they are ready
 *              to read data from the proximity sensors. This process involves:
 *               - Writing a 0 to DDA to set GPIO as input.
 *               - Writing a 1 to PORTA to enable the pull-up resistor.
 *               - Writing a 0 to the PUD bit in MCUCR
 *
 * Notes:       This function assumes that no other peripherals are going to use
 *              PA[0..7] pins; the configuration might not work if this is the
 *              case.
 */
void init_prox_gpio(void);


/*
 * is_obj_nearby
 *
 * Description: Determine whether or not there is an object nearby using the
 *              ultrasonic proximity sensors. This function returns 0 if no
 *              objects are detected by the proximity sensors, and returns
 *              nonzero is objects are detected.
 *
 * Return:      If no objects are in range of the ultrasonic sensors, returns 0.
 *              If one or more objects are in range, returns nonzero.
 *
 * Notes:       The return value uses the even 4 bits to represent the
 *              rangefinders in each direction, so the number of triggered
 *              rangefinders can also be found from the return value.
 */
unsigned char is_obj_nearby(void);


#endif /* end of include guard: _PROXIMITY_H_ */
