/*
 * @Author: ChenHongBin 944278386@qq.com
 * @Date: 2024-07-25 20:33:41
 * @LastEditors: ChenHongBin chenhongbin@cnautool.com
 * @LastEditTime: 2024-08-20 17:14:38
 * @FilePath: \Projectc:\Users\IBM\Desktop\PT50_stmf103MAXMIN\MyCode\Middleware\key_handler.h
 * @Description: ����Ĭ������,������`customMade`, ��koroFileHeader�鿴���� ��������: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __KEY_HANDLER_H
#define __KEY_HANDLER_H

#include "key.h"



// ��λ�ʹ���������������ѡ��
typedef enum {
    SETTING_UNIT,
    SETTING_SENSOR_COUNT,     //����������
    SETTING_STROKE2T4T_MODE,       // 2��̻�4���ģʽ������
    SETTING_AUTO_SHUTDOWN,    // �Զ��ػ�������
    SETTING_MAX
} SettingItems;

typedef struct {
    int buzzer_enabled;   // ����������
    int current_unit;     // ��ǰ��λ
    int sensor_count;     // ������������0: 2T, 1: 4T��ÿ�������»������Ǵ�0��ʼ���������Խ������int sensor_count = 3;
    int stroke2T4T_mode;      // 0��ʾ2��̣�1��ʾ4���
    int auto_shutdown_enabled;   // �Ƿ����ػ����ܣ�0: �ر�, 1: ������
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

extern  int power_on;
extern u32 P_0_cnt;
extern int settings_mode;
extern u8 Zero_flag, lock_flag, longocked_flag, Switch_flag, REC_flag;  // ����һЩȫ�ֱ���
extern Settings current_settings;  // ��ǰ����
#endif
