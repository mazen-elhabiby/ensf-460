/*
 * File:   main.c
 * Author: marshal
 *
 * Created on September 20, 2023, 6:03 PM
 */


#include "xc.h"

int main(void) {
    
    
    // Set input pins:
    TRISAbits.TRISA0 = 1; // Most significant bit
    TRISAbits.TRISA1 = 1; // 
    TRISAbits.TRISA4 = 1; // 
    TRISAbits.TRISA5 = 1; // Least significant bit
    
    // TRISAbits.TRISA2 = 1; Has clock on it
    // TRISAbits.TRISA3 = 1; Has clock on it
    
    // Set output pins:
    TRISBbits.TRISB0 = 0; // 1
    TRISBbits.TRISB1 = 0; // 2
    TRISBbits.TRISB2 = 0; // 3
    TRISBbits.TRISB4 = 0; // 4
    TRISBbits.TRISB7 = 0; // 5
    TRISBbits.TRISB8 = 0; // 6
    TRISBbits.TRISB9 = 0; // 7
    TRISBbits.TRISB12 = 0; // 8
    TRISBbits.TRISB13 = 0; // 9
 
    
    while(1){

        if ((PORTAbits.RA0 == 0) && (PORTAbits.RA1 == 0) && (PORTAbits.RA4 == 1) && (PORTAbits.RA5 == 1)) { 
            // 1
            LATBbits.LATB0 = 1; 
            LATBbits.LATB1 = 0;
            LATBbits.LATB2 = 0; 
            LATBbits.LATB4 = 0; 
            LATBbits.LATB7 = 0; 
            LATBbits.LATB8 = 0; 
            LATBbits.LATB9 = 0; 
            LATBbits.LATB12 = 0; 
            LATBbits.LATB13 = 0; 
        } else if (((PORTAbits.RA0 == 0) && (PORTAbits.RA1 == 0) && (PORTAbits.RA4 == 0) && (PORTAbits.RA5 == 1)) ||
                ((PORTAbits.RA0 == 0) && (PORTAbits.RA1 == 1) && (PORTAbits.RA4 == 0) && (PORTAbits.RA5 == 1))) { 
            // 3
            LATBbits.LATB0 = 1; 
            LATBbits.LATB1 = 1; 
            LATBbits.LATB2 = 1; 
            LATBbits.LATB4 = 0; 
            LATBbits.LATB7 = 0; 
            LATBbits.LATB8 = 0; 
            LATBbits.LATB9 = 0; 
            LATBbits.LATB12 = 0; 
            LATBbits.LATB13 = 0; 
        } else if (((PORTAbits.RA0 == 0) && (PORTAbits.RA1 == 1) && (PORTAbits.RA4 == 0) && (PORTAbits.RA5 == 0)) ||
                ((PORTAbits.RA0 == 1) && (PORTAbits.RA1 == 0) && (PORTAbits.RA4 == 0) && (PORTAbits.RA5 == 0))) { 
            // 5
            LATBbits.LATB0 = 1; 
            LATBbits.LATB1 = 1; 
            LATBbits.LATB2 = 1; 
            LATBbits.LATB4 = 1; 
            LATBbits.LATB7 = 1; 
            LATBbits.LATB8 = 0; 
            LATBbits.LATB9 = 0; 
            LATBbits.LATB12 = 0; 
            LATBbits.LATB13 = 0; 
        } else if((PORTAbits.RA0 == 0) && (PORTAbits.RA1 == 1) && (PORTAbits.RA4 == 1) && (PORTAbits.RA5 == 0)) { 
            // 8
            LATBbits.LATB0 = 1; 
            LATBbits.LATB1 = 1; 
            LATBbits.LATB2 = 1; 
            LATBbits.LATB4 = 1; 
            LATBbits.LATB7 = 1; 
            LATBbits.LATB8 = 1; 
            LATBbits.LATB9 = 1; 
            LATBbits.LATB12 = 1; 
            LATBbits.LATB13 = 0; 
        } else if((PORTAbits.RA0 == 0) && (PORTAbits.RA1 == 1) && (PORTAbits.RA4 == 1) && (PORTAbits.RA5 == 1)) { 
            // 9
            LATBbits.LATB0 = 1; 
            LATBbits.LATB1 = 1; 
            LATBbits.LATB2 = 1; 
            LATBbits.LATB4 = 1; 
            LATBbits.LATB7 = 1; 
            LATBbits.LATB8 = 1; 
            LATBbits.LATB9 = 1; 
            LATBbits.LATB12 = 1; 
            LATBbits.LATB13 = 1; 
        } else { 
            LATBbits.LATB0 = 0; 
            LATBbits.LATB1 = 0; 
            LATBbits.LATB2 = 0; 
            LATBbits.LATB4 = 0; 
            LATBbits.LATB7 = 0; 
            LATBbits.LATB8 = 0; 
            LATBbits.LATB9 = 0; 
            LATBbits.LATB12 = 0; 
            LATBbits.LATB13 = 0; 
        }
    }

}
