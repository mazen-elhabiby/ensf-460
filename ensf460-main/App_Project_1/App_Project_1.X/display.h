/*
 * File:   display.h
 * Author: Maged El Habiby, Mazen El Habiby, Marshal Kalynchuk
 * Group 20
 * Created on November 05, 2023, 2:10 PM
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#ifdef __cplusplus
extern "C" {
#endif

// Function to initialize the display
void InitDisplay(void);

// Function to clear the display
void ClearDisplay(void);

// Function to display an alarm message
void DisplayAlarm(void);

// Function to display timer
void DisplayTimerCount(unsigned int minutes, unsigned int seconds);

// Function to update the timer display with the current timer values.
void UpdateTimerDisplay(unsigned int minutes, unsigned int seconds);

// Function to display a message indicating the timer has been reset.
void DisplayResetMessage(void);

#ifdef __cplusplus
}
#endif

#endif /* DISPLAY_H */
