#pragma once
#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsUser.h"
#include "D:/Programming/Programming Advices/Course 11/Project2_MS/clsInputValidate.h"
using namespace std;

class clsDeleteClientScreen : protected clsScreen
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

public:
	static void ShowDeleteClientScreen()
	{
		if (!clsScreen::CheckAccessRights(clsUser::enPermissions::pDeleteClient))
		{
			return;
		}

		DrawScreenHeader("\tDelete Client Screen");

		cout << "\nPlease Enter Account Number: ";
		string AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number is not found, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);

		char Answer;
		cout << "\nAre you sure you want to delete this client? y/n? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			if (Client.Delete())
			{
				cout << "\nClient Delete Successfully :-)\n";
				_PrintClient(Client);
			}
			else
			{
				cout << "\nError Client was not Deleted\n";
			}
		}
	}
};

