#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "D:/Programming/Programming Advices/Course 10/Project2_MS/clsString.h"
#include "D:/Programming/Programming Advices/Course 11/Project2_MS/clsInputValidate.h"
using namespace std;

class clsCurrencyCalculatorScreen : protected clsScreen
{
private:
	static void _PrintCurrencyCard(clsCurrency Currency, string Title)
	{
		cout << "\n" << Title;
		cout << "\n_____________________________\n";
		cout << "\nCountry    : " << Currency.Country();
		cout << "\nCode       : " << Currency.CurrencyCode();
		cout << "\nName       : " << Currency.CurrencyName();
		cout << "\nRate(1$) = : " << Currency.Rate();
		cout << "\n_____________________________\n\n";
	}

	static clsCurrency _GetCurrency(string Message)
	{
		string CurrencyCode;
		cout << Message << endl;
		CurrencyCode = clsInputValidate::ReadString();

		while (!clsCurrency::IsCurrencyExist(CurrencyCode))
		{
			cout << "\nCurrency is not found, choose another one: \n";
			CurrencyCode = clsInputValidate::ReadString();
		}

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		return Currency;
	}

	static double _ReadAmount()
	{
		double Amount;
		cout << "\nEnter Amount to Exchange: ";
		cin >> Amount;
		return Amount;
	}

	static void _PrintCalculationsResults(double Amount, clsCurrency CurrencyFrom, clsCurrency CurrencyTo)
	{
		double AmountInUSD = Amount;
		if (CurrencyFrom.CurrencyCode() != "USD")
		{
			_PrintCurrencyCard(CurrencyFrom, "Convert From:");
			AmountInUSD = CurrencyFrom.ConvertToUSD(Amount);
		
			cout << Amount << " " << CurrencyFrom.CurrencyCode()
				<< " = " << AmountInUSD << " USD\n";
		}

		if (CurrencyFrom.CurrencyCode() == "USD")
		{
			if (CurrencyTo.CurrencyCode() == "USD")
			{
				cout << "\nConverting from USD to:\n";
				_PrintCurrencyCard(CurrencyTo, "Convert To:");

				cout << Amount << " " << CurrencyFrom.CurrencyCode()
					<< " = " << AmountInUSD << " USD\n";
			}

			return;
		}
		
		if(CurrencyFrom.CurrencyCode() != "USD")
			cout << "\nConverting from USD to:\n";

		_PrintCurrencyCard(CurrencyTo, "Convert To:");

		double AmountInOtherCurrency = CurrencyFrom.ConvertToOtherCurrency(Amount, CurrencyTo);

		cout << Amount << " " << CurrencyFrom.CurrencyCode() << " = " 
			<< AmountInOtherCurrency << " " << CurrencyTo.CurrencyCode() << endl;
	}

public:
	static void ShowCurrencyCalculatorScreen()
	{ 
		char Answer = 'y';

		while (Answer == 'Y' || Answer == 'y')
		{
			system("cls");
			DrawScreenHeader("\t  Currency Calculator Screen");
	
			clsCurrency CurrencyFrom = _GetCurrency("\nPlease Enter Currency1 Code: ");
			clsCurrency CurrencyTo = _GetCurrency("\nPlease Enter Currency2 Code: ");
			double Amount = _ReadAmount();

			_PrintCalculationsResults(Amount, CurrencyFrom, CurrencyTo);
	
			cout << "\nDo you want to perform another calculation y/n? ";
			cin >> Answer;
		} 
	}
};

