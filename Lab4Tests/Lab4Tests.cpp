#include "pch.h"
#include "CppUnitTest.h"
#include "../Лаба4/Warshall.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
#define INF 9999999 

namespace Lab4Tests
{
	TEST_CLASS(FloydWarshallTests)
	{
	public:
		
		TEST_METHOD(findway_1)
		{
			int matrix[4][4] = { {0,10,14,20},{20,0,40,INF},{INF,35,0,8},{INF,INF,13,0} };
			int** check = new int* [4];
			for (int i = 0; i < 4; i++)
				check[i] = new int[4];
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					check[i][j] = matrix[i][j];
			FloydWarshall(check, 4);
			int path = findway(check, 3, 2);
			Assert::AreEqual(path, 13);
		}
		TEST_METHOD(findway_2)
		{
			int matrix[4][4] = { {0,10,14,20},{20,0,40,INF},{INF,35,0,8},{INF,INF,13,0} };
			int** check = new int* [4];
			for (int i = 0; i < 4; i++)
				check[i] = new int[4];
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					check[i][j] = matrix[i][j];
			FloydWarshall(check, 4);
			int path = findway(check, 1, 3);
			Assert::AreEqual(path, 40);
		}
		TEST_METHOD(findway_3)
		{
			int matrix[4][4] = { {0,10,14,20},{20,0,40,INF},{INF,35,0,8},{INF,INF,13,0} };
			int** check = new int* [4];
			for (int i = 0; i < 4; i++)
				check[i] = new int[4];
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					check[i][j] = matrix[i][j];
			FloydWarshall(check, 4);
			int path = findway(check, 1, 1);
			Assert::AreEqual(path, 0);
		}
		TEST_METHOD(findway_4)
		{
			int matrix[4][4] = { {0,10,14,20},{20,0,40,INF},{INF,35,0,8},{INF,INF,13,0} };
			int** check = new int* [4];
			for (int i = 0; i < 4; i++)
				check[i] = new int[4];
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					check[i][j] = matrix[i][j];
			FloydWarshall(check, 4);
			int path = findway(check, 3, 0);
			Assert::AreEqual(path, 68);
		}
	};
}
