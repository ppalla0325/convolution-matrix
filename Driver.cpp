#include "Matrix.cpp"
#include <string>
#include <map> 
#include <chrono> 
using namespace std::chrono; 

/*
* Given Instructions
*/
// 1. Read rows and columns (cols) as integer arguments from the command line.
// 2. Create an unsigned char matrix M of size [rows x cols] (if your language of choice does not support the unsigned char type, upgrade the type to the shortest integer type supported by that language).
// 3. Fill M with randomly selected non-negative integers.
// 4. Apply the filter K=[-1, 0, 1] along the rows axis, then the cols axis (i.e. convolve the matrix M with K along the vertical & horizontal axis respectively).
// 5. Store the vertical convolution result computed above in a new matrix Dy and the horizontal convolution result in Dx. You must explicitly compute and store the Dy & Dx matrices. 
// 6. Print the total time taken by the machine in computing Dx and Dy matrices.
// 7. Compute the min and max values for both Dx & Dy matrices individually (and in separate functions from the above computation of Dx and Dy). Print the computed min & max values.
/*
* End of Given Instructions
*/

/**
* Map to store and access the rows and columns inputted by the user
*/
std::map<std::string, int> user_input;

/*
* Description: Get the number of rows and column size of our matrix from the user.
* Implementation: Prompt user for the row and column size and check to see if the input works
* @Preconditions: NONE
* @Postcondtions: user_input map will have 2 keys "rows" = numOfRows and "columns" = numOfColumns
* @params: int row, input row from user
* @params: int column, input column from user
* @returns: None
*/
void userinput()
{
	int rows;
	int columns;
	char toPrint;
	//grab user input
	std::cout << "enter number of rows: ";
	std::cin >> rows;
	std::cout << "enter number of columns: ";
	std::cin >> columns;
	std::cout << "enter 'y' if u want to print M, Dx, and Dy, 'n' for don't print: ";
	std::cin >> toPrint;
	//at this point we have to check for bad user input

	//if the user has inputted a negative number
	while(rows < 1 || columns < 1)
	{
		std::cout << "cannot have rows or column length to be less than 1" << std::endl;
		std::cout << "enter number of rows: ";
		std::cin >> rows;
		std::cout << "enter number of columns: ";
		std::cin >> columns;
	}
	//loops until we have correct user input

	//insert the user input to our map
	user_input.insert({ "rows", rows });
	user_input.insert({ "columns", columns });
	user_input.insert({ "toPrint", (toPrint == 'y') ? 1 : 0});
}

/*
* Description: Prints M, Dx, and Dy in "row x column" form
* Implementation: if the user inputted 'y', then function will invoke and call 
* printMatrix() of the Matrix object, if not then it won't invoke.
* @Preconditions: NONE
* @Postcondtions: console shows the printed values of the matrices
* @params Matrix M, convolve with filter [-1, 0, 1] on horizontal and vertical axis
* @params Matrix Dx, covolution result of filter [-1, 0, 1] on horizontal axis
* @params Matrix Dy, covolution result of filter [-1, 0, 1] on vertical axis
* @returns: None
*/
void print(Matrix<unsigned char> & M, Matrix<short int> & Dx, Matrix<short int> & Dy)
{
	//print M first
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "Matrix M " << std::endl;
	M.printMatrix(); 

	//print Dx
	std::cout << std::endl;
	std::cout << "Matrix Dx " << std::endl;
	Dx.printMatrix(); 

	//print Dy
	std::cout << std::endl;
	std::cout << "Matrix Dy " << std::endl;
	Dy.printMatrix(); 
}

