/*
	Autor: Diego Abraham Olvera Mendoza
	Descripci�n: Este programa trata de resolver el problema de encontrar el m�ximo valor de la suma de elementos consecurivos 
	dentro de una lista de enteros (que puede contener valores negativos).
	Si todos los valores de la lista son negativos la suma m�xima es 0. Existen 4 algoritmos que resuelven este problema con 
	distintos tiempos de complejidad. Se implementan los 4 algoritmos y se obtienen estimaciones de los resultados.
*/

#include <iostream>
#include <fstream> // Biblioteca para manipular archivos
#include <string> // Biblioteca para cadenas de texto
#include <time.h> // Biblioteca para tiempos
#include <sstream> // Biblioteca para manipular cadenas de textos
#include <vector> // Biblioteca para arreglos
#include <limits.h> // Biblioteca para buscar m�ximos
#include <math.h> // Potencias
using namespace std;

// Funci�n para crear un archivo
void createCsvFile(string fileName)
{
	fstream file;
	file.open(fileName, ios::out);
	file.close();
}


// Funci�n que genera el dataset
void createSubsequenceDataset(int k) 
{
	createCsvFile("dataset1.csv");
	fstream file;
	// Inicializar la semilla aleatoria
	srand(time(NULL));

	// Abrir o crear un archivo .csv
	file.open("dataset1.csv", ios::app);

	// Escribir enteros aleatorios en el archivo
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < pow(10,k); j++)
		{
			file << rand() % 18 - 9;
			if (j < pow(10, k) - 1)
			{
				file << ',';
			}
		}
		file << '\n';
	}
	file.close();
}

// Funci�n para agregar las posiciones de la solucion y tiempo de cpu de cada instancia a un archivo .csv
void appendToCsvFile(string fileName, int startPosition, int endPosition, int maxSum, double cpu_time)
{
	fstream file;
	file.open(fileName, ios::app);
	file << startPosition << ',' << endPosition << ',' << maxSum << ',' << cpu_time <<'\n';
	file.close();
}

int maxSubSum1(const vector<int>& a)
{
	int maxSum = 0; // Respuesta al problema de la m�xima suma de elementos consecutivos de un vector
	int startPosition = 0; // Posici�n del vector donde inicia la soluci�n. 
	int finishPosition = 0; // Posici�n del vector donde termina la soluci�n.
	clock_t start; // Tiempo de inicio
	clock_t end; // Tiempo de fin
	double cpu_time_used;

	start = clock(); // Iniciamos a cronometrar
	for (int i = 0; i < a.size(); i++)
	{
		for (int j = i; j < a.size(); j++)
		{
			int thisSum = 0;
			for (int k = i; k <= j; k++)
			{
				thisSum += a[k];
			}
			if (thisSum > maxSum)
			{
				maxSum = thisSum;
				startPosition = i;
				finishPosition = j;
			}
		}
	}
	end = clock(); // Paramos de cronometrar
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

	//cout << "La solucion inicia en la posicion " << startPosition << " y termina en la posicion " << finishPosition << endl;
	//cout << "El cpu tardo " << cpu_time_used << " segundos.\n";
	appendToCsvFile("maxSubSum1.csv", startPosition, finishPosition, maxSum, cpu_time_used);
	return maxSum;
}

int maxSubSum2(const vector<int>& a)
{
	int startPosition = 0; // Posici�n del vector donde inicia la soluci�n. 
	int finishPosition = 0; // Posici�n del vector donde termina la soluci�n.
	clock_t start; // Tiempo de inicio
	clock_t end; // Tiempo de fin
	double cpu_time_used;

	int maxSum = 0;

	start = clock();
	for (int i = 0; i < a.size(); i++)
	{
		int thisSum = 0;
		for (int j = i; j < a.size(); j++)
		{
			thisSum += a[j];
			if (thisSum > maxSum)
			{
				maxSum = thisSum;
				startPosition = i;
				finishPosition = j;
			}
		}
	}
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	appendToCsvFile("maxSubSum2.csv", startPosition, finishPosition, maxSum, cpu_time_used);
	return maxSum;
}

// A utility funtion to find maximum of two integers 
int max(int a, int b) { return (a > b) ? a : b; }

// A utility funtion to find maximum of three integers 		center	1	int

int max3(int a, int b, int c) { return max(max(a, b), c); }

