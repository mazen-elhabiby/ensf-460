/*
 * File:   pwm.c
 * Author: Maged El Habiby, Mazen El Habiby, Marshal Kalynchuk
 * Group 20
 * Created on December 3, 2023, 5:38 PM
 */

#include "xc.h"
#include "pwm.h"
#include <p24F16KA101.h>

#define MAX_PWM 0xFFFF
#define MIN_PWM 0x0000

// Initialize PWM module
void PWM_Init() {
    // Set the PWM period using OCxR register
    OC1R = 0x0000; // Set the initial duty cycle
    OC1RS = 0x0000; // Set the period
    
    // Configure OC1 Control Register (OC1CON)
    OC1CONbits.OCM = 0b110; // Set OC1 to PWM mode without fault pin enabled
    OC1CONbits.OCTSEL = 1; // Use Timer 3 as the clock source for OC1

    // Start Timer 3
    T3CONbits.TON = 1; // Turn on Timer 3
}

// Set PWM duty cycle
void PWM_SetDutyCycle(unsigned int duty) {
    if (duty <= MAX_PWM) {
        OC1RS = duty; // Set the duty cycle
    }
}
