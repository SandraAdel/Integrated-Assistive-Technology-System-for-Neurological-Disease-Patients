
#include "SENSORS.h"
#include "avr/io.h"
#include "DIO.h"
#include "avr/interrupt.h"
#include "LCD.h"
#include "util/delay.h"
#include "KEYPAD.h"
#include "TIMERS.h"
#include "ADC.h"


ISR (INT0_vect)
{
    unsigned char key = Keypad_GetKey();
    if (key == '1') {
        LCD_Open();
        Start_Timer0();
        return;
    }
    if (key == '2') {
        ADC_Open();
        Start_Timer1();
        return;
    }
    if (key == '3') {
        Open_LEDs();
        Start_Timer2();
        return;
    }
}

ISR (INT1_vect)
{
    unsigned char key = Keypad_GetKey();
    if (key == '4') {
        Stop_Timer0();
        LCD_Close();
        return;
    }
    if (key == '5') {
        Stop_Timer1();
        ADC_Close();
        return;
    }
    if (key == '6') {
        Stop_Timer2();
        Close_LEDs();
        return;

    }   
}

void Vibration_Sensor_Init() {

    DIO_SetPinDirection('C', 1, INPUT);
    LCD_Init();
    LCD_SetCursorAt(1,1);

}

unsigned char Read_Vibration_Sensor() {

   unsigned char measurement = DIO_ReadPin('C', 1);
   return measurement;

}

void Water_Sensor_Init() {

    DIO_SetPinDirection('C', 0, INPUT);
    DIO_SetPinDirection('C', 3, OUTPUT);
    ADC_Init();
    ADC_Open();
    ADC_SelectChannel(0);
    ADCSRA |= (1 << 6);

}

int Read_Water_Sensor() {
    
    int measurement = (float)(( ADC * (5.0/1024) ) / (5.0/1023) );
    return measurement;

}

void Sound_Sensor_Init() {

    DIO_SetPinDirection('C', 2, INPUT);
    Open_LEDs();

}

unsigned char Read_Sound_Sensor() {

   unsigned char measurement = DIO_ReadPin('C', 2);
   return measurement;

}

void Open_LEDs() {

    DIO_SetPinDirection('C', 4, OUTPUT);
    DIO_SetPinDirection('C', 5, OUTPUT);

}

void Close_LEDs() {

    DIO_SetPinDirection('C', 4, INPUT);
    DIO_SetPinDirection('C', 5, INPUT); 

}

void Enable_Modules_Control() {

    EICRA |= ( (1<<ISC01)|(1<<ISC11) );
    EIMSK |= ( (1<<INT0)|(1<<INT1) );

}