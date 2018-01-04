#include <stdio.h>
#include <vector>
#include "instruction_set.h"
#include "util.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        perror("Invalid number of arguments!");
        return 1;
    }
    FILE *f = fopen(argv[1], "r");
    int op;
    std::vector<unsigned char> code;
    while ((op = getc(f)) != -1) {
        switch (op) {
            case OP_NOP:
                break;
            case OP_DEC:
                code.push_back(102);
        }
    }
    unsigned char *pCode = new unsigned char(code.size());
}