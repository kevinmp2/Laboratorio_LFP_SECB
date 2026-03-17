#include "LexicalAnalyzer.h"
#include <cctype>

LexicalAnalyzer::LexicalAnalyzer(const std::string& fuente)
    : codigo(fuente), pos(0), linea(1), columna(1) {}

// ── Helpers ─────────────────────────────────────────────────────

char LexicalAnalyzer::actual() {
    if (pos < (int)codigo.size()) return codigo[pos];
    return '\0';
}

char LexicalAnalyzer::avanzar() {
    char c = actual();
    pos++;
    if (c == '\n') { linea++; columna = 1; }
    else           { columna++; }
    return c;
}

void LexicalAnalyzer::saltarBlancos() {
    while (pos < (int)codigo.size() && std::isspace((unsigned char)actual()))
        avanzar();
}

void LexicalAnalyzer::registrarError(const std::string& lex,
                                     const std::string& tipo,
                                     const std::string& desc) {
    errores.push_back({ lex, tipo, desc, linea, columna });
}

// ── AFD Principal ────────────────────────────────────────────────

Token LexicalAnalyzer::siguienteToken() {
    saltarBlancos();

    int linIni = linea;
    int colIni = columna;

    if (pos >= (int)codigo.size())
        return { TokenType::FIN_ARCHIVO, "EOF", linIni, colIni };

    char c = actual();

    // Delimitadores de un solo carácter
    if (c == '{') { avanzar(); return { TokenType::LLAVE_ABRE,   "{", linIni, colIni }; }
    if (c == '}') { avanzar(); return { TokenType::LLAVE_CIERRA, "}", linIni, colIni }; }
    if (c == ';') { avanzar(); return { TokenType::PUNTO_COMA,   ";", linIni, colIni }; }

    // Palabra reservada o identificador
    if (std::isalpha((unsigned char)c) || c == '_')
        return leerPalabraReservada();

    // Carácter no reconocido → error léxico
    std::string lex(1, c);
    avanzar();
    registrarError(lex, "Carácter ilegal",
                   "El carácter '" + lex + "' no pertenece al alfabeto de MedLang.");
    return { TokenType::DESCONOCIDO, lex, linIni, colIni };
}

// ── Reconocedor de palabras reservadas ──────────────────────────

Token LexicalAnalyzer::leerPalabraReservada() {
    int linIni = linea;
    int colIni = columna;
    std::string lexema;

    // Leer todos los caracteres alfanuméricos o guión bajo
    while (pos < (int)codigo.size() &&
           (std::isalnum((unsigned char)actual()) || actual() == '_')) {
        lexema += avanzar();
    }

    // Tabla de palabras reservadas (por ahora solo HOSPITAL)
    if (lexema == "HOSPITAL")
        return { TokenType::HOSPITAL, lexema, linIni, colIni };

    // No es una palabra reservada conocida → error
    registrarError(lexema, "Token no reconocido",
                   "'" + lexema + "' no es una palabra reservada válida en MedLang.");
    return { TokenType::DESCONOCIDO, lexema, linIni, colIni };
}

// ── Tokenización completa ────────────────────────────────────────

std::vector<Token> LexicalAnalyzer::tokenize() {
    std::vector<Token> tokens;
    pos = 0; linea = 1; columna = 1;
    errores.clear();

    while (true) {
        Token t = siguienteToken();
        if (t.tipo == TokenType::FIN_ARCHIVO) break;
        if (t.tipo != TokenType::DESCONOCIDO)
            tokens.push_back(t);
    }
    return tokens;
}
