/*********************************************************************
 ** Program Filename: assignment5.cpp
 ** Author: Lily Shellhammer
 ** Date: 3/5/15
 ** Description: This function creates a 2D dynamic array, fills it with random numbers, and finds the greatest product of shapes created with 4 cells and prints out that value, its position in the array, and the name of the shape with the greatest product.
 ** Input: The number of rows and columns for the dynamic array, or information from a test.txt file (previously created by the user).
 ** Output: The greatest product of shapes created with 4 cells (in a row, adjacent, or diagonal), the position in the array where this shape occurs, and the name of the shape that has the greatest product.
 *********************************************************************/
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>

using namespace std; 

struct greatest_product_info{
	int total;
	int i;
	int j;
	string shape;
};

/*********************************************************************
 ** Function: check_input()
 ** Description: This function checks the user inputted rows and columns and makes sure they are valid integers. It reprompts the user if their input isn't an integer.
 ** Parameters: None
 ** Pre-Conditions: A user has inputted a number of rows and a number of columns. The number hasn't been checked to see if it is an integer.
 ** Post-Conditions: The user inputted number of rows and columns are valid integers.
 *********************************************************************/ 
int check_input(){
	string input;
	int value;

	do{
		value = 0;
		cin >> input;
		for (int i = 0; i < input.length(); i++){ 
			if ( (input[i] < '0') || (input[i] > '9') ){
				cout << "Error! Enter a valid integer number: ";
				value = 0;
				break;
			}
			else{
				value = (value * 10) + (input[i]- '0');
			}
				
		}
	}while(value == 0);
return value;
}

/*********************************************************************
 ** Function: get_user_input()
 ** Description: This functon gets a number of rows and a number of columns inputted from the user and checks that they are valid integers before storing them in the variables rows and columns. The 2D array is defined with this number of rows and columns.
 ** Parameters: This function accesses the integer variable row and the integer variable column.
 ** Pre-Conditions: A dynamic array exists in the program
 ** Post-Conditions: A dynamic array of a user inputted amount of rows and columns (filled with valid integers) exists
 *********************************************************************/ 

void get_user_input(int &rows, int &columns){
	cout << "Enter the number of rows: ";
 	rows = check_input();

 	cout << "Enter the number of columns: ";
	columns = check_input();

}

/*********************************************************************
 ** Function: create_array()
 ** Description: This function creates a dynamic array that can be intialized with a user inputted amount of rows and columns
 ** Parameters: This function accesses and changes the int rows, int columns and the 2D array a.
 ** Pre-Conditions: None
 ** Post-Conditions: A dynamic array (that can be intialized with a user inputted number of rows and columns) exists in the program
 *********************************************************************/ 
int** create_array(int &rows, int &columns, int **a){

	a = new int *[rows]; 

	for (int i = 0; i < rows; i++){
		a[i] = new int [columns];  
	}
	return a;

 }

/*********************************************************************
 ** Function: initialize_array()
 ** Description: This function fills a 2D array (with a user inputted number of rows and columns) with random numbers.
 ** Parameters: This function accesses the value in int rows, int columns and the 2D array a. 
 ** Pre-Conditions: A dynamic array, intialized with a user inputted number of rows and columns, exists in the program.
 ** Post-Conditions: A dynamic array, intialized with a user inputted number of rows and columns, is filled with random numbers.
 *********************************************************************/ 
 int initialize_array(int rows, int columns, int **a){

 	for (int i = 0; i < rows; i++){
 		for (int j = 0; j < columns; j++){
 			a[i][j] = (rand() % 50 + 1);
 		}
 	}
 }

/*********************************************************************
 ** Function: normal_run()
 ** Description: This function runs the program normally when it the program is called only with its name. It calls the functions that create an array with a user inputted number of rows and columns and fills it with random numbers.
 ** Parameters: This function accesses and can change int rows, int columns and the 2D array a.
 ** Pre-Conditions: The user called the program assignment5 without any modifying arguments in the command line: "assignment5"
 ** Post-Conditions: A 2D dynamic array with a user inputted number of rows and columns exists and is filled with random integers.
 *********************************************************************/ 
 int normal_run(int &rows, int &columns, int** &a){

	get_user_input(rows, columns);
	a = create_array(rows, columns, a);  
	initialize_array(rows, columns, a);
}

