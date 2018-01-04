#include <stdio.h>
#include <math.h>
#include <map>
#include "instruction_set.h"

#define MEMSIZE 64 * 1024

std::map<int64_t, FILE *> fd;
unsigned char memory[MEMSIZE];
__int64_t r[4] = {0, 0, 0, 0};
double f[4] = {0, 0, 0, 0};
__int64_t ip = 0;
bool c = false;

__int64_t &readRval() {
    __int64_t *val;
    switch (memory[ip++]) {
        case 0:
            val = (__int64_t *)(memory + ip);
            ip += 8;
            return *val;
        case 1:
            return *(__int64_t *)(memory + readRval());
        case 2:
        case 3:
        case 4:
        case 5:
            return r[memory[ip - 1] - 2];
        case 6:
            return ip;
    }
}

__int64_t &readLval() {
    switch (memory[ip++]) {
        case 1:
            return *(__int64_t *)(memory + readRval());
        case 2:
        case 3:
        case 4:
        case 5:
            return r[memory[ip - 1] - 2];
        case 6:
            return ip;
    }
}

double &readRvalf() {
    double *val;
    switch (memory[ip++]) {
        case 0:
            val = (double *)(memory + ip);
            ip += 8;
            return *val;
        case 1:
            return *(double *)(memory + readRval());
        case 2:
        case 3:
        case 4:
        case 5:
            return f[memory[ip - 1] - 2];
    }
}

double &readLvalf() {
    switch (memory[ip++]) {
        case 1:
            return *(double *)(memory + readRval());
        case 2:
        case 3:
        case 4:
        case 5:
            return f[memory[ip - 1] - 2];
    }
}

unsigned char &readRvalb() {
    switch (memory[ip++]) {
        case 0:
            return memory[ip++];
        case 1:
            return memory[readRval()];
        case 2:
        case 3:
        case 4:
        case 5:
            return reinterpret_cast<unsigned char &>(r[memory[ip - 1] - 2]);
        case 6:
            return reinterpret_cast<unsigned char &>(ip);
    }
}

