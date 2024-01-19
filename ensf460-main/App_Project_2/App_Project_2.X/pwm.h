/* 
 * File:   pwm.h
 * Author: Maged El Habiby, Marshal Kalynchuk, Mazen El Habiby
 * Group: Group 20
 * Created on November 4, 2023
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  


void PWM_Init();
void PWM_SetDutyCycle(unsigned int  dutyCycle);


#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

