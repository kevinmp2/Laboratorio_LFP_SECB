#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType {
    // Palabra reservada raíz
    HOSPITAL,

    // Delimitadores
    LLAVE_ABRE,     // {
    LLAVE_CIERRA,   // }
    PUNTO_COMA,     // ;

    // Especiales
    DESCONOCIDO,
    FIN_ARCHIVO
};

// Convierte el enum a string legible para la tabla
inline std::string tokenTypeToString(TokenType t) {
    switch (t) {
    case TokenType::HOSPITAL:      return "PALABRA_RESERVADA";
    case TokenType::LLAVE_ABRE:    return "LLAVE_ABRE";
    case TokenType::LLAVE_CIERRA:  return "LLAVE_CIERRA";
    case TokenType::PUNTO_COMA:    return "PUNTO_COMA";
    case TokenType::FIN_ARCHIVO:   return "FIN_ARCHIVO";
    default:                       return "DESCONOCIDO";
    }
}

struct Token {
    TokenType   tipo;
    std::string lexema;
    int         linea;
    int         columna;
};

#endif // TOKEN_H
