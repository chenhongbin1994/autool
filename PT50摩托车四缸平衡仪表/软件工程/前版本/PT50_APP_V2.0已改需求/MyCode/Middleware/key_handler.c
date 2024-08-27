#include "key_handler.h"
#include "stdio.h"
#include "buzzer.h"
#include "delay.h"
#include "LCD_HT1623.h"
#include "battery.h"
#include "stmflash.h"
#include "timer.h"
#include "adc.h"
extern u8 Timing_Switch_5min, MinAuto, SecondAuto;
u8 Zero_flag, lock_flag, longocked_flag, Switch_flag, REC_flag;  // ����һЩȫ�ֱ���
extern float pressure_offset[4];// ���ڴ洢У׼��ѹ��ƫ��ֵ
// �������ýṹ����ⲿ����
extern KEY_Configure_TypeDef Key0Cfg;
extern KEY_Configure_TypeDef Key1Cfg;
extern KEY_Configure_TypeDef Key2Cfg;
extern KEY_Configure_TypeDef Key3Cfg;
extern KEY_Configure_TypeDef Key4Cfg;
extern KEY_Configure_TypeDef Key5Cfg;

Settings current_settings;  // ��ǰ����
int settings_mode = 0;  // ����ģʽ��־
static int setting_item = SETTING_UNIT;  // ��ǰ������
u8 Zero_flag = 0;  // �����־

/*--------------------------------------- Flash �洢��ض��� ----------------------------------------------------*/
#define SETTINGS_FLASH_ADDR 0X08030000  // ���ñ����ַ
#define HISTORY_INDEX_ADDR 0x08030000+(sizeof(Settings))  // �洢��ʷ��¼�����ĵ�ַ
#define BUFFER_SIZE 2048  // �������Ĵ�С
#define HISTORY_FLASH_ADDR 0x08030800  // ����������ʼ��ַ

// �����ñ��浽 Flash
void SaveSettingsToFlash(const Settings *settings) {
    STMFLASH_Write(SETTINGS_FLASH_ADDR, (uint16_t*)settings, sizeof(Settings) / 2);
}

// �� Flash �ж�ȡ����
void LoadSettingsFromFlash(Settings *settings) {
    STMFLASH_Read(SETTINGS_FLASH_ADDR, (uint16_t*)settings, sizeof(Settings) / 2);
}

// ���浱ǰ���õ�����ʧ�Դ洢��
void SaveCurrentSettings() {
    SaveSettingsToFlash(&current_settings);
}

// �������ú���
void SaveSettings() {
    printf("��������: ��ǰ��λ: %d, ��ǰ����������: %d,��ǰ���: %d\n", current_settings.current_unit, current_settings.sensor_count,current_settings.stroke2T4T_mode);
    SaveCurrentSettings();
    setting_item = (setting_item + 1) % SETTING_MAX;  // ��ת����һ��������
    
    SwitchingNumberCylinders();
    
    // ��ӡ��ͬ���������Ϣ
    switch (setting_item) {
        case SETTING_UNIT:
            printf("�л������õ�λ\n");
            break;
        case SETTING_SENSOR_COUNT:
            printf("�л������ô���������\n");
            break;
        case SETTING_STROKE2T4T_MODE:
            printf("�л������ó��ģʽ\n");
            Switching2T4T_display();
            break;
        case SETTING_AUTO_SHUTDOWN:  // �����Զ��ػ�������
            AUutoshutdownONOFF_display();
            printf("�л��������Զ��ػ�\n");
            printf("%d\n",current_settings.auto_shutdown_enabled);
            break;
    }
    if (setting_item == 0) {
        // ��������������꣬�˳�����ģʽ
        settings_mode = 0;
        printf("��������������꣬�˳�����ģʽ\n");
    }
}
/*-------------------------------------- Flash �洢��ʷ���� --------------------------------------*/
#define MAX_HISTORY_RECORDS 20  // ��ʷ��¼�������
extern float pressure[4];
extern u8 Second, Minute, Hour;
static u8 rec_data = 0;

typedef struct {
    float pressure[4];
    u16 ADC_Value[4];
    u8 Second, Minute, Hour;
    u8 sensor_mode;  // �����ֶΣ�0 ��ʾ ch1��1 ��ʾ ch2
} Record;

int history_index = 0;  // ��ǰ��¼������
int total_records = 0;  // �ܼ�¼��
int current_history_display = -1;  // ��ǰ��ʾ����ʷ��¼������-1 ��ʾ���ڲ鿴��ʷ��¼״̬
int in_submode = 0; // ����Ƿ�����ģʽ
int submode_index = 0; // ��ǰ��ģʽ���� 0:���ֵ, 1:��Сֵ, 2:��ֵ

// ������ʷ��¼�� Flash
void SaveHistoryRecordToFlash(int index, const Record *record) {
    int adjusted_index = (index % MAX_HISTORY_RECORDS) + 1;  // ʹ��ѭ���������� 1 ��ʼ
    uint32_t write_addr = HISTORY_FLASH_ADDR + (adjusted_index - 1) * sizeof(Record); // ���������������1��ʼ
    STMFLASH_Write(write_addr, (uint16_t*)record, sizeof(Record) / 2);
}

// ����ǰ��ʷ��¼�������浽 Flash
void SaveCurrentHistoryIndexToFlash() {
    STMFLASH_Write(HISTORY_INDEX_ADDR, (uint16_t*)&history_index, sizeof(int) / 2);
    STMFLASH_Write(HISTORY_INDEX_ADDR + sizeof(int), (uint16_t*)&total_records, sizeof(int) / 2);
}

