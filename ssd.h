#ifndef SSD_H
#define SSD_H

#include <xc.h>

/* Seven segment codes - common cathode */

#define ZERO    0x3F
#define ONE     0x06
#define TWO     0x5B
#define THREE   0x4F
#define FOUR    0x66
#define FIVE    0x6D
#define SIX     0x7D
#define SEVEN   0x07
#define EIGHT   0x7F
#define NINE    0x6F

#define SSD_DATA_PORT      PORTD
#define SSD_DATA_TRIS      TRISD

#define SSD_CTRL_PORT      PORTA
#define SSD_CTRL_TRIS      TRISA

#define SSD_CTRL_MASK      0x3C

void init_ssd(void);
void display(unsigned char *ssd);
unsigned char read_dkp(unsigned char mode);
#endif