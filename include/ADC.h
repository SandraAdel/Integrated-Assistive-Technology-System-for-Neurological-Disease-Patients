
#ifndef ADC_H
#define ADC_H

void ADC_Init(void);

void ADC_Open(void);
void ADC_Close(void);

void ADC_SelectChannel(unsigned char ChannelNum);

unsigned short ADC_ReadChannel(unsigned char ChannelNum);


#endif /* ADC_H */
