#include "SyntaxAnalyzer.h"
#include <iostream>

void SyntaxAnalyzer::match(TokenType type) {
    if (currentToken.type == type) currentToken = lexer.nextToken();
    else std::cerr << "Error: Token inesperado.\n";
}

std::string SyntaxAnalyzer::parsePrograma() {
    match(TokenType::TABLERO);
    std::string nombreTablero = currentToken.lexeme;
    match(TokenType::CADENA);
    match(TokenType::LBRACE);
    
    std::string json = "{\"tablero\": \"" + nombreTablero + "\", \"columnas\": [";
    json += parseColumnas();
    json += "]}";
    
    match(TokenType::RBRACE);
    return json;
}

std::string SyntaxAnalyzer::parseColumnas() {
    std::string col = parseColumna();
    if (currentToken.type == TokenType::COLUMNA) {
        return col + ", " + parseColumnas();
    }
    return col;
}

std::string SyntaxAnalyzer::parseColumna() {
    match(TokenType::COLUMNA);
    std::string nombreCol = currentToken.lexeme;
    match(TokenType::CADENA);
    match(TokenType::LBRACE);
    
    std::string json = "{\"nombre\": \"" + nombreCol + "\", \"tareas\": [";
    json += parseTareas();
    json += "]}";
    
    match(TokenType::RBRACE);
    return json;
}

std::string SyntaxAnalyzer::parseTareas() {
    std::string t = parseTarea();
    if (currentToken.type == TokenType::COMMA) {
        match(TokenType::COMMA);
        return t + ", " + parseTareas();
    }
    return t;
}

std::string SyntaxAnalyzer::parseTarea() {
    match(TokenType::TAREA);
    match(TokenType::COLON);
    std::string nombreTarea = currentToken.lexeme;
    match(TokenType::CADENA);
    return "{\"nombre\": \"" + nombreTarea + "\"}";
}