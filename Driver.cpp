#include "Matrix.cpp"

/**
*
*
*
*/
int main()
{
	Matrix<unsigned char> input(2,4); //unsigned char data type, 3 rows and 2 columns.

	unsigned char toAdd = 69;
	input.put(0,0,toAdd);
	input.put(0,1,toAdd);
	//input.put(1,4,toAdd);
	input.printMatrix();
	return 0;
}