// �� Flash �ж�ȡ��ʷ��¼
void LoadHistoryRecordFromFlash(int index, Record *record) {
    int adjusted_index = index % MAX_HISTORY_RECORDS;  // ʹ��ѭ������
    uint32_t read_addr = HISTORY_FLASH_ADDR + adjusted_index * sizeof(Record);
    STMFLASH_Read(read_addr, (uint16_t*)record, sizeof(Record) / 2);
}

// �� Flash �м�����ʷ��¼����
void LoadHistoryIndexFromFlash() {
    STMFLASH_Read(HISTORY_INDEX_ADDR, (uint16_t*)&history_index, sizeof(int) / 2);   
    STMFLASH_Read(HISTORY_INDEX_ADDR + sizeof(int), (uint16_t*)&total_records, sizeof(int) / 2);
}
extern u8 decimal_points;
// ��ʾ��ʷ��¼�ĺ���
Record record;
void History_Time(void);
void DisplayHistoryRecord(int index) {
    if (index >= 0 && index < total_records) {
        // Record record;
        LoadHistoryRecordFromFlash(index, &record);  // index+1����������ƥ��� 1 ��ʼ�ļ�¼
        printf("��ʾ��ʷ��¼����: %d\n", index + 1);
   
        float convertedPressure[4];
        //SwitcUint(record.pressure);
        switch (current_settings.current_unit) {
            case 0: // kPa   ��Ҫ2λС����
            UpdateReadModifyWriteDisplay(22, Switching_Unit_Data_K+Switching_Unit_Data_pa, 1);
            for (int i = 0; i < 4; i++) {
                convertedPressure[i] = record.pressure[i] * 10;//0.1*100
                printf("Pressure %d: AD_Value= %d, ѹ��= %.2f HPa\r\n", i, ADC_Value[i], convertedPressure[i]);
                //convertedPressure[i] = convertedPressure[i]*100;               
            }
            decimal_points = 2;
            break;

        case 1: // mmHg   1С����
            UpdateReadModifyWriteDisplay(22, Switching_Unit_Data_mmHg, 1);
            for (int i = 0; i < 4; i++) {
                convertedPressure[i] = record.pressure[i] * 7.50062;//0.750062
                printf("Pressure %d: AD_Value= %d, ѹ��= %.2f HPa\r\n", i, ADC_Value[i], convertedPressure[i]);
            }
            decimal_points = 1; 
            break;

        case 2: // Torr    1С����   �����λ�����ûҪ��
            UpdateReadModifyWriteDisplay(22, Switching_Unit_Data_Torr, 1);
            for (int i = 0; i < 4; i++) {
                convertedPressure[i] = record.pressure[i] * 7.50062;
                printf("Pressure %d: AD_Value= %d, ѹ��= %.2f HPa\r\n", i, ADC_Value[i], convertedPressure[i]);

            }
            decimal_points = 1; 
            break; 

        case 3: // mbar    1С����
            UpdateReadModifyWriteDisplay(22, Switching_Unit_Data_m + Switching_Unit_Data_bar, 1);
            for (int i = 0; i < 4; i++) {
                convertedPressure[i] = record.pressure[i] * 10;
                printf("Pressure %d: AD_Value= %d, ѹ��= %.2f HPa\r\n", i, ADC_Value[i], convertedPressure[i]);
                
            }
            decimal_points = 1; 
            break;

        case 4: // inHg    2С����
            UpdateReadModifyWriteDisplay(23, Switching_Unit_Data_inHg, 1);
            for (int i = 0; i < 4; i++) {
                convertedPressure[i] = record.pressure[i] * 2.95301;//0.0295301*100
                printf("Pressure %d: AD_Value= %d, ѹ��= %.2f HPa\r\n", i, ADC_Value[i], convertedPressure[i]);               
            }
            decimal_points = 2; 
            break;

        case 5: // inH2O    1С����   �����λ�����ûҪ��
            UpdateReadModifyWriteDisplay(23, Switching_Unit_Data_inH2O, 1);
            for (int i = 0; i < 4; i++) {
                convertedPressure[i] = record.pressure[i] * 4.01463;//0.401463
                printf("Pressure %d: AD_Value= %d, ѹ��= %.2f HPa\r\n", i, ADC_Value[i], convertedPressure[i]);

            }
            decimal_points = 1; 
            break;

        case 6: // mmH2O    ��С����   �����λ�����ûҪ��
            UpdateReadModifyWriteDisplay(23, Switching_Unit_Data_mmH2O, 1);
            for (int i = 0; i < 4; i++) {
                convertedPressure[i] = record.pressure[i] * 10.1972;
                printf("Pressure %d: AD_Value= %d, ѹ��= %.2f HPa\r\n", i, ADC_Value[i], convertedPressure[i]);

            }
            decimal_points = 0; 
            break;

        case 7: // psi  ��Ҫ2��С����
            UpdateReadModifyWriteDisplay(23, Switching_Unit_Data_psi, 1);
            for (int i = 0; i < 4; i++) {
                convertedPressure[i] = record.pressure[i] * 1.45038;//0.0145038*100                
                printf("Pressure %d: AD_Value= %d, ѹ��= %.2f HPa\r\n", i, ADC_Value[i], convertedPressure[i]);

                
            }
            decimal_points = 2; 
            break;

        case 8: // hPa  1С����
            UpdateReadModifyWriteDisplay(23, Switching_Unit_Data_hpa, 1);
            for (int i = 0; i < 4; i++) {
                convertedPressure[i] = record.pressure[i]*10;
                printf("Pressure %d: AD_Value= %d, ѹ��= %.2f HPa\r\n", i, ADC_Value[i], convertedPressure[i]);               
            }
            decimal_points = 1; 
            break;
        }

       if (record.sensor_mode == MODE_CH1) { // 1��ʾch1ģʽ
            ClearDigitalTubeDisplay();//ˢ���ĸ�
            ClearMercuryDisplay();
            for(int i=5;i<11;i++)UpdateReadModifyWriteDisplay(i,0xf0,0);
            for(int i=16;i<22;i++)UpdateReadModifyWriteDisplay(i,0xf0,0);
            Digital_tube_display(1 + 5 * 0, 2 + 5 * 0, 3 + 5 * 0, 4 + 5 * 0, 5 + 5 * 0, convertedPressure[3], record.ADC_Value[3]);
            History_Time();
            NumHistoricalData_Display(26, 27, 28, 29, 30, index + 1); // ��ʾ��ʷ���ݱ��
            printf("Pressure %d: AD_Value= %d, ѹ��= %.2f HPa\r\n", 0, record.ADC_Value[3], record.pressure[3]);//1�Ÿ�
             
        }
        else if(record.sensor_mode == MODE_CH2){
            ClearDigitalTubeDisplay();//ˢ���ĸ�
            ClearMercuryDisplay();          
            for(int i=5;i<11;i++)UpdateReadModifyWriteDisplay(i,0xf0,0);
            for(int i=16;i<22;i++)UpdateReadModifyWriteDisplay(i,0xf0,0);
            Digital_tube_display(1 + 5 * 0, 2 + 5 * 0, 3 + 5 * 0, 4 + 5 * 0, 5 + 5 * 0, convertedPressure[3], record.ADC_Value[3]);//1�Ÿ�
            Digital_tube_display(1 + 5 * 1, 2 + 5 * 1, 3 + 5 * 1, 4 + 5 * 1, 5 + 5 * 1, convertedPressure[2], record.ADC_Value[2]);//2�Ÿ�
            History_Time();
            NumHistoricalData_Display(26, 27, 28, 29, 30, index + 1); // ��ʾ��ʷ���ݱ��
            printf("Pressure %d: AD_Value= %d, ѹ��= %.2f HPa\r\n", 0, record.ADC_Value[3], record.pressure[3]);
            printf("Pressure %d: AD_Value= %d, ѹ��= %.2f HPa\r\n", 1, record.ADC_Value[2], record.pressure[2]);     
        }
        else if(record.sensor_mode == MODE_CH3){
            ClearDigitalTubeDisplay();//ˢ���ĸ�
            ClearMercuryDisplay();          
            for(int i=5;i<11;i++)UpdateReadModifyWriteDisplay(i,0xf0,0);
            for(int i=16;i<22;i++)UpdateReadModifyWriteDisplay(i,0xf0,0);
            Digital_tube_display(1 + 5 * 0, 2 + 5 * 0, 3 + 5 * 0, 4 + 5 * 0, 5 + 5 * 0, convertedPressure[3], record.ADC_Value[3]);//1�Ÿ�
            Digital_tube_display(1 + 5 * 1, 2 + 5 * 1, 3 + 5 * 1, 4 + 5 * 1, 5 + 5 * 1, convertedPressure[2], record.ADC_Value[2]);//2�Ÿ�
            Digital_tube_display(1 + 5 * 2, 2 + 5 * 2, 3 + 5 * 2, 4 + 5 * 2, 5 + 5 * 2, convertedPressure[1], record.ADC_Value[1]);//3�Ÿ�
            History_Time();
            NumHistoricalData_Display(26, 27, 28, 29, 30, index + 1); // ��ʾ��ʷ���ݱ��
            printf("Pressure %d: AD_Value= %d, ѹ��= %.2f HPa\r\n", 0, record.ADC_Value[3], record.pressure[3]);
            printf("Pressure %d: AD_Value= %d, ѹ��= %.2f HPa\r\n", 1, record.ADC_Value[2], record.pressure[2]);
            printf("Pressure %d: AD_Value= %d, ѹ��= %.2f HPa\r\n", 2, record.ADC_Value[1], record.pressure[1]);    
        }
        else if(record.sensor_mode == MODE_CH4){
            ClearDigitalTubeDisplay();//ˢ���ĸ�
            ClearMercuryDisplay();          
            for(int i=5;i<11;i++)UpdateReadModifyWriteDisplay(i,0xf0,0);
            for(int i=16;i<22;i++)UpdateReadModifyWriteDisplay(i,0xf0,0);
            Digital_tube_display(1 + 5 * 0, 2 + 5 * 0, 3 + 5 * 0, 4 + 5 * 0, 5 + 5 * 0, convertedPressure[3], record.ADC_Value[3]);//1�Ÿ�
            Digital_tube_display(1 + 5 * 1, 2 + 5 * 1, 3 + 5 * 1, 4 + 5 * 1, 5 + 5 * 1, convertedPressure[2], record.ADC_Value[2]);//2�Ÿ�
            Digital_tube_display(1 + 5 * 2, 2 + 5 * 2, 3 + 5 * 2, 4 + 5 * 2, 5 + 5 * 2, convertedPressure[1], record.ADC_Value[1]);//3�Ÿ�
            Digital_tube_display(1 + 5 * 3, 2 + 5 * 3, 3 + 5 * 3, 4 + 5 * 3, 5 + 5 * 3, convertedPressure[0], record.ADC_Value[0]);//4�Ÿ� 
            History_Time();
            NumHistoricalData_Display(26, 27, 28, 29, 30, index + 1); // ��ʾ��ʷ���ݱ��
            printf("Pressure %d: AD_Value= %d, ѹ��= %.2f HPa\r\n", 0, record.ADC_Value[3], record.pressure[3]);
            printf("Pressure %d: AD_Value= %d, ѹ��= %.2f HPa\r\n", 1, record.ADC_Value[2], record.pressure[2]);
            printf("Pressure %d: AD_Value= %d, ѹ��= %.2f HPa\r\n", 2, record.ADC_Value[1], record.pressure[1]);
            printf("Pressure %d: AD_Value= %d, ѹ��= %.2f HPa\r\n", 3, record.ADC_Value[0], record.pressure[0]);     
        }
    } else {
        printf("��Ч����ʷ��¼����: %d\n", index + 1);
        NumHistoricalData_Display(26, 27, 28, 29, 30, 0); // ��ʾ��ʷ���ݱ��
        SwitchingNumberCylinders();
    }   
}
void History_Time(void) {
    
    UpdateReadModifyWriteDisplay(11, Screen_Data_Time, 1); // TIMEͼ����ʾ
    TIME_Digital_tube_Bit_Display(record.Hour / 10, 1);
    TIME_Digital_tube_Bit_Display(record.Hour % 10, 2);
    UpdateReadModifyWriteDisplay(10, Group2_digitron_TIME_colon_S32, 1); // ð��1��ʾ
    TIME_Digital_tube_Bit_Display(record.Minute / 10, 3);
    TIME_Digital_tube_Bit_Display(record.Minute % 10, 4);
    UpdateReadModifyWriteDisplay(22, Group2_digitron_TIME_colon_S38, 1); // ð��2��ʾ
    TIME_Digital_tube_Bit_Display(record.Second / 10, 5);
    TIME_Digital_tube_Bit_Display(record.Second % 10, 6);
}

