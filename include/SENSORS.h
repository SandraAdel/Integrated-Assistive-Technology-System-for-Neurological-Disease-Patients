
#ifndef SENSORS_H
#define SENSORS_H

void Vibration_Sensor_Init();
unsigned char Read_Vibration_Sensor();

void Water_Sensor_Init();
int Read_Water_Sensor();

void Sound_Sensor_Init();
unsigned char Read_Sound_Sensor();
void Open_LEDs();
void Close_LEDs();

void Enable_Modules_Control();  // Through external interrupts


#endif /* SENSORS_H */