/*********************************************************************
 ** Function: test_run()
 ** Description: This function runs the program with the infomation stored a matrix saved in a .txt file. This function runs when the user includes -test in the command line.
 ** Parameters: This function accesses and changes the integer variable rows, the integer variable columns, and the 2D array a.
 ** Pre-Conditions: The user called assignment5 with a -test argument and a .txt file to get matrix data from.
 ** Post-Conditions: A 2D array exists and is filled with the .txt file's matrix contents.
 *********************************************************************/ 
int test_run(int &rows, int &columns, int** &a){   //for when user enters command line -test

 	cin >> rows;
 	cin >> columns;

 	a = create_array(rows, columns, a);

 	for(int i=0; i < rows; i++){
 		for(int j=0; j < columns; j++){
 			cin >> a[i][j];
 		}
 	}
 	return 0; 
}

/*********************************************************************
 ** Function: horizontal()
 ** Description: This function finds the greatest product of all possible horizontal shapes (The product of 4 cells in a row)
 ** Parameters: This function accesses int rows, int columns, the 2D array a, and the struct greatest_product_info g.
 ** Pre-Conditions: A 2D array with a user inputted number of rows and columns exists and is filled with random integer numbers.
 ** Post-Conditions: The greatest product of all possible 4-cell horizontal shapes is stored in struct greatest_product_info g if it is greater than the product value currently stored.
 *********************************************************************/ 
int horizontal(int rows, int columns, int **a, greatest_product_info &g){

	int n = 0, x =0, y = 0, z = 0;

	for (int i = 0; i < rows; i++){
 		for (int j = 0; j < (columns-3); j++){
 			n = ((a)[i][j]) * ((a)[i][j+1]) * ((a)[i][j+2]) * ((a)[i][j+3]);
 			if (n > x){
 				x = n;
 				y = i;
 				z = j;
 			}
 		}
 	}
 	if (x > g.total){
 		g.total = x;
 		g.i = y;
 		g.j = z;
 		g.shape = "Horizontal line";
 	}
}

/*********************************************************************
 ** Function: vertical()
 ** Description: This function finds the greatest product of all possible vertical shapes (The product of 4 cells in a row) 
 ** Parameters: This function accesses int rows, int columns, the 2D array a, and the struct greatest_product_info g.
 ** Pre-Conditions: A 2D array with a user inputted number of rows and columns exists and is filled with random integer numbers.
 ** Post-Conditions: The greatest product of all possible 4-cell veritcal shapes is stored in struct greatest_product_info g if it is greater than the product value currently stored.
 *********************************************************************/ 
int vertical(int rows, int columns, int **a, greatest_product_info &g){

	int n = 0, x =0, y = 0, z = 0;

	for (int i = 0; i < (rows-3); i++){
 		for (int j = 0; j < (columns); j++){
 			n = ((a)[i][j]) * ((a)[i+1][j]) * ((a)[i+2][j]) * ((a)[i+3][j]);
 			if (n > x){
 				x = n;
 				y = i;
 				z = j;
 			}
 		}
 	}
 	if (x > g.total){
 		g.total = x;
 		g.i = y;
 		g.j = z;
 		g.shape = "Vertical line";
 	}
}

/*********************************************************************
 ** Function: diagonal_to_right()
 ** Description: This function finds the greatest product of all possible right diagonal lines (The product of 4 cells diagonal starting from the upper right corner and going downwards and to the left)
 ** Parameters: This function accesses int rows, int columns, the 2D array a, and the struct greatest_product_info g.
 ** Pre-Conditions: A 2D array with a user inputted number of rows and columns exists and is filled with random integer numbers.
 ** Post-Conditions: The greatest product of all possible 4-cell right diagonal lines shapes is stored in struct greatest_product_info g if it is greater than the product value currently stored.
 *********************************************************************/ 
