#include <iostream>
#include "Warshall.h"

int main() {
	Map<string, int> map_of_cities;
	read_file(&map_of_cities);
	auto ListOfCities = map_of_cities.get_keys();
	auto matrix = createMatrix(map_of_cities);    //creating a Adj Matrix
	cout << "List of Cities: " << endl;
	auto temp = ListOfCities->first;
	//to see what cities we are looking for
	for (int i = 0; i < ListOfCities->get_size(); i++) {
		while (temp) {
			cout << temp->number << endl;
			temp = temp->next;
		}
	}
	cout << endl;

	auto newMatrix = FloydWarshall(matrix, map_of_cities.get_size());  //creating a matrix of reachability with Floyd-Warshall algorithm

	//entering two names of needed cities 
	string City1, City2;
	cout << "Enter the first city: ";
	getline(cin, City1);
	int ID1 = map_of_cities.FindNode(City1);
	cout << "Enter the second city: ";
	getline(cin, City2);
	int ID2 = map_of_cities.FindNode(City2);
	cout << "The Most Effective way is: " << matrix[ID1][ID2] << endl;
	findway(newMatrix,ID1,ID2); //find a optimal distance between 2 cities
	return 0;
}