
#include "LCD.h"

#include "DIO.h"
#include "util/delay.h"

#define LCD_DPRT 'D'  // LCD DATA PORT
#define LCD_CPRT 'B'  // LCD COMMANDS PORT
#define LCD_RS 0      // LCD RS
#define LCD_RW 1      // LCD RW
#define LCD_EN 2      // LCD EN

static void LCD_LatchSignal(void);

void LCD_Init() {
    #if LCD_MODE == LCD_8BIT_MODE

        DIO_SetPortDirection(LCD_DPRT, OUTPUT);
        DIO_SetPinDirection(LCD_CPRT, LCD_RS, OUTPUT);
        DIO_SetPinDirection(LCD_CPRT, LCD_RW, OUTPUT);
        DIO_SetPinDirection(LCD_CPRT, LCD_EN, OUTPUT);
        LCD_SendCommand(0x38);
        LCD_SendCommand(0x0E);
        LCD_SendCommand(0x01);
        _delay_ms(2);

    #elif LCD_MODE == LCD_4BIT_MODE

        /// TODO:
        // Initialization of LCD_DPRT Direction (Pins D4-D7)
        unsigned char i = 4;
        for (i=4; i<=7; i++)
        {
            DIO_SetPinDirection(LCD_DPRT, i, OUTPUT);
        }
        // Intialization of Control Pins
        DIO_SetPinDirection(LCD_CPRT, LCD_RS, OUTPUT);
        DIO_SetPinDirection(LCD_CPRT, LCD_RW, OUTPUT);
        DIO_SetPinDirection(LCD_CPRT, LCD_EN, OUTPUT);
        // Sending Commands (0x33, 0x32, 0x28)
        LCD_SendCommand(0x33);
        //_delay_ms(2);
        LCD_SendCommand(0x32);
       // _delay_ms(2);
        LCD_SendCommand(0x28);
        //_delay_ms(2);
        LCD_SendCommand(0x0E);
       // _delay_ms(2);
        LCD_SendCommand(0x01);
        //_delay_ms(2);

    #else
        #error Please Select The Correct Mode of LCD
    #endif
}

void LCD_Close(void) {

    LCD_SendCommand(0x08);
    LCD_SendCommand(0x01);
    _delay_ms(2);

}

void LCD_Open(void) {

    LCD_SendCommand(0x0E);
    _delay_ms(2);

}

void LCD_SendCommand(unsigned char Command) {
    #if LCD_MODE == LCD_8BIT_MODE

        DIO_WritePort(LCD_DPRT, Command);
        DIO_WritePin(LCD_CPRT, LCD_RS, 0);
        DIO_WritePin(LCD_CPRT, LCD_RW, 0);
        LCD_LatchSignal();

    #elif LCD_MODE == LCD_4BIT_MODE

        /// TODO:
       DIO_WritePin(LCD_CPRT, LCD_RS, 0);
       DIO_WritePin(LCD_CPRT, LCD_RW, 0);

       unsigned char high_nibble =  (Command & 0xF0) >> 4;
       unsigned char low_nibble =  (Command & 0x0F) ;

        LCD_SendNibble(high_nibble);
        LCD_SendNibble(low_nibble);

    #else
        #error Please Select The Correct Mode of LCD
    #endif
}

void LCD_SendData(unsigned char Data) {
    #if LCD_MODE == LCD_8BIT_MODE

        DIO_WritePort(LCD_DPRT, Data);
        DIO_WritePin(LCD_CPRT, LCD_RS, 1);
        DIO_WritePin(LCD_CPRT, LCD_RW, 0);
        LCD_LatchSignal();

    #elif LCD_MODE == LCD_4BIT_MODE

        /// TODO:
       DIO_WritePin(LCD_CPRT, LCD_RS, 1);
       DIO_WritePin(LCD_CPRT, LCD_RW, 0);

       unsigned char high_nibble =  (Data & 0xF0) >> 4;
       unsigned char low_nibble =  (Data & 0x0F) ;

        LCD_SendNibble(high_nibble);
        LCD_SendNibble(low_nibble);

    #else
        #error Please Select The Correct Mode of LCD
    #endif
}

void LCD_SetCursorAt(unsigned char x, unsigned char y) {

  /// TODO: 
    unsigned char first_char_address [] = {0x80, 0xC0};
    unsigned char position_command = first_char_address[x-1] + y - 1;

    LCD_SendCommand(position_command);
    _delay_ms(2);

}

void LCD_Print(const char* Str) {

  /// TODO: 
    unsigned char i = 0;
    while( Str[i]!=0 )
    {   
        LCD_SendData( Str[i] );
        _delay_ms(2);
        i++ ;
    }

}

static void LCD_LatchSignal(void) {
  DIO_WritePin(LCD_CPRT, LCD_EN, 1);
  _delay_us(1);
  DIO_WritePin(LCD_CPRT, LCD_EN, 0);
  _delay_us(100);
}

void LCD_SendNibble(unsigned char nibble) {

    unsigned char i = 0;
    unsigned char bit;
    for (i=0; i<=3; i++)
    {
        bit = (nibble & (1<<i)) >> i;
        DIO_WritePin(LCD_DPRT, i+4, bit);
    }


    LCD_LatchSignal();
    _delay_us(100);

}