#define LARGE_NUMBER -1e30 // ���ڸ��������LARGE_NUMBER��ʼΪһ���ǳ�С�ĸ���
#define SMALL_NUMBER  1e30  // ��ʼΪһ���ǳ��������

void DisplaySubmodeData(int index) {
    REC_flag = 0;

    if (index >= 0 && index < total_records) {
        Record record;
        LoadHistoryRecordFromFlash(index, &record);

        float maxPressure = SMALL_NUMBER;  // ���ֵ��ʼΪһ���ǳ�С�ĸ���
        float minPressure = LARGE_NUMBER;  // ��Сֵ��ʼΪһ���ǳ��������
        float diffPressure = 0;

        if (record.sensor_mode == MODE_CH1) { 
            //current_settings.sensor_count = 1;
            //for (int i = 2; i < 4; i++) {
                if (record.pressure[3] < maxPressure) { // ���ڸ���������ֵԽС����ֵԽ�󣩱�ʾ���ֵ
                    maxPressure = record.pressure[3];
                }
                if (record.pressure[3] > minPressure) { // ���ڸ���������ֵԽ����ֵԽС����ʾ��Сֵ
                    minPressure = record.pressure[3];
                }
           // }
        } 
        else if(record.sensor_mode == MODE_CH2){ 
            for (int i = 2; i < 4; i++) {
                if (record.pressure[i] < maxPressure) { // ���ڸ���������ֵԽС����ֵԽ�󣩱�ʾ���ֵ
                    maxPressure = record.pressure[i];
                }
                if (record.pressure[i] > minPressure) { // ���ڸ���������ֵԽ����ֵԽС����ʾ��Сֵ
                    minPressure = record.pressure[i];
                }
            }
        }
        else if(record.sensor_mode == MODE_CH3){
            for (int i = 1; i < 4; i++) {
                if (record.pressure[i] < maxPressure) { // ���ڸ���������ֵԽС����ֵԽ�󣩱�ʾ���ֵ
                    maxPressure = record.pressure[i];
                }
                if (record.pressure[i] > minPressure) { // ���ڸ���������ֵԽ����ֵԽС����ʾ��Сֵ
                    minPressure = record.pressure[i];
                }
            }
        }
        else if(record.sensor_mode == MODE_CH4){
            for (int i = 0; i < 4; i++) {
                if (record.pressure[i] < maxPressure) { // ���ڸ���������ֵԽС����ֵԽ�󣩱�ʾ���ֵ
                    maxPressure = record.pressure[i];
                }
                if (record.pressure[i] > minPressure) { // ���ڸ���������ֵԽ����ֵԽС����ʾ��Сֵ
                    minPressure = record.pressure[i];
                }
            }
        }
        // if (display_num < 0) {
        // display_num = -display_num; // ת��Ϊ����
        // }
        diffPressure = maxPressure - minPressure; // �����ֵ
        float display_value = 0;
        switch (submode_index) {
            case 0:
                display_value = maxPressure;
                UpdateReadModifyWriteDisplay(11, Screen_Data_MAX, 1); // MAXͼ����ʾ				
                SettingsUint(display_value);
                printf("��ʾ���ֵ: %.2f\n", display_value);
                break;
            case 1:
                display_value = minPressure;
                UpdateReadModifyWriteDisplay(11, Screen_Data_MIN, 1); // MINͼ����ʾ
                SettingsUint(display_value);
                printf("��ʾ��Сֵ: %.2f\n", display_value);
                break;
            case 2:
                display_value = diffPressure;
                UpdateReadModifyWriteDisplay(11, Screen_Data_DifferValue, 1); // ��ֵͼ����ʾ
                SettingsUint(display_value);
                printf("��ʾ��ֵ: %.2f\n", display_value);
                break;
        }
    } else {
        printf("��Ч����ʷ��¼����: %d\n", index + 1);
    }
}


