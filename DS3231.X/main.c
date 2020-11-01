
#include "mcc_generated_files/mcc.h"
#include "TM1637.h"
#include "DS3231.h"
#include "i2c.h"

void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
        
    TRISB2 = 1;
    TRISB5 = 1;
    WPUB = 0x24;
    
    //SSP2ADD = _XTAL_FREQ / (4 * (100000)) - 1;
    SSP2ADD = 0x13;
    SSP2CON1 = 0x28;
    SSP2CON2 = 0x0;
    SSP2STAT = 0;
    
    struct Date date;
    date.year = 20;
    date.month = 11;
    date.day = 1;
    date.hour = 10;
    date.min = 38;
    date.sec = 24;
    
    write_date(&date);
    
    set_brigthness(0x0f, 1);

            
    while (1)
    {
        read_date(&date);        
        rtc_display(&date);
        __delay_ms(100);        
    }
}



void rtc_display(struct Date *date){
    uint8_t segments[] = {0xff, 0xff, 0xff, 0xff};
    
    uint8_t year = date->year;
    uint8_t month = date->month;
    uint8_t day = date->day;
    uint8_t hour = date->hour;
    uint8_t min = date->min;
    uint8_t sec = date->sec;
    
    segments[0] = encode_dig(min / 10);
    segments[1] = encode_dig(min % 10);    
    segments[2] = encode_dig(sec / 10);
    segments[3] = encode_dig(sec % 10);
    
    set_segments(segments, 4, 0);
}

/**
 End of File
*/