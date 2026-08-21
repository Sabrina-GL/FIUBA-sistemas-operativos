# sched

Repositorio para el esqueleto del [TP sched](https://fisop.github.io/website/tps/sched) del curso Mendez-Fresia de **Sistemas Operativos (7508) - FIUBA**

## Descripción

Implementación de un **planificador de procesos (scheduler)** y el **mecanismo de cambio de contexto** sobre JOS, un exokernel educativo del MIT. El proyecto se desarrolla sobre arquitectura x86 y se ejecuta emulado con QEMU.

El trabajo cubre los conceptos fundamentales de:
- **Cambio de contexto**: kernel ↔ usuario mediante `iret` e interrupciones
- **Planificación Round Robin**: política justa con turnos equitativos
- **Planificación con prioridades**: scheduling basado en importancia de procesos
- **Syscalls**: manipulación de prioridades desde espacio de usuario
- **Estadísticas de scheduling**: seguimiento y monitoreo de decisiones del planificador

## Respuestas teóricas

Ver el archivo `sched.md` provisto en el repositorio.

## Características implementadas

### Parte 1: Cambio de contexto
- **`context_switch`** en `kern/switch.S`: restauración del estado de CPU mediante `iret`
- **`env_run`** en `kern/env.c`: ejecución de procesos con carga de tabla de páginas
- **`_alltraps`** en `kern/trapentry.S`: manejo de interrupciones y paso de usuario a kernel
- Validación con GDB mostrando el stack durante el cambio de contexto

### Parte 2: Scheduler Round Robin
- **`sched_yield`** en `kern/sched.c`: selección circular de procesos
- Política justa: cada proceso recibe la misma proporción de CPU
- Manejo de procesos en estado `ENV_RUNNABLE`
- Idle cuando no hay procesos para ejecutar

### Parte 3: Scheduler con prioridades
- Asignación de prioridad en creación de procesos (`env_alloc`)
- Syscalls para obtener y modificar prioridades (seguras: no se puede aumentar)
- Heredación de prioridades en `fork()`
- Estadísticas de scheduling:
  - Historial de procesos ejecutados
  - Número de ejecuciones por proceso
  - Tiempos de inicio y fin

## Compilación

Por _default_ se compilará el _scheduler_ en versión **round-robin**.

```bash
make
```

## Compilación condicional de _schedulers_

Para compilar y probar el kernel y poder probar ambos planificadores, se puede:

- **round-robin**:

```bash
make <target> USE_RR=1
```

- **priorities**:

```bash
make <target> USE_PR=1
```

## Pruebas

```bash
make grade
```

## Docker

Se provee un _script_ `dock` que permite ejecutar los siguientes comandos:

- **build**: genera la imagen del proyecto usando el `Dockerfile` provisto
- **run**: genera un _container_ a partir de la imagen anterior y lo corre
- **exec**: permite abrir una nueva _shell_ en el _container_ anterior

Dentro del _container_ se pueden ejecutar todos los comandos provistos por el `GNUmakefile` como `make grade` o `make qemu-nox`.

El _container_ utiliza [mount volumes](https://docs.docker.com/storage/volumes/) con lo cual los cambios que se realicen por fuera del mismo, serán visibles de forma automática.

## Linter

```bash
$ make format
```

Para efectivamente subir los cambios producidos por el `format`, hay que `git add .` y `git commit`.
