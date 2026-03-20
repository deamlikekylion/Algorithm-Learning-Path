// 禁用VS2022的CRT安全警告（解决strcpy/sprintf等函数的C4996报错）
#define _CRT_SECURE_NO_WARNINGS
// 引入标准输入输出头文件（printf/scanf等函数）
#include <stdio.h>
// 引入字符串操作头文件（strcpy等函数）
#include <string.h>

// ==================== 实验常量宏定义（核心配置） ====================
#define N 5       // 学生总数：实验设定5个学生
#define N1 2      // 前2个学生采用「逐字节压缩」方式（验证字节级内存操作）
#define N2 3      // 后3个学生采用「整体压缩」方式（验证数据类型整体存储）
// 单个学生结构体的理论字节数：8(name)+2(age)+4(score)+200(remark) = 214
// 注：VS默认内存对齐下实际占216字节，实验中强制按理论值逐字节操作，忽略对齐填充
#define student_size 214  

// ==================== 学生结构体定义（实验核心数据结构） ====================
// 定义学生结构体，模拟实际业务数据，用于验证「数据在内存中的表示与压缩解压」
struct student {
    char name[8];    // 姓名：字符数组，固定8字节（不足补'\0'，超出截断）
    short age;       // 年龄：短整型，2字节（范围-32768~32767）
    float score;     // 分数：单精度浮点型，4字节（IEEE754标准存储）
    char remark[200];// 备注：字符数组，固定200字节
};

// ==================== 任务1：数据压缩与解压函数（核心实验任务） ====================
/**
 * @brief 逐字节压缩学生数据（实验核心：验证字节级内存操作）
 * @param s      待压缩的学生结构体数组指针
 * @param sno    需要压缩的学生人数
 * @param buf    存储压缩数据的缓冲区指针（输出参数）
 * @return       压缩后的数据总字节数
 * @原理         逐个成员、逐字节读取结构体数据，写入缓冲区，无内存对齐填充
 */
int pack_student_bytebybyte(struct student* s, int sno, char* buf) {
    int total_len = 0;  // 记录压缩数据的总长度，初始化为0
    // 遍历每个需要压缩的学生
    for (int i = 0; i < sno; i++) {
        // 1. 逐字节写入姓名（8字节）：char类型本身1字节，直接遍历赋值
        for (int j = 0; j < 8; j++) {
            buf[total_len++] = s[i].name[j];  // 写入1字节后，总长度+1
        }
        // 2. 逐字节写入age（short类型，2字节）：通过char指针拆解短整型
        char* p_age = (char*)&s[i].age;  // 把short类型地址转为char指针（按字节访问）
        buf[total_len++] = *p_age;       // 写入age的低字节（小端序：低地址存低字节）
        buf[total_len++] = *(p_age + 1); // 写入age的高字节
        // 3. 逐字节写入score（float类型，4字节）：通过char指针拆解浮点型
        char* p_score = (char*)&s[i].score; // 把float地址转为char指针
        buf[total_len++] = *p_score;       // 第1字节（低字节）
        buf[total_len++] = *(p_score + 1); // 第2字节
        buf[total_len++] = *(p_score + 2); // 第3字节
        buf[total_len++] = *(p_score + 3); // 第4字节（高字节）
        // 4. 逐字节写入备注（200字节）：同姓名逻辑
        for (int j = 0; j < 200; j++) {
            buf[total_len++] = s[i].remark[j];
        }
    }
    return total_len; // 返回总压缩长度，用于后续解压
}

/**
 * @brief 整体写入压缩学生数据（对比实验：验证数据类型整体存储）
 * @param s      待压缩的学生结构体数组指针
 * @param sno    需要压缩的学生人数
 * @param buf    存储压缩数据的缓冲区指针（输出参数）
 * @return       压缩后的数据总字节数
 * @原理         按数据类型整体写入缓冲区，效率更高，与逐字节压缩结果一致
 */
int pack_student_whole(struct student* s, int sno, char* buf) {
    int total_len = 0;  // 记录压缩数据的总长度
    // 遍历每个需要压缩的学生
    for (int i = 0; i < sno; i++) {
        // 1. 姓名整体写入：strcpy直接拷贝8字节（含'\0'）
        strcpy(buf + total_len, s[i].name);
        total_len += 8; // 总长度+8
        // 2. age整体写入：把缓冲区对应位置转为short指针，直接赋值
        *(short*)(buf + total_len) = s[i].age;
        total_len += 2; // 总长度+2
        // 3. score整体写入：把缓冲区对应位置转为float指针，直接赋值
        *(float*)(buf + total_len) = s[i].score;
        total_len += 4; // 总长度+4
        // 4. 备注整体写入：strcpy直接拷贝200字节
        strcpy(buf + total_len, s[i].remark);
        total_len += 200; // 总长度+200
    }
    return total_len;
}

