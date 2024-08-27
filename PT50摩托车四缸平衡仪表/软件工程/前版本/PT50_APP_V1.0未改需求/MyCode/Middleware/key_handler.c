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
u8 Zero_flag, lock_flag, longocked_flag, Switch_flag, REC_flag;  // 定义一些全局变量
extern float pressure_offset[4];// 用于存储校准的压力偏移值
// 按键配置结构体的外部声明
extern KEY_Configure_TypeDef Key0Cfg;
extern KEY_Configure_TypeDef Key1Cfg;
extern KEY_Configure_TypeDef Key2Cfg;
extern KEY_Configure_TypeDef Key3Cfg;
extern KEY_Configure_TypeDef Key4Cfg;
extern KEY_Configure_TypeDef Key5Cfg;

Settings current_settings;  // 当前设置
int settings_mode = 0;  // 设置模式标志
static int setting_item = SETTING_UNIT;  // 当前设置项
u8 Zero_flag = 0;  // 清零标志

/*--------------------------------------- Flash 存储相关定义 ----------------------------------------------------*/
#define SETTINGS_FLASH_ADDR 0X08030000  // 设置保存地址
#define HISTORY_INDEX_ADDR 0x08030000+(sizeof(Settings))  // 存储历史记录索引的地址
#define BUFFER_SIZE 2048  // 缓冲区的大小
#define HISTORY_FLASH_ADDR 0x08030800  // 缓冲区的起始地址

// 将设置保存到 Flash
void SaveSettingsToFlash(const Settings *settings) {
    STMFLASH_Write(SETTINGS_FLASH_ADDR, (uint16_t*)settings, sizeof(Settings) / 2);
}

// 从 Flash 中读取设置
void LoadSettingsFromFlash(Settings *settings) {
    STMFLASH_Read(SETTINGS_FLASH_ADDR, (uint16_t*)settings, sizeof(Settings) / 2);
}

// 保存当前设置到非易失性存储器
void SaveCurrentSettings() {
    SaveSettingsToFlash(&current_settings);
}

// 保存设置函数
void SaveSettings() {
    printf("保存设置: 当前单位: %d, 当前传感器数量: %d\n", current_settings.current_unit, current_settings.sensor_count == 0 ? 2 : 4);
    SaveCurrentSettings();
    setting_item = (setting_item + 1) % SETTING_MAX;  // 跳转到下一个设置项
    Switching2T4T_display();
    
    // 打印不同设置项的消息
    switch (setting_item) {
        case SETTING_UNIT:
            printf("切换到设置单位\n");
            break;
        case SETTING_SENSOR_COUNT:
            printf("切换到设置传感器数量\n");
            break;
        case SETTING_AUTO_SHUTDOWN:  // 处理自动关机设置项
            AUutoshutdownONOFF_display();
            printf("切换到设置自动关机\n");
            printf("%d\n",current_settings.auto_shutdown_enabled);
            break;
    }
    if (setting_item == 0) {
        // 所有设置项都设置完，退出设置模式
        settings_mode = 0;
        printf("所有设置项都设置完，退出设置模式\n");
    }
}
/*-------------------------------------- Flash 存储历史数据 --------------------------------------*/
#define MAX_HISTORY_RECORDS 20  // 历史记录最大数量
extern float pressure[4];
extern u8 Second, Minute, Hour;
static u8 rec_data = 0;

typedef struct {
    float pressure[4];
    u16 ADC_Value[4];
    u8 Second, Minute, Hour;
    u8 sensor_mode;  // 新增字段：0 表示 4T，1 表示 2T
} Record;

int history_index = 0;  // 当前记录的索引
int total_records = 0;  // 总记录数
int current_history_display = -1;  // 当前显示的历史记录索引，-1 表示不在查看历史记录状态
int in_submode = 0; // 标记是否处于子模式
int submode_index = 0; // 当前子模式索引 0:最大值, 1:最小值, 2:差值

// 保存历史记录到 Flash
void SaveHistoryRecordToFlash(int index, const Record *record) {
    int adjusted_index = (index % MAX_HISTORY_RECORDS) + 1;  // 使用循环索引并从 1 开始
    uint32_t write_addr = HISTORY_FLASH_ADDR + (adjusted_index - 1) * sizeof(Record); // 将调整后的索引从1开始
    STMFLASH_Write(write_addr, (uint16_t*)record, sizeof(Record) / 2);
}

