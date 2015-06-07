/*
 * adc.h
 *
 * Functions for collecting data over the ADC.
 *
 * This file contains functions that handle data collection from the ADC using
 * interrupts. The ADC will be run at set intervals and generate an interrupt
 * every time it has a new data point. Functions in this file will record the
 * data point and disable further interrupts once the buffer is full. Once the
 * buffer is no longer in use, interrupts can be re-enabled when needed.
 *
 * Peripherals Used:
 *      ADC
 *      External interrupts
 *
 * Pins Used:
 *      PF0
 *      PD0
 *
 * Revision History:
 *      05 Jun 2015     Brian Kubisiak      Initial revision.
 *      06 Jun 2015     Brian Kubisiak      Added external trigger.
 */

#ifndef _ADC_H_
#define _ADC_H_


#include "data.h"

/*
 * init_adc
 *
 * Description: This function initializes the ADC peripheral so that the proper
 *              pins are allocated for use. After this function, the ADC will
 *              *not* be running; the 'adc_start_collection' function should be
 *              called before data will be collected. This initialization
 *              involves:
 *               - Writing to ADMUX and ADCSRB to select the input channel.
 *               - Enable ADC by writing to ADCSRA.
 *               - Left-adjust the data input by writing to ADMUX.
 *               - Set the trigger source using ADCSRB.
 *               - Setting up interrupts for autotriggering.
 *               - Setting up external interrupt.
 *
 * Notes:       This function will initialize the ADC to use PF0. If this pin is
 *              used for another purpose, these functions will not work
 *              properly.
 */
void init_adc(void);


/*
 * adc_get_buffer
 *
 * Description: Get a pointer to the buffer of data that has been filled by the
 *              ADC. Note that this buffer should be retrieved each time that
 *              the data collection completes and should not be used globally.
 *
 * Returns:     Returns a pointer to the buffer containing the data collected by
 *              the ADC.
 *
 * Notes:       This kind of makes the buffer into a global variable, so be
 *              careful where this is used. Also note that the buffer should
 *              only be used once it is filled.
 */
complex *adc_get_buffer(void);

/*
 * is_data_collected
 *
 * Description: Determines whether or not the data has been fully collected. If
 *              the buffer is full of new data, this function returns nonzero.
 *              If the ADC is still collecting data for the buffer, returns 0.
 *              This is used to find if the data is ready to run through the
 *              FFT.
 *
 * Returns:     If the buffer is full of new data, return nonzero. Else, return
 *              zero.
 *
 * Notes:       The data collection is reset when the 'adc_start_collection'
 *              function is called.
 */
unsigned char is_data_collected(void);

/*
 * adc_reset_buffer
 *
 * Description: Resets the data buffer that is filled by the ADC. This function
 *              will clear empty the buffer and cause the ADC to begin filling
 *              from the beginning. Note that this function does not start the
 *              ADC data collection; the buffer will be refilled from the
 *              beginning once the 'adc_start_collection' function is called.
 *
 * Notes:       This function should not be called while the buffer is in the
 *              process of being filled. This may cause unexpected race
 *              conditions.
 */
void adc_reset_buffer(void);


#endif /* end of include guard: _ADC_H_ */
