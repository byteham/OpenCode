#ifndef ARBOL_EXPRESION_H
#define ARBOL_EXPRESION_H

#include <string>
#include <vector>
#include "Nodo.h"

class ArbolExpresion {
private:
    Nodo* raiz;

    void preorden(Nodo* n, std::string& out) const;
    void inorden(Nodo* n, std::string& out) const;
    void postorden(Nodo* n, std::string& out) const;

    int altura(Nodo* n) const;
    int anchoMaximoToken(Nodo* n) const;
    void asignarPosiciones(Nodo* n, int prof, int& contador, int espacio);
    void colocar(std::vector<std::string>& cuadricula, Nodo* n) const;

public:
    ArbolExpresion();
    ~ArbolExpresion();

    bool construir(const std::vector<std::string>& postfija);

    std::string recorridoPreorden() const;
    std::string recorridoInorden() const;
    std::string recorridoPostorden() const;

    // Dibuja el árbol en la consola, centrado en la columna indicada
    void dibujar(int columnaCentro);
};

#endif
