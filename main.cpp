#include "libeFunction.h"

int main() {
	
	sSaper *s;										//create pointe on struct
	int size, nbomb; 
	
	do{
		EntPar(size,nbomb);
		s = (sSaper*)calloc(size, sizeof(sSaper));	//create aaray = size
		EntArr(s,size,nbomb);
		inpCell(s, size, 0, nbomb);

		free(s);
		fflush(stdin);
		getchar();	
	} while(!exitRepeat());

	return 0;
}


