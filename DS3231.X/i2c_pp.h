/* 
 * File:   i2c.h
 * Author: Pete
 *
 * Created on March 13, 2019, 9:36 PM
 */

#ifndef I2C_PP_H
#define	I2C_PP_H

#include <xc.h>
#include <stdint.h>

// I2C functions for MSSP1 module
void bit_delay();
void start();
void stop();
void set_brigthness(uint8_t brightness, uint8_t on);
uint8_t write_byte(uint8_t b);
void set_segments(const uint8_t segments[], uint8_t length, uint8_t pos);
void clear();
uint8_t encode_digit(uint8_t digit);



#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_PP_H */

