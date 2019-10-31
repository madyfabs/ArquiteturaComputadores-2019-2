#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <cmath>
#include <ctime>

#define TAM  2000

using namespace std;


int main() {

	int i, j,k,*a,*b,*c,tmp;
	int n, m, p;

	n = m = p = TAM;

	clock_t tempo_inicial, tempo_final;

	a = (int*)malloc(n * p * sizeof(int));
	b = (int*)malloc(p * m * sizeof(int));
	c = (int*)malloc(n * m * sizeof(int));

	for (i = 0; i < TAM; i++) {
		for (j = 0; j < TAM; j++) {
			*(a + (i * n + j)) = rand() % 10;
			*(b + (i * n + j)) = rand() % 10;
			*(c + (i * n + j)) = 0;
		}
	}

	tempo_inicial = clock();

	omp_set_num_threads(8);

#pragma omp parallel for private(tmp, i, j, k) shared (n, m, p)
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			tmp = 0;
			for (k = 0; k < p; k++) {
				tmp += (*(a + (i * n + k))) * (*(b + (k * p + j)));
			}
			*(c + (i * n + j)) = tmp;
		}
	}
	
	tempo_final = clock();

	cout << fixed;
	cout.precision(6); 
	cout << "execucao: " << (tempo_final - tempo_inicial) / ((double)CLOCKS_PER_SEC);

/*
	for (i = 0; i < TAM; i++) {
		for (j = 0; j < TAM; j++) {
			cout << *(c + (i * TAM + j));
		}
	}  */

	
	return 0;

}




