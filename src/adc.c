/*
 * adc.c
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
 *      08 Jun 2015     Brian Kubisiak      Added pullup resistor to INT0.
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#include "adc.h"

/* Initial values for the ADC configuration registers. */
#define ADMUX_VAL   0x60
#define ADCSRA_VAL  0x8F
#define ADCSRB_VAL  0x00
#define DIDR0_VAL   0x01
#define DIDR2_VAL   0x00

/* Initial values for external interrupt configuration. */
#define EICRA_VAL   0x03
#define EIMSK_VAL   0x01

/* Add pullup resistor to interrupt pin. */
#define PORTD_VAL   0xFF

/* ORing this with ADCSRA will begin the data collection process. */
#define ADCSTART    0x60

static complex databuf[SAMPLE_SIZE];
static unsigned int bufidx = 0;
static unsigned char buffull = 0;
static unsigned char collecting = 0;

/*
 * adc_start_collection
 *
 * Description: Start collecting a new buffer of data. This function will enable
 *              auto-triggering off of the ADC interrupt and start a new
 *              conversion to start the chain of data collection. Once the
 *              buffer is full, the interrupt vector will disable the
 *              autotriggering automatically.
 *
 * Notes:       This function should not be called until the buffer is filled
 *              and data collection halts. This can be checked with the
 *              'is_data_collected' function.
 */
static void adc_start_collection(void)
{
    /* Reset the index to load values into the start of the buffer. */
    bufidx = 0;

    /* Buffer is no longer full. */
    buffull = 0;

    /* Set the flag signaling that collection is in progress. */
    collecting = 1;

    /* Enable autotriggering and start the first conversion. */
    ADCSRA |= ADCSTART;
}

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
 *               - Enable the ADC interrupt.
 *               - Setting up interrupts for autotriggering.
 *               - Setting up external interrupt.
 *
 * Notes:       This function will initialize the ADC and external interrupt to
 *              use PF0 and PD0. If these pins are used for another purpose,
 *              these functions will not work properly.
 */
void init_adc(void)
{
    /* Set all the configuration registers to their initial values. */
    ADMUX   = ADMUX_VAL;
    ADCSRA  = ADCSRA_VAL;
    ADCSRB  = ADCSRB_VAL;
    DIDR0   = DIDR0_VAL;
    DIDR2   = DIDR2_VAL;

    /* Reset the buffer collection. */
    adc_reset_buffer();

    /* Add pullup resistor to the INT0 pin. */
    PORTD = PORTD_VAL;

    /* Activate the external interrupt for triggering a recording. */
    EICRA = EICRA_VAL;
    EIMSK = EIMSK_VAL;
}

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
 *              careful where this is used.
 */
complex *adc_get_buffer(void)
{
    /* Return the current buffer. */
    return databuf;
}

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
unsigned char is_data_collected(void)
{
    /* Data is collected once the buffer is full. */
    return buffull;
}


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
void adc_reset_buffer(void)
{
    /* Start buffer collection from the beginning. */
    bufidx = 0;

    /* Buffer is no longer full. */
    buffull = 0;

    /* No longer collecting data. */
    collecting = 0;
}

/*
 * ADC_vect
 *
 * Description: Interrupt vector for the ADC interrupt. When this interrupt
 *              occurs, the function will store the new data point if the buffer
 *              is not yet full. Then, the function will check to see if the
 *              buffer is now full, updating the flag accordingly. Once the
 *              buffer is full, data collection is disabled.
 *
 * Notes:       The interrupt should be automatically reset in hardware.
 */
ISR(ADC_vect)
{
    /* If the buffer is not yet full, record the data. */
    if (!buffull)
    {
        /* Take the upper 8 bits of the ADC as the real part of the signal. The
         * imaginary part is zero. */
        databuf[bufidx].real = ADCH;
        databuf[bufidx].imag = 0;

        /* Next data point should be stored in the next slot. */
        bufidx++;

        /* Check to see if the buffer is full. */
        if (bufidx == SAMPLE_SIZE)
        {
            /* When full, set the flag. */
            buffull = 1;

            /* Disable further data collection. */
            ADCSRA = ADCSRA_VAL;
        }
    }
    /* If the buffer is already full, then we triggered once too many
     * conversions. This interrupt can be ignored. */

    /* Interrupt flag is automatically turned off in hardware. */
}

/*
 * INT0_vect
 *
 * Description: Triggers the ADC data collection on an external interrupt. Once
 *              the amplitude of the audio input goes above a certain level,
 *              this interrupt will fire and begin recording data. If data is
 *              already being collected, or the buffer is already full, then the
 *              interrupt will be ignored.
 *
 * Notes:       The interrupt should be automatically reset in hardware.
 */
ISR(INT0_vect)
{
    /* If we aren't already collecting, start the collection. */
    if (!collecting) {
        adc_start_collection();
    }
    /* Else, just ignore this interrupt. */

    /* The interrupt flag is cleared automatically in hardware. */
}
