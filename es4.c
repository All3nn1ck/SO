
/*Il programma deve: generare NUM_KIDS (Macro). Ogni figlio genera un numero casuale tra 1 e 6. Se il numero casuale è uguale al PID del processo che lo ha generato modulo 6 quel processo figlio si suicida
  altrimenti il processo esegue la exit con stato uguale al numero generato casualmente. Il processo padre deve aspettare che tutti i figli abbiano terminato e fare la somma degli stati di ognuno*/

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#define NUM_KIDS 2

int main(int argc, char * argv[]) {
	int i, numero_casuale, child_status, somma;
	pid_t PID_padre, PID_figlio;

	somma = 0;
	/*Ciclo per generare i figli*/
	for(i = 0; i < NUM_KIDS; i++) {
		/*Switch per suddividere il codice del figlio dal codice del padre*/
		switch(PID_figlio = fork()) {

			case -1:
				fprintf(stderr, "Errore durante la generazione di processi figlio\n");
				break;

			case 0:
				/*Codice figlio*/
				srand(getpid());
				numero_casuale = rand()%(6)+1;
				if(numero_casuale == (getpid()%6)) {
					raise(SIGTERM);
				} else {
					fprintf(stdout, "PID_PADRE: %d | PID_FIGLIO: %d | NUMERO: %d\n", getppid(), getpid(), numero_casuale);
					exit(numero_casuale);
					fprintf(stdout, "Non dovresti mai vedere questo messaggio\n");
				}
				break;

				/*Codice padre*/
			default:
				while(PID_figlio = (wait(&numero_casuale)) != -1) {
					somma = somma + WEXITSTATUS(numero_casuale);
				}
		}
	}
	if(errno == ECHILD) {
		fprintf(stdout, "Somma: %d", somma);
		exit(EXIT_SUCCESS);
	} else {
		fprintf(stderr, "%s:%d: Error#%d: %s\n", __FILE__, __LINE__, errno, strerror(errno));
		exit(EXIT_FAILURE);
	}
}

		