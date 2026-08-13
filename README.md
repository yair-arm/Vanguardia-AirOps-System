# Vanguardia AirOps System

Sistema de gestión de vuelos e itinerarios para el **Aeropuerto Vanguardia de Villavicencio (VVC)** — proyecto académico de Estructuras de Datos (C++ / POO).

## Descripción

Administra la agenda semanal de 3 aerolíneas precargadas (Avianca, SATENA y Clic Air) mediante un menú de consola con CRUD de vuelos, regla de ocupación máxima (pasajeros = capacidad del avión asignado) y persistencia en JSON.

## Estructura

```
├── include/       # Cabeceras .h (Avion, Vuelo, Aerolinea, GestorJSON, InterfazConsola)
├── src/           # Implementaciones .cpp + main.cpp
├── docs/          # Documentación entregable (especificación JSON, guías, UML)
│   └── uml/       # Diagrama UML final
└── Vault/         # Documentación interna de trabajo (gitignored)
```

## Características

- 3 aerolíneas precargadas desde JSON: Avianca (L-V, Bogotá), SATENA (L-Mi-V, Bogotá/Mitú/Puerto Carreño/Inírida), Clic Air (S, Medellín/Bogotá/Puerto Gaitán)
- Agenda semanal como matriz 3D dinámica (`Vuelo***`)
- CRUD: consultar itinerarios, modificar vuelo (cambia avión → actualiza pasajeros), cancelar vuelo (libera memoria, `nullptr`, avión disponible)
- Persistencia JSON (`nlohmann/json`): carga al iniciar, guarda tras cada cambio
- Gestión segura de memoria dinámica (composición/agregación bien delimitadas)

## Compilar y ejecutar

Requisitos: g++ (C++17) y `nlohmann/json` en `include/`. Ver [Guía de compilación](docs/Guia-de-Compilacion.md).

```bash
g++ -std=c++17 -Iinclude src/*.cpp -o aerolineas
./aerolineas
```

## Documentación

- [Manual de usuario](docs/Manual-de-Usuario.md)
- [Especificación del JSON](docs/Especificacion-JSON.md)
- [Informe de validación de memoria](docs/Informe-de-Memoria.md)
- [UML final](docs/uml/uml-final.png)

## Notas

- `Vault/` es el repositorio interno de conocimiento del proyecto (contexto, requisitos, decisiones) y no se versiona.
- `docs/Informe-de-Memoria.md` se completa al validar la Fase 4.
