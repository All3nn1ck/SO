#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void my_handler(int signal);

int main(int argc, char * argv[]) {
	/*Continuo ciclo è una finta variabile booleana per terminare il ciclo del gioco*/
	int continuo_ciclo,numero_casuale, tempo; 
	int * numero_scelto;
	struct sigaction sa;

	/*Inizializzazione event_handler e sigaction*/
	bzero(&sa, sizeof(sa));
	sa.sa_handler = my_handler;

	sigaction(SIGALRM, &sa, NULL);

	/*Inizializzazione altre variabili*/
	continuo_ciclo = 1;
	numero_casuale = 0;
	numero_scelto = malloc(sizeof(int));
	tempo = atoi(argv[2]);


	/*Genero un numero casuale tra 0 e argv[1]*/
	srand(time(0));
	numero_casuale = rand()%(atoi(argv[1]))+1;
	
	/*Per facilitarmi con il debugging*/
	fprintf(stdout, "Il numero generatore è: %d\n", numero_casuale);	

	while(continuo_ciclo != 0) {
		/*Da qui in avanti l'utente avrà tempo secondi per indovinare il numero*/
		alarm(tempo);
		fprintf(stdout, "Inserisci il numero che secondo te è stato generato:\n");
		scanf("%d", numero_scelto);

		/*Numero indovinato: finisce il gioco*/
		if(*numero_scelto == numero_casuale) {
			fprintf(stdout, "Congratulazioni, hai indovinato!\n");
			continuo_ciclo = 0;
		} else {
			if(*numero_scelto > numero_casuale) {
				fprintf(stdout, "Il numero da te selezionato è maggiore del valore da indovinare!\n");
			} else {
				fprintf(stdout, "Il numero da te selezionato è minore del valore da indovinare\n");
			}
		} 
	}
	return 0;
}

void my_handler(int signal) {
	fprintf(stdout, "Ho ricevuto il segnale: %d\n TEMPO SCADUTO\n", signal);
	/*Mi mando un sengale di SIGTERM per terminare il prcesso*/
	raise(SIGTERM);
}