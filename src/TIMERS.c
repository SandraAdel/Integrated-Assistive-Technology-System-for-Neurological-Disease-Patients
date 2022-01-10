
#include "TIMERS.h"
#include "avr/io.h"
#include "avr/interrupt.h"
#include "SENSORS.h"
#include "DIO.h"
#include "LCD.h"
#include "util/delay.h"


unsigned char vibration_sensor_reading_counter = 0;
unsigned char vibration_sensor_time_counter = 0;
int water_sensor_reading;
unsigned char sound_sensor_reading_counter = 0;
unsigned char sound_sensor_time_counter = 0;

ISR (TIMER0_COMPA_vect)
{

  vibration_sensor_time_counter ++;

  if (vibration_sensor_time_counter == 15) {

    vibration_sensor_time_counter = 0;

    unsigned char measurement = Read_Vibration_Sensor();
    if (measurement == 1) {

        if (vibration_sensor_reading_counter < 8) {
            vibration_sensor_reading_counter ++;
        } 
    }
    else {

        if (vibration_sensor_reading_counter > 0) {
            vibration_sensor_reading_counter --;
        }
    }

    if (vibration_sensor_reading_counter >=3 ) {
       LCD_Print("Rest Your Hand!!");
       LCD_SendCommand(0x02);
       _delay_ms(220);
    }
    else if (vibration_sensor_reading_counter < 3) {
       LCD_Print("Safe To Use Hand");
       LCD_SendCommand(0x02);
    }

  }

}

ISR(ADC_vect) {
  
  water_sensor_reading = Read_Water_Sensor();
  ADCSRA|=(1<<ADSC); 

}

ISR (TIMER1_COMPA_vect) {

    if (water_sensor_reading <= 500) { 

        DIO_WritePin('C', 3, 1);
        _delay_ms(185);
        DIO_WritePin('C', 3, 0);

    }
    else if (water_sensor_reading > 500)
    { 
        DIO_WritePin('C', 3, 0);
    }

}

ISR (TIMER2_COMPA_vect)
{

  sound_sensor_time_counter ++;

  if (sound_sensor_time_counter == 19) {

    sound_sensor_time_counter = 0;

    unsigned char measurement = Read_Sound_Sensor();
    if (measurement == 1) {

        if (sound_sensor_reading_counter < 11) {
            sound_sensor_reading_counter ++;
        } 
    }
    else {

        if (sound_sensor_reading_counter > 0) {
            sound_sensor_reading_counter --;
        }
    }

    if (sound_sensor_reading_counter >=3 ) {
       DIO_WritePin('C', 5, 1);              // turn on green LED
       DIO_WritePin('C', 4, 0);              // turn off red LED
        _delay_ms(750);
    }
    else if (sound_sensor_reading_counter <3 ) {
       DIO_WritePin('C', 4, 1);              // turn on red LED
       DIO_WritePin('C', 5, 0);              // turn off green LED
    }

  }

}

void Timer0_CTC_Init() {

    OCR0A = 0XC3; // decimal: 61 --> 62 clk (CHANGE ACCORDING TO NEED)
    TCCR0A |= (1<< WGM01); // Setting CTC mode only
    TIMSK0 |= (1<<OCIE0A); // Enable interrupt flag

}

void Start_Timer0() {

    TCCR0B |=  (1<<CS00) | (1<<CS02) ; // Set prescaler (clk/1024)
}

void Stop_Timer0() {

    TCCR0B &= ~( (1<<CS00) | (1<<CS01) | (1<<CS02) ); // Clear prescaler

}

void Timer1_CTC_Init() {

    OCR1A = 0XC3; // decimal: 61 --> 62 clk (CHANGE ACCORDING TO NEED)
    TCCR1B |= (1<< WGM12); // Setting CTC mode only
    TIMSK1 |= (1<<OCIE1A); // Enable interrupt flag

}

void Start_Timer1() {

    TCCR1B |=  (1<<CS10) | (1<<CS12) ; // Set prescaler (clk/1024)

}

void Stop_Timer1() {

    TCCR1B &= ~( (1<<CS10) | (1<<CS11) | (1<<CS12) ); // Clear prescaler

}

void Timer2_CTC_Init() {

    OCR2A = 0X5D; // decimal: 102 --> 103 clk (CHANGE ACCORDING TO NEED)
    TCCR2A |= (1<< WGM21); // Setting CTC mode only
    TIMSK2 |= (1<<OCIE2A); // Enable interrupt flag

}

void Start_Timer2() {

    TCCR2B |=  ( (1<<CS20) | (1<<CS21) | (1<<CS22) ) ; // Set prescaler (clk/1024)

}

void Stop_Timer2() {

    TCCR2B &= ~( (1<<CS20) | (1<<CS21) | (1<<CS22) ); // Clear prescaler

}