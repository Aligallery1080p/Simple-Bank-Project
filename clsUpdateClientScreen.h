#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsBankClient.h"
#include "D:/Programming/Programming Advices/Course 11/Project2_MS/clsInputValidate.h"
using namespace std;

class clsUpdateClientScreen : protected clsScreen
{
private:
	static void ReadClientInfo(clsBankClient& Client)
	{
		cout << "\nEnter FirstName: ";
		Client.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter LastName: ";
		Client.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email: ";
		Client.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone: ";
		Client.Phone = clsInputValidate::ReadString();

		cout << "\nEnter PinCode: ";
		Client.PinCode = clsInputValidate::ReadString();

		cout << "\nEnter Account Balance: ";
		Client.AccountBalance = clsInputValidate::ReadNumber<float>();
	}

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
	static void ShowUpdateClientScreen()
	{
		if (!clsScreen::CheckAccessRights(clsUser::enPermissions::pUpdateClient))
		{
			return;
		}

		DrawScreenHeader("\t Update Client Screen");

		cout << "\nPlease Enter client Account Number: ";
		string AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number is not found, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);

		char Answer;
		cout << "\nAre you sure you want to update this client y/n? ";
		cin >> Answer;

		if(toupper(Answer) == 'Y')
		{	
			cout << "\n\nUpdate Client Info:";		
			cout << "\n____________________\n";

			ReadClientInfo(Client);

			clsBankClient::enSaveResults SaveResult;
			SaveResult = Client.Save();

			switch (SaveResult)
			{
			case clsBankClient::enSaveResults::svSucceeded:
				cout << "\nAccount Updated Successfully :-)\n";
				_PrintClient(Client);
				break;

			case clsBankClient::enSaveResults::svFaildEmptyObject:
				cout << "\nError account was not saved because it's Empty";
				break;
			}
		}
	}
};