/*
* Description: Calculate the horizontal and vertical convolultion result using filter [-1, 0, 1]
* and store the resultant horizontal result in Dx and resultant vertical result in Dy
* Implementation: for-loop implementation taking O(n) time to calculate the left and right 
* sum. loop through each index of Matrix M and calculate Dx convolution and Dy convolution
* and store them in the approriate index. 
* EDGE CASE HANDLING: To deal with the edges of the matrix, we employ "WRAP-AROUND"
* The reason for "WRAP-AROUND" is that I expect that matrices resemble around* the same values
* on one-side of the edge as the other.
*
* Dx EDGE-CASE: For Dx edge-case, the edges are one the leftmost column and the rightmost column.
* For the leftmost column, we need to assume a postive '1' value, so we take it from the rightmost column same row.
* imagine like a wrap around, taking the matrix and bending it on the vertical axis so that the left and right edges touch.
* For the rightmost column, we do the exact same thing but make the '-1' assumption for the leftmost column same row.
*
* Dy EDGE-CASE: For Dy edge-case, the edges are the topmost and bottommost row. This is the top and bottom row respectively.
* When we convolve on the topmost row, our '-1' filter value will be the bottommost row same column
* When we convolve on the bottommost row, our '1' filter value will be the topmost row same column
* Employ the same assumption of the Wrap-Around method, assume that the matrix is like a picture and bend it across the 
* horizontal access so that the topmost and bottommost rows touch.
*
* Preconditions: NONE
* Postconditions: Dx and Dy will hold the respective horizontal and vertical convolution.
* @params Matrix M, convolve with filter [-1, 0, 1] on horizontal and vertical axis
* @params Matrix Dx, covolution result of filter [-1, 0, 1] on horizontal axis
* @params Matrix Dy, covolution result of filter [-1, 0, 1] on vertical axis
* @return NONE
*/
void convolve(Matrix<unsigned char> & M, Matrix<short int> & Dx, Matrix<short int> & Dy)
{
	//calculate time taken by program
	//start counting
	auto start = high_resolution_clock::now(); 

	//Value after summing the filter neighbors
	short int xValAccumalator;
	short int yValAccumalator;
	//mirror value to deal with value being at edges of matrix
	short int xMirror;
	short int yMirror;

	//loop through the matrix, calculate the convolution result for Dx and Dy
	//by summing the neighbors of M with the given filter kernel [-1, 0, 1]
	//and store the value in Dx and Dy which are passed in by references
	for(int i = 0; i < user_input["rows"]; i++)//start the outer loop at first row and make our way down
	{
		for(int j = 0; j < user_input["columns"]; j++)// for each row, loop through each value
		{
			// first calculate Dx and then calculate Dy
			// Start of Dx calculation
			if(M.leftEdge(i, j))// Dx calculation, value is on the leftmost edge so our "assumed -1 filter is the rightmost-edge mirror"
			{
				xMirror = M.get(i, user_input["columns"]-1); //mirror value is on 'same row' and last column
				xValAccumalator = (-1*xMirror) + M.get(i, j+1);
				Dx.put(i, j, xValAccumalator);
			}
			else if(M.rightEdge(i, j))// Dx calculation, value is the rightmost edge so our "assumed 1 filter is the leftmost-edge mirror"
			{
				xMirror = M.get(i, 0); //mirror value is on 'same row' and 0th column
				xValAccumalator = (-1*M.get(i, j-1)) + xMirror;
				Dx.put(i, j, xValAccumalator);
			}
			else// calculate the Dx value normally [-1, 0, 1] as the filter values exist -- no assuming values (not at critical edge)
			{
				xValAccumalator = (-1*M.get(i, j-1)) + M.get(i, j+1); //no edge case, -1*left of index + right of index = new value of index at Dx
				Dx.put(i, j, xValAccumalator);
			}
			//End of Dx calculation
			/*
			* 
			*/
			// Start of Dy calculation
			if(M.topEdge(i, j))// Dy Calculation, value is on the topmost edge so our assumed -1 filter is the bottommost-edge mirror"
			{
				yMirror = M.get(user_input["rows"]-1, j);//y Mirror for the '-1' counterpart on the filter will be on the bottommost edge on the same column
				yValAccumalator = (-1*yMirror) + M.get(i+1, j);
				Dy.put(i, j, yValAccumalator);
			}
			else if(M.bottomEdge(i, j))// Dy Calculation, value is on the bottommost edge so our assumed 1 filter is the topmost-edge mirror"
			{
				yMirror = M.get(0, j);// yMirror for the '1' counterpart is on the same column on the 0th row
				yValAccumalator = (-1*M.get(i-1, j)) + yMirror;
				Dy.put(i, j, yValAccumalator);
			}
			else// calculate the Dx value normally [-1, 0, 1] as the filter values exist -- no assuming values (not at critical edge)
			{
				yValAccumalator = -1*M.get(i-1, j) + M.get(i+1, j);
				Dy.put(i, j, yValAccumalator);
			}
			// End of Dy calculation
		}
	}

	// end time count
	auto stop = high_resolution_clock::now();
	auto timeTaken = duration_cast<microseconds>(stop - start);

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "Time taken by convolution function: " << timeTaken.count() << " microseconds" << std::endl;

	// print the matrix if the user asks to print
	if(user_input["toPrint"]) print(M, Dx, Dy); 
}

int main()
{
	//1. gather user input
	userinput(); 
	//2. instantiate a matrix of size = rows x columns
	Matrix<unsigned char> M(user_input["rows"], user_input["columns"]);
	//instantiate Dx and Dy to be of short ints to hold the negative values occuring
	//when you applying convolution method.
	Matrix<short int> Dx(user_input["rows"], user_input["columns"]);
	Matrix<short int> Dy(user_input["rows"], user_input["columns"]);


	//3. through Matrix member function fillRand(), M is filled with random unsigned chars 
	//4. Applied convolution on x-axis and y-axis
	//5. Stored results from step-4 in Dx and Dy
	//6. Calculated time taken by convolution function
	convolve(M, Dx, Dy);
	
	//7. Calculate the Min and Max of Dx and Dy matrix
	std::cout << std::endl;
	std::cout << "x_max: " << Dx.getMax() << std::endl;
	std::cout << "x_min: " << Dx.getMin() << std::endl;
	std::cout << "y_max: " << Dy.getMax() << std::endl;
	std::cout << "y_min: " << Dy.getMin() << std::endl;
}