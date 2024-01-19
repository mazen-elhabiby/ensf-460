/*
 * File:   ADC.c
 * Author: Maged El Habiby, Marshal Kalynchuk, Mazen El Habiby
 * Group: Group 20
 * Created on November 4, 2023, 11:12 AM
 */


#include <p24F16KA101.h>
#include "ADC.h"

uint16_t readADC(void) {
    uint16_t ADC_value;
    
    /* ADC initialization */
    AD1CON1bits.ADON = 1; // Turn on ADC module
    AD1CON1bits.FORM = 0;
    AD1CON1bits.SSRC = 0b111;
    
    AD1CON2bits.VCFG = 0b000; // Select AVDD, AVSS as Vref
    
    AD1CON2bits.CSCNA = 0;
    AD1CON2bits.SMPI = 0b0000;
    AD1CON2bits.BUFM = 0; 
    AD1CON2bits.ALTS = 0; // Use MUX A
    
    AD1CON3bits.ADRC = 0; // Use system clock
    AD1CON3bits.ADCS = 0b11111;
    AD1CON3bits.SAMC = 0b11111; // Slowest sampling time
    
    // Setting analog inputs (MUX A)
    AD1CHSbits.CH0NA = 0; 
    AD1CHSbits.CH0SA = 5;
    
    // Setting input scan setup
    AD1PCFG = 0x0000;
    AD1CSSL = 0x0000;
            
    /* ADC Sampling and conversion */
    AD1CON1bits.SAMP = 1; // Start sampling
    while(AD1CON1bits.DONE == 0) {} // Until conversion is done
    ADC_value = ADC1BUF0;
    AD1CON1bits.SAMP = 0; // Stop sampling
    AD1CON1bits.ADON = 0;
    return (ADC_value);
}