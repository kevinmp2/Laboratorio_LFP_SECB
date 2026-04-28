#ifndef TOKEN_H
#define TOKEN_H
#include <string>

enum class TokenType { TABLERO, COLUMNA, TAREA, CADENA, LBRACE, RBRACE, COLON, COMMA, END, ERR };

struct Token {
    TokenType type;
    std::string lexeme;
    int line, col;
};
#endif