// 将当前历史记录索引保存到 Flash
void SaveCurrentHistoryIndexToFlash() {
    STMFLASH_Write(HISTORY_INDEX_ADDR, (uint16_t*)&history_index, sizeof(int) / 2);
    STMFLASH_Write(HISTORY_INDEX_ADDR + sizeof(int), (uint16_t*)&total_records, sizeof(int) / 2);
}

// 从 Flash 中读取历史记录
void LoadHistoryRecordFromFlash(int index, Record *record) {
    int adjusted_index = index % MAX_HISTORY_RECORDS;  // 使用循环索引
    uint32_t read_addr = HISTORY_FLASH_ADDR + adjusted_index * sizeof(Record);
    STMFLASH_Read(read_addr, (uint16_t*)record, sizeof(Record) / 2);
}

// 从 Flash 中加载历史记录索引
void LoadHistoryIndexFromFlash() {
    STMFLASH_Read(HISTORY_INDEX_ADDR, (uint16_t*)&history_index, sizeof(int) / 2);
    STMFLASH_Read(HISTORY_INDEX_ADDR + sizeof(int), (uint16_t*)&total_records, sizeof(int) / 2);
}
extern u8 decimal_points;
// 显示历史记录的函数
void DisplayHistoryRecord(int index) {
    if (index >= 0 && index < total_records) {
        Record record;
        LoadHistoryRecordFromFlash(index, &record);  // index+1调整索引以匹配从 1 开始的记录
        printf("显示历史记录索引: %d\n", index + 1);
   
        float convertedPressure[4];
        //SwitcUint(record.pressure);
        
#if 1
        switch (current_settings.current_unit) {
            case 0: // Pa
                UpdateReadModifyWriteDisplay(22, Switching_Unit_Data_pa, 1);
                for (int i = 0; i < 4; i++) {
                    convertedPressure[i] = record.pressure[i] * 100;
                }
                decimal_points = 0; // 不需要小数点
                break;
            case 1: // kPa   需要2位小数点
                UpdateReadModifyWriteDisplay(22, 0x30, 1);
                for (int i = 0; i < 4; i++) {
                    convertedPressure[i] = record.pressure[i] * 0.1;
                    convertedPressure[i] = convertedPressure[i] * 100;
                }
                decimal_points = 2;
                break;
            case 2: // mmHg   1小数点
                UpdateReadModifyWriteDisplay(22, Switching_Unit_Data_mmHg, 1);
                for (int i = 0; i < 4; i++) {
                    convertedPressure[i] = record.pressure[i] * 0.750062;
                    convertedPressure[i] = convertedPressure[i] * 10;
                }
                decimal_points = 1;
                break;
            case 3: // Torr    1小数点   这个单位立项报告没要求
                UpdateReadModifyWriteDisplay(22, Switching_Unit_Data_Torr, 1);
                for (int i = 0; i < 4; i++) {
                    convertedPressure[i] = record.pressure[i] * 0.750062;
                    convertedPressure[i] = convertedPressure[i] * 10;
                }
                decimal_points = 1;
                break;
            case 4: // mbar    1小数点
                UpdateReadModifyWriteDisplay(22, Switching_Unit_Data_m + Switching_Unit_Data_bar, 1);
                for (int i = 0; i < 4; i++) {
                    convertedPressure[i] = record.pressure[i];
                    convertedPressure[i] = convertedPressure[i] * 10;
                }
                decimal_points = 1;
                break;
            case 5: // inHg    2小数点
                UpdateReadModifyWriteDisplay(23, Switching_Unit_Data_inHg, 1);
                for (int i = 0; i < 4; i++) {                    
                    convertedPressure[i] = record.pressure[i] * 0.0295301;
                    convertedPressure[i] = convertedPressure[i] * 100;
                }
                decimal_points = 2;
                break;
            case 6: // inH2O    1小数点   这个单位立项报告没要求
                UpdateReadModifyWriteDisplay(23, Switching_Unit_Data_inH2O, 1);
                for (int i = 0; i < 4; i++) {                   
                    convertedPressure[i] = record.pressure[i] * 0.401463;
                    convertedPressure[i] = convertedPressure[i] * 10;
                }
                decimal_points = 2;
                break;
            case 7: // mmH2O    无小数点   这个单位立项报告没要求
                UpdateReadModifyWriteDisplay(23, Switching_Unit_Data_mmH2O, 1);
                for (int i = 0; i < 4; i++) {
                    convertedPressure[i] = record.pressure[i] * 10.1972;
                }
                decimal_points = 0;
                break;
            case 8: // psi  需要2个小数点
                UpdateReadModifyWriteDisplay(23, Switching_Unit_Data_psi, 1);
                for (int i = 0; i < 4; i++) {
                    convertedPressure[i] = record.pressure[i] * 0.0145038;
                    convertedPressure[i] = convertedPressure[i] * 100;
                }
                decimal_points = 2;
                break;
            case 9: // hPa  1小数点
                UpdateReadModifyWriteDisplay(23, Switching_Unit_Data_hpa, 1);
                for (int i = 0; i < 4; i++) {
                    convertedPressure[i] = record.pressure[i];
                    convertedPressure[i] = convertedPressure[i] * 10;
                }
                decimal_points = 1;
                break;
        }
#endif
       if (record.sensor_mode == 1) { // 1表示2T模式
        
            // UpdateReadModifyWriteDisplay(10, Screen_Data_4T, 0);   //4T
            // UpdateReadModifyWriteDisplay(15, Screen_Data_2T, 1);   //2T        
            Digital_tube_display(1 + 5 * 0, 2 + 5 * 0, 3 + 5 * 0, 4 + 5 * 0, 5 + 5 * 0, convertedPressure[3], record.ADC_Value[3]);
            Digital_tube_display(1 + 5 * 1, 2 + 5 * 1, 3 + 5 * 1, 4 + 5 * 1, 5 + 5 * 1, convertedPressure[2], record.ADC_Value[2]);
            // 显示历史记录时钟
            UpdateReadModifyWriteDisplay(11, Screen_Data_Time, 1); // TIME图标显示
            TIME_Digital_tube_Bit_Display(record.Hour / 10, 1);
            TIME_Digital_tube_Bit_Display(record.Hour % 10, 2);
            UpdateReadModifyWriteDisplay(10, Group2_digitron_TIME_colon_S32, 1); // 冒号1显示
            TIME_Digital_tube_Bit_Display(record.Minute / 10, 3);
            TIME_Digital_tube_Bit_Display(record.Minute % 10, 4);
            UpdateReadModifyWriteDisplay(22, Group2_digitron_TIME_colon_S38, 1); // 冒号2显示
            TIME_Digital_tube_Bit_Display(record.Second / 10, 5);
            TIME_Digital_tube_Bit_Display(record.Second % 10, 6);
            NumHistoricalData_Display(26, 27, 28, 29, 30, index + 1); // 显示历史数据编号
            UpdateReadModifyWriteDisplay(10, Screen_Data_4T, 0);   //4T
            UpdateReadModifyWriteDisplay(15, Screen_Data_2T, 1);   //2T
            printf("Pressure %d: AD_Value= %d, 压力= %.2f HPa\r\n", 0, record.ADC_Value[3], record.pressure[3]);//1号缸
            printf("Pressure %d: AD_Value= %d, 压力= %.2f HPa\r\n", 1, record.ADC_Value[2], record.pressure[2]); //2号缸       
        }else{//4T模式             
            // UpdateReadModifyWriteDisplay(15, Screen_Data_2T, 0);   //2T  
            // UpdateReadModifyWriteDisplay(10, Screen_Data_4T, 1);     //4T
            Digital_tube_display(1 + 5 * 0, 2 + 5 * 0, 3 + 5 * 0, 4 + 5 * 0, 5 + 5 * 0, convertedPressure[3], record.ADC_Value[3]);//1号缸
            Digital_tube_display(1 + 5 * 1, 2 + 5 * 1, 3 + 5 * 1, 4 + 5 * 1, 5 + 5 * 1, convertedPressure[2], record.ADC_Value[2]);//2号缸
            Digital_tube_display(1 + 5 * 2, 2 + 5 * 2, 3 + 5 * 2, 4 + 5 * 2, 5 + 5 * 2, convertedPressure[1], record.ADC_Value[1]);//3号缸
            Digital_tube_display(1 + 5 * 3, 2 + 5 * 3, 3 + 5 * 3, 4 + 5 * 3, 5 + 5 * 3, convertedPressure[0], record.ADC_Value[0]);//4号缸                        
            // 显示历史记录时钟
            UpdateReadModifyWriteDisplay(11, Screen_Data_Time, 1); // TIME图标显示
            TIME_Digital_tube_Bit_Display(record.Hour / 10, 1);
            TIME_Digital_tube_Bit_Display(record.Hour % 10, 2);
            UpdateReadModifyWriteDisplay(10, Group2_digitron_TIME_colon_S32, 1); // 冒号1显示
            TIME_Digital_tube_Bit_Display(record.Minute / 10, 3);
            TIME_Digital_tube_Bit_Display(record.Minute % 10, 4);
            UpdateReadModifyWriteDisplay(22, Group2_digitron_TIME_colon_S38, 1); // 冒号2显示
            TIME_Digital_tube_Bit_Display(record.Second / 10, 5);
            TIME_Digital_tube_Bit_Display(record.Second % 10, 6);
            UpdateReadModifyWriteDisplay(10, Screen_Data_4T, 1);     //4T图标，因为受6号断码管影响会关掉4T图标，所以重新打开
            NumHistoricalData_Display(26, 27, 28, 29, 30, index + 1); // 显示历史数据编号
            UpdateReadModifyWriteDisplay(15, Screen_Data_2T, 0);   //2T  
            UpdateReadModifyWriteDisplay(10, Screen_Data_4T, 1);     //4T
            printf("Pressure %d: AD_Value= %d, 压力= %.2f HPa\r\n", 0, record.ADC_Value[3], record.pressure[3]);
            printf("Pressure %d: AD_Value= %d, 压力= %.2f HPa\r\n", 1, record.ADC_Value[2], record.pressure[2]);
            printf("Pressure %d: AD_Value= %d, 压力= %.2f HPa\r\n", 2, record.ADC_Value[1], record.pressure[1]);
            printf("Pressure %d: AD_Value= %d, 压力= %.2f HPa\r\n", 3, record.ADC_Value[0], record.pressure[0]);
       
        }
    } else {
        printf("无效的历史记录索引: %d\n", index + 1);
        if (current_settings.sensor_count == 0) {  //无历史记录时显示      
            // ClearDigitalTubeDisplay(); 
            // ClearMercuryDisplay();
            // Clear_Clock_Display();
            Digital_tube_display(1, 2, 3, 4, 5, 0, 1900);//1号缸
            Digital_tube_display(6, 7, 8, 9, 10, 0, 1900);//2号缸
            Digital_tube_display(11, 12, 13, 14, 15, 0, 1900);//3号缸
            Digital_tube_display(16, 17, 18, 19, 20, 0, 1900);//4号缸                  
        }else{     
            // ClearDigitalTubeDisplay(); 
            // ClearMercuryDisplay();
            // Clear_Clock_Display();
            Digital_tube_display(1, 2, 3, 4, 5,0, 1900);//1号缸
            Digital_tube_display(6, 7, 8, 9, 10,0, 1900);//2号缸             
        }
    }   
}

