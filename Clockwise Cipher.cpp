#include <iostream>
#include <string>
#include <cmath>

int level = 0;

using namespace std;

int iterate_func(char** matrix, char* s, int rowsOfficial, int stringCount, int size) {

	--rowsOfficial;
	int first = 0, a = 0, b = rowsOfficial, c = 0;

	
	int necessaryIterations = rowsOfficial - (level*2); //Necessary iterations for the outside of the matrix
	if (necessaryIterations == 3 && (rowsOfficial % 2 == 0)) {
		necessaryIterations = 2; //In case the matrix is 3x3, we need to run it only 2 times and not (rowsOfficial - level) times
	}
	

	for (int i = necessaryIterations; i > 0; --i) {
		
		if (size == stringCount) { break; }
		matrix[first + level][c + level] = s[stringCount];
		stringCount++;

		if (size == stringCount) { break; }
		matrix[a + level][rowsOfficial - level] = s[stringCount];
		stringCount++;

		if (size == stringCount) { break; }
		matrix[rowsOfficial - level][b - level] = s[stringCount];
		stringCount++;

		if (size == stringCount) { break; }
		matrix[b - level][first + level] = s[stringCount];
		stringCount++;

		a++;
		b--;
		c++;
		
	}

	return stringCount;

}

void fill_matrix(char** matrix, char* s, int rows, int size) {

	int stringCount = 0, iterations = (int)ceil(rows / 2); //There are ceil(size/2) necessary iterations to fill the matrix clockwise
	int half = (int)ceil(rows / 2), officialRows = rows;
	int flag = rows % 2;

	for (int i = iterations; i > 0; --i) {

		stringCount = iterate_func(matrix, &s[0], officialRows, stringCount, size);
		++level;
		
	}

	if (flag == 1) {
		matrix[half][half] = s[size - 1];
	}

}

void print_matrix(char** matrix, int size) {

	for (int i = 0; i < size; ++i) {

		for (int j = 0; j < size; ++j) {
			cout << matrix[i][j];
		}
		cout << endl;

	}

	cout << endl;

}

void print_encrypted(char** matrix, int rows) {

	cout << "The encrypted message is:" << endl;
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < rows; ++j) {
			cout << matrix[i][j];
		}
	}
	cout << endl;

}

void free_matrix(char** matrix, int rows) {
	for (int i = 0; i < rows; ++i)
		delete[] matrix[i];
	delete[] matrix;
}

void encrypt_start(string s, const int size) {

	int rows = (int)ceil(sqrt(size)); //Round up the square root of the size to know the size of the row of the quadratic matrix
	int cols = rows;

	char** matrix = new char* [rows]; //Dinamically allocate the matrix
	for (int i = 0; i < rows; ++i) {
		matrix[i] = new char[cols];
	}
	
	fill_matrix(matrix, &s[0], rows, size);

	print_matrix(matrix, rows);

	print_encrypted(matrix, rows);

	free_matrix(matrix, rows);

}

int main()
{
	string s;
	cout << "Insert the string" << endl;
	getline(cin, s);

	char choose;
	cout << "Decide if you want to Encrypt (e) or Decrypt (d) the message" << endl;
	cin >> choose;

	encrypt_start(s, size(s));


	//In case someone wants to add the decryption mode
	/*
	switch (choose) {

	case 'e':

		encrypt_start(s, size(s));
		break;

	case 'd':

		break;

	default:
		break;

	}
	*/

	return 0;
}

//The idea was to find a mathematical solution to such problem. After trying various iterations, I found out that the best direct
//way to make this work was the use of iterate_func(). It works like this:
//1. Given the size of the string, make the ceiling of sqrt(size) to know the minimun rows and cols needed for the matrix (it's quadratic)
//2. int iterations tells how many submatrixes there are, therefore how many times an iteration is needed to input the characters
//3. All iterations need to insert (rows-1)*4 numbers, because there are 4 corners and (rows-1) positions on a row (the first one excluded).
//4. The int level keeps track of the level of the sub-matrix, a 6x6 matrix has 3 levels: 6x6, 4x4, 2x2 ; a 3x3 matrix has 2 levels: 3x3, 1x1
//5. The iterate_func() will run 'iterations' times, each time will insert ('considerated-matrix/sub.matrix'Rows - 1)*4 characters
//6. At the end the program will output the matrix in its current state