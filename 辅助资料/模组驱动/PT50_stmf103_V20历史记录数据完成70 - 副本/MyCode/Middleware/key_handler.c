#include "key_handler.h"
#include "stdio.h"
#include "buzzer.h"
#include "delay.h"
#include "LCD_HT1623.h"
#include "battery.h"
#include "stmflash.h"

u8 Zero_flag,lock_flag,longocked_flag;

// �������ýṹ����ⲿ����
extern KEY_Configure_TypeDef Key0Cfg;
extern KEY_Configure_TypeDef Key1Cfg;
extern KEY_Configure_TypeDef Key2Cfg;
extern KEY_Configure_TypeDef Key3Cfg;
extern KEY_Configure_TypeDef Key4Cfg;
extern KEY_Configure_TypeDef Key5Cfg;

Settings current_settings;
int settings_mode = 0;
static int setting_item = SETTING_UNIT; // ��ǰ������
u8 Zero_flag = 0; //����

/*---------------------------------------flash----------------------------------------------------*/
#define SETTINGS_FLASH_ADDR  0X08030000 //����FLASH �����ַ(����Ϊż��������ֵҪ���ڱ�������ռ��FLASH�Ĵ�С+0X08000000)
void SaveSettingsToFlash(const Settings *settings) {
    STMFLASH_Write(SETTINGS_FLASH_ADDR, (uint16_t*)settings, sizeof(Settings) / 2);
}

void LoadSettingsFromFlash(Settings *settings) {
    STMFLASH_Read(SETTINGS_FLASH_ADDR, (uint16_t*)settings, sizeof(Settings) / 2);
}

// ���浱ǰ���õ�����ʧ�Դ洢��
void SaveCurrentSettings() {
    SaveSettingsToFlash(&current_settings);
}

/*---------------------------------------flash----------------------------------------------------*/
// �������ú���
void SaveSettings()
{
    printf("��������: ��ǰ��λ: %d, ��ǰ����������: %d\n", current_settings.current_unit, current_settings.sensor_count == 0 ? 2 : 4);
    SaveCurrentSettings();
    setting_item = (setting_item + 1) % SETTING_MAX; // ��ת����һ��������
    if (setting_item == SETTING_UNIT)
    {
        printf("�л������õ�λ\n");
    }
    else if (setting_item == SETTING_SENSOR_COUNT)
    {
        printf("�л������ô���������\n");
    }
    if (setting_item == 0)
    {
        // ��������������꣬�˳�����ģʽ
        settings_mode = 0;
        printf("��������������꣬�˳�����ģʽ\n");
    }
}

/*---------------------------------------------------flash�洢��ʷ����---------------------------------------------------*/
#define MAX_HISTORY_RECORDS 20 // ��ʷ��¼�������
//#define HISTORY_FLASH_ADDR 0x08030800 // ��ʷ��¼�洢����ʼ��ַ
#define BUFFER_SIZE 2048 // ÿ���������Ĵ�С
#define HISTORY_FLASH_ADDR1 0x08030800 // ��һ������������ʼ��ַ
#define HISTORY_FLASH_ADDR2 (HISTORY_FLASH_ADDR1 + BUFFER_SIZE) // �ڶ�������������ʼ��ַ

extern uint16_t ADC_Value[4];
extern float pressure[4];
typedef struct {
    float pressure[4];
    u16 ADC_Value[4];
} Record;

int history_index = 0; // ��ǰ��¼������
int current_history_display = -1; // ��ǰ��ʾ����ʷ��¼������-1��ʾ���ڲ鿴��ʷ��¼״̬