//u8 REC_flag = 0;
#define LARGE_NUMBER -1e30 // 对于负数情况，LARGE_NUMBER初始为一个非常小的负数
#define SMALL_NUMBER  1e30  // 初始为一个非常大的正数

void DisplaySubmodeData(int index) {
    REC_flag = 0;

    if (index >= 0 && index < total_records) {
        Record record;
        LoadHistoryRecordFromFlash(index, &record);

        float maxPressure = SMALL_NUMBER;  // 最大值初始为一个非常小的负数
        float minPressure = LARGE_NUMBER;  // 最小值初始为一个非常大的正数
        float diffPressure = 0;

        if (record.sensor_mode == 1) { // 1表示2T模式
            current_settings.sensor_count = 1;
            for (int i = 2; i < 4; i++) {
                if (record.pressure[i] < maxPressure) { // 对于负数，绝对值越小（数值越大）表示最大值
                    maxPressure = record.pressure[i];
                }
                if (record.pressure[i] > minPressure) { // 对于负数，绝对值越大（数值越小）表示最小值
                    minPressure = record.pressure[i];
                }
            }
        } else { // 4T模式
            for (int i = 0; i < 4; i++) {
                if (record.pressure[i] < maxPressure) { // 对于负数，绝对值越小（数值越大）表示最大值
                    maxPressure = record.pressure[i];
                }
                if (record.pressure[i] > minPressure) { // 对于负数，绝对值越大（数值越小）表示最小值
                    minPressure = record.pressure[i];
                }
            }
        }
        // if (display_num < 0) {
        // display_num = -display_num; // 转换为正数
        // }
        diffPressure = maxPressure - minPressure; // 计算差值
        float display_value = 0;
        switch (submode_index) {
            case 0:
                display_value = maxPressure;
                UpdateReadModifyWriteDisplay(11, Screen_Data_MAX, 1); // MAX图标显示				
                SettingsUint(display_value);
                printf("显示最大值: %.2f\n", display_value);
                break;
            case 1:
                display_value = minPressure;
                UpdateReadModifyWriteDisplay(11, Screen_Data_MIN, 1); // MIN图标显示
                SettingsUint(display_value);
                printf("显示最小值: %.2f\n", display_value);
                break;
            case 2:
                display_value = diffPressure;
                UpdateReadModifyWriteDisplay(11, Screen_Data_DifferValue, 1); // 差值图标显示
                SettingsUint(display_value);
                printf("显示差值: %.2f\n", display_value);
                break;
        }
    } else {
        printf("无效的历史记录索引: %d\n", index + 1);
    }
}


