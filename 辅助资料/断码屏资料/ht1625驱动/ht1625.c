#include "HT66F2372.h"
#include "define.h"
#include "digit.h"
#include "display.h"
#include "ht1625_display.h"
#include "power.h"

//#define HT1623_PIN_LEVEL
/*
				//dcegbfa
const char digit_table1[] =   { 0b11101110,  // '0'   
                                0b01001000,  // '1'      
                                0b10111010,  // '2'          
                                0b11011010,  // '3'	   
                                0b01011100,  // '4'		
                                0b11010110,  // '5'
                                0b11110110,  // '6'
                                0b01001010,  // '7'
                                0b11111110,  // '8'
                                0b11011110,  // '9'  
                                0b00000000,  // CLR                             
                              };                
				//afbgecd       
const char digit_table2[] =   { 0b11101110,  // '0' 
                                0b00100100,  // '1'
                                0b10111010,  // '2'
                                0b10110110,  // '3'
                                0b01110100,  // '4'
                                0b11010110,  // '5'
                                0b11011110,  // '6'
                                0b10100100,  // '7'
                                0b11111110,  // '8'
                                0b11110110,  // '9'   
                                0b00000000,  // CLR                            
                              };
                              */
      
void  HT1623_SendData_Lcd(unsigned short len,unsigned short data);


void  HT1623_Intial(void)
{
//        HT1623PWR_TRIS = 0;	
	HT1623CS_TRIS = 0;	
	HT1623WR_TRIS = 0;	
	HT1623RD_TRIS = 0;	
	HT1623DATA_TRIS = 0;        
	
//	HT1623PWR_PORT = 0;
	HT1623CS_PORT = 0;
	HT1623WR_PORT = 0;
	HT1623RD_PORT = 0;
//	HT1623DATA_LAT = 0;
}

/*函数功能：HT1625初始化*/
void  HT1623_PWROn(void)
{
//	LATBbits.LATB2 = 0;
//	LATEbits.LATE5 = 0;
//	HT1623PWR_PORT = 1;		// Power on

	DelayMs(100);
#ifdef  HT1623_PIN_LEVEL
	HT1623CS_PORT = 1;		// It must initial when power on
	HT1623WR_PORT = 1;		
	HT1623DATA_PORT = 1;
#else	
	HT1623CS_PORT = 0;		// It must initial when power on
	HT1623WR_PORT = 0;		
	HT1623DATA_PORT = 0;
#endif
        DelayMs(100);

#ifdef  HT1623_PIN_LEVEL
	HT1623CS_PORT = 0;		// It must initial when power on
	HT1623CS_PORT = 0;		// It must initial when power on
	HT1623WR_PORT = 0;		
	HT1623RD_PORT = 0;
	HT1623DATA_PORT = 0;
#else	
	HT1623CS_PORT = 1;		// It must initial when power on
	HT1623CS_PORT = 1;		// It must initial when power on
	HT1623WR_PORT = 1;		
	HT1623RD_PORT = 1;
	HT1623RD_PORT = 1;
	HT1623DATA_PORT = 1;
#endif	

       	Nop();Nop();Nop();Nop();Nop(); 
       	Nop();Nop();Nop();Nop();Nop();
       	Nop();Nop();Nop();Nop();Nop();
       	Nop();Nop();Nop();Nop();Nop();
       	Nop();Nop();Nop();Nop();Nop(); 

#ifdef  HT1623_PIN_LEVEL
        HT1623CS_PORT = 1;
#else
        HT1623CS_PORT = 0;
#endif        
       	Nop();Nop();Nop();Nop();Nop();
       	Nop();Nop();Nop();Nop();Nop();
       	Nop();Nop();Nop();Nop();Nop();
       	Nop();Nop();Nop();Nop();Nop(); 
       	Nop();Nop();Nop();Nop();Nop(); 
 // Configure the HT1623 feature
        HT1623_SendData_Lcd(3,0x4);  // send command: 100
        HT1623_SendData_Lcd(9,0x3);  //send : 0000 0001 1 to turn on osc        
        //HT1623_SendData_Lcd(9,0x4f); //3 commons 1/2 bias:  0010 0111 1        
        HT1623_SendData_Lcd(9,0x1f); //send : 0000 1111 1 to clr tb and wdt
        HT1623_SendData_Lcd(9,0xb);  // send : 0000 0101 1 to disable wdt
//        HT1623_SendData_Lcd(9,0x9);  // send : 0000 0100 1 to disable Time       
        HT1623_SendData_Lcd(9,0x1c7);  // send : 1110 0011 1 to normal
        HT1623_SendData_Lcd(9,0x7);  //send : 0000 0011 1 to LCD on     

#ifdef  HT1623_PIN_LEVEL
        HT1623CS_PORT = 0; 
#else
        HT1623CS_PORT = 1; 
#endif        
        
}