// ��ʼ������
void InitializeSettings() {
    LoadSettingsFromFlash(&current_settings);
    LoadHistoryIndexFromFlash();  // ������ʷ����
    // �����ȡ����Ч�����ã���������Ĭ��ֵ
    if (current_settings.buzzer_enabled != 0 && current_settings.buzzer_enabled != 1) {
        current_settings.buzzer_enabled = 1;  // Ĭ��ֵ
    }
    if (current_settings.current_unit >= 9) {
        current_settings.current_unit = 0;  // Ĭ��ֵKPa��λ
    }
    if (current_settings.sensor_count >= 4) {
        current_settings.sensor_count = MODE_CH4;  // �����ȡ����Чֵ����ָ���Ĭ�ϵ�ch4
    }
    if (current_settings.stroke2T4T_mode != 0 && current_settings.stroke2T4T_mode != 1) {
        current_settings.stroke2T4T_mode = 0;  // Ĭ��ֵ 4T
    }
    if (current_settings.auto_shutdown_enabled != 0 && current_settings.auto_shutdown_enabled != 1) {
        current_settings.auto_shutdown_enabled = 0;  // Ĭ��ֵ ON  �����Զ��ػ�
    }
}
#if 1
    int power_on = 0;
    static int backlight_on = 0;
// ������0�¼�
void Handle_Key0_Event(KEY_EventList_TypeDef event) {    
    MinAuto = 0; SecondAuto = 0; Timing_Switch_5min = 0;
  
    switch (event) {
       
        case KEY_Event_SingleClick:
        if(lock_flag == 0){ 
            if (current_settings.buzzer_enabled) {
                Key_Beep();  // ������������100ms
            }
            backlight_on = !backlight_on;
            if (!backlight_on){
                GPIO_SetBits(GPIOB, GPIO_Pin_3);  // ���⿪
                UpdateReadModifyWriteDisplay(15, Screen_Data_LED, 1);
            } else {
                GPIO_ResetBits(GPIOB, GPIO_Pin_3);  // �����
                UpdateReadModifyWriteDisplay(15, Screen_Data_LED, 0);
            }
        }        
            break;
    
        case KEY_Event_LongPress: 
         if (current_settings.buzzer_enabled) {
                Key_Beep();  // ������������100ms
            }           
            power_on = !power_on;
            if (power_on) {
                GPIO_SetBits(GPIOA, GPIO_Pin_4);  // ��Դ��
                GPIO_SetBits(GPIOB, GPIO_Pin_3);  // ���⿪
                UpdateReadModifyWriteDisplay(15, Screen_Data_LED, 1);
            } else {
                cleandisp();//������һЩ���ܿ��ܲ�������������Ŀǰ�ǵ�����
                GPIO_ResetBits(GPIOB, GPIO_Pin_3);  // �����				              
                GPIO_ResetBits(GPIOA, GPIO_Pin_4);  // �ػ���Դ
							
            }
            break;
        default:
            break;
        }
    

}
#endif


