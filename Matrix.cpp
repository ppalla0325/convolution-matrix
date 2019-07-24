#include <iostream>
#include <limits>
#include <time.h>  
template <typename T> 
class Matrix { 
public:
	///////////////////////////////////////
	//Constructors and Destructors
	///////////////////////////////////////
	Matrix(int rows, int columns);
	~Matrix();

	///////////////////////////////////////
	//Getters
	///////////////////////////////////////
	T * getMatrix(); 

	///////////////////////////////////////
	//Class specific methods
	///////////////////////////////////////
	T get(int row, int column);
	void put(int row, int column, T data);
	bool isEdge(int row, int column) const;
	T getMin() const;
	T getMax() const;

private:
	///////////////////////////////////////
	//PRIVATE DATA VARIABLES
	///////////////////////////////////////
	/**
	* input matrix that represents an "image" 
	* dynamically allocated at runtime from userinput
	* to perform convolution operation on.
	*/
	T * matrix;

	/**
	*  The row size of the matrix
	*/
	int row;

	/**
	* The column size of the matrix
	*/
	int column;

	/////////////////////////////////////////
	//PRIVATE HELPER METHODS
	/////////////////////////////////////////
	int indexMap(int row, int column); 
	void fillRand();
};

///////////////////////////////////////
//Constructors and Destructors
///////////////////////////////////////
/**
* Constructor
* Description: Initializes the matrix with the given user input
* Implementation: Dynamically allocates an array with the given Data 
* Type and initializes the given row and column data variables
* Preconditions: NONE
* Postconditions: Initializes an Array of size row * column 
* @params rows, the number of rows of the given matrix
* @params columns, the number of columns of the given matrix 
*/
template <typename T> 
Matrix<T>::Matrix(int rows, int columns)
{
	//initialize the row and column variables
	this->row = rows;
	this->column = columns;

	//dynamically allocate the internal array of size = row*column
	int matrixSize = row*column;
	this->matrix = new T[matrixSize];
}

/**
* Destructor
* Description: Deletes the matrix object
* Implementation: Frees the memory from the heap the data variable 'matrix pointer points to'
* Preconditions: NONE
* Postconditions: Deallocates the matrix array from the Heap 
*/
template <typename T> 
Matrix<T>::~Matrix()
{
	//deallocate the matrix pointer from memory
	delete this->matrix;
}

///////////////////////////////////////
//Getters
///////////////////////////////////////
/**
* Description: Allows an outside access into the matrix array.
* Implementation: Returns a pointer to the matrix object.
* Preconditions: NONE
* Postconditions: NONE
* @params NONE
* @returns T*, pointer to matrix array
*/
template <typename T> 
T * Matrix<T>::getMatrix()
{
	return this->matrix;
}

///////////////////////////////////////
//Class specific methods
///////////////////////////////////////
/*
* Description: insert the data into the appropriate mapped index into the matrix array
* Implementation: Calculates the mapped index and places the data in there
* Throws: ERROR 0 - row and column are greater than matrix row and colum variables
* @Preconditions: NONE
* @Postcondtions: At the mapped index in the matrix array, "data" will take its place
* @params: int row, input row from user
* @params: int column, input column from user
* @returns: None
*/
template <typename T> 
void Matrix<T>::put(int row, int column, T data) 
{
	//calculate the mapped index
	int mappedIndex = indexMap(row, column);

	//place the data variable in matrix[mappedIndex]
	this->matrix[mappedIndex] = data;
}

/*
* Description: gets data from the index at given row and column inputs
* Implementation: calls indexMap() method and returns the data at the index from matrix array
* Throws: ERROR 0 - row and column are greater than matrix row and colum variables
* @Preconditions: NONE
* @Postconditions: NONE
* @params: int row, input row from user
* @params: int column, input column from user
* @returns: T, data at the specified index from the matrix array
*/
template <typename T> 
T Matrix<T>::get(int row, int column)
{
	//calculate the mapped index
	int mappedIndex = indexMap(row, column);

	//return the data variable in matrix[mappedIndex]
	return matrix[mappedIndex];
}

