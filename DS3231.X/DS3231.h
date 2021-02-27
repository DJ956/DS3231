/* 
 * File:   DS3231.h
 * Author: dexte
 *
 * Created on October 31, 2020, 10:08 AM
 */

#ifndef DS3231_H
#define	DS3231_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <stdint.h>
    
#define RTC_ADR 0xD0
    
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
uint8_t read_(uint8_t address);
uint8_t bcd_2_decimal(uint8_t number);
uint8_t decimal_2_bcd(uint8_t number);


#ifdef	__cplusplus
}
#endif

#endif	/* DS3231_H */