// ������1�¼�   
void Handle_Key1_Event(KEY_EventList_TypeDef event) {
    if(lock_flag == 0){
    MinAuto = 0; SecondAuto = 0; Timing_Switch_5min = 0; // �Զ��ػ����¼�ʱ
    if (current_settings.buzzer_enabled) {
        Key_Beep();  // ������������100ms
    }
    printf("����1�¼�: %d, settings_mode: %d, setting_item: %d\n", event, settings_mode, setting_item);
    switch (event) {
        case KEY_Event_SingleClick:				
        UpdateReadModifyWriteDisplay(11, Screen_Data_MAX + Screen_Data_MIN + Screen_Data_DifferValue, 0); // ˢ��
            if (settings_mode) {
                // ����ģʽ�°���1�������Ϸ���
                if (setting_item == SETTING_UNIT) {
                    current_settings.current_unit = (current_settings.current_unit - 1 + 9) % 9;
                    SettingsUint_display();
                    printf("��ǰ��λ: %d\r\n", current_settings.current_unit);
                } else if (setting_item == SETTING_SENSOR_COUNT) {
                    // current_settings.sensor_count = (current_settings.sensor_count - 1 + 2) % 2;
                    current_settings.sensor_count = (current_settings.sensor_count - 1 + 4) % 4;  // ֧��ch1��ch2��ch3��ch4ģʽѭ���л�
                    SwitchingNumberCylinders();					                    
                    printf("��ǰ����������: %d\r\n", current_settings.sensor_count);
                }else if (setting_item == SETTING_STROKE2T4T_MODE) {
                    current_settings.stroke2T4T_mode = (current_settings.stroke2T4T_mode - 1 + 2) % 2;
                    Switching2T4T_display();
                    printf("��ǰ���ģʽ: %s\r\n", current_settings.stroke2T4T_mode ? "4���" : "2���");        
                }else if (setting_item == SETTING_AUTO_SHUTDOWN) {  // �����Զ��ػ�������
                    current_settings.auto_shutdown_enabled = (current_settings.auto_shutdown_enabled - 1 + 2) % 2;
                    AUutoshutdownONOFF_display();
                    printf("�Զ��ػ�����: %s\r\n", current_settings.auto_shutdown_enabled ? "����" : "�ر�");
                    printf("�Զ��ػ����ܵ�ǰѡ��Ϊ: %d\n",current_settings.auto_shutdown_enabled);
                }
            } else if (current_history_display != -1) {
                if (total_records > 0) {  //������ʷ��¼�������
                // ClearDigitalTubeDisplay();//ˢ���ĸ�
                // ClearMercuryDisplay();
                Clear_Group1dig();
                submode_index = 0;  // ȷ�������ֵ��ʼ��ʾ
                in_submode = 0;
                // �鿴��ʷ��¼ģʽ
                if (current_history_display > 0) {
                    current_history_display--;
                } else {
                    current_history_display = total_records - 1;
                }
                DisplayHistoryRecord(current_history_display);
                } else {
                //���Լ�����룺�޼�¼���¿��Լ���ʵ�ַ���������������
                //  û����ʷ��¼ʱ�Ĵ���
                printf("û����ʷ��¼���޷��Ϸ�\n");
                }

            }else{
                current_settings.buzzer_enabled = !current_settings.buzzer_enabled;  // �л�������״̬
                //printf("������%s\r\n", current_settings.buzzer_enabled ? "��" : "�ر�");
                if (current_settings.buzzer_enabled) {
                UpdateReadModifyWriteDisplay(15, Screen_Data_BUZZER, 1);
                } else {
                UpdateReadModifyWriteDisplay(15, Screen_Data_BUZZER, 0);
                }
                SaveCurrentSettings();  // ��������
            }
            break;
        //������������
        //case KEY_Event_LongPress:
        //    break;
        default:
            break;
        }
    }
}

