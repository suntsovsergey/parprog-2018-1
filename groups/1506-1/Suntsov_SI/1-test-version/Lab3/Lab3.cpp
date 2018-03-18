// Lab2.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include  "iostream"
#include <random>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <fstream>
#include <string>

using namespace std;

/*
*
*/


int ADD(double* MatrixA, double* MatrixB, double* MatrixResult, int MatrixSize)
{
	for (int i = 0; i < MatrixSize*MatrixSize; i++)
	{

		MatrixResult[i] = MatrixA[i] + MatrixB[i];

	}
	return 0;
}

int SUB(double* MatrixA, double* MatrixB, double* MatrixResult, int MatrixSize)
{
	for (int i = 0; i < MatrixSize*MatrixSize; i++)
	{

		MatrixResult[i] = MatrixA[i] - MatrixB[i];

	}
	return 0;
}

int MUL(double* MatrixA, double * MatrixB, double* MatrixResult, int MatrixSize)
{
	for (int i = 0; i<MatrixSize; i++)
	{
		for (int j = 0; j<MatrixSize; j++)
		{
			MatrixResult[i*MatrixSize + j] = 0;
			for (int k = 0; k<MatrixSize; k++)
			{
				MatrixResult[j + MatrixSize*i] += MatrixA[i*MatrixSize + k] * MatrixB[j + MatrixSize*k];
			}
		}
	}
	return 0;
}


int Strassen(int N, double *MatrixA, double *MatrixB, double *MatrixC)
{

	int HalfSize = N / 2;
	int newSize = N / 2;

	if (N <= 2)
	{
		MUL(MatrixA, MatrixB, MatrixC, N);
	}
	else
	{
		double* A11;
		double* A12;
		double* A21;
		double* A22;

		double* B11;
		double* B12;
		double* B21;
		double* B22;

		double* C11;
		double* C12;
		double* C21;
		double* C22;

		double* M1;
		double* M2;
		double* M3;
		double* M4;
		double* M5;
		double* M6;
		double* M7;
		double* AResult;
		double* BResult;


		A11 = new double[newSize*newSize];
		A12 = new double[newSize*newSize];
		A21 = new double[newSize*newSize];
		A22 = new double[newSize*newSize];

		B11 = new double[newSize*newSize];
		B12 = new double[newSize*newSize];
		B21 = new double[newSize*newSize];
		B22 = new double[newSize*newSize];

		C11 = new double[newSize*newSize];
		C12 = new double[newSize*newSize];
		C21 = new double[newSize*newSize];
		C22 = new double[newSize*newSize];

		M1 = new double[newSize*newSize];
		M2 = new double[newSize*newSize];
		M3 = new double[newSize*newSize];
		M4 = new double[newSize*newSize];
		M5 = new double[newSize*newSize];
		M6 = new double[newSize*newSize];
		M7 = new double[newSize*newSize];

		AResult = new double[newSize*newSize];
		BResult = new double[newSize*newSize];


		for (int i = 0; i < N / 2; i++)
		{
			for (int j = 0; j < N / 2; j++)
			{
				A11[j + i*N / 2] = MatrixA[j + i*N];
				A12[j + i*N / 2] = MatrixA[i*N + (j + N / 2)];
				A21[j + i*N / 2] = MatrixA[(i + N / 2)*N + j];
				A22[j + i*N / 2] = MatrixA[(i + N / 2)*N + (j + N / 2)];

				B11[j + i*N / 2] = MatrixB[j + i*N];
				B12[j + i*N / 2] = MatrixB[i*N + (j + N / 2)];
				B21[j + i*N / 2] = MatrixB[(i + N / 2)*N + j];
				B22[j + i*N / 2] = MatrixB[(i + N / 2)*N + (j + N / 2)];

			}
		}



		//M1[][]
		ADD(A11, A22, AResult, HalfSize);

		ADD(B11, B22, BResult, HalfSize);
		Strassen(HalfSize, AResult, BResult, M1);

		//M2[][]
		ADD(A21, A22, AResult, HalfSize);              //M2=(A21+A22)B11
		Strassen(HalfSize, AResult, B11, M2);       //Mul(AResult,B11,M2);

													//M3[][]
		SUB(B12, B22, BResult, HalfSize);              //M3=A11(B12-B22)
		Strassen(HalfSize, A11, BResult, M3);       //Mul(A11,BResult,M3);

													//M4[][]
		SUB(B21, B11, BResult, HalfSize);           //M4=A22(B21-B11)
		Strassen(HalfSize, A22, BResult, M4);       //Mul(A22,BResult,M4);

													//M5[][]
		ADD(A11, A12, AResult, HalfSize);           //M5=(A11+A12)B22
		Strassen(HalfSize, AResult, B22, M5);       //Mul(AResult,B22,M5);


													//M6[][]
		SUB(A21, A11, AResult, HalfSize);
		ADD(B11, B12, BResult, HalfSize);             //M6=(A21-A11)(B11+B12)
		Strassen(HalfSize, AResult, BResult, M6);    //Mul(AResult,BResult,M6);

													 //M7[][]
		SUB(A12, A22, AResult, HalfSize);
		ADD(B21, B22, BResult, HalfSize);             //M7=(A12-A22)(B21+B22)
		Strassen(HalfSize, AResult, BResult, M7);     //Mul(AResult,BResult,M7);

													  //C11 = M1 + M4 - M5 + M7;
		ADD(M1, M4, AResult, HalfSize);
		SUB(M7, M5, BResult, HalfSize);
		ADD(AResult, BResult, C11, HalfSize);

		//C12 = M3 + M5;
		ADD(M3, M5, C12, HalfSize);

		//C21 = M2 + M4;
		ADD(M2, M4, C21, HalfSize);

		//C22 = M1 + M3 - M2 + M6;
		ADD(M1, M3, AResult, HalfSize);
		SUB(M6, M2, BResult, HalfSize);
		ADD(AResult, BResult, C22, HalfSize);



		for (int i = 0; i < HalfSize; i++)
		{
			for (int j = 0; j < HalfSize; j++)
			{
				MatrixC[i*N + j] = C11[i*HalfSize + j];
				MatrixC[i*N + (j + N / 2)] = C12[i*HalfSize + j];
				MatrixC[(i + N / 2)*N + j] = C21[i*HalfSize + j];
				MatrixC[(i + N / 2)*N + (j + N / 2)] = C22[i*HalfSize + j];
			}
		}

		delete[] A11; delete[] A12; delete[] A21; delete[] A22;
		delete[] B11; delete[] B12; delete[] B21; delete[] B22;
		delete[] C11; delete[] C12; delete[] C21; delete[] C22;
		delete[] M1; delete[] M2; delete[] M3; delete[] M4; delete[] M5;
		delete[] M6; delete[] M7;
		delete[] AResult;
		delete[] BResult;


	}


	return 0;
}

