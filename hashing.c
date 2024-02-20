
#include "hashing.h"

#include <string.h>
#include <stdio.h>


#include "sha256.h"

int hash_for_row(unsigned int row_num)
{

	//String buffer to store the column number to be hashed
	char col_counter_buf[7] = {};
	col_counter_buf[0] = '0';

	
	//Buffer that the hash is written to
	char col_hashing_buf[32];

	//Reduced hash value in int form
	unsigned int col_hashing_int;

	//Perform the string concatenation
	//(The first entry is already zero)
	sprintf(col_counter_buf + 1, "%d", row_num);

	//Hash the row number
	sha256(col_counter_buf, strlen(col_counter_buf), col_hashing_buf);	

	char last_int_ptr[4];

	//Reversing byte order
	for(int i = 0; i < 4; i++)
	{
		last_int_ptr[i] = *(col_hashing_buf + 31 - i);
	}

	unsigned int last_int = *(int*)last_int_ptr;

	//Mod 2 to determine which RBF column
	last_int = last_int % 2;

	return last_int;

}

//Start at 1 for iteration
int hash_for_column(int iteration, int rbf_size, char* input)
{

	//Buffer to store the hash value to
	char hashing_buf[32];

	//Buffer to store concatenated input
	char input_buf[strlen(input) + 2];

	//Convert the iteration count to a char
	char iteration_char[2];
	sprintf(iteration_char, "%d", iteration);

	//Perform the string concatenation
	input_buf[0] = iteration_char[0];
	sprintf(input_buf + 1, "%s", input);

	//Hash for the column value
	sha256(input_buf, strlen(input_buf), hashing_buf);

	char last_int_ptr[4];

	//Reversing byte order
	for(int i = 0; i < 4; i++)
	{
		last_int_ptr[i] = *(hashing_buf + 31 - i);
	}

	unsigned int last_int = *(int*)last_int_ptr;

	//Mask off the bottom twenty bits
	last_int = last_int & 0xfffff;

	//Mod by the RBF size
	last_int = last_int % rbf_size;

	return last_int;

}