int diagonal_to_right(int rows, int columns, int **a, greatest_product_info &g){

	int n = 0, x =0, y = 0, z = 0;

	for (int i = 0; i < (rows-3); i++){
 		for (int j = 0; j < (columns); j++){
 			n = ((a)[i][j]) * ((a)[i+1][j]) * ((a)[i+2][j]) * ((a)[i+3][j]);
 			if (n > x){
 				x = n;
 				y = i;
 				z = j;
 			}
 		}
 	}
 	if (x > g.total){
 		g.total = x;
 		g.i = y;
 		g.j = z;
 		g.shape = "Diagonal line from left to right";
 	}
 
}

/*********************************************************************
 ** Function: diagonal_to_left()
 ** Description: This function finds the greatest product of all possible left diagonal lines (The product of 4 cells diagonal starting from the upper left corner and going downwards and to the right)
 ** Parameters: This function accesses int rows, int columns, the 2D array a, and the struct greatest_product_info g.
 ** Pre-Conditions: A 2D array with a user inputted number of rows and columns exists and is filled with random integer numbers.
 ** Post-Conditions: The greatest product of all possible 4-cell left diagonal shapes is stored in struct greatest_product_info g if it is greater than the product value currently stored.
 *********************************************************************/ 
int diagonal_to_left(int rows, int columns, int **a, greatest_product_info &g){

	int n = 0, x =0, y = 0, z = 0;

	for (int i = 0; i < (rows-3); i++){
 		for (int j = 3; j < columns; j++){
 			n = ((a)[i][j]) * ((a)[i+1][j-1]) * ((a)[i+2][j-2]) * ((a)[i+3][j-3]);
 			if (n > x){
 				x = n;
 				y = i;
 				z = j;
 			}
 		}
 	}
 	if (x > g.total){
 		g.total = x;
 		g.i = y;
 		g.j = z;
 		g.shape = "Diagonal line from right to left";
 	}
}

/*********************************************************************
 ** Function: box()
 ** Description: This function finds the greatest product of all possible box shapes (The product of 4 adjacent cells in a box formation)
 ** Parameters: This function accesses int rows, int columns, the 2D array a, and the struct greatest_product_info g.
 ** Pre-Conditions: A 2D array with a user inputted number of rows and columns exists and is filled with random integer numbers.
 ** Post-Conditions: The greatest product of all possible 4-cell box shapes is stored in struct greatest_product_info g.
 *********************************************************************/ 
int box(int rows, int columns, int **a, greatest_product_info &g){

	int n = 0, x =0, y = 0, z = 0;

	for (int i = 0; i < (rows-1); i++){
 		for (int j = 0; j < (columns-1); j++){
 			n = ((a)[i][j]) * ((a)[i+1][j]) * ((a)[i][j+1]) * ((a)[i+1][j+1]);
 			if (n > x){
 				x = n;
 				y = i;
 				z = j;
 			}
 		}
 	}
 	if (x > g.total){
 		g.total = x;
 		g.i = y;
 		g.j = z;
 		g.shape = "Box";
 	}
}

/*********************************************************************
 ** Function: zig_zag()
 ** Description: This function finds the greatest product of all vertical zig zags lines going from upper left to downward right.
 ** Parameters: This function accesses int rows, int columns, the 2D array a, and the struct greatest_product_info g.
 ** Pre-Conditions: A 2D array with a user inputted number of rows and columns exists and is filled with random integer numbers.
 ** Post-Conditions: The greatest product of all vertical left 4-cell zig_zag shapes is stored in struct greatest_product_info g if it is greater than the product value currently stored.
 *********************************************************************/ 
int zig_zag_up_left(int rows, int columns, int **a, greatest_product_info &g){

	int n = 0, x =0, y = 0, z = 0;

	//zig zag upward, left to right
	for (int i = 0; i < (rows-2); i++){
 		for (int j = 0; j < (columns-1); j++){
 			n = ((a)[i][j]) * ((a)[i+1][j]) * ((a)[i+1][j+1]) * ((a)[i+2][j+1]);
 			if (n > x){
 				x = n;
 				y = i;
 				z = j;
 			}
 		}
 	}
 	if (x > g.total){
 		g.total = x;
 		g.i = y;
 		g.j = z;
 		g.shape = "A upward pointing zig zag line going from left to right";
 	}
 }

