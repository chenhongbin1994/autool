#ifndef		_HT1621_H
#define		_HT1621_H

#define BIAS 0x52	//4COM,1/3BIAS
#define SYSEN 0x02
#define SYSDIS 0x00
#define LCDON 0x06
#define LCDOFF 0x04

void init_1621(void);
void Write_1621(unsigned char addr,unsigned char data);
void clr_1621(void);

#endif