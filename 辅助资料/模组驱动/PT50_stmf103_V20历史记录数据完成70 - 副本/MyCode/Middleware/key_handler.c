#include "key_handler.h"
#include "stdio.h"
#include "buzzer.h"
#include "delay.h"
#include "LCD_HT1623.h"
#include "battery.h"
#include "stmflash.h"

u8 Zero_flag,lock_flag,longocked_flag;

// 按键配置结构体的外部声明
extern KEY_Configure_TypeDef Key0Cfg;
extern KEY_Configure_TypeDef Key1Cfg;
extern KEY_Configure_TypeDef Key2Cfg;
extern KEY_Configure_TypeDef Key3Cfg;
extern KEY_Configure_TypeDef Key4Cfg;
extern KEY_Configure_TypeDef Key5Cfg;

Settings current_settings;
int settings_mode = 0;
static int setting_item = SETTING_UNIT; // 当前设置项
u8 Zero_flag = 0; //清零

/*---------------------------------------flash----------------------------------------------------*/
#define SETTINGS_FLASH_ADDR  0X08030000 //设置FLASH 保存地址(必须为偶数，且其值要大于本代码所占用FLASH的大小+0X08000000)
void SaveSettingsToFlash(const Settings *settings) {
    STMFLASH_Write(SETTINGS_FLASH_ADDR, (uint16_t*)settings, sizeof(Settings) / 2);
}

void LoadSettingsFromFlash(Settings *settings) {
    STMFLASH_Read(SETTINGS_FLASH_ADDR, (uint16_t*)settings, sizeof(Settings) / 2);
}

// 保存当前设置到非易失性存储器
void SaveCurrentSettings() {
    SaveSettingsToFlash(&current_settings);
}

/*---------------------------------------flash----------------------------------------------------*/
// 保存设置函数
void SaveSettings()
{
    printf("保存设置: 当前单位: %d, 当前传感器数量: %d\n", current_settings.current_unit, current_settings.sensor_count == 0 ? 2 : 4);
    SaveCurrentSettings();
    setting_item = (setting_item + 1) % SETTING_MAX; // 跳转到下一个设置项
    if (setting_item == SETTING_UNIT)
    {
        printf("切换到设置单位\n");
    }
    else if (setting_item == SETTING_SENSOR_COUNT)
    {
        printf("切换到设置传感器数量\n");
    }
    if (setting_item == 0)
    {
        // 所有设置项都设置完，退出设置模式
        settings_mode = 0;
        printf("所有设置项都设置完，退出设置模式\n");
    }
}

/*---------------------------------------------------flash存储历史数据---------------------------------------------------*/
#define MAX_HISTORY_RECORDS 20 // 历史记录最大数量
//#define HISTORY_FLASH_ADDR 0x08030800 // 历史记录存储的起始地址
#define BUFFER_SIZE 2048 // 每个缓冲区的大小
#define HISTORY_FLASH_ADDR1 0x08030800 // 第一个缓冲区的起始地址
#define HISTORY_FLASH_ADDR2 (HISTORY_FLASH_ADDR1 + BUFFER_SIZE) // 第二个缓冲区的起始地址

extern uint16_t ADC_Value[4];
extern float pressure[4];
typedef struct {
    float pressure[4];
    u16 ADC_Value[4];
} Record;

int history_index = 0; // 当前记录的索引
int current_history_display = -1; // 当前显示的历史记录索引，-1表示不在查看历史记录状态