unsigned char &readLvalb() {
    switch (memory[ip++]) {
        case 1:
            return memory[readRval()];
        case 2:
        case 3:
        case 4:
        case 5:
            return reinterpret_cast<unsigned char &>(r[memory[ip - 1] - 2]);
        case 6:
            return reinterpret_cast<unsigned char &>(ip);
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        perror("Invalid number of arguments!");
        return 1;
    }
    FILE *f = fopen(argv[1], "rb");
    fseek(f, 0, SEEK_END);
    size_t len = ftell(f);
    fseek(f, 0, SEEK_SET);
    int64_t start = ip = MEMSIZE - len;
    fread(memory + ip, len, 1, f);
    fclose(f);
    fd[0] = stdin;
    fd[1] = stdout;
    fd[2] = stderr;
    while (ip >= start && ip < MEMSIZE) {
        switch(memory[ip++]) {
            case OP_NOP:
                break;
            case OP_BRA:
                ip = start + *(uint64_t *)&memory[ip];
                break;
            case OP_ADD:
                readLval() = readRval() + readRval();
                break;
            case OP_SUB:
                readLval() = readRval() - readRval();
                break;
            case OP_MUL:
                readLval() = readRval() * readRval();
                break;
            case OP_DIV:
                readLval() = readRval() / readRval();
                break;
            case OP_MOD:
                readLval() = readRval() % readRval();
                break;
            case OP_AND:
                readLval() = readRval() & readRval();
                break;
            case OP_NAND:
                readLval() = ~(readRval() & readRval());
                break;
            case OP_OR:
                readLval() = readRval() | readRval();
                break;
            case OP_NOR:
                readLval() = ~(readRval() | readRval());
                break;
            case OP_XOR:
                readLval() = readRval() ^ readRval();
                break;
            case OP_ADDF:
                readLvalf() = readRvalf() + readRvalf();
                break;
            case OP_SUBF:
                readLvalf() = readRvalf() - readRvalf();
                break;
            case OP_MULF:
                readLvalf() = readRvalf() * readRvalf();
                break;
            case OP_DIVF:
                readLvalf() = readRvalf() / readRvalf();
                break;
            case OP_MODF:
                readLvalf() = fmod(readRvalf(), readRvalf());
                break;
            case OP_MOV:
                readLval() = readRval();
                break;
            case OP_MOVF:
                readLvalf() = readRvalf();
                break;
            case OP_INC:
                ++readLval();
                break;
            case OP_DEC:
                --readLval();
                break;
            case OP_SYSCALL:
                switch (r[0]) {
                    case 0:
                        return r[1];
                    case 1:
                        fread(&memory[r[2]], r[3], 1, fd[r[1]]);
                        break;
                    case 2:
                        fwrite(&memory[r[2]], r[3], 1, fd[r[1]]);
                        break;
                    case 3:
                        r[0] = ftell(fd[r[1]]);
                        break;
                    case 4:
                        fseek(fd[r[1]], r[2], SEEK_SET);
                        break;
                    case 5:
                        fseek(fd[r[1]], r[2], SEEK_END);
                        break;
                }
                break;
            case OP_CEQ:
                c = readRval() == readRval();
                break;
            case OP_CNE:
                c = readRval() != readRval();
                break;
            case OP_CGT:
                c = readRval() > readRval();
                break;
            case OP_CLT:
                c = readRval() < readRval();
                break;
            case OP_CGTE:
                c = readRval() >= readRval();
                break;
            case OP_CLTE:
                c = readRval() <= readRval();
                break;
            case OP_CEQF:
                c = readRvalf() == readRvalf();
                break;
            case OP_CNEF:
                c = readRvalf() != readRvalf();
                break;
            case OP_CGTF:
                c = readRvalf() > readRvalf();
                break;
            case OP_CLTF:
                c = readRvalf() < readRvalf();
                break;
            case OP_CGTEF:
                c = readRvalf() >= readRvalf();
                break;
            case OP_CLTEF:
                c = readRvalf() <= readRvalf();
                break;
            case OP_BRC:
                if (c)
                    ip = start + *(uint64_t *)&memory[ip];
                else
                    ip += 8;
                break;
            case OP_BRV:
                ip = start + readRval();
                break;
            case OP_ADDB:
                readLvalb() = readRvalb() + readRvalb();
                break;
            case OP_SUBB:
                readLvalb() = readRvalb() - readRvalb();
                break;
            case OP_MULB:
                readLvalb() = readRvalb() * readRvalb();
                break;
            case OP_DIVB:
                readLvalb() = readRvalb() / readRvalb();
                break;
            case OP_MODB:
                readLvalb() = readRvalb() % readRvalb();
                break;
            case OP_ANDB:
                readLvalb() = readRvalb() & readRvalb();
                break;
            case OP_NANDB:
                readLvalb() = ~(readRvalb() & readRvalb());
                break;
            case OP_ORB:
                readLvalb() = readRvalb() | readRvalb();
                break;
            case OP_NORB:
                readLvalb() = ~(readRvalb() | readRvalb());
                break;
            case OP_XORB:
                readLvalb() = readRvalb() ^ readRvalb();
                break;
            case OP_MOVB:
                readLvalb() = readRvalb();
                break;
            case OP_CEQB:
                c = readRvalb() == readRvalb();
                break;
            case OP_CNEB:
                c = readRvalb() != readRvalb();
                break;
            case OP_CGTB:
                c = readRvalb() > readRvalb();
                break;
            case OP_CLTB:
                c = readRvalb() < readRvalb();
                break;
            case OP_CGTEB:
                c = readRvalb() >= readRvalb();
                break;
            case OP_CLTEB:
                c = readRvalb() <= readRvalb();
                break;
        }
    }
}