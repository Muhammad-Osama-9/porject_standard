/*
 * ecu_motor.c
 *
 *  Created on: Dec 8, 2023
 *      Author: engmu
 */

#include "ecu_motor.h"


const uint32_t porta_timer_channels [] =
{
		TIM_CHANNEL_1 , TIM_CHANNEL_2 , TIM_CHANNEL_3,TIM_CHANNEL_4,  // TIM2 Pins  0 , 1 ,2 , 3
		RESERVED , RESERVED ,   									  // RESERVED PINS 	4 , 5
		TIM_CHANNEL_1 , TIM_CHANNEL_2 ,								  // TIM3 Pins 6 ,7
		TIM_CHANNEL_1 , TIM_CHANNEL_2 , TIM_CHANNEL_3,TIM_CHANNEL_4   // TIM1 Pins 8,9,10,11

};

const uint32_t portb_timer_channels [] =
{
		 TIM_CHANNEL_3,TIM_CHANNEL_4,  						   		  // TIM3 Pins  0 , 1
		 RESERVED , RESERVED ,  RESERVED , RESERVED ,  		          // RESERVED PINS 	2,3,4,5
		 TIM_CHANNEL_1 , TIM_CHANNEL_2 , TIM_CHANNEL_3,TIM_CHANNEL_4   // TIM4 Pins 6,7,8,9

};

static uint8_t  log2fun (uint32_t num  )
{
	uint8_t res = 0 ;
	while (num )
	{
		res++ ;
		num/=2 ;
	}
	res -- ;

	return res ;
}

static void timers_init (const motor_t *motor )
{
	/*	declaration  variables   */

    TIM_HandleTypeDef htim;
    uint32_t PSC_Value = 0;
    uint32_t ARR_Value = 0;
    uint32_t tim_channel = 0  ;
	DWT_Delay_Init();

	/*Enable RCC Port Clocks and Timers */
	if (motor->ports[LEFT_PORT] == GPIOA )
	{
		/* Enable RCC Clock */

		__HAL_RCC_GPIOA_CLK_ENABLE() ;

		/*	Enable Timer Corresponding  to its pin 	*/

		if (   motor->left_pins[PWM] == GPIO_PIN_0
			|| motor->left_pins[PWM] == GPIO_PIN_1
			|| motor->left_pins[PWM] == GPIO_PIN_2
			|| motor->left_pins[PWM] == GPIO_PIN_3 )
		{
				   __HAL_RCC_TIM2_CLK_ENABLE();


				   htim.Instance = TIM2 ;

		}else if ( motor->left_pins[PWM] == GPIO_PIN_6
				|| motor->left_pins[PWM] == GPIO_PIN_7 )
			{
					__HAL_RCC_TIM3_CLK_ENABLE();

					   htim.Instance = TIM3 ;


		}else if ( motor->left_pins[PWM] == GPIO_PIN_8
				|| motor->left_pins[PWM] == GPIO_PIN_9
				|| motor->left_pins[PWM] == GPIO_PIN_10
				|| motor->left_pins[PWM] == GPIO_PIN_11 )

		 	{
					__HAL_RCC_TIM1_CLK_ENABLE();

					   htim.Instance = TIM1 ;

			}


		tim_channel = porta_timer_channels[log2fun(motor->left_pins[PWM])] ;

	}
	else if (motor->ports[LEFT_PORT] == GPIOB)
	{
		/* Enable RCC Clock */
		__HAL_RCC_GPIOB_CLK_ENABLE() ;

		/*	Enable Timer Corresponding  to its pin 	*/

		 if (motor->left_pins[PWM] == GPIO_PIN_6
		  || motor->left_pins[PWM] == GPIO_PIN_7
		  || motor->left_pins[PWM] == GPIO_PIN_8
		  || motor->left_pins[PWM] == GPIO_PIN_9 )
		 {
			 __HAL_RCC_TIM4_CLK_ENABLE() ;

			 	 htim.Instance = TIM4 ;

		 }
		 else if (	 motor->left_pins[PWM] == GPIO_PIN_0
				  || motor->left_pins[PWM] == GPIO_PIN_1  )
		 {
			 __HAL_RCC_TIM3_CLK_ENABLE() ;

			   htim.Instance = TIM3 ;

		 }

	tim_channel = portb_timer_channels[log2fun(motor->left_pins[PWM])] ;


	}

	else {/*Do Nothing*/}


	if (motor->ports[RIGHT_PORT] == GPIOA)
	{

		__HAL_RCC_GPIOA_CLK_ENABLE() ;
		/* Know Each Timer according to pin to Enable */

				if (   motor->left_pins[PWM] == GPIO_PIN_0
					|| motor->left_pins[PWM] == GPIO_PIN_1
					|| motor->left_pins[PWM] == GPIO_PIN_2
					|| motor->left_pins[PWM] == GPIO_PIN_3 )
				{
						   __HAL_RCC_TIM2_CLK_ENABLE();

						    htim.Instance = TIM2 ;


				}else if ( motor->left_pins[PWM] == GPIO_PIN_6
						|| motor->left_pins[PWM] == GPIO_PIN_7 )
					{
							__HAL_RCC_TIM3_CLK_ENABLE();

							   htim.Instance = TIM3 ;


				}else if ( motor->left_pins[PWM] == GPIO_PIN_8
						|| motor->left_pins[PWM] == GPIO_PIN_9
						|| motor->left_pins[PWM] == GPIO_PIN_10
						|| motor->left_pins[PWM] == GPIO_PIN_11 )

				 	{
							__HAL_RCC_TIM1_CLK_ENABLE();

							   htim.Instance = TIM1 ;

					}

		tim_channel = porta_timer_channels[log2fun(motor->right_pins[PWM])] ;


	}
	else if (motor->ports[RIGHT_PORT] == GPIOB)
	{
		/* Enable RCC Clock */
				__HAL_RCC_GPIOB_CLK_ENABLE() ;

				/*	Enable Timer Corresponding  to its pin 	*/

				 if (motor->left_pins[PWM] == GPIO_PIN_6
				  || motor->left_pins[PWM] == GPIO_PIN_7
				  || motor->left_pins[PWM] == GPIO_PIN_8
				  || motor->left_pins[PWM] == GPIO_PIN_9 )
				 {
					 __HAL_RCC_TIM4_CLK_ENABLE() ;

					   htim.Instance = TIM4 ;

				 }
				 else if (	 motor->left_pins[PWM] == GPIO_PIN_0
						  || motor->left_pins[PWM] == GPIO_PIN_1  )
				 {
					 __HAL_RCC_TIM3_CLK_ENABLE() ;

					   htim.Instance = TIM3 ;

				 }

				 /*	Determine the channel type from its port and pin  */

		tim_channel = portb_timer_channels[log2fun(motor->right_pins[PWM])] ;


	}
	else {/*Do Nothing */}

//-----------------------------------------------------------------//

		/*Calculate Prescaler and F_PWM*/

	
	PSC_Value = (uint32_t) (CPU_FREQ / 3276800.0);
	ARR_Value = (uint32_t) ((CPU_FREQ / (PWM_FREQ*(PSC_Value+1.0)))-1.0);


	/*	put values in htim object */
	htim.Init.Prescaler = PSC_Value ;
	htim.Init.Period = ARR_Value 	;
	htim.Init.CounterMode = TIM_COUNTERMODE_UP ;
	htim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	
	HAL_TIM_PWM_Init(&htim);
	HAL_TIM_PWM_Start(&htim,tim_channel );


}