// void SaveHistoryRecordToFlash(int index, const Record *record)
// {
//     int adjusted_index = (index - 1) % MAX_HISTORY_RECORDS; // ʹ��ѭ������
//     STMFLASH_Write(HISTORY_FLASH_ADDR + adjusted_index * sizeof(Record), (uint16_t*)record, sizeof(Record) / 2);
// }
void SaveHistoryRecordToFlash(int index, const Record *record)//��鵱ǰ�������Ƿ����ˣ�������˾��л�����һ����������
{
    int buffer_index = (index - 1) / MAX_HISTORY_RECORDS; // �ж�ʹ���ĸ�������
    int adjusted_index = (index - 1) % MAX_HISTORY_RECORDS; // ʹ��ѭ������

    uint32_t write_addr = buffer_index == 0 ? 
        (HISTORY_FLASH_ADDR1 + adjusted_index * sizeof(Record)) :
        (HISTORY_FLASH_ADDR2 + adjusted_index * sizeof(Record));

    STMFLASH_Write(write_addr, (uint16_t*)record, sizeof(Record) / 2);

    // ���������������������һ������
    if (adjusted_index == MAX_HISTORY_RECORDS - 1) {
        uint32_t erase_addr = buffer_index == 0 ? HISTORY_FLASH_ADDR2 : HISTORY_FLASH_ADDR1;
        FLASH_ErasePage(erase_addr);
    }
}

// void SaveCurrentHistoryIndexToFlash()
// {
//     STMFLASH_Write(HISTORY_FLASH_ADDR - sizeof(int), (uint16_t*)&history_index, sizeof(int) / 2);
// }
#define HISTORY_INDEX_ADDR 0x08030000 // �洢��ʷ��¼�����ĵ�ַ

void SaveCurrentHistoryIndexToFlash()
{
    STMFLASH_Write(HISTORY_INDEX_ADDR, (uint16_t*)&history_index, sizeof(int) / 2);
}

void LoadHistoryIndexFromFlash()
{
    STMFLASH_Read(HISTORY_INDEX_ADDR, (uint16_t*)&history_index, sizeof(int) / 2);
}

// void LoadHistoryRecordFromFlash(int index, Record *record)
// {
//     if (index > 0 && index <= MAX_HISTORY_RECORDS) {
//         int adjusted_index = (index - 1) % MAX_HISTORY_RECORDS; // ʹ��ѭ������
//         STMFLASH_Read(HISTORY_FLASH_ADDR + adjusted_index * sizeof(Record), (uint16_t*)record, sizeof(Record) / 2);
//     }
// }
void LoadHistoryRecordFromFlash(int index, Record *record)//�жϵ�ǰʹ���ĸ�����������ȡ���ݡ�
{
    if (index > 0 && index <= MAX_HISTORY_RECORDS * 2) {
        int buffer_index = (index - 1) / MAX_HISTORY_RECORDS;
        int adjusted_index = (index - 1) % MAX_HISTORY_RECORDS;

        uint32_t read_addr = buffer_index == 0 ? 
            (HISTORY_FLASH_ADDR1 + adjusted_index * sizeof(Record)) :
            (HISTORY_FLASH_ADDR2 + adjusted_index * sizeof(Record));

        STMFLASH_Read(read_addr, (uint16_t*)record, sizeof(Record) / 2);
    }
}

// void LoadHistoryIndexFromFlash()
// {
//     STMFLASH_Read(HISTORY_FLASH_ADDR - sizeof(int), (uint16_t*)&history_index, sizeof(int) / 2);
// }

// void SaveHistoryIndexToFlash()
// {
//     STMFLASH_Write(HISTORY_FLASH_ADDR - sizeof(int), (uint16_t*)&history_index, sizeof(int) / 2);
// }

