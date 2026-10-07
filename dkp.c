#include "dkp.h"

void init_dkp(void)
{
    /*
     * RB0 = SW1 = INPUT
     * RB1 = SW2 = INPUT
     */
    TRISB |= 0x03;
}


unsigned char read_dkp(unsigned char mode)
{
    static unsigned char once = 1;

    unsigned char key;

    /*
     * Read RB0 and RB1
     */
    key = PORTB & 0x03;

    /*
     * LEVEL MODE
     *
     * Return switch continuously
     * while it is pressed.
     */
    if (mode == LEVEL)
    {
        /*
         * SW1 pressed
         *
         * Active LOW:
         * RB0 = 0
         */
        if ((key & 0x01) == 0)
        {
            return SW1;
        }

        /*
         * SW2 pressed
         *
         * RB1 = 0
         */
        if ((key & 0x02) == 0)
        {
            return SW2;
        }
    }

    /*
     * EDGE MODE
     *
     * Return only once for each press.
     */
    else if (mode == EDGE)
    {
        /*
         * SW1 pressed
         */
        if ((key & 0x01) == 0 && once)
        {
            once = 0;
            return SW1;
        }

        /*
         * SW2 pressed
         */
        if ((key & 0x02) == 0 && once)
        {
            once = 0;
            return SW2;
        }

        /*
         * No switch pressed.
         *
         * Allow next press.
         */
        if ((key & 0x03) == 0x03)
        {
            once = 1;
        }
    }

    /*
     * No key
     */
    return 0xFF;
}