/**
 * @brief 解压压缩数据（还原为学生结构体）
 * @param buf     存储压缩数据的缓冲区指针
 * @param len     压缩数据的总长度（由压缩函数返回）
 * @param s       存储解压后数据的学生结构体数组指针（输出参数）
 * @return        解压出的学生人数
 * @原理         按压缩的逆流程，逐字节/整体读取缓冲区数据，还原为结构体成员
 */
int restore_student(char* buf, int len, struct student* s) {
    int count = 0;  // 记录解压出的学生人数
    int pos = 0;    // 记录当前读取缓冲区的位置，初始化为0
    // 循环读取缓冲区，直到读完所有数据
    while (pos < len) {
        // 1. 读取姓名（8字节）：逐字节写入结构体
        for (int j = 0; j < 8; j++) {
            s[count].name[j] = buf[pos++]; // 读取1字节后，位置+1
        }
        // 2. 读取age（2字节）：把缓冲区位置转为short指针，直接赋值
        s[count].age = *(short*)(buf + pos);
        pos += 2; // 位置+2
        // 3. 读取score（4字节）：把缓冲区位置转为float指针，直接赋值
        s[count].score = *(float*)(buf + pos);
        pos += 4; // 位置+4
        // 4. 读取备注（200字节）：逐字节写入结构体
        for (int j = 0; j < 200; j++) {
            s[count].remark[j] = buf[pos++];
        }
        count++; // 解压完1个学生，人数+1
    }
    return count; // 返回解压人数，用于验证是否全部还原
}

// ==================== 任务2：位运算等效函数（核心实验任务） ====================
/**
 * @brief 位运算实现绝对值（无if/else，仅用位运算）
 * @param x  输入整数
 * @return   x的绝对值
 * @原理     利用补码特性：负数的掩码是全1（-1），正数掩码是0
 *           (x ^ mask) - mask：负数时等价于 ~x + 1（取反加1），正数时等价于x
 */
int absVal(int x) {
    int mask = x >> 31;  // 右移31位：正数mask=0，负数mask=-1（补码全1）
    return (x ^ mask) - mask;
}
// 标准绝对值函数（对比验证）
int absVal_standard(int x) { return x < 0 ? -x : x; }

/**
 * @brief 位运算实现相反数（无负号-，仅用位运算）
 * @param x  输入整数
 * @return   -x（x的相反数）
 * @原理     补码规则：相反数 = 按位取反 + 1（~x + 1）
 */
int negate(int x) { return ~x + 1; }
// 标准相反数函数（对比验证）
int negate_standard(int x) { return -x; }

/**
 * @brief 仅用~和|实现位与（&）运算（德摩根定律）
 * @param x  输入整数1
 * @param y  输入整数2
 * @return   x & y的结果
 * @原理     德摩根定律：x & y = ~(~x | ~y)
 */
int bitAnd(int x, int y) { return ~(~x | ~y); }
// 标准位与函数（对比验证）
int bitAnd_standard(int x, int y) { return x & y; }

/**
 * @brief 仅用~和&实现位或（|）运算（德摩根定律）
 * @param x  输入整数1
 * @param y  输入整数2
 * @return   x | y的结果
 * @原理     德摩根定律：x | y = ~(~x & ~y)
 */
int bitOr(int x, int y) { return ~(~x & ~y); }
// 标准位或函数（对比验证）
int bitOr_standard(int x, int y) { return x | y; }

/**
 * @brief 仅用~和&实现异或（^）运算
 * @param x  输入整数1
 * @param y  输入整数2
 * @return   x ^ y的结果
 * @原理     异或 = (x | y) & ~(x & y)，结合德摩根定律转换为仅用~和&
 */
int bitXor(int x, int y) { return ~(~x & ~y) & ~(x & y); }
// 标准异或函数（对比验证）
int bitXor_standard(int x, int y) { return x ^ y; }

/**
 * @brief 判断是否为32位有符号整数最大值（0x7FFFFFFF）
 * @param x  输入整数
 * @return   1（是）/0（否）
 * @原理     1. (x+1) ^ ~x == 0：仅x=0x7FFFFFFF或x=-1时成立
 *           2. !!(x ^ ~0)：排除x=-1的情况（~0=-1）
 */
int isTmax(int x) { return !((x + 1) ^ ~x) & !!(x ^ ~0); }
// 标准判断函数（对比验证）
int isTmax_standard(int x) { return x == 0x7FFFFFFF; }

/**
 * @brief 位运算统计二进制中1的个数（分治法）
 * @param x  输入整数
 * @return   x的二进制中1的个数
 * @原理     分治法：先统计每2位的1的个数，再统计每4位，直到32位
 */
