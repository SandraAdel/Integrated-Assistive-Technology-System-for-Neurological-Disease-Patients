
#ifndef LCD_H
#define LCD_H

/* LCD Modes */
#define LCD_8BIT_MODE 0
#define LCD_4BIT_MODE 1

/* User Input */
#define LCD_MODE LCD_4BIT_MODE

void LCD_Init(void);

void LCD_Open(void);
void LCD_Close(void);

void LCD_SendCommand(unsigned char Command);

void LCD_SendData(unsigned char Data);

void LCD_SetCursorAt(unsigned char x, unsigned char y);

void LCD_Print(const char * Str);

// For LCD_4BIT_MODE only
void LCD_SendNibble(unsigned char nibble);


#endif /* LCD_H */
