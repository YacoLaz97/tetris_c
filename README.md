# Proyecto Tetris - Universidad

Este es un desarrollo de Tetris programado en **Lenguaje C** como trabajo práctico para la universidad. El proyecto utiliza la biblioteca gráfica **GBT**.

LINK A BIBLIOTECA GBT
```text
https://gitlab.com/RodrigoMaranzana/libgbt-dist
```

## 📂 Estructura del Proyecto

Para que el proyecto compile correctamente en Code::Blocks, se debe mantener la siguiente estructura de carpetas (asegúrate de tener las bibliotecas fuera de la carpeta del código fuente):

```text
TETRIS C
├── GBT/                                          # Carpeta con archivos de la biblioteca GBT
├── lib/                                          # Bibliotecas estáticas (.a)
├── bin/                                          # Binarios generados (.dll)
└── tetris_c/                                     # Carpeta del repositorio (Código Fuente)
    ├── gbt.dll                                   # Archivo necesario para la ejecución
    ├── main.c
    ├── juego.c / juego.h
    ├── piezas.c / piezas.h
    ├── graficos.c / graficos.h
    └── tetrisc.cbp
