/**
 * Copyright (C) PlatformIO <contact@platformio.org>
 * See LICENSE for details.
 */

#include "ADC.h"
#include "LCD.h"
#include "DIO.h"
#include "TIMERS.h"
#include "util/delay.h"
#include <stdio.h>
#include "avr/interrupt.h"
#include "avr/io.h"
#include "SENSORS.h"
#include "KEYPAD.h"


int main(void) {


  Vibration_Sensor_Init();
  Water_Sensor_Init();
  Sound_Sensor_Init();
  sei ();

  Keypad_Init();
  Enable_Modules_Control();

  Timer0_CTC_Init();
  Start_Timer0();

  Timer1_CTC_Init();
  Start_Timer1();

  Timer2_CTC_Init();
  Start_Timer2();

  while(1) {}


  return 0;
}
