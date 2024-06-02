#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"
#include "codegen.h"
#include "symtable.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source.asm> <output.bin>\n", argv[0]);
        return 1;
    }

    const char *source_file = argv[1];
    const char *output_file = argv[2];

    FILE *f = fopen(source_file, "r");
    if (!f) {
        perror("Failed to open source file");
        return 1;
    }

    fseek(f, 0, SEEK_END);
    long length = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *source_code = (char *)malloc(length + 1);
    if (!source_code) {
        perror("Failed to allocate memory for source code");
        fclose(f);
        return 1;
    }
    fread(source_code, 1, length, f);
    source_code[length] = '\0';
    fclose(f);

    codegen_init();
    symtable_init();

    parse(source_code);

    codegen_write(output_file);

    free(source_code);

    printf("Assembled successfully\n");
    return 0;
}
