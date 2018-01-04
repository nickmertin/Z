//
// Created by nmertin on 06/05/16.
//

#ifndef Z_INSTRUCTION_SET_H
#define Z_INSTRUCTION_SET_H

#include <map>
#include <string>
#include <vector>

enum arg_type {
    LVALUE,
    RVALUE,
    LVALUEF,
    RVALUEF,
    LVALUEB,
    RVALUEB,
    LABEL,
};

extern std::map<unsigned char, std::pair<std::string, std::vector<arg_type>>> &instructionsAssembly;

extern std::map<std::string, std::pair<unsigned char, std::vector<arg_type>>> &instructionsDisassembly;

#define OP_NOP     0
#define OP_BRA     1
#define OP_ADD     2
#define OP_SUB     3
#define OP_MUL     4
#define OP_DIV     5
#define OP_MOD     6
#define OP_AND     7
#define OP_NAND    8
#define OP_OR      9
#define OP_NOR     10
#define OP_XOR     11
#define OP_ADDF    12
#define OP_SUBF    13
#define OP_MULF    14
#define OP_DIVF    15
#define OP_MODF    16
#define OP_MOV     17
#define OP_MOVF    18
#define OP_INC     19
#define OP_DEC     20
#define OP_SYSCALL 21
#define OP_CEQ     22
#define OP_CNE     23
#define OP_CGT     24
#define OP_CLT     25
#define OP_CGTE    26
#define OP_CLTE    27
#define OP_CEQF    28
#define OP_CNEF    29
#define OP_CGTF    30
#define OP_CLTF    31
#define OP_CGTEF   32
#define OP_CLTEF   33
#define OP_BRC     34
#define OP_BRV     35
#define OP_ADDB    36
#define OP_SUBB    37
#define OP_MULB    38
#define OP_DIVB    39
#define OP_MODB    40
#define OP_ANDB    41
#define OP_NANDB   42
#define OP_ORB     43
#define OP_NORB    44
#define OP_XORB    45
#define OP_MOVB    46
#define OP_CEQB    47
#define OP_CNEB    48
#define OP_CGTB    49
#define OP_CLTB    50
#define OP_CGTEB   51
#define OP_CLTEB   52

#endif //Z_INSTRUCTION_SET_H