// ��ʾ��ʷ��¼�ĺ���
void DisplayHistoryRecord(int index)
{
    if (index > 0 && index <= MAX_HISTORY_RECORDS)
    {
        Record record;
        LoadHistoryRecordFromFlash(index, &record); // ����������ƥ���1��ʼ�ļ�¼
        printf("��ʾ��ʷ��¼����: %d\n", index);

        float convertedPressure[4];
        switch(current_settings.current_unit)
        {
            case 0: // Pa
                for (int i = 0; i < 4; i++) {
                    convertedPressure[i] = record.pressure[i] * 100;
                }
                break;

            case 1: // kPa   ��Ҫ1��С����
                for (int i = 0; i < 4; i++) {
                    convertedPressure[i] = record.pressure[i] * 0.1;
                }
                break;

            case 2: // mmHg
                for (int i = 0; i < 4; i++) {
                    convertedPressure[i] = record.pressure[i] * 0.750062;
                }
                break;

            case 3: // Torr    �����λ�����ûҪ��
                for (int i = 0; i < 4; i++) {
                    convertedPressure[i] = record.pressure[i] * 0.750062;
                }
                break;

            case 4: // mbar
                for (int i = 0; i < 4; i++) {
                    convertedPressure[i] = record.pressure[i];
                }
                break;

            case 5: // inHg
                for (int i = 0; i < 4; i++) {
                    convertedPressure[i] = record.pressure[i] * 0.0295301;
                }
                break;

            case 6: // inH2O    �����λ�����ûҪ��
                for (int i = 0; i < 4; i++) {
                    convertedPressure[i] = record.pressure[i] * 0.401463;
                }
                break;

            case 7: // mmH2O    �����λ�����ûҪ��
                for (int i = 0; i < 4; i++) {
                    convertedPressure[i] = record.pressure[i] * 10.1972;
                }
                break;

            case 8: // psi  ��Ҫ2��С����
                for (int i = 0; i < 4; i++) {
                    convertedPressure[i] = record.pressure[i] * 0.0145038;
                }
                break;

            case 9: // hPa
                for (int i = 0; i < 4; i++) {
                    convertedPressure[i] = record.pressure[i];
                }
                break;
        }

        for (int i = 0; i < 4; i++) {
            Digital_tube_display(1 + 5 * i, 2 + 5 * i, 3 + 5 * i, 4 + 5 * i, 5 + 5 * i, convertedPressure[i], record.ADC_Value[i]);
            printf("Pressure %d: AD_Value= %d, ѹ��= %.2f HPa\r\n", i, record.ADC_Value[i], record.pressure[i]);
        }
    }
    else
    {
        printf("��Ч����ʷ��¼����: %d\n", index);
    }
}

void InitializeSettings() {
    LoadSettingsFromFlash(&current_settings);
    LoadHistoryIndexFromFlash();  //��ʷ����
    // �����ȡ����Ч�����ã���������Ĭ��ֵ
    if (current_settings.buzzer_enabled != 0 && current_settings.buzzer_enabled != 1) {
        current_settings.buzzer_enabled = 1; // Ĭ��ֵ
    }
    if (current_settings.current_unit >= 10) {
        current_settings.current_unit = 0; // Ĭ��ֵ
    }
    if (current_settings.sensor_count != 0 && current_settings.sensor_count != 1) {
        current_settings.sensor_count = 0; // Ĭ��ֵ 2T
    }
}

// ������0�¼�
void Handle_Key0_Event(KEY_EventList_TypeDef event)
{
    static int power_on = 0;
    static int backlight_on = 0;
    if (current_settings.buzzer_enabled)
    {
        Key_Beep();// ������������100ms
    }
    switch(event)
    {
        case KEY_Event_SingleClick:
            if (!power_on)
            {
                power_on = 1;
                GPIO_SetBits(GPIOA, GPIO_Pin_4);//��Դ
                GPIO_SetBits(GPIOB, GPIO_Pin_3);//�����   
                UpdateReadModifyWriteDisplay(15,Screen_Data_LED,1);
            }
            else
            {   
                backlight_on = !backlight_on;
                if (!backlight_on)
                {
                    GPIO_SetBits(GPIOB, GPIO_Pin_3);//�����       
                    UpdateReadModifyWriteDisplay(15,Screen_Data_LED,1);
                }
                else
                {
                    GPIO_ResetBits(GPIOB, GPIO_Pin_3);//����ر�                     
                    UpdateReadModifyWriteDisplay(15,Screen_Data_LED,0);
                }
            }
            break;

        case KEY_Event_LongPress:
            if (power_on)
            {
                power_on = 0;
                GPIO_ResetBits(GPIOB, GPIO_Pin_3);//����ر�
                UpdateReadModifyWriteDisplay(15,Screen_Data_LED,0);
                GPIO_ResetBits(GPIOA, GPIO_Pin_4); // �ػ���Դ                             
            }
            break;

        default:
            break;
    }
}

