#include <cstdio>
#include <map>
#include "util.h"
#include "instruction_set.h"

FILE *out;

const char *readArg(char *arg, bool allowRValue) {
    const char *err;
    switch (*arg) {
        case '`':
            if (!allowRValue)
                return "LValue expected! (%s:%d)\n";
            putc(0, out);
            fwritev(strtoll(arg + 1, NULL, 0), out);
            break;
        case '*':
            putc(1, out);
            if (err = readArg(arg + 1, true))
                return err;
            break;
        case '%':
#define CMP(r) arg[1] == #r[0] && arg[2] == #r[1]
            if(CMP(ra))
                putc(2, out);
            else if(CMP(rb))
                putc(3, out);
            else if(CMP(rc))
                putc(4, out);
            else if(CMP(rd))
                putc(5, out);
            else if(CMP(ip))
                putc(6, out);
            else
                return "Unknown register! (%s:%d)\n";
#undef CMP
            break;
        default:
            return "Unknown specifier! (%s:%d)\n";
    }
    return NULL;
}

const char *readArgf(char *arg, bool allowRValue) {
    const char *err;
    switch (*arg) {
        case '`':
            if (!allowRValue)
                return "LValue expected! (%s:%d)\n";
            putc(0, out);
            fwritev(strtod(arg, NULL), out);
            break;
        case '*':
            putc(1, out);
            if (err = readArg(arg + 1, true))
                return err;
            break;
        case '%':
#define CMP(r) arg[1] == #r[0] && arg[2] == #r[1]
            if(CMP(fa))
                putc(2, out);
            else if(CMP(fb))
                putc(3, out);
            else if(CMP(fc))
                putc(4, out);
            else if(CMP(fd))
                putc(5, out);
            else
                return "Unknown register! (%s:%d)\n";
#undef CMP
            break;
        default:
            return "Unknown specifier! (%s:%d)\n";
    }
    return NULL;
}

const char *readArgb(char *arg, bool allowRValue) {
    const char *err;
    switch (*arg) {
        case '`':
            if (!allowRValue)
                return "LValue expected! (%s:%d)\n";
            putc(0, out);
            fwritev((unsigned char)strtol(arg + 1, NULL, 0), out);
            break;
        case '*':
            putc(1, out);
            if (err = readArg(arg + 1, true))
                return err;
            break;
        case '%':
#define CMP(r) arg[1] == #r[0] && arg[2] == #r[1]
            if(CMP(ra))
                putc(2, out);
            else if(CMP(rb))
                putc(3, out);
            else if(CMP(rc))
                putc(4, out);
            else if(CMP(rd))
                putc(5, out);
            else if(CMP(ip))
                putc(6, out);
            else
                return "Unknown register! (%s:%d)\n";
#undef CMP
            break;
        default:
            return "Unknown specifier! (%s:%d)\n";
    }
    return NULL;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        perror("No source files!\n");
        return 1;
    }
    std::map<std::string, long> labels;
    std::vector<std::pair<std::string, long>> labelRefs;
    char buffer[256];
    char *line, *cmd, *second;
    const char *err;
    size_t len;
    int pos;
    out = fopen(argv[argc - 1], "wb+");
    for (int i = 1; i < argc - 1; ++i) {
        line = buffer;
        FILE *f = fopen(argv[i], "r");
        int n = 0;
        while (getline(&line, &len, f) != -1) {
            ++n;
            trim(&line);
            if (!*line)
                continue;
            pos = strfind(line, ';');
            if (pos != -1)
                line[pos] = 0;
            if (!pos)
                continue;
            pos = strfind(line, ' ');
            second = pos == -1 ? NULL : line + pos + 1;
            if (pos != -1)
                line[pos] = 0;
            pos = strfind(line, ':');
            if (pos != -1) {
                cmd = line + pos + 1;
                line[pos] = 0;
                labels[line] = ftell(out);
                if (!*cmd)
                    continue;
            }
            else
                cmd = line;
            toUpper(&cmd);
            if (instructionsDisassembly.find(cmd) == instructionsDisassembly.end()) {
                fprintf(stderr, "Unknown opcode! (%s:%d)\n", argv[i], n);
                return 1;
            }
            auto v = instructionsDisassembly[cmd];
            putc(v.first, out);
            if(second)
                for (auto &d : v.second) {
                    trim(&second);
                    if (!*second) {
                        fprintf(stderr, "Too few arguments! (%s:%d)\n", argv[i], n);
                        return 1;
                    }
                    switch (d) {
                        case LVALUE:
                            if (err = readArg(second, false)) {
                                fprintf(stderr, err, argv[i], n);
                                return 1;
                            }
                            break;
                        case RVALUE:
                            if (err = readArg(second, true)) {
                                fprintf(stderr, err, argv[i], n);
                                return 1;
                            }
                            break;
                        case LVALUEF:
                            if (err = readArgf(second, false)) {
                                fprintf(stderr, err, argv[i], n);
                                return 1;
                            }
                            break;
                        case RVALUEF:
                            if (err = readArgf(second, true)) {
                                fprintf(stderr, err, argv[i], n);
                                return 1;
                            }
                            break;
                        case LVALUEB:
                            if (err = readArgb(second, false)) {
                                fprintf(stderr, err, argv[i], n);
                                return 1;
                            }
                            break;
                        case RVALUEB:
                            if (err = readArgb(second, true)) {
                                fprintf(stderr, err, argv[i], n);
                                return 1;
                            }
                            break;
                        case LABEL:
                            labelRefs.push_back(std::pair<std::string, long>(second, ftell(out)));
                            fwritev(long(), out);
                            break;
                    }
                    pos = strfind(second, ',');
                    if (pos != -1)
                        second += pos + 1;
                }
            else if (v.second.size()) {
                fprintf(stderr, "No arguments! (%s:%d)\n", argv[i], n);
                return 1;
            }
        }
    }
    for (auto &r : labelRefs) {
        fseek(out, r.second, SEEK_SET);
        fwritev(labels[r.first], out);
    }
    return 0;
}