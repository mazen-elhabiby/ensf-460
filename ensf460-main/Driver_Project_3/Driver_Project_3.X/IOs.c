/*
 * File:   IOs.c
 * Author: Maged El Habiby, Mazen El Habiby, Marshal Kalynchuk
 * Group 20
 * Created on October 17, 2023, 2:10 PM
 */


#include "xc.h"
#include "TimeDelay.h"
#include "ChangeClk.h"

void IOinit(){
    // Disable analog functionality on all pins
    AD1PCFG = 0xFFFF;
    CNPU1bits.CN0PUE = 1; // Enables pull up resistor on RA4/CN0
    CNPU1bits.CN1PUE = 1; // Enables pull up resistor on RB4/CN1
    CNPU2bits.CN30PUE = 1; // Enables pull up resistor on RA2/CN30
     
    // Make RB8 an output for LED and  Initially turn off LED
    TRISBbits.TRISB8 = 0;
    LATBbits.LATB8 = 0;
    
    // Make RA2, RA4 and RB4 inputs for pushbuttons
    TRISAbits.TRISA2 = 1; //PB1
    TRISAbits.TRISA4 = 1; //PB2
    TRISBbits.TRISB4 = 1; //PB3
    
}


void IOcheck() {
    
    // PB1 pressed only
    delay_ms(50);
    if (PORTAbits.RA2 == 0 && PORTAbits.RA4 == 1 && PORTBbits.RB4 == 1) {
        LATBbits.LATB8 ^= 1; // Toggle LED
        delay_ms(1000);  // Set delay to 1 second
    }
    // PB2 pressed only
    else if (PORTAbits.RA2 == 1 && PORTAbits.RA4 == 0 && PORTBbits.RB4 == 1) {
        LATBbits.LATB8 ^= 1; // Toggle LED
        delay_ms(2000);  // Set delay to 2 seconds
    }
    // PB3 pressed only
    else if (PORTAbits.RA2 == 1 && PORTAbits.RA4 == 1 && PORTBbits.RB4 == 0) {
        LATBbits.LATB8 ^= 1; // Toggle LED
        delay_ms(3000);  // Set delay to 3 seconds
    }
    // PB1 and PB2 pressed
    else if (PORTAbits.RA2 == 0 && PORTAbits.RA4 == 0 && PORTBbits.RB4 == 1) {
        LATBbits.LATB8 ^= 1; // Toggle LED quickly
        delay_ms(1);    // Set delay to 1 millisecond
    }
    // No buttons pressed
    else {
        LATBbits.LATB8 = 0;  // Turn off the LED
    }
    return;
}