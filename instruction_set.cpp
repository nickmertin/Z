#include "instruction_set.h"

using namespace std;

map<unsigned char, pair<string, vector<arg_type>>> *generateIA() {
    auto *out = new map<unsigned char, pair<string, vector<arg_type>>>();
#define OP(c,...) (*out)[OP_##c] = pair<string, vector<arg_type>>(#c, vector<arg_type>({__VA_ARGS__}));
    OP(NOP)
    OP(BRA,     LABEL)
    OP(ADD,     LVALUE, RVALUE, RVALUE)
    OP(SUB,     LVALUE, RVALUE, RVALUE)
    OP(MUL,     LVALUE, RVALUE, RVALUE)
    OP(DIV,     LVALUE, RVALUE, RVALUE)
    OP(MOD,     LVALUE, RVALUE, RVALUE)
    OP(AND,     LVALUE, RVALUE, RVALUE)
    OP(NAND,    LVALUE, RVALUE, RVALUE)
    OP(OR,      LVALUE, RVALUE, RVALUE)
    OP(NOR,     LVALUE, RVALUE, RVALUE)
    OP(XOR,     LVALUE, RVALUE, RVALUE)
    OP(ADDF,    LVALUEF, RVALUEF, RVALUEF)
    OP(SUBF,    LVALUEF, RVALUEF, RVALUEF)
    OP(MULF,    LVALUEF, RVALUEF, RVALUEF)
    OP(DIVF,    LVALUEF, RVALUEF, RVALUEF)
    OP(MODF,    LVALUEF, RVALUEF, RVALUEF)
    OP(MOV,     LVALUE, RVALUE)
    OP(MOVF,    LVALUEF, RVALUEF)
    OP(INC,     LVALUE)
    OP(DEC,     LVALUE)
    OP(SYSCALL)
    OP(CEQ,     RVALUE, RVALUE);
    OP(CNE,     RVALUE, RVALUE);
    OP(CGT,     RVALUE, RVALUE);
    OP(CLT,     RVALUE, RVALUE);
    OP(CGTE,    RVALUE, RVALUE);
    OP(CLTE,    RVALUE, RVALUE);
    OP(CEQF,    RVALUE, RVALUE);
    OP(CNEF,    RVALUE, RVALUE);
    OP(CGTF,    RVALUE, RVALUE);
    OP(CLTF,    RVALUE, RVALUE);
    OP(CGTEF,   RVALUE, RVALUE);
    OP(CLTEF,   RVALUE, RVALUE);
    OP(BRC,     LABEL);
    OP(BRV,     RVALUE);
    OP(ADDB,    LVALUEB, RVALUEB, RVALUEB)
    OP(SUBB,    LVALUEB, RVALUEB, RVALUEB)
    OP(MULB,    LVALUEB, RVALUEB, RVALUEB)
    OP(DIVB,    LVALUEB, RVALUEB, RVALUEB)
    OP(MODB,    LVALUEB, RVALUEB, RVALUEB)
    OP(ANDB,    LVALUEB, RVALUEB, RVALUEB)
    OP(NANDB,   LVALUEB, RVALUEB, RVALUEB)
    OP(ORB,     LVALUEB, RVALUEB, RVALUEB)
    OP(NORB,    LVALUEB, RVALUEB, RVALUEB)
    OP(XORB,    LVALUEB, RVALUEB, RVALUEB)
    OP(MOVB,    LVALUEB, RVALUEB)
    OP(CEQB,     RVALUEB, RVALUEB);
    OP(CNEB,     RVALUEB, RVALUEB);
    OP(CGTB,     RVALUEB, RVALUEB);
    OP(CLTB,     RVALUEB, RVALUEB);
    OP(CGTEB,    RVALUEB, RVALUEB);
    OP(CLTEB,    RVALUEB, RVALUEB);
#undef OP
    return out;
};

map<unsigned char, pair<string, vector<arg_type>>> &instructionsAssembly = *generateIA();

map<string, pair<unsigned char, vector<arg_type>>> *generateDA() {
    auto *out = new map<string, pair<unsigned char, vector<arg_type>>>();
    for (auto &p : instructionsAssembly)
        (*out)[p.second.first] = pair<unsigned char, vector<arg_type>>(p.first, p.second.second);
    return out;
};

map<string, pair<unsigned char, vector<arg_type>>> &instructionsDisassembly = *generateDA();