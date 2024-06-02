#ifndef CODEGEN_H
#define CODEGEN_H

void codegen_init();
void codegen_generate(const char *mnemonic, const char *rd, const char *rs1, const char *rs2);
void codegen_write(const char *filename);

extern int instruction_count;

#endif // CODEGEN_H
#ifndef CODEGEN_H
#define CODEGEN_H

void codegen_init();
void codegen_generate(const char *mnemonic, const char *rd, const char *rs1, const char *rs2);
void codegen_write(const char *filename);

extern int instruction_count;

#endif // CODEGEN_H
