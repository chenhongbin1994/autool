/********************************************
Programmer : zhang qi wu
Project Name: FB60 (Nautilus Project for Fitness Equipment
Supplement Documents: Function Specifiction
MCU: Microchip PIC24F
********************************************/
#include "display.h"
#include "digit.h"
#include "display.h"
#include "LCD_HT1623.h"
//#include "power.h"



#if 0
void	Dsp_ClrRam_Except_Batt(void);
void	Dsp_BattIcon_Flash(void);
void	Dsp_ErrorIcon_Flash(void);
void	Dsp_Auto_Cali(void);
void    Dsp_RUN_Mode(void);


volatile unsigned short int dsp_bike_miss;
volatile unsigned short int dsp_pwr_miss;
volatile unsigned short int dsp_miss_timer;


volatile unsigned char dsp_main_mode;
volatile unsigned char dsp_sub_mode;
volatile unsigned char dsp_sub_mode2;

volatile unsigned char dsp_rpm_lit;
volatile char hr_icon_on_cnt;
volatile char dsp_4hz_cnt;
volatile char pwr_999_flag;
volatile char cal_1999_flag;
volatile char dst_9999_flag;

volatile DSP_FLAG dsp_flag;
volatile DSP_ZONE dsp_zone_flag;

volatile unsigned long  pdsp_max,pdsp_min,pdsp_avg,pdsp_relative;

#define Tone4k 0x40
#define Tone2k 0x60



void	Dsp_FullOn(void)
{
//	HT1623_ramdump(0xff);
	unsigned char i;
	
       	for (i=0;i<38;i++)
      	     lcd_ram[i] = 0xff;
    	HT1623_Disp_SomeRam(0,38,lcd_ram);
}

void	Dsp_FullOff(void)
{
	HT1623_ramdump(0x00);	
}

void	Dsp_Lcdram_Clr_Except_Batt(void)
{
	unsigned char i;

       	for (i=0;i<14;i++)
       		lcd_ram[i] = 0x0;
//       	lcd_ram[ST46] &= 0x04;	
       	for (i=15;i<37;i++)
       		lcd_ram[i] = 0x0;
       	lcd_ram[37] &= 0x0F;          	     
}	


void	Dsp_ServiceCali(void)
{
	unsigned char i;
  	unsigned char dsp_timer;  	
    unsigned long temp;

 
}