// 初始化设置
void InitializeSettings() {
    LoadSettingsFromFlash(&current_settings);
    LoadHistoryIndexFromFlash();  // 加载历史数据
    // 如果读取到无效的设置，可以设置默认值
    if (current_settings.buzzer_enabled != 0 && current_settings.buzzer_enabled != 1) {
        current_settings.buzzer_enabled = 1;  // 默认值
    }
    if (current_settings.current_unit >= 10) {
        current_settings.current_unit = 0;  // 默认值
    }
    if (current_settings.sensor_count != 0 && current_settings.sensor_count != 1) {
        current_settings.sensor_count = 0;  // 默认值 4T
    }
    if (current_settings.auto_shutdown_enabled != 0 && current_settings.auto_shutdown_enabled != 1) {
        current_settings.auto_shutdown_enabled = 0;  // 默认值 ON  开启自动关机
    }
}
#if 1
 int power_on = 0;
    static int backlight_on = 0;
// 处理按键0事件
void Handle_Key0_Event(KEY_EventList_TypeDef event) {    
    MinAuto = 0; SecondAuto = 0; Timing_Switch_5min = 0;
  
    switch (event) {
       
        case KEY_Event_SingleClick:
        if(lock_flag == 0){ 
            if (current_settings.buzzer_enabled) {
                Key_Beep();  // 按键声音持续100ms
            }
            backlight_on = !backlight_on;
            if (!backlight_on){
                GPIO_SetBits(GPIOB, GPIO_Pin_3);  // 背光开
                UpdateReadModifyWriteDisplay(15, Screen_Data_LED, 1);
            } else {
                GPIO_ResetBits(GPIOB, GPIO_Pin_3);  // 背光关
                UpdateReadModifyWriteDisplay(15, Screen_Data_LED, 0);
            }
        }        
            break;
    
        case KEY_Event_LongPress: 
         if (current_settings.buzzer_enabled) {
                Key_Beep();  // 按键声音持续100ms
            }           
            power_on = !power_on;
            if (power_on) {
                GPIO_SetBits(GPIOA, GPIO_Pin_4);  // 电源开
                GPIO_SetBits(GPIOB, GPIO_Pin_3);  // 背光开
                UpdateReadModifyWriteDisplay(15, Screen_Data_LED, 1);
            } else {
                cleandisp();//清屏，一些功能可能不能设置清屏，目前是调试用
                GPIO_ResetBits(GPIOB, GPIO_Pin_3);  // 背光关				              
                GPIO_ResetBits(GPIOA, GPIO_Pin_4);  // 关机电源
							
            }
            break;
        default:
            break;
        }
    

}
#endif