/*********************************************************************
 ** Function: zig_zag_up_right()
 ** Description: This function finds the greatest product of all vertical zig zags lines going from upward right to downward left.
 ** Parameters: This function accesses int rows, int columns, the 2D array a, and the struct greatest_product_info g.
 ** Pre-Conditions: A 2D array with a user inputted number of rows and columns exists and is filled with random integer numbers.
 ** Post-Conditions: The greatest product of all vertical right 4-cell zig_zag shapes is stored in struct greatest_product_info g if it is greater than the product value currently stored.
 *********************************************************************/ 
int zig_zag_up_right(int rows, int columns, int **a, greatest_product_info &g){

	int n = 0, x =0, y = 0, z = 0;

 	//zig zag upward, right to left
 	for (int i = 0; i < (rows-2); i++){
 		for (int j = 1; j < columns; j++){
 			n = ((a)[i][j]) * ((a)[i+1][j]) * ((a)[i+1][j-1]) * ((a)[i+2][j-1]);
 			if (n > x){
 				x = n;
 				y = i;
 				z = j;
 			}
 		}
 	}
 	if (x > g.total){
 		g.total = x;
 		g.i = y;
 		g.j = z;
 		g.shape = "A upward pointing zig zag line going from right to left";
 	}
}

/*********************************************************************
 ** Function: zig_zag_side_down()
 ** Description: This function finds the greatest product of all horizontal zig zags lines going from downward left to upward right.
 ** Parameters: This function accesses int rows, int columns, the 2D array a, and the struct greatest_product_info g.
 ** Pre-Conditions: A 2D array with a user inputted number of rows and columns exists and is filled with random integer numbers.
 ** Post-Conditions: The greatest product of all horizontal down to up 4-cell zig_zag shapes is stored in struct greatest_product_info g if it is greater than the product value currently stored.
 *********************************************************************/ 
int zig_zag_side_down(int rows, int columns, int **a, greatest_product_info &g){

	int n = 0, x =0, y = 0, z = 0;

 	//zig zag sideways, down to up
 	for (int i = 1; i < rows; i++){
 		for (int j = 0; j < (columns-2); j++){
 			n = ((a)[i][j]) * ((a)[i][j+1]) * ((a)[i-1][j+1]) * ((a)[i-1][j+2]);
 			if (n > x){
 				x = n;
 				y = i;
 				z = j;
 			}
 		}
 	}
 	if (x > g.total){
 		g.total = x;
 		g.i = y;
 		g.j = z;
 		g.shape = "A sidways zig zag line going from bottom to top";
 	}
}

/*********************************************************************
 ** Function: zig_zag_side_up()
 ** Description: This function finds the greatest product of all horizontal zig zags lines going from upward left to downward right.
 ** Parameters: This function accesses int rows, int columns, the 2D array a, and the struct greatest_product_info g.
 ** Pre-Conditions: A 2D array with a user inputted number of rows and columns exists and is filled with random integer numbers.
 ** Post-Conditions: The greatest product of all horizontal up to down 4-cell zig_zag shapes is stored in struct greatest_product_info g if it is greater than the product value currently stored.
 *********************************************************************/ 
int zig_zag_side_up(int rows, int columns, int **a, greatest_product_info &g){

	int n = 0, x =0, y = 0, z = 0;

 	//zig zag sideways, up to down
 	for (int i = 0; i < (rows-3); i++){
 		for (int j = 0; j < (columns-1); j++){
 			n = ((a)[i][j]) * ((a)[i][j+1]) * ((a)[i+1][j+1]) * ((a)[i+1][j+2]);
 			if (n > x){
 				x = n;
 				y = i;
 				z = j;
 			}
 		}
 	}
 	if (x > g.total){
 		g.total = x;
 		g.i = y;
 		g.j = z;
 		g.shape = "A sideways zig zag line going from top to bottom";
 	}
}

/*********************************************************************
 ** Function: L_shape()
 ** Description: This function finds the greatest product of all upward L-shapes.
 ** Parameters: This function accesses int rows, int columns, the 2D array a, and the struct greatest_product_info g.
 ** Pre-Conditions: A 2D array with a user inputted number of rows and columns exists and is filled with random integer numbers.
 ** Post-Conditions: The greatest product of all upward 4 cell L-shapes is stored in struct greatest_product_info g if it is greater than the product value currently stored.
 *********************************************************************/ 
