// 用于单元测试的相关函数
#define FLOAT_PRECISION 0.00005
// #define DOUBLE_PRECISION 0.000000000000001
#define STRING_MAX_LENGTH 200

int compare_float(float a, float b)
{
    float diff = a - b;
    if (diff <= FLOAT_PRECISION && (-diff) <= FLOAT_PRECISION) {
        return 1;
    } else {
        return 0;
    }
}

// int compare_double(double a, double b)
// {
//     double diff = a - b;
//     if (diff <= DOUBLE_PRECISION && (-diff) <= DOUBLE_PRECISION) {
//         return 1;
//     } else {
//         return 0;
//     }
// }

int compare_string(const char str1[], const char str2[])
{
    int i = 0;
    while (str1[i] == str2[i] && str1[i] != '\0' && str2[i] != '\0' && i < STRING_MAX_LENGTH) {
        ++i;
    }
    if (str1[i] == str2[i]) {
        return 1;
    } else {
        return 0;
    }
}

// 机械键盘用起来还可以，就是没有ThinkPad 好用