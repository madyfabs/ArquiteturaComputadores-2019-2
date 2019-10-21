#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

// Tamanho da matriz !!
#define TAM 4 

// Numero de Threads 
#define THREADS 4 

int m1[TAM][TAM];
int m2[TAM][TAM];
int m3[TAM][TAM];
int cont = 0;

void* multi(void* arg){
	int nucl = cont++;

	for (int i = nucl * TAM / THREADS; i < (nucl + 1) * TAM / THREADS; i++) {
		for (int j = 0; j < TAM; j++) {
			for (int k = 0; k < TAM; k++) {
				m3[i][j] += m1[i][k] * m2[k][j];
			}
		}
	}
	
}


int main(){

	clock_t tempo_inicial, tempo_final;

	tempo_inicial = clock();

	for (int i = 0; i < TAM; i++) {
		for (int j = 0; j < TAM; j++) {
			m1[i][j] = rand() % 10;
			m2[i][j] = rand() % 10;
		}
	}

	
	pthread_t threads[THREADS];

	for (int i = 0; i < THREADS; i++) {
		int* p;
		pthread_create(&threads[i], NULL, multi, (void*)(p));
	}

	
	for (int i = 0; i < THREADS; i++) {
		pthread_join(threads[i], NULL);
	}
	
	cout << "\n"<< "Resultado: " << "\n";
	for (int i = 0; i < TAM; i++) {
		for (int j = 0; j < TAM; j++)
			cout << m3[i][j] << " ";
		cout << "\n";
	}

	tempo_final = clock();

	cout <<"execucao: "<< (tempo_final - tempo_inicial) / (double)CLOCKS_PER_SEC);

	return 0;
}
