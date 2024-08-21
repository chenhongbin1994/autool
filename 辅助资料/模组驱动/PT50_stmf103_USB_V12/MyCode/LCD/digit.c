#include "digit.h"
#include "digit.h"
#include "display.h"
#include "LCD_HT1623.h"
//#include "power.h"

#if 0

volatile unsigned char 	lcd_ram[38];		// use to light all lcd at one time
volatile unsigned char  digit_10000;
volatile unsigned char	digit_1000;
volatile unsigned char  digit_100;
volatile unsigned char  digit_10;
volatile unsigned char	digit_1;




const unsigned char Digit_Tb2[] = 
{
		SEGOK_A + SEGOK_B + SEGOK_C + SEGOK_F + SEGOK_E + SEGOK_D, 	//0 LCD segments a+b+c+d+e+f 353	
		SEGOK_B + SEGOK_C,                      		 		//1  
		SEGOK_D + SEGOK_G + SEGOK_E + SEGOK_A + SEGOK_B,		//2
		SEGOK_G + SEGOK_D + SEGOK_A + SEGOK_B + SEGOK_C,        //3                    		
		SEGOK_C + SEGOK_B + SEGOK_F +SEGOK_G,    		        //4
		SEGOK_A + SEGOK_C + SEGOK_F + SEGOK_D + SEGOK_G,        //5
		SEGOK_A + SEGOK_C + SEGOK_F + SEGOK_G + SEGOK_E + SEGOK_D,   //6
		SEGOK_A + SEGOK_B + SEGOK_C,			                     //7
		SEGOK_F + SEGOK_G + SEGOK_E + SEGOK_D + SEGOK_A + SEGOK_B + + SEGOK_C,   //8
		SEGOK_A + SEGOK_B + SEGOK_C + SEGOK_F + SEGOK_G + SEGOK_D,          //9		        
		SEGOK_G,                                      // - 10
		SEGOK_OFF                         			//clr 11
};

const unsigned char Digit_Tbl[] = 
{
		SEGOK_A2 + SEGOK_B2 + SEGOK_C2 + SEGOK_F2 + SEGOK_E2 + SEGOK_D2, 	//0 LCD segments a+b+c+d+e+f 353	
		SEGOK_B2 + SEGOK_C2,                      		 		//1  
		SEGOK_D2 + SEGOK_G2 + SEGOK_E2 + SEGOK_A2 + SEGOK_B2,		//2
		SEGOK_G2 + SEGOK_D2 + SEGOK_A2 + SEGOK_B2 + SEGOK_C2,        //3                    		
		SEGOK_C2 + SEGOK_B2 + SEGOK_F2 +SEGOK_G2,    		        //4
		SEGOK_A2 + SEGOK_C2 + SEGOK_F2 + SEGOK_D2 + SEGOK_G2,        //5
		SEGOK_A2 + SEGOK_C2 + SEGOK_F2 + SEGOK_G2 + SEGOK_E2 + SEGOK_D2,   //6
		SEGOK_A2 + SEGOK_B2 + SEGOK_C2,			                     //7
		SEGOK_F2 + SEGOK_G2 + SEGOK_E2 + SEGOK_D2 + SEGOK_A2 + SEGOK_B2  + SEGOK_C2,   //8
		SEGOK_A2 + SEGOK_B2 + SEGOK_C2 + SEGOK_F2 + SEGOK_G2 + SEGOK_D2,          //9		        
		SEGOK_G2,                                      // - 10
		SEGOK_OFF                         			//clr 11
};

