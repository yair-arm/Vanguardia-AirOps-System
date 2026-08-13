#ifndef GESTORJSON_H
#define GESTORJSON_H

#include <string>

class Avion;
class Aerolinea;

class GestorJSON {
private:
    std::string rutaArchivo;
public:
    GestorJSON(std::string ruta);
    bool cargarDatos(Aerolinea* outAerolineas[], Avion* outAviones[], int& outNumAviones);
    bool guardarDatos(Aerolinea* aerolineas[], Avion* aviones[], int numAviones);
};

#endif