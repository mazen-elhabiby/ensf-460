/* 
 * File:   IOs.h
 * Author: Maged El Habiby, Marshal Kalynchuk, Mazen El Habiby
 * Group: Group 20
 * Created on November 4, 2023
 */

#ifndef IOS_H
#define IOS_H

// Function Prototypes
void IOInit(void);
void IOCheck(void);
void enterIdleMode(void);
void updateLEDBrightness(void);
void handleBlinkingMode(void);
void display(uint16_t val);

#endif /* IOS_H */