const unsigned char Digit_Tb3[] = 
{
		SEGOK_A3 + SEGOK_B3 + SEGOK_C3 + SEGOK_F3 + SEGOK_E3 + SEGOK_D3, 	//0 LCD segments a+b+c+d+e+f 353	
		SEGOK_B3 + SEGOK_C3,                      		 		//1  
		SEGOK_D3 + SEGOK_G3 + SEGOK_E3 + SEGOK_A3 + SEGOK_B3,		//2
		SEGOK_G3 + SEGOK_D3 + SEGOK_A3 + SEGOK_B3 + SEGOK_C3,        //3                    		
		SEGOK_C3 + SEGOK_B3 + SEGOK_F3 +SEGOK_G3,    		        //4
		SEGOK_A3 + SEGOK_C3 + SEGOK_F3 + SEGOK_D3 + SEGOK_G3,        //5
		SEGOK_A3 + SEGOK_C3 + SEGOK_F3 + SEGOK_G3 + SEGOK_E3 + SEGOK_D3,   //6
		SEGOK_A3 + SEGOK_B3 + SEGOK_C3,			                     //7
		SEGOK_F3 + SEGOK_G3 + SEGOK_E3 + SEGOK_D3 + SEGOK_A3 + SEGOK_B3  + SEGOK_C3,   //8
		SEGOK_A3 + SEGOK_B3 + SEGOK_C3 + SEGOK_F3 + SEGOK_G3 + SEGOK_D3,          //9		        
		SEGOK_G3,                                      // - 10
		SEGOK_OFF                         			//clr 11
};
//-----------------------------------------------
void Digit_1Num_Process(unsigned char addr1,unsigned char dotflag_onoff,unsigned char loadflg,unsigned int disp_value)
{
      	unsigned char data,dflag,loadfalg; 
      	dflag = dotflag_onoff;
      	loadfalg = 	loadflg;
      	
	lcd_ram[addr1] = 0;

		
      	//data = disp_value;     
      //	if(data>0 || dflag==1)
       //       	dflag=1;
      //	else data=CLR;              	      	
//	lcd_ram[addr1] = Digit_Tbl[data];	
		//if(dflag ==1)lcd_ram[addr2] |= 0x80;  //dsp dot icon		
	lcd_ram[addr1] = Digit_Tbl[disp_value];
		
		if(loadfalg == 0)HT1623_Disp_SomeRam(2*addr1,1,lcd_ram+addr1);
}
//-----------------------------------------------
void  	Digit_2Num_converse_Process(unsigned char addr1,unsigned char addr2,
		unsigned char dotflag_onoff,unsigned char loadflg,unsigned int disp_value)
{
      	unsigned char data,dflag,loadfalg; 
      	dflag = dotflag_onoff;
      	loadfalg = 	loadflg;
      	
	lcd_ram[addr1] = 0;
	lcd_ram[addr2] = 0;	
		
      	data = disp_value/10;     
      	if(data>0 || dflag==1)
              	dflag=1;
      	else data=CLR;              	      	
	lcd_ram[addr1] = Digit_Tb3[data];	
		if(dflag ==1)lcd_ram[addr1] |= 0x01;  //dsp dot icon			
	lcd_ram[addr2] = Digit_Tb3[disp_value%10];
		if(dflag ==1)lcd_ram[addr2] |= 0x01;  //min icon	
		if(loadfalg == 0)HT1623_Disp_SomeRam(2*addr1,2,lcd_ram+addr1);
}
//-----------------------------------------------
void  	Digit_3Num_Process(unsigned char addr1,unsigned char addr2,unsigned char addr3,
		unsigned char dotflag_onoff,unsigned char loadflg,unsigned int disp_value)
{
      	unsigned char data,dflag,loadfalg;  
      	dflag = dotflag_onoff;
      	loadfalg = 	loadflg;
      		
	lcd_ram[addr1] = 0;
	lcd_ram[addr2] = 0;
	lcd_ram[addr3] = 0;	
	
	data = disp_value/100;
      	if(data>0 || dflag==1)
             	dflag=1;
      	else data=CLR;          	
	lcd_ram[addr1] = Digit_Tbl[data];

      	disp_value %= 100; 
      	data = disp_value/10;     
      	if(data>0 || dflag==1)
              	dflag=1;
      	else data=CLR;              	      	
	lcd_ram[addr2] = Digit_Tbl[data];	
//		if(dflag ==1)lcd_ram[addr3] |= 0x80;  //dsp dot icon		
	lcd_ram[addr3] = Digit_Tbl[disp_value%10];
		
		if(loadfalg == 0)HT1623_Disp_SomeRam(2*addr1,3,lcd_ram+addr1);
}

