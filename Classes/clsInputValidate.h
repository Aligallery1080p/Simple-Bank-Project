#pragma once
#include <iostream>
#include <string>
#include "D:/Programming/Programming Advices/Course 10/Project3_MS/clsDate.h"

class clsInputValidate
{
public:
	
	template <typename T> static bool IsNumberBetween(T Number, T From, T To) {
		return (Number >= From && Number <= To);
	}

	template <typename T> static bool IsDateBetween(T Date, T Date1, T Date2) {
		if ((clsDate::CompareDates(Date, Date1) == clsDate::enDateCompare::Equal)
			|| (clsDate::CompareDates(Date, Date2) == clsDate::enDateCompare::Equal))
			return true;

		if ((clsDate::CompareDates(Date, Date1) == clsDate::enDateCompare::After)
			&& (clsDate::CompareDates(Date, Date2) == clsDate::enDateCompare::Before))
			return true;
			
		if ((clsDate::CompareDates(Date, Date1) == clsDate::enDateCompare::Before)
			&& (clsDate::CompareDates(Date, Date2) == clsDate::enDateCompare::After))
			return true;

		return false;
	}

	template <typename T> static T ReadNumber(string Message = "Invalid Number, Enter again: ")
	{
		T Number;

		cin >> Number;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << Message;
			cin >> Number;
		}

		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		return Number;
	}

	template <typename T> static T ReadNumberBetween(T From, T To, string Message = "Number is not within range, please enter again:\n") {
		T Number = ReadNumber<T>("Invalid Number, Enter again: ");

		while (Number < From || Number > To) {
			cout << Message;

			Number = ReadNumber<T>("Invalid Number, Enter again: ");
		}

		return Number;
	}

	template <typename T> static bool IsValidDate(T Date) {
		return clsDate::IsValid(Date);
	}

	static string ReadString()
	{
		string String;

		getline(cin >> ws, String);

		return String;
	}

};

