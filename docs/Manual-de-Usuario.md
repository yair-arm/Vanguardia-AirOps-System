# Manual de usuario

## Descripción

Sistema de gestión de vuelos e itinerarios del **Aeropuerto Vanguardia (VVC)**, Villavicencio. Administra 3 aerolíneas precargadas desde un archivo JSON:

| Aerolínea | Días de operación | Rutas |
|---|---|---|
| Avianca | Lunes a Viernes | Bogotá |
| SATENA | Lunes, Miércoles y Viernes | Bogotá, Mitú, Puerto Carreño, Inírida |
| Clic Air | Sábados | Medellín, Bogotá, Puerto Gaitán |

Todo vuelo viaja a su capacidad máxima: el número de pasajeros equivale a la capacidad del avión asignado (no se ingresa manualmente).

## Menú principal

Al iniciar, el programa muestra:

```
==========================================
  VANGUARDIA AIR-OPS — Aeropuerto VVC
==========================================
  1. Ver itinerarios
  2. Modificar vuelo
  3. Cancelar vuelo
  0. Salir
Seleccione una opción:
```

## Opciones

### 1. Ver itinerarios (Read)

Muestra la agenda semanal de cada aerolínea: por cada día y posición, el vuelo (origen → destino, horario) con su avión asignado y la cantidad de pasajeros. Las posiciones sin vuelo se muestran como **Libre**.

### 2. Modificar vuelo (Update)

1. Selecciona la aerolínea (0-2).
2. Indica el día y la posición del vuelo a modificar (debe existir un vuelo ahí).
3. Ingresa los nuevos datos del vuelo: origen, destino y horario.
4. Elige el nuevo avión de la flota (por `id`).
5. El vuelo se recrea con los datos nuevos y la capacidad de pasajeros se actualiza automáticamente.
6. Los cambios se guardan en el JSON.

### 3. Cancelar vuelo (Delete)

1. Selecciona la aerolínea (0-2).
2. Indica el día y la posición del vuelo a cancelar (debe existir un vuelo ahí).
3. El vuelo se elimina y la posición queda **Libre**. El avión NO se destruye: queda disponible en la flota.
4. Los cambios se guardan en el JSON.

### 0. Salir

Guarda los cambios y termina el programa.

## Validaciones

- Los índices de aerolínea, día y posición se validan antes de acceder a la matriz.
- No se puede modificar ni cancelar un vuelo en una posición vacía.
- El `id` de avión debe existir en la flota.

## Persistencia

- **Al iniciar**: carga flota y aerolíneas desde `datos.json`.
- **Tras cada cambio**: reescribe `datos.json`.
- **Al salir**: guarda una última copia del estado.