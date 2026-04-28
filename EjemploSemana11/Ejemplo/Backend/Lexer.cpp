#include "Lexer.h"
#include <cctype>
#include <iostream>

Token LexicalAnalyzer::nextToken() {
    
    while (pos < input.size() && std::isspace(input[pos])) {
        if (input[pos] == '\n') { line++; col = 1; }
        else { col++; }
        pos++;
    }
    
    if (pos >= input.size()) return {TokenType::END, "", line, col};

    char current = input[pos];
    int startCol = col;

   
    if (std::isalpha(current)) {
        std::string lexeme;
        while (pos < input.size() && (std::isalnum(input[pos]) || input[pos] == '_')) {
            lexeme += input[pos++]; col++;
        }
        if (lexeme == "TABLERO") return {TokenType::TABLERO, lexeme, line, startCol};
        if (lexeme == "COLUMNA") return {TokenType::COLUMNA, lexeme, line, startCol};
        if (lexeme == "tarea") return {TokenType::TAREA, lexeme, line, startCol};
        return {TokenType::ERR, lexeme, line, startCol};
    }
    
   
    if (current == '\"') {
        std::string lexeme; pos++; col++;
        while (pos < input.size() && input[pos] != '\"') {
            lexeme += input[pos++]; col++;
        }
        pos++; col++; 
        return {TokenType::CADENA, lexeme, line, startCol};
    }

   
    if (current == '{') { pos++; col++; return {TokenType::LBRACE, "{", line, startCol}; }
    if (current == '}') { pos++; col++; return {TokenType::RBRACE, "}", line, startCol}; }
    if (current == ':') { pos++; col++; return {TokenType::COLON, ":", line, startCol}; }
    if (current == ',') { pos++; col++; return {TokenType::COMMA, ",", line, startCol}; }

    
    std::string char_err(1, current);
    std::cerr << "LEXER ERROR: Caracter no reconocido '" << char_err << "' en linea " << line << " col " << col << std::endl;
    
    pos++; col++;
    return {TokenType::ERR, char_err, line, startCol};
}