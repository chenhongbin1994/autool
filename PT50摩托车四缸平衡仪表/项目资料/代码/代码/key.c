#include <stdio.h>
#include <stdbool.h>

// 定义按键枚举值
typedef enum {
    KEY_ONE,
    KEY_TWO,
    KEY_THREE,
    KEY_FOUR,
    KEY_FIVE,
    KEY_SIX
} Key;

// 按键状态
typedef enum {
    KEY_STATE_IDLE,
    KEY_STATE_SHORT_PRESS,
    KEY_STATE_LONG_PRESS
} KeyState;

// 按键处理函数
void handle_key_press(Key key, KeyState state) {
    // 根据按键和状态执行相应的操作
    switch (key) {
        case KEY_ONE:
 if (state == KEY_STATE_SHORT_PRESS) {
 // 点按开关背光
 toggle_backlight();
 } else if (state == KEY_STATE_LONG_PRESS) {
 // 进入设置模式
 enter_setting_mode();
 }
 break;
        case KEY_TWO:
 if (state == KEY_STATE_SHORT_PRESS) {
 // 向上翻动
 flip_up();
 } else if (state == KEY_STATE_LONG_PRESS) {
 // 开关声音
 toggle_sound();
 }
 break;
        case KEY_THREE:
 if (state == KEY_STATE_SHORT_PRESS) {
 // 进入REC模式或保存数据
 enter_rec_mode_or_save_data();
 } else if (state == KEY_STATE_LONG_PRESS) {
 // 查看历史数据
 view_history_data();
 }
 break;
        case KEY_FOUR:
 if (state == KEY_STATE_SHORT_PRESS) {
 // 锁定或解锁数据
 toggle_data_lock();
 } else if (state == KEY_STATE_LONG_PRESS) {
 // 双击锁定四缸
 double_click_lock_four_cylinder();
 }
 break;
        case KEY_FIVE:
 if (state == KEY_STATE_SHORT_PRESS) {
 // 向下翻动
 flip_down();
 } else if (state == KEY_STATE_LONG_PRESS) {
 // 开关机
 toggle_power();
 }
 break;
        case KEY_SIX:
 if (state == KEY_STATE_LONG_PRESS) {
 // 设置 P=0
 set_p_zero();
 }
 break;
        default:
 break;
    }
}

int main() {
    // 主循环中检测按键状态并调用处理函数
    while (true) {
        // 检测按键状态并获取按键和状态
        Key key = detect_key_press();
        KeyState state = get_key_state(key);
        
        // 处理按键事件
        handle_key_press(key, state);
    }

    return 0;
}
