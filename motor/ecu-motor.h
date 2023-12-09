/*
 * ecu_motor.h
 *
 *  Created on: Dec 8, 2023
 *      Author: engmu
 */

#ifndef INC_ECU_MOTOR_H_
#define INC_ECU_MOTOR_H_
/*  Section : includes   */
#include "stm32f1xx_hal.h"
#include "DWT_Delay.h"
/*	section : macros */
#define LEFT_PORT 0
#define RIGHT_PORT 1

#define PWM    0
#define ENABLE 1

#define RESERVED 0xFFF

#define CPU_FREQ 72000000
#define PWM_FREQ 1000.0
/*	section : user defined data types*/
typedef uint8_t std_return_type ;

typedef struct
{
	GPIO_TypeDef *ports       [2]  ;
	uint16_t      left_pins   [2]  ;
	uint16_t      right_pins  [2]  ;

}motor_t;

typedef enum {
	MOTOR_OK ,
	MOTOR_NOT_OK

}motor_status_t;

/*	section : functions declaration */
std_return_type ecu_motor_init 		 		 (const motor_t *motor  , uint8_t speed) ;
std_return_type ecu_motor_move_left  	     (const motor_t *motor) ;
std_return_type ecu_motor_move_right 		 (const motor_t *motor) ;
std_return_type ecu_motor_brake		 		 (const motor_t *motor) ;
std_return_type ecu_motor_off 				 (const motor_t *motor) ;
std_return_type ecu_motor_change_speed 		 (const motor_t *motor , uint8_t speed) ;


#endif /* INC_ECU_MOTOR_H_ */
