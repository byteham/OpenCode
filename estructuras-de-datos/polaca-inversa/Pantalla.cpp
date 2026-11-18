#include "Pantalla.h"
#include <algorithm>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

int Pantalla::getAncho() const {
#ifdef _WIN32
    return GetSystemMetrics(SM_CXSCREEN);
#else
    return 1920;                      // valor por defecto fuera de Windows
#endif
}

int Pantalla::getAlto() const {
#ifdef _WIN32
    return GetSystemMetrics(SM_CYSCREEN);
#else
    return 1080;
#endif
}

int Pantalla::getMitadAncho() const {
    return getAncho() / 2;
}

int Pantalla::getColumnasConsola() const {
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO info;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info))
        return info.srWindow.Right - info.srWindow.Left + 1;
#endif
    return 120;
}

int Pantalla::getCentroEnColumnas() const {
    // Un caracter mide ~8 px; se limita al ancho real de la terminal de VS Code
    int centro = getMitadAncho() / 8;
    return std::min(centro, getColumnasConsola() / 2);
}