//-----------------------------------------------
void  	Digit_3Num_Process_Nodspzero(unsigned char addr1,unsigned char addr2,unsigned char addr3,
		unsigned char dotflag_onoff,unsigned char loadflg,unsigned int disp_value)
{
      	unsigned char data,dflag,loadfalg;  
      	dflag = dotflag_onoff;
      	loadfalg = 	loadflg;
      		
	lcd_ram[addr1] = 0;
	lcd_ram[addr2] = 0;
	lcd_ram[addr3] = 0;	
	
	data = disp_value/100;
      	if(data>0 || dflag==1)
             	dflag=1;
      	else data=CLR;          	
	lcd_ram[addr1] = Digit_Tbl[data];

      	disp_value %= 100; 
      	data = disp_value/10;     
      	if(data>0 || dflag==1)
              	dflag=1;
      	else data=CLR;              	      	
	lcd_ram[addr2] = Digit_Tbl[data];	
//		if(dflag ==1)lcd_ram[addr3] |= 0x80;  //dsp dot icon

	data = disp_value%10;     
      	if(data>0 || dflag==1)
              	dflag=1;
      	else data=CLR;      		
	lcd_ram[addr3] = Digit_Tbl[data];
		
		if(loadfalg == 0)HT1623_Disp_SomeRam(2*addr1,3,lcd_ram+addr1);
}

void  	Digit_4Num_Process(unsigned char addr1,unsigned char addr2,unsigned char addr3,
		unsigned char addr4,unsigned char dotflag_onoff,unsigned char loadflg,unsigned int disp_value)
{
      	unsigned char data,dflag,loadfalg; 
      	dflag = dotflag_onoff;
      	loadfalg = 	loadflg;
      		
	lcd_ram[addr1] = 0;
	lcd_ram[addr2] = 0;
	lcd_ram[addr3] = 0;	
	lcd_ram[addr4] = 0;

	data = disp_value/1000;
      	if(data>0 || dflag==1)
             	dflag=1;
      	else data=CLR;                  	    	
		lcd_ram[addr1] = Digit_Tbl[data];
		
	disp_value %= 1000;
	data = disp_value/100;
      	if(data>0 || dflag==1)
             	dflag=1;
      	else data=CLR;               	 	
	lcd_ram[addr2] = Digit_Tbl[data];

      	disp_value %= 100; 
      	data = disp_value/10;     
      	if(data>0 || dflag==1)
              	dflag=1;
      	else data=CLR;
	lcd_ram[addr3] = Digit_Tbl[data];
//	if(dflag ==1)lcd_ram[addr3] |= 0x80;  //display dot icon 
	lcd_ram[addr4] = Digit_Tbl[disp_value%10];
		
		if(loadfalg == 0)HT1623_Disp_SomeRam(2*addr1,4,lcd_ram+addr1);				
}
//-------------------------------------------------------------------
//-----------------------------------------------
void  	Digit_3Num_converse_Process(unsigned char addr1,unsigned char addr2,unsigned char addr3,
		unsigned char dotflag_onoff,unsigned char loadflg,unsigned int disp_value)
{
      	unsigned char data,dflag,loadfalg; 
      	dflag = dotflag_onoff;
      	loadfalg = 	loadflg;
      		
	lcd_ram[addr1] = 0;
	lcd_ram[addr2] = 0;
	lcd_ram[addr3] = 0;	
	
	data = disp_value/100;
      	if(data>0 || dflag==1)
             	dflag=1;
      	else data=CLR;              	
	lcd_ram[addr1] = Digit_Tbl[data];

      	disp_value %= 100; 
      	data = disp_value/10;     
      	if(data>0 || dflag==1)
              	dflag=1;
      	else data=CLR;              	      	
	lcd_ram[addr2] = Digit_Tbl[data];	
//		if(dflag ==1)lcd_ram[addr3] |= 0x80;  //dsp dot icon		
	lcd_ram[addr3] = Digit_Tbl[disp_value%10];
		
		if(loadfalg == 0)HT1623_Disp_SomeRam(2*addr3,3,lcd_ram+addr3);
}

//-----------------------------------------------
void  	Digit_3Num_converse_Process_Nodspzero(unsigned char addr1,unsigned char addr2,unsigned char addr3,
		unsigned char dotflag_onoff,unsigned char loadflg,unsigned int disp_value)
{
      	unsigned char data,dflag,loadfalg; 
      	dflag = dotflag_onoff;
      	loadfalg = 	loadflg;
      		
	lcd_ram[addr1] = 0;
	lcd_ram[addr2] = 0;
	lcd_ram[addr3] = 0;	
	
	data = disp_value/100;
      	if(data>0 || dflag==1)
             	dflag=1;
      	else data=CLR;              	
	lcd_ram[addr1] = Digit_Tbl[data];

      	disp_value %= 100; 
      	data = disp_value/10;     
      	if(data>0 || dflag==1)
              	dflag=1;
      	else data=CLR;              	      	
	lcd_ram[addr2] = Digit_Tbl[data];	
//		if(dflag ==1)lcd_ram[addr3] |= 0x80;  //dsp dot icon		
	data = disp_value%10;     
      	if(data>0 || dflag==1)
              	dflag=1;
      	else data=CLR;             
	lcd_ram[addr3] = Digit_Tbl[data];
		
		if(loadfalg == 0)HT1623_Disp_SomeRam(2*addr3,3,lcd_ram+addr3);
}