std_return_type ecu_motor_init 	 (const motor_t *motor  , uint8_t speed)
{
	uint8_t ret = MOTOR_NOT_OK;
	if(NULL == motor )
	{
		ret = MOTOR_NOT_OK ;
	}
	else {
			/* Init Timers used in PWM */
		
		timers_init(motor) ;

		/*Make GPIO pin Objects */
			/* Right Pins 	*/
		GPIO_InitTypeDef right_enable_pin_obj = {
				.Pin = motor->right_pins[ENABLE],
				.Mode = GPIO_MODE_OUTPUT_PP,
				.Speed = GPIO_SPEED_FREQ_LOW
		};
		GPIO_InitTypeDef right_PWM_pin_obj = {
				.Pin = motor->right_pins[PWM],
				.Mode = GPIO_MODE_AF_PP,
				.Speed = GPIO_SPEED_FREQ_LOW
		};

			/* left  Pins 	*/
		GPIO_InitTypeDef left_enable_pin_obj = {
			.Pin = motor->left_pins[ENABLE],
			.Mode = GPIO_MODE_OUTPUT_PP,
			.Speed = GPIO_SPEED_FREQ_LOW
		};
		GPIO_InitTypeDef left_PWM_pin_obj = {
			.Pin = motor->left_pins[PWM],
			.Mode = GPIO_MODE_AF_PP,
			.Speed = GPIO_SPEED_FREQ_LOW
		};

		/* init left pins  in HAL layer */
		HAL_GPIO_Init(motor->ports[LEFT_PORT], &left_enable_pin_obj ) ;
		HAL_GPIO_Init(motor->ports[LEFT_PORT], &left_PWM_pin_obj ) ;

		/* init right pins  in HAL layer */
		HAL_GPIO_Init(motor->ports[RIGHT_PORT], &right_enable_pin_obj ) ;
		HAL_GPIO_Init(motor->ports[RIGHT_PORT], &right_PWM_pin_obj   ) ;

	}
	return ret ;
}
std_return_type ecu_motor_move_left  (const motor_t *motor)
{
	uint8_t ret = MOTOR_NOT_OK;
	if(NULL == motor )
	{
		ret = MOTOR_NOT_OK ;
	}
	else {

	}
	return ret ;

}
std_return_type ecu_motor_move_right (const motor_t *motor)
{
	uint8_t ret = MOTOR_NOT_OK;
	if(NULL == motor )
	{
		ret = MOTOR_NOT_OK ;
	}
	else {

	}
	return ret ;
}
std_return_type ecu_motor_brake	 (const motor_t *motor)
{
	uint8_t ret = MOTOR_NOT_OK;
	if(NULL == motor )
	{
		ret = MOTOR_NOT_OK ;
	}
	else {

	}
	return ret ;
}
std_return_type ecu_motor_off 	(const motor_t *motor)
{
	uint8_t ret = MOTOR_NOT_OK;
	if(NULL == motor )
	{
		ret = MOTOR_NOT_OK ;
	}
	else {

	}
	return ret ;


}

std_return_type ecu_motor_change_speed  (const motor_t *motor , uint8_t speed)
{
	uint8_t ret = MOTOR_NOT_OK;
	if(NULL == motor )
	{
		ret = MOTOR_NOT_OK ;
	}
	else {

	}
	return ret ;

}


