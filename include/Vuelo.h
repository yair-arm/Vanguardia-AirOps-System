#ifndef VUELO_H
#define VUELO_H

#include <string>

class Avion;

class Vuelo {
private:
    std::string origen;
    std::string destino;
    std::string horario;
    Avion* avionAsignado;

public:
    Vuelo(std::string origen, std::string destino, std::string horario, Avion* avionAsignado);
    std::string getOrigen() const;
    std::string getDestino() const;
    std::string getHorario() const;
    int getPasajeros() const;
    Avion* getAvionAsignado() const;
};

#endif