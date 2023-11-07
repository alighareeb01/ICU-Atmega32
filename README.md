# ATmega32 Duty Cycle Calculator

This project is designed for the ATmega32 microcontroller and aims to calculate the duty cycle of a PWM wave. The wave is generated using Timer0 in fast PWM mode and measured via the ICP1 pin of Timer1.

## Description

The code is set up to configure the I/O for PWM output and input capture, initialize peripherals, and continuously calculate the period, `T_on`, and duty cycle of the PWM signal. The results are displayed on an LCD.

## Features

- PWM wave generation using Timer0.
- Duty cycle measurement using Input Capture Interrupt (ICI) of Timer1.
- Real-time display of period, `T_on` time, and duty cycle percentage on an LCD.


## Drivers Used

- `DIO_MCAL_Interface.h` - Digital I/O interface
- `GIE_MCAL_Interface.h` - Global Interrupt Enable
- `TMR_MCAL_Interface.h` - Timers
- `LCD_HAL_Interface.h` - LCD Hardware Abstraction Layer

## How to Use

1. Connect OC0 pin directly to ICP1.
2. connect an oscilloscope to observe the input wave
3. Observe the period and duty cycle readings on the LCD display.
