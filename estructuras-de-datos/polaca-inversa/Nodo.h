#ifndef NODO_H
#define NODO_H

#include <string>

class Nodo {
private:
    std::string valor;
    Nodo* izq;
    Nodo* der;
    int x, y;                      // posición para dibujar

public:
    explicit Nodo(const std::string& valor);
    ~Nodo();

    const std::string& getValor() const;
    Nodo* getIzq() const;
    Nodo* getDer() const;
    int getX() const;
    int getY() const;

    void setIzq(Nodo* n);
    void setDer(Nodo* n);
    void setPos(int x, int y);
};

#endif
