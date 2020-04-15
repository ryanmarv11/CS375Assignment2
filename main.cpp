#include "BestFirstSearch.h"
#include <iostream>
#include <stdio.h>

using namespace std;

int main(int argv, char *args[])
{
	if(argv != 3)
	{
		cout << "Error, improper arguments: " << argv << endl;
		exit(1);
	}
	BestFirstSearch BFTS(args);
	return 0;
}