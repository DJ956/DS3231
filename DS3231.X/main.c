
#include "mcc_generated_files/mcc.h"
#include "TM1637.h"
#include "TM1637_m.h"
#include "DS3231.h"
#include "i2c.h"

#define BUTTON PORTBbits.RB4

uint16_t money = 0;

const uint16_t REGULAR_HOUR = 17;

const uint16_t MIN_4_MONEY = 27;
const uint16_t HOUR_4_MONEY = 1620;

uint8_t t_segments[] = {0x0f, 0x0f, 0x0f, 0x0f};
uint8_t m_segments[] = {0x0f, 0x0f, 0x0f, 0x0f};

void money_display();
void calc_money(struct Date date);
void add_time(struct Date *date);

void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
        
    ANSELB = 0xCA;
    
    TRISB2 = 1;
    TRISB5 = 1;
    
    uint8_t prev;
    TRISB4 = 1;
    //WPUB = 0x24;
    WPUB = 0x34;    
    
    SSP2ADD = 0x13;
    SSP2CON1 = 0x28;
    SSP2CON2 = 0x0;
    SSP2STAT = 0;
    
    struct Date date;    
    date.year = 20;
    date.month = 11;
    date.day = 15;
    date.hour = 8;
    date.min = 40;
    date.sec = 0;
    
    write_date(&date);
        
    set_brigthness(0x0f, 1);
    m_set_brigthness(0x0f, 1);
            
    read_date(&date);
    calc_money(date);
    money_display();
    
    prev = 0;
    
    while (1)
    {
        read_date(&date);        
        __delay_ms(20);
        
        /*
        if(BUTTON == 1){
            if(prev == 0){                
                add_time(&date);
                rtc_display(&date);
                __delay_ms(20);
            }
            prev = 1;
        }else{
            if(prev){
                __delay_ms(20);                
            }            
            prev = 0;
        } 
         * */        
        
        rtc_display(&date);       
        
        if(date.sec == 0){
            calc_money(date);
        }
        
        money_display();        
        __delay_ms(100);        
    }
}

void add_time(struct Date *date){
    if(date->min == 59){
        date->min = 0;
        if(date->hour == 23){
            date->hour = 0;
        }else{
            date-> hour = date->hour + 1;
        }
    }else{
        date->min = date->min + 1;
    }

    write_date(&date);    
    __delay_ms(1000 * 5);
}

void calc_money(struct Date date){
    if(date.hour > 17){
        uint16_t hour = (uint16_t)date.hour;
        uint16_t min = (uint16_t)date.min;
        money = ((hour - REGULAR_HOUR) * HOUR_4_MONEY) +  (MIN_4_MONEY * min) - (MIN_4_MONEY * 20);
    }else{
        money = 0;
    }
}

void rtc_display(struct Date *date){    
    //uint8_t year = date->year;
    //uint8_t month = date->month;
    //uint8_t day = date->day;
    uint8_t hour = date->hour;
    uint8_t min = date->min;
    //uint8_t sec = date->sec;    
         
    t_segments[0] = encode_digit(hour / 10);
    t_segments[1] = encode_digit(hour % 10);    
    t_segments[2] = encode_digit(min / 10);
    t_segments[3] = encode_digit(min % 10);    
    
    set_segments(t_segments, 4, 0);        
}

void money_display(){    
    uint16_t value = money;
    
    m_segments[0] = encode_digit(value / 1000);
    value %= 1000;
    m_segments[1] = encode_digit(value / 100);
    value %= 100;
    m_segments[2] = encode_digit(value / 10);
    value %= 10;
    m_segments[3] = encode_digit(value);
        
    m_set_segments(m_segments, 4, 0);
}

/**
 End of File
*/