int bitCount(int x) {
    // 每2位分组，统计每组1的个数
    int cnt = (x & 0x55555555) + ((x >> 1) & 0x55555555);
    // 每4位分组，统计每组1的个数
    cnt = (cnt & 0x33333333) + ((cnt >> 2) & 0x33333333);
    // 每8位分组，统计每组1的个数
    cnt = (cnt & 0x0F0F0F0F) + ((cnt >> 4) & 0x0F0F0F0F);
    // 每16位分组，统计每组1的个数
    cnt = (cnt & 0x00FF00FF) + ((cnt >> 8) & 0x00FF00FF);
    // 每32位分组，统计总个数
    cnt = (cnt & 0x0000FFFF) + ((cnt >> 16) & 0x0000FFFF);
    return cnt;
}
// 标准统计函数（对比验证）
int bitCount_standard(int x) {
    int cnt = 0;
    while (x) { cnt++; x &= x - 1; } // 每次消去最右侧的1
    return cnt;
}

/**
 * @brief 生成位掩码（highbit到lowbit位为1，其余为0）
 * @param highbit  高位位置（0~31）
 * @param lowbit   低位位置（0~31）
 * @return         对应的位掩码
 * @原理         (全1 << lowbit) ^ (全1 << (highbit+1))，强制转为无符号避免未定义行为
 */
int bitMask(int highbit, int lowbit) {
    return (((unsigned int)~0 << lowbit) ^ ((unsigned int)~0 << (highbit + 1)));
}

/**
 * @brief 判断两个整数相加是否溢出
 * @param x  加数1
 * @param y  加数2
 * @return   1（溢出）/0（未溢出）
 * @原理     同号相加，结果符号与加数不同则溢出
 */
int addOK(int x, int y) {
    int sum = x + y;
    // 获取符号位：右移31位，正数为0，负数为-1
    int sign_x = x >> 31, sign_y = y >> 31, sign_sum = sum >> 31;
    // 同号且结果符号不同 → 溢出，返回1；否则返回0
    return !!(sign_x == sign_y && sign_x != sign_sum);
}

/**
 * @brief 交换整数中指定字节的位置
 * @param x  输入整数
 * @param n  待交换的字节位置1（0~3，0为最低字节）
 * @param m  待交换的字节位置2（0~3，0为最低字节）
 * @return   交换后的整数
 * @原理     1. 提取n和m位置的字节 2. 清空原位置字节 3. 写入交换后的字节
 */
int byteSwap(int x, int n, int m) {
    // 提取n位置的字节（&0xFF确保只保留1字节）
    int bn = (x >> (n << 3)) & 0xFF;
    // 提取m位置的字节
    int bm = (x >> (m << 3)) & 0xFF;
    // 清空n和m位置的字节（~0xFF<<(n<<3)生成掩码，与运算清空）
    x &= ~(0xFF << (n << 3)) & ~(0xFF << (m << 3));
    // 写入交换后的字节
    x |= (bn << (m << 3)) | (bm << (n << 3));
    return x;
}

/**
 * @brief 位运算实现逻辑非（!）
 * @param x  输入整数
 * @return   1（x=0）/0（x≠0）
 * @原理     (x | ~x + 1) >>31：x≠0时为-1，x=0时为0；+1后得到逻辑非结果
 */
int bang(int x) { return ((x | (~x + 1)) >> 31) + 1; }

/**
 * @brief 二进制1的奇偶校验（统计1的个数是奇数/偶数）
 * @param x  输入整数
 * @return   1（奇数个1）/0（偶数个1）
 * @原理     位折叠：逐次异或，最终结果的最低位即为奇偶性
 */
int bitParity(int x) {
    x ^= x >> 16; // 高16位与低16位异或
    x ^= x >> 8;  // 高8位与低8位异或
    x ^= x >> 4;  // 高4位与低4位异或
    x ^= x >> 2;  // 高2位与低2位异或
    x ^= x >> 1;  // 高1位与低1位异或
    return x & 1; // 取最低位，1=奇数，0=偶数
}

// ==================== 工具函数（辅助验证实验结果） ====================
/**
 * @brief 打印学生结构体数组信息（验证压缩解压是否一致）
 * @param s  学生结构体数组指针
 * @param n  需要打印的学生人数
 */
void print_student(struct student* s, int n) {
    for (int i = 0; i < n; i++) {
        printf("第%d个学生：姓名=%s，年龄=%d，分数=%.2f，备注=%s\n",
            i, s[i].name, s[i].age, s[i].score, s[i].remark);
    }
}