// void SaveHistoryRecordToFlash(int index, const Record *record)
// {
//     int adjusted_index = (index - 1) % MAX_HISTORY_RECORDS; // 使用循环索引
//     STMFLASH_Write(HISTORY_FLASH_ADDR + adjusted_index * sizeof(Record), (uint16_t*)record, sizeof(Record) / 2);
// }
void SaveHistoryRecordToFlash(int index, const Record *record)//检查当前缓冲区是否满了，如果满了就切换到另一个缓冲区。
{
    int buffer_index = (index - 1) / MAX_HISTORY_RECORDS; // 判断使用哪个缓冲区
    int adjusted_index = (index - 1) % MAX_HISTORY_RECORDS; // 使用循环索引

    uint32_t write_addr = buffer_index == 0 ? 
        (HISTORY_FLASH_ADDR1 + adjusted_index * sizeof(Record)) :
        (HISTORY_FLASH_ADDR2 + adjusted_index * sizeof(Record));

    STMFLASH_Write(write_addr, (uint16_t*)record, sizeof(Record) / 2);

    // 如果缓冲区已满，擦除下一缓冲区
    if (adjusted_index == MAX_HISTORY_RECORDS - 1) {
        uint32_t erase_addr = buffer_index == 0 ? HISTORY_FLASH_ADDR2 : HISTORY_FLASH_ADDR1;
        FLASH_ErasePage(erase_addr);
    }
}

// void SaveCurrentHistoryIndexToFlash()
// {
//     STMFLASH_Write(HISTORY_FLASH_ADDR - sizeof(int), (uint16_t*)&history_index, sizeof(int) / 2);
// }
#define HISTORY_INDEX_ADDR 0x08030000 // 存储历史记录索引的地址

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
//         int adjusted_index = (index - 1) % MAX_HISTORY_RECORDS; // 使用循环索引
//         STMFLASH_Read(HISTORY_FLASH_ADDR + adjusted_index * sizeof(Record), (uint16_t*)record, sizeof(Record) / 2);
//     }
// }
void LoadHistoryRecordFromFlash(int index, Record *record)//判断当前使用哪个缓冲区来读取数据。
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

// 显示历史记录的函数
void DisplayHistoryRecord(int index)
{
    if (index > 0 && index <= MAX_HISTORY_RECORDS)
    {
        Record record;
        LoadHistoryRecordFromFlash(index, &record); // 调整索引以匹配从1开始的记录
        printf("显示历史记录索引: %d\n", index);

        float convertedPressure[4];
        switch(current_settings.current_unit)
        {
            case 0: // Pa
                for (int i = 0; i < 4; i++) {
                    convertedPressure[i] = record.pressure[i] * 100;
                }
                break;

            case 1: // kPa   需要1个小数点
                for (int i = 0; i < 4; i++) {
                    convertedPressure[i] = record.pressure[i] * 0.1;
                }
                break;

            case 2: // mmHg
                for (int i = 0; i < 4; i++) {
                    convertedPressure[i] = record.pressure[i] * 0.750062;
                }
                break;

            case 3: // Torr    这个单位立项报告没要求
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

            case 6: // inH2O    这个单位立项报告没要求
                for (int i = 0; i < 4; i++) {
                    convertedPressure[i] = record.pressure[i] * 0.401463;
                }
                break;

            case 7: // mmH2O    这个单位立项报告没要求
                for (int i = 0; i < 4; i++) {
                    convertedPressure[i] = record.pressure[i] * 10.1972;
                }
                break;

            case 8: // psi  需要2个小数点
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
            printf("Pressure %d: AD_Value= %d, 压力= %.2f HPa\r\n", i, record.ADC_Value[i], record.pressure[i]);
        }
    }
    else
    {
        printf("无效的历史记录索引: %d\n", index);
    }
}

void InitializeSettings() {
    LoadSettingsFromFlash(&current_settings);
    LoadHistoryIndexFromFlash();  //历史数据
    // 如果读取到无效的设置，可以设置默认值
    if (current_settings.buzzer_enabled != 0 && current_settings.buzzer_enabled != 1) {
        current_settings.buzzer_enabled = 1; // 默认值
    }
    if (current_settings.current_unit >= 10) {
        current_settings.current_unit = 0; // 默认值
    }
    if (current_settings.sensor_count != 0 && current_settings.sensor_count != 1) {
        current_settings.sensor_count = 0; // 默认值 2T
    }
}

