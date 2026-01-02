#pragma once
#include<iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsBankClient.h"
#include "D:/Programming/Programming Advices/Course 11/Project2_MS/clsInputValidate.h"
using namespace std;

class clsFindClientScreen : protected clsScreen
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
	static void ShowFindClientScreen()
	{
		if (!clsScreen::CheckAccessRights(clsUser::enPermissions::pFindClient))
		{
			return;
		}

		DrawScreenHeader("\tFind Client Screen");

		cout << "\nPlease Enter Account Number: ";
		string AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number is not found, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);

		if (!Client.IsEmpty())
		{
			cout << "\nClient Found :-)\n";
		}
		else
		{
			cout << "\nClient Was not Found :-(\n";
		}

		_PrintClient(Client);
	}
};