/**
 * @brief 打印缓冲区前40字节的十六进制（验证压缩数据的内存布局）
 * @param buf  缓冲区指针
 * @param len  缓冲区数据长度
 */
void print_buf_hex(char* buf, int len) {
    printf("缓冲区前40字节十六进制：\n");
    // 最多打印前40字节，避免输出过长
    for (int i = 0; i < (len < 40 ? len : 40); i++) {
        // 以十六进制打印，%02X表示补零到2位，unsigned char避免负数显示异常
        printf("%02X ", (unsigned char)buf[i]);
        // 每8字节换行，方便查看
        if ((i + 1) % 8 == 0) printf("\n");
    }
    printf("\n");
}

/**
 * @brief 测试位运算函数（对比自定义位运算与标准函数的结果）
 */
void test_bit_op() {
    printf("\n==================== 任务2：位运算测试 ====================\n");
    int x = -123, y = 456; // 测试用例：包含正负整数
    // 逐一测试位运算函数，对比自定义实现与标准实现的结果
    printf("absVal(%d)：自定义=%d，标准=%d\n", x, absVal(x), absVal_standard(x));
    printf("negate(%d)：自定义=%d，标准=%d\n", x, negate(x), negate_standard(x));
    printf("bitAnd(%d,%d)：自定义=%d，标准=%d\n", x, y, bitAnd(x, y), bitAnd_standard(x, y));
    printf("bitOr(%d,%d)：自定义=%d，标准=%d\n", x, y, bitOr(x, y), bitOr_standard(x, y));
    printf("bitXor(%d,%d)：自定义=%d，标准=%d\n", x, y, bitXor(x, y), bitXor_standard(x, y));
    printf("isTmax(0x7FFFFFFF)：%d\n", isTmax(0x7FFFFFFF));
    printf("bitCount(%d)：自定义=%d，标准=%d\n", x, bitCount(x), bitCount_standard(x));
    printf("bitMask(5,3)：0x%X\n", bitMask(5, 3));
    printf("addOK(0x7FFFFFFF,1)：%d\n", addOK(0x7FFFFFFF, 1));
    printf("byteSwap(0x12345678,1,3)：0x%X\n", byteSwap(0x12345678, 1, 3));
    printf("bang(0)：%d，bang(5)：%d\n", bang(0), bang(5));
    printf("bitParity(5)：%d，bitParity(7)：%d\n", bitParity(5), bitParity(7));
}

// ==================== 主函数（实验流程入口） ====================
int main() {
    // 1. 定义变量：压缩前/解压后的学生数组、压缩缓冲区
    struct student beforecompress[N]={0}; // 压缩前的学生数组，初始化为0
    struct student decompress[N]={0};     // 解压后的学生数组，初始化为0
    char message[student_size*N]={0};     // 压缩缓冲区，大小=单个学生字节数×总人数
    int total_pack_len = 0;               // 压缩数据总长度，初始化为0

    // 2. 初始化第一个学生（个性化信息：姓名、年龄、学号最后两位分数）
    strcpy(beforecompress[0].name,"KuangYu");
    beforecompress[0].age=20;                 
    beforecompress[0].score=12.0f;            
    strcpy(beforecompress[0].remark,"Great");

    // 3. 初始化剩余4个学生（自动生成，方便测试）
    for (int i = 1; i < N; i++) {
        strcpy(beforecompress[i].name, "Student"); // 姓名：Student1~Student4
        beforecompress[i].age = 20 + i;                  // 年龄：21~24
        beforecompress[i].score = 80.0f + i;             // 分数：81~84
        sprintf(beforecompress[i].remark, "Remark%d", i); // 备注：Remark1~Remark4
    }

    // 4. 执行压缩：前2个学生逐字节压缩，后3个学生整体压缩
    total_pack_len += pack_student_bytebybyte(beforecompress, N1, message);
    total_pack_len += pack_student_whole(beforecompress + N1, N2, message + total_pack_len);

    // 5. 打印缓冲区前40字节十六进制（验证压缩数据的内存布局）
    print_buf_hex(message, total_pack_len);

    // 6. 执行解压：将压缩数据还原为学生结构体
    int restore_num = restore_student(message, total_pack_len, decompress);

    // 7. 打印压缩前/后的数据（验证是否一致）
    printf("\n==================== 压缩前数据 ====================\n");
    print_student(beforecompress, N);
    printf("\n==================== 解压后数据 ====================\n");
    print_student(decompress, restore_num);
    // 打印压缩长度（验证是否等于理论值：5×214=1070）
    printf("\n压缩前总长度：%d字节，压缩后总长度：%d字节\n", N*student_size, total_pack_len);

    // 8. 测试位运算函数（验证自定义位运算的正确性）
    test_bit_op();

    return 0;
}