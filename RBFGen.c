#include "RBFGen.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashing.h"
#include "sha256.h"

int main(int argc, char** argv)
{


	if(argc < 2)
	{
		fprintf(stderr, "Usage: ./RBFGen [filter size] <outfile name>\n");
		exit(1);
	}

	char* outfile_name;

	if(argc >=3)
	{
		outfile_name = argv[2];
	}else{
		outfile_name = "output.txt";
	}

	//Parse the size of the filter
	int m = atoi(argv[1]);

	//Generate the bad IP addresses
	char** addresses = generate_ip_addresses();

	//Array to contain the first row of BF values
	char rbf_data[m];

	//Initialize the empty bloom filter
	for(int i = 0; i < m; i++)
	{
		rbf_data[i] = hash_for_row(i);
	}

	//Enter each bad IP
	for(int i = 0; i < 10000; i++)
	{

		//Spin it through the 8 hash functions
		for(int j = 1; j <= 8; j++)
		{
			//Get the desired column
			int column = hash_for_column(j, m, addresses[i]);

			//Get the true row
			int row = hash_for_row(column);

			//If the true row is 0, set it to 1
			if(row == 0)
				rbf_data[column] = 1;
			//Otherwise, set it to 0
			else
				rbf_data[column] = 0;
			
			
		}

	}

	//Open a file to write the results to
	FILE* fptr;
	fptr = fopen(outfile_name, "w");

	for(int i = 0; i < m; i++)
	{
		fprintf(fptr, "%d", rbf_data[i]);
	}

	fclose(fptr);

}

//Generate the IP addresses to be checked
char** generate_ip_addresses()
{
	

	char** addresses = malloc(sizeof(char*) * 10000);

	for(int i = 0; i < 10000; i++)
	{

		char* address = malloc(14);	
		sprintf(address, "192.168.%d.%03d", i/1000, i%1000);
		addresses[i] = address;
		

	}


	return addresses;

}
