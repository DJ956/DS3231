
// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  

void bit_delay();
void start();
void stop();
void set_brigthness(uint8_t brightness, uint8_t on);
uint8_t write_data(uint8_t b);
void set_segments(const uint8_t segments[], uint8_t length, uint8_t pos);
void clear();
uint8_t encode_dig(uint8_t digit);

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

