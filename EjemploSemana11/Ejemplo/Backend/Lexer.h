#ifndef LEXER_H
#define LEXER_H
#include "Token.h"
#include <string>

class LexicalAnalyzer {
    std::string input;
    size_t pos;
    int line, col;
public:
    LexicalAnalyzer(std::string in) : input(in), pos(0), line(1), col(1) {}
    Token nextToken();
};
#endif