int L_shape(int rows, int columns, int **a, greatest_product_info &g){

	int n = 0, x =0, y = 0, z = 0;
	//For an L shape
	for (int i = 0; i < (rows-2); i++){
 		for (int j = 0; j < (columns-1); j++){
 			n = ((a)[i][j]) * ((a)[i+1][j]) * ((a)[i+2][j]) * ((a)[i+2][j+1]);
 			if (n > x){
 				x = n;
 				y = i;
 				z = j;
 			}
 		}
 	}
 	if (x > g.total){
 		g.total = x;
 		g.i = y;
 		g.j = z;
 		g.shape = "An L shape";
 	}
}

/*********************************************************************
 ** Function: L_shape_down()
 ** Description: This function finds the greatest product of all upside down L-shapes.
 ** Parameters: This function accesses int rows, int columns, the 2D array a, and the struct greatest_product_info g.
 ** Pre-Conditions: A 2D array with a user inputted number of rows and columns exists and is filled with random integer numbers.
 ** Post-Conditions: The greatest product of all upside down 4 cell L-shapes is stored in struct greatest_product_info g if it is greater than the product value currently stored.
 *********************************************************************/ 
int L_shape_down(int rows, int columns, int **a, greatest_product_info &g){

	int n = 0, x =0, y = 0, z = 0;
 	//For an upside down L shape
 	for (int i = 0; i < (rows-2); i++){
 		for (int j = 0; j < (columns-1); j++){
 			n = ((a)[i][j]) * ((a)[i][j+1]) * ((a)[i+1][j]) * ((a)[i+2][j]);
 			if (n > x){
 				x = n;
 				y = i;
 				z = j;
 			}
 		}
 	}
 	if (x > g.total){
 		g.total = x;
 		g.i = y;
 		g.j = z;
 		g.shape = "An L shape";
 	}
}

/*********************************************************************
 ** Function: L_shape_mirrored()
 ** Description: This function finds the greatest product of all mirrored L-shapes.
 ** Parameters: This function accesses int rows, int columns, the 2D array a, and the struct greatest_product_info g.
 ** Pre-Conditions: A 2D array with a user inputted number of rows and columns exists and is filled with random integer numbers.
 ** Post-Conditions: The greatest product of all mirrored 4 cell L-shapes is stored in struct greatest_product_info g if it is greater than the product value currently stored.
 *********************************************************************/ 
int L_shape_mirrored(int rows, int columns, int **a, greatest_product_info &g){

	int n = 0, x =0, y = 0, z = 0;
 	// For a mirrored L shape
 	for (int i = 0; i < (rows-2); i++){
 		for (int j = 1; j < columns; j++){
 			n = ((a)[i][j]) * ((a)[i+1][j]) * ((a)[i+2][j]) * ((a)[i+2][j-1]);
 			if (n > x){
 				x = n;
 				y = i;
 				z = j;
 			}
 		}
 	}
 	if (x > g.total){
 		g.total = x;
 		g.i = y;
 		g.j = z;
 		g.shape = "An L shape";
 	}
}

/*********************************************************************
 ** Function: L_shape_mirrored_down()
 ** Description: This function finds the greatest product of all upside down, mirrored L-shapes.
 ** Parameters: This function accesses int rows, int columns, the 2D array a, and the struct greatest_product_info g.
 ** Pre-Conditions: A 2D array with a user inputted number of rows and columns exists and is filled with random integer numbers.
 ** Post-Conditions: The greatest product of all upside down, mirrored 4 cell L-shapes is stored in struct greatest_product_info g if it is greater than the product value currently stored.
 *********************************************************************/ 
int L_shape_mirrored_down(int rows, int columns, int **a, greatest_product_info &g){

	int n = 0, x =0, y = 0, z = 0;
 	//For a mirrored, upside down L shape
 	for (int i = 0; i < (rows-2); i++){
 		for (int j = 0; j < (columns-1); j++){
 			n = ((a)[i][j]) * ((a)[i][j+1]) * ((a)[i+1][j+1]) * ((a)[i+2][j+1]);
 			if (n > x){
 				x = n;
 				y = i;
 				z = j;
 			}
 		}
 	}
 	if (x > g.total){
 		g.total = x;
 		g.i = y;
 		g.j = z;
 		g.shape = "An L shape";
 	}
}

