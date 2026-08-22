# Sistemas Operativos (7508) - FIUBA

Repositorio con los trabajos prácticos de la materia **Sistemas Operativos** de la **Facultad de Ingeniería de la Universidad de Buenos Aires (FIUBA)**.

**Curso:** Méndez  
**Año de cursada:** 2024

---

## Trabajos Prácticos

### 1. [fork - Criba de Eratóstenes y xargs](./fork/)
*Trabajo individual* - Implementación de dos programas clásicos de Unix que exploran la creación y comunicación de procesos.


### 2. [shell - Intérprete de comandos](./shell/)
*Trabajo grupal* - Implementación de un intérprete de comandos (shell) con funcionalidad similar a bash/zsh.

### 3. [sched - Scheduling y cambio de contexto](./sched/)
*Trabajo grupal* - Implementación de un planificador de procesos sobre **JOS**, un exokernel educativo del MIT. El proyecto se desarrolla sobre arquitectura x86 y se ejecuta emulado con QEMU.

### 4. [fisopfs - Filesystem FUSE](./fisopfs/)
*Trabajo grupal* - Implementación de un sistema de archivos en espacio de usuario utilizando **FUSE (Filesystem in USErspace)**.



---

## 🛠️ Tecnologías utilizadas

| Tecnología | Uso |
|------------|-----|
| **C11 / POSIX** | Lenguaje principal y estándar de syscalls |
| **Fork / Exec / Wait** | Creación y gestión de procesos |
| **Pipes** | Comunicación entre procesos (IPC) |
| **Dup2** | Redirección de flujos estándar |
| **Signals** | Manejo de SIGCHLD para procesos en background |
| **FUSE** | Implementación de filesystem en espacio de usuario |
| **Assembler x86** | Cambio de contexto en JOS |
| **QEMU / GDB** | Emulación y depuración de bajo nivel |
| **Make / GCC** | Compilación y automatización |
| **Valgrind** | Detección de memory leaks |