struct resultMaxSubSum3
{
	int startPosition, endPosition, maxSum;
	double cpu_time_used;
};
int maxSumRec(const vector<int>& a, int left, int right, int* startPosition, int* endPosition, int* startPositionLeft, int* endPositionLeft, int* startPositionRight, int* endPositionRight)
{
	int maxSum;
	// int startPositionLeft, endPositionLeft , startPositionRight, endPositionRight;
	
	if (left == right) // Caso base
	{
		if (a[left] > 0)
		{
			*startPosition = left;
			*endPosition = left;
			return a[left];
		}
		else
		{
			return 0;
		}
	}
	int center = (left + right) / 2;
	int maxLeftSum = maxSumRec(a, left, center, startPosition, endPosition, startPositionLeft, endPositionLeft, startPositionRight, endPositionRight);
	int maxRightSum = maxSumRec(a, center + 1, right, startPosition, endPosition, startPositionLeft, endPositionLeft, startPositionRight, endPositionRight);
	int maxLeftBorderSum = 0, leftBorderSum = 0;
	for (int i = center; i >= left; i--)
	{
		leftBorderSum += a[i];
		if (leftBorderSum > maxLeftBorderSum)
		{
			*startPositionLeft = i;
			*endPositionLeft = center;
			maxLeftBorderSum = leftBorderSum;
		}
	}
	int maxRightBorderSum = 0, rightBorderSum = 0;
	for (int j = center + 1	; j <= right; j++)
	{
		rightBorderSum += a[j];
		if (rightBorderSum > maxRightBorderSum)
		{
			*startPositionRight = center + 1;
			*endPositionRight = j;
			maxRightBorderSum = rightBorderSum;
		}
	}
	int midSum = maxLeftBorderSum + maxRightBorderSum;
	maxSum = max3(maxLeftSum, maxRightSum, midSum);
	
	if (maxLeftSum == maxSum)
	{
		*startPosition = *startPositionLeft;
		//*endPosition = *endPositionLeft;
	}
	if (maxRightSum == maxSum)
	{
		// *startPosition = *startPositionRight;
		*endPosition = *endPositionRight;
	}
	if (midSum == maxSum)
	{
		 *startPosition = *startPosition;
		 *endPosition = *endPosition;
	}
	return maxSum;
}

int maxSubSum3(const vector<int>& a)
{
	clock_t start; // Tiempo de inicio
	clock_t end; // Tiempo de fin
	double cpu_time_used;
	int startPosition = 0; // Posici�n del vector donde inicia la soluci�n. 
	int endPosition = 0; // Posici�n del vector donde termina la soluci�n.
	int maxSum = 0;
	int startPositionLeft = 0;
	int endPositionLeft = 0;
	int startPositionRight = 0, endPositionRight = 0;

	start = clock();
	maxSum = maxSumRec(a, 0, a.size() - 1, &startPosition, &endPosition, &startPositionLeft, &endPositionLeft, &startPositionRight, &endPositionRight);
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	appendToCsvFile("maxSubSum3.csv", startPosition, endPosition, maxSum, cpu_time_used);
	return maxSum;
}

int maxSubSum4(const vector<int>& a)
{
	int maxSum = 0, thisSum = 0, startPosition = 0, endPosition = 0, newPosition = 0;
	clock_t start; // Tiempo de inicio
	clock_t end; // Tiempo de fin
	double cpu_time_used;

	start = clock();
	for (int j = 0; j < a.size(); j++)
	{
		thisSum += a[j];
		if (thisSum > maxSum)
		{
			maxSum = thisSum;
			startPosition = newPosition;
			endPosition = j;

		}		
		else if (thisSum < 0)
		{
			thisSum = 0;
			newPosition = j + 1;
		}
			
	}
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	appendToCsvFile("maxSubSum4.csv", startPosition, endPosition, maxSum, cpu_time_used);
	return maxSum;
}

int main() {
	
	string cell;
	vector<int> parsedRow;
	vector<vector<int>> parsedCsv;
	
	// Ejecutar solo una vez
	 createSubsequenceDataset(4);

	// Leer un archivo .csv y guardar su contenido en arreglos

	fstream data("dataset1.csv",ios::in);
	string line;
	while (std::getline(data,line))
	{
		stringstream dataStream(line);
		while (getline(dataStream, cell, ','))
		{
			//cout << "Cell value is: " << cell << '\n';
			parsedRow.push_back(stoi(cell));
		}
		parsedCsv.push_back(parsedRow);
		//restart parsedRow vector
		parsedRow.clear();
	}

	// Imprimir los elementos de la matriz
	for (int i = 0; i < parsedCsv.size(); i++)
	{
		for (int j = 0; j < parsedCsv[i].size(); j++)
		{
			cout << parsedCsv[i][j] << ' ';
		}
		cout << endl;
	}
	// Ejecutar el algoritmo con complejidad O(n)
	createCsvFile("maxSubSum4.csv");
	for (int i = 0; i < parsedCsv.size(); i++)
	{
		maxSubSum4(parsedCsv[i]);
	}
	// Ejecutar el algoritmo con complejidad O(n log n)
	createCsvFile("maxSubSum3.csv"); // Posiciones erroneas
	for (int i = 0; i < parsedCsv.size(); i++)
	{
		maxSubSum3(parsedCsv[i]);
	}

	// Ejecutar el algoritmo con complejidad O( n^2)
	createCsvFile("maxSubSum2.csv"); // Archivo donde se almacenan los resultados del utilizando los datos de entrada dataset1.csv
	for (int i = 0; i < parsedCsv.size(); i++)
	{
		maxSubSum2(parsedCsv[i]);
	}

	// Ejecutar el algoritmo con complejidad O(n^3)
	createCsvFile("maxSubSum1.csv"); // Archivo donde se almacenan los resultados del algoritmo utilizando los datos de dataset1.csv
	// NOTA: Los resultados se agregan a maxSubSum1.csv dentro de la funci�n, por lo tanto se debe crear el archivo antes
	for (int i = 0; i < parsedCsv.size(); i++)
	{
		maxSubSum1(parsedCsv[i]);
	}
	//cout << "La suma maxima es " << maxSubSum1(parsedCsv[0]) << endl;
	//maxSubSum1(parsedCsv[1]);
	//maxSubSum1(parsedCsv[2]);
	
	return 0;
}