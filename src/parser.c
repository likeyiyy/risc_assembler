#include "parser.h"
#include "lexer.h"
#include "symtable.h"
#include "codegen.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 解析立即数long
long parse_immediate(const char *imm) {
    // 支持十进制和十六进制表示
    if (imm[0] == '0' && (imm[1] == 'x' || imm[1] == 'X')) {
        return strtol(imm, NULL, 16); // 解析十六进制
    } else {
        return strtol(imm, NULL, 10); // 解析十进制
    }
}

void parse(const char *source) {
    lexer_init(source);
    Token token;
    char current_label[32] = "";

    while ((token = lexer_next_token()).type != TOKEN_EOF) {
        if (token.type == TOKEN_IDENTIFIER) {
            Token next_token = lexer_next_token();
            if (next_token.type == TOKEN_COLON) {
                // Handle labels
                strncpy(current_label, token.text, sizeof(current_label) - 1);
                current_label[sizeof(current_label) - 1] = '\0';
                symtable_add(current_label, instruction_count);
            } else {
                // Handle instructions
                Token rd, rs1, rs2;
                if (next_token.type == TOKEN_REGISTER) {
                    rd = next_token;
                    next_token = lexer_next_token();
                    if (next_token.type == TOKEN_COMMA) {
                        next_token = lexer_next_token();
                        if (next_token.type == TOKEN_REGISTER) {
                            rs1 = next_token;
                            next_token = lexer_next_token();
                            if (next_token.type == TOKEN_COMMA) {
                                next_token = lexer_next_token();
                                if (next_token.type == TOKEN_REGISTER) {
                                    rs2 = next_token;
                                    codegen_generate(token.text, rd.text, rs1.text, rs2.text);
                                }
                            }
                        }
                    }
                }
            }
        } else if (token.type == TOKEN_DIRECTIVE) {
            if (strcmp(token.text, ".global") == 0) {
                lexer_next_token(); // Skip the identifier
            } else if (strcmp(token.text, ".text") == 0) {
                // Handle .text directive, switch to code section
            } else if (strcmp(token.text, ".data") == 0) {
                // Handle .data directive, switch to data section
            } else if (strcmp(token.text, ".align") == 0) {
                Token align_token = lexer_next_token();
                if (align_token.type == TOKEN_NUMBER) {
                    int alignment = parse_immediate(align_token.text);
                    while (instruction_count % alignment != 0) {
                        codegen_generate("nop", "%x0", "%x0", "%x0");
                    }
                }
            }
        }
    }
}
