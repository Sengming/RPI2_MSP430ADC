#include <msp430.h> 
#include <driverlib.h>
#include <General.hpp>
/**
 * main.c
 */
int main(void)
{

	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

    GPIO_setAsOutputPin(
        GPIO_PORT_P1,
        GPIO_PIN0
        );

    //Set P1.0 as Output Low.
    /*

     * Select Port 1
     * Set Pin 0 to output Low.
     */
    GPIO_setOutputLowOnPin(
        GPIO_PORT_P1,
        GPIO_PIN0
        );

//	initializeSystems();
	cExec* executable = newExec();

	runExec(executable);
}


