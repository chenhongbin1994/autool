
#ifndef		_DIGIT
#define		_DIGIT



extern volatile unsigned char lcd_ram[];	
extern volatile unsigned char  digit_10000;
extern volatile unsigned char  digit_1000;
extern volatile unsigned char  digit_100;
extern volatile unsigned char  digit_10;
extern volatile unsigned char  digit_1;



void 	Digit_1Num_Process(unsigned char addr1,unsigned char dotflag_onoff,unsigned char loadflg,unsigned int disp_value);
void  	Digit_2Num_converse_Process(unsigned char addr1,unsigned char addr2,unsigned char dotflag_onoff,unsigned char loadflg,unsigned int disp_value);
void  	Digit_2Num_Process(unsigned char addr1,unsigned char addr2,unsigned char dotflag_onoff,unsigned char loadflg,unsigned int disp_value);
void  	Digit_3Num_Process(unsigned char addr1,unsigned char addr2,unsigned char addr3,unsigned char dotflag_onoff, unsigned char loadflg,unsigned int disp_value);
void  	Digit_4Num_Process(unsigned char addr1,unsigned char addr2,unsigned char addr3,unsigned char addr4, unsigned char dotflag_onoff,unsigned char loadflg,unsigned int disp_value);
void  	Digit_3Num_converse_Process(unsigned char addr1,unsigned char addr2,unsigned char addr3,unsigned char dotflag_onoff, unsigned char loadflg,unsigned int disp_value);
void  	Digit_4Num_converse_Process(unsigned char addr1,unsigned char addr2,unsigned char addr3,unsigned char addr4, unsigned char dotflag_onoff,unsigned char loadflg,unsigned int disp_value);
void  	Digit_3Num_converse_Process_Clr(unsigned char addr1,unsigned char addr2,unsigned char addr3,unsigned char dotflag_onoff, unsigned char loadflg,unsigned int disp_value);
void  	Digit_5Num_converse_Process(unsigned char addr1,unsigned char addr2,unsigned char addr3,unsigned char addr4,
		unsigned char addr5,unsigned char dotflag_onoff,unsigned char loadflg,unsigned long disp_value);

void  	Digit_3Num_Process_Nodspzero(unsigned char addr1,unsigned char addr2,unsigned char addr3,
		unsigned char dotflag_onoff,unsigned char loadflg,unsigned int disp_value);

void  	Digit_3Num_converse_Process_Nodspzero(unsigned char addr1,unsigned char addr2,unsigned char addr3,
		unsigned char dotflag_onoff,unsigned char loadflg,unsigned int disp_value);

void  	Digit_5Num_Process(unsigned char addr1,unsigned char addr2,unsigned char addr3,unsigned char addr4,
		unsigned char addr5,unsigned char dotflag_onoff,unsigned char loadflg,unsigned int disp_value);
void  	Digit_5Num_3nd_Process(unsigned char addr1,unsigned char addr2,unsigned char addr3,unsigned char addr4,
		unsigned char addr5,unsigned char dotflag_onoff,unsigned char loadflg,unsigned int disp_value);
void  	Digit_5Num_2nd3nd_Process(unsigned char addr1,unsigned char addr2,unsigned char addr3,unsigned char addr4,
		unsigned char addr5,unsigned char dotflag_onoff,unsigned char loadflg,unsigned int disp_value);




void	Dig_RPM_Num(unsigned int disp_value);

void  	Dig_Hex_To_Bcd_4B(unsigned int hex_value);
void  	Dig_Hex_To_Bcd_5B(unsigned int hex_value);
void	Dig_Zero_Omit_4Bit(void);
void	Dig_Zero_Omit_3Bit(void);
void	Dig_Zero_Omit_2Bit(void);
//void	Dsp_FullOn();
//void	Dsp_FullOff();

#endif