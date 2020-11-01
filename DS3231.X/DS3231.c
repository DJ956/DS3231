/*
 * File:   DS3231.c
 * Author: dexte
 *
 * Created on October 14, 2020, 12:00 AM
 */

#include "i2c.h"
#include "DS3231.h"
#include <stdio.h>

#include "mcc_generated_files/mcc.h"


uint8_t bcd_2_decimal(uint8_t number){
    return ((number >> 4) * 10 + (number & 0x0F));
}

uint8_t decimal_2_bcd(uint8_t number){
    return (((number / 10) << 4) + (number % 10));
}

void write_date(struct Date *date){
    i2c_start();
    write_byte(RTC_ADR);
    write_byte(0x00);

    write_byte(decimal_2_bcd(date->sec));
    write_byte(decimal_2_bcd(date->min));
    write_byte(decimal_2_bcd(date->hour));
    write_byte(1);
    write_byte(decimal_2_bcd(date->day));
    write_byte(decimal_2_bcd(date->month));
    write_byte(decimal_2_bcd(date->year));
    i2c_stop();
    
    // printf("[W] year:%d, month:%d day:%d h:%d m:%d s:%d\r\n",
    //        date->year, date->month, date->day, date->hour, date->min, date->sec);
    
    __delay_ms(200);
}


uint8_t read_(uint8_t address){
    uint8_t data;
    i2c_start();
    write_byte(RTC_ADR);
    write_byte(address);
    
    i2c_repeated_start();
    
    write_byte(RTC_ADR | 0x01);
    data = bcd_2_decimal(recv_byte(1));
    i2c_stop();
    
    return data;
}

void read_date(struct Date *date){
    
    
    date->year = read_(6);
    date->month = read_(5);
    date->day = read_(4);
    read_(3);
    date->hour = read_(2);
    date->min = read_(1);
    date->sec = read_(0);
    
    /*
    i2c_start();
    write_byte(RTC_ADR);    
    write_byte(0);
    //i2c_stop();
    
    i2c_repeated_start();
    
    //i2c_start();
    write_byte(RTC_ADR | 0x01);    
    
    date->sec = bcd_2_decimal(recv_byte(1));
    date->min = bcd_2_decimal(recv_byte(1));
    date->hour = bcd_2_decimal(recv_byte(1));
    recv_byte(1);
    date->day = bcd_2_decimal(recv_byte(1));
    date->month = bcd_2_decimal(recv_byte(1));
    date->year = bcd_2_decimal(recv_byte(0));    
    
    i2c_stop();
    __delay_ms(50);
    */
    
    /*    
    printf("[R] year:%d, month:%d day:%d h:%d m:%d s:%d\r\n",
            date->year, date->month, date->day, date->hour, date->min, date->sec);
    */
}

