#include "ConversorPostfija.h"
#include <stack>
#include <cctype>

bool ConversorPostfija::esOperador(const std::string& s) {
    return s == "+" || s == "-" || s == "*" || s == "/" || s == "^";
}

int ConversorPostfija::prioridad(const std::string& op) const {
    if (op == "^") return 3;
    if (op == "*" || op == "/") return 2;
    return 1;
}

bool ConversorPostfija::asociativoDerecha(const std::string& op) const {
    return op == "^";
}

std::vector<std::string> ConversorPostfija::tokenizar(const std::string& e) const {
    std::vector<std::string> tokens;
    size_t i = 0;
    while (i < e.size()) {
        unsigned char c = e[i];
        if (std::isspace(c)) { i++; continue; }
        if (std::isalnum(c) || c == '.') {          // números y variables
            std::string s;
            while (i < e.size() && (std::isalnum((unsigned char)e[i]) || e[i] == '.'))
                s += e[i++];
            tokens.push_back(s);
        } else {
            tokens.push_back(std::string(1, e[i]));
            i++;
        }
    }
    return tokens;
}

std::vector<std::string> ConversorPostfija::convertir(const std::string& expresion) const {
    std::vector<std::string> salida;
    std::stack<std::string> pila;

    for (const std::string& t : tokenizar(expresion)) {
        if (esOperador(t)) {
            while (!pila.empty() && esOperador(pila.top()) &&
                   (prioridad(pila.top()) > prioridad(t) ||
                   (prioridad(pila.top()) == prioridad(t) && !asociativoDerecha(t)))) {
                salida.push_back(pila.top());
                pila.pop();
            }
            pila.push(t);
        } else if (t == "(") {
            pila.push(t);
        } else if (t == ")") {
            while (!pila.empty() && pila.top() != "(") {
                salida.push_back(pila.top());
                pila.pop();
            }
            if (!pila.empty()) pila.pop();          // descarta "("
        } else {
            salida.push_back(t);                    // operando
        }
    }
    while (!pila.empty()) {
        salida.push_back(pila.top());
        pila.pop();
    }
    return salida;
}
