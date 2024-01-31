#include "lcd.h"
#include "Ultrasonic.h"
#include <avr/io.h> 

int main(void)
{
    uint16 distance=0;
    
	SREG |= (1<<7);

    LCD_init();
    LCD_displayString(  "Distance= 000cm");

    Ultrasonic_Init();

    for (;;) {
        distance = Ultrasonic_readDistance();
        LCD_moveCursor(0, 10);
        LCD_intgerToString(distance);

        if (distance<100) {
            LCD_displayCharacter(' ');
        }
    }
    
}