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

// Función que genera el dataset
void createCsvFile() 
{
	fstream file;

	// Inicializar la semilla aleatoria
	srand(time(NULL));

	// Abrir o crear un archivo .csv
	file.open("dataset1.csv", ios::out);

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


int main() {
	
	string cell;
	vector<int> parsedRow;
	vector<vector<int>> parsedCsv;
	
	// Ejecutar solo una vez
	// createCsvFile();

	// Leer un archivo .csv y guardar su contenido en arreglos

	ifstream data("dataset1.csv");
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

	return 0;
}