/*
 * File:   TM1637_m.c
 * Author: dexte
 *
 * Created on November 2, 2020, 9:29 PM
 */


#include <xc.h>
#include "TM1637_m.h"
#include "TM.h"
#include "mcc_generated_files/mcc.h"

uint8_t m_brightness;

void m_start(void){
    DIO_M_SetDigitalOutput();
    CLK_M_SetDigitalOutput();
    
    DIO_M_SetHigh();      
    CLK_M_SetHigh();
    
    DIO_M_SetLow();    
    CLK_M_SetLow();
}

void m_stop(void){
    DIO_M_SetDigitalOutput();
    CLK_M_SetDigitalOutput();
    
    CLK_M_SetLow();
    DIO_M_SetLow();
        
    CLK_M_SetHigh();
    DIO_M_SetHigh();    
}

uint8_t m_write_data(uint8_t b){
    uint8_t data = b;
    
    CLK_M_SetDigitalOutput();    
    for(uint8_t i = 0; i < 8; i++){      
        CLK_M_SetLow();        
        
        if(data & 0x01){
            DIO_M_SetHigh();
        }else{
            DIO_M_SetLow();
        }
        
        CLK_M_SetHigh();
        
        data = data >> 1;
    }
    
    //wait ACK
    CLK_M_SetLow();
    DIO_M_SetHigh();    
    
    //SCL high    
    CLK_M_SetHigh();    
    
    DIO_M_SetDigitalInput();    
    
    uint8_t ack = DIO_M_GetValue();
    if(ack == 0){
        DIO_M_SetDigitalOutput();       
        DIO_M_SetLow();
    }
        
    DIO_M_SetDigitalOutput();           
    
    return ack;
}

void m_set_brigthness(uint8_t brightness, uint8_t on){
    if(on == 1){
        m_brightness = (brightness & 0x7 | 0x08);
    }else{
        m_brightness = (brightness & 0x7 | 0x00);
    }
}

void m_set_segments(const uint8_t segments[], uint8_t length, uint8_t pos){
    
    //write COMM1
    m_start();
    m_write_data(COMM1);
    m_stop();
    
    //write COMM2 + first digit address
    m_start();
    m_write_data(COMM2 + (pos & 0x03));
    
    //write the data bytes
    for(uint8_t k = 0; k < length; k++){
        m_write_data(segments[k]);        
    }
    
    m_stop();
    
    //write COMM3 + brigthness
    m_start();
    m_write_data(COMM3 + (m_brightness & 0x0f));    
    m_stop();
}