//---------------------------------------------------------------------------------------------
void  	Digit_5Num_converse_Process(unsigned char addr1,unsigned char addr2,unsigned char addr3,unsigned char addr4,
		unsigned char addr5,unsigned char dotflag_onoff,unsigned char loadflg,unsigned long disp_value)
{
      	unsigned char data,dflag,loadfalg; 
      	dflag = dotflag_onoff;
      	loadfalg = 	loadflg;
      		
	lcd_ram[addr1] = 0;
	lcd_ram[addr2] = 0;
	lcd_ram[addr3] = 0;	
	lcd_ram[addr4] = 0;
	lcd_ram[addr5] = 0;

	data = disp_value/10000;
      	if(data>0 || dflag==1)
             	dflag=1;
      	else data=CLR;               	    	
	lcd_ram[addr1] = Digit_Tb2[data];
		
	disp_value %= 10000;
	data = disp_value/1000;
      	if(data>0 || dflag==1)
             	dflag=1;
      	else data=CLR;  
      	                 	 	
	lcd_ram[addr2] = Digit_Tb2[data];
      	disp_value %= 1000; 
      	data = disp_value/100;     
      //	if(data>0 || dflag==1)
              	dflag=1;
      //	else data=CLR;
      	
      lcd_ram[addr3] = Digit_Tb2[data];
      	disp_value %= 100; 
      	data = disp_value/10;     
      	//if(data>0 || dflag==1)
        //      	dflag=1;
      //	else data=CLR;
      if(dflag ==1)lcd_ram[addr3] |= 0x01;  //display dot icon 	
      	      	
	lcd_ram[addr4] = Digit_Tb2[data];
//	if(dflag ==1)lcd_ram[addr3] |= 0x80;  //display dot icon 
	lcd_ram[addr5] = Digit_Tb2[disp_value%10];
		
		if(loadfalg == 0)HT1623_Disp_SomeRam(2*addr5,5,lcd_ram+addr5);				
}
//---------------------------------------------------------------------------------
void  	Digit_5Num_Process(unsigned char addr1,unsigned char addr2,unsigned char addr3,unsigned char addr4,
		unsigned char addr5,unsigned char dotflag_onoff,unsigned char loadflg,unsigned int disp_value)
{
      	unsigned char data,dflag,loadfalg; 
      	dflag = dotflag_onoff;
      	loadfalg = 	loadflg;
      		
	lcd_ram[addr1] = 0;
	lcd_ram[addr2] = 0;
	lcd_ram[addr3] = 0;	
	lcd_ram[addr4] = 0;
	lcd_ram[addr5] = 0;

	data = disp_value/10000;
      	if(data>0 || dflag==1)
             	dflag=1;
      	else data=CLR;               	    	
	lcd_ram[addr1] = Digit_Tbl[data];
		
	disp_value %= 10000;
	data = disp_value/1000;
      	if(data>0 || dflag==1)
             	dflag=1;
      	else data=CLR;  
      	                 	 	
	lcd_ram[addr2] = Digit_Tbl[data];
      	disp_value %= 1000; 
      	data = disp_value/100;     
      //	if(data>0 || dflag==1)
              	dflag=1;
      //	else data=CLR;
      	
      lcd_ram[addr3] = Digit_Tbl[data];
      	disp_value %= 100; 
      	data = disp_value/10;     
      	//if(data>0 || dflag==1)
        //      	dflag=1;
      	//else data=CLR;
      	      	
	lcd_ram[addr4] = Digit_Tbl[data];
	//if(dflag ==1)lcd_ram[addr4] |= 0x01;  //display dot icon 
	lcd_ram[addr5] = Digit_Tbl[disp_value%10];
	if(dflag ==1)lcd_ram[addr3] |= 0x01;  //display dot icon 	
		if(loadfalg == 0)
		{
			HT1623_Disp_SomeRam(2*addr1,1,lcd_ram+addr1);
			HT1623_Disp_SomeRam(2*addr2,4,lcd_ram+addr2);				
		}				
}
//---------------------------------------------------------------------------------
void  	Digit_5Num_3nd_Process(unsigned char addr1,unsigned char addr2,unsigned char addr3,unsigned char addr4,
		unsigned char addr5,unsigned char dotflag_onoff,unsigned char loadflg,unsigned int disp_value)
{
      	unsigned char data,dflag,loadfalg; 
      	dflag = dotflag_onoff;
      	loadfalg = 	loadflg;
      		
	lcd_ram[addr1] = 0;
	lcd_ram[addr2] = 0;
	lcd_ram[addr3] = 0;	
	lcd_ram[addr4] = 0;
	lcd_ram[addr5] = 0;

	data = disp_value/10000;
      	if(data>0 || dflag==1)
             	dflag=1;
      	else data=CLR;               	    	
	lcd_ram[addr1] = Digit_Tb3[data];
		
	disp_value %= 10000;
	data = disp_value/1000;
      	if(data>0 || dflag==1)
             	dflag=1;
      	else data=CLR;  
      	                 	 	
	lcd_ram[addr2] = Digit_Tb3[data];
      	disp_value %= 1000; 
      	data = disp_value/100;     
      	//if(data>0 || dflag==1)
              	dflag=1;
      //	else data=CLR;
      	
      lcd_ram[addr3] = Digit_Tb3[data];
      	disp_value %= 100; 
      	//data = disp_value/10;     
      	//if(data>0 || dflag==1)
        //      	dflag=1;
      	//else data=CLR;
      	      	
	lcd_ram[addr4] = Digit_Tb3[data];
	
	lcd_ram[addr5] = Digit_Tb3[disp_value%10];
	if(dflag ==1)lcd_ram[addr5] |= 0x01;  //display dot icon 	
		if(loadfalg == 0)
		{
			//HT1623_Disp_SomeRam(2*addr1,1,lcd_ram+addr1);
			//HT1623_Disp_SomeRam(2*addr2,4,lcd_ram+addr2);		
			if(loadfalg == 0)HT1623_Disp_SomeRam(2*addr1,5,lcd_ram+addr1);			
		}				
}

