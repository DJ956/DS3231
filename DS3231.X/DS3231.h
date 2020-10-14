/* 
 * File:   DS3231.h
 * Author: dexte
 *
 * Created on October 13, 2020, 11:45 PM
 */

#ifndef DS3231_H
#define DS3231_H

#include <xc.h>
#include <stdint.h>
    
#define RTC_ADR 0x68

struct Date{
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
};

void write_date(struct Date *date);

void read_date(struct Date *date);

void i2c_init(uint8_t clk_freq);
void i2c_start();
void i2c_stop();
void i2c_repeated_start();
void i2c_write(uint8_t data);
uint8_t i2c_read(uint8_t ack);

uint8_t bcd_2_decimal(uint8_t number);
uint8_t decimal_2_bcd(uint8_t number);

void rtc_display(struct Date *date);

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	__cplusplus
}
#endif

#endif