// 处理按键0事件
void Handle_Key0_Event(KEY_EventList_TypeDef event)
{
    static int power_on = 0;
    static int backlight_on = 0;
    if (current_settings.buzzer_enabled)
    {
        Key_Beep();// 按键声音持续100ms
    }
    switch(event)
    {
        case KEY_Event_SingleClick:
            if (!power_on)
            {
                power_on = 1;
                GPIO_SetBits(GPIOA, GPIO_Pin_4);//电源
                GPIO_SetBits(GPIOB, GPIO_Pin_3);//背光打开   
                UpdateReadModifyWriteDisplay(15,Screen_Data_LED,1);
            }
            else
            {   
                backlight_on = !backlight_on;
                if (!backlight_on)
                {
                    GPIO_SetBits(GPIOB, GPIO_Pin_3);//背光打开       
                    UpdateReadModifyWriteDisplay(15,Screen_Data_LED,1);
                }
                else
                {
                    GPIO_ResetBits(GPIOB, GPIO_Pin_3);//背光关闭                     
                    UpdateReadModifyWriteDisplay(15,Screen_Data_LED,0);
                }
            }
            break;

        case KEY_Event_LongPress:
            if (power_on)
            {
                power_on = 0;
                GPIO_ResetBits(GPIOB, GPIO_Pin_3);//背光关闭
                UpdateReadModifyWriteDisplay(15,Screen_Data_LED,0);
                GPIO_ResetBits(GPIOA, GPIO_Pin_4); // 关机电源                             
            }
            break;

        default:
            break;
    }
}

// 处理按键1事件
void Handle_Key1_Event(KEY_EventList_TypeDef event)
{
    if (current_settings.buzzer_enabled)
    {
        Key_Beep();// 按键声音持续100ms
    }
    printf("按键1事件: %d, settings_mode: %d, setting_item: %d\n", event, settings_mode, setting_item);    
    switch(event)
    {
        case KEY_Event_SingleClick:
            if (settings_mode)
            {
                // 设置模式下按键1用于向上翻动
                if (setting_item == SETTING_UNIT)
                {
                    current_settings.current_unit = (current_settings.current_unit - 1 + 10) % 10;
                    printf("当前单位: %d\r\n", current_settings.current_unit);
                }
                else if (setting_item == SETTING_SENSOR_COUNT)
                {
                    current_settings.sensor_count = (current_settings.sensor_count - 1 + 2) % 2;
                    printf("当前传感器数量: %d\r\n", current_settings.sensor_count == 0 ? 2 : 4);
                }
            }   
            else if (current_history_display != -1)
            {
                // 查看历史记录模式
                if (current_history_display > 1) //从第一条记录开始查看
                {
                    current_history_display--;
                    DisplayHistoryRecord(current_history_display);
                }
            }
            break;

        case KEY_Event_LongPress:
            current_settings.buzzer_enabled = !current_settings.buzzer_enabled;//按键声音标志位
            printf("蜂鸣器%s\r\n", current_settings.buzzer_enabled ? "打开" : "关闭");
            if (current_settings.buzzer_enabled)
            {                  
                printf("这里要点亮蜂鸣器图标\r\n");   
                UpdateReadModifyWriteDisplay(15,Screen_Data_BUZZER,1);                                   
            }
            else
            {
                printf("这里要熄灭蜂鸣器图标\r\n");    
                UpdateReadModifyWriteDisplay(15,Screen_Data_BUZZER,0);                                    
            }
            SaveCurrentSettings(); // 保存设置
            break;

        default:
            break;
    }
}

