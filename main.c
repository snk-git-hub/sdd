#pragma config FOSC = XT
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

#include <xc.h>
#include "ssd.h"
#include "dkp.h"


void main(void)
{
    unsigned char digit[10] =
    {
        ZERO, ONE, TWO, THREE, FOUR,
        FIVE, SIX, SEVEN, EIGHT, NINE
    };

    unsigned char ssd[4];

    unsigned char i;
    unsigned char j;
    unsigned char k;
    unsigned char l;

    unsigned char key;
    unsigned int delay = 0;

    /*
     * Read saved count from EEPROM
     */
    i = eeprom_read(0x00);
    j = eeprom_read(0x01);
    k = eeprom_read(0x02);
    l = eeprom_read(0x03);

    /*
     * EEPROM safety check
     */
    if (i > 9)
        i = 0;

    if (j > 9)
        j = 0;

    if (k > 9)
        k = 0;

    if (l > 9)
        l = 0;

    init_ssd();
    init_dkp();

    while (1)
    {
        /*
         * Read keypad
         */
        key = read_dkp(EDGE);

        /*
         * SW1 = SAVE
         */
        if (key == SW1)
        {
            eeprom_write(0x00, i);
            eeprom_write(0x01, j);
            eeprom_write(0x02, k);
            eeprom_write(0x03, l);
        }

        /*
         * SW2 = RESET
         */
        else if (key == SW2)
        {
            i = 0;
            j = 0;
            k = 0;
            l = 0;

            eeprom_write(0x00, 0);
            eeprom_write(0x01, 0);
            eeprom_write(0x02, 0);
            eeprom_write(0x03, 0);
        }

        /*
         * Prepare SSD
         *
         * l = thousands
         * k = hundreds
         * j = tens
         * i = units
         */
        ssd[0] = digit[l];
        ssd[1] = digit[k];
        ssd[2] = digit[j];
        ssd[3] = digit[i];

        /*
         * Counter speed
         */
        if (delay++ == 200)
        {
            delay = 0;

            i++;

            if (i == 10)
            {
                i = 0;
                j++;

                if (j == 10)
                {
                    j = 0;
                    k++;

                    if (k == 10)
                    {
                        k = 0;
                        l++;

                        if (l == 10)
                        {
                            l = 0;
                        }
                    }
                }
            }
        }

        /*
         * Display
         */
        display(ssd);
    }
}