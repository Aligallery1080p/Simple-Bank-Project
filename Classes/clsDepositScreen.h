#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "D:/Programming/Programming Advices/Course 11/Project2_MS/clsInputValidate.h"
using namespace std;

class clsDepositScreen : protected clsScreen
{
private:
	static void _PrintClient(clsBankClient& Client)
	{
		cout << "\nClient Card:\n";
		cout << "___________________\n";
		cout << "FirstName   : " << Client.FirstName << endl;
		cout << "LastName    : " << Client.LastName << endl;
		cout << "Full Name   : " << Client.FullName() << endl;
		cout << "Email       : " << Client.Email << endl;
		cout << "Phone       : " << Client.Phone << endl;
		cout << "Acc. Number : " << Client.AccountNumber() << endl;
		cout << "PinCode     : " << Client.PinCode << endl;
		cout << "Balance     : " << Client.AccountBalance << endl;
		cout << "___________________\n";
	}

	static string _ReadAccountNumber()
	{
		cout << "\nPlease enter AccountNumber? ";
		string AccountNumber = clsInputValidate::ReadString();
		return AccountNumber;
	}

public:
	static void ShowDepositScreen()
	{
		system("cls");
		DrawScreenHeader("\t   Deposit Screen");

		string AccountNumber = _ReadAccountNumber();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
			AccountNumber = _ReadAccountNumber();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);

		double Amount = 0;
		cout << "\nPlease enter deposit amount? ";
		Amount = clsInputValidate::ReadNumber<double>();

		char Answer = 'n';
		cout << "\nAre you sure you want to perform this transaction? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			Client.Deposit(Amount);
			cout << "\nAmount Deposited Successfully.\n";
			cout << "\nNew Balance is: " << Client.AccountBalance;
		}
		else
		{
			cout << "\nOperation was cancelled.\n";
		}
	}
};