// 处理按键2事件
void Handle_Key2_Event(KEY_EventList_TypeDef event)
{
    static u8 rec_mode = 0;
    static u8 rec_data = 0;
    if (current_settings.buzzer_enabled)
    {
        Key_Beep();// 按键声音持续100ms
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
                printf("保存数据\r\n");
                Record new_record;
                for (int i = 0; i < 4; i++) {
                    new_record.pressure[i] = pressure[i];
                    new_record.ADC_Value[i] = ADC_Value[i];
                }
                SaveHistoryRecordToFlash(history_index + 1, &new_record); // 调整索引以匹配从1开始的记录
                printf("保存数据到记录索引: %d\n", (history_index + 1) % MAX_HISTORY_RECORDS);
                history_index = (history_index + 1) % (MAX_HISTORY_RECORDS + 1); // 确保索引循环使用
                SaveCurrentHistoryIndexToFlash(); // 保存当前历史记录索引
            }
        }
            break;

        case KEY_Event_LongPress:
        rec_mode =0;
        rec_data =1;    
            if (current_history_display == -1) {
                current_history_display = history_index ==1; // 从最新的记录开始查看
                UpdateReadModifyWriteDisplay(14, Screen_Data_REC + Screen_Data_R1, 1);
                printf("查看历史数据\n");
                DisplayHistoryRecord(current_history_display);
            } else {
                // 退出历史记录查看模式
                current_history_display = -1;
                printf("退出查看历史数据模式\n");
                UpdateReadModifyWriteDisplay(14, Screen_Data_REC + Screen_Data_R1, 0);
                rec_data =0;
            }
            break;

        default:
            break;
    }
}

// 处理按键3事件lock
void Handle_Key3_Event(KEY_EventList_TypeDef event)
{
    static int data_locked = 0;
    static int longdata_locked = 0;
    if (current_settings.buzzer_enabled)
    {
        Key_Beep();// 按键声音持续100ms
    }
    switch(event)
    {
        case KEY_Event_SingleClick:
            data_locked = !data_locked;
            printf("数据%s\r\n", data_locked ? "锁定" : "解锁");
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
            printf("数据%s\r\n", longdata_locked ? "锁定" : "解锁");
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

// 处理按键4事件
void Handle_Key4_Event(KEY_EventList_TypeDef event)
{
    if (current_settings.buzzer_enabled)
    {
        Key_Beep();// 按键声音持续100ms
    }
    switch(event)
    {
        case KEY_Event_SingleClick:
            if (settings_mode)
            {
                // 设置模式下按键4用于向下翻动
                if (setting_item == SETTING_UNIT)
                {
                    current_settings.current_unit = (current_settings.current_unit + 1 + 10) % 10;
                    printf("当前单位: %d\r\n", current_settings.current_unit);
                }
                else if (setting_item == SETTING_SENSOR_COUNT)
                {
                    current_settings.sensor_count = (current_settings.sensor_count + 1 + 2) % 2;
                    printf("当前传感器数量: %d\r\n", current_settings.sensor_count == 0 ? 2 : 4);
                }
            }
            else if (current_history_display != -1)
            {
                // 查看历史记录模式
                if (current_history_display < history_index)
                {
                    current_history_display++;
                    DisplayHistoryRecord(current_history_display);
                }
            }
            break;

        case KEY_Event_DoubleClick:   
            SaveSettings();
            printf("保存设置并跳转到下一个设置项\n");
            break;

        case KEY_Event_LongPress:
            settings_mode = 1; //
            ClearMercuryDisplay();//压力显示数码段和汞柱刷新
            printf("进入设置模式\r\n");
            break;

        default:
            break;
    }
}



// 处理按键5事件
void Handle_Key5_Event(KEY_EventList_TypeDef event)
{
    if (current_settings.buzzer_enabled)
    {
        Key_Beep();// 按键声音持续100ms
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
            printf("清0长按P=0\r\n");
            break;

        default:
            break;
    }
}

void KeyHandler_Process(void)
{
    if(Key0Cfg.KEY_Event != KEY_Event_Null)
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_4);//电源
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
