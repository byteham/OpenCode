#ifndef VALIDADOR_EXPRESION_H
#define VALIDADOR_EXPRESION_H

#include <string>

// Valida una expresión matemática usando recursividad (descenso recursivo).
//
// Gramática:
//   expresion -> termino   { ('+' | '-') termino }
//   termino   -> potencia  { ('*' | '/') potencia }
//   potencia  -> factor    [ '^' potencia ]
//   factor    -> NUMERO | VARIABLE | '(' expresion ')'
class ValidadorExpresion {
private:
    std::string texto;
    size_t pos;
    std::string error;

    void saltarEspacios();
    char actual();
    bool fallar(const std::string& mensaje);

    // Cada regla de la gramática es una función que se llama recursivamente
    bool expresion();
    bool termino();
    bool potencia();
    bool factor();
    bool numero();
    bool variable();

public:
    ValidadorExpresion();

    bool validar(const std::string& expresion);
    const std::string& getError() const;
};

#endif
