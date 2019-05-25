#pragma once
#include "RedBlackTree.h"
#include <string>
#include <fstream>

using namespace std;
enum INF {INF = 9999999}; //making a INFEMUM distannce

void read_file(Map<string,int>* map_of_cities)
{
	fstream inFile;
	string buffer_string;
	inFile.open("Sample.txt", ios::in);
	int id = 0;
	do
	{
		int cnt = 0;
		getline(inFile, buffer_string);
		while (cnt != 2)
		{
			size_t found = buffer_string.find(';');             //while not first ';'
			auto ExistingNode = map_of_cities->FindNode(buffer_string.substr(0, found));
			if (ExistingNode == -1) { //if there's no that element
				map_of_cities->insertnode(buffer_string.substr(0, found), id);  //insert name as key, id as value
				id++;
				cnt++;
			}
			else { cnt++; }
			buffer_string.erase(0, found + 1); //erase everything before first ; with it
		}

	} while (!inFile.eof());

	inFile.close();
}

int** createMatrix(Map<string, int> map_of_cities)
{
	int GraphSize = map_of_cities.get_size();
	int** matrix = new int* [GraphSize];
	for (int i = 0; i < GraphSize; i++)
		matrix[i] = new int[GraphSize];
	for (int i = 0; i < GraphSize; i++) {
		for (int j = 0; j < GraphSize; j++) {
			if (i == j) {
				matrix[i][j] = 0;
			}
			else matrix[i][j] = INF;		//make everything except diagonal of matrix as infemum to avoid mistakes
		}
	}
	fstream inFile;
	string buffer_string;
	inFile.open("Sample.txt", ios::in);
	do
	{
		getline(inFile, buffer_string);
		size_t found = buffer_string.find(';');
		int row = map_of_cities.FindNode(buffer_string.substr(0, found));			//find an id of needed cities then erase it from string
		buffer_string.erase(0, found + 1);
		int column = map_of_cities.FindNode(buffer_string.substr(0, buffer_string.find(';')));
		found = buffer_string.find(';');
		buffer_string.erase(0, found + 1);
		found = buffer_string.find(';');

		if (buffer_string.substr(0, found) != "N/A") {						//write 
			matrix[row][column] = stoi(buffer_string.substr(0, found));
		}
		else matrix[row][column] = INF;
		buffer_string.erase(0, found + 1);

		if (buffer_string.substr(0, buffer_string.length()) != "N/A") {
			matrix[column][row] = stoi(buffer_string.substr(0, buffer_string.length()));
		}
		else matrix[column][row] = INF;
	} while (!inFile.eof());

	inFile.close();
	return matrix;
}

int** FloydWarshall(int** matrix, size_t size) {
	for (int k = 0; k < size; k++) {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (matrix[i][k] != 0 && matrix[j][k] != 0 && matrix[i][j] > (matrix[i][k] + matrix[k][j])) {
					matrix[i][j] = matrix[i][k] + matrix[k][j];
				}
			}
		}
	}
	return matrix;
}

int findway(int **matrix, int id1, int id2) {
	return matrix[id1][id2];
}