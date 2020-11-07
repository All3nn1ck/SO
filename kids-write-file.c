#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

/*	Ogni processo figlio dovrà scrivere in un file un "numero_scritture" di volte il proprio PID e il PID del padre */

int main(int argc, char *argv[]) {

	FILE * file;
	int errno, numero_figli=0, numero_scritture=0;
	pid_t processo_figlio, PID_figlio, PID_padre;

	file = fopen(argv[1], "w");
	/*	Apro il file passato come argomento in scrittura	*/
	if(file == NULL) {
		fprintf(stderr, "Errore %d (%s)\nFile in cui scrivere NON presente: %s\n", errno, strerror(errno), argv[1]);
		exit(EXIT_FAILURE);
	}

	numero_figli = atoi(argv[2]);
	if(numero_figli < 1) {
		fprintf(stderr, "Il numero di figli da creare non può essere negativo. Inserisci un valore valido. \nCodice errore: %d (%s)\n", errno, strerror(errno));
		exit(EXIT_FAILURE);
	}

	numero_scritture = atoi(argv[3]);
	if(numero_scritture < 1) {
		fprintf(stderr, "Il numero di scritture deve essere positivo.\n Codice errore: %d (%s)\n", errno, strerror(errno));
		exit(EXIT_FAILURE);
	}

	while(numero_figli > 0) {
		processo_figlio = fork();

		/*	Se mi trovo nel processo padre continuo a fare fork fino ad esaurire la richiesta di fork	*/
		if(processo_figlio != 0) 
			numero_figli--;

		/*	Se mi trovo nel processo figlio stampo numero_scritture volte in un file il PID mio e quello del relativo genitore	*/
		if(processo_figlio == 0) {
			while(numero_scritture > 0) {
				PID_figlio = getpid();
				PID_padre = getppid();
				fprintf(file, "PID_padre = %d ---------- PID processo: %d\n", PID_padre, PID_figlio);
				numero_scritture--;
			}
		/*	Termino il processo processo figlio */
			exit(EXIT_SUCCESS);
		}
		
	}

	fclose(file);
	exit(EXIT_SUCCESS);
}