#include "Account.hpp"
#include "AccountList.hpp"
#include <iostream>
#include "Importer.h"

using namespace std;

int main() 
{
	AccountList acclist;
	acclist.ImportClass("Class-1.csv");
	//system("pause");
	return 0;
}