void Dsp_RUN_Mode(void)
{
	unsigned char i,j;
	unsigned long temp;
	j = lcd_ram[44];
	
	 for (i=0;i<64;i++)
             lcd_ram[i] = 0x0;
             
             
         	test_char1= 1234;
	        test_char2 += 1111;
	        if(test_char2>10000)
	        {
	        	test_char2 = 0;
	        }
	        
	        		if(english_flag == 1) //enlish-->1,china-->0
			{
				
				
    	
    			
    			switch(r_unit)
	    		{
	      			case 0:
	      					Digit_5Num_converse_Process(D1,D2,D3,D4,D5,0,1,r_Psi_data);//;p_DspRelative);	//f
	        				Digit_5Num_Process(D6,D7,D8,D9,D10,0,1,Psip_max_dps);	//f
	        				Digit_5Num_3nd_Process(D11,D12,D13,D14,D15,0,1,Psip_min_dps);
	        				Digit_5Num_Process(D16,D17,D18,D19,D20,0,1,Psip_avg_dps);//TEMP_CF);
	      					
	      					//english_flag = 1;
	      					
	      					lcd_ram[D11] 	|= T10;	 	// Psi
							lcd_ram[D14] 	|= T13; 	// Psi
							//r_Psi_data
	      			break;
	      			case 1:
	      					pdsp_relative = p_relative/100;
	      					pdsp_max = p_max/10;//p_relative/1000;
	      					pdsp_min = p_min/10;
	      					pdsp_avg = p_avg/10;
	      			
	      				  	Digit_5Num_converse_Process(D1,D2,D3,D4,D5,0,1,pdsp_relative);//;p_DspRelative);	//f
	        				Digit_5Num_Process(D6,D7,D8,D9,D10,0,1,pdsp_max);	//f
	        				Digit_5Num_3nd_Process(D11,D12,D13,D14,D15,0,1,pdsp_min);
	        				Digit_5Num_Process(D16,D17,D18,D19,D20,0,1,pdsp_avg);//TEMP_CF);

							//english_flag = 0;
								 
    						lcd_ram[D12] 	|= T11;   	//Bar   	
    						lcd_ram[D20] 	|= T14;   	//Bar  
    						//p_relative 	        	       	        
	      			break;	
	      			case 2:
	      				    Digit_5Num_converse_Process(D1,D2,D3,D4,D5,0,1,r_kg_cm2_data);//;p_DspRelative);	//f
	        				Digit_5Num_Process(D6,D7,D8,D9,D10,0,1,Kgcm2p_max_dps);	//f
	        				Digit_5Num_3nd_Process(D11,D12,D13,D14,D15,0,1,Kgcm2p_min_dps);
	        				Digit_5Num_Process(D16,D17,D18,D19,D20,0,1,Kgcm2p_avg_dps);//TEMP_CF);

	      					//english_flag = 1;
	      					
	        	     	    lcd_ram[D13] 	|= T12; 	 //Kg/cm2
    						lcd_ram[D19] 	|= T15; 	 //Kg/cm2   
    						//r_kg_cm2_data   	        
	      			break;
	      			default:
                  
		  			break;      
    			}					    				
    			lcd_ram[D1] 	|= T8;    	//PRESSURE ENGLISH
    			lcd_ram[D22] 	|= T18;		//	T4_F;   	
    			lcd_ram[D9] 	|= P2;		//	T4_F; 	
			}
			else
			{											
				switch(r_unit)
	    		{
	      			case 0:
	      					lcd_ram[D11] 	|= T10;	 	// Psi
							lcd_ram[D14] 	|= T13; 	// Psi
							
								english_flag = 1;
	      			break;
	      			case 1:
    						lcd_ram[D12] 	|= T11;   	//Bar   	
    						lcd_ram[D20] 	|= T14;   	//Bar   	 
    						
    							english_flag = 0;       	       	        
	      			break;	
	      			case 2:
	        	     	    lcd_ram[D13] 	|= T12; 	 //Kg/cm2
    						lcd_ram[D19] 	|= T15; 	 //Kg/cm2     
    						
    							english_flag = 1; 	        
	      			break;
	      			default:
                  
		  			break;      
    			}			
    		   	lcd_ram[D2] 	|= T9; //PRESSURE CHINA			    					   				   				
				lcd_ram[D21] 	|= T17;		//T2_C;					
			}
	        
	        //Digit_4Num_Process(D24,D25,D26,D27,0,0,test_char2);//p_relative);
	      //  Digit_5Num_converse_Process(D1,D2,D3,D4,D5,1,1,p_DspRelative);//;p_DspRelative);	//f
	        
	      //  Digit_5Num_Process(D6,D7,D8,D9,D10,0,1,P_dspE);	//f
	      //  Digit_5Num_3nd_Process(D11,D12,D13,D14,D15,0,1,P_dsp);
	      //  Digit_5Num_Process(D16,D17,D18,D19,D20,1,1,TEMP_CF20);//TEMP_CF);
	        
	        if(english_flag == 0)
	        {
	        	Digit_5Num_2nd3nd_Process(D21,D22,D23,D24,D25,0,1,TEMP_CF);
	        	lcd_ram[D21] 	|= T17;		//T2_C;
	        }
	        else
	        {
	        	Digit_5Num_2nd3nd_Process(D21,D22,D23,D24,D25,0,1,TEMP_F_dsp);
	        	lcd_ram[D22] 	|= T18;		//	T4_F;   
	        }
	       
	        //Digit_4Num_Process(D20,D21,D22,D23,0,1,test_char1);
	        
//	        Digit_5Num_Process(D28,D29,D30,D31,D32,0,1,P_dspTest);    
             
			Digit_2Num_converse_Process(D26,D27,0,1,run_min);
  			Digit_2Num_converse_Process(D28,D29,1,1,run_sec);
		

			
			lcd_ram[D17] 	|= T19;	// TEMP
			lcd_ram[D25] 	|= P5;	// TEMP p
			
			if(g_bit_lingt_onoff_flag ==1)
			{
				lcd_ram[D4] 	|= T6;	// LIGHT LED
			}
			else
			{
			//	lcd_ram[D4] 	= ~T6;	// LIGHT LED
			}
			
			lcd_ram[D24] 	|= T16;	//TIME
			
			//lcd_ram[D5] 	|= T7;	//BUZER
			
		
			lcd_ram[ST1] 	|= T1; 	//BATTER ICON
			lcd_ram[ST1] 	|= T2;
			lcd_ram[ST1] 	|= T3;
			lcd_ram[ST1] 	|= T4;
			lcd_ram[ST1] 	|= T5;
			
			lcd_ram[D16] 	|= T20;	// AVG
			lcd_ram[D7] 	|= T21;	// MIN
			lcd_ram[D8] 	|= T22;	// MAX
			


//==================== batt icon display =====================			
			//r_bat_icon_grade
			
			switch(r_bat_icon_grade)
	    		{
	      			case 0:
	      					lcd_ram[ST1] 	= 0x1f;	 	// all batt icon display						
	      			break;
	      			case 1:
    						lcd_ram[ST1] 	= T1;   	//   t1	
    						//lcd_ram[ST1] 	|= T5;   	//   t5   	        	       	        
	      			break;	
	      			case 2:
	        				lcd_ram[ST1] 	= T1;   	//   t1	
    						lcd_ram[ST1] 	|= T5;   	//   t5   	     
    						//lcd_ram[ST1] 	|= T4;   	//   t4    
	      			break;
	      			case 3:
	      					lcd_ram[ST1] 	= T1;   	//   t1	
    						lcd_ram[ST1] 	|= T5;   	//   t5   	     
    						lcd_ram[ST1] 	|= T4;   	//   t4    
    						//lcd_ram[ST1] 	|= T3;   	//   t3    
	      			break;
	      			case 4:
    						lcd_ram[ST1] 	= T1;   	//   t1	
    						lcd_ram[ST1] 	|= T5;   	//   t5   	     
    						lcd_ram[ST1] 	|= T4;   	//   t4    
    						lcd_ram[ST1] 	|= T3;   	//   t3    	        	       	        
	      			break;	
	      			case 5:
	        	 			lcd_ram[ST1] 	= T1;   	//   t1	
    						lcd_ram[ST1] 	|= T5;   	//   t5   	     
    						lcd_ram[ST1] 	|= T4;   	//   t4    
    						lcd_ram[ST1] 	|= T3;   	//   t3        
    						lcd_ram[ST1] 	|= T2;   	//   t2      	        
	      			break;
	      			default:
                  
		  			break;      
    			}
//===========================================================

				if(g_bit_buzzer_flag == 1)
				{
					lcd_ram[D5] 	|= 0x01;		//T7 buzzer;					
				}
				else
				{
				//	lcd_ram[D5] 	= ~0x01;		//T7 buzzer;
					
				}
	


			
//============================================================			
			HT1623_Disp_SomeRam(0,38,lcd_ram);
}


#endif

