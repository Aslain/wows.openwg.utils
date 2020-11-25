#include <iostream>

#include "module_wotfinder/api_wotfinder.h"

int main()
{
	std::cout << WOT_GetClientsCount() << std::endl;
	system("pause");
}
