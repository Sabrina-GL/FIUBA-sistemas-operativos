#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#ifndef NARGS
#define NARGS 4
#endif

int
main(int argc, char *argv[])
{
	// Chequeo de cantidad de argumentos requeridos
	if (argc < 2) {
		perror("Parámetros incorrectos\n");
		exit(EXIT_FAILURE);
	}

	char *linea = NULL;
	size_t n = 0;
	ssize_t read;
	char *args[NARGS + 2];  // NARGS + 2, 1 para el comando y otro para finalizar en NULL
	while (1) {
		int i;
		args[0] = argv[1];  // Inicializo args[0] con el comando a ejecutar

		for (i = 1; i < NARGS + 1; i++) {
			read = getline(&linea, &n, stdin);
			if (read == -1) {  // Llegó al EOF
				break;
			}

			// Elimino el salto de cada línea
			if (linea[read - 1] == '\n') {
				linea[read - 1] = '\0';
			}
			args[i] = strdup(linea);
		}
		args[i] = NULL;  // El último elemento debe ser NULL para el exec()

		// Creación del fork
		pid_t pid = fork();
		if (pid < 0) {
			perror("Hubo un error en el fork\n");
			exit(EXIT_FAILURE);
		}

		if (pid == 0) {  // Entra el proceso hijo
			if (execvp(argv[1], args) == -1) {
				perror("Error al hacer execvp\n");
				exit(EXIT_FAILURE);
			}
			exit(EXIT_SUCCESS);
		} else {  // Entra el proceso padre
			wait(NULL);
		}

		// Libero la memoria de los argumentos
		for (int j = 1; j < i; j++) {
			free(args[j]);
		}

		// Llegó al EOF
		if (read == -1) {
			break;
		}
	}

	// Libero la memoria de la línea
	free(linea);
	return 0;
}
