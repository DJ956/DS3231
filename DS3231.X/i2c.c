
#include <xc.h>
#include "i2c.h"

/*
void i2c_wait(){
    while(SSP2CON2bits.SEN || SSP2CON2bits.PEN || SSP2CON2bits.RCEN
            || SSP2CON2bits.ACKEN || SSP2STATbits.R_nW);    
}
 * */

void i2c_wait(){
    while((SSP2CON2 & 0x1F) || (SSP2STAT & 0x04));
}

void i2c_start(){
    i2c_wait();
    SSP2CON2bits.SEN = 1;
    while(SSP2CON2bits.SEN);
}

void i2c_stop(){
    SSP2CON2bits.PEN = 1;
    while(SSP2CON2bits.PEN);
}

void i2c_repeated_start(){
    i2c_wait();
    SSP2CON2bits.RSEN = 1;
    while(SSP2CON2bits.RSEN);
}

void write_byte(uint8_t data){
    SSP2BUF = data;
    while(SSP2STATbits.BF);
    while(SSP2CON2bits.ACKSTAT);
    i2c_wait();
}

void i2c_cmd(uint8_t address, uint8_t reg, uint8_t data){
    i2c_start();
    write_byte(address);
    write_byte(reg);
    write_byte(data);
    i2c_stop();
}

uint8_t recv_byte(uint8_t ack){
    uint8_t data;
    
    SSP2CON2bits.ACKDT = ack;
    SSP2CON2bits.RCEN = 1;
    while(!SSP2STATbits.BF);
    SSP2CON2bits.ACKEN = 1;
    data = SSP2BUF;
    SSP2CON1bits.SSPOV = 0;
    i2c_wait();
    
    return data;
}

void recv_data(uint8_t address, uint8_t *buffer, uint8_t cnt){
    uint8_t i;
    
    i2c_start();
    write_byte(address+1);
    for(i = 0; i < cnt; i++){
        buffer[i] = recv_byte(0);        
    }
    buffer[i] = recv_byte(1);
    
    i2c_stop();
}

