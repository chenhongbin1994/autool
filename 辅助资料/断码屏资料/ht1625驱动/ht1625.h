#ifndef DEFINED_HT1623
#define DEFINED_HT1623

	// HT1623 COMMUNICATION Mapping -- PORTB
//#define	HT1623PWR_TRIS	    TRISBbits.TRISB10
#define	HT1623CS_TRIS	    _pdc5
#define	HT1623WR_TRIS	    _pdc6
#define HT1623RD_TRIS	    _pfc7
#define HT1623DATA_TRIS   _pfc6

//#define HT1623PWR_PORT	    LATBbits.LATB10
#define HT1623CS_PORT	    _pd5
#define HT1623WR_PORT	    _pd6
#define HT1623RD_PORT 	  	_pf7
//#define HT1623DATA_LAT    _pf6
#define HT1623DATA_PORT    _pf6

#define HT1623DATA_LAT HT1623DATA_PORT    

#define SEG_BIT0 0x01 
#define SEG_BIT1 0x02 
#define SEG_BIT2 0x04 
#define SEG_BIT3 0x08 
#define SEG_BIT4 0x10 
#define SEG_BIT5 0x20 
#define SEG_BIT6 0x40 
#define SEG_BIT7 0x80

#define SEGOK_A 0x80	
#define SEGOK_B 0x20
#define SEGOK_C 0x04 	
#define SEGOK_D 0x02
#define SEGOK_E 0x08
#define SEGOK_F 0x40
#define SEGOK_G 0x10	


	
#define SEGOK_A2 0x02	
#define SEGOK_B2 0x08
#define SEGOK_C2 0x40	
#define SEGOK_D2 0x80
#define SEGOK_E2 0x20
#define SEGOK_F2 0x04
#define SEGOK_G2 0x10

#define SEGOK_A3 0x01	
#define SEGOK_B3 0x04
#define SEGOK_C3 0x20 	
#define SEGOK_D3 0x40
#define SEGOK_E3 0x10
#define SEGOK_F3 0x02
#define SEGOK_G3 0x08



#define SEGOK_A4 0x40	
#define SEGOK_B4 0x10
#define SEGOK_C4 0x02 	
#define SEGOK_D4 0x01
#define SEGOK_E4 0x04
#define SEGOK_F4 0x20
#define SEGOK_G4 0x08



#define SEGOK_OFF 0x00	





#define  	T1			S4
#define 	T2			S3
#define  	T3			S2
#define   	T4			S1
#define  	T5			S5

