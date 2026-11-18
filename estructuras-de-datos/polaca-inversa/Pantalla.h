#ifndef PANTALLA_H
#define PANTALLA_H

class Pantalla {
public:
    int getAncho() const;            // resolución horizontal en píxeles
    int getAlto() const;             // resolución vertical en píxeles
    int getMitadAncho() const;       // ancho dividido en 2
    int getColumnasConsola() const;  // columnas de la terminal
    int getCentroEnColumnas() const; // mitad de la resolución -> columnas
};

#endif