//---------------------------------------------------------------------------------
void  	Digit_5Num_2nd3nd_Process(unsigned char addr1,unsigned char addr2,unsigned char addr3,unsigned char addr4,
		unsigned char addr5,unsigned char dotflag_onoff,unsigned char loadflg,unsigned int disp_value)
{
      	unsigned char data,dflag,loadfalg; 
      	dflag = dotflag_onoff;
      	loadfalg = 	loadflg;
      		
	lcd_ram[addr1] = 0;
	lcd_ram[addr2] = 0;
	lcd_ram[addr3] = 0;	
	lcd_ram[addr4] = 0;
	lcd_ram[addr5] = 0;

	data = disp_value/10000;
      	if(data>0 || dflag==1)
             	dflag=1;
      	else data=CLR;               	    	
	lcd_ram[addr1] = Digit_Tb3[data];
		
	disp_value %= 10000;
	data = disp_value/1000;
      	if(data>0 || dflag==1)
             	dflag=1;
      	else data=CLR;  
      	                 	 	
	lcd_ram[addr2] = Digit_Tb3[data];
      	disp_value %= 1000; 
      	data = disp_value/100;     
      //	if(data>0 || dflag==1)
              	dflag=1;
      //	else data=CLR;
      	
      lcd_ram[addr3] = Digit_Tb3[data];
      	disp_value %= 100; 
      	data = disp_value/10;     
      //	if(data>0 || dflag==1)
      //        	dflag=1;
      //	else data=CLR;
      	      	
	lcd_ram[addr4] = Digit_Tb3[data];
	if(dflag ==1)lcd_ram[addr5] |= 0x01;  //display dot icon 
	lcd_ram[addr5] = Digit_Tb3[disp_value%10];
		
		if(loadfalg == 0)
		{
			HT1623_Disp_SomeRam(2*addr1,1,lcd_ram+addr1);
			HT1623_Disp_SomeRam(2*addr4,4,lcd_ram+addr4);		
			//if(loadfalg == 0)HT1623_Disp_SomeRam(2*addr1,5,lcd_ram+addr1);			
		}				
}
//----------------------------------------------------------------------------------------------
void  	Digit_4Num_converse_Process(unsigned char addr1,unsigned char addr2,unsigned char addr3,
		unsigned char addr4,unsigned char dotflag_onoff,unsigned char loadflg,unsigned int disp_value)
{
      	unsigned char data,dflag,loadfalg; 
      	dflag = dotflag_onoff;
      	loadfalg = 	loadflg;
      		
	lcd_ram[addr1] = 0;
	lcd_ram[addr2] = 0;
	lcd_ram[addr3] = 0;	
	lcd_ram[addr4] = 0;

	data = disp_value/1000;
      	if(data>0 || dflag==1)
             	dflag=1;
      	else data=CLR;               	    	
		lcd_ram[addr1] = Digit_Tbl[data];
		
	disp_value %= 1000;
	data = disp_value/100;
      	if(data>0 || dflag==1)
             	dflag=1;
      	else data=CLR;                   	 	
	lcd_ram[addr2] = Digit_Tbl[data];

      	disp_value %= 100; 
      	data = disp_value/10;     
      	if(data>0 || dflag==1)
              	dflag=1;
      	else data=CLR;
	lcd_ram[addr3] = Digit_Tbl[data];
//	if(dflag ==1)lcd_ram[addr3] |= 0x80;  //display dot icon 
	lcd_ram[addr4] = Digit_Tbl[disp_value%10];
		
		if(loadfalg == 0)HT1623_Disp_SomeRam(2*addr4,4,lcd_ram+addr4);				
}

