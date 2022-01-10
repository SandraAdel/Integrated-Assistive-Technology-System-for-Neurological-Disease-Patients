
#include "DIO.h"
#include "util/delay.h"
#include "KEYPAD.h"
#include "LCD.h"


#define KEYPAD_COLS 'B'
#define KEYPAD_ROWS 'D'
#define ROW1 2  
#define ROW2 3  
#define COL1 3 
#define COL2 4 
#define COL3 5 
#define COL4 6 

unsigned char row_location, column_location = 'N';
unsigned char look_up_table[2][4] = { {'1', '2', '3', 'A'},
                                      {'4', '5', '6', 'B'} };

void Keypad_Init(void) {

    for(unsigned char i=COL1; i<=COL4; i++)
    {
        DIO_SetPinDirection(KEYPAD_COLS, i, OUTPUT);
    }

    for(unsigned char i=ROW1; i<=ROW2; i++)
    {
        DIO_SetPinDirection(KEYPAD_ROWS, i, INPUT);
        DIO_WritePin(KEYPAD_ROWS, i, 1);             // Activate Pull-Up Resistor
    }
}

unsigned char Keypad_GetKey(void) {

    unsigned char key; 

    for (unsigned char i=COL1; i<=COL4; i++) { 

        DIO_WritePin(KEYPAD_COLS, i, 0); 
    }  

    if (column_location == 'N') {
        DIO_WritePin(KEYPAD_COLS, COL1, 0);        //ground column 0
        DIO_WritePin(KEYPAD_COLS, COL2, 1);
        DIO_WritePin(KEYPAD_COLS, COL3, 1);
        DIO_WritePin(KEYPAD_COLS, COL4, 1);
        row_location = (DIO_ReadPort(KEYPAD_ROWS) & ((1<<ROW1)|(1<<ROW2)));
        if(row_location != ((1<<ROW1)|(1<<ROW2)))
        {
            column_location = 0;
        }
    }

    if (column_location == 'N') {
        DIO_WritePin(KEYPAD_COLS, COL1, 1);
        DIO_WritePin(KEYPAD_COLS, COL2, 0);         //ground column 1
        DIO_WritePin(KEYPAD_COLS, COL3, 1);
        DIO_WritePin(KEYPAD_COLS, COL4, 1);
        row_location = (DIO_ReadPort(KEYPAD_ROWS) & ((1<<ROW1)|(1<<ROW2)));
        if(row_location != ((1<<ROW1)|(1<<ROW2)))
        {
            column_location = 1;
        }
    }

    if (column_location == 'N') {
        DIO_WritePin(KEYPAD_COLS, COL1, 1);
        DIO_WritePin(KEYPAD_COLS, COL2, 1);
        DIO_WritePin(KEYPAD_COLS, COL3, 0);        //ground column 2
        DIO_WritePin(KEYPAD_COLS, COL4, 1);
        row_location = (DIO_ReadPort(KEYPAD_ROWS) & ((1<<ROW1)|(1<<ROW2)));
        if(row_location != ((1<<ROW1)|(1<<ROW2)))
        {
            column_location = 2;
        }
    }

    if (column_location == 'N') {
        DIO_WritePin(KEYPAD_COLS, COL1, 1);
        DIO_WritePin(KEYPAD_COLS, COL2, 1);
        DIO_WritePin(KEYPAD_COLS, COL3, 1);        
        DIO_WritePin(KEYPAD_COLS, COL4, 0);       //ground column 3
        row_location = (DIO_ReadPort(KEYPAD_ROWS) & ((1<<ROW1)|(1<<ROW2)));
        if(row_location != ((1<<ROW1)|(1<<ROW2)))
        {
            column_location = 3;
        }
    }

    if(row_location == (1<<ROW2))
    key = look_up_table[0][column_location];

    else if(row_location == (1<<ROW1))
    key = look_up_table[1][column_location];

    for (unsigned char i=COL1; i<=COL4; i++) { 

        DIO_WritePin(KEYPAD_COLS, i, 0); 
    } 
    column_location = 'N';

    return key;

}
