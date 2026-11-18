#include "ValidadorExpresion.h"
#include <cctype>

ValidadorExpresion::ValidadorExpresion() : pos(0) {}

void ValidadorExpresion::saltarEspacios() {
    while (pos < texto.size() && std::isspace((unsigned char)texto[pos])) pos++;
}

char ValidadorExpresion::actual() {
    saltarEspacios();
    return pos < texto.size() ? texto[pos] : '\0';
}

bool ValidadorExpresion::fallar(const std::string& mensaje) {
    if (error.empty())
        error = mensaje + " (posicion " + std::to_string(pos + 1) + ")";
    return false;
}

const std::string& ValidadorExpresion::getError() const { return error; }

// ---------- Punto de entrada ----------
bool ValidadorExpresion::validar(const std::string& e) {
    texto = e;
    pos = 0;
    error.clear();

    if (actual() == '\0') return fallar("La expresion esta vacia");

    if (!expresion()) return false;

    if (actual() != '\0') {
        if (actual() == ')') return fallar("Parentesis de cierre sin apertura");
        return fallar(std::string("Caracter inesperado '") + actual() + "'");
    }
    return true;
}

// expresion -> termino { (+|-) termino }
bool ValidadorExpresion::expresion() {
    if (!termino()) return false;
    while (actual() == '+' || actual() == '-') {
        pos++;
        if (!termino()) return false;           // llamada recursiva
    }
    return true;
}

// termino -> potencia { (*|/) potencia }
bool ValidadorExpresion::termino() {
    if (!potencia()) return false;
    while (actual() == '*' || actual() == '/') {
        pos++;
        if (!potencia()) return false;          // llamada recursiva
    }
    return true;
}

// potencia -> factor [ ^ potencia ]
bool ValidadorExpresion::potencia() {
    if (!factor()) return false;
    if (actual() == '^') {
        pos++;
        return potencia();                      // recursividad (asociativa a la derecha)
    }
    return true;
}

// factor -> NUMERO | VARIABLE | ( expresion )
bool ValidadorExpresion::factor() {
    char c = actual();

    if (c == '(') {
        pos++;
        if (actual() == ')') return fallar("Parentesis vacios");
        if (!expresion()) return false;         // recursividad indirecta
        if (actual() != ')') return fallar("Falta cerrar el parentesis");
        pos++;
        return true;
    }
    if (std::isdigit((unsigned char)c) || c == '.') return numero();
    if (std::isalpha((unsigned char)c)) return variable();

    if (c == '\0') return fallar("Falta un operando al final de la expresion");
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
        return fallar(std::string("Operador '") + c + "' sin operando que lo preceda");
    if (c == ')') return fallar("Falta un operando antes del parentesis de cierre");
    return fallar(std::string("Caracter no valido '") + c + "'");
}

bool ValidadorExpresion::numero() {
    int puntos = 0, digitos = 0;
    while (pos < texto.size() &&
           (std::isdigit((unsigned char)texto[pos]) || texto[pos] == '.')) {
        if (texto[pos] == '.') puntos++; else digitos++;
        pos++;
    }
    if (digitos == 0) return fallar("Numero mal formado");
    if (puntos > 1) return fallar("Numero con mas de un punto decimal");
    if (pos < texto.size() && std::isalpha((unsigned char)texto[pos]))
        return fallar("Numero pegado a una letra");
    return true;
}

bool ValidadorExpresion::variable() {
    while (pos < texto.size() &&
           (std::isalnum((unsigned char)texto[pos]) || texto[pos] == '_'))
        pos++;
    return true;
}
