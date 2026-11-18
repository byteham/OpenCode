#include "Nodo.h"

Nodo::Nodo(const std::string& valor)
    : valor(valor), izq(nullptr), der(nullptr), x(0), y(0) {}

Nodo::~Nodo() {
    delete izq;
    delete der;
}

const std::string& Nodo::getValor() const { return valor; }
Nodo* Nodo::getIzq() const { return izq; }
Nodo* Nodo::getDer() const { return der; }
int Nodo::getX() const { return x; }
int Nodo::getY() const { return y; }

void Nodo::setIzq(Nodo* n) { izq = n; }
void Nodo::setDer(Nodo* n) { der = n; }
void Nodo::setPos(int nx, int ny) { x = nx; y = ny; }
