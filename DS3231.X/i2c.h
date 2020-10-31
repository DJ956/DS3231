#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  

void i2c_wait();
void i2c_start();
void i2c_stop();
void i2c_repeated_start();
void write_byte(uint8_t data);
void i2c_cmd(uint8_t address, uint8_t reg, uint8_t data);
uint8_t recv_byte(uint8_t ack);
void recv_data(uint8_t address, uint8_t *buffer, uint8_t cnt);

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

