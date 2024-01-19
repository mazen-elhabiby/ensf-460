/*
 * File:   TimeDelay.c
 * Author: Maged El Habiby, Mazen El Habiby, Marshal Kalynchuk
 * Group 20
 * Created on October 29, 2023, 2:10 PM
 */
#include "xc.h"
#include "ChangeClk.h"

/*
 * File:   IOs.c
 * Author: Maged El Habiby, Mazen El Habiby, Marshal Kalynchuk
 * Group 20
 * Created on October 17, 2023, 2:10 PM
 */
// Declare a flag that is set by the ISR
//volatile int timer2Flag = 0;

void delay_ms(uint16_t time_ms, uint8_t idle_on)
{
    // config timer
    IPC1bits.T2IP = 2;
    IEC0bits.T2IE = 1;
    IFS0bits.T2IF = 0;
    // config t2con
    T2CONbits.TSIDL = 0;
    T2CONbits.T32 = 0;
    // start timer
    PR2 = time_ms << 4; 
    TMR2 = 0;
    T2CONbits.TON = 1;
    if(idle_on == 1) Idle(); 
    T2CONbits.TON=0; // Stop timer
    return;
}

// Interrupt
void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void)
{
    //Clear timer 2 interrupt flag
    IFS0bits.T2IF=0; 
    Nop();
    return;
}