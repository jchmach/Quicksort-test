/*
Developed by: Justin Mach
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/*
	Function: is_number
	Purpose: Returns a boolean 1 if the given string is an integer
	Parameters:
		char input - a string that the function checks for	
	Returns: 1 if the input is an integer, 0 otherwise
 */
int is_number(char input[1024]) {
	int boolean = 1;
	int count = 0;
	while (input[count] != '\0') {
		if(isdigit(input[count]) == 0) {
			boolean = 0;
		}
		//if the very first character is '-', then it's a negative sign. Making the number valid. Change boolean back to true
		if (count == 0 && input[count] == '-') {
			boolean = 1;
		}
		count++;
	}
	//if the entered string is empty or if it is just a negative sign, set the boolean to false
	if (input[0] == '\0' || (input[0] == '-' && input[1] == '\0')) {
		boolean = 0;
	}
	return boolean;
}

/*
	Function: insert_array
	Purpose: to take in an integer array pointer of size 10 and ask the user to insert integers into the array
	Parameters:
		int *user_arr this is a pointer to the array in which the user will be filling
	Returns: none
 */
void insert_array(int *user_arr) {
	char input[1024];
	for(int i = 0; i < 10; i++) {
		strcpy(input, "Temp");
		while(is_number(input) == 0) {
			printf("Enter any number: ");
			fgets(input, 1024, stdin);
			input[strcspn(input, "\n")] = '\0';
			if(is_number(input) == 0) {
				printf("You did not enter a number. Try again. \n");
			}
		}
		*(user_arr + i) = atoi(input);
	}
}


/*
	Function: quick_sort
	Purpose: To sort the given array with quicksort
	Parameters:
		int *user_arr a pointer to the array the program is sorting
		int x the index of the element on the left of the pivot; it represents the start of a subarray
		int y the index of the element on the right of the pivot; it represents the end of a subarray
	Returns: none
 */
void quick_sort(int *user_arr, int x, int y) {
	int pivot = *(user_arr + ((x + y) / 2));
	int pivloc = (x + y) / 2;
	int Lcount = x;
	int temp;
	int Rcount = y - 1;
	//swaps the elements of the array if the elements left of the pivot is greater and if the elements
	//right of the pivot is less than the elements
	while(Lcount < Rcount) {
		//loop until you either find an element left of the pivot to be greater than the pivot
		while(*(user_arr + Lcount) <= pivot && Lcount < pivloc) {
			Lcount++;
		}
		//likeweise for the right side
		while(*(user_arr + Rcount) >= pivot && Rcount > pivloc) {
			Rcount--;
		}
		//swap the two elements if both elements are on the wrong side
		if(*(user_arr + Rcount) < pivot && *(user_arr + Lcount) > pivot) {
			temp = *(user_arr + Rcount);
			*(user_arr + Rcount) = *(user_arr + Lcount);
			*(user_arr + Lcount) = temp;
		}
		//if only the left element is in the wrong location, shift the array over until you make room for it and insert it there
		else if(Lcount < pivloc) {
			temp = *(user_arr + Lcount);
			for (int i = Lcount; i < pivloc; i++) {
				*(user_arr + i) = *(user_arr + i + 1);
			}
			*(user_arr + pivloc) = temp;
			pivloc--;
		}
		//likewise for right
		else if(Rcount > pivloc) {
			temp = *(user_arr + Rcount);
			for (int i = Rcount; i > pivloc; i--) {
				*(user_arr + i) = *(user_arr + i - 1);
			}
			*(user_arr + pivloc) = temp;
			pivloc++;
		}
	}
	//recursively call quicksort twice with each array representing a slice between the beginning and the pivot
	//and the pivot to the end of the array. Stop once the number of element of the array is one (the pivot is the only element)
	if(x + 1 <= pivloc) {
		quick_sort(user_arr, x, pivloc);
	}
	if(y - 2 >= pivloc) {
		quick_sort(user_arr, pivloc + 1, y);
	}
}


int main(){
	int user_arr[10];
	char operation[1024];
	int empty = 0;
	while(strcmp(operation, "Exit") != 0) {
		printf("Please enter an operation you would like to perform on an integer array.\n");
		printf("Enter 'Insert' to insert numbers into an array of size 10, 'Sort' to quicksort the current array, 'Print' to print all elements in the array or 'Exit' to stop the program: ");
		fgets(operation,1024,stdin);
		operation[strcspn(operation, "\n")] = '\0';
		if(strcmp(operation, "Insert") == 0) {
			insert_array(user_arr);
			empty = 1;
		}
		else if(strcmp(operation, "Sort") == 0) {
			quick_sort(user_arr, 0 ,10);
		}
		else if(strcmp(operation, "Print") == 0) {
			if (empty == 1){
				for (int i = 0; i < 10; i++) {
					printf("| %d | ", user_arr[i]);
				}
				printf("\n");
			}
			else{
				printf("The list is currently empty.\n");
			}
		}
		else if(strcmp(operation, "Exit") != 0) {
			printf("You entered an invalid operation. Please enter the operation name within the \" quotations. \n");
		}
	}
	return 0;
}