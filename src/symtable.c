#include "symtable.h"
#include <string.h>

#define MAX_SYMBOLS 256

static Symbol symbols[MAX_SYMBOLS];
static int symbol_count = 0;

void symtable_init() {
    symbol_count = 0;
}

void symtable_add(const char *name, uint32_t address) {
    if (symbol_count < MAX_SYMBOLS) {
        strncpy(symbols[symbol_count].name, name, sizeof(symbols[symbol_count].name) - 1);
        symbols[symbol_count].name[sizeof(symbols[symbol_count].name) - 1] = '\0';
        symbols[symbol_count].address = address;
        symbol_count++;
    }
}

Symbol* symtable_find(const char *name) {
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbols[i].name, name) == 0) {
            return &symbols[i];
        }
    }
    return NULL;
}
