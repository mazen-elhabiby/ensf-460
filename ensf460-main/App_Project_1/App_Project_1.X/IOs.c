/*
 * File:   IOs.c
 * Author: Maged El Habiby, Mazen El Habiby, Marshal Kalynchuk
 * Group 20
 * Created on November 05, 2023, 2:10 PM
 */


#include "xc.h"
#include "TimeDelay.h"
#include "ChangeClk.h"
#include "UART2.h"
#include "display.h"

void IOinit(){
    
    AD1PCFG = 0xFFFF;// Disable analog functionality on all pins
    
    // Enable pull up resistors
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
    TRISBbits.TRISB8 = 0;   // Makes RB8 as an output
    LATBbits.LATB8 = 0;     // Turns LED Light off
    
    // Make RA2, RA4 and RB4 inputs for pushbuttons
    TRISAbits.TRISA2 = 1; //PB1
    TRISAbits.TRISA4 = 1; //PB2
    TRISBbits.TRISB4 = 1; //PB3
    
    InitUART2();
}

// global variables to track time and state
static int minute_time = 0;
static int second_time = 0;
static int timer_running = 0;
const static int LOOP_MS = 800; // used for the 3 second delay on timer reset
static int pb3_press_duration = 0;
static int pb3_prev_state = 1; // button is not pressed initially
static int just_reset = 0;

// Utility function to increment minutes
void incrementMinutes() {
    minute_time = (minute_time + 1) % 60; // Wrap around at 59 minutes
}

// Utility function to increment seconds
void incrementSeconds() {
    second_time = (second_time + 1) % 60; // Wrap around at 59 seconds
}

// Utility function to start
void startTimer() {
    timer_running = 1;
}

// Utility function to stop the timer and turns off the LED light
void stopTimer() {
    timer_running = 0;
    LATBbits.LATB8 = 0;
}

// Utility function to Reset the timer
void resetTimer() {
    minute_time = 0;
    second_time = 0;
    just_reset = 1;
    stopTimer();
    DisplayResetMessage();
}

//  Utility function for when timer is finished
void timerFinished() {
    stopTimer();
    DisplayAlarm();
    LATBbits.LATB8 = 1; // LED on.
}

// Function for incrementing the pb3_press_duration and reseting the timer
void incrementPB3PressDuration() {
    if (pb3_prev_state == 0 && !timer_running) { // If the button is currently pressed
        delay_ms(LOOP_MS, 1);
        pb3_press_duration += LOOP_MS; // Increment the press duration counter
        if (pb3_press_duration >= LOOP_MS * 3) {
            resetTimer();
            pb3_press_duration = 0;
        }
    }
}

// Function to check the state. Call in inf. loop
void IOcheck() {
    // if timer not running and no button pressed 
    if (!timer_running && PORTAbits.RA2 && PORTAbits.RA4 && PORTBbits.RB4) {
        // make sure the interrupt finish executed
        if (!U2STAbits.TRMT) {
            Idle();
        }
    } else {

        incrementPB3PressDuration();

        // Check if PB1 is pressed to set minutes
        if (!PORTAbits.RA2 && !timer_running) {
            incrementMinutes();
            UpdateTimerDisplay(minute_time, second_time);
            delay_ms(300, 1); // Simple button press delay
        }

        // Check if PB2 is pressed to set seconds
        if (!PORTAbits.RA4 && !timer_running) {
            incrementSeconds();
            UpdateTimerDisplay(minute_time, second_time);
            delay_ms(300, 1); // Simple button press delay
        }

        // Timer countdown logic
        if (timer_running) {
            LATBbits.LATB8 ^= 1;
            if (second_time > 0) {
                second_time--; // Reduce seconds
                UpdateTimerDisplay(minute_time, second_time);
            } else if (minute_time > 0) {
                minute_time--; // reduce minutes
                second_time = 59; // loop back seconds
                UpdateTimerDisplay(minute_time, second_time);
            } else {
                timerFinished(); // timer finished
            }
        } else {
            LATBbits.LATB8 = 0; // turn off led
        }
    }
    
}

// Interrupt for pb3 and to take controller out of idle
void __attribute__((interrupt, auto_psv)) _CNInterrupt(void) {
    // Clear CN interrupt flag
    IFS1bits.CNIF = 0;

    // Read the current state of PB3
    int pb3_state = PORTBbits.RB4;

    // Check if the state of PB3 has changed from high to low (button pressed)
    if (pb3_prev_state == 1 && pb3_state == 0) {
        // Reset the press duration counter on a new press
        pb3_press_duration = 0;
    }

    // If the button is released, check the duration it was pressed
    if (pb3_prev_state == 0 && pb3_state == 1) {
        // savegaurd so the timer state does not change if pb3 was pressed to reset the timer
        if (just_reset) {
            just_reset = 0;
        } else {
            // If button was pressed for less than 3 seconds, start/pause the timer
            if (timer_running) {
                stopTimer();
            } else {
                startTimer();
            }
        }
    }

    // Save the current state of PB3 for the next interrupt
    pb3_prev_state = pb3_state;
}