/*********************************************************************
 ** Function: intialize_g()
 ** Description: This function sets the intital variable values in the struct greatest_product_info g.
 ** Parameters: This function accesses and can change the struct greatest_product_info g.
 ** Pre-Conditions: A struct greatest_product_info g exists and contains an int total, int i, int j, and string shape.
 ** Post-Conditions: A struct greatest_product_info g exists and contains an int total, int i, int j, and string shape, which all have intilalized values.
 *********************************************************************/ 
void initialize_g (greatest_product_info &g){
	g.total = 0;
	g.i = 0;
	g.j = 0;
	g.shape = " ";
}

/*********************************************************************
 ** Function: call_shape_functions()
 ** Description: This function calls all of the functions that find and compare the greatest product of 4 cell shapes.
 ** Parameters: This function accesses int rows, int columns, the 2D array a, and the struct greatest_product_info g.
 ** Pre-Conditions: A 2D array with a user inputted number of rows and columns exists and is filled with random numbers.
 ** Post-Conditions: The greatest product of 4 cell shapes is stored (along with its position in the array and shape name) in the struct greatest_product_info g.
 *********************************************************************/ 
int call_shape_functions(int &rows, int &columns, int **a, greatest_product_info &g){   

	box(rows, columns, a, g);
 	horizontal(rows, columns, a, g);
 	diagonal_to_right(rows, columns, a, g);
 	diagonal_to_left(rows, columns, a, g);
 	vertical(rows, columns, a, g);

 	zig_zag_up_left(rows, columns, a, g);
 	zig_zag_side_up(rows, columns, a, g);
 	zig_zag_side_down(rows, columns, a, g);
 	zig_zag_up_right(rows, columns, a, g);

 	L_shape(rows, columns, a, g);
 	L_shape_mirrored(rows, columns, a, g);
 	L_shape_down(rows, columns, a, g);
 	L_shape_mirrored_down(rows, columns, a, g);
 }

/*********************************************************************
 ** Function: print_function()
 ** Description: This functon prints out the matrix by printing each cell in the array.
 ** Parameters: This function accesses the values in int row and the int column.
 ** Pre-Conditions: A dynamic array of a user inputted amount of rows and columns (filled with valid integers) exists
 ** Post-Conditions: A dynamic array of a user inputted amount of rows and columns (filled with valid integers) exists and is printed out.
 *********************************************************************/ 

int print_function(int &rows, int &columns, int **a){    //Print out matrix

	for (int i = 0; i < rows; i++){
 		for (int j = 0; j < columns; j++){
 			cout << a[i][j] << "  ";
 		}
 		cout << " " << endl;
 	} 
}

void delete_fn(int rows, int cols, int**a){
	for (int i = 0; i < rows; i++)
	{
		delete [] a[i];
	}
	delete [] a;
}

/*********************************************************************
 ** Function: main()
 ** Description: This is the main function that calls either the normal run function or the test run function (depending on how many valid arguments the user inputs) and the check shape function. It outputs the greatest product of the 4-cell shapes, its position in the array and the name of the shape.
 ** Parameters: This function accesses the arguments that the user entered in the command line.
 ** Pre-Conditions: None.
 ** Post-Conditions: A 2D array, defined by the user and filled with random numbers, exists and the greatest product of 4-cell shapes at any position in the array is printed out, along with its position in the array and the name of the type of shape.
 *********************************************************************/ 
int main(int argc, char *(argv[])){

	int rows, columns, **a;
	greatest_product_info g;
	initialize_g(g);

	if (argc == 1){    //Check run type (-test vs. normal run)
		normal_run(rows, columns, a);
	}
	if (argc > 1){
		if ((strcmp(argv[1], "-test") == 0)){    //do I need this??

			test_run(rows, columns, a);

		}
		else {
			cout << "You didn't call -test properly. Enter another command line: ";
			exit(0);
		}
	}

 	print_function(rows, columns, a);
 	call_shape_functions(rows, columns, a, g);

 	cout << "Max Prod: " << g.total << " Position: row " << g.i << ", col " << g.j << " Shape: " << g.shape << endl; 
 	delete_fn(rows, columns, a);
 	return 0; 
}  