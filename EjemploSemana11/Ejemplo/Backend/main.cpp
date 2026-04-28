#include <iostream>
#include <fstream>
#include "Lexer.h"
#include "SyntaxAnalyzer.h"

int main() {
    // 1. Leer el archivo de entrada
    std::ifstream inFile("input.task");
    std::string input((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    
    
    if (input.size() >= 3 && static_cast<unsigned char>(input[0]) == 0xEF && 
        static_cast<unsigned char>(input[1]) == 0xBB && static_cast<unsigned char>(input[2]) == 0xBF) {
        input = input.substr(3);
    }
    
    // 2. Procesar
    LexicalAnalyzer lexer(input);
    SyntaxAnalyzer parser(lexer);
    std::string resultado = parser.parsePrograma();
    
    // 3. Escribir el resultado en JSON
    std::ofstream outFile("../frontend/public/output.json");
    outFile << resultado;
    
    return 0;
}