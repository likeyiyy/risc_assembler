#ifndef PARSER_H
#define PARSER_H

void parse(const char *source);

// 解析立即数long
long parse_immediate(const char *imm);

#endif // PARSER_H
