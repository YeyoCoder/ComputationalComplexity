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

using namespace std;

// Función para crear un archivo
void createCsvFile(string fileName)
{
	fstream file;
	file.open(fileName, ios::out);
	file.close();
}


// Función que genera el dataset
void createSubsequenceDataset() 
{
	createCsvFile("dataset1.csv");
	fstream file;
	// Inicializar la semilla aleatoria
	srand(time(NULL));

	// Abrir o crear un archivo .csv
	file.open("dataset1.csv", ios::app);

	// Escribir enteros aleatorios en el archivo
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			file << rand() % 18 - 9;
			if (j < 10)
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

int maxSubSum1(const vector<int>& a)
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
	appendToCsvFile("maxSubSum1.csv", startPosition, finishPosition, maxSum, cpu_time_used);
	return maxSum;
}

int maxSubSum2(const vector<int>& a)
{

	return 0;
}

int main() {
	
	string cell;
	vector<int> parsedRow;
	vector<vector<int>> parsedCsv;
	
	// Ejecutar solo una vez
	// createSubsequenceDataset();

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

	// Ejecutar el algoritmo con complejidad O(n log n)

	// Ejecutar el algoritmo con complejidad O( n^2)

	// Ejecutar el algoritmo con complejidad O(n^3)
	createCsvFile("maxSubSum1.csv"); // Archivo donde se almacenan los resultados del algoritmo utilizando los datos de dataset1.csv
	// NOTA: Los resultados se agregan a maxSubSum1.csv dentro de la función, por lo tanto se debe crear el archivo antes
	for (int i = 0; i < parsedCsv.size(); i++)
	{
		maxSubSum1(parsedCsv[i]);
	}
	//cout << "La suma maxima es " << maxSubSum1(parsedCsv[0]) << endl;
	//maxSubSum1(parsedCsv[1]);
	//maxSubSum1(parsedCsv[2]);

	return 0;
}