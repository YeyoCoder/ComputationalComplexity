/*
	Autor: Diego Abraham Olvera Mendoza
	Descripción: Este programa trata de resolver el problema de encontrar el máximo valor de la suma de elementos consecurivos 
	dentro de una lista de enteros (que puede contener valores negativos).
	Si todos los valores de la lista son negativos la suma máxima es 0. Existen 4 algoritmos que resuelven este problema con 
	distintos tiempos de complejidad. Se implementan los 4 algoritmos y se obtienen estimaciones de los resultados.
*/

#include <iostream>
#include <fstream> // Biblioteca para manipular archivos
#include <string> // Biblioteca para cadenas de texto
#include <time.h> // Biblioteca para tiempos
#include <sstream> // Biblioteca para manipular cadenas de textos
#include <vector> // Biblioteca para arreglos
#include <limits.h> // Biblioteca para buscar máximos
#include <math.h> // Potencias
using namespace std;

// Función para crear un archivo
void createCsvFile(string fileName)
{
	fstream file;
	file.open(fileName, ios::out);
	file.close();
}


// Función que genera el dataset
void createSubsequenceDataset(int k) 
{
	int array_size = pow(10, k);
	string fileName = "arraysSize10exp" + to_string(k) + ".csv";
	createCsvFile(fileName);
	fstream file;
	// Inicializar la semilla aleatoria
	srand(time(NULL));

	// Abrir o crear un archivo .csv
	file.open(fileName, ios::app);

	// Escribir enteros aleatorios en el archivo
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < array_size; j++)
		{
			file << rand() % 18 - 9;
			if (j < array_size - 1)
			{
				file << ',';
			}
		}
		file << '\n';
	}
	file.close();
}

// Función para agregar las posiciones de la solucion y tiempo de cpu de cada instancia a un archivo .csv
void appendToCsvFile(string fileName, int startPosition, int endPosition, int maxSum, double cpu_time)
{
	fstream file;
	file.open(fileName, ios::app);
	file << startPosition << ',' << endPosition << ',' << maxSum << ',' << cpu_time <<'\n';
	file.close();
}

int maxSubSum1(const vector<int>& a, int k)
{
	int maxSum = 0; // Respuesta al problema de la máxima suma de elementos consecutivos de un vector
	int startPosition = 0; // Posición del vector donde inicia la solución. 
	int finishPosition = 0; // Posición del vector donde termina la solución.
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
	appendToCsvFile("maxSubSum1_for_nSize10exp" + to_string(k) + ".csv", startPosition, finishPosition, maxSum, cpu_time_used);
	return maxSum;
}

int maxSubSum2(const vector<int>& a, int k)
{
	int startPosition = 0; // Posición del vector donde inicia la solución. 
	int finishPosition = 0; // Posición del vector donde termina la solución.
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
	appendToCsvFile("maxSubSum2_for_nSize10exp"+ to_string(k) + ".csv", startPosition, finishPosition, maxSum, cpu_time_used);
	return maxSum;
}

// A utility funtion to find maximum of two integers 
int max(int a, int b) { return (a > b) ? a : b; }

// A utility funtion to find maximum of three integers 		center	1	int

int max3(int a, int b, int c) { return max(max(a, b), c); }

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

int maxSubSum3(const vector<int>& a, int k)
{
	clock_t start; // Tiempo de inicio
	clock_t end; // Tiempo de fin
	double cpu_time_used;
	int startPosition = 0; // Posición del vector donde inicia la solución. 
	int endPosition = 0; // Posición del vector donde termina la solución.
	int maxSum = 0;
	int startPositionLeft = 0;
	int endPositionLeft = 0;
	int startPositionRight = 0, endPositionRight = 0;

	start = clock();
	maxSum = maxSumRec(a, 0, a.size() - 1, &startPosition, &endPosition, &startPositionLeft, &endPositionLeft, &startPositionRight, &endPositionRight);
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	appendToCsvFile("maxSubSum3_for_nSize10exp"+ to_string(k) + ".csv", startPosition, endPosition, maxSum, cpu_time_used);
	return maxSum;
}

