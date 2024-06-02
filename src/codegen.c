#include "codegen.h"
#include "lexer.h"
#include "riscv_defs.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INSTRUCTIONS 1024

static uint32_t instructions[MAX_INSTRUCTIONS];
int instruction_count = 0;

void codegen_init() {
    instruction_count = 0;
}

int parse_register(const char *reg) {
    if (reg[0] == '%' && reg[1] == 'x' && reg[2] >= '0' && reg[2] <= '9') {
        return atoi(&reg[2]);
    }
    return -1;
}

void codegen_generate(const char *mnemonic, const char *rd, const char *rs1, const char *rs2) {
    uint32_t instruction = 0;

    if (strcmp(mnemonic, "add") == 0) {
        instruction |= OPCODE_R_TYPE;
        instruction |= (parse_register(rd) << 7);
        instruction |= (FUNCT3_ADD_SUB << 12);
        instruction |= (parse_register(rs1) << 15);
        instruction |= (parse_register(rs2) << 20);
        instruction |= (FUNCT7_ADD << 25);
    } else if (strcmp(mnemonic, "sub") == 0) {
        instruction |= OPCODE_R_TYPE;
        instruction |= (parse_register(rd) << 7);
        instruction |= (FUNCT3_ADD_SUB << 12);
        instruction |= (parse_register(rs1) << 15);
        instruction |= (parse_register(rs2) << 20);
        instruction |= (FUNCT7_SUB << 25);
    }

    // 添加更多指令支持，如 addi, lw, sw 等等
    // ...

    if (instruction_count < MAX_INSTRUCTIONS) {
        instructions[instruction_count++] = instruction;
    }
}

void codegen_write(const char *filename) {
    FILE *f = fopen(filename, "wb");
    if (!f) {
        perror("Failed to open output file");
        return;
    }
    fwrite(instructions, sizeof(uint32_t), instruction_count, f);
    fclose(f);
}
