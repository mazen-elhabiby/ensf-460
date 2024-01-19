/*
 * File:   TimeDelay.c
 * Author: Maged El Habiby, Mazen El Habiby, Marshal Kalynchuk
 * Group 20
 * Created on October 17, 2023, 2:10 PM
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

void delay_ms(uint16_t time_ms) {
    
    int fclk;
    if (time_ms > 262 && time_ms < 4095) {
        fclk = 16;
        NewClk(32);
    } else if (time_ms > 16 && time_ms <= 262) {
        fclk = 250;
        NewClk(500);
    } else if (time_ms <= 16) {
        fclk = 4000;
        NewClk(8);
    }
    
    T2CONbits.TON =0; //turns timer off
    //IPC1bits.T2IP0 = 0; //low priority

    T2CONbits.TSIDL = 0; //operate in idle mode
    T2CONbits.T32 = 0; // operate timer 2 as 16 bit timer
    T2CONbits.TCKPS = 0b00; //Prescaler=1
    T2CONbits.TCS = 0; // use internal clock
    TMR2 = 0; // Clear TMR2 register
    PR2 = time_ms * fclk;
 
    T2CONbits.TON = 1; //Starts Timer 2
    IPC1bits.T2IP = 7; //7 is highest priority, 1 is lowest
    IFS0bits.T2IF = 0; //Clear Timer 2 flag
    IEC0bits.T2IE = 1; // Enable Timer 2 interrupt
    
    Idle(); //Sets the CPU to idle until interrupt flag becomes 1.

    return;
}

void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void) {
    IFS0bits.T2IF = 0; // Clear Timer 2 interrupt flag
    TMR2 = 0;
    T2CONbits.TON = 0; // Stop Timer 2
    return;
    //TMR2 = 0;
    //timer2Flag = 1; // Set the flag
}
