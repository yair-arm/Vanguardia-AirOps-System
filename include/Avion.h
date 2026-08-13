#ifndef AVION_H
#define AVION_H

#include <string>

class Avion {
private:
    std::string id;
    std::string modelo;
    int capacidad;

public:
    Avion(std::string id, std::string modelo, int capacidad);
    std::string getId() const;
    std::string getModelo() const;
    int getCapacidad() const;
};

#endif