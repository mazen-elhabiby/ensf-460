/*
 * File:   display.c
 * Author: Maged El Habiby, Mazen El Habiby, Marshal Kalynchuk
 * Group 20
 * Created on November 05, 2023, 2:10 PM
 */


#include "xc.h"
#include "UART2.h" 
#include <stdio.h>

// Function to initialize the display
void InitDisplay(void) {
    InitUART2();  // Calls the UART initialization function.
}

// Function to clear the display
void ClearDisplay(void) {
    char *clear = "\033[2J\033[H"; // ANSI CLear Screen Code
    Disp2String(clear);
}

// Function to display an alarm message
void DisplayAlarm(void) {
    ClearDisplay();
    char *alarmMsg = "00m : 00s -- ALARM";
    Disp2String(alarmMsg);
}

//function to display timer
void DisplayTimerCount(unsigned int minutes, unsigned int seconds) {
    Disp2Dec(minutes);
    Disp2String("m : ");
    Disp2Dec(seconds);
    XmitUART2('s', 1);
}

// Function to update the timer display with the current timer values.
void UpdateTimerDisplay(unsigned int minutes, unsigned int seconds) {
    ClearDisplay();                       // Clear the terminal screen
    DisplayTimerCount(minutes, seconds); // Display the current timer count
}

// Function to display a message indicating the timer has been reset.
void DisplayResetMessage(void) {
    ClearDisplay();                     // Clear the terminal screen
    char *resetMsg = "00m : 00s";       // The reset Message
    Disp2String(resetMsg);              // Display Message
}