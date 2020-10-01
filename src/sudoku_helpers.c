#include <stdio.h>

/* Each of the n elements of array elements, is the address of an
 * array of n integers.
 * Return 0 if every integer is between 1 and n^2 and all
 * n^2 integers are unique, otherwise return 1.
 */

int check_group(int **elements, int n) {

	int *first_three = elements[0];
	int *second_three = elements[1];
	int *last_three = elements[2];
	int all_nine[9];

    for (int i = 0; i < n; i++) {
    	all_nine[i] = first_three[i];
    	all_nine[i+3] = second_three[i];
    	all_nine[i+6] = last_three[i];
    }

 	// Check if all integers in array are unique.
 	// Credit for algorithm.
 	// https://www.dreamincode.net/forums/topic/87748-finding-if-elements-in-array-are-distinct/
 	int l; 
 	int k; 
 	int ogi_val = 0; 
 	int new_val = 0;

	for (l = 0; l < 9; l++) {
		ogi_val = all_nine[l];

		for (k = l+1; k < 10; k++) {

			if (ogi_val == all_nine[k]) {
				new_val = 1;
			}
		}	
	}
	if (new_val == 1) {
		return 1;
	}
	return 0;
}

/* puzzle is a 9x9 sudoku, represented as a 1D array of 9 pointers
 * each of which points to a 1D array of 9 integers.
 * Return 0 if puzzle is a valid sudoku and 1 otherwise. You must
 * only use check_group to determine this by calling it on
 * each row, each column and each of the 9 inner 3x3 squares
 */

int check_regular_sudoku(int **puzzle) {

	int first_three[3];
    int second_three[3];
    int last_three[3];
    int *arr_ptr[3];

    // Uniqueness in rows.
    int *a_row;

    // Select a row from the puzzle
	for (int row_indx = 0; row_indx < 9; row_indx++) {
		
		// Assign row to a varialbe
		for (int count = 0; count < 9; count++) {
			
			a_row = puzzle[row_indx];

			// Break each row into a 3 columns/ subrows
		    for (int i = 0; i < 9; i++) {

		    	if(i<3) {
		    		first_three[i%3] = a_row[i];
		    	}

		    	if(i>=3 && i<6) {
		    		second_three[i%3] = a_row[i];
		    	}

		    	if(i>=6 && i<9) {
		    		last_three[i%3] = a_row[i];
		    	}
		        
		    }

		    // Add each pointer each sub row
		    // to an array to array of pointers
		    arr_ptr[0] = first_three;
		    arr_ptr[1] = second_three;
		    arr_ptr[2] = last_three;


    	}

    		// Call to check group if all numbers 
    		// in row row_index are unique.
			if(check_group(arr_ptr, 3)) {
    			return 1;
    		}
	}
	
	// Uniqueness in columns.
	int *a_col;

	// Select column col_indx in a row
	for (int col_indx = 0; col_indx < 9; col_indx++) {

		// Select row at row_indx
		for (int row_indx = 0; row_indx < 9; row_indx++ ) {

		a_col = puzzle[row_indx];
		if (row_indx < 3) {
			first_three[row_indx%3] = a_col[col_indx];
		}

		if (row_indx < 6) {
			second_three[row_indx%3] = a_col[col_indx];
		}

		if (row_indx < 9) {
			last_three[row_indx%3] = a_col[col_indx];
		}
	}

	// Add each pointer ro each sub column
	// to an array to array of pointers
	arr_ptr[0] = first_three;
    arr_ptr[1] = second_three;
    arr_ptr[2] = last_three;

    // Call to check group if all numbers 
    // in row row_index are unique.
    if(check_group(arr_ptr, 3)) {
    			return 1;
    		}

	}

	//Uniquness in boxes

	int *a_box1;
	int *a_box2;
	int *a_box3;

	for (int box_indx = 0; box_indx < 9; box_indx++) {
		if (box_indx < 3) {
			a_box1 = puzzle[0];
			a_box2 = puzzle[1];
			a_box3 = puzzle[2];
		}

		if (box_indx >= 3 && box_indx < 6) {
			a_box1 = puzzle[3];
			a_box2 = puzzle[4];
			a_box3 = puzzle[5];
		}

		if (box_indx >= 6) {
			a_box1 = puzzle[6];
			a_box2 = puzzle[7];
			a_box3 = puzzle[8];
		}

		// Build box at box_indx
		first_three[0] = a_box1[3*(box_indx%3)]; first_three[1] = a_box1[3*(box_indx%3) + 1]; first_three[2] = a_box1[3*(box_indx%3) + 2];
		second_three[0] = a_box2[3*(box_indx%3)]; second_three[1] = a_box2[3*(box_indx%3) + 1]; second_three[2] = a_box2[3*(box_indx%3) + 2];
		last_three[0] = a_box3[3*(box_indx%3)]; last_three[1] = a_box3[3*(box_indx%3) + 1]; last_three[2] = a_box3[3*(box_indx%3) + 2];

		// Add each pointer to each triplet 
		// in a box an array to array of pointers
		arr_ptr[0] = first_three;
	    arr_ptr[1] = second_three;
	    arr_ptr[2] = last_three;

	 	// Call to check group if all numbers 
    	// in row row_index are unique.
	    if(check_group(arr_ptr, 3)) {
	    			return 1;
	    		}
	}
	    
    return 0;
}
