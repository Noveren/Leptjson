#include "testFrame.h"

#include "leptjson.h"

static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

#define TEST_ERROR(error, json)\
    do {\
        Lept_value v = {.type = LEPT_FALSE};\
        EXPECT_EQ_INT(error, Lept_parse(&v, json));\
        EXPECT_EQ_INT(LEPT_NULL, Lept_get_type(&v));\
    } while(0)

void test_parse_null(void)
{
    Lept_value v = {LEPT_TRUE};     // 暂时初始化为 true，判断后续解析是否能够更新
    EXPECT_EQ_INT(LEPT_PARSE_OK, Lept_parse(&v, "null"));
    EXPECT_EQ_INT(LEPT_NULL, Lept_get_type(&v));
}

void test_parse_true(void)
{
    Lept_value v = {LEPT_FALSE};
    EXPECT_EQ_INT(LEPT_PARSE_OK, Lept_parse(&v, "true"));
    EXPECT_EQ_INT(LEPT_TRUE, Lept_get_type(&v));
}

void test_parse_false(void)
{
    Lept_value v = {LEPT_TRUE};
    EXPECT_EQ_INT(LEPT_PARSE_OK, Lept_parse(&v, "false"));
    EXPECT_EQ_INT(LEPT_FALSE, Lept_get_type(&v));
}

void test_parse_expect_value(void)
{
    TEST_ERROR(LEPT_PARSE_EXPECT_VALUE, "      ");
    TEST_ERROR(LEPT_PARSE_EXPECT_VALUE, "");
}

void test_parse_invalid_value(void)
{
    TEST_ERROR(LEPT_PARSE_INVALID_VALUE, "Null");
    TEST_ERROR(LEPT_PARSE_INVALID_VALUE, "nul");

}

void test_parse_root_not_singular(void)
{
    // 目标字符串后面有非空格非\0的字符
    TEST_ERROR(LEPT_PARSE_ROOT_NOT_SINGULAR, "null N");
    TEST_ERROR(LEPT_PARSE_ROOT_NOT_SINGULAR, "nulll");
}

void test(void)
{
    // 测试对 null 的解析
    test_parse_null();
    test_parse_true();
    test_parse_false();
    test_parse_expect_value();
    test_parse_invalid_value();
    test_parse_root_not_singular();
}

int main(void)
{
    test();
    EXPECT_EQ_RESULT();
    return 0;
}