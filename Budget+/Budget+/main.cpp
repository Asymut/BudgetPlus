#include "Header.h"

int main()
{	
	do {
			std::vector<std::vector<std::string>> budzet_miesiac = wczytaj("../budget.txt");
			std::vector<BudgetMiesiac> Budget = zaladuj_klasy(budzet_miesiac, Budget);

			menu(Budget);

	} while (true);

	return 0;
}