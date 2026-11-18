#include <iostream>
#include <string>
#include "ConversorPostfija.h"
#include "ArbolExpresion.h"
#include "Pantalla.h"
#include "ValidadorExpresion.h"

int main() {
    Pantalla pantalla;
    ValidadorExpresion validador;
    ConversorPostfija conversor;
    ArbolExpresion arbol;

    std::cout << "Resolucion: " << pantalla.getAncho() << "x" << pantalla.getAlto()
              << "  | mitad del ancho: " << pantalla.getMitadAncho() << " px\n\n";

    std::cout << "Escribe una expresion (ej. (3+4)*2-5/(1+x)): ";
    std::string expresion;
    std::getline(std::cin, expresion);

    // 1) Validacion recursiva
    if (!validador.validar(expresion)) {
        std::cout << "\nExpresion INCORRECTA: " << validador.getError() << "\n";
        return 1;
    }
    std::cout << "\nExpresion CORRECTA\n";

    // 2) Polaca inversa
    std::vector<std::string> postfija = conversor.convertir(expresion);
    std::cout << "\nPolaca inversa: ";
    for (const std::string& t : postfija) std::cout << t << " ";
    std::cout << "\n";

    // 3) Arbol y recorridos
    if (!arbol.construir(postfija)) {
        std::cout << "No se pudo construir el arbol.\n";
        return 1;
    }

    std::cout << "\nPreorden : " << arbol.recorridoPreorden();
    std::cout << "\nInorden  : " << arbol.recorridoInorden();
    std::cout << "\nPostorden: " << arbol.recorridoPostorden() << "\n\n";

    arbol.dibujar(pantalla.getCentroEnColumnas());
    return 0;
}
