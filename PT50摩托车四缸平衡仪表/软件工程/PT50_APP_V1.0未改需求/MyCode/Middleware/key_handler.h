/*
 * @Author: ChenHongBin 944278386@qq.com
 * @Date: 2024-07-25 20:33:41
 * @LastEditors: ChenHongBin chenhongbin@cnautool.com
 * @LastEditTime: 2024-08-12 19:14:48
 * @FilePath: \Projectc:\Users\IBM\Desktop\PT50_stmf103MAXMIN\MyCode\Middleware\key_handler.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __KEY_HANDLER_H
#define __KEY_HANDLER_H

#include "key.h"

// 单位和传感器数量的设置选项
typedef enum {
    SETTING_UNIT,
    SETTING_SENSOR_COUNT,
    SETTING_AUTO_SHUTDOWN,    // 自动关机设置项
    SETTING_MAX
} SettingItems;

typedef struct {
    int buzzer_enabled;   // 蜂鸣器开关
    int current_unit;     // 当前单位
    int sensor_count;     // 传感器数量（0: 2T, 1: 4T）
    int auto_shutdown_enabled;   // 是否开启关机功能（0: 关闭, 1: 开启）
} Settings;
void InitializeSettings();

// 按键事件处理函数
void KeyHandler_Process(void);
// 各个按键的具体功能处理函数
void Handle_Key0_Event(KEY_EventList_TypeDef event);
void Handle_Key1_Event(KEY_EventList_TypeDef event);
void Handle_Key2_Event(KEY_EventList_TypeDef event);
void Handle_Key3_Event(KEY_EventList_TypeDef event);
void Handle_Key4_Event(KEY_EventList_TypeDef event);
void Handle_Key5_Event(KEY_EventList_TypeDef event);

extern  int power_on;
extern u32 P_0_cnt;
extern int settings_mode;
extern u8 Zero_flag, lock_flag, longocked_flag, Switch_flag, REC_flag;  // 定义一些全局变量
extern Settings current_settings;  // 当前设置
#endif
