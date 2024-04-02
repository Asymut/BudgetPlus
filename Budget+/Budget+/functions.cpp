#include "Header.h"


std::vector<std::vector<std::string>> wczytaj(const std::string& dane)
{
	std::vector<std::vector<std::string>> budzet_miesiac;
	std::string linia;

	std::ifstream plik(dane);

	if (!plik) {
		std::cerr << "Plik budget.txt nie istnieje" << std::endl;
		return budzet_miesiac;
	}

	while (std::getline(plik, linia))
	{
		std::vector<std::string> wiersz;
		std::istringstream iss(linia);
		std::string pole;
		while (iss >> pole)
		{
			wiersz.push_back(pole);

		}
		budzet_miesiac.push_back(wiersz);
	}
	return budzet_miesiac;
}

std::vector<BudgetMiesiac> zaladuj_klasy(std::vector<std::vector<std::string>> budzet_miesiac, std::vector<BudgetMiesiac> Budget)
{
	for (int i = 0; i < budzet_miesiac.size(); i++) {
		BudgetMiesiac budget(std::stoi(budzet_miesiac[i][0]), budzet_miesiac[i][1], std::stoi(budzet_miesiac[i][2]));
		Budget.push_back(budget);
	}
	return Budget;
}

void BudgetMiesiac::zapisBudget(std::vector<BudgetMiesiac> &Budget) {

	std::ofstream plik("../budget.txt");
	if (plik.is_open()) {

		//iterator z zajec
		for (const auto& x : Budget) {
			plik << x.id << " " << x.name << " " << x.prize << std::endl;
		}
	
		plik.close();

	}
	 
	zaladuj_klasy(wczytaj("../budget.txt"), Budget);

}

BudgetMiesiac::BudgetMiesiac(int lp, std::string imie, double wartosc)
{
	id = lp;
	name = imie;
	prize = wartosc;
}

void BudgetMiesiac::stworzBudget(std::vector<BudgetMiesiac> Budget)
{
	bool check=0;
	double przychod; 
	std::cout << std::endl;
	std::cout << "$ TWORZENIE BUDZETU NA BIEZACY MIESIAC $" << std::endl;
	
	do
	{
		std::cout << "Podaj swoj przychod: " << std::endl;
		//std::cin >> przychod;
			
			if (!(std::cin >> przychod)) {
				std::cout << "Nieprawidlowa postac pensji. ";
				std::cin.clear(); // Resetowanie stanu strumienia
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Ignorowanie danych - bufor
				check = 0;
			} 
			else if (przychod < 0)
			{
				check = 0;
				std::cout << "Przychod nie moze byc ujemny! ";
			}
			else if (przychod >= 0)
			{
				check =1;
			}
			
	} while (!check);

	Budget[0].prize = przychod;

	for(int i=1;i<Budget.size(); i++)
	{
		bool check;
		double wydatek;
		
		do {
		std::cout << "Podaj wartosc wydatkow - " + Budget[i].name + ": " << std::endl;
		std::cin >> wydatek;

			if (std::cin.fail()) 
			{
				std::cout << "Nieprawidlowa postac kwoty wydatku. "<<std::endl;
				std::cin.clear(); // Resetowanie stanu strumienia
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Ignorowanie danych - bufor
				check = 0;
			}
			else if(wydatek < 0)
			{
					std::cout << "Wydatek nie moze byc ujemny!" << std::endl;
					check = 0;
			}
			else {
				check = 1; 
			}
		
		} while (!check);

		Budget[i].prize = wydatek;

		
	}

	Budget[0].zapisBudget(Budget);
	std::cout << "$ BUDZET ZOSTAL STWORZONY $" << std::endl;

	getchar(); getchar();
}

