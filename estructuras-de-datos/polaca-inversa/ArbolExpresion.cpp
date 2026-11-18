#include "ArbolExpresion.h"
#include "ConversorPostfija.h"
#include <stack>
#include <iostream>
#include <algorithm>

ArbolExpresion::ArbolExpresion() : raiz(nullptr) {}

ArbolExpresion::~ArbolExpresion() {
    delete raiz;
}

// ---------- Construcción desde la postfija ----------
bool ArbolExpresion::construir(const std::vector<std::string>& postfija) {
    delete raiz;
    raiz = nullptr;

    std::stack<Nodo*> pila;
    for (const std::string& t : postfija) {
        Nodo* n = new Nodo(t);
        if (ConversorPostfija::esOperador(t)) {
            if (pila.size() < 2) {
                delete n;
                while (!pila.empty()) { delete pila.top(); pila.pop(); }
                return false;                       // expresión inválida
            }
            n->setDer(pila.top()); pila.pop();
            n->setIzq(pila.top()); pila.pop();
        }
        pila.push(n);
    }
    if (pila.size() != 1) {
        while (!pila.empty()) { delete pila.top(); pila.pop(); }
        return false;
    }
    raiz = pila.top();
    return true;
}

// ---------- Recorridos ----------
void ArbolExpresion::preorden(Nodo* n, std::string& out) const {
    if (!n) return;
    out += n->getValor() + " ";
    preorden(n->getIzq(), out);
    preorden(n->getDer(), out);
}

void ArbolExpresion::inorden(Nodo* n, std::string& out) const {
    if (!n) return;
    inorden(n->getIzq(), out);
    out += n->getValor() + " ";
    inorden(n->getDer(), out);
}

void ArbolExpresion::postorden(Nodo* n, std::string& out) const {
    if (!n) return;
    postorden(n->getIzq(), out);
    postorden(n->getDer(), out);
    out += n->getValor() + " ";
}

std::string ArbolExpresion::recorridoPreorden() const {
    std::string s; preorden(raiz, s); return s;
}
std::string ArbolExpresion::recorridoInorden() const {
    std::string s; inorden(raiz, s); return s;
}
std::string ArbolExpresion::recorridoPostorden() const {
    std::string s; postorden(raiz, s); return s;
}

// ---------- Dibujo gráfico en consola ----------
int ArbolExpresion::altura(Nodo* n) const {
    return n ? 1 + std::max(altura(n->getIzq()), altura(n->getDer())) : 0;
}

int ArbolExpresion::anchoMaximoToken(Nodo* n) const {
    if (!n) return 0;
    int w = (int)n->getValor().size();
    return std::max(w, std::max(anchoMaximoToken(n->getIzq()),
                                anchoMaximoToken(n->getDer())));
}

// La columna de cada nodo sale de su orden inorden; la fila, de su profundidad
void ArbolExpresion::asignarPosiciones(Nodo* n, int prof, int& contador, int espacio) {
    if (!n) return;
    asignarPosiciones(n->getIzq(), prof + 1, contador, espacio);
    n->setPos(contador * espacio, prof * 2);
    contador++;
    asignarPosiciones(n->getDer(), prof + 1, contador, espacio);
}

void ArbolExpresion::colocar(std::vector<std::string>& g, Nodo* n) const {
    if (!n) return;

    const std::string& v = n->getValor();
    for (size_t i = 0; i < v.size(); i++)
        g[n->getY()][n->getX() + i] = v[i];

    Nodo* hijos[2] = { n->getIzq(), n->getDer() };
    for (int k = 0; k < 2; k++) {
        Nodo* h = hijos[k];
        if (!h) continue;
        int col = (n->getX() + h->getX()) / 2;
        g[n->getY() + 1][col] = (k == 0) ? '/' : '\\';
        colocar(g, h);
    }
}

void ArbolExpresion::dibujar(int columnaCentro) {
    if (!raiz) { std::cout << "(arbol vacio)\n"; return; }

    int espacio = anchoMaximoToken(raiz) + 2;
    int contador = 0;
    asignarPosiciones(raiz, 0, contador, espacio);

    int filas = altura(raiz) * 2 - 1;
    int ancho = contador * espacio + espacio;
    std::vector<std::string> cuadricula(filas, std::string(ancho, ' '));
    colocar(cuadricula, raiz);

    int margen = std::max(0, columnaCentro - ancho / 2);
    for (std::string& linea : cuadricula) {
        size_t fin = linea.find_last_not_of(' ');
        if (fin == std::string::npos) { std::cout << "\n"; continue; }
        std::cout << std::string(margen, ' ') << linea.substr(0, fin + 1) << "\n";
    }
}
