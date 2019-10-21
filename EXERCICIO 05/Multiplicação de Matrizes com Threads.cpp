#include <iostream>
#include <pthread.h>
#include <stdlib.h>

using namespace std;

// Tamanho da matriz
#define TAM 4 

// Numero de Threads 
#define THREADS 4 

int m1[TAM][TAM];
int m2[TAM][TAM];
int m3[TAM][TAM];
int cont = 0;

void* multi(void* arg)
{
	int nucl = cont++;

	// cada thread vai calcular apenas uma linha x coluna da multiplicação 
	for (int i = nucl * TAM / 4; i < (nucl + 1) * TAM / 4; i++)
		for (int j = 0; j < TAM; j++)
			for (int k = 0; k < TAM; k++)
				m3[i][j] += m1[i][k] * m2[k][j];
	
}


int main()
{
	for (int i = 0; i < TAM; i++) {
		for (int j = 0; j < TAM; j++) {
			m1[i][j] = rand() % 10;
			m2[i][j] = rand() % 10;
		}
	}

	
	cout << "\n"<< "Matriz 1" << endl;
	for (int i = 0; i < TAM; i++) {
		for (int j = 0; j < TAM; j++)
			cout << m1[i][j] << " ";
		cout << endl;
	}

	 
	cout << "\n"<< "Matriz 2" << endl;
	for (int i = 0; i < TAM; i++) {
		for (int j = 0; j < TAM; j++)
			cout << m2[i][j] << " ";
		cout << endl;
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

	return 0;
}
