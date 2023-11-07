/*
 * main.c
 *
 *  Created on: Oct 3, 2023
 *      Author: Lenovo
 */


#include <util/delay.h>.
#include <avr/interrupt.h>


#define F_CPU 8000000UL
#include "../MCAL/DIO-DRIVER/DIO_MCAL_Interface.h"
#include "../MCAL/GIE-DRIVER/GIE_MCAL_Interface.h"
#include "../MCAL/EXTI-DRIVER/EXTI_MCAL_Interface.h"
#include "../MCAL/ADC-DRIVER/ADC_MCAL_Interface.h"
#include "../MCAL/TMR-DRIVER/TMR_MCAL_Interface.h"
#include "../MCAL/USART-DRIVER/USART_MCAL_Interface.h"

#include "../HAL/LCD-DRIVER/LCD_HAL_Interface.h"
#include "../HAL/SEGMENT_DRIVER/SEG_HAL_Interface.h"
#include "../HAL/KPD_DRIVER/KPD_HAL_Interface.h"
#include "../HAL/LM_SENSOR-DIRVER/LM_HAL_Interface.h"
#include "../HAL/STEPPER_MOTOR-DRIVER/STEP_HAL_Interface.h"

#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"

void ICU_Task(void);

static u16 a = 0, b = 0, c = 0;
f32 DutyCycle = 0;
u16 Ton = 0;
u16 Peroid = 0;
int main() {
	//OC0 pin
	DIO_SetPinDirection(DIO_PORTB,DIO_PIN3,DIO_OUTPUT);
	//IC1 pin
	DIO_SetPinDirection(DIO_PORTD,DIO_PIN6,DIO_INPUT);
	//LCD init
	LCD_Init();
	//Timer 1 init
	TMR1_ICU_Init();
	TMR1_ICU_SetCallBack(&ICU_Task);
	//Timer 0 init
	TMR0_FastPWM(Inverted,100);
	GIE_Enable();



	while(1)
	{

		LCD_SendString("peroid:");
		LCD_SendNumber(Peroid);
//		LCD_SetPosition(0,8);
		_delay_ms(1000);
		LCD_ClearDisplay();
		LCD_SendString("Ton : ");
		LCD_SendNumber(Ton);
//		LCD_SetPosition(1,0);
		_delay_ms(1000);
		LCD_ClearDisplay();
		LCD_SendString("DC:");
		LCD_SendFloatNumber(DutyCycle*100,2);
		break;
//		_delay_ms(1000);
//		LCD_ClearDisplay();

	}
return 0;
}
void ICU_Task(void)
{
    static uint8_t count = 0 ;
    count++;
    // Handle the first edge (rising edge)
    if(count == 1)
    {
    	a = TMR1_ICU_GetReading();
    }
    else if(count == 2)
    {
       b = TMR1_ICU_GetReading();  // Capture the time of the falling edge
       Peroid = b - a;
       TMR1_ICU_Set_Edge(Falling);
    }
    else if(count == 3)
    {
    	c = TMR1_ICU_GetReading();
    	Ton = c - b;
    	count = 0;
    	TMR1_ICU_Set_Edge(Rising);
    	DutyCycle = (f32)Ton / (f32)Peroid;
    }
}