// 处理按键1事件   
void Handle_Key1_Event(KEY_EventList_TypeDef event) {
    if(lock_flag == 0){
    MinAuto = 0; SecondAuto = 0; Timing_Switch_5min = 0; // 自动关机重新计时
    if (current_settings.buzzer_enabled) {
        Key_Beep();  // 按键声音持续100ms
    }
    printf("按键1事件: %d, settings_mode: %d, setting_item: %d\n", event, settings_mode, setting_item);
    switch (event) {
        case KEY_Event_SingleClick:				
        UpdateReadModifyWriteDisplay(11, Screen_Data_MAX + Screen_Data_MIN + Screen_Data_DifferValue, 0); // 刷新
            if (settings_mode) {
                // 设置模式下按键1用于向上翻动
                if (setting_item == SETTING_UNIT) {
                    current_settings.current_unit = (current_settings.current_unit - 1 + 10) % 10;
                    SettingsUint_display();
                    printf("当前单位: %d\r\n", current_settings.current_unit);
                } else if (setting_item == SETTING_SENSOR_COUNT) {
                    current_settings.sensor_count = (current_settings.sensor_count - 1 + 2) % 2;
					Switching2T4T_display();
                    printf("当前传感器数量: %d\r\n", current_settings.sensor_count == 0 ? 2 : 4);
                }else if (setting_item == SETTING_AUTO_SHUTDOWN) {  // 处理自动关机设置项
                    current_settings.auto_shutdown_enabled = (current_settings.auto_shutdown_enabled - 1 + 2) % 2;
                    AUutoshutdownONOFF_display();
                    printf("自动关机功能: %s\r\n", current_settings.auto_shutdown_enabled ? "开启" : "关闭");
                    printf("自动关机功能当前选择为: %d\n",current_settings.auto_shutdown_enabled);
                }
            } else if (current_history_display != -1) {
                if (total_records > 0) {  //增加历史记录数量检查
                ClearDigitalTubeDisplay();//刷新四缸
                ClearMercuryDisplay();

                submode_index = 0;  // 确保从最大值开始显示
                in_submode = 0;
                // 查看历史记录模式
                if (current_history_display > 0) {
                    current_history_display--;
                } else {
                    current_history_display = total_records - 1;
                }
                DisplayHistoryRecord(current_history_display);
                } else {
                //可以加入代码：无记录按下可以加入实现蜂鸣器不发出声音
                //  没有历史记录时的处理
                printf("没有历史记录，无法上翻\n");
                }

            }else{
                current_settings.buzzer_enabled = !current_settings.buzzer_enabled;  // 切换蜂鸣器状态
                //printf("蜂鸣器%s\r\n", current_settings.buzzer_enabled ? "打开" : "关闭");
                if (current_settings.buzzer_enabled) {
                UpdateReadModifyWriteDisplay(15, Screen_Data_BUZZER, 1);
                //delay_ms(100);//看看500ms
                } else {
                UpdateReadModifyWriteDisplay(15, Screen_Data_BUZZER, 0);
                //delay_ms(100);
                }
                SaveCurrentSettings();  // 保存设置
            }
            break;
        //长按功能闲置
        //case KEY_Event_LongPress:
        //    break;
        default:
            break;
        }
    }
}

