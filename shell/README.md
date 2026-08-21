# shell

Repositorio para el esqueleto del [TP: shell](https://fisop.github.io/website/tps/shell) del curso Mendez-Fresia de **Sistemas Operativos (7508) - FIUBA**

## Descripción

Implementación de un intérprete de comandos (shell) en C con funcionalidad similar a bash/zsh. El proyecto cubre los conceptos fundamentales de:

- **Gestión de procesos**: fork, exec, wait
- **Redirecciones**: `<`, `>`, `2>`, `2>&1`
- **Pipes**: comunicación entre procesos con `|`
- **Variables de entorno**: expansión y variables temporales
- **Comandos built-in**: `cd`, `pwd`, `exit`
- **Procesos en segundo plano**: manejo de señales con `SIGCHLD`

## Respuestas teóricas

Ver el archivo `shell.md` provisto en el repositorio.

## Características implementadas

### Parte 1: Invocación de comandos
- Búsqueda de binarios en `$PATH`
- Ejecución con y sin argumentos mediante `execvp(3)`

### Parte 2: Redirecciones y pipes
- Redirección de entrada: `< archivo`
- Redirección de salida: `> archivo`
- Redirección de error: `2> archivo`
- Combinación de salida y error: `2>&1`
- Pipes simples y múltiples: `cmd1 | cmd2 | cmd3`

### Parte 3: Variables de entorno
- Expansión de variables: `echo $HOME`
- Variables temporales: `USER=nadie ./programa`
- Pseudo-variable `$?` (código de retorno del último comando)

### Parte 4: Comandos built-in
- `cd` - cambio de directorio
- `pwd` - directorio actual
- `exit` - finaliza la shell

### Parte 5: Procesos en segundo plano
- Ejecución en background con `&`
- Notificación automática al finalizar (vía `SIGCHLD`)
- Liberación de recursos sin intervención del usuario

## Compilar

```bash
make
```

## Ejecutar

```bash
./sh
```

## Pruebas

* Ejecutar todas las pruebas

```bash
make test
```

- Ejecutar una **única** prueba

```bash
make test-TEST_NAME
```

Por ejemplo:

```bash
make test-env_empty_variable
```

Cada identificador de una prueba se muestra entre paréntesis `(TEST_NAME)` al lado de cada _test_ cuando se ejecutan todas las pruebas.

```
=== Temporary files will be stored in: /tmp/tmp0l10br1k-shell-test ===

PASS 1/26: cd . and cd .. work correctly by checking pwd (no prompt) (cd_back)
PASS 2/26: cd works correctly by checking pwd (no prompt) (cd_basic)
PASS 3/26: cd with no arguments takes you home (/proc/sys :D) (cd_home)
PASS 4/26: empty variables are not substituted (env_empty_variable)
...
```

## Linter

```bash
make format
```