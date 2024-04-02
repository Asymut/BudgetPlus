#pragma once
#ifndef Header_h
#define Header_h

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <iomanip>


class BudgetMiesiac
{
public:
	int id;
	double prize;
	std::string name;

	BudgetMiesiac(int id = 0, std::string = "name", double = 0);

	friend std::vector<BudgetMiesiac> zaladuj_klasy(std::vector<std::vector<std::string>> budzet_miesiac, std::vector<BudgetMiesiac> Budget);

	void zapisBudget(std::vector<BudgetMiesiac> &Budget);

	void stworzBudget(std::vector<BudgetMiesiac> Budget);

	void wyswietlBudget(std::vector<BudgetMiesiac> Budget);

	void modyfikacjaBudget(std::vector<BudgetMiesiac> Budget);

	void dodajBudget(std::vector<BudgetMiesiac> &Budget);
	void usunBudget(std::vector<BudgetMiesiac> &Budget);

};

std::vector<std::vector<std::string>> wczytaj(const std::string& dane);

struct CelFinansowy {
	std::string target_name;
	double target_prize;
	int target_months;
};

std::vector<CelFinansowy> cel();

//Funkcja wyswietlajaca menu
void menu(std::vector<BudgetMiesiac> Budget);
#endif
