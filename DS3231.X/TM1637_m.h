/* 
 * File:   TM1637_m.h
 * Author: dexte
 *
 * Created on November 2, 2020, 9:28 PM
 */

#ifndef TM1637_M_H
#define	TM1637_M_H

#ifdef	__cplusplus
extern "C" {
#endif

void m_start();
void m_stop();
void m_set_brigthness(uint8_t brightness, uint8_t on);
uint8_t m_write_data(uint8_t b);
void m_set_segments(const uint8_t segments[], uint8_t length, uint8_t pos);


#ifdef	__cplusplus
}
#endif

#endif	/* TM1637_M_H */

