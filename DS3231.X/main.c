#include "mcc_generated_files/mcc.h"
#include "i2c_pp.h"
#include "DS3231.h"

/*
                         Main application
 */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    
    WPUB = 0x24;
    
    i2c_init(100000);
    
    struct Date date = {2020, 10, 14, 1, 19, 84};
        
    write_date(&date);
           
    set_brigthness(0x0f, 1);
    
    while (1)
    {       
        read_date(&date);        
        rtc_display(&date);
        
        __delay_ms(1000);
    }
    
}
/**
 End of File
*/