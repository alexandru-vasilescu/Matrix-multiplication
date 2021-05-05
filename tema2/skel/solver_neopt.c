/*
 * Tema 2 ASC
 * 2021 Spring
 */
#include "utils.h"

/*
 * Add your unoptimized implementation here
 */
//functie de adunare a doua matrici
void add_matrix(int N, double *A, double *B)
{
	int i;
	for (i = 0; i < N * N; i++)
	{
		B[i] += A[i];
	}
}
double *my_solver(int N, double *A, double *B)
{
	printf("NEOPT SOLVER\n");
	//matrici auxiliare folosite pentru calculul rezultatului
	double *A_B = calloc(N * N, sizeof(double));
	if(A_B == NULL){
		return NULL;
	}
	double *A_B_Bt = calloc(N * N, sizeof(double));
	if(A_B_Bt == NULL){
		free(A_B);
		return NULL;
	}
	double *At_A = calloc(N * N, sizeof(double));
	if(At_A == NULL){
		free(A_B);
		free(A_B_Bt);
		return NULL;
	}
	int i, j, k;
	// Inmultire A cu B
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			// Inmultirea se face cu o matrice superior triunghiulara deci se incepe de la A[i][i]
			for (k = i; k < N; k++)
				A_B[i * N + j] += A[i * N + k] * B[k * N + j];

	//Inmultire A_B cu B transpus
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			for (k = 0; k < N; k++)
				A_B_Bt[i * N + j] += A_B[i * N + k] * B[j * N + k];

	//Inmultire A transpus cu A
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			//Inmultirea se face cu o matrice inferior triunghiulara(traspunsa lui A)
			//Se face pana la A[i][i]
			for (k = 0; k <= i; k++)
				At_A[i * N + j] += A[k * N + i] * A[k * N + j];

	//Adun matricile
	add_matrix(N, At_A, A_B_Bt);
	//Eliberez memoria
	free(At_A);
	free(A_B);
	return A_B_Bt;
}