void  HT1623_PWROff(void)
{
//	LATBbits.LATB2 = 1;
//	HT1623PWR_PORT = 0;		// Power off
	
	HT1623WR_PORT = 0;		// with HT1623 pin connected must output low
	HT1623DATA_LAT = 0;
	HT1623RD_PORT = 0;
	HT1623CS_PORT = 0;
}

//////////////////////////////////////////////////////////////////////
void  HT1623_Write_Bit(void)
{
       	Nop();Nop();Nop();Nop();
       	Nop();Nop();Nop();Nop();
       	Nop();Nop();Nop();Nop();
#ifdef  HT1623_PIN_LEVEL
       	HT1623WR_PORT = 1;       
#else
       	HT1623WR_PORT = 0;       
#endif       	
       	Nop();Nop();Nop();Nop();   
       	Nop();Nop();Nop();Nop();   
       	Nop();Nop();Nop();Nop();   
       	Nop();Nop();Nop();Nop();       
       	Nop();Nop();Nop();Nop();   
       	Nop();Nop();Nop();Nop();   
       	Nop();Nop();Nop();Nop();   
       	Nop();Nop();Nop();Nop();       
       	Nop();Nop();Nop();Nop();   

#ifdef  HT1623_PIN_LEVEL
       	HT1623WR_PORT = 0; 
#else
       	HT1623WR_PORT = 1; 
#endif       	
       	Nop();Nop();Nop();Nop();
       	Nop();Nop();Nop();Nop();
       	Nop();Nop();Nop();Nop();
       	Nop();Nop();Nop();Nop();
       	Nop();Nop();Nop();Nop();
       	Nop();Nop();Nop();Nop();
       	Nop();Nop();Nop();Nop(); 
       	Nop();Nop();Nop();Nop();
       	Nop();Nop();Nop();Nop();
       	Nop();Nop();Nop();Nop(); 
       	Nop();Nop();Nop();Nop();

}

void  HT1623_Read_Bit(void)
{
       	Nop();Nop();Nop();Nop();
       	Nop();Nop();Nop();Nop();
       	Nop();Nop();Nop();Nop();
       	Nop();Nop();Nop();Nop();
       	Nop();Nop();Nop();Nop();
       	Nop();Nop();Nop();Nop();
       	Nop();Nop();Nop();Nop();
       	Nop();Nop();Nop();Nop();
       	Nop();Nop();Nop();Nop();
#ifdef  HT1623_PIN_LEVEL
       	HT1623RD_PORT = 1;       
#else
       	HT1623RD_PORT = 0;       
#endif       	
       	Nop();Nop();Nop();Nop(); 
       	Nop();Nop();Nop();Nop();       
       	Nop();Nop();Nop();Nop();   
       	Nop();Nop();Nop();Nop(); 
       	Nop();Nop();Nop();Nop();       
       	Nop();Nop();Nop();Nop();   
       	Nop();Nop();Nop();Nop();   
       	Nop();Nop();Nop();Nop();       
#ifdef  HT1623_PIN_LEVEL
       	HT1623RD_PORT = 0; 
#else
       	HT1623RD_PORT = 1; 
#endif       	
}
      
/////////////////////////////////////////////////////////////////////
void  HT1623_SendData_Lcd(unsigned short len,unsigned short data)
{
     	unsigned short i,sdata;
//        M_Switch_Clk(NOSC_PRI);
     	sdata=0;
#ifdef  HT1623_PIN_LEVEL
       	HT1623RD_PORT = 0; 
#else
       	HT1623RD_PORT = 1; 
#endif       	
     	if(len!=4)
     	{
         for (i=len;i>0;i--) //reverse the data
         {
            sdata<<=1;
            sdata += data & 0x1;
            data>>=1;
         }       
     	}
     	else sdata=data;
     
     	for(i=len;i>0;i--)// send out data
     	{
         HT1623WR_PORT = 0;       	// WR data must be low before send data
         Nop();
         Nop();
#ifdef  HT1623_PIN_LEVEL
         if((sdata & 0x1)==1)
             HT1623DATA_LAT = 0; 
         else    
             HT1623DATA_LAT = 1; 
#else
         if((sdata & 0x1)==1)
             HT1623DATA_LAT = 1; 
         else    
             HT1623DATA_LAT = 0; 
#endif             
         HT1623_Write_Bit();
                     
         sdata>>=1;     
     	}
#ifdef  HT1623_PIN_LEVEL
        HT1623DATA_LAT = 0; 		// add on 2009/02/13
#else        
        HT1623DATA_LAT = 1; 
#endif        
}

