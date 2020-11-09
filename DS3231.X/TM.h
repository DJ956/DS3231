/* 
 * File:   TM.h
 * Author: dexte
 *
 * Created on November 2, 2020, 10:01 PM
 */

#ifndef TM_H
#define	TM_H

#ifdef	__cplusplus
extern "C" {
#endif

#define COMM1 0x40 
#define COMM2 0xC0
#define COMM3 0x80

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



#ifdef	__cplusplus
}
#endif

#endif	/* TM_H */