/*
* Description: checks to see if the given row and index represent an "edge in the matrix array"
* an "edge" is defined as any index in the "first and last" column AND "first and last" row
* Implementation: checks to see if row is 0 or this->row-1 OR column is 0 or this->column-1
* @Preconditions: NONE
* @Postconditions: NONE
* @params: int row, input row from user
* @params: int column, input column from user
* @returns: bool, indicates whether user is trying to access an "edge"
*/
template <typename T> 
bool Matrix<T>::isEdge(int row, int column) const
{
	//row == 0 -> topmost row of the matrix
	//column == 0 -> leftmost column of the matrix
	//row == this->row-1 -> bottommost row of the matrix
	//columnn == this->column-1 -> rightmost column of the matrix
	if(row == 0 || column == 0 || row == this->row-1 || column == this->column-1)
	{
		return true;
	}
	return false; //none of the aforementioned indices
}

/*
* Description: Returns the minimum value in the matrix.
* Implementation: loops through the matrix array and keeps track
* of the "lowest found so far" value and returns that value in the end
* @Preconditions: NONE
* @Postconditions: NONE
* @params: NONE
* @returns: T, the lowest value in the matric array
*/
template <typename T> 
T Matrix<T>::getMin() const
{
	T lowestFoundSoFar = std::numeric_limits<T>::max();

	//loop through the matrix array and return the lowest value
	for(int i = 0; i < row*column; i++)
	{
		//check to see which value is minimum
		//our stored value or the value in the specified index in the matrix
		lowestFoundSoFar = std::min(lowestFoundSoFar, matrix[i]);
	}
	return lowestFoundSoFar;
}

/*
* Description: Returns the maximum value in the matrix.
* Implementation: loops through the matrix array and keeps track
* of the "greatest found so far" value and returns that value in the end
* @Preconditions: NONE
* @Postconditions: NONE
* @params: NONE
* @returns: T, the greatest value in the matric array
*/
template <typename T> 
T Matrix<T>::getMax() const
{
	T greatestFoundSoFar = std::numeric_limits<T>::min();

	//loop through the matrix array and return the greatest value
	for(int i = 0; i < row*column; i++)
	{
		//check to see which value is greater
		//our stored value or the value in the specified index in the matrix
		greatestFoundSoFar = std::max(greatestFoundSoFar, matrix[i]);
	}
	return greatestFoundSoFar;
}

/////////////////////////////////////////
//PRIVATE HELPER METHODS
/////////////////////////////////////////
/*
* Description: converts the row and column input to the correct corresponding index in the matrix array
* Implementation: To calculate the index of the corresponding row and column query, 
* we use the formula "index = row*this->row + column"
* @Preconditions: Needs instantiated matrix array
* @Postcondtions: NONE
* @params: int row, input row from user
* @params: int column, input column from user
* @returns: int, index mapped to the matrix array
*/
template <typename T> 
int Matrix<T>::indexMap(int row, int column) 
{
	try
	{
		//if the user input row or column goes outside the
		//bounds of the 
		if(row >= this->row || column >= this->column)
		{
			throw 0;
		}
	}
	catch (int x)
	{
		std::cout << "INPUTS found: row = " << row << ", found: column = " 
		<< column << std::endl;
		std::cout << "EXPECTED input row: " << row << " < " << this->row
		<< " AND " << "input column: " << column << " < " << this->column << std::endl;

		std::cout << "ERROR NUMBER: " << x;
	}

	//return the mapped index from user row and column input
	return row*this->row + column;
}

/*
* Description: Populates the matrix with random values of the data type
* Implementation: Initialize a seed random variable and loop through the
* max values of that particular data type
* @Preconditions: NONE
* @Postconditions: matrix array will now be populated with random values
* @params NONE
* @return NONE
*/
template <typename T> 
void Matrix<T>::fillRand()
{
	//set a random seed
	srand(time(NULL));

	//populate the matrix with random values of the given type
	for(int i = 0; i < row*column; i++)
	{
		matrix[i] = rand() % std::numeric_limits<T>::max();
 	}
} 