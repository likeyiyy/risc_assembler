#ifndef LEXER_H
#define LEXER_H

// 标记类型的枚举
typedef enum {
    TOKEN_EOF,          // 文件结束
    TOKEN_IDENTIFIER,   // 标识符
    TOKEN_REGISTER,     // 寄存器
    TOKEN_NUMBER,       // 数字
    TOKEN_COMMA,        // 逗号
    TOKEN_COLON,        // 冒号
    TOKEN_DIRECTIVE,    // 伪指令
    TOKEN_UNKNOWN       // 未知标记
} TokenType;

// 标记结构体
typedef struct {
    TokenType type;     // 标记类型
    char text[32];      // 标记文本
} Token;

// 初始化词法分析器
void lexer_init(const char *source);

// 获取下一个标记
Token lexer_next_token();

#endif // LEXER_H
