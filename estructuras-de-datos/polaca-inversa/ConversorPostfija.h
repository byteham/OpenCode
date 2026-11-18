#ifndef CONVERSOR_POSTFIJA_H
#define CONVERSOR_POSTFIJA_H

#include <string>
#include <vector>

class ConversorPostfija {
private:
    std::vector<std::string> tokenizar(const std::string& expresion) const;
    int prioridad(const std::string& op) const;
    bool asociativoDerecha(const std::string& op) const;

public:
    static bool esOperador(const std::string& s);
    // Infija -> Polaca inversa (algoritmo Shunting-yard)
    std::vector<std::string> convertir(const std::string& expresion) const;
};

#endif
