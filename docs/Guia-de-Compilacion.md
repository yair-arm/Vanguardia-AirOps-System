# Guía de compilación

Requisitos y pasos para compilar y ejecutar el sistema Vanguardia AirOps.

## Requisitos

- Compilador C++ con soporte C++17: **g++** (MinGW-w64 / MSYS2 en Windows, o g++ en Linux/macOS)
- Librería **nlohmann/json** (header-only): colocar `json.hpp` en `include/` (o en una carpeta `third_party/` y ajustar la ruta de inclusión)
- [Opcional] `make` para usar el Makefile

## Estructura esperada

```
.
├── include/            # cabeceras .h (+ json.hpp)
├── src/                # implementaciones .cpp de las clases
├── main.cpp            # punto de entrada (raíz del proyecto)
└── datos.json          # archivo de datos (se crea/lee en runtime)
```

## Compilar

### Opción 1: g++ directo

```bash
g++ -std=c++17 -Iinclude main.cpp src/*.cpp -o aerolineas
```

En Windows con MinGW:

```powershell
g++ -std=c++17 -Iinclude main.cpp src/*.cpp -o aerolineas.exe
```

> Nota: `main.cpp` vive en la raíz; por eso se lista aparte de `src/*.cpp` (que solo contiene las implementaciones de las clases).

### Opción 2: Makefile (próximamente)

```bash
make
```

## Ejecutar

```bash
./aerolineas            # Linux/macOS
.\aerolineas.exe        # Windows
```

El programa busca `datos.json` en el directorio de trabajo. Si no existe, `cargarDatos` falla y el programa lo informa.

## Validación de memoria (Fase 4)

Linux/macOS con AddressSanitizer:

```bash
g++ -std=c++17 -fsanitize=address -g -Iinclude main.cpp src/*.cpp -o aerolineas_asan
./aerolineas_asan
```

Linux con Valgrind:

```bash
valgrind --leak-check=full ./aerolineas
```

Los resultados se registran en `docs/Informe-de-Memoria.md`.