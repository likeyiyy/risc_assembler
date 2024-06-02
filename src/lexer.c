#include "lexer.h"
#include <ctype.h>
#include <string.h>

static const char *source_code;
static size_t current_pos;

void lexer_init(const char *source) {
    source_code = source;
    current_pos = 0;
}

static char current_char(void) {
    return source_code[current_pos];
}

static void advance(void) {
    current_pos++;
}

Token lexer_next_token(void) {
    Token token;
    token.type = TOKEN_UNKNOWN;
    size_t text_pos = 0;

    while (isspace(current_char())) {
        advance();
    }

    if (current_char() == '\0') {
        token.type = TOKEN_EOF;
        return token;
    }

    if (isalpha(current_char()) || current_char() == '.') {
        while (isalnum(current_char()) || current_char() == '.' || current_char() == '_') {
            token.text[text_pos++] = current_char();
            advance();
        }
        token.text[text_pos] = '\0';
        if (token.text[0] == '.') {
            token.type = TOKEN_DIRECTIVE;
        } else {
            token.type = TOKEN_IDENTIFIER;
        }
        return token;
    }

    if (current_char() == '%') {
        advance();
        while (isalnum(current_char())) {
            token.text[text_pos++] = current_char();
            advance();
        }
        token.text[text_pos] = '\0';
        token.type = TOKEN_REGISTER;
        return token;
    }

    if (isdigit(current_char())) {
        while (isdigit(current_char())) {
            token.text[text_pos++] = current_char();
            advance();
        }
        token.text[text_pos] = '\0';
        token.type = TOKEN_NUMBER;
        return token;
    }

    if (current_char() == ',') {
        token.text[text_pos++] = current_char();
        token.text[text_pos] = '\0';
        token.type = TOKEN_COMMA;
        advance();
        return token;
    }

    if (current_char() == ':') {
        token.text[text_pos++] = current_char();
        token.text[text_pos] = '\0';
        token.type = TOKEN_COLON;
        advance();
        return token;
    }

    token.text[text_pos++] = current_char();
    token.text[text_pos] = '\0';
    advance();
    return token;
}
