#ifndef SYMTABLE_H
#define SYMTABLE_H
#include <stdint.h>

typedef struct {
    char name[32];
    uint32_t address;
} Symbol;

void symtable_init();
void symtable_add(const char *name, uint32_t address);
Symbol* symtable_find(const char *name);

#endif // SYMTABLE_H
