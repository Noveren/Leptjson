#ifndef LEPTJSON_H_
#define LEPTJSON_H_

// 解析过程种的结果及错误
enum {
    LEPT_PARSE_OK = 0,              // 解析无错误
    LEPT_PARSE_EXPECT_VALUE,
    LEPT_PARSE_INVALID_VALUE,
    LEPT_PARSE_ROOT_NOT_SINGULAR    // 目标字符串后面有非空格非\0的字符
};
// JSON中的六种数据类型（bool --> true,false）共七种
typedef enum {
    LEPT_NULL = 0,      // 值：null
    LEPT_TRUE,          // 值：ture
    LEPT_FALSE,         // 值：false
    LEPT_NUMBER,
    LEPT_STRING,
    LEPT_ARRAY,
    LEPT_OBJECT
} Lept_type;

// JSON解析树的节点的数据类型
typedef struct {
    Lept_type type;             // null, true, false
    // 后续添加
} Lept_value;

int Lept_parse(Lept_value *v, const char* json);
Lept_type Lept_get_type(const Lept_value *v);

#endif