// ������2�¼�
void Handle_Key2_Event(KEY_EventList_TypeDef event) {
    if(lock_flag == 0){
    if(settings_mode == 0){
    MinAuto = 0; SecondAuto = 0; Timing_Switch_5min = 0; // �Զ��ػ��ر������¼�ʱ
    static int rec_mode = 0;
    if (current_settings.buzzer_enabled) {
        Key_Beep();  // ������������100ms
    }
    UpdateReadModifyWriteDisplay(11, Screen_Data_MAX + Screen_Data_MIN + Screen_Data_DifferValue, 0); // ˢ��
    switch (event) {
        case KEY_Event_SingleClick:
        
            if (in_submode)Clear_Clock_Display();//ˢ��ʱ�������

            if (current_history_display != -1) {
                if (in_submode) {
                    submode_index = (submode_index + 1) % 3;  // �л���ģʽ��ʾ����
                    DisplaySubmodeData(current_history_display);
                } else {
                    // �л�������ģʽ
                    Clear_Clock_Display();//ˢ��ԭʱ�������
                    submode_index = 0;
                    in_submode = 1;
                    DisplaySubmodeData(current_history_display);
                }
            } else {
                if (rec_data == 0) {
                    if (!rec_mode) {
                        rec_mode = 1;
                        UpdateReadModifyWriteDisplay(14, Screen_Data_REC, 1);                                               
                    } else {
                        //printf("��������\r\n");
                        Clear_Group1dig();
                        Record new_record;
                        for (int i = 0; i < 4; i++) {
                            new_record.pressure[i] = pressure[i];
                            new_record.ADC_Value[i] = ADC_Value[i];
                        }
                        new_record.Second = Second;
                        new_record.Minute = Minute;
                        new_record.Hour = Hour;
                        new_record.sensor_mode = current_settings.sensor_count; // ���浱ǰ����������
                        SaveHistoryRecordToFlash(history_index, &new_record);  // ʹ�ô� 0 ��ʼ������
                        history_index = (history_index % MAX_HISTORY_RECORDS) + 1;  // ����������1��ʼ��ʹ��ѭ������
                        
                        if (total_records < MAX_HISTORY_RECORDS) {
                            total_records++;
                        }
                        printf("�������ݵ���¼����: %d\n", history_index % MAX_HISTORY_RECORDS);
                        NumHistoricalData_Display(26, 27, 28, 29, 30, history_index);    // �������ݵ���¼����
                        SaveCurrentHistoryIndexToFlash();  // ���浱ǰ��ʷ��¼����
                        printf("�������ݵ���¼����: %d\n", history_index);
                      
                    }
                }
            
            break;
        case KEY_Event_LongPress:
            UpdateReadModifyWriteDisplay(11, Screen_Data_MAX + Screen_Data_MIN + Screen_Data_DifferValue, 0); // ˢ��
            rec_mode = 0;
            rec_data = 1;
            if (current_history_display == -1) {
                ClearDigitalTubeDisplay();//ˢ���ĸ�
                ClearMercuryDisplay();//ˢ���ĸ�
                Clear_Clock_Display();//ˢ��ʱ��
                Clear_Group1dig();
                // UpdateReadModifyWriteDisplay(15, Screen_Data_2T, 0);   
                // UpdateReadModifyWriteDisplay(10, Screen_Data_4T, 0);   
                current_history_display = total_records == 1;  // �����µļ�¼��ʼ�鿴
                UpdateReadModifyWriteDisplay(14, Screen_Data_REC + Screen_Data_R1, 1);
                UpdateReadModifyWriteDisplay(11,Screen_Data_rec , 1);
                printf("�鿴��ʷ����\n");
                DisplayHistoryRecord(current_history_display);
            } else {
                // �˳���ʷ��¼�鿴ģʽ
                current_history_display = -1;
                in_submode = 0;
                printf("�˳��鿴��ʷ����ģʽ\n");
                ClearDigitalTubeDisplay();//ˢ���ĸ�
                ClearMercuryDisplay();//ˢ���ĸ�
                Clear_Group1dig();
                UpdateReadModifyWriteDisplay(14, Screen_Data_REC + Screen_Data_R1, 0);
                UpdateReadModifyWriteDisplay(11,Screen_Data_rec , 0);
                rec_data = 0;
            }
        
            break;
        default:
            break;
        }
    }
    }
    }
}

