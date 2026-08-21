#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Filtrar recibe el fds de lectura abierto de un pipe con núms cargados a
// filtrar segun el primero que se lee, que es un núm primo. Luego, se realiza
// un fork donde el proceso padre realiza el filtrado y vuelca el resultado en
// el pipe que filtrará el proceso hijo. Esto se repita hasta que no haya más núms que leer.
void
filtrar(int fds_read)
{
	int recibido;
	int bytes_leidos = 0;
	int fds_b[2];

	// Leo el primer núm primo y lo imprimo, si read devuelve 0, no quedan núms por leer
	if (read(fds_read, &recibido, sizeof(recibido)) == 0)
		return;
	printf("primo %d\n", recibido);
	int primo = recibido;

	// Creación del pipe
	if (pipe(fds_b) == -1) {
		perror("Error al crear el pipe\n");
		exit(EXIT_FAILURE);
	}

	// Creación del fork
	pid_t pid = fork();
	if (pid < 0) {
		perror("Hubo un error en el fork\n");
		exit(EXIT_FAILURE);
	}

	if (pid == 0) {  // Entra el proceso hijo
		close(fds_read);
		close(fds_b[1]);
		filtrar(fds_b[0]);
		close(fds_b[0]);
		exit(EXIT_SUCCESS);
	} else {  // Entra el proceso padre
		close(fds_b[0]);

		// Se filtran los núms que sean múltiplos de primo, y el resto
		// se escriben en el pipe que filtrará el proceso hijo
		while ((bytes_leidos =
		                read(fds_read, &recibido, sizeof(recibido))) > 0) {
			if (recibido % primo != 0) {
				if (write(fds_b[1], &recibido, sizeof(recibido)) ==
				    -1) {
					perror("Error al crear el pipe\n");
					exit(EXIT_FAILURE);
				}
			}
		}
		close(fds_b[1]);
		close(fds_read);
		wait(NULL);
	}
}

int
main(int argc, char *argv[])
{
	// Chequeo de cantidad de argumentos requeridos
	if (argc != 2) {
		perror("Parámetros incorrectos\n");
		exit(EXIT_FAILURE);
	}

	// Chequeo si el núm ingresado es válido
	int n = atoi(argv[1]);
	if (n < 2) {
		perror("El número ingresado debe ser mayor o igual a 2\n");
		exit(EXIT_FAILURE);
	}

	pid_t pid;

	// Creación del pipe
	int fds[2];
	if (pipe(fds) == -1) {
		perror("Hubo un error al crear el pipe\n");
		exit(EXIT_FAILURE);
	}

	// Creación del fork
	pid = fork();
	if (pid < 0) {  // Error en el fork
		perror("Hubo un error en el fork\n");
		exit(EXIT_FAILURE);
	}

	if (pid == 0) {  // Entra el proceso hijo para filtrar
		close(fds[1]);
		filtrar(fds[0]);
		close(fds[0]);
		exit(EXIT_SUCCESS);
	} else {  // Entra el proceso padre
		close(fds[0]);
		for (int i = 2; i < n + 1; i++) {
			int num = i;

			// Se escriben los núms en el pipe
			if (write(fds[1], &num, sizeof(num)) == -1) {
				perror("Error al crear el pipe");
				exit(EXIT_FAILURE);
			}
		}
		close(fds[1]);
		wait(NULL);  // Espera que termine el proceso hijo
	}

	return 0;
}