#define	S1	0x80
#define	S2	0x40
#define	S3	0x20
#define	S4	0x10
#define	S5	0x08
#define	S6	0x04
#define	R1	0x02
#define	R2	0x04
#define	S7	0x01
#define	S8	0x01
#define	S9	0x02
#define	S10	0x01
#define	S11	0x01
#define	S12	0x01
#define	S13	0x40
#define	S14	0x20
#define	S15	0x10
#define	S16	0x10
#define	S17	0x08
#define	S18	0x08
#define	S19	0x04
#define	S20	0x04
#define	S21	0x02
#define	S22	0x20
#define	S23	0x01
#define	S24	0x80
#define	S25	0x01
#define	S26	0x80
#define	S27	0x08
#define	S28	0x10
#define	S29	0x20
#define	S30	0x40
#define	S31	0x80
#define	S32	0x80
#define	S33	0x80
#define	S34	0x80
#define	S35	0x80
#define	S36	0x80
#define	S37	0x80
#define	S38	0x40
#define	S39	0x20
#define	S40	0x08
#define	S41	0x10
#define	S42	0x01
#define	S43	0x01
#define	S44	0x01
#define	S45	0x01
#define	S46	0x01
#define	S47	0x04
#define	S48	0x02
#define	S49	0x01
#define	S50	0x80
#define	S51	0x80
#define	S52	0x80
#define	S53	0x80
#define	S54	0x80
#define	S55	0x80
#define	S56	0x40
#define	S57	0x20
#define	S58	0x10
#define	S59	0x08
#define	S60	0x04
#define	S61	0x02
#define	S62	0x01
#define	S63	0x80
#define	S64	0x80
#define	S65	0x01
#define	S66	0x02
#define	S67	0x04
#define	S68	0x08
#define	S69	0x10
#define	S70	0x20
#define	S71	0x40
#define	S72	0x20
#define	S73	0x08
#define	S74	0x10
#define	S75	0x02
#define	S76	0x04
#define	S77	0x01


	
  enum Symbol
  {
    CLR = 11
  };
  
  enum  Digit_Addr		// DIGIT display address
  {
  	ST49,	//PIN9	SEG0
  	D11,	//PIN10	SEG1
  	D12,	//PIN11	SEG2
  	D13,	//PIN12	SEG3
  	D14,	//PIN13	SEG4
  	D15,	//PIN14	SEG5
  	D16,	//PIN15	SEG6
  	D4,		//PIN16 SEG7
  	D3,		//PIN17	SEG8
  	D2,		//PIN18	SEG9
  	D1=38,	//PIN52	SEG35
  	ST7, 	//PIN51	SGE34
  	ST8,	//PIN50	SEG33
  	ST23,	//PIN49	SEG32
  	RS2,	//PIN48	SEG31
  	D5,		//PIN47	SEG30
  	D6,		//PIN46	SEG29
  	D7,		//PIN45	SEG28
  	D8,   	//PIN44	SEG27
  	D9,   	//PIN43	SEG26
  	D10,	//PIN42	SEG25
  	D17,	//PIN41	SEG24
  	D18,	//PIN40	SEG23
  	D19,	//PIN39	SEG22
  	D20,	//PIN38	SEG21
  	D21,	//PIN37	SEG20
  	D22,	//PIN36	SEG19
  	ST65,	//PIN35	SEG18
  	ST77,	//PIN34	SEG17
  	D28,	//PIN33	SEG16
  	D27,	//PIN32	SEG15
  	D26,	//PIN31	SEG14
  	D25,	//PIN30	SEG13
  	D24,	//PIN29	SEG12
  	D23,	//PIN28	SEG11
  	ST62	//PIN27	SEG10
  };

#define		FONT_A		1	//digit_table2 - 'afbgecd' type 
					// " D1,D2,D3,D4,D5,D6,	     "
					// " D13,D14,D15,D26,D27,    "	
					// " D28,D29,D30,D31,D32,D33 "
#define		FONT_B		0	//digit_table1 - 'dcegbfa' type
					// " D7,D8,D9,D10,D11,D12    "	
					// " D16,D17,D18,D19,D20,D21 "
					// " D22,D23,D24 "


void  HT1623_Intial(void);
void  HT1623_PWROn(void);
void  HT1623_lcdOFF(void);
void  HT1623_lcdON(void);
void  HT1623_ramdump(unsigned char);
void  HT1623_Disp_SomeRam(unsigned char addr,unsigned char pcs,volatile unsigned char *buf);
void  HT1623_displayInt(unsigned char,unsigned int,unsigned char,
            unsigned char,unsigned char,unsigned char,unsigned char);
void  HT1623_dispDigit(unsigned char htdis_number,unsigned char htvalue,unsigned char icon,unsigned char font);
//void  HT1623_Disp999(unsigned char startPosi,unsigned int display_data,unsigned char,
//            unsigned char, unsigned char,unsigned char,unsigned char);
void  HT1623_displayIcon(unsigned char Icon,unsigned char Onoff);      
void  HT1623_displayTwoDigit(unsigned char startPosi,unsigned char display_data,unsigned char icon1,unsigned char icon2,unsigned char font);
void  HT1623_displayTwoDigit1(unsigned char startPosi,unsigned char display_data,unsigned char icon1,unsigned char icon2,unsigned char font);
void  HT1623_WritedataTolcd(unsigned char adr,unsigned char data);
void  HT1623_ReadData_From_Lcd(unsigned char addr,unsigned char value,unsigned char opr);


#endif  