unsigned char  HT1623_ReadData_Lcd(void)
{
     	unsigned short i,sdata;
	// unsigned int b;

	sdata = 0;

	HT1623DATA_TRIS = 1;	// set DATA to input
	//HT1623DATA_LAT = 0;
	Nop();
	Nop();
	Nop();
     	for(i=4;i>0;i--)
     	{      
           sdata>>=1;     
           //HT1623_Write_Bit();
           HT1623_Read_Bit();
	   //b= PORTB;
           if(HT1623DATA_PORT)
           //if (b & 0x4000)
             	sdata |= 0x80; 
     	}
     	sdata>>=4;
	HT1623DATA_TRIS = 0;	// set DATA to output    	
#ifdef  HT1623_PIN_LEVEL
	HT1623DATA_LAT = 0;
#else	
	HT1623DATA_LAT = 1;
#endif
   	return ((unsigned char)sdata);
}

void	HT1623_ReadData_From_Lcd(unsigned char addr,unsigned char value,unsigned char opr)
{
    	volatile unsigned char byte;
        unsigned int p;
        unsigned char point;

#ifdef  HT1623_PIN_LEVEL
	HT1623CS_PORT = 1;
#else	
	HT1623CS_PORT = 0;
#endif	
	
	point = addr;
	addr += point;
	HT1623_SendData_Lcd(3,5);       // The program is used to read data
	HT1623_SendData_Lcd(7,addr);	// then modify the data
	Nop();Nop();Nop();		
	byte = HT1623_ReadData_Lcd();
     	p = byte;
     	if (opr) p |= value;
	else	p ^= value;

     	HT1623_SendData_Lcd(4,p);
	Nop();
	Nop();

#ifdef  HT1623_PIN_LEVEL
	HT1623CS_PORT = 0;		// End
#else
	HT1623CS_PORT = 1;		// End
#endif	
/*	
	Nop();Nop();Nop();Nop();
	Nop();Nop();Nop();Nop();         	

	HT1623CS_PORT = 0;		// The part is used to read data from HT1623
	Nop();Nop();Nop();Nop();
	HT1623_SendData_Lcd(3,6);
	HT1623_SendData_Lcd(7,addr);
	byte = HT1623_ReadData_Lcd();
	Nop();Nop();Nop();Nop();
	HT1623CS_PORT = 1;		// End
*/	
}

/////////////////////////////////////////////////////////////////////
void HT1623_lcdOFF(void)
{
#ifdef  HT1623_PIN_LEVEL
	HT1623CS_PORT = 1;     //clear cs= 0
#else
	HT1623CS_PORT = 0;     //clear cs= 0
#endif	
	Nop();Nop();Nop();Nop();Nop();
	Nop();Nop();Nop();Nop();Nop();
	Nop();Nop();Nop();Nop();Nop();
   	HT1623_SendData_Lcd(3,0x4); // send command: 100
   	HT1623_SendData_Lcd(9,0x0); //send : 0000 0001 1 to turn on osc   
   	Nop();Nop();Nop();Nop();Nop();        
   	Nop();Nop();Nop();Nop();Nop();        
   	Nop();Nop();Nop();Nop();Nop();        
#ifdef  HT1623_PIN_LEVEL
   	HT1623CS_PORT = 0;       
#else
   	HT1623CS_PORT = 1;       
#endif   	
}
void HT1623_lcdON(void)
{
#ifdef  HT1623_PIN_LEVEL
   	HT1623CS_PORT = 1;     //clear cs= 0
#else
   	HT1623CS_PORT = 0;     //clear cs= 0
#endif   	
   	Nop();Nop();Nop();Nop();Nop();
   	Nop();Nop();Nop();Nop();Nop();
   	Nop();Nop();Nop();Nop();Nop();
   	HT1623_SendData_Lcd(3,0x4); // send command: 100
   	HT1623_SendData_Lcd(9,0x2); //send : 0000 0001 1 to turn on osc       
   	HT1623_SendData_Lcd(9,0x6); //send : 0000 0001 1 to turn on osc          
   	Nop();Nop();Nop();Nop();Nop();        
   	Nop();Nop();Nop();Nop();Nop();        
   	Nop();Nop();Nop();Nop();Nop();        
#ifdef  HT1623_PIN_LEVEL
   	HT1623CS_PORT = 0;
#else
   	HT1623CS_PORT = 1;
#endif   	
}
/*********************************************************************   
 * Function Description:  It write one byte address value
 *
 ********************************************************************/
