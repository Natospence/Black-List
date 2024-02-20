
#ifndef HASHING_H
#define HASHING_H

//Function used to hash over mod 2 to determine which row of the RBF to use
int hash_for_row(unsigned int);

//Runction used to hash over mod rbf_size to determine which column of the RBF
int hash_for_column(int, int, char*);

#endif
