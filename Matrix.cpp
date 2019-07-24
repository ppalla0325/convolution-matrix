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
		T get(int row, int column) const;
		void put(int row, int column, T data);

	private:
		///////////////////////////////////////
		///////////////////////////////////////
		//PRIVATE DATA VARIABLES
		///////////////////////////////////////
		///////////////////////////////////////
		/**
		* input matrix that represents an "image" 
		* dynamically allocated at runtime from userinput
		* to perform convolution operation on.
		*/
		T * matrix = null;

		/**
		*  The row size of the matrix
		*/
		int row;

		/**
		* The column size of the matrix
		*/
		int column;

		/////////////////////////////////////////
		//HELPER METHODS
		/////////////////////////////////////////
		int indexMap(int row, int column); 
		int fillRand();
};
