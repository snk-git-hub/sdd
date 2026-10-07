#ifndef DKP_H
#define DKP_H

#include <xc.h>

#define SW1     0x01
#define SW2     0x02

#define LEVEL   0
#define EDGE    1

void init_dkp(void);
unsigned char read_dkp(unsigned char mode);

#endif