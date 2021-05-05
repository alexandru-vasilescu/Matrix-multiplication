/*
 * Tema 2 ASC
 * 2021 Spring
 */
#include "utils.h"

/*
 * Add your optimized implementation here
 */
double *my_solver(int N, double *A, double *B)
{
	printf("OPT SOLVER\n");
	// Aloc matrici ajutatoare pentru a pastra continutul calculelor pe parcurs
	double *B_Bt = calloc(N * N, sizeof(double));
	if(B_Bt == NULL){
		return NULL;
	}
	double *A_B_Bt = calloc(N * N, sizeof(double));
	if(A_B_Bt == NULL){
		free(B_Bt);
		return NULL;
	}
	// Matricea a transpusa
	double *At = malloc(N * N * sizeof(double));
	if(At == NULL){
		free(B_Bt);
		free(A_B_Bt);
		return NULL;
	}

	int i, j;
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			At[i * N + j] = A[j * N + i];

	//B * Bt
	for (i = 0; i < N; i++)
	{
		double *original_b = &B[i * N];
		for (j = 0; j < N; j++)
		{
			register double *p_b = original_b;
			/* Inmultirea se face linie cu linie (linia i cu fiecare linie j)
			*  deoarce a doua matrice este transpusa
			*/
			register double *p_bt = &B[j * N];
			register double sum = 0;
			register int k;
			for (k = 0; k < N; k++)
			{
				sum += *p_b * *p_bt;
				p_b++;
				p_bt++;
			}
			B_Bt[i * N + j] = sum;
		}
	}
	// A * (B * Bt)
	for (i = 0; i < N; i++)
	{
		double *original_pa = &A[i * N];
		for (j = 0; j < N; j++)
		{
			register int k = i;
			/* Se inmulteste cu o matrice superior triunghiulara
			*  se incepe de la A[i][i]
			*/
			register double *p_a = original_pa + k;
			// Inmultirea se face linie cu linie
			register double *p_b = &B_Bt[j * N + k];
			register double sum = 0;

			for (; k < N; k++)
			{
				sum += *p_a * *p_b;
				p_a++;
				p_b++;
			}
			A_B_Bt[i * N + j] = sum;
		}
	}
	// At * A
	for (i = 0; i < N; i++)
	{
		//Folosesc A transpus pentru a inmultire pe linii in loc de inmultire pe coloane
		double *original_pat = &At[i * N];
		for (j = 0; j < N; j++)
		{
			register double *p_at = original_pat;
			// Inmultirea se face linie cu linie
			register double *p_a = &At[j * N];
			register double sum = 0;
			register int k;
			for (k = 0; k <= i && k <= j; k++)
			{
				sum += *p_at * *p_a;
				p_at++;
				p_a++;
			}
			A_B_Bt[i * N + j] += sum;
		}
	}
	//Eliberez matricile auxiliare
	free(B_Bt);
	free(At);
	return A_B_Bt;
}

