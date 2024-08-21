#ifndef __KEY_HANDLER_H
#define __KEY_HANDLER_H

#include "key.h"

// ��λ�ʹ���������������ѡ��
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
// �����¼�������
void KeyHandler_Process(void);
// ���������ľ��幦�ܴ�����
void Handle_Key0_Event(KEY_EventList_TypeDef event);
void Handle_Key1_Event(KEY_EventList_TypeDef event);
void Handle_Key2_Event(KEY_EventList_TypeDef event);
void Handle_Key3_Event(KEY_EventList_TypeDef event);
void Handle_Key4_Event(KEY_EventList_TypeDef event);
void Handle_Key5_Event(KEY_EventList_TypeDef event);

#endif