void String_to_Char(string str, char* ch)
{
	for (int i = 0; i < str.length(); i++)
		ch[i] = str[i];
}




int main(int argc, char * argv[])
{
	FILE *matr_in, *matr_out;

	char* fileName = "matr.in";
	char* answerName = "matr.out";
	int realSize = 0; //��������� �� �����



	if (argc > 1) {
		fileName = argv[1];
		string str = string(argv[1]) + string(".out");
		answerName = new char[str.length()];
		String_to_Char(str, answerName);
	}
	freopen_s(&matr_in, fileName, "rb", stdin);

	fread(&realSize, sizeof(int), 1, stdin);
	int N = 0;
	//�������� ������ �������, ������� ������� ������� 2

	N = (int)(log2(realSize));
	int k = pow(2, N);
	if (realSize == k) { N = realSize; ; }
	else
	{
		N++;
		N = pow(2, N);
	}


	double *A = new double[N*N];
	double *B = new double[N*N];
	double *C = new double[N*N];
	double *C_new = new double[realSize*realSize];

	for (int i = 0; i<N; i++) {
		for (int j = 0; j<N; j++) {

			A[i*N + j] = 0;
			B[i*N + j] = 0;
			C[i*N + j] = 0;

		}

	}


	for (int i = 0; i<realSize; i++) {
		for (int j = 0; j<realSize; j++) {
			fread(&A[i*N + j], sizeof(double), 1, stdin);
			//cout << A[i*N + j] << " ";
		}
		//cout << endl;

	}

	//cout << endl;

	for (int i = 0; i < realSize; i++) {
		for (int j = 0; j < realSize; j++) {

			fread(&B[i*N + j], sizeof(double), 1, stdin);
			//cout << B[i*N + j] << " ";
		}
		//cout << endl;
	}

	//cout << endl;

	Strassen(N, A, B, C);

	/*for (int i = 0; i < N; i++) {
	for (int j = 0; j < N; j++) {
	cout << C[i*N + j] << " ";
	}
	cout << endl;
	}
	*/

	for (int i = 0; i < realSize; i++) {
		for (int j = 0; j < realSize; j++) {
			C_new[i*realSize + j] = C[i*N + j];
			cout << C_new[i*realSize + j] << " ";
		}
		cout << endl;
	}


	freopen_s(&matr_in, "matr.out", "wb", stdout);
	fwrite(&realSize, sizeof(realSize), 1, stdout);
	fwrite(C_new, sizeof(*C_new), realSize*realSize, stdout);

	//freopen_s(&matr_out, "answer.ans", "wb", stdout);
	////fwrite(&time, sizeof(time), 1, answer);
	//fwrite(&realSize, sizeof(realSize), 1, matr_out);
	//fwrite(C_new, sizeof(*C_new), realSize*realSize, matr_out);


	//fclose(&matr_out);
	system("pause");
	return 0;

}