#include "Vuelo.h"
#include "Avion.h"

Vuelo::Vuelo(std::string origen, std::string destino, std::string horario, Avion* avionAsignado) : origen(origen), destino(destino), horario(horario), avionAsignado(avionAsignado) {}

std::string Vuelo::getOrigen() const{
    return origen;
}
std::string Vuelo::getDestino() const{
    return destino;
}
std::string Vuelo::getHorario() const{
    return horario;
}

int Vuelo::getPasajeros() const{
    if(avionAsignado != nullptr){
        return avionAsignado->getCapacidad();
    }
    return 0;
}
Avion* Vuelo::getAvionAsignado() const{
    return avionAsignado;
}