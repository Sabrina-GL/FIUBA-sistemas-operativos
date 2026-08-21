# fork

Repositorio para el esqueleto del lab [fork](https://fisop.github.io/website/labs/fork) del curso Mendez-Fresia de **Sistemas Operativos (7508) - FIUBA**

## Contenido

Este repositorio contiene las implementaciones del lab fork:

### 1. primes - Criba de Eratóstenes
Implementación del algoritmo de la criba de Eratóstenes utilizando **pipes** y **fork()** recursivo.
- Genera números primos hasta N usando un pipeline de procesos
- Cada proceso filtra los múltiplos de un número primo
- Comunicación mediante pipes anónimos

### 2. xargs - Empaquetador de argumentos
Implementación simplificada del comando `xargs(1)`.
- Lee argumentos línea a línea desde stdin
- Empaqueta NARGS argumentos por ejecución
- Ejecuta el comando con `execvp()`

## Compilar

```bash
make
```

## Ejecución

### primes

```bash
./primes <n>    # Donde n >= 2
```

####  Ejemplo:

```bash
./primes 10
primo 2
primo 3
primo 5
primo 7
```

### xargs

```bash
./xargs <comando>
```

#### Ejemplo:

```bash
seq 10 | ./xargs /bin/echo
1 2 3 4
5 6 7 8
9 10
```

## Pruebas

```bash
make test
```

## Linter

```bash
make format
```
