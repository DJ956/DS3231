
#include "mcc_generated_files/mcc.h"
#include "DS3231.h"
#include "i2c.h"


void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
        
    ANSELB = 0xCA;
    
    WPUB = 0x24;
    
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
    
            
    read_date(&date);
    
    while (1)
    {
        read_date(&date);        
        __delay_ms(20);
    }
}