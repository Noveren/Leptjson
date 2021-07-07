#include "leptjson.h"
// #define NDEBUG
#include <assert.h>

#ifndef NULL
#define NULL (void *)0
#endif

// 内部结构体，用于减少内部解析函数间所传递的参数
typedef struct {
    const char *jsonPos;       // 记录传入JSON字符串目前所解析的位置
} Lept_context;

// 断言当前解析位置的字符，防止分支对应错误；将解析位置向后移动一个字符
#define EXPECT(Lept_context_ptr, expectChar)\
    do {\
        assert(*(Lept_context_ptr->jsonPos) == (expectChar));\
        ++(Lept_context_ptr->jsonPos);\
    } while(0)

/**
 * @name: lept_parse_whitespace
 * @brief: 预先解析空白部分，将当次解析的位置移动到第一个非空字符前
 * @marks: JOSN的空白的定义：ws 
 */
static void lept_parse_whitespace(Lept_context *c)
{
    const char *ptr = c->jsonPos;       // 我觉的作者可能是懒采写这一步的
    /* ws = *(%x20 / %x09 / %x0A / %x0D) */
    while (*ptr == ' ' || *ptr == '\t' || *ptr == '\n' || *ptr == '\r') {
        ++ptr;
    }
    c->jsonPos = ptr;                   // 到达第一个非空字符位置
}


// static int lept_parse_null(Lept_context *c, Lept_value *v)
// {
//     EXPECT(c, 'n');                     // 防止switch分支设置错误，位置前进
//     if (c->jsonPos[0] != 'u' || c->jsonPos[1] != 'l' || c->jsonPos[2] != 'l') {
//         return LEPT_PARSE_INVALID_VALUE;
//     } else {
//         c->jsonPos += 3;
//         v->type = LEPT_NULL;
//         return LEPT_PARSE_OK;
//     }
// }
// static int lept_parse_true(Lept_context *c, Lept_value *v)
// {
//     EXPECT(c, 't');                     // 防止switch分支设置错误，位置前进
//     if (c->jsonPos[0] != 'r' || c->jsonPos[1] != 'u' || c->jsonPos[2] != 'e') {
//         return LEPT_PARSE_INVALID_VALUE;
//     } else {
//         c->jsonPos += 3;
//         v->type = LEPT_TRUE;
//         return LEPT_PARSE_OK;
//     }
// }
// static int lept_parse_false(Lept_context *c, Lept_value *v)
// {
//     EXPECT(c, 'f');                     // 防止switch分支设置错误，位置前进
//     if (c->jsonPos[0] != 'a' || c->jsonPos[1] != 'l' || c->jsonPos[2] != 's' || c->jsonPos[3] != 'e') {
//         return LEPT_PARSE_INVALID_VALUE;
//     } else {
//         c->jsonPos += 4;
//         v->type = LEPT_FALSE;
//         return LEPT_PARSE_OK;
//     }
// }
static int lept_parse_literal(Lept_context *c, Lept_value *v, const char literal[], Lept_type type)
{
    EXPECT(c, literal[0]);
    int i;
    for (i=0; literal[1+i] != '\0'; ++i) {
        if (c->jsonPos[i] != literal[1+i]) {
            return LEPT_PARSE_INVALID_VALUE;
        }
    }
    c->jsonPos += i;
    v->type = type;
    return LEPT_PARSE_OK;
}

/**
 * @name: lept_parse_value
 * @brief: 内部函数，
 */
static int lept_parse_value(Lept_context *c, Lept_value *v)
{   
    // 由于 null false true 即为字面值，通过非空白的第一个字符进行分支
    switch (*(c->jsonPos)) {
    case 'n':
        return lept_parse_literal(c, v, "null", LEPT_NULL);
    case 't':
        return lept_parse_literal(c, v, "true", LEPT_TRUE);
    case 'f':
        return lept_parse_literal(c, v, "false", LEPT_FALSE);
    case '\0':
        return LEPT_PARSE_EXPECT_VALUE;
    default:
        return LEPT_PARSE_INVALID_VALUE;
    }
}



/**
 * @name: Lept_parse
 * @brief: 解析函数，解析json字符串，并将结果保存到节点的值中
 * @ret: 解析成功，返回 OK，失败，按情况返回，同时将节点类型设置为 LEPT_NULL
 */
int Lept_parse(Lept_value *v, const char* json)
{
    assert(v != NULL);              // 确保传入的节点已分配内存
    
    int ret = LEPT_PARSE_INVALID_VALUE;
    v->type = LEPT_NULL;            // 提前设置为 LEPT_NULL，若解析成功会更改
    Lept_context c = {json};        // 记录每次解析后的位置
    lept_parse_whitespace(&c);      // 解析JSON字符串开头的空白
    ret = lept_parse_value(&c, v);  // 实际进行解析的函数
    if (ret == LEPT_PARSE_OK) {
        lept_parse_whitespace(&c);
        if (*(c.jsonPos) != '\0') {
            ret = LEPT_PARSE_ROOT_NOT_SINGULAR;
        }
    }
    return ret;
}

/**
 * @name: Lept_get_type
 * @brief: 获得节点值的JSON类型
 */
Lept_type Lept_get_type(const Lept_value *v)
{
    return v->type;
}