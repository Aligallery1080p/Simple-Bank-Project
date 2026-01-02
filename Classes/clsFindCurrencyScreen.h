#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "D:/Programming/Programming Advices/Course 11/Project2_MS/clsInputValidate.h"
using namespace std;

class clsFindCurrencyScreen : protected clsScreen
{
private:

	static short _ReadCurrencyFindMethod()
	{
		cout << "\nFind By: [1] Code or [2] Country? ";
		short CurrencyFindMethod = clsInputValidate::ReadNumberBetween<int>(1, 2, "Wrong Number!, Find By: [1] Code or [2] Country? ");
		return CurrencyFindMethod;
	}

	static void _PrintCurrency(clsCurrency Currency)
	{
		cout << "\nCurrency Card:";
		cout << "\n_____________________________\n";
		cout << "\nCountry    : " << Currency.Country();
		cout << "\nCode       : " << Currency.CurrencyCode();
		cout << "\nName       : " << Currency.CurrencyName();
		cout << "\nRate(1$) = : " << Currency.Rate();
		cout << "\n_____________________________\n";
	}

	static void _ShowResults(clsCurrency Currency)
	{
		if (!Currency.IsEmpty())
		{
			cout << "\nCurrency Found :-)\n";
			_PrintCurrency(Currency);
		}
		else
		{
			cout << "\nCurrency was not found!\n";
		}
	}

public:
	static void ShowFindCurrencyScreen()
	{
		DrawScreenHeader("\t  Find Currency Screen");

		short CurrencyFindMethod = _ReadCurrencyFindMethod();
		clsCurrency Currency = clsCurrency::FindByCode("");

		if (CurrencyFindMethod == 1)
		{
			string CurrencyCode;
			cout << "\nPlease Enter Currency Code: ";
			CurrencyCode = clsInputValidate::ReadString();
			Currency = clsCurrency::FindByCode(CurrencyCode);
			_ShowResults(Currency);
		}
		else
		{
			string CountryName;
			cout << "\nPlease Enter Country Name: ";
			CountryName = clsInputValidate::ReadString();
			Currency = clsCurrency::FindByCountry(CountryName);
			_ShowResults(Currency);
		}
	}
};