// ������1�¼�
void Handle_Key1_Event(KEY_EventList_TypeDef event)
{
    if (current_settings.buzzer_enabled)
    {
        Key_Beep();// ������������100ms
    }
    printf("����1�¼�: %d, settings_mode: %d, setting_item: %d\n", event, settings_mode, setting_item);    
    switch(event)
    {
        case KEY_Event_SingleClick:
            if (settings_mode)
            {
                // ����ģʽ�°���1�������Ϸ���
                if (setting_item == SETTING_UNIT)
                {
                    current_settings.current_unit = (current_settings.current_unit - 1 + 10) % 10;
                    printf("��ǰ��λ: %d\r\n", current_settings.current_unit);
                }
                else if (setting_item == SETTING_SENSOR_COUNT)
                {
                    current_settings.sensor_count = (current_settings.sensor_count - 1 + 2) % 2;
                    printf("��ǰ����������: %d\r\n", current_settings.sensor_count == 0 ? 2 : 4);
                }
            }   
            else if (current_history_display != -1)
            {
                // �鿴��ʷ��¼ģʽ
                if (current_history_display > 1) //�ӵ�һ����¼��ʼ�鿴
                {
                    current_history_display--;
                    DisplayHistoryRecord(current_history_display);
                }
            }
            break;

        case KEY_Event_LongPress:
            current_settings.buzzer_enabled = !current_settings.buzzer_enabled;//����������־λ
            printf("������%s\r\n", current_settings.buzzer_enabled ? "��" : "�ر�");
            if (current_settings.buzzer_enabled)
            {                  
                printf("����Ҫ����������ͼ��\r\n");   
                UpdateReadModifyWriteDisplay(15,Screen_Data_BUZZER,1);                                   
            }
            else
            {
                printf("����ҪϨ�������ͼ��\r\n");    
                UpdateReadModifyWriteDisplay(15,Screen_Data_BUZZER,0);                                    
            }
            SaveCurrentSettings(); // ��������
            break;

        default:
            break;
    }
}

// ������2�¼�
void Handle_Key2_Event(KEY_EventList_TypeDef event)
{
    static u8 rec_mode = 0;
    static u8 rec_data = 0;
    if (current_settings.buzzer_enabled)
    {
        Key_Beep();// ������������100ms
    }
    switch(event)
    {
        case KEY_Event_SingleClick:
        if(rec_data ==0){
            if (!rec_mode)
            {
                rec_mode = 1;
                UpdateReadModifyWriteDisplay(14,Screen_Data_REC,1);
            }
            else
            {
                printf("��������\r\n");
                Record new_record;
                for (int i = 0; i < 4; i++) {
                    new_record.pressure[i] = pressure[i];
                    new_record.ADC_Value[i] = ADC_Value[i];
                }
                SaveHistoryRecordToFlash(history_index + 1, &new_record); // ����������ƥ���1��ʼ�ļ�¼
                printf("�������ݵ���¼����: %d\n", (history_index + 1) % MAX_HISTORY_RECORDS);
                history_index = (history_index + 1) % (MAX_HISTORY_RECORDS + 1); // ȷ������ѭ��ʹ��
                SaveCurrentHistoryIndexToFlash(); // ���浱ǰ��ʷ��¼����
            }
        }
            break;

        case KEY_Event_LongPress:
        rec_mode =0;
        rec_data =1;    
            if (current_history_display == -1) {
                current_history_display = history_index ==1; // �����µļ�¼��ʼ�鿴
                UpdateReadModifyWriteDisplay(14, Screen_Data_REC + Screen_Data_R1, 1);
                printf("�鿴��ʷ����\n");
                DisplayHistoryRecord(current_history_display);
            } else {
                // �˳���ʷ��¼�鿴ģʽ
                current_history_display = -1;
                printf("�˳��鿴��ʷ����ģʽ\n");
                UpdateReadModifyWriteDisplay(14, Screen_Data_REC + Screen_Data_R1, 0);
                rec_data =0;
            }
            break;

        default:
            break;
    }
}