void BudgetMiesiac::wyswietlBudget(std::vector<BudgetMiesiac> Budget)
{	
	system("cls");
	std::cout << std::setw(23) << "$ BUDZET $" << std::endl;
	std::cout << "----------------<$>----------------" << std::endl;
	std::cout << "Przychod: " << Budget[0].prize << " zl" << std::endl;
	std::cout << "----------------<$>----------------" << std::endl;
	std::cout << std::setw(30) << "$ MIESIECZNE WYDATKI $ " << std::endl;
	int suma =0;

	for (int i = 1; i < Budget.size(); i++)
	{
		std::cout << std::setw(5) << std::right << Budget[i].id << std::left << ". " << std::setw(16) << std::left << Budget[i].name << std::setw(10) << std::right << Budget[i].prize << " zl" << std::endl;
		suma += Budget[i].prize;
	}
	
	std::cout << "SUMA MIESIECZNYCH WYDATKOW:     " << suma << " zl" << std::endl;
	std::cout << "----------------<$>----------------" << std::endl;
	std::cout << std::endl;

	std::cout << std::setw(30) << "<$> PODSUMOWANIE <$>   " << std::endl;
	std::cout << "----------------<$>----------------" << std::endl;

	if(Budget[0].prize >= suma)
	{
		std::cout << "OSZCZEDZISZ PO TYM MIESIACU:     " << Budget[0].prize - suma << " zl" << std::endl;
	}
	else if (Budget[0].prize < suma)
	{
		std::cout << "BRAKNIE CI W TYM MIESIACU:  " << Budget[0].prize - suma << " zl" << std::endl;
		std::cout << "-----------------------------------" << std::endl;
		std::cout << "OGRANICZ WYDATKI LUB ZWIEKSZ PRZYCHOD" << std::endl;
		std::cout << "----------------<$>----------------" << std::endl;
	}

	std::vector<CelFinansowy> target;
	std::string linia;

	std::ifstream plik("../cel.txt");

	if (!plik) {
		std::cerr << "Plik cel.txt nie istnieje" << std::endl;
	}

	if (std::getline(plik, linia))
	{
		std::istringstream iss(linia);
		CelFinansowy celFinansowy;
		iss >> celFinansowy.target_name >> celFinansowy.target_prize >> celFinansowy.target_months;
		target.push_back(celFinansowy);
	}

	std::cout << std::endl;
	std::cout << std::setw(30) << "<$> CEL FINANSOWY <$>   " << std::endl;
	std::cout << "----------------<$>----------------" << std::endl;
	std::cout << "Twoj aktualny cel finansowy to: " << target[0].target_name << std::endl;
	std::cout << "Zbierasz kwote " << target[0].target_prize << " zl, przez " << target[0].target_months << " miesiecy " << std::endl;
	std::cout << "-----------------------------<$>-----------------------------" << std::endl;
	std::cout << "Kazdego miesiaca musisz doliczyc do swojego budzetu wydatek " << target[0].target_prize/ target[0].target_months <<"zl na "<< target[0].target_name << "." << std::endl;

	getchar(); getchar();
}

void BudgetMiesiac::dodajBudget(std::vector<BudgetMiesiac> &Budget)
{
	std::string new_kat;
	double wartosc;

	
	auto walidacjaNazwy = [](const std::string& name) {
		for (char x : name) {
			if (x == ' ') {
				return false;
			}
		}
		return true;
	};
	

	auto walidacjaWartosci = [](double value) {
		return value > 0;
	};


	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	do {
		std::cout << "Dodaj nowa kategorie wydatku (podaj nazwe): " << std::endl;
		std::getline(std::cin, new_kat); 

		if (!walidacjaNazwy(new_kat)) {
			std::cout << "Nazwa celu nie moze zawierac spacji. Sprobuj ponownie." << std::endl;
		}
	} while (!walidacjaNazwy(new_kat));

	bool check = 1;
	do {
		std::cout << "Podaj wartosc wydatkow - " << new_kat << ": " << std::endl;

		
		if (!(std::cin >> wartosc)) {
			std::cout << "Nieprawidlowa postac kwoty. ";
			check = 0;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		}

		if (!walidacjaWartosci(wartosc)) {
			std::cout << "Kwota musi byc wieksza od 0. Sprobuj ponownie." << std::endl;
		}


	} while (!walidacjaWartosci(wartosc) || !check);

	

	std::ofstream plik("../budget.txt", std::ios_base::app);
	if (plik)
	{
		int liczba = Budget.size();

		std::string zawartosc = std::to_string(liczba) + " " + new_kat + " " + std::to_string(wartosc);
		plik << zawartosc << std::endl;
		plik.close();
		std::cout << "Dodano nowa kategorie wydatkow " << new_kat << std::endl;
	}
	else
		std::cerr << "Nie mo¿na otworzyæ pliku." << std::endl;
}

void BudgetMiesiac::usunBudget(std::vector<BudgetMiesiac>& Budget)
{
	int id;
	std::string odp;
	std::cout << "Usun istniejaca kategorie wydatku (podaj nr id: 1 - " << Budget.size() - 1 << " ):" << std::endl;
	std::cin >> id;

	if (id < 1 || id >= Budget.size()) {
		std::cout << "Podano nieprawidlowy numer id!" << std::endl;
		return;
	}

	std::string nazwa = Budget[id].name;
	std::cout << "Czy na pewno chcesz usunac kategorie " << nazwa << "? (T/N)" << std::endl;
	std::cin >> odp;

	if (odp == "T" or odp == "t" or odp == "tak")
	{
		
		auto usuwElement = Budget.begin() + id;
		Budget.erase(usuwElement);

		for (auto& elem : Budget)
		{
			if (elem.id > id)
			{
				elem.id -= 1;
			}
		}

		Budget[0].zapisBudget(Budget);

		std::cout << "Usunieto kategorie  " << nazwa << "!" << std::endl;
	}
	else
	{
		std::cout << "Brak potwierdzenia operacji!" << std::endl;
	}
}