void HT1623_WritedataTolcd(unsigned char adr,unsigned char data)
{
#ifdef  HT1623_PIN_LEVEL
     	HT1623CS_PORT = 1;     //clear cs= 0
#else
     	HT1623CS_PORT = 0;     //clear cs= 0
#endif     	
     	Nop();Nop();Nop();Nop();Nop();
     	Nop();Nop();Nop();Nop();Nop();
     	Nop();Nop();Nop();Nop();Nop();
     	HT1623_SendData_Lcd(3,5);
     	HT1623_SendData_Lcd(7,adr);
     	HT1623_SendData_Lcd(4,data);
     	Nop();Nop();Nop();Nop();Nop();        
     	Nop();Nop();Nop();Nop();Nop();        
#ifdef  HT1623_PIN_LEVEL
     	HT1623CS_PORT = 0;
#else
     	HT1623CS_PORT = 1;
#endif     	
}        

void HT1623_WritebyteTolcd(unsigned char adr,unsigned char data)
{
#ifdef  HT1623_PIN_LEVEL
     	HT1623CS_PORT = 1;     //clear cs= 0
#else
     	HT1623CS_PORT = 0;     //clear cs= 0
#endif     	
     	Nop();Nop();Nop();Nop();Nop();
     	Nop();Nop();Nop();Nop();Nop();
     	Nop();Nop();Nop();Nop();Nop();
     	HT1623_SendData_Lcd(3,5);
     	HT1623_SendData_Lcd(7,adr);
     	HT1623_SendData_Lcd(4,data);
     	HT1623_SendData_Lcd(4,data>>4);
     	Nop();Nop();Nop();Nop();Nop();        
     	Nop();Nop();Nop();Nop();Nop();        
#ifdef  HT1623_PIN_LEVEL
     	HT1623CS_PORT = 0;
#else
     	HT1623CS_PORT = 1;
#endif     	
}        

void  HT1623_ramdump(unsigned char data)
{
       	unsigned int i=0;
       	
#ifdef  HT1623_PIN_LEVEL
       	HT1623CS_PORT = 1;  //clear cs=0
#else
       	HT1623CS_PORT = 0;  //clear cs=0
#endif       	
       	Nop();
       	Nop();
       	Nop();
       	Nop();
       	Nop();
       	Nop();
       	Nop();
       	Nop();
       	Nop();
       	Nop();
       	Nop();
       	Nop();
       	Nop();
       	Nop();
       	HT1623_SendData_Lcd(3,0x5);  // send command: 101
       	HT1623_SendData_Lcd(7,0x0);  // send start address: 0000000
       	for  (i=0 ; i<128 ; i++)
       	{
            HT1623_SendData_Lcd(4,data);  //send data
       	}
       	Nop();
       	Nop();       
       	Nop();
       	Nop();       
#ifdef  HT1623_PIN_LEVEL
       	HT1623CS_PORT = 0;
#else
       	HT1623CS_PORT = 1;
#endif       	
}

/*HT1625连续写入函数
函数功能：将buf里的数据连续写入到HT1625的RAM中，并更新到LCD
参数	addr:	要写入的显存RAM地址
		pcs:	写入长度
		buf:	要写入的数据指针
*/
void    HT1623_Disp_SomeRam(unsigned char addr,unsigned char pcs,volatile unsigned char *buf)
{
       	unsigned int i=0;
       	unsigned char data;
       	
#ifdef  HT1623_PIN_LEVEL
       	HT1623CS_PORT = 1;  //clear cs=0
#else
       	HT1623CS_PORT = 0;  //clear cs=0
#endif       	
       	Nop();
       	Nop();
       	Nop();
       	Nop();
       	Nop();
       	Nop();
       	HT1623_SendData_Lcd(3,0x5);  // send command: 101
       	HT1623_SendData_Lcd(7,addr);  // send start address: 0000000
       	for  (i=0 ; i<pcs ; i++)
       	{
       	    data = *buf++;	
            HT1623_SendData_Lcd(4,data);  //send data
            data >>= 4;
            HT1623_SendData_Lcd(4,data);  //send data
       	}
       	Nop();
       	Nop();       
       	Nop();
       	Nop();       
#ifdef  HT1623_PIN_LEVEL
       	HT1623CS_PORT = 0;
#else
       	HT1623CS_PORT = 1;
#endif       	
}

void  HT1623_dispDigit(unsigned char htdis_addr,unsigned char htvalue,unsigned char icon,unsigned char font)
{
       	unsigned int ht_pointer,cal_i;
       
       	cal_i = htdis_addr;
       	htdis_addr += cal_i;
       	ht_pointer = htvalue;

      // 	if (font)		// font = 1 -> table1, = 0 -> table2
      //  	htvalue = Digit_Tbl[ht_pointer];
 	//else
     //   	htvalue = Digit_Tb2[ht_pointer];

       	if (icon == 1) htvalue |= 0x01;	       	     
        HT1623_WritebyteTolcd(htdis_addr,htvalue);
/*
        HT1623_WritedataTolcd(htdis_addr,htvalue);

        //ht_pointer ++;
        htdis_addr ++;
        //htvalue = tab_disdat[ht_pointer];
        htvalue >>= 4;
        HT1623_WritedataTolcd(htdis_addr,htvalue);
*/
}

void  HT1623_displayInt(unsigned char startPosi,unsigned int display_data,unsigned char font,
                        unsigned char icon1,unsigned char icon2,unsigned char icon3,unsigned char icon4)
{
      	unsigned char data,dflag; 
      	dflag=0;
/*
      	data=display_data/10000;
      	if(data>0)
        	dflag=1;
      	else data=CLR;
      
      	HT1623_dispDigit(startPosi++,data,0,font);
      	display_data %= 10000;      
*/      	
      	data=display_data/1000;      
      
      	if(data>0 || dflag==1)
              	dflag=1;
      	else data=CLR;

      	HT1623_dispDigit(startPosi++,data,icon1,font);

      	display_data %= 1000;    
      	data=display_data/100;    

      	if(data>0 || dflag==1)
             	dflag=1;
      	else data=CLR;

      	HT1623_dispDigit(startPosi++,data,icon2,font);

      	display_data %= 100;      
      	data=display_data/10;    
      	if(data>0 || dflag==1)
        	dflag=1;
      	else data=CLR;

      	HT1623_dispDigit(startPosi++,data,icon3,font);
      
      	HT1623_dispDigit(startPosi++,display_data%10,icon4,font);
      	//HT1623_WritedataTolcd(0,0x4);    //display heart   
}

//void  HT1623_Disp999(unsigned char startPosi,unsigned int display_data, unsigned char icon1,
//            unsigned char icon2, unsigned char icon3,unsigned char seq,unsigned char font)
//{
//      	unsigned char data,dflag; 
//      	dflag=0;
//      	if (display_data>999)display_data=999;
//
//      	data=display_data/100;    
//      	if(data>0)
//         	dflag = 1;
//      	else    data = CLR;
//
//      	HT1623_dispDigit(startPosi,data,icon1,font);
//      
//      	display_data %= 100; 
//      	data = display_data/10;     
//
//      	if(data>0 || dflag==1)
//             dflag = 1;
//      	else data = CLR;
//      	
//      	if (seq) startPosi++;		// seq = 1 -> address add sequance
//      	else  startPosi--;		// seq = 0 -> address dec sequance
//      
//      	HT1623_dispDigit(startPosi,data,icon2,font);
//
//      	if (seq) startPosi++;
//      	else  startPosi--;
//
//      	HT1623_dispDigit(startPosi,display_data%10,icon3,font);
//      //HT1623_WritedataTolcd(0,0x4);    //display heart   
//}

void  HT1623_displayTwoDigit(unsigned char startPosi,unsigned char display_data,unsigned char icon1,unsigned char icon2,unsigned char font)
{
      	HT1623_dispDigit(startPosi++,display_data/10,icon1,font);
      	HT1623_dispDigit(startPosi++,display_data%10,icon2,font);
}

void  HT1623_displayTwoDigit1(unsigned char startPosi,unsigned char display_data,unsigned char icon1,unsigned char icon2,unsigned char font)
{
      	HT1623_dispDigit(startPosi--,display_data/10,icon1,font);
      	HT1623_dispDigit(startPosi--,display_data%10,icon2,font);
}


