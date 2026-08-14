#ifndef AEROLINEA_H
#define AEROLINEA_H

#include <string>

class Vuelo;

class Aerolinea {
private:
    std::string nombre;
    int numDias;
    Vuelo*** itinerario;
    std::string* nombreDias;
    int* vuelosPorDia;

public:
    Aerolinea(std::string nombre, int numDias, std::string* nombreDias, int* vuelosPorDia);
    ~Aerolinea();
    std::string mostrarInformacion() const;
    bool agregarVuelo(int diaIdx, int vueloIdx, Vuelo* vuelo);
    bool eliminarVuelo(int diaIdx, int vueloIdx);
};

#endif