// 处理按键2事件
void Handle_Key2_Event(KEY_EventList_TypeDef event) {
    if(lock_flag == 0){
    if(settings_mode == 0){
    MinAuto = 0; SecondAuto = 0; Timing_Switch_5min = 0; // 自动关机关背光重新计时
    static int rec_mode = 0;
    if (current_settings.buzzer_enabled) {
        Key_Beep();  // 按键声音持续100ms
    }
    UpdateReadModifyWriteDisplay(11, Screen_Data_MAX + Screen_Data_MIN + Screen_Data_DifferValue, 0); // 刷新
    switch (event) {
        case KEY_Event_SingleClick:
        
            if (in_submode)Clear_Clock_Display();//刷新时钟数码段

            if (current_history_display != -1) {
                if (in_submode) {
                    submode_index = (submode_index + 1) % 3;  // 切换子模式显示内容
                    DisplaySubmodeData(current_history_display);
                } else {
                    // 切换进入子模式
                    Clear_Clock_Display();//刷新原时钟数码段
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
                        //printf("保存数据\r\n");
                        Record new_record;
                        for (int i = 0; i < 4; i++) {
                            new_record.pressure[i] = pressure[i];
                            new_record.ADC_Value[i] = ADC_Value[i];
                        }
                        new_record.Second = Second;
                        new_record.Minute = Minute;
                        new_record.Hour = Hour;
                        new_record.sensor_mode = current_settings.sensor_count; // 保存当前2T还是4T模式
                        SaveHistoryRecordToFlash(history_index, &new_record);  // 使用从 0 开始的索引
                        history_index = (history_index % MAX_HISTORY_RECORDS) + 1;  // 调整索引从1开始并使用循环索引
                        
                        if (total_records < MAX_HISTORY_RECORDS) {
                            total_records++;
                        }
                        printf("保存数据到记录索引: %d\n", history_index % MAX_HISTORY_RECORDS);
                        NumHistoricalData_Display(26, 27, 28, 29, 30, history_index);    // 保存数据到记录索引
                        
                        SaveCurrentHistoryIndexToFlash();  // 保存当前历史记录索引
                        printf("保存数据到记录索引: %d\n", history_index);
                      
                    }
                }
            
            break;
        case KEY_Event_LongPress:
            UpdateReadModifyWriteDisplay(11, Screen_Data_MAX + Screen_Data_MIN + Screen_Data_DifferValue, 0); // 刷新
            rec_mode = 0;
            rec_data = 1;
            if (current_history_display == -1) {
                ClearDigitalTubeDisplay();//刷新四缸
                ClearMercuryDisplay();//刷新四缸
                Clear_Clock_Display();//刷新时钟
                UpdateReadModifyWriteDisplay(15, Screen_Data_2T, 0);   
                UpdateReadModifyWriteDisplay(10, Screen_Data_4T, 0);   
                current_history_display = total_records == 1;  // 从最新的记录开始查看
                UpdateReadModifyWriteDisplay(14, Screen_Data_REC + Screen_Data_R1, 1);
                UpdateReadModifyWriteDisplay(11,Screen_Data_rec , 1);
                printf("查看历史数据\n");
                DisplayHistoryRecord(current_history_display);
            } else {
                // 退出历史记录查看模式
                current_history_display = -1;
                in_submode = 0;
                printf("退出查看历史数据模式\n");
                ClearDigitalTubeDisplay();//刷新四缸
                ClearMercuryDisplay();//刷新四缸
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

// 处理按键3事件 (锁定)
void Handle_Key3_Event(KEY_EventList_TypeDef event) {
    MinAuto = 0; SecondAuto = 0; Timing_Switch_5min = 0; // 自动关机关背光重新计时
    static int data_locked = 0;
    if (current_settings.buzzer_enabled) {
        Key_Beep();  // 按键声音持续100ms
    }
    switch (event) {
        case KEY_Event_SingleClick:
             if (settings_mode) {
                SaveSettings();  // 保存设置并跳转到下一个设置项
                //printf("保存设置并跳转到下一个设置项\n");

             } else {
            data_locked = !data_locked;
            printf("数据%s\r\n", data_locked ? "锁定" : "解锁");
            if (data_locked) {
                UpdateReadModifyWriteDisplay(15, Screen_Data_lock, 1);
                lock_flag = 1;
            } else {
                UpdateReadModifyWriteDisplay(15, Screen_Data_lock, 0);
                lock_flag = 0;
                }
            }
            break;
        //长按闲置
        //case KEY_Event_LongPress:
        //    break;
        default:
            break;
    }
}

// 处理按键4事件
void Handle_Key4_Event(KEY_EventList_TypeDef event) {
    if(lock_flag == 0){
    MinAuto = 0; SecondAuto = 0; Timing_Switch_5min = 0; // 自动关机关背光重新计时
    if (current_settings.buzzer_enabled) {
        Key_Beep();  // 按键声音持续100ms
    }
    switch (event) {
        case KEY_Event_SingleClick:
            UpdateReadModifyWriteDisplay(11, Screen_Data_MAX + Screen_Data_MIN + Screen_Data_DifferValue, 0); // 刷新
            if (settings_mode) {
                // 设置模式下按键4用于向下翻动
                if (setting_item == SETTING_UNIT) {
                    current_settings.current_unit = (current_settings.current_unit + 1 + 10) % 10;
                    SettingsUint_display();
                    //printf("当前单位: %d\r\n", current_settings.current_unit);
                } else if (setting_item == SETTING_SENSOR_COUNT) {
                    current_settings.sensor_count = (current_settings.sensor_count + 1 + 2) % 2;
                    Switching2T4T_display();
                    //printf("当前传感器数量: %d\r\n", current_settings.sensor_count == 0 ? 2 : 4);
                } else if (setting_item == SETTING_AUTO_SHUTDOWN) {  // 新增自动关机设置项的处理
                    current_settings.auto_shutdown_enabled = (current_settings.auto_shutdown_enabled + 1) % 2;
                    AUutoshutdownONOFF_display();
                    printf("自动关机功能: %s\r\n", current_settings.auto_shutdown_enabled ? "开启" : "关闭");
                    printf("自动关机功能当前选择为: %d\n",current_settings.auto_shutdown_enabled);
                }

            } else if (current_history_display != -1) {
                if (total_records > 0) {  //增加历史记录数量检查
                ClearDigitalTubeDisplay();//刷新四缸
                ClearMercuryDisplay();

                submode_index = 0;  // 确保从最大值开始显示
                in_submode = 0;

                // 查看历史记录模式
                current_history_display = (current_history_display + 1) % total_records;
                DisplayHistoryRecord(current_history_display);  
                } else {
                //可以加入代码：无记录按下可以加入实现蜂鸣器不发出声音
                //  没有历史记录时的处理
                printf("没有历史记录，无法上翻\n");
                } 
            }
            break;
        case KEY_Event_LongPress:
        if (current_history_display == -1) {
            settings_mode = 1;  // 进入设置模式
            UpdateReadModifyWriteDisplay(15, Screen_Data_2T, 0);             
            UpdateReadModifyWriteDisplay(10, Screen_Data_4T, 0);
            UpdateReadModifyWriteDisplay(11, Screen_Data_Auto+Screen_Data_on+Screen_Data_off, 0);   
            Clear_Clock_Display();
            ClearMercuryDisplay();  // 清空压力显示数码段和汞柱刷新
            //printf("进入设置模式\r\n");
        }
            break;
        default:
            break;
        }
    }
}
float ADValue_offset[4] = {0, 0, 0, 0};//需要存入flash
int initial_value = 0;  //需要存入flash
int Calibration_offset = 0;//需要存入flash
int ProgressBar = 0;//显示p=0进度条需要用
// 处理按键5事件
void Handle_Key5_Event(KEY_EventList_TypeDef event) {
    if(lock_flag == 0){
	if(settings_mode == 0){
    MinAuto = 0; SecondAuto = 0; Timing_Switch_5min = 0; // 自动关机关背光重新计时
    // if (current_settings.buzzer_enabled) {
    //     Key_Beep();  // 按键声音持续100ms
    // }
    switch (event) {
        case KEY_Event_SingleClick:
        Key_Beep();  // 按键声音持续100ms
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
				Calibration();  // 校准p=0进度条显示
                if(ProgressBar == 10)ProgressBar = 0;
            }

                history_index = 0;total_records = 0;         // 清除历史记录，需要可以加上时间和压力值
                NumHistoricalData_Display(26, 27, 28, 29, 30, history_index);    // 保存数据到记录索引
                Key_Beep();  // 按键声音持续100ms
        if (current_settings.sensor_count == 0) {  //无历史记录时显示      
            ClearDigitalTubeDisplay(); 
            ClearMercuryDisplay();
            Clear_Clock_Display();
            Digital_tube_display(1, 2, 3, 4, 5, 0, 1900);//1号缸
            Digital_tube_display(6, 7, 8, 9, 10, 0, 1900);//2号缸
            Digital_tube_display(11, 12, 13, 14, 15, 0, 1900);//3号缸
            Digital_tube_display(16, 17, 18, 19, 20, 0, 1900);//4号缸                  
        }else{     
            ClearDigitalTubeDisplay(); 
            ClearMercuryDisplay();
            Clear_Clock_Display();
            Digital_tube_display(1, 2, 3, 4, 5,0, 1900);//1号缸
            Digital_tube_display(6, 7, 8, 9, 10,0, 1900);//2号缸             
        }



        }else{             
            uint16_t adc_sum[4] = {0, 0, 0, 0};
            for (int i = 0; i < 10; i++) {
                ADC_GetAverageValues();
                for (int j = 0; j < 4; j++) {
                    adc_sum[j] += ADC_Value[j];
                }
                ProgressBar++;
                Calibration();  // 校准p=0进度条显示  
            }
            for (int i = 0; i < 4; i++) {
                ADValue_offset[i] = adc_sum[i] / 10.0;
            }
				initial_value =1784;
                Key_Beep();  // 按键声音持续100ms
                printf("校准完成: ADC偏移量 = %f, %f, %f, %f;initial_value = %d\n", ADValue_offset[0], ADValue_offset[1], ADValue_offset[2], ADValue_offset[3],initial_value);	
                Calibration_offset = 1;
                ProgressBar = 0;
        }
#if 0 //按下校准归0，再次按下解除校准归0
            Calibration_offset = !Calibration_offset;
            Calibration();  // 校准p=0进度条显示
            if (Calibration_offset) {
                //printf("开始校准\n");

                uint16_t adc_sum[4] = {0, 0, 0, 0};
                for (int i = 0; i < 10; i++) {
                ADC_GetAverageValues();
                for (int j = 0; j < 4; j++) {
                    adc_sum[j] += ADC_Value[j];
                }
                delay_ms(100); // 每次读取间隔200ms，总共读取2秒
            }
            for (int i = 0; i < 4; i++) {
                ADValue_offset[i] = adc_sum[i] / 10.0;
            }
				initial_value =1784;
                Key_Beep();  // 按键声音持续100ms
                printf("校准完成: ADC偏移量 = %f, %f, %f, %f;initial_value = %d\n", ADValue_offset[0], ADValue_offset[1], ADValue_offset[2], ADValue_offset[3],initial_value);	
			}else{
						
				for (int i = 0; i < 4; i++) {
                ADValue_offset[i] = 0;
				initial_value = 0;								
                }
                Key_Beep();  // 按键声音持续100ms
				printf("校准完成: ADC偏移量 = %f, %f, %f, %f;initial_value = %d\n", ADValue_offset[0], ADValue_offset[1], ADValue_offset[2], ADValue_offset[3],initial_value);		
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

// 按键处理函数
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