void BudgetMiesiac::modyfikacjaBudget(std::vector<BudgetMiesiac> Budget)
{
	system("cls");
	int opcja;
	std::cout << "--------------$--------------" << std::endl;
	std::cout << "Modyfikacja biezacego budzetu" << std::endl;
	std::cout << "--------------$--------------" << std::endl << std::endl;

	std::cout << "Wybierz modyfikacje:" << std::endl;
	std::cout << "1. Dodanie kategori wydatkow" << std::endl;
	std::cout << "2. Usuniecie kategori wydatkow" << std::endl;
	std::cout << "3. Powrot" << std::endl;
	std::cin >> opcja;

	switch (opcja)
	{
	case 1:
		Budget[0].dodajBudget(Budget);
		break;
	case 2:
		Budget[0].usunBudget(Budget);
		break;
	case 3:
		system("cls");
		break;
	default:
	{
		if (opcja > 3)
			std::cerr << "Podana wartosc jest wieksza od 3." << std::endl;
		if (opcja < 1)
			std::cerr << "Podana wartosc jest mniejsza od 1." << std::endl;
		else
			std::cerr << "Podaj wlasciwa wartosc (cyfra 1-3)";
	}
	}
}

std::vector<CelFinansowy> cel()
{

	system("cls");
	std::vector<CelFinansowy> target;
	std::string linia;

	std::string target_name;
	double target_prize;
	int target_months;
	
	auto walidacjaNazwy = [](const std::string& name) {
		for (char x : name) {
			if (x == ' ') {
				return false;
			}
		}
		return true;
	};

	auto walidacjaCeny = [](double prize) {
		return prize > 0;
	};

	auto walidacjaMiesiecy = [](double months) {
		return months > 0;
	};


	std::cout << "* Tworzenie celu finansowego *" << std::endl;

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
	do {
		std::cout << "Podaj nazwe celu: " << std::endl;
		std::getline(std::cin, target_name);

		if (!walidacjaNazwy(target_name)) {
			std::cout << "Nazwa celu nie moze zawierac spacji. Sprobuj ponownie." << std::endl;
		}
	} while (!walidacjaNazwy(target_name));

	do {
		std::cout << "Podaj swoj cel (kwota): " << std::endl;
		std::cin >> target_prize;

		if (!walidacjaCeny(target_prize)) {
			std::cout << "Kwota musi byc wieksza od 0. Sprobuj ponownie." << std::endl;
		}
	} while (!walidacjaCeny(target_prize));


	do {
		std::cout << "Podaj liczbe miesiecy (czas zebrania): " << std::endl;
		std::cin >> target_months;

		if (!walidacjaMiesiecy(target_months)) {
			std::cout << "Liczba miesiecy musi byc dodatnia" << std::endl;
		}
	} while (!walidacjaMiesiecy(target_months));


	std::cout << "* CEL ZOSTAL UTWORZONY *" << std::endl;
	std::cout << "Zbierasz " << target_prize << " zl, na " << target_name << " przez " << target_months << "!" << std::endl;

	CelFinansowy nowyCel;
	nowyCel.target_name = target_name;
	nowyCel.target_prize = target_prize;
	nowyCel.target_months = target_months;

	target.push_back(nowyCel);

	std::ofstream plikZapis("../cel.txt", std::ios::trunc);
	if (plikZapis.is_open()) {
		for (const auto& x : target) {
			plikZapis << x.target_name << " " << x.target_prize << " " << x.target_months << std::endl;
		}

		plikZapis.close();
	}

	std::ifstream plik("../cel.txt");

	if (!plik) {
		std::cerr << "Plik cel.txt nie istnieje" << std::endl;
		return target;
	}

	if (std::getline(plik, linia))
	{
		std::istringstream iss(linia);
		CelFinansowy celFinansowy;
		iss >> celFinansowy.target_name >> celFinansowy.target_prize >> celFinansowy.target_months;
		target.push_back(celFinansowy);
		return target;
	}

}

void menu(std::vector<BudgetMiesiac> Budget)
{
	system("cls");
	std::cout << "-------------$-------------" <<std::endl;
	std::cout << "Witaj w aplikacji Budget+" <<std::endl;
	std::cout << "-------------$-------------" <<std::endl << std::endl;

	int opcja = 0;
	std::cout << "Wybierz opcje: " <<std::endl;
	std::cout << "1. Utworz nowy budzet domowy" <<std::endl;
	std::cout << "2. Zmodyfikuj biezacy budzet" <<std::endl;
	std::cout << "3. Wyswietl raport budzetowy" <<std::endl;
	std::cout << "4. Dodaj cel finansowy" <<std::endl;
	std::cout << "5. Wyjdz z programu" <<std::endl;
	std::cin >> opcja;

	switch(opcja)
	{
	case 1:
		Budget[0].stworzBudget(Budget);
		break;
	case 2:
		Budget[0].modyfikacjaBudget(Budget);
		break;
	case 3:
		Budget[0].wyswietlBudget(Budget);
		break;
	case 4:
		cel();
		
		break;
	case 5: 
		exit(0);
	default:
		{
		
			if (std::cin.fail() || opcja < 1 || opcja > 5) 
			{
				std::cerr << "Podaj wlasciwa wartosc (cyfra 1-5). Wcisnij ENTER!" << std::endl;
			}

			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		getchar(); 
		system("cls");
		
	}


}



