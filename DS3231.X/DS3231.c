/*
 * File:   DS3231.c
 * Author: dexte
 *
 * Created on October 14, 2020, 12:00 AM
 */

#include "i2c.h"
#include "DS3231.h"

#include "mcc_generated_files/mcc.h"


/**
 * RTC format to number
 * @param number
 * @return 
 */
uint8_t bcd_2_decimal(uint8_t number){
    return ((number >> 4) * 10 + (number & 0x0F));
}

/**
 * number to RCT format
 * @param number
 * @return 
 */
uint8_t decimal_2_bcd(uint8_t number){
    return (((number / 10) << 4) + (number % 10));
}

/**
 * Write date to RTC
 * @param date
 */
void write_date(struct Date *date){
    i2c_start();
    i2c_write(RTC_ADR);
    i2c_write(0x00);

    i2c_write(decimal_2_bcd(date->sec));        //write sec
    i2c_write(decimal_2_bcd(date->min));        //write min
    i2c_write(decimal_2_bcd(date->hour));       //write hour
    i2c_write(1);                               //write day_of_week
    i2c_write(decimal_2_bcd(date->day));        //write day
    i2c_write(decimal_2_bcd(date->month));      //write month
    i2c_write(decimal_2_bcd(date->year));       //write year
    i2c_stop();
    
    __delay_ms(200);
}


/**
 * Read data from RTC
 * @param address (0:sec, 1:min, 2:hour, 3:day_week, 4:day, 5:month, 6:yaer)
 * @return 
 */
uint8_t _read(uint8_t address){
    uint8_t data;
    i2c_start();
    i2c_write(RTC_ADR);
    i2c_write(address);
    
    i2c_repeated_start();
    
    i2c_write(RTC_ADR | 0x01);
    data = bcd_2_decimal(i2c_read(1));
    i2c_stop();
    
    return data;
}

/**
 * Read date from RTC & update date
 * @param date
 */
void read_date(struct Date *date){ 
    date->year = _read(6);      //read year(necessary add 2000)
    date->month = _read(5);     //read month
    date->day = _read(4);       //read day
    _read(3);                   //read day_of_week
    date->hour = _read(2);      //read hour
    date->min = _read(1);       //read min
    date->sec = _read(0);       //read sec
}

