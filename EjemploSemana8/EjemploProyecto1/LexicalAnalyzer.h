#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

#include "Token.h"
#include <string>
#include <vector>

class LexicalAnalyzer {
public:
    explicit LexicalAnalyzer(const std::string& fuente);

    // Retorna todos los tokens del archivo
    std::vector<Token> tokenize();

    // Errores acumulados durante el análisis
    struct ErrorLexico {
        std::string lexema;
        std::string tipoError;
        std::string descripcion;
        int linea;
        int columna;
    };
    std::vector<ErrorLexico> errores;

private:
    std::string codigo;   // Contenido completo del archivo
    int pos;              // Posición actual en el string
    int linea;
    int columna;

    char actual();        // Carácter en pos actual
    char avanzar();       // Avanza y retorna el siguiente carácter
    void saltarBlancos(); // Ignora espacios, tabs, saltos de línea

    Token siguienteToken();                      // AFD principal
    Token leerPalabraReservada();                // Reconoce HOSPITAL (y futuras)
    void  registrarError(const std::string& lexema,
                        const std::string& tipo,
                        const std::string& desc);
};

#endif // LEXICALANALYZER_H