int maxSubSum4(const vector<int>& a, int k)
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
	appendToCsvFile("maxSubSum4_for_nSize10exp" + to_string(k) + ".csv", startPosition, endPosition, maxSum, cpu_time_used);
	return maxSum;
}

int main() {
	
	string cell;
	vector<int> parsedRow;
	vector<vector<int>> parsedCsv;

	//for (int i = 1; i < 7; i++)
	//{
	//	// Ejecutar solo una vez
	//	// createSubsequenceDataset(i);
	//}

	//cout << "Datasets creados!!!" << endl;

	for (int k = 1; k <= 6; k++)
	{
	// Leer un archivo .csv y guardar su contenido en arreglos

		fstream data("arrayssize10exp" + to_string(k) + ".csv", ios::in);
		string line;
		while (std::getline(data, line))
		{
			stringstream datastream(line);
			while (getline(datastream, cell, ','))
			{
				parsedRow.push_back(stoi(cell));	
			}
			parsedCsv.push_back(parsedRow);
			//restart parsedrow vector
			parsedRow.clear();
		}

		// Imprimir los elementos de la matriz
		// for (int i = 0; i < parsedCsv.size(); i++)
		// {
		//	cout << i << endl;
		//	for (int j = 0; j < parsedCsv[i].size(); j++)
		//	{
		//		cout << parsedCsv[i][j] << ' ';
		//	}
		//	cout << endl;
		// }

		//A Small example


		// Ejecutar el algoritmo con complejidad O(n)
		createCsvFile("maxSubSum1_for_nSize10exp" + to_string(k) + ".csv");
		for (int i = 0; i < parsedCsv.size(); i++)
		{
			maxSubSum4(parsedCsv[i], k);
		}
		// Ejecutar el algoritmo con complejidad O(n log n)
		createCsvFile("maxSubSum3_for_nSize10exp" + to_string(k) + ".csv"); // Posiciones erroneas
		for (int i = 0; i < parsedCsv.size(); i++)
		{
			maxSubSum3(parsedCsv[i], k);
		}
		parsedCsv.clear();
	}

		cout << "Algoritmos O(n) y O(n log2 n) ejecutados!!!" << endl;

	for (int k = 1; k < 5; k++)
	{
		// Leer un archivo .csv y guardar su contenido en arreglos

		fstream data("arraysSize10exp" + to_string(k) + ".csv", ios::in);
		string line;
		while (std::getline(data, line))
		{
			stringstream dataStream(line);
			while (getline(dataStream, cell, ','))
			{
				parsedRow.push_back(stoi(cell));
			}
			parsedCsv.push_back(parsedRow);
			//restart parsedRow vector
			parsedRow.clear();
		}

		//// Ejecutar el algoritmo con complejidad O( n^2)
		createCsvFile("maxSubSum2_for_nSize10exp" + to_string(k) + ".csv"); // Archivo donde se almacenan los resultados del utilizando los datos de entrada dataset1.csv
		for (int i = 0; i < parsedCsv.size(); i++)
		{
			maxSubSum2(parsedCsv[i], k);
		}

		// Ejecutar el algoritmo con complejidad O(n^3)
		createCsvFile("maxSubSum1_for_nSize10exp" + to_string(k) + ".csv"); // Archivo donde se almacenan los resultados del algoritmo utilizando los datos de dataset1.csv
		// NOTA: Los resultados se agregan a maxSubSum1.csv dentro de la función, por lo tanto se debe crear el archivo antes
		for (int i = 0; i < parsedCsv.size(); i++)
		{
			maxSubSum1(parsedCsv[i], k);
		}
		parsedCsv.clear(); // Limpiar el arreglo 2D para que almacene solo el siguiente archivo
	}

	cout << "Algoritmos O(n^2) y O(n^3) ejecutados!!!" << endl;
	
	return 0;
}