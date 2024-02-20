#include "RBFGen.h"

#include <stdio.h>
#include <stdlib.h>

#include "hashing.h"

int main(int argc, char** argv)
{

	//If not enough arguments given, throw usage error
	if(argc < 2)
	{
		fprintf(stderr, "Usage: ./IPCheck <RBF file> [XXX.XXX.X.XXX]\n");
		exit(-1);
	}

	//IP address entered by user
	char* input_IP;

	//File name potentially entered by user
	char* input_file_name;

	unsigned int RBF_size = 0;

	//Parse user arguments
	if(argc == 2)
	{
		input_file_name = "output.txt";
		input_IP = argv[1];
	}
	if(argc >= 3)
	{
		input_file_name = argv[1];	
		input_IP = argv[2];
	}


	//Read the length of the RBF
	FILE* input_file = fopen(input_file_name, "r");

	if(input_file == NULL)
	{
		fprintf(stderr, "Could not find input file \"%s\"\n", input_file_name);
		exit(0);
	}

	//Count the size of the file
	while (fgetc(input_file) != EOF)
		RBF_size++;
	fclose(input_file);

	//Parse the RBF
	unsigned char RBF[RBF_size];
	input_file = fopen(input_file_name, "r");
	
	for(int i = 0; i < RBF_size; i++)
	{
		RBF[i] = fgetc(input_file) - 48;
	}
	fclose(input_file);

	//Spin it through the 8 hash functions
	for(int i = 1; i <= 8; i++)
	{

		//Get the desired column
		int column = hash_for_column(i, RBF_size, input_IP);

		//Get the true row
		int row = hash_for_row(column);

		if(row == 0 && RBF[column] == 0)
		{
			printf("block\n");
			exit(0);
		}

		if(row == 1 && RBF[column] == 1)
		{
			printf("block\n");
			exit(0);
		}

	}

	printf("pass\n");
	exit(0);

}
