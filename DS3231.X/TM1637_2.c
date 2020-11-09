/*
 * File:   TM1637_2.c
 * Author: dexte
 *
 * Created on November 2, 2020, 7:03 PM
 */


#include <xc.h>

#define COMM1 0x40 
#define COMM2 0xC0
#define COMM3 0x80

uint8_t m_brightness;

unsigned char porta;

uint8_t segdata[] = { 
   0x3F, // 0
   0x06, // 1
   0x5B, // 2
   0x4F, // 3
   0x66, // 4
   0x6D, // 5
   0x7D, // 6
   0x07, // 7
   0x7F, // 8
   0x6F  // 9 
};


void start(uint8_t dio, uint8_t clk){        
    uint8_t pins = dio | clk;    
    TRISA = 0xff; //init
    
    porta = TRISA;        
    TRISA = porta ^ pins; //dio clk digital output        
    /*
    DIO_SetDigitalOutput();
    CLK_SetDigitalOutput();
    */
    
    porta = LATA;
    LATA = porta | pins; // dio clk set high
    /*
    DIO_SetHigh();      
    CLK_SetHigh();
    */
    
    porta = LATA;
    LATA = porta ^ pins; //dio clk set low    
    /*
    DIO_SetLow();    
    CLK_SetLow();
    */
}

void stop(uint8_t dio, uint8_t clk){
    uint8_t pins = dio | clk;
    TRISA = 0xff;
    
    porta = TRISA;
    TRISA = porta ^ pins; //dio clk set high
    /*
    DIO_SetDigitalOutput();
    CLK_SetDigitalOutput();
    */
    
    porta = LATA;
    LATA = porta ^ pins; //dio clk set low
    /*
    CLK_SetLow();
    DIO_SetLow();
    */
    
    porta = LATA;
    LATA = porta | pins; //dio clk set high
    /*
    CLK_SetHigh();
    DIO_SetHigh();    
    */
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
    bit_delay();
    
    uint8_t ack = DIO_GetValue();
    if(ack == 0){
        DIO_SetDigitalOutput();       
        DIO_SetLow();
    }
    
    bit_delay();
    DIO_SetDigitalOutput();       
    bit_delay();
    
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

void clear(){
    uint8_t data[] = { 0, 0, 0, 0 };
	set_segments(data, 4, 0);
}


uint8_t encode_digit(uint8_t digit){        
    return segdata[digit & 0x0f];
}