#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#define NUM_KIDS 1


int main(int argc, char *argv[]) {
	pid_t processo_padre, PID_processo;
	int numero_figli = NUM_KIDS, numero_casuale, somma=0;

	while(numero_figli) {
		switch(processo_padre = fork()) {
			case -1: //errore
				fprintf(stderr, "Errore durante la creazione di un processo figlio.\nCodice errore: %d.\nDescrizione errore: %s ", 
																									errno, strerror(errno));
				break;

			case 0:  //codice figlio
				numero_casuale = rand()%(6)+1; //genera un numero casuale tra 1 e 6
				PID_processo = getpid();
				printf("PID processo figlio: %d\nStampo n: %d\n", PID_processo, numero_figli);
				exit(numero_casuale);

			default: //codice padre
				while (wait(NULL) != -1) {
					somma = somma + WEXITSTATUS(numero_casuale);
				} 
		}
		numero_figli--;
	}

	printf("Somma: %d", somma);
	exit(EXIT_SUCCESS);
}