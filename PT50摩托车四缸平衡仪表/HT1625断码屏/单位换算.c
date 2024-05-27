void Dsp_RUN_Mode(void)
{
//-------------------------------------------------------------------------------	        
	switch(r_unit)
	{
		case 0:			//pa ?????????????
		{
			lcd_ram[ST65] 	|= S66;   	//pa	????
			if(Rec_Data_Display_Num)	//??????1~30
			{
				tempdsp_unit 		=	DATA_ADC1[Rec_Data_Display_Num];
				DATA_Pressure[0] 	= (UINT32)(tempdsp_unit);
				tempdsp_unit_1 =	DATA_ADC2[Rec_Data_Display_Num];
				DATA_Pressure[1] 	= (UINT32)(tempdsp_unit_1);
				tempdsp_unit = DATA_ADC_DIF[Rec_Data_Display_Num];
				DATA_Pressure[2] 	= (UINT32)(tempdsp_unit);
			}
			else					//Rec_Data_Display	==0?
			{
				tempdsp_unit = u32_Positive_Side_Cur_Pressure;
				DATA_Pressure[0] = (UINT32)tempdsp_unit;	//? ??? ???????
				CYL_p_avg[1] = u32_Negative_Side_Cur_Pressure;	
				tempdsp_unit = u32_Negative_Side_Cur_Pressure;
				DATA_Pressure[1] = (UINT32)tempdsp_unit;	//? ???	???????
				tempdsp_unit = CYL_p_avg[2];
				DATA_Pressure[2] = (UINT32)tempdsp_unit;	//? ???? ?????
			}
		}
		break;

		case 1:			//hpa ?????????????
		{
			lcd_ram[ST65] 	|= S65;   	//hpa
			if(Rec_Data_Display_Num)
			{
				tempdsp_unit 		=	DATA_ADC1[Rec_Data_Display_Num];
				DATA_Pressure[0] 	= (UINT32)(tempdsp_unit/10);
				tempdsp_unit_1 		=	DATA_ADC2[Rec_Data_Display_Num];
				DATA_Pressure[1] 	= (UINT32)(tempdsp_unit_1/10);
				tempdsp_unit 		= DATA_ADC_DIF[Rec_Data_Display_Num];
				DATA_Pressure[2] 	= (UINT32)(tempdsp_unit/10);
			}
			else
			{					
				tempdsp_unit = u32_Positive_Side_Cur_Pressure ;
				DATA_Pressure[0] = (UINT32)tempdsp_unit/10;
				tempdsp_unit = u32_Negative_Side_Cur_Pressure;
				DATA_Pressure[1] = (UINT32)tempdsp_unit/10;
				tempdsp_unit = CYL_p_avg[2];
				DATA_Pressure[2] = (UINT32)tempdsp_unit/10;
			}
		}
		break;	

		case 2:			//torr	?????????????
		{
			lcd_ram[ST65] 	|= S67;  	 
			if(Rec_Data_Display_Num)
			{
				tempdsp_unit 		=	DATA_ADC1[Rec_Data_Display_Num]*3000;
				DATA_Pressure[0] 	= (UINT32)(tempdsp_unit/40000);
				
				tempdsp_unit_1 =	DATA_ADC2[Rec_Data_Display_Num]*3000;
				DATA_Pressure[1] 	= (UINT32)(tempdsp_unit_1/40000);
				
				tempdsp_unit = DATA_ADC_DIF[Rec_Data_Display_Num]*3000;
				DATA_Pressure[2] = (UINT32)tempdsp_unit/40000;
			}
			else
			{	      					
				tempdsp_unit_1 = u32_Positive_Side_Cur_Pressure*3000;
				DATA_Pressure[0] = (UINT32)tempdsp_unit_1/40000;
				
		
				tempdsp_unit = u32_Negative_Side_Cur_Pressure*3000;
				DATA_Pressure[1] = (UINT32)tempdsp_unit/40000;
				
				tempdsp_unit = CYL_p_avg[2]*3000;
				DATA_Pressure[2] = (UINT32)tempdsp_unit/40000;	
				
			}	
		}
		break;
	
		case 3:			//mBar	?????????????
		{
			lcd_ram[ST65] 	|= S68; 	 					
			if(Rec_Data_Display_Num)
			{
				tempdsp_unit 		=	DATA_ADC1[Rec_Data_Display_Num];
				DATA_Pressure[0] 	= (UINT32)(tempdsp_unit/10);
				tempdsp_unit_1 =	DATA_ADC2[Rec_Data_Display_Num];
				DATA_Pressure[1] 	= (UINT32)(tempdsp_unit_1/10);
				tempdsp_unit_1 =	DATA_ADC_DIF[Rec_Data_Display_Num];
				DATA_Pressure[2] 	= (UINT32)(tempdsp_unit_1/10);
			}
			else
			{						
				tempdsp_unit = u32_Positive_Side_Cur_Pressure ;
				DATA_Pressure[0] = (UINT32)tempdsp_unit/10;
				tempdsp_unit = u32_Negative_Side_Cur_Pressure;
				DATA_Pressure[1] = (UINT32)tempdsp_unit/10;
				tempdsp_unit = CYL_p_avg[2];
				DATA_Pressure[2] = (UINT32)tempdsp_unit/10;
			}
		}
		break;	
			
		case 4:			//inHg	?????????????
		{
			lcd_ram[ST65] 	|= S69;  	 
			if(Rec_Data_Display_Num)
			{
				tempdsp_unit 		=	DATA_ADC1[Rec_Data_Display_Num]*14765;
				DATA_Pressure[0] 	= (UINT32)(tempdsp_unit/500000);
				tempdsp_unit_1 =	DATA_ADC2[Rec_Data_Display_Num]*14765;
				DATA_Pressure[1] 	= (UINT32)(tempdsp_unit_1/500000);
				tempdsp_unit_1 =	DATA_ADC_DIF[Rec_Data_Display_Num]*14765;
				DATA_Pressure[2] 	= (UINT32)(tempdsp_unit_1/500000);
			}
			else
			{					
				tempdsp_unit = u32_Positive_Side_Cur_Pressure *14765;
				DATA_Pressure[0] = (UINT32)tempdsp_unit/500000;
				tempdsp_unit = u32_Negative_Side_Cur_Pressure*14765;
				DATA_Pressure[1] = (UINT32)tempdsp_unit/500000;
				tempdsp_unit = CYL_p_avg[2]*14765;
				DATA_Pressure[2] = (UINT32)tempdsp_unit/500000;
			}
		}
		break;

		case 5:			//mmHg	?????????????
		{
			lcd_ram[ST65] 	|= S70;		
			if(Rec_Data_Display_Num)
			{
				tempdsp_unit 		=	DATA_ADC1[Rec_Data_Display_Num]*3000;
				DATA_Pressure[0] 	= (UINT32)(tempdsp_unit/40000);
				tempdsp_unit_1 =	DATA_ADC2[Rec_Data_Display_Num]*3000;
				DATA_Pressure[1] 	= (UINT32)(tempdsp_unit_1/40000);
				tempdsp_unit_1 =	DATA_ADC_DIF[Rec_Data_Display_Num]*3000;
				DATA_Pressure[2] 	= (UINT32)(tempdsp_unit_1/40000);
			}
			else
			{						
				tempdsp_unit = u32_Positive_Side_Cur_Pressure*3000;
				DATA_Pressure[0] = (UINT32)tempdsp_unit/40000;
				tempdsp_unit = u32_Negative_Side_Cur_Pressure*3000;
				DATA_Pressure[1] = (UINT32)tempdsp_unit/40000;
				tempdsp_unit = CYL_p_avg[2] *3000;
				DATA_Pressure[2] = (UINT32)tempdsp_unit/40000;
			}
		}
		break;
				
		default:
		break;      
	}
}	