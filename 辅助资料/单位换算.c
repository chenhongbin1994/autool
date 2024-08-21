void disp_Pressure_update()
{
	double p1_fb,p2_fb;
	
	if(ui_interface	!= T_Evacuation)
	{
		if(type_p == 0)
		{
			p1_fb = p1_value;
			p2_fb = p2_value;
			switch(unit_p)
			{
				case 0:
					p1_fb /= 10000;
					float2char(p1_fb,p1_string,2);
					p2_fb /= 10000;
					float2char(p2_fb,p2_string,2);
				break;
				case 1:
					p1_fb /= 10000;
					p1_fb *=14.5037;
					float2char(p1_fb,p1_string,1);
					p2_fb /= 10000;
					p2_fb *=14.5037;
					float2char(p2_fb,p2_string,1);
				break;
				case 2:
					p1_fb /= 100;
					float2char(p1_fb,p1_string,0);
					p2_fb /= 100;
					float2char(p2_fb,p2_string,0);
				break;
				case 3:
					p1_fb /= 100000;
					float2char(p1_fb,p1_string,3);
					p2_fb /= 100000;
					float2char(p2_fb,p2_string,3);
				break;
				case 4:
					p1_fb /= 10000;
					p1_fb *=1.0197;
					float2char(p1_fb,p1_string,2);
					p2_fb /= 10000;
					p2_fb *=1.0197;
					float2char(p2_fb,p2_string,2);
				break;
				case 5:
					p1_fb /= 10000;
					p1_fb *=29.5299;
					float2char(p1_fb,p1_string,1);
					p2_fb /= 10000;
					p2_fb *=29.5299;
					float2char(p2_fb,p2_string,1);
				break;
			}
		}
		else
		{
			p1_fb = Pre_abs1;
			p2_fb = Pre_abs2;
			switch(unit_p)
			{
				case 0:
					p1_fb /= 10000;
					float1char(p1_fb,p1_string,2);
					p2_fb /= 10000;
					float1char(p2_fb,p2_string,2);
				break;
				case 1:
					p1_fb /= 10000;
					p1_fb *=14.5037;
					float1char(p1_fb,p1_string,1);
					p2_fb /= 10000;
					p2_fb *=14.5037;
					float1char(p2_fb,p2_string,1);
				break;
				case 2:
					p1_fb /= 100;
					float1char(p1_fb,p1_string,0);
					p2_fb /= 100;
					float1char(p2_fb,p2_string,0);
				break;
				case 3:
					p1_fb /= 100000;
					float1char(p1_fb,p1_string,3);
					p2_fb /= 100000;
					float1char(p2_fb,p2_string,3);
				break;
				case 4:
					p1_fb /= 10000;
					p1_fb *=1.0197;
					float1char(p1_fb,p1_string,2);
					p2_fb /= 10000;
					p2_fb *=1.0197;
					float1char(p2_fb,p2_string,2);
				break;
				case 5:
					p1_fb /= 10000;
					p1_fb *=29.5299;
					float1char(p1_fb,p1_string,1);
					p2_fb /= 10000;
					p2_fb *=29.5299;
					float1char(p2_fb,p2_string,1);
				break;
			}
		}
	}
	else
	{
		p1_fb = Pre_abs1;
		p2_fb = Pre_abs2;
		switch(unit_vac)
		{
			case 0:
			case 1:	
				p1_fb /= 10;
				float2char(p1_fb,p1abs_string,1);
				p2_fb /= 10;
				float2char(p2_fb,p2abs_string,1);
			break;
			case 2:
				p1_fb /= 10;
				p1_fb *=0.75;
				float2char(p1_fb,p1abs_string,1);
				p2_fb /= 10;
				p2_fb *=0.75;
				float2char(p2_fb,p2abs_string,1);
			break;
			case 3:
				p1_fb /= 10;
				p1_fb *=0.02953;
				float2char(p1_fb,p1abs_string,2);
				p2_fb /= 10;
				p2_fb *=0.02953;
				float2char(p2_fb,p2abs_string,2);
			break;
			case 4:
				p1_fb /= 10;
				p1_fb *=750;
				float2char(p1_fb,p1abs_string,0);
				p2_fb /= 10;
				p2_fb *=750;
				float2char(p2_fb,p2abs_string,0);
			break;
			case 5:
				p1_fb /= 10;
				p1_fb *=0.4015;
				float2char(p1_fb,p1abs_string,1);
				p2_fb /= 10;
				p2_fb *=0.4015;
				float2char(p2_fb,p2abs_string,1);
			break;
		}
	}
}




void float1char(double fltData,unsigned char*buffer,int n)  //绝对值//浮点型数，存储的字符数组，小数点位数
{
 //double decimal=0.0;
 //long int idata=0,i=0;
 int i=0;
 i = n;
 idata = fltData;
 decimal = fltData - (double)idata;
 
 if(n > 0)
 {
  for(;i>0;i--)
     decimal *= 10;
 }
 decimal /= 0.9999;
 
    if(fltData>=0)    //判断是否大于0
    {  

    }    
    else
    {
        fltData = -fltData;
        decimal = -decimal;
    }
    idata = fltData;    //取整数部分
             
    for(i9=0;idata!=0;i9++)   //计算整数部分的位数
        idata /=10;
        
    idata = fltData;    
    if(idata == 0)
    {
     buffer[i9] = '0';
		 i9++;
    }    
    else
    {    
     for(j9=i9;j9>0;j9--)  //将整数部分转换成字符串型
     {
         buffer[j9-1] = idata%10+'0';
         idata /=10;
     }
    }
 
 if(n>0)
 {
  buffer[i9]= '.';
  idata = (long)decimal;    //取小数部分
             
   i9=i9+n+1;
         
  if((decimal-idata)>0)
	 idata = (long)(decimal+0.5);    

     for(j9=i9;j9>i9-n;j9--)  //将小数部分转换成字符串型
     {
         buffer[j9-1] = idata%10+'0';
         idata /=10;
     }
 }    

	if(i9<6)
 {
		 for(;i9<5;i9++)
     {
         buffer[i9] = ' ';
     }
		 buffer[i9] = '\0';
 }
 else
	buffer[i9+1]= '\0';
}
void float2char(double fltData,unsigned char*buffer,int n)  //浮点型数，存储的字符数组，小数点位数
{
 double add=0.0;
 //long int idata=0,i=0;
 int i=0;
	
	if(fltData>=0)
	{
		switch(n)
		{
			default: break;
			case 1:
				fltData = ((double)((int)((fltData+0.05)*10))) / 10;
			break;
			case 2:
				fltData = ((double)((int)((fltData+0.005)*100))) / 100;
			break;
			case 3:
				fltData = ((double)((int)((fltData+0.0005)*1000))) / 1000;
			break;
			case 4:
				fltData = ((double)((int)((fltData+0.00005)*10000))) / 10000;
			break;
		}
	}
	
	
