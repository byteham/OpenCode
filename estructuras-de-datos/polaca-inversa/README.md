# Polaca inversa y recursividad (C++)

Deber de **Estructura de Datos** (ESPE, Tercer Semestre — Parcial 2).

Programa de consola que recibe una expresión aritmética infija, la valida con
recursividad, la convierte a **notación polaca inversa (postfija)** y construye
un **árbol de expresión** para mostrar sus recorridos y dibujarlo en la terminal.

## Características

- **Validación por descenso recursivo** con esta gramática:

  ```
  expresion -> termino  { ('+' | '-') termino }
  termino   -> potencia { ('*' | '/') potencia }
  potencia  -> factor   [ '^' potencia ]
  factor    -> NUMERO | VARIABLE | '(' expresion ')'
  ```

- **Conversión a postfija** con el algoritmo *shunting-yard*, respetando
  precedencia y asociatividad de los operadores.
- **Árbol de expresión** con recorridos `preorden`, `inorden` y `postorden`.
- **Dibujo del árbol en consola**, centrado según la resolución de pantalla.

## Estructura de archivos

| Archivo | Descripción |
| --- | --- |
| `main.cpp` | Flujo principal: valida, convierte, construye y dibuja. |
| `ValidadorExpresion.*` | Validación recursiva de la expresión infija. |
| `ConversorPostfija.*` | Tokenizador y conversión infija → postfija. |
| `ArbolExpresion.*` | Construcción del árbol desde la postfija, recorridos y dibujo. |
| `Nodo.*` | Nodo del árbol (valor, hijos izquierdo/derecho, posición). |
| `Pantalla.*` | Utilidades de resolución/centrado para el dibujo. |

## Compilar y ejecutar

```bash
g++ -std=c++17 *.cpp -o programa
./programa
```

Ejemplo de entrada:

```
(3+4)*2-5/(1+x)
```

Salida esperada (resumida):

```
Expresion CORRECTA

Polaca inversa: 3 4 + 2 * 5 1 x + / -

Preorden : * + 3 4 2 ...
Inorden  : 3 + 4 * 2 - ...
Postorden: 3 4 + 2 * ...
```

> `programa.exe` no se versiona: es un artefacto de compilación (ver `.gitignore`).
