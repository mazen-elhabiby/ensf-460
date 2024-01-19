/*
 * File:   display.c
 * Author: Maged El Habiby, Marshal Kalynchuk, Mazen El Habiby
 * Group: Group 20
 * Created on November 4, 2023, 12:10 PM
 */

#include "xc.h"
//#include <p24fxxxx.h>
#include <p24F16KA101.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include "UART2.h"
#include "ADC.h"
#include "display.h"

void display(uint16_t ADC_value) {
    XmitUART2('\r', 1);
    XmitUART2('\n', 1);
    Disp2Hex(ADC_value);
}