// ������3�¼� (����)
void Handle_Key3_Event(KEY_EventList_TypeDef event) {
    MinAuto = 0; SecondAuto = 0; Timing_Switch_5min = 0; // �Զ��ػ��ر������¼�ʱ
    static int data_locked = 0;
    if (current_settings.buzzer_enabled) {
        Key_Beep();  // ������������100ms
    }
    switch (event) {
        case KEY_Event_SingleClick:
             if (settings_mode) {
                SaveSettings();  // �������ò���ת����һ��������
                //printf("�������ò���ת����һ��������\n");

             } else {
            data_locked = !data_locked;
            printf("����%s\r\n", data_locked ? "����" : "����");
            if (data_locked) {
                UpdateReadModifyWriteDisplay(15, Screen_Data_lock, 1);
                lock_flag = 1;
            } else {
                UpdateReadModifyWriteDisplay(15, Screen_Data_lock, 0);
                lock_flag = 0;
                }
            }
            break;
        //��������
        //case KEY_Event_LongPress:
        //    break;
        default:
            break;
    }
}

// ������4�¼�
void Handle_Key4_Event(KEY_EventList_TypeDef event) {
    if(lock_flag == 0){
    MinAuto = 0; SecondAuto = 0; Timing_Switch_5min = 0; // �Զ��ػ��ر������¼�ʱ
    if (current_settings.buzzer_enabled) {
        Key_Beep();  // ������������100ms
    }
    switch (event) {
        case KEY_Event_SingleClick:
            UpdateReadModifyWriteDisplay(11, Screen_Data_MAX + Screen_Data_MIN + Screen_Data_DifferValue, 0); // ˢ��
            if (settings_mode) {
                // ����ģʽ�°���4�������·���
                if (setting_item == SETTING_UNIT) {
                    current_settings.current_unit = (current_settings.current_unit + 1 + 9) % 9;
                    SettingsUint_display();
                    //printf("��ǰ��λ: %d\r\n", current_settings.current_unit);
                } else if (setting_item == SETTING_SENSOR_COUNT) {
                    current_settings.sensor_count = (current_settings.sensor_count + 1) % 4;  // ֧��ch1��ch2��ch3��ch4ģʽѭ���л�
                    SwitchingNumberCylinders();
                    //printf("��ǰ����������: %d\r\n", current_settings.sensor_count == 0 ? 2 : 4);
                }else if (setting_item == SETTING_STROKE2T4T_MODE) {
                    current_settings.stroke2T4T_mode = (current_settings.stroke2T4T_mode + 1) % 2;
                    Switching2T4T_display();
                    printf("��ǰ���ģʽ: %s\r\n", current_settings.stroke2T4T_mode ? "4���" : "2���");        
                }else if (setting_item == SETTING_AUTO_SHUTDOWN) {  // �����Զ��ػ�������Ĵ���
                    current_settings.auto_shutdown_enabled = (current_settings.auto_shutdown_enabled + 1) % 2;
                    AUutoshutdownONOFF_display();
                    printf("�Զ��ػ�����: %s\r\n", current_settings.auto_shutdown_enabled ? "����" : "�ر�");
                    printf("�Զ��ػ����ܵ�ǰѡ��Ϊ: %d\n",current_settings.auto_shutdown_enabled);
                }
            } else if (current_history_display != -1) {
                if (total_records > 0) {  //������ʷ��¼�������
                // ClearDigitalTubeDisplay();//ˢ���ĸ�
                // ClearMercuryDisplay();
                Clear_Group1dig();
                submode_index = 0;  // ȷ�������ֵ��ʼ��ʾ
                in_submode = 0;
                // �鿴��ʷ��¼ģʽ
                current_history_display = (current_history_display + 1) % total_records;
                DisplayHistoryRecord(current_history_display);  
                } else {
                //���Լ�����룺�޼�¼���¿��Լ���ʵ�ַ���������������
                //  û����ʷ��¼ʱ�Ĵ���
                printf("û����ʷ��¼���޷��Ϸ�\n");
                } 
            }
            break;
        case KEY_Event_LongPress:
        if (current_history_display == -1) {
            settings_mode = 1;  // ��������ģʽ
            UpdateReadModifyWriteDisplay(15, Screen_Data_2T, 0);             
            UpdateReadModifyWriteDisplay(10, Screen_Data_4T, 0);
            UpdateReadModifyWriteDisplay(11, Screen_Data_Auto+Screen_Data_on+Screen_Data_off, 0);   
            Clear_Clock_Display();
            ClearMercuryDisplay();  // ���ѹ����ʾ����κ͹���ˢ��
            //printf("��������ģʽ\r\n");
        }
            break;
        default:
            break;
        }
    }
}
float ADValue_offset[4] = {0, 0, 0, 0};//��Ҫ����flash
int initial_value = 0;  //��Ҫ����flash
int Calibration_offset = 0;//��Ҫ����flash
int ProgressBar = 0;//��ʾp=0��������Ҫ��
// ������5�¼�
void Handle_Key5_Event(KEY_EventList_TypeDef event) {
    if(lock_flag == 0){
	if(settings_mode == 0){
    MinAuto = 0; SecondAuto = 0; Timing_Switch_5min = 0; // �Զ��ػ��ر������¼�ʱ
    // if (current_settings.buzzer_enabled) {
    //     Key_Beep();  // ������������100ms
    // }
    switch (event) {
        case KEY_Event_SingleClick:
        Key_Beep();  // ������������100ms
            UpdateReadModifyWriteDisplay(15, Screen_Data_Zero, 1);
            delay_ms(50);
            Zero_flag = 1;
            delay_ms(300);
            UpdateReadModifyWriteDisplay(15, Screen_Data_Zero, 0);
            delay_ms(50);
            break;
        case KEY_Event_LongPress:
        if (current_history_display != -1) {
            for(int i = 0 ; i < 10; i++){
                ProgressBar++;
				Calibration();  // У׼p=0��������ʾ
                if(ProgressBar == 10)ProgressBar = 0;
            }

                history_index = 0;total_records = 0;         // �����ʷ��¼����Ҫ���Լ���ʱ���ѹ��ֵ
                SaveCurrentHistoryIndexToFlash();
                Clear_Group1dig();
                NumHistoricalData_Display(26, 27, 28, 29, 30, history_index);    // �������ݵ���¼����
                Key_Beep();  // ������������100ms
                SwitchingNumberCylinders();


        }else{             
            uint16_t adc_sum[4] = {0, 0, 0, 0};
            for (int i = 0; i < 10; i++) {
                ADC_GetAverageValues();
                for (int j = 0; j < 4; j++) {
                    adc_sum[j] += ADC_Value[j];
                }
                ProgressBar++;
                Calibration();  // У׼p=0��������ʾ  
            }
            for (int i = 0; i < 4; i++) {
                ADValue_offset[i] = adc_sum[i] / 10.0;
            }
				initial_value =1784;
                Key_Beep();  // ������������100ms
                printf("У׼���: ADCƫ���� = %f, %f, %f, %f;initial_value = %d\n", ADValue_offset[0], ADValue_offset[1], ADValue_offset[2], ADValue_offset[3],initial_value);	
                Calibration_offset = 1;
                ProgressBar = 0;
        }
#if 0 //����У׼��0���ٴΰ��½��У׼��0
            Calibration_offset = !Calibration_offset;
            Calibration();  // У׼p=0��������ʾ
            if (Calibration_offset) {
                //printf("��ʼУ׼\n");

                uint16_t adc_sum[4] = {0, 0, 0, 0};
                for (int i = 0; i < 10; i++) {
                ADC_GetAverageValues();
                for (int j = 0; j < 4; j++) {
                    adc_sum[j] += ADC_Value[j];
                }
                delay_ms(100); // ÿ�ζ�ȡ���200ms���ܹ���ȡ2��
            }
            for (int i = 0; i < 4; i++) {
                ADValue_offset[i] = adc_sum[i] / 10.0;
            }
				initial_value =1784;
                Key_Beep();  // ������������100ms
                printf("У׼���: ADCƫ���� = %f, %f, %f, %f;initial_value = %d\n", ADValue_offset[0], ADValue_offset[1], ADValue_offset[2], ADValue_offset[3],initial_value);	
			}else{
						
				for (int i = 0; i < 4; i++) {
                ADValue_offset[i] = 0;
				initial_value = 0;								
                }
                Key_Beep();  // ������������100ms
				printf("У׼���: ADCƫ���� = %f, %f, %f, %f;initial_value = %d\n", ADValue_offset[0], ADValue_offset[1], ADValue_offset[2], ADValue_offset[3],initial_value);		
				}
        }
#endif	
			break;
	
        default:
            break;
        
        }
    }
    }
}