void  	Digit_3Num_converse_Process_Clr(unsigned char addr1,unsigned char addr2,unsigned char addr3,
		unsigned char dotflag_onoff,unsigned char loadflg,unsigned int disp_value)
{
      	unsigned char data,dflag,loadfalg; 
      	dflag = dotflag_onoff;
      	loadfalg = 	loadflg;
      		
	lcd_ram[addr1] = 0;
	lcd_ram[addr2] = 0;
	lcd_ram[addr3] = 0;	
	
	data = disp_value/100;
      	if(data>0 || dflag==1)
             	dflag=1;
      	else data=CLR;              	
	lcd_ram[addr1] = Digit_Tbl[data];

      	disp_value %= 100; 
      	data = disp_value/10;     
      	if(data>0 || dflag==1)
              	dflag=1;
      	else data=CLR;              	      	
	lcd_ram[addr2] = Digit_Tbl[data];	
		disp_value %= 10; 
		if(data>0 || dflag==1)
              	dflag=1;
      	else data=CLR;  
	lcd_ram[addr3] = Digit_Tbl[data];		
}

void  	Dig_Hex_To_Bcd_4B(unsigned int hex_value)
{
	unsigned char temp;
 	
 	digit_1000 = hex_value/1000;
 	digit_100 = (hex_value%1000)/100;
 	
 	temp = (hex_value%1000)%100;
 	digit_10 = temp/10;
 	digit_1 = temp%10;
}

void  	Dig_Hex_To_Bcd_5B(unsigned int hex_value)
{
	unsigned int temp;
 	
 	digit_10000 = hex_value/10000;
 	
 	temp = hex_value%10000;
 	digit_1000 = temp/1000;
 	digit_100 = (temp%1000)/100;
 	
 	temp = (temp%1000)%100;
 	digit_10 = temp/10;
 	digit_1 = temp%10;
}

void	Dig_Zero_Omit_4Bit(void)
{
	if(digit_10000 == 0) 
 	{
 		digit_10000 = CLR;
  		if(digit_1000 == 0)
  		{
  			digit_1000 = CLR;
   			if(digit_100 == 0)
   			{
   				digit_100 = CLR;
   				if(digit_10 == 0) digit_10 = CLR;
   			}	 
   		}
  	}
}

void	Dig_Zero_Omit_3Bit(void)
{
	if(digit_1000 == 0) 
 	{
 		digit_1000 = CLR;
  		if(digit_100 == 0)
  		{
  			digit_100 = CLR;
   			if(digit_10 == 0) digit_10 = CLR;
   		}
  	}
}

void	Dig_Zero_Omit_2Bit(void)
{
  	if(digit_100 == 0)
  	{
  		digit_100 = CLR;
   		if(digit_10 == 0) digit_10 = CLR;
   	}
}

#endif
