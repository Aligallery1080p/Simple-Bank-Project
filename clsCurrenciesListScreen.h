#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include "clsCurrency.h"
#include "D:/Programming/Programming Advices/Course 11/Project3_MS/clsScreen.h"
using namespace std;

class clsCurrenciesListScreen : protected clsScreen
{
private:
	static void PrintCurrencyRecordLine(clsCurrency Currency)
	{
		cout << setw(8) << left << "" << "| " << left << setw(30) << Currency.Country();
		cout << "| " << left << setw(8) << Currency.CurrencyCode();
		cout << "| " << left << setw(39) << Currency.CurrencyName();
		cout << "| " << left << setw(10) << Currency.Rate();
	}

public:
	static void ShowCurrenciesList()
	{
		vector <clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();
		string Title = "\t  Currencies List Screen";
		string SubTitle = "\t    (" + to_string(vCurrencies.size()) + ") Currencies.";

		DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "\n\t______________________________________________________";
		cout << "__________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(30) << "Country";
		cout << "| " << left << setw(8) << "Code";
		cout << "| " << left << setw(39) << "Name";
		cout << "| " << left << setw(10) << "Rate/(1$)";
		cout << setw(8) << left << "\n\t______________________________________________________";
		cout << "__________________________________________\n" << endl;

		if (vCurrencies.size() == 0)
		{
			cout << "\t\t\tNo Currencies Available in the System!\n";
		}

		for (clsCurrency& Currency : vCurrencies)
		{
			PrintCurrencyRecordLine(Currency);
			cout << endl;
		}

		cout << setw(8) << left << "\n\t______________________________________________________";
		cout << "__________________________________________\n" << endl;
	}
};

