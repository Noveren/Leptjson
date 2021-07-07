#ifndef TESTFRAME_H_
#define TESTFRAME_H_

#include <stdio.h>

// 用于单元测试的相关函数及宏定义
// 使用该头文件中的宏函数前，请定义如下三个全局变量
// 单元测试主函数的返回值：static int main_ret = 0;
// 单元测试进行的个数：static int test_count = 0;
// 单元测试通过的个数：static int test_pass = 0;

int compare_float(float a, float b);
// int compare_double(double a, double b);
int compare_string(const char str1[], const char str2[]);


/**
 * @name: EXPECT_EQ_BASE
 * @brief: 测试核心宏函数，传入比较结果，期待值，实际值，格式化字符("%d" 等)
 */
#define EXPECT_EQ_BASE(equality, expect, actual, format)\
    do {\
        ++test_count;\
        if (equality == 1) {\
            ++test_pass;\
        } else {\
            printf("%s=> %s:%d : expect: " format " actual: " format "\n", __FILE__, __func__, __LINE__, expect, actual);\
            main_ret = 1;\
        }\
    } while(0)
#define EXPECT_EQ_RESULT()\
    do {\
        printf("Result: %d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);\
    } while(0)
// 具体类型，调用EXPECT_EQ_BASE
#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect == actual), expect, actual, "%d")
#define EXPECT_EQ_FLOAT(expect, actual) EXPECT_EQ_BASE(compare_float(expect, actual), expect, actual, "%.5f")
// #define EXPECT_EQ_DOUBLE(expect, actual) EXPECT_EQ_BASE(compare_double(expect, actual), expect, actual, "%.15f")
#define EXPECT_EQ_STRING(expect, actual) EXPECT_EQ_BASE(compare_string(expect, actual), expect, actual, "%s")
#endif