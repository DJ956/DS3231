/*
 * File:   TM1637.c
 * Author: dexte
 *
 * Created on 2020/10/31, 8:36
 */

#include "TM1637.h"
#include "TM.h"
#include "mcc_generated_files/mcc.h"

uint8_t m_brightness;

void start(void){
    DIO_SetDigitalOutput();
    CLK_SetDigitalOutput();
    
    DIO_SetHigh();      
    CLK_SetHigh();
    
    DIO_SetLow();    
    CLK_SetLow();
}

void stop(void){
    DIO_SetDigitalOutput();
    CLK_SetDigitalOutput();
    
    CLK_SetLow();
    DIO_SetLow();
        
    CLK_SetHigh();
    DIO_SetHigh();    
}

uint8_t write_data(uint8_t b){
    uint8_t data = b;
    
    CLK_SetDigitalOutput();    
    for(uint8_t i = 0; i < 8; i++){      
        CLK_SetLow();        
        
        if(data & 0x01){
            DIO_SetHigh();
        }else{
            DIO_SetLow();
        }
        
        CLK_SetHigh();
        
        data = data >> 1;
    }
    
    //wait ACK
    CLK_SetLow();
    DIO_SetHigh();    
    
    //SCL high    
    CLK_SetHigh();    
    
    DIO_SetDigitalInput();    
    
    uint8_t ack = DIO_GetValue();
    if(ack == 0){
        DIO_SetDigitalOutput();       
        DIO_SetLow();
    }
    
    DIO_SetDigitalOutput();       
    
    return ack;
}

void set_brigthness(uint8_t brightness, uint8_t on){
    if(on == 1){
        m_brightness = (brightness & 0x7 | 0x08);
    }else{
        m_brightness = (brightness & 0x7 | 0x00);
    }
}

void set_segments(const uint8_t segments[], uint8_t length, uint8_t pos){
    
    //write COMM1
    start();
    write_data(COMM1);
    stop();
    
    //write COMM2 + first digit address
    start();
    write_data(COMM2 + (pos & 0x03));
    
    //write the data bytes
    for(uint8_t k = 0; k < length; k++){
        write_data(segments[k]);        
    }
    
    stop();
    
    //write COMM3 + brigthness
    start();
    write_data(COMM3 + (m_brightness & 0x0f));    
    stop();
}


uint8_t encode_digit(uint8_t digit){        
    return segdata[digit & 0x0f];
}