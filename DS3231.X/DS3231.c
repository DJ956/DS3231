/*
 * File:   DS3231.c
 * Author: dexte
 *
 * Created on October 14, 2020, 12:00 AM
 */

#include "DS3231.h"
#include "i2c_pp.h"
#include <xc.h>
#include "mcc_generated_files/mcc.h"

void i2c_init(uint8_t clk_freq){
    SSPCON = 0x28;
    SSPADD = (_XTAL_FREQ/(4 * clk_freq)) -1;
    SSPSTAT = 0;
}

void i2c_start(){
    while((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
    SSP2CON2bits.SEN = 1;
}

void i2c_stop(){
    while((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
    SSP2CON2bits.PEN = 1;
}

void i2c_repeated_start(){
    while((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
    SSP2CON2bits.RSEN = 1;
}

void i2c_write(uint8_t data){
    while((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
    SSPBUF = data;
}

uint8_t i2c_read(uint8_t ack){
    uint8_t data;
    while((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
    SSP2CON2bits.RCEN = 1;
    while((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
    data = SSPBUF;
    while((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
    
    SSP2CON2bits.ACKDT = !ack;
    SSP2CON2bits.ACKEN = 1;
    
    return data;
}

uint8_t bcd_2_decimal(uint8_t number){
    return ((number >> 4) * 10 + (number & 0x0F));
}

uint8_t decimal_2_bcd(uint8_t number){
    return (((number / 10) << 4) + (number % 10));
}

void write_date(struct Date *date){
    i2c_start();
    i2c_write(RTC_ADR);
    i2c_write(0);

    i2c_write(decimal_2_bcd(date->sec));
    i2c_write(decimal_2_bcd(date->min));
    i2c_write(decimal_2_bcd(date->hour));
    i2c_write(1);
    i2c_write(decimal_2_bcd(date->day));
    i2c_write(decimal_2_bcd(date->month));
    i2c_write(decimal_2_bcd(date->year));
    i2c_stop();
    
    __delay_ms(200);
}

void read_date(struct Date *date){
    i2c_start();
    i2c_write(RTC_ADR);
    i2c_write(0);
    i2c_repeated_start();
    i2c_write(0xD1);
    
    date->sec = i2c_read(1);
    date->min = i2c_read(1);
    date->hour = i2c_read(1);
    i2c_read(1);
    date->day = i2c_read(1);
    date->month = i2c_read(1);
    date->year = i2c_read(0);
    
    i2c_stop();       
}



void rtc_display(struct Date *date){
    uint8_t segments[] = {0xff, 0xff, 0xff, 0xff};
    
    uint8_t min = bcd_2_decimal(date->min);
    uint8_t sec = bcd_2_decimal(date->sec);
    
    segments[0] = encode_digit(min / 10);
    segments[1] = encode_digit(min % 10);    
    segments[2] = encode_digit(sec / 10);
    segments[3] = encode_digit(sec % 10);
    
    set_segments(segments, 4, 0);
}