#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stdint.h>

// 定义伪操作符和标号支持
typedef struct Label {
    char name[32];
    uint32_t address;
} Label;

typedef struct Instruction {
    uint32_t machine_code;
    char label[32];
    struct Instruction *next;
} Instruction;

Instruction* assemble(const char *source);
void free_instructions(Instruction *head);

#endif // ASSEMBLER_H
