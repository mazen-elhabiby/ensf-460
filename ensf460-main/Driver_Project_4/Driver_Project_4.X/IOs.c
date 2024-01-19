/*
 * File:   IOs.c
 * Author: Maged El Habiby, Mazen El Habiby, Marshal Kalynchuk
 * Group 20
 * Created on October 29, 2023, 2:10 PM
 */


#include "xc.h"
#include "TimeDelay.h"
#include "ChangeClk.h"
#include "UART2.h"

//volatile int blinkRate = 0;

void IOinit(){
    // Disable analog functionality on all pins
    AD1PCFG = 0xFFFF;
    CNPU1bits.CN0PUE = 1; // Enables pull up resistor on RA4/CN0
    CNPU1bits.CN1PUE = 1; // Enables pull up resistor on RB4/CN1
    CNPU2bits.CN30PUE = 1; // Enables pull up resistor on RA2/CN30
     
    // Enable Change Notification on the required pins
    CNEN1bits.CN0IE = 1;   // Enable CN for RA4
    CNEN1bits.CN1IE = 1;   // Enable CN for RB4
    CNEN2bits.CN30IE = 1;  // Enable CN for RA2
    
    IFS1bits.CNIF = 0;  // Clear CN interrupt flag
    IEC1bits.CNIE = 1;  // Enable CN interrupt
    
    // Make RB8 an output for LED and  Initially turn off LED
    TRISBbits.TRISB8 = 0;
    LATBbits.LATB8 = 0;
    
    // Make RA2, RA4 and RB4 inputs for pushbuttons
    TRISAbits.TRISA2 = 1; //PB1
    TRISAbits.TRISA4 = 1; //PB2
    TRISBbits.TRISB4 = 1; //PB3
    InitUART2();

}
    static int pb1_flag = 0;
    static int pb2_flag = 0;
    static int pb3_flag = 0;
    static int pb1_pb2_flag = 0;
    static int pb1_pb3_flag = 0;
    static int pb2_pb3_flag = 0;
    static int pb_all_flag = 0;
    static int pb_non_flag = 0;

void IOcheck() {
    //delay_ms(100, 1);

    // PB1 pressed only
    if ((PORTAbits.RA2 == 0) && (PORTAbits.RA4 == 1) && (PORTBbits.RB4 == 1)) {
        while ((PORTAbits.RA2 == 0) && (PORTAbits.RA4 == 1 )&& (PORTBbits.RB4 == 1)) {
            if (!pb1_flag) {
                Disp2String("\n\rPB1 is pressed");
                pb1_flag = 1;
                pb_non_flag = 0;
            }
            LATBbits.LATB8 ^= 1; // Toggle LED
            delay_ms(500, 1);  // Set delay to 0.5 second
        }
        return;
    } else {
        pb1_flag = 0;
    }

    // PB2 pressed only
    if ((PORTAbits.RA2 == 1) && (PORTAbits.RA4 == 0) && (PORTBbits.RB4 == 1)) {
        while ((PORTAbits.RA2 == 1) && (PORTAbits.RA4 == 0) && (PORTBbits.RB4 == 1)) {
            if (!pb2_flag) {
            Disp2String("\n\rPB2 is pressed");
            pb2_flag = 1;
            pb_non_flag = 0;
        }
        LATBbits.LATB8 ^= 1; // Toggle LED
        delay_ms(2000, 1);  // Set delay to 2 seconds
        }
                return;
    } else {
        pb2_flag = 0;
    }
    
    // PB3 pressed only
    if ((PORTAbits.RA2 == 1) && (PORTAbits.RA4 == 1) && (PORTBbits.RB4 == 0)) {
        while ((PORTAbits.RA2 == 1) && (PORTAbits.RA4 == 1) && (PORTBbits.RB4 == 0)) {
            if (!pb3_flag) {
            Disp2String("\n\rPB3 is pressed");
            pb3_flag = 1;
            pb_non_flag = 0;
        }
        LATBbits.LATB8 ^= 1; // Toggle LED
        delay_ms(3000, 1);  // Set delay to 3 seconds
        }
                return;
    }
    else {
        pb3_flag = 0;
    }

    // 2 PBs are pressed together
    if (((PORTAbits.RA2 == 0) + (PORTAbits.RA4 == 0) + (PORTBbits.RB4 == 0)) == 2) {
        while (((PORTAbits.RA2 == 0) + (PORTAbits.RA4 == 0) + (PORTBbits.RB4 == 0)) == 2) {
            LATBbits.LATB8 = 1; // LED stays on
        if (PORTAbits.RA2 == 0 && PORTAbits.RA4 == 0 && !pb1_pb2_flag) {
            Disp2String("\n\rPB1 and PB2 are pressed");
            pb1_pb2_flag = 1;
            pb_non_flag = 0;
        }
        else if (PORTAbits.RA2 == 0 && PORTBbits.RB4 == 0 && !pb1_pb3_flag) {
            Disp2String("\n\rPB1 and PB3 are pressed");
            pb1_pb3_flag = 1;
                            pb_non_flag = 0;
        }
        else if (PORTAbits.RA4 == 0 && PORTBbits.RB4 == 0 && !pb2_pb3_flag) {
            Disp2String("\n\rPB2 and PB3 are pressed");
            pb2_pb3_flag = 1;
                            pb_non_flag = 0;
        }
        }
                return;
    }
    else {
        pb1_pb2_flag = pb1_pb3_flag = pb2_pb3_flag = 0;
    }

    // All 3 PBs are pressed
    if (((PORTAbits.RA2 == 0) + (PORTAbits.RA4 == 0) + (PORTBbits.RB4 == 0)) == 3) {
        while(((PORTAbits.RA2 == 0) + (PORTAbits.RA4 == 0) + (PORTBbits.RB4 == 0)) == 3) {
            if (!pb_all_flag) {
                Disp2String("\n\rAll PBs pressed");
                pb_all_flag = 1;
                                pb_non_flag = 0;
            }
        LATBbits.LATB8 = 1; // LED stays on
        }
               return;
    }
    else {
       pb_all_flag = 0;
    }
    
 
    if (!pb_non_flag) {
        Disp2String("\n\rNo PBs pressed");
        pb_non_flag = 1;
    }
  
    LATBbits.LATB8 = 0;

}

void __attribute__((interrupt, auto_psv)) _CNInterrupt(void) {
    
    IFS1bits.CNIF = 0;  // Clear CN interrupt flag
    delay_ms(100,1);
    
}
