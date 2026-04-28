#ifndef SYNTAX_H
#define SYNTAX_H
#include "Lexer.h"
#include <string>

class SyntaxAnalyzer {
    LexicalAnalyzer& lexer;
    Token currentToken;
    void match(TokenType type);
public:
    SyntaxAnalyzer(LexicalAnalyzer& l) : lexer(l) { currentToken = lexer.nextToken(); }
    std::string parsePrograma();
    std::string parseColumnas();
    std::string parseColumna();
    std::string parseTareas();
    std::string parseTarea();
};
#endif