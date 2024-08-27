#ifndef _DISPLAY_H
#define _DISPLAY_H

#include "stm32f10x.h"



#if 0
#if defined(__CC_ARM)
#pragma anon_unions
#elif defined(__ICCARM__)
#endif


extern volatile unsigned short int dsp_bike_miss;
extern volatile unsigned short int dsp_pwr_miss;
extern volatile unsigned short int dsp_miss_timer;

extern volatile unsigned char dsp_main_mode;
#define DSP_SERVICE_MODE 0
#define DSP_USER_SETUP 1
#define DSP_WORK_OUT 2
#define DSP_RESULT 3
#define DSP_SYS_FAULT 4
#define	DSP_PAIRING_MODE 5
#define DSP_SLEEP 6
#define	DSP_AUTO_CALI	7
extern volatile unsigned char dsp_sub_mode;
extern volatile unsigned char dsp_sub_mode2;
extern volatile char pwr_999_flag;
extern volatile char cal_1999_flag;
extern volatile char dst_9999_flag;

typedef union tagDSP_ZONE{
	struct {
  	unsigned char ZONE1:1;
  	unsigned char ZONE2:1;
  	unsigned char ZONE3:1;
  	unsigned char ZONE4:1;
  	unsigned char ZONE5:1;
  	unsigned char ZONE6:1;
  	unsigned char ZONE7:1;
  	unsigned char ZONE8:1;
	};
	struct {
	unsigned char	ZONE;
	};
	

} DSP_ZONE;
extern volatile DSP_ZONE dsp_zone_flag;

typedef struct tagDSP_FLAG{
  unsigned char UPDATE:1;
  unsigned char FLASH:1;
  unsigned char	FLASH_ON:1;
  unsigned char PAIRING_FLAG:1;
  unsigned char LOW_BATT:1;		// low 2.2v
  
} DSP_FLAG;
extern volatile DSP_FLAG dsp_flag;

enum   SERVICE_MODE
{
	DSP_BIKE_TYPE,
	DSP_UNIT_SET,
	DSP_PAIRING_SET,
	DSP_CALI_SET,
	DSP_BATTERY_SET,
	DSP_EEPROM_SET,
	DSP_USB_SET,
	DSP_EXIT_SET
};

enum	BIKE_ITEM
{	
	DSP_BIKE_01,
	DSP_BIKE_02,
	DSP_BIKE_03,
    DSP_BIKE_04,
	DSP_BIKE_EXIT
};

enum	UNIT_ITEM
{
	DSP_UNIT_01,	
	DSP_UNIT_02,	
	DSP_UNIT_EXIT
};

enum	PAIR_ITEM
{
	DSP_PAIR_01,
	DSP_PAIR_02,
	DSP_PAIR_EXIT
};

enum	CALI_ITEM
{
	DSP_CALI_01,
	DSP_CALI_02,
	DSP_CALI_03,
	DSP_CALI_04,
	DSP_CALI_05,
	DSP_CALI_EXIT	
};

enum	BATT_ITEM
{
	DSP_BATT_01,
	DSP_BATT_02,
	DSP_BATT_03,
	DSP_BATT_EXIT
};

enum	EEPROM_ITEM
{
	DSP_EEPROM_01,
	DSP_EEPROM_02,
	DSP_EEPROM_03,
	DSP_EEPROM_04,
	DSP_EEPROM_05,
	DSP_EEPROM_06,
	DSP_EEPROM_07,
	DSP_EEPROM_EXIT
};

enum	USB_ITEM
{
	DSP_USB_01,
	DSP_USB_02,
	DSP_USB_03,
	DSP_USB_EXIT
};




//Routine
void	Dsp_FullOn();
void	Dsp_FullOff();
void	Dsp_BattLevel_Disp(unsigned char level);
void	Dsp_Lcdram_Clr_Except_Batt(void);
void	Dsp_BattIcon_Flash(void);
void	Dsp_ClrErrorIcon(void);
void Dsp_RUN_Mode(void);
#endif
#endif/*_DISPLAY_H*/

