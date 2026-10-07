#include "ssd.h"

void init_ssd(void)
{
  TRISD = 0;
  TRISA = TRISA&0xC3;
}

void display(unsigned char *ssd)
{
    for (int i = 0; i < 4; i++)
    {
       PORTD = ssd[i];                    
       PORTA = (PORTA&0xC3)|4<<i;
       for(unsigned int i =100;i--;);
    }
}