// ������3�¼�lock
void Handle_Key3_Event(KEY_EventList_TypeDef event)
{
    static int data_locked = 0;
    static int longdata_locked = 0;
    if (current_settings.buzzer_enabled)
    {
        Key_Beep();// ������������100ms
    }
    switch(event)
    {
        case KEY_Event_SingleClick:
            data_locked = !data_locked;
            printf("����%s\r\n", data_locked ? "����" : "����");
            if (data_locked)
            {
                UpdateReadModifyWriteDisplay(15,Screen_Data_lock,1);
                lock_flag = 1;
            }
            else
            {
                UpdateReadModifyWriteDisplay(15,Screen_Data_lock,0);
                lock_flag = 0;
            }
            break;
        case KEY_Event_LongPress:
            longdata_locked = !longdata_locked;
            printf("����%s\r\n", longdata_locked ? "����" : "����");
            if (longdata_locked)
            {
                UpdateReadModifyWriteDisplay(15,Screen_Data_lock,1);
                longocked_flag = 1;
            }
            else
            {
                UpdateReadModifyWriteDisplay(15,Screen_Data_lock,0);
                longocked_flag = 0;
            }
            break;

        default:
            break;
    }
}

// ������4�¼�
void Handle_Key4_Event(KEY_EventList_TypeDef event)
{
    if (current_settings.buzzer_enabled)
    {
        Key_Beep();// ������������100ms
    }
    switch(event)
    {
        case KEY_Event_SingleClick:
            if (settings_mode)
            {
                // ����ģʽ�°���4�������·���
                if (setting_item == SETTING_UNIT)
                {
                    current_settings.current_unit = (current_settings.current_unit + 1 + 10) % 10;
                    printf("��ǰ��λ: %d\r\n", current_settings.current_unit);
                }
                else if (setting_item == SETTING_SENSOR_COUNT)
                {
                    current_settings.sensor_count = (current_settings.sensor_count + 1 + 2) % 2;
                    printf("��ǰ����������: %d\r\n", current_settings.sensor_count == 0 ? 2 : 4);
                }
            }
            else if (current_history_display != -1)
            {
                // �鿴��ʷ��¼ģʽ
                if (current_history_display < history_index)
                {
                    current_history_display++;
                    DisplayHistoryRecord(current_history_display);
                }
            }
            break;

        case KEY_Event_DoubleClick:   
            SaveSettings();
            printf("�������ò���ת����һ��������\n");
            break;

        case KEY_Event_LongPress:
            settings_mode = 1; //
            ClearMercuryDisplay();//ѹ����ʾ����κ͹���ˢ��
            printf("��������ģʽ\r\n");
            break;

        default:
            break;
    }
}



// ������5�¼�
void Handle_Key5_Event(KEY_EventList_TypeDef event)
{
    if (current_settings.buzzer_enabled)
    {
        Key_Beep();// ������������100ms
    }
    switch(event)
    {
        case KEY_Event_SingleClick:
            UpdateReadModifyWriteDisplay(15,Screen_Data_Zero,1);
            Zero_flag  = 1;
            delay_ms(300);
            UpdateReadModifyWriteDisplay(15,Screen_Data_Zero,0);
            printf("ZERO\r\n");
            break;

        case KEY_Event_LongPress:
            Calibration(); //
            printf("��0����P=0\r\n");
            break;

        default:
            break;
    }
}

void KeyHandler_Process(void)
{
    if(Key0Cfg.KEY_Event != KEY_Event_Null)
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_4);//��Դ
        Handle_Key0_Event(Key0Cfg.KEY_Event);
        Key0Cfg.KEY_Event = KEY_Event_Null;
    }

    if(Key1Cfg.KEY_Event != KEY_Event_Null)
    {
        Handle_Key1_Event(Key1Cfg.KEY_Event);
        Key1Cfg.KEY_Event = KEY_Event_Null;
    }

    if(Key2Cfg.KEY_Event != KEY_Event_Null)
    {
        Handle_Key2_Event(Key2Cfg.KEY_Event);
        Key2Cfg.KEY_Event = KEY_Event_Null;
    }

    if(Key3Cfg.KEY_Event != KEY_Event_Null)
    {
        Handle_Key3_Event(Key3Cfg.KEY_Event);
        Key3Cfg.KEY_Event = KEY_Event_Null;
    }

    if(Key4Cfg.KEY_Event != KEY_Event_Null)
    {
        Handle_Key4_Event(Key4Cfg.KEY_Event);
        Key4Cfg.KEY_Event = KEY_Event_Null;
    }

    if(Key5Cfg.KEY_Event != KEY_Event_Null)
    {
        Handle_Key5_Event(Key5Cfg.KEY_Event);
        Key5Cfg.KEY_Event = KEY_Event_Null;
    }
}
