/**
 * @brief 从HT1621控制器读取数据
 * @param addr - [in] 要读取的地址
 * @param bits - [in] 数据位数（4位或8位）
 * @return 读取到的数据
 */
uint8_t HT1621_ReadData(uint8_t addr, uint8_t bits) {
    // 这里模拟一个读取数据的过程，实际上并不会从HT1621控制器中读取数据
    // 你需要根据你的具体情况实现读取外部数据的方法
    
    // 假设读取的数据为固定值，例如 0xAA
    return 0xAA;
}
