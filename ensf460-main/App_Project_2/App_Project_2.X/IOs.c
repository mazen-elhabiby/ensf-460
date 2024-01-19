/*
 * File:   IO.c
 * Author: Maged El Habiby, Mazen El Habiby, Marshal Kalynchuk
 * Group 20
 * Created on December 3, 2023, 5:23 PM
 */


#include "xc.h"

#include "IOs.h"
#include "pwm.h" 
#include "ADC.h"
#include "UART2.h"
#include "TimeDelay.h"


// define bounds for brightness
#define MAX_PWM 0xFFFF
#define MIN_PWM 0x0000

#define FCY 16000000UL
#include <libpic30.h>


// Global variables to track the previous state of buttons
static int lastPB1State = 1; // buttons are not pressed initially
static int lastPB2State = 1;
static int systemOn = 0;     // state - 0 for OFF, 1 for ON
static int ledBlinking = 0;  // state - 0 for not blinking, 1 for blinking
static int ledOn = 0; // 1 for on, 0 for off
static int brightness = 0; // global brightness value

void IOInit() {
    
    // Make RA2, RA4 and RB4 inputs for pushbuttons
    TRISAbits.TRISA2 = 1; //PB1
    TRISAbits.TRISA4 = 1; //PB2
    TRISBbits.TRISB4 = 1; //PB3
    
    //Clock output on REFO pin - pin 18 RB15
    TRISBbits.TRISB15 = 0;  // Set RB15 as output for REFO
    REFOCONbits.ROEN = 1; // Ref oscillator is enabled
    REFOCONbits.ROSSLP = 0; // Ref oscillator is disabled in sleep
    REFOCONbits.ROSEL = 0; // Output base clk showing clock switching
    REFOCONbits.RODIV = 0b0000;

    //IO Inititalizations

    AD1PCFG = 0xFFFF;// Disable analog functionality on all pins
    
    // Enable pull up resistors
    CNPU1bits.CN0PUE = 1; // Enables pull up resistor on RA4/CN0
    CNPU1bits.CN1PUE = 1; // Enables pull up resistor on RB4/CN1
    CNPU2bits.CN30PUE = 1; // Enables pull up resistor on RA2/CN30
     
    // Enable Change Notification on the required pins
    CNEN1bits.CN0IE = 1;   // Enable CN for RA4
    CNEN1bits.CN1IE = 1;   // disable CN for RB4
    CNEN2bits.CN30IE = 1;  // Enable CN for RA2
    
    //IPC4 = IPC4 | 0xF000;   // CN Interrupts set to priority 7
    IPC4bits.CNIP = 6;
    IFS1bits.CNIF = 0;  // Clear CN interrupt flag
    IEC1bits.CNIE = 1;  // Enable CN interrupt
    
    InitUART2();
    PWM_Init();

}

void __attribute__((interrupt, auto_psv)) _CNInterrupt(void) {
    IFS1bits.CNIF = 0; // Clear CN interrupt flag

    // Simple debouncing
    __delay_ms(50);

    int currentPB1State = PORTBbits.RB4;
    int currentPB2State = PORTAbits.RA4;

    // Check for PB1 state change
    if (lastPB1State != currentPB1State) {
        if (!currentPB1State) { // If button is pressed
            
            systemOn = !systemOn; // Toggle system state
            if (!systemOn) ledBlinking = 0; // Toggle blinking when in Off mode
        }
        
        lastPB1State = currentPB1State; // Update last state
    }

    
    // Check for PB2 state change
    if (lastPB2State != currentPB2State) {
        if (!currentPB2State) { // If button is pressed
            ledBlinking = !ledBlinking; // Toggle blinking state
            
        }
       
        lastPB2State = currentPB2State; // Update last state
    }
}


void IOCheck() {
    
    if (systemOn) {
        // ON Mode
        
        if (ledBlinking) {
            // LED blinking Mode
            handleBlink();
        } else {
            // ON Mode
           updateLEDBrightness();

        }
        
    } else {
        // OFF Mode
        brightness = MIN_PWM;
        PWM_SetDutyCycle(brightness);
        display(brightness);
        enterIdleMode();
    }
    //display(brightness);
    
}

void enterIdleMode() {
    Idle();
}

// Calculate and set the brightness based on potentiometer voltage
void updateLEDBrightness() {
    uint16_t potValue = readADC(); // Assuming readADC() reads potentiometer value
    brightness = ((float) potValue / 0x03FF) * MAX_PWM; // calculate brightness
    display(brightness); // send brightness to UART2
    PWM_SetDutyCycle(brightness); // set brightness
}

// sends a given value through the UART2 in hex
void display(uint16_t value) {
    XmitUART2('\r', 1);
    XmitUART2('\n', 1);
    Disp2Hex(value); // send value in hex
}


// toggles the led from high to low
void handleBlink() {
    brightness = (ledOn = !ledOn) ? MAX_PWM : MIN_PWM;
    //display(brightness);
    PWM_SetDutyCycle(brightness);
    // delay many short times to increase the 
    // resolution of data being send to UART
    for (int i = 0, j = 25; i < 250; i += j) {
        display(brightness);
       __delay_ms(j); 
    }
    
}