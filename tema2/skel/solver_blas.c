/*
 * Tema 2 ASC
 * 2021 Spring
 */
#include "utils.h"
#include <string.h>
#include "cblas.h"
/* 
 * Add your BLAS implementation here
 */
double *my_solver(int N, double *A, double *B)
{
	double *C = calloc(N * N, sizeof(double));
	double *D = calloc(N * N, sizeof(double));

	// C = A * B
	memcpy(C, B, N * N * sizeof(double));
	//folosesc functia de inmultire cu o matrice triunghiulara
	cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasNoTrans, CblasNonUnit, N, N, 1, A, N, C, N);

	// D = A^t * A
	memcpy(D, A, N * N * sizeof(double));
	//folosesc functia de inmultire cu o matrice triunghiulara
	cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasTrans, CblasNonUnit, N, N, 1, A, N, D, N);

	// C * B^t + D
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasTrans, N, N, N, 1, C, N, B, N, 1, D, N);

	free(C);
	return D;
}
