#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "D:/Programming/Programming Advices/Course 10/Project2_MS/clsString.h"
using namespace std;

class clsCurrency
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1 };
	enMode _Mode;

	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	double _Rate;

	static clsCurrency _ConvertLineToCurrencyObject(string Line, string Sperator = "#//#")
	{
		vector <string> vCurrencyData;
		vCurrencyData = clsString::Split(Line, Sperator);

		return clsCurrency(enMode::UpdateMode, vCurrencyData[0], vCurrencyData[1],
			vCurrencyData[2], stod(vCurrencyData[3]));
	}

	static string _ConvertCurrencyObjectToLine(clsCurrency& Currency, string Sperator = "#//#")
	{
		string stCurrencyObject = "";

		stCurrencyObject += Currency.Country() + Sperator;
		stCurrencyObject += Currency.CurrencyCode() + Sperator;
		stCurrencyObject += Currency.CurrencyName() + Sperator;
		stCurrencyObject += to_string(Currency.Rate());

		return stCurrencyObject;
	}

	static vector <clsCurrency> _LoadCurrenciesDataFromFile()
	{
		vector <clsCurrency> vCurrencies;
		fstream MyFile("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				vCurrencies.push_back(Currency);
			}

			MyFile.close();
		}

		return vCurrencies;
	}

	static void _SaveCurrenciesDataToFile(vector <clsCurrency> vCurrencies)
	{
		string DataLine;

		fstream MyFile("Currencies.txt", ios::out);//overwrite

		if (MyFile.is_open())
		{
			for (clsCurrency& Currency : vCurrencies)
			{
				DataLine = _ConvertCurrencyObjectToLine(Currency);
				MyFile << DataLine << endl;
			}

			MyFile.close();
		}
	}

	void _Update()
	{
		vector <clsCurrency> vCurrencies = _LoadCurrenciesDataFromFile();

		for (clsCurrency& Currency : vCurrencies)
		{
			if (Currency.CurrencyCode() == CurrencyCode())
			{
				Currency = *this;
				break;
			}
		}

		_SaveCurrenciesDataToFile(vCurrencies);
	}

	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}

public:
	clsCurrency(enMode Mode, string Country, string CurrencyCode,
		string CurrencyName, double Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	string Country()
	{
		return _Country;
	}

	string CurrencyCode()
	{
		return _CurrencyCode;
	}

	string CurrencyName()
	{
		return _CurrencyName;
	}

	void UpdateRate(double Rate)
	{
		_Rate = Rate;
		_Update();
	}

	double Rate()
	{
		return _Rate;
	}

	static clsCurrency FindByCode(string CurrencyCode)
	{
		CurrencyCode = clsString::UpperAllString(CurrencyCode);

		fstream MyFile("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line = "";

			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				if (Currency.CurrencyCode() == CurrencyCode)
				{
					MyFile.close();
					return Currency;
				}
			}

			MyFile.close();
		}

		return _GetEmptyCurrencyObject();
	}

	static clsCurrency FindByCountry(string Country)
	{
		Country = clsString::UpperAllString(Country);

		fstream MyFile("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line = "";

			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				if (clsString::UpperAllString(Currency.Country()) == Country)
				{
					MyFile.close();
					return Currency;
				}
			}

			MyFile.close();
		}

		return _GetEmptyCurrencyObject();
	}

	static bool IsCurrencyExist(string CurrencyCode)
	{
		clsCurrency Currency = FindByCode(CurrencyCode);
		return (!Currency.IsEmpty());
	}

	static vector <clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrenciesDataFromFile();
	}

	double ConvertToUSD(double Amount)
	{
		return double(Amount / Rate());
	}

	double ConvertToOtherCurrency(double Amount, clsCurrency CurrencyTo)
	{
		double AmountInUSD = Amount;

		if (CurrencyCode() != "USD")
		{
			AmountInUSD = ConvertToUSD(Amount);
		}

		return double(AmountInUSD * CurrencyTo.Rate());
	}
};

