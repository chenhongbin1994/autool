#ifndef __KEY_HANDLER_H
#define __KEY_HANDLER_H

#include "key.h"

// 单位和传感器数量的设置选项
typedef enum {
    SETTING_UNIT,
    SETTING_SENSOR_COUNT,
    SETTING_MAX
} SettingItems;

typedef struct {
    int buzzer_enabled;
    int current_unit;
    int sensor_count;
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

#endif