// ����������
void KeyHandler_Process(void) {
    if (Key0Cfg.KEY_Event != KEY_Event_Null) {
        Handle_Key0_Event(Key0Cfg.KEY_Event);
        Key0Cfg.KEY_Event = KEY_Event_Null;
    }
    if (Key1Cfg.KEY_Event != KEY_Event_Null) {
        Handle_Key1_Event(Key1Cfg.KEY_Event);
        Key1Cfg.KEY_Event = KEY_Event_Null;
    }
    if (Key2Cfg.KEY_Event != KEY_Event_Null) {
        Handle_Key2_Event(Key2Cfg.KEY_Event);
        Key2Cfg.KEY_Event = KEY_Event_Null;
    }
    if (Key3Cfg.KEY_Event != KEY_Event_Null) {
        Handle_Key3_Event(Key3Cfg.KEY_Event);
        Key3Cfg.KEY_Event = KEY_Event_Null;
    }
    if (Key4Cfg.KEY_Event != KEY_Event_Null) {
        Handle_Key4_Event(Key4Cfg.KEY_Event);
        Key4Cfg.KEY_Event = KEY_Event_Null;
    }
    if (Key5Cfg.KEY_Event != KEY_Event_Null) {
        Handle_Key5_Event(Key5Cfg.KEY_Event);
        Key5Cfg.KEY_Event = KEY_